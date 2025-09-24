#include "Base.h"
#include<cmath>
void base::Rotate(VECTOR Vector)
{
    MV1SetRotationXYZ(m_Handle, VAdd(MV1GetRotationXYZ(m_Handle), Vector));
    Rotation = MV1GetRotationXYZ(m_Handle);
    Forward = VGet(sin(MV1GetRotationXYZ(m_Handle).x) * 0.1f, tan(MV1GetRotationXYZ(m_Handle).y) * 0.1f, cos(MV1GetRotationXYZ(m_Handle).z) * 0.1f);
}
void base::Move(VECTOR Vector)
{
    MV1SetPosition(m_Handle, VAdd(MV1GetPosition(m_Handle), Vector));
    Position = MV1GetPosition(m_Handle);
}
float  base::DegToRad(float Euler)
{
    return Euler * PI / 180;
}