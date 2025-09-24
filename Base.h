#pragma once
#include "DxLib.h"
#include "main.h"
class base
{
private:
    int m_Handle;
public:
    VECTOR Position;
    VECTOR Rotation;
    VECTOR Scale;
    VECTOR Forward;
    void Rotate(VECTOR Vector);
    void Move(VECTOR Vector);
    float DegToRad(float Euler);
};