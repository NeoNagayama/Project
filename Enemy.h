#pragma once
#include "base.h"
class Enemy:public base
{
private:
    float moveSpeed = 0.2f;
    float moveRange = 10;
    float rotateSpeed = 0.04;
    float x, y;
    VECTOR offset = VGet(0, -5, 0);
    VECTOR BasePosition;
    VECTOR targetAngle;
    VECTOR targetAnglePitch;

    float firingTimer = 0;
    float firingRate = 0.07f;
    float firingInterval = 2;
    float firingCooldown = 0;
    bool Launching = false;
public:
    int Health;

    void InitialProcess();
    void Vulcan();
    void mainProcess(bool mode);
    void roll();
    void pitch();
};