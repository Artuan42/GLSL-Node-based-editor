#pragma once

class GLSLParam
{
public:
    GLSLParam(EParamIO, EParam, const std::string);

    std::string GetParam() { return ParamString; };
    std::string GetParamRefName() { return ParamRefName; };

    void SetParamId(int Id) { ParamID = Id; };
    int GetParamId() { return ParamID; };

private:
    std::string ParamRefName;
    std::string ParamString;
    int ParamID;
};
