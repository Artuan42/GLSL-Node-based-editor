#pragma once

#include "GLSLParameters.h"
#include "GLSLFuncDeclaration.h"

class GLSLHead
{
public:
	GLSLHead(GLSLHeadDeclaration* Declaration, GLSLParameters* Params);

	std::string GetHeadDeclaration() { return FullHeadDeclaration; };
private:
	std::string FullHeadDeclaration;
};
