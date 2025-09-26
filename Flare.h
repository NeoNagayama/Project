#pragma once
#include "DxLib.h"
class Flare
{
private:
    VECTOR position;
public:
    bool isActivated = false;
    VECTOR forward;
    VECTOR StartPosition;
    void mainProcess();
};