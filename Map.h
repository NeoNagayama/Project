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
class Player;
class mapBase
{
private:
    VECTOR edgePosition1, edgePosition2;
public:
    VECTOR position = VGet(0,0,0);
    void DrawbaseOutline();
    bool DamageBox(bool upper, bool lower, bool right, bool left, bool center,VECTOR hitbox1,VECTOR hitbox2);
    void DrawDamageBox(VECTOR edge1,VECTOR edge2);
    bool checkHit(VECTOR edge1, VECTOR edge2, VECTOR playerEdge1, VECTOR playerEdge2,bool current);
};

class explosion
{
private:
    VECTOR position = VGet(0,-20,0);
    float maxRadius=3;
    float radius=3;
    float damping=0.2f;
public:
    bool DrawExplosion();
    void SetPosition(VECTOR edge1,VECTOR edge2);

};
class antiAir :public mapBase
{
private:
    explosion expls[5];
public:
    bool DamageZone(bool upper, bool lower, bool right, bool left, VECTOR hitbox1, VECTOR hitbox2);
    void DrawDamageBoxTransparent(VECTOR edge1, VECTOR edge2);
};