#include "Bullet.h"
void Bullet::mainProcess()
{
    StartPosition = VAdd(StartPosition, VScale(VGet(forward.x,-forward.y,forward.z), 1));
    DrawSphere3D(StartPosition, 0.1f, 32, GetColor(255, 255, 0), GetColor(255, 255, 255), true);
    if (StartPosition.z >= target.z)
    {
        isActivated = false;
    }
}