#pragma once
#include "Base.h"
#include "main.h"
class Missile :public base
{
private:
	VECTOR Angle = VGet(0,0,1);
    int MissileHandle;
public:
	void mainProcess(VECTOR targetPosition, float remainingTime);
	void SetStartPosition(VECTOR StartPosition);
	void guideLosted();
    void SetUp();
};