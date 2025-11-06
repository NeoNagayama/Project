#include"Trail.h"
void smoke::DrawSmoke()
{
    progress += oneFlame;
    if (progress > LIFETIME)
    {
        return;
    }
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255*(1-progress/LIFETIME));
    DrawBillboard3D(Position, 0.5f, 0.5f, 0.8f,0, smokeHandle,true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    return;
}
void smoke::SetPosition(VECTOR pos)
{
    Position = pos;
    progress = 0;
}