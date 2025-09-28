#pragma once
#include "DxLib.h"
#include "stage1Scene.h"
#include "base.h"
class Bullet
{
private:
    VECTOR position;
public:
    bool isActivated = false;
    VECTOR target;
    VECTOR forward;
    VECTOR StartPosition;
    bool mainProcess(VECTOR hitbox1,VECTOR hitbox2);
};