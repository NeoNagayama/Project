#include "Flare.h"
void Flare::mainProcess()
{
    StartPosition = VAdd(StartPosition, forward);
    DrawSphere3D(StartPosition, 0.1f, 32, GetColor(255, 122, 0), GetColor(255, 255, 255), true);
    if (StartPosition.y < -30)
    {
        isActivated = false;
    }
}