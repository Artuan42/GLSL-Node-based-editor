#pragma once

#include <iostream>
#include "glfw3.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class WindowGLFW
{
public:
    WindowGLFW(const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT)
    {
        CreateWindow(SCR_WIDTH, SCR_HEIGHT);
    };

	//~WindowGLFW();

    GLFWwindow* GetWindow() { return Window; };

private:
    GLFWwindow* Window;
	void CreateWindow(const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT);
};

void WindowGLFW::CreateWindow(const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    Window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (Window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(Window);
    glfwSetFramebufferSizeCallback(Window, framebuffer_size_callback);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}