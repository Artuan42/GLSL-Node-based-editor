#include "GLSLBody.h"

GLSLBody::GLSLBody(std::deque<GLSLOperations*> BodyOperations)
{
	FullBody += "{\n";

	for (int i = 0; i < BodyOperations.size(); i++)
	{
		FullBody += BodyOperations[i]->ReturnedOperationLine() + '\n';
	}

	FullBody += "}\n";
}
