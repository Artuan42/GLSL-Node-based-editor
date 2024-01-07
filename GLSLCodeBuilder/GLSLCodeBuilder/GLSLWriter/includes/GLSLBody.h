#pragma once

#include "GLSLHead.h"
#include "GLSLUtils.h"

class GLSLBody
{
public:
	GLSLBody(std::deque<GLSLOperations*> BodyOperations);

	std::string GetBody() { return FullBody; };
private:
	std::string FullBody;
};