#include "GLSLFunction.h"

GLSLFunction::GLSLFunction(GLSLHead* Head, GLSLBody* Body)
{
	Functionstr = Head->GetHeadDeclaration() + Body->GetBody();
}
