#pragma once
#include "Base.h"
#include "main.h"
class Missile :public base
{
private:
	VECTOR Angle;
public:
	void mainProcess(VECTOR targetPosition, float remainingTime);
	void SetStartPosition(VECTOR StartPosition);
	void guideLosted();
};