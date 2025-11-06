#pragma once
#include "main.h"
class smoke
{
private:
    VECTOR Position;
    float progress = 256;
    const float LIFETIME = 3;
public:
    void DrawSmoke();
    void SetPosition(VECTOR pos);
};