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
    forwardDirection.x = sin(Rotation.y);
    return forwardDirection;
}
void base::SetRotation(VECTOR vector)
{
    MV1SetRotationXYZ(ModelHandle, vector);
    Rotation = vector;
}
void base::SetHitBox(float width, float height)
{
    hitbox1 = VGet(Position.x - width / 2, Position.y+0.5f - height / 2, Position.z - width);
    hitbox2 = VGet(Position.x + width / 2, Position.y+0.5f + height / 2, Position.z + width);
    //calcBox();
    DrawhitBoxToUI();
}
void base::calcBox()
{
    Rotation = MV1GetRotationXYZ(ModelHandle);
    hitbox1.x = 3 * cos(Rotation.z);
    hitbox1.y = 1 * sin(Rotation.x);
    hitbox1.z = 2 * sin(Rotation.z);
    hitbox2.x = -3 * cos(Rotation.z);
    hitbox2.y = -1 * sin(Rotation.x);
    hitbox2.z = -2 * sin(Rotation.z);
    hitbox1 = VAdd(hitbox1, Position);
    hitbox2 = VAdd(hitbox2, Position);
}
void base::TestHitBox()
{
    DrawSphere3D(hitbox1, 0.5f, 8, GetColor(255, 255, 0), GetColor(255, 255, 255), true);
    DrawSphere3D(hitbox2, 0.5f, 8, GetColor(255, 255, 0), GetColor(255, 255, 255), true);
}
void base::DrawhitBoxToUI()
{
    DrawCube3D(hitbox1, hitbox2, GetColor(0, 255, 0), GetColor(0, 255, 0), false);
}