#include "Flare.h"
void Flare::mainProcess()
{
    timer += 0.016f;
    position = VAdd(position, forward);
    DrawSphere3D(position, 0.1f, 32, GetColor(255, 122, 0), GetColor(255, 255, 255), true);
    if (timer > 4)
    {
        isActivated = false;
        timer = 0;
    }
}