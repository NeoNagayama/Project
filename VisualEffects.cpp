#include "VisualEffects.h"
void explosionEffect::DrawExprosion()
{
    progress += oneFlame;
    size += 20 * oneFlame;
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * (1 - progress / LIFETIME));
    DrawBillboard3D(BasePosition, 0.5f, 0.5f, size, 0, explosionHandle, true);
    DrawSubExpl(Position1, Direction1);
    DrawSubExpl(Position2, Direction2);
    DrawSubExpl(Position3, Direction3);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
bool explosionEffect::DrawSingleExplosion()
{
    progress += oneFlame;
    size += 20 * oneFlame;
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * (1 - progress / (LIFETIME-1.5f)));
    DrawBillboard3D(BasePosition, 0.5f, 0.5f, size, 0, explosionHandle, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    return (progress > LIFETIME ? true : false);
}
void explosionEffect::SetPosition(VECTOR pos)
{
    size = 2;
    progress = 0;
    BasePosition = pos;
    Position1 = BasePosition;
    Position2 = BasePosition;
    Position3 = BasePosition;
}
VECTOR explosionEffect::MovePosition(VECTOR pos ,VECTOR dir)
{
    return VAdd(pos, VScale(dir,3));
}
void explosionEffect::DrawSubExpl(VECTOR pos,VECTOR dir)
{
    pos = MovePosition(pos, dir);
    DrawBillboard3D(pos, 0.5f, 0.5f, size * subExplSize, 0, explosionHandle, true);
}