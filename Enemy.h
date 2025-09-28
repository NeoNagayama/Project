#pragma once
#include "base.h"
#include "stage1Scene.h"
#include "Bullet.h"
#include "Player.h"
class Player;
class Enemy:public base
{
private:
    Player* playerObject;
    
    float moveSpeed = 0.2f;
    float moveRange = 10;
    float rotateSpeed = 0.04;
    float x, y;
    VECTOR offset = VGet(0, -5, 0);
    VECTOR BasePosition;
    VECTOR targetAngle;
    VECTOR targetAnglePitch;

    float firingTimer = 0;
    float firingRate = 0.2f;
    float firingInterval = 2;
    float firingCooldown = 0;
    bool isFiring = false;
    VECTOR vulcanTargetPosition;
    Bullet bullets[10];
    int firingCount;
public:
    int Health = 100;;

    void InitialProcess();
    void Vulcan();
    void mainProcess(bool mode);
    void roll();
    void pitch();
    void PlayerSet(Player* player)
    {
        playerObject = player;
    }
    int get_rand(int min, int max);
};