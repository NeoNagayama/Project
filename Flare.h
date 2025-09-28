#pragma once
#include "DxLib.h"
class Flare
{
private:
    float timer = 0;
public:
    bool isActivated = false;
    VECTOR forward;
    VECTOR position;
    void mainProcess();
};