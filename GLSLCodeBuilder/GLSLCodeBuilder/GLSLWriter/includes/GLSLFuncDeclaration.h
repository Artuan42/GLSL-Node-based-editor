#pragma once

#include <iostream>
#include "GLSLConstants.h"

class GLSLHeadDeclaration
{
public:
	GLSLHeadDeclaration(EDeclareType Type, const std::string DeclarationName);

	std::string GetHeadDeclaration() { return HeadFuncDeclaration; };
	std::string GetFuncName() { return HeadFuncName; };

private:
	std::string HeadFuncDeclaration = "";
	std::string HeadFuncName = "";
	std::string HeadFuncType = "";
};
