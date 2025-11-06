#pragma once
#include "DxLib.h"
#include "Trail.h"
class smoke;
class Flare
{
private:
    float timer = 0;
    smoke smokes[180];
    int smokeNum = 0;
public:
    bool isActivated = false;
    VECTOR forward;
    VECTOR position;
    void mainProcess();
    void Passive();
};