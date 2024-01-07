#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <fstream>
#include <string>
#include "GLSLHead.h"
#include "GLSLBody.h"
#include "GLSLFunction.h"
#include "glad/glad.h"
#include "glfw3.h"
#include "glfw3.h"
#include "WindowGLFW.h"

using std::string;

void processInput(GLFWwindow* window);

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform float size;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(size * aPos.x, size * aPos.y, size * aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 color;\n"
"void main()\n"
"{\n"
"   FragColor = color;\n"
"}\n\0";

bool Wireframe;

int main()
{
    //Window
    WindowGLFW* Window = new WindowGLFW(800, 600);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    //IMGUI Initizialization
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(Window->GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    static char shadername[128] = "MyGLSLShader";
    const std::string extension = ".glsl";

    float size = 1.0f;
    float color[4] = { 0.8f, 0.3f, 0.02f, 1.0f };
    glUseProgram(shaderProgram);
    glUniform1f(glGetUniformLocation(shaderProgram, "size"), size);
    glUniform4f(glGetUniformLocation(shaderProgram, "color"),
        color[0], color[1], color[2], color[3]);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(Window->GetWindow()))
    {
        // input
        // -----
        processInput(Window->GetWindow());

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // uncomment this call to draw in wireframe polygons.
        if (Wireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        // draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        ImGui::Begin("Settings");
        ImGui::InputText("ShaderName", shadername, IM_ARRAYSIZE(shadername));
        ImGui::Checkbox("WireFrame Mode", &Wireframe);
        ImGui::SliderFloat("Size Geo", &size, 0.1f, 2.0f);
        ImGui::ColorEdit4("Color", color);

        ImDrawData* drawdat = ImGui::GetDrawData();
        ImDrawList* drawlist = ImGui::GetWindowDrawList();

        drawlist->AddLine(ImVec2(0, 0), ImGui::GetMousePos(), ImU32(1), 50);

        if(ImGui::Button("Export Shader", ImVec2(100, 45)))
        {
            //Test shader export
            GLSLParam* param = new GLSLParam(EParamIO::IN, EParam::FLOAT, "Value");
            std::deque<GLSLParam> params = { *param };
            GLSLParameters* Parameters = new GLSLParameters(params);
            GLSLHeadDeclaration* declaration = new GLSLHeadDeclaration(EDeclareType::DECLAREVOID, "main");
            GLSLHead* Head = new GLSLHead(declaration, Parameters);
            GLSLComment* Comment = new GLSLComment("MyComment");
            std::deque<GLSLOperations*> MainOperations = { Comment };
            GLSLBody* Body = new GLSLBody(MainOperations);
            GLSLFunction * function = new GLSLFunction(Head, Body);

            string FinalShader = function->GetFunctionStr();

            //Export shader code into a file
            std::ofstream outfile;
            outfile.open(shadername + extension, std::ios_base::app);//std::ios_base::app

            outfile << FinalShader;

            std::cout << "Shader Exported\n";
            std::cout << FinalShader;
        }

        ImGui::End();

        glUseProgram(shaderProgram);
        glUniform1f(glGetUniformLocation(shaderProgram, "size"), size);
        glUniform4f(glGetUniformLocation(shaderProgram, "color"),
            color[0], color[1], color[2], color[3]);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // glBindVertexArray(0); // no need to unbind it every time 

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(Window->GetWindow());
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        Wireframe = true;

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        Wireframe = false;
}