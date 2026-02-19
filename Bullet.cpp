#include "Bullet.h"
bool Bullet::Main(VECTOR hitbox1, VECTOR hitbox2)
{
    
    StartPosition = VAdd(StartPosition, VScale(VGet(forward.x,-forward.y,forward.z * timeScale), 1));
    MV1SetPosition(handle, StartPosition);
    MV1DrawModel(handle);
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
void Bullet::setUp()
{
    handle = MV1DuplicateModel(bulletHandle);
    MV1SetRotationXYZ(handle, VGet(0,0, 45.0f * DX_PI_F / 180.0f ));
}