#include "Missile.h"
void Missile::mainProcess(VECTOR targetPosition ,float remainingTime)
{
	remainingTime = remainingTime / 0.016f;
	Angle = VScale(VNorm(VGet(targetPosition.x-Position.x, targetPosition.y - Position.y, targetPosition.z - Position.z)), 2.3f);
	Position = VAdd(Position, Angle);
    MV1SetPosition(MissileHandle, Position);
    MV1SetRotationXYZ(MissileHandle, Angle);
    MV1DrawModel(MissileHandle);
}
void Missile::SetStartPosition(VECTOR StartPosition)
{
	Position = StartPosition;
}
void Missile::guideLosted()
{
	Position = VAdd(Position, Angle);
    MV1SetPosition(MissileHandle, Position);
    MV1DrawModel(MissileHandle);
}
void Missile::SetUp()
{
    MissileHandle= MV1LoadModel("MissileModel.mv1");
}