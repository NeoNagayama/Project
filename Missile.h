#pragma once
#include "Base.h"
#include "main.h"
#include "Trail.h"
class smoke;
class Missile :public base
{
private:
	VECTOR Angle = VGet(0,0,1);
    int MissileHandle;
    smoke smokes[180];
    int smokeNum = 0;
public:
	void mainProcess(VECTOR targetPosition, float remainingTime,float speed);
	void SetStartPosition(VECTOR StartPosition);
	void guideLosted();
    void SetUp();
    void Passive();
};