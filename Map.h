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
    UPPER_CENTER,
    LOWER_RIGHT,
    LOWER_LEFT,
    LOWER_CENTER,
    RIGHT_LEFT,
    RIGHT_CENTER,
    LEFT_CENTER,
    CENTER,
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
    bool checkHit(VECTOR edge1, VECTOR edge2, VECTOR playerEdge1, VECTOR playerEdge2);
};