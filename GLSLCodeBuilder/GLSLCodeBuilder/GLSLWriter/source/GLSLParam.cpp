#include <iostream>
#include <string>
#include "GLSLConstants.h"
#include "GLSLParam.h"

GLSLParam::GLSLParam(EParamIO IOType, EParam Type, const std::string NameParam)
{
    ParamID = 0;
    ParamRefName = NameParam;
    std::string ParamTypeStr;

    switch (Type)
    {
    case EParam::NONE:

        ParamTypeStr = "NONE";
        std::cout << "NONE parameter was created '\n";

        break;

    case EParam::VOID:

        ParamTypeStr = "void";

        break;

    case EParam::FLOAT:

        ParamTypeStr = "float";

        break;
    case EParam::INT:

        ParamTypeStr = "int";

        break;

    case EParam::VEC2:

        ParamTypeStr = "vec2";

        break;

    case EParam::VEC3:

        ParamTypeStr = "vec3";

        break;

    case EParam::VEC4:

        ParamTypeStr = "vec4";

        break;
    }

    ParamString =
        IOType == EParamIO::OUT ? "out " + ParamTypeStr + " " + NameParam :
        IOType == EParamIO::IN ? "in " + ParamTypeStr + " " + NameParam :
        ParamTypeStr + " " + NameParam;

    //std::cout << ParamString << " was created" << '\n';
}