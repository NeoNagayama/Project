#pragma once
#include "main.h"
class base
{
private:
    
public:
    int ModelHandle = 0;
    VECTOR Position = zeroVector;
    VECTOR Rotation = zeroVector;
    VECTOR Scale = zeroVector;
    bool isInvisible = false;
    VECTOR BasePosition = zeroVector;
    VECTOR targetAngle = zeroVector;
    float Health = 100;
    VECTOR offset = VGet(0, -5, 0);
    void Rotate(VECTOR Vector);
    void Move(VECTOR Vector);
    float DegToRad(float Euler);
    VECTOR upper() ;
    VECTOR forward();
    VECTOR hitbox1 = zeroVector;
    VECTOR hitbox2 = zeroVector;
    void SetRotation(VECTOR vector);
    void SetHitBox(float width, float height);
    void DrawhitBoxToUI();
    //–¢Žg—p
    void calcBox();
    void Draw();
};