#pragma once
#include "DxLib.h"
#include "main.h"
#include "Player.h"
enum DamageBoxType
{

    NOTHING,
    UPPER,
    LOWER,
    RIGHT,
    LEFT,
    UPPER_LOWER,
    UPPER_RIGHT,
    UPPER_LEFT,
    LOWER_RIGHT,
    LOWER_LEFT,
    RIGHT_LEFT,
    NOT_SELECTED
};
enum MoveWallType
{
    HIGH,
    MID,
    LOW,
    HIGH_MID,
    HIGH_LOW,
    MID_LOW,
};
class explosionEffect;
class Player;
class mapBase
{
private:
    VECTOR edgePosition1, edgePosition2;
    int BaseModelHandle;
public:
    VECTOR position = VGet(0,0,0);
    void DrawbaseOutline();
    bool DamageBox(bool upper, bool lower, bool right, bool left, bool center,VECTOR hitbox1,VECTOR hitbox2);
    void DrawDamageBox(VECTOR edge1,VECTOR edge2);
    bool checkHit(VECTOR edge1, VECTOR edge2, VECTOR playerEdge1, VECTOR playerEdge2,bool current);
    void BaseSetUp();
    bool isHit;
};

class explosion
{
private:
    VECTOR position = VGet(0,-20,0);
    const float maxRadius=6;
    float radius=3;
    const float damping=0.05f;
public:
    bool DrawExplosion();
    void SetPosition(VECTOR edge1,VECTOR edge2);

};
class antiAir :public mapBase
{
private:
    float count = 0;
    timer firingTimer;
    explosionEffect expls[3];
public:
    bool DamageZone(bool upper, bool lower, bool right, bool left, VECTOR hitbox1, VECTOR hitbox2);
    void DrawDamageBoxTransparent(VECTOR edge1, VECTOR edge2);
};
class wallmove :public mapBase
{
private:
    const float returnThleshold = 50;
    const float moveSpeed = get_rand(1,5) * 0.1f;
    const float returnPosition = -50;
    int cargoHandle;
public:
    void MovePosition();
    bool DrawMoveWall(bool high, bool mid, bool low, VECTOR hitbox1, VECTOR hitbox2);
    void DrawHole(VECTOR edge1, VECTOR edge2);
    void SetUp();
};