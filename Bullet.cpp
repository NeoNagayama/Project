#include "Bullet.h"
bool Bullet::mainProcess(VECTOR hitbox1, VECTOR hitbox2)
{
    StartPosition = VAdd(StartPosition, VScale(VGet(forward.x,-forward.y,forward.z), 1));
    
    DrawSphere3D(StartPosition, 0.3f, 32, GetColor(255, 255, 0), GetColor(255, 255, 255), true);
    if (StartPosition.z >= target.z)
    {
        isActivated = false;
    }
    if (StartPosition.x > hitbox1.x && StartPosition.y > hitbox1.y && StartPosition.z > hitbox1.z && StartPosition.x < hitbox2.x && StartPosition.y < hitbox2.y && StartPosition.z < hitbox2.z)
    {
        
        isActivated = false;
        return true;
    }
    /*clsDx();
    printfDx("%f %f\n", hitbox1.z, hitbox2.z);*/
    return false;
}