#pragma once
#include "DxLib.h"
#include "main.h"
class base
{
private:
    
public:
    int ModelHandle;
    VECTOR Position;
    VECTOR Rotation;
    VECTOR Scale;
    void Rotate(VECTOR Vector);
    void Move(VECTOR Vector);
    float DegToRad(float Euler);
    VECTOR upper();
    VECTOR forward();
    void SetRotation(VECTOR vector);
};