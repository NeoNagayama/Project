#include "DxLib.h"
int progress = 0;
bool fadeout(float time)
{
    float rate = 255 / (time / 0.016f);
    progress += rate;
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, progress);
    DrawBox(0, 0, 2000, 2000, GetColor(0, 0, 0), true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    if (progress >= 255)
    {
        return true;
    }
    return false;
}