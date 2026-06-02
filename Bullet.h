#pragma once
#include "DxLib.h"
#include "base.h"

class Bullet
{
  private:
    VECTOR position = zeroVector;
    int handle = 0;

  public:
    bool isActivated = false;
    VECTOR target = zeroVector;
    VECTOR forward = zeroVector;
    VECTOR Position = zeroVector;
    bool Main(VECTOR hitbox1, VECTOR hitbox2);
    void setUp();
};