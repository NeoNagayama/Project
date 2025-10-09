#pragma once
#include "base.h"
#include "stage1Scene.h"
#include "Bullet.h"
#include "Player.h"
#include "Missile.h"
#include "fontLoader.h"
enum evadeType
{
    TYPE_BARRELROLL,
    TYPE_HORIZONTAL_FLUCTUATING,
    TYPE_VERTICAL_FLUCTUATING

};
class Player;
class Enemy:public base
{
private:
    Player* playerObject;
    
    float moveSpeed = 0.56f;
    float rotateSpeed = 0.08f;
    float x, y;
    VECTOR offset = VGet(0, -5, 0);
    VECTOR BasePosition;
    VECTOR targetAngle;
    VECTOR targetAnglePitch;

    
    float firingRate = 0.2f;
    float firingInterval = 2.0f;
    VECTOR vulcanTargetPosition;
    Bullet bullets[10];
    int LoadedAmmoCount;
    float missileCooldown = 5.0f;
    float DespawnTimer = 0.0f;

    int evadetype = 0;
    int evadeCount = 0;
    void barrelRoll();
    void H_Fluctuating();
    void V_Fluctuating();
    float xSpeed = 0.0f, ySpeed = 0.0f;
public:
    bool isFiring = false;
    bool isLaunched = false;
    float missilecooldowntimer = 0.0f;
    float missileflyingTimer = 0.0f;
    Missile missileObject;
    float firingCooldown = 0.0f;
    float firingTimer = 0.0f;
    int Health = 100;
    float moveRangeX = 10.0f;
    float minimumMoveRangeX = -10.0f;
    float moveRangeY = 10.0f;
    float minimumMoveRangeY = -10.0f;
    void missile();
    void InitialProcess();
    void Vulcan();
    void mainProcess(bool mode);
    void run();
    void roll();
    void pitch();
    void EnemyMoveXY();
    void PlayerSet(Player* player)
    {
        playerObject = player;
    }
    
    bool isGuideLost = false;
    bool Transition();
    float transitionMoveZaxis = -50.0f;
};