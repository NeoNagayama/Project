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
    //vulcanópÇÃïœêî
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
    void Flare();
    void Vulcan();
    void mainProcess(bool mode);
};