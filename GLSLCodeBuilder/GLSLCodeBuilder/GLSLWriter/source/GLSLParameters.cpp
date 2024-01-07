#include "GLSLParameters.h"

GLSLParameters::GLSLParameters(std::deque<GLSLParam> Params)
{
	Parameters = "(";

	for (int i = 0; i < Params.size(); i++)
	{
		Params[i].SetParamId(i);
		Parameters += Params[i].GetParam() + ", ";
	}
	Parameters.erase(Parameters.find_last_of(","));

	Parameters += ")";
}
