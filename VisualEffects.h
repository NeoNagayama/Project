#pragma once
#include "main.h"
class explosionEffect
{
private:
    VECTOR BasePosition = zeroVector;
    VECTOR Position1 = zeroVector;
    VECTOR Position2 = zeroVector;
    VECTOR Position3 = zeroVector;
    VECTOR Direction1 = VNorm(VGet(3,1,0));
    VECTOR Direction2 = VNorm(VGet(-3,-4, 0));
    VECTOR Direction3 = VNorm(VGet(-6, -1, 0));
    float progress = 256;
    float subExplSize = 0.7f;
    float size = 0;
    float angle = 0;
    const float LIFETIME = 3;
    VECTOR MovePosition(VECTOR pos, VECTOR dir);
    void DrawSubExpl(VECTOR pos, VECTOR dir);
public:
    void DrawExprosion();
    bool DrawSingleExplosion();
    void SetPosition(VECTOR pos);
    
};