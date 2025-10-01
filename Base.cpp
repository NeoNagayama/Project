#include "Base.h"
#include<cmath>
void base::Rotate(VECTOR Vector)
{
    MV1SetRotationXYZ(ModelHandle, VAdd(MV1GetRotationXYZ(ModelHandle), Vector));
    Rotation = MV1GetRotationXYZ(ModelHandle);
}
void base::Move(VECTOR Vector)
{
    MV1SetPosition(ModelHandle, Vector);
    Position = MV1GetPosition(ModelHandle);
}
float  base::DegToRad(float Euler)
{
    return Euler * PI / 180;
}
VECTOR base::upper()
{
    VECTOR upperDirection;
    Rotation = MV1GetRotationXYZ(ModelHandle);
    upperDirection.y = cos(Rotation.z);
    upperDirection.x = sin(Rotation.z);
    upperDirection.z = 0;
    return upperDirection;
}
VECTOR base::forward()
{
    VECTOR forwardDirection;
    Rotation = MV1GetRotationXYZ(ModelHandle);
    forwardDirection.z = cos(Rotation.x);
    forwardDirection.y = sin(Rotation.x);
    forwardDirection.x = tan(Rotation.y);
    return forwardDirection;
}
void base::SetRotation(VECTOR vector)
{
    MV1SetRotationXYZ(ModelHandle, vector);
    Rotation = vector;
}
void base::SetHitBox(float width, float height)
{
    hitbox1 = VGet(Position.x - width / 2, Position.y - height / 2, Position.z - width);
    hitbox2 = VGet(Position.x + width / 2, Position.y + height / 2, Position.z + width);
    DrawhitBoxToUI();
}
void base::TestHitBox()
{
    DrawSphere3D(hitbox1, 0.5f, 8, GetColor(255, 255, 0), GetColor(255, 255, 255), true);
    DrawSphere3D(hitbox2, 0.5f, 8, GetColor(255, 255, 0), GetColor(255, 255, 255), true);
}
void base::DrawhitBoxToUI()
{
    /*VECTOR screenPos1 = ConvWorldPosToScreenPos(hitbox1);
    VECTOR screenPos2 = ConvWorldPosToScreenPos(hitbox2);
    VECTOR screenPos3 = ConvWorldPosToScreenPos(VGet(hitbox1.x,hitbox1.y,hitbox2.z));
    VECTOR screenPos4 = ConvWorldPosToScreenPos(VGet(hitbox2.x, hitbox2.y, hitbox1.z));
    SetDrawZ(0.1f);
    DrawBox(screenPos1.x, screenPos1.y, screenPos2.x, screenPos2.y, GetColor(0,255,0),false,0.2f);
    DrawBox(screenPos3.x, screenPos3.y, screenPos4.x, screenPos4.y, GetColor(0, 255, 255), false, 0.2f);*/
    DrawLine3D((hitbox1), VGet(hitbox1.x, hitbox1.y, hitbox2.z),GetColor(0, 255, 0));
    DrawLine3D((hitbox1), VGet(hitbox2.x, hitbox1.y, hitbox1.z), GetColor(0, 255, 0));
    DrawLine3D((hitbox1), VGet(hitbox1.x, hitbox2.y, hitbox1.z), GetColor(0, 255, 0));
    DrawLine3D((hitbox2), VGet(hitbox2.x, hitbox1.y, hitbox2.z), GetColor(0, 255, 0));
    DrawLine3D((hitbox2), VGet(hitbox2.x, hitbox2.y, hitbox1.z), GetColor(0, 255, 0));
    DrawLine3D((hitbox2), VGet(hitbox1.x, hitbox2.y, hitbox2.z), GetColor(0, 255, 0));
    DrawLine3D(VGet(hitbox2.x, hitbox1.y, hitbox1.z), VGet(hitbox2.x, hitbox2.y, hitbox1.z), GetColor(0, 255, 0));
    DrawLine3D(VGet(hitbox2.x, hitbox1.y, hitbox1.z), VGet(hitbox2.x, hitbox1.y, hitbox2.z), GetColor(0, 255, 0));
    DrawLine3D(VGet(hitbox1.x, hitbox2.y, hitbox2.z), VGet(hitbox1.x, hitbox2.y, hitbox1.z), GetColor(0, 255, 0));
    DrawLine3D(VGet(hitbox1.x, hitbox2.y, hitbox2.z), VGet(hitbox1.x, hitbox1.y, hitbox2.z), GetColor(0, 255, 0));
    DrawLine3D(VGet(hitbox1.x, hitbox1.y, hitbox2.z), VGet(hitbox2.x, hitbox1.y, hitbox2.z), GetColor(0, 255, 0));
    DrawLine3D(VGet(hitbox1.x, hitbox2.y, hitbox1.z), VGet(hitbox2.x, hitbox2.y, hitbox1.z), GetColor(0, 255, 0));
}