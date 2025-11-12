#pragma once
#include "DxLib.h"
#include "main.h"
class base
{
private:
    
public:
    int ModelHandle;
    VECTOR Position;
    VECTOR Rotation;
    VECTOR Scale;

    VECTOR BasePosition;
    VECTOR targetAngle;
    int Health = 100;
    VECTOR offset = VGet(0, -5, 0);
    void Rotate(VECTOR Vector);
    void Move(VECTOR Vector);
    float DegToRad(float Euler);
    VECTOR upper();
    VECTOR forward();
    VECTOR hitbox1;
    VECTOR hitbox2;
    void SetRotation(VECTOR vector);
    void SetHitBox(float width, float height);
    void TestHitBox();
    void DrawhitBoxToUI();
    void calcBox();
};