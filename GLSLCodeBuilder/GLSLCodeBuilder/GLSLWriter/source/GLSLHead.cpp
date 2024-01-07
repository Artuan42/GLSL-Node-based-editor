#include "GLSLHead.h"

GLSLHead::GLSLHead(GLSLHeadDeclaration* Declaration, GLSLParameters* Params)
{
	FullHeadDeclaration = Declaration->GetHeadDeclaration() + Params->GetGLSLParameters() + '\n';
}
