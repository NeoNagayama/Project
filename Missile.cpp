#include "Missile.h"
void Missile::mainProcess(VECTOR targetPosition ,float remainingTime)
{
	remainingTime = remainingTime / 0.016f;
	Angle = VScale(VNorm(VGet(targetPosition.x-Position.x, targetPosition.y - Position.y, targetPosition.z - Position.z)), 2.3f);
	Position = VAdd(Position, Angle);
    MV1SetPosition(MissileHandle, Position);
    MV1SetRotationXYZ(MissileHandle, VNorm(VGet(targetPosition.x - Position.x, targetPosition.y - Position.y, targetPosition.z - Position.z)));
    MV1DrawModel(MissileHandle);
    DrawBillboard3D(VAdd(VScale(MV1GetRotationXYZ(MissileHandle), -2.6f), Position), 0.5f, 0.49f, 4, 0, missileBurnerHandle, true);
    smokes[smokeNum].SetPosition(Position);
    smokeNum++;
    if (smokeNum >= 180)
    {
        smokeNum = 0;
    }
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
    smokes[smokeNum].SetPosition(Position);
    smokeNum++;
    if (smokeNum >= 180)
    {
        smokeNum = 0;
    }
}
void Missile::SetUp()
{
    MissileHandle= MV1LoadModel("MissileModel.mv1");
    for (int i = 0; i < MV1GetMaterialNum(MissileHandle); i++)
    {
        MV1SetMaterialDifColor(MissileHandle, i, GetColorF(0.7f, 0.7f, 0.7f, 1.0f));
        MV1SetMaterialAmbColor(MissileHandle, i, GetColorF(0.2f, 0.2f, 0.2f, 1.0f));
        MV1SetMaterialSpcColor(MissileHandle, i, GetColorF(0.4f, 0.4f, 0.4f, 1));
        MV1SetMaterialEmiColor(MissileHandle, i, GetColorF(0.8f, 0.8f, 0.8f, 0.2f));
        MV1SetMaterialSpcPower(MissileHandle, i, 6);
    }
}
void Missile::Passive()
{
    for (int i = 0; i < 180; i++)
    {
        smokes[i].DrawSmoke();
    }
}