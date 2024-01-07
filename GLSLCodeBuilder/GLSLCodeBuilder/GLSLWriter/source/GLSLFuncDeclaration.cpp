#include "GLSLFuncDeclaration.h"

GLSLHeadDeclaration::GLSLHeadDeclaration(EDeclareType Type, const std::string DeclarationName)
{
	HeadFuncName = DeclarationName;

	switch (Type)
	{
	case DECLARENONE:
		HeadFuncType = "None";
		std::cout << "NONE function was declared";
		break;

	case DECLAREVOID:
		HeadFuncType = "void";
		break;

	case DECLARESTRUCT:
		HeadFuncType = "struct";
		break;

	case DECLAREFLOAT:
		HeadFuncType = "float";
		break;
	}

	HeadFuncDeclaration = HeadFuncType + " " + HeadFuncName;
}