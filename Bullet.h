#pragma once
#include "DxLib.h"
class Bullet
{
private:
    VECTOR position;
public:
    bool isActivated = false;
    VECTOR target;
    VECTOR forward;
    VECTOR StartPosition;
    void mainProcess();
};