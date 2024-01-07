#pragma once

enum EParam
{
    NONE  = 0,
    VOID  = 1,
    FLOAT = 2,
    INT   = 3,
    VEC2  = 4,
    VEC3  = 5,
    VEC4  = 6
};

enum EParamIO
{
    IONONE = 0,
    IN   = 1,
    OUT  = 2
};

enum EDeclareType
{
    DECLARENONE = 0,
    DECLAREVOID = 1,
    DECLARESTRUCT = 2,
    DECLAREFLOAT = 3,
};
