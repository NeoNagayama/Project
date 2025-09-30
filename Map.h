#pragma once
#include "DxLib.h"
#include "main.h"
class mapBase
{
public:
    VECTOR position;
    void DrawbaseOutline();
    void DrawDamageBox(bool upper, bool lower, bool right, bool left, bool center);
};