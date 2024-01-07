#pragma once

#include <iostream>
#include "GLSLHead.h"

class GLSLOperations
{
public:
	virtual std::string ReturnedOperationLine() { return "Operator"; };

};

class GLSLComment : public GLSLOperations
{
public:
	GLSLComment(std::string Comment) { M_Comment = "\t//" + Comment + '\n'; };
	virtual std::string ReturnedOperationLine() { return M_Comment; };

private:
	std::string M_Comment;
};