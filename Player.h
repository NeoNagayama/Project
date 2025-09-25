#pragma once
#include"DxLib.h"
#include "base.h"
#include"Input.h"
class Player: public base
{
private:
    int PlayerLightHandle;
    float moveSpeed= 0.2f;
    float moveRange = 10;
    float rotateSpeed = 0.04;
    float x, y;
    void KeyInput();
    void PlayerMoveXY();
    VECTOR offset = VGet(0,-5,0);
    VECTOR BasePosition;
    VECTOR targetAngle;
    VECTOR targetAnglePitch;
    //機銃とフレア用の変数
    float firingTimer = 0;
    float FlareCoolDown = 0;
    float FlareFiringTimer = 0;
    float firingRate = 0.07f;
    float FlareFiringRate = 0.1f;
    float FlareInterval = 5;
    bool Launching = false;
    int FlareAmount = 10;
    int maxAmmo = 200;
public:
    int ammo = 200;
    void InitialProcess();
    void Flare();
    void Vulcan();
    void mainProcess(bool mode);
    void rotatePlayer();
    void pitch();
};