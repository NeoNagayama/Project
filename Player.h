#pragma once
#include"DxLib.h"
#include "base.h"
#include"Input.h"
#include "bullet.h"
#include "Flare.h"
#include "Enemy.h"
#include "Text.h"
class Enemy;
class Player: public base
{
private:
    UIText VulcanText;
    UIText FlareText;
    Enemy* enemyObject;
    const float NEUTRAL_ANGLE_Y = 0.99f;
    const int TARGET_CAMERA_POSZ = 20;
    int PlayerLightHandle;
    const float moveSpeed= 0.2f;
    float speedLimit = 0.7f;
    const float moveRange = 11;
    const float rotateSpeed = 0.08f;
    float x, y;
    void KeyInput();
    void PlayerMoveXY();
    VECTOR targetAnglePitch;
    float bulletPositionX[50];
    float bulletPositionY[50];
    //機銃とフレア用の変数
    float firingTimer = 0;
    float FlareCoolDown = 0;
    float FlareFiringTimer = 0;
    const float firingRate = 0.07f;
    const float FlareFiringRate = 0.1f;
    const float FlareInterval = 5;
    bool Launching = false;
    int FlareAmount = 10;
    const int maxAmmo = 200;
    Bullet bullets[200];
    Flare Flares[10];
    VECTOR CameraPosition;
    void FlareLaunch();
    void VulcanProjectile();
    void InputUp(float speed);
    void InputDown(float speed);
    void InputNeutral(float speed);
    void Limit();
public:
    int ammo = 200;
    void InitialProcess();
    void Flare();
    void Vulcan();
    void mainProcess(bool mode);
    void rotatePlayer();
    void pitch();
    void transitionProcess(bool mode);
    void autoEvade();
    void EnemySet(Enemy* enemy)
    {
        enemyObject = enemy;
    }
    bool Transition();
};