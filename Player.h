#pragma once
#include"DxLib.h"
#include "base.h"
#include"Input.h"
class Player: public base
{
private:
    float moveSpeed= 1.5f;
    float moveRange = 200;
    float x, y;
    void KeyInput();
    void PlayerMoveXY();
    VECTOR offset;
    VECTOR BasePosition;
public:
    void Flare();
    void Vulcan();
    void mainProcess();
};