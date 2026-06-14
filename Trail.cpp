#include "Trail.h"

void smoke::DrawSmoke(float cameraZ)
{
    if (!isActive)
    {
        return;
    }

    if (progress > LIFETIME)
    {
        isActive = false;
        return;
    }

    if (Position.z <= cameraZ)
    {
        return;
    }

    progress += oneFlame;
    const int alpha = (int)(255 * (1 - progress / LIFETIME));
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    DrawBillboard3D(Position, 0.5f, 0.5f, 0.8f, progress, smokeHandle, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void smoke::SetPosition(VECTOR pos)
{
    Position = pos; // •`‰æ‚·‚éˆÊ’u‚Éˆø”‚Ìpos‚ð“ü‚ê‚é
    progress = 0;   // •`‰æ‚µ‚½ŽžŠÔ‚ðƒŠƒZƒbƒg‚·‚é
    isActive = true;
}