#pragma once

#include "GLSLBody.h"

class GLSLFunction
{
public:
	GLSLFunction(GLSLHead* Head, GLSLBody* Body);

	std::string GetFunctionStr() { return Functionstr; };
private:

	std::string Functionstr;
};