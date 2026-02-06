#pragma once
#include "main.h"
class smoke
{
private:
    VECTOR Position = VGet(0,0,0);
    float progress = 256;
    const float LIFETIME = 3;
public:
    void DrawSmoke();
    void SetPosition(VECTOR pos);
};