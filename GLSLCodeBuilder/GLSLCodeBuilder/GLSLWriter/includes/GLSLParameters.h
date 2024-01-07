#pragma once

#include <iostream>
#include <sstream>
#include <queue>
#include "GLSLConstants.h"
#include "GLSLParam.h"

class GLSLParameters
{
public:
	
	GLSLParameters(std::deque<GLSLParam> Params);

	std::string GetGLSLParameters() { return Parameters; };

private:
	std::string Parameters;

};
