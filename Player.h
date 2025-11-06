#pragma once
#include"DxLib.h"
#include "base.h"
#include"Input.h"
#include "bullet.h"
#include "Flare.h"
#include "Enemy.h"
#include "Text.h"
#include "VisualEffects.h"
class Enemy;
class explosionEffect;
class Player: public base
{
private:
    UIText VulcanText;
    UIText FlareText;
    explosionEffect exp;
    Enemy* enemyObject;
    static constexpr float NEUTRAL_ANGLE_Y = 0.99f;
    static constexpr int TARGET_CAMERA_POSZ = 20;
    static constexpr float moveSpeed= 0.4f;
    float speedLimit = 0.7f;
    static constexpr float moveRange = 11;
    static constexpr float rotateSpeed = 0.08f;
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
    static constexpr float firingRate = 0.07f;
    static constexpr float FlareFiringRate = 0.1f;
    static constexpr float FlareInterval = 5;
    bool Launching = false;
    int FlareAmount = 10;
    static constexpr int maxAmmo = 200;
    Bullet bullets[200];
    Flare Flares[10];
    VECTOR CameraPosition;
    void FlareLaunch();
    void VulcanProjectile();
    void InputUp(float speed);
    void InputDown(float speed);
    void InputNeutral(float speed);
    void rotateOnlyRoll();
    void autoLevel();
    void Limit();
public:
    int ammo = 200;
    bool isDead = false;
    void InitialProcess();
    void Flare();
    void Vulcan();
    void mainProcess(bool mode);
    void rotatePlayer();
    void pitch();
    void transitionProcess(bool mode);
    void clearProcess();
    void autoEvade();
    void EnemySet(Enemy* enemy)
    {
        enemyObject = enemy;
    }
    bool Transition();
};