#pragma once
#include "main.h"
#include "Stage.h"
class builder:public stage
{
private:
    int wipObstacle[50] = { 0 };
    int wipTypes[50] = { 0 };
    int wipMoveWalls[50] = { 0 };
    int pos = 0;
    VECTOR cam = VGet(5, 0, -30);
    float camSpeed = 0.3f;

    void save();
public:
    void Update();
    void Init();
};