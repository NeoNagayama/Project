#include "Base.h"
#include<cmath>
void base::Rotate(VECTOR Vector)
{
    MV1SetRotationXYZ(ModelHandle, VAdd(MV1GetRotationXYZ(ModelHandle), Vector));
    Rotation = MV1GetRotationXYZ(ModelHandle);
    Forward = VGet(sin(MV1GetRotationXYZ(ModelHandle).x) * 0.1f, tan(MV1GetRotationXYZ(ModelHandle).y) * 0.1f, cos(MV1GetRotationXYZ(ModelHandle).z) * 0.1f);
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
    forwardDirection.x = 0;
    return forwardDirection;
}