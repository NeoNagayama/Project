#include "Missile.h"
void Missile::mainProcess(VECTOR targetPosition ,float remainingTime)
{
	remainingTime = remainingTime / 0.016f;
	Angle = VScale(VGet(targetPosition.x-Position.x, targetPosition.y - Position.y, targetPosition.z - Position.z), 1/remainingTime);
	Position = VAdd(Position, Angle);
    
	DrawSphere3D(Position,1,8, GetColor(255, 255, 0), GetColor(255, 255, 255), true);
}
void Missile::SetStartPosition(VECTOR StartPosition)
{
	Position = StartPosition;
}
void Missile::guideLosted()
{
	Position = VAdd(Position, Angle);
	DrawSphere3D(Position, 1, 8, GetColor(255, 255, 0), GetColor(255, 255, 255), true);
}