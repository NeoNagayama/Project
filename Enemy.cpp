#include"Enemy.h"
#include "stage1Scene.h"
#include <cmath>
#include <random>
void Enemy::InitialProcess()
{
    ModelHandle = MV1LoadModel("F-14Test.mv1");
    MV1SetPosition(ModelHandle, VGet(0, -5, 15));
    MV1SetScale(ModelHandle, VGet(3.5f, 3.5f, 3.5f));
    Position = VGet(0, -5, 15);
}
void Enemy::mainProcess(bool mode)
{
    if (mode)
    {
        BasePosition = VAdd(playerObject->BasePosition, VGet(0, -5, 50));
    }
    else
    {
        BasePosition = VAdd(playerObject->BasePosition, VGet(0, -5, -50));
        Vulcan();
    }
        Move(VAdd(VGet(0, 0, 0),BasePosition));
    Position = MV1GetPosition(ModelHandle);
    MV1DrawModel(ModelHandle);
    SetHitBox(4, 2);
    
}
void Enemy::Vulcan()
{
    firingCooldown += 0.016f;
    float hormingForcex = 0, hormingForcey = 0;
    float distance = 0;
    if (firingInterval < firingCooldown && !isFiring)
    {
        vulcanTargetPosition = playerObject->Position;
        isFiring = true;
    }
    else if (isFiring)
    {
        firingTimer += 0.016f;
        if (firingTimer > firingRate)
        {
            for (int i = 0; i < 10; i++)
            {
                if (bullets[i].isActivated == false)
                {
                    bullets[i].isActivated = true;
                    bullets[i].StartPosition = VGet(vulcanTargetPosition.x, vulcanTargetPosition.y,BasePosition.z);
                    bullets[i].target = VGet(vulcanTargetPosition.x, vulcanTargetPosition.y, BasePosition.z + 220);
                    bullets[i].forward = VGet(0, 0, 3);
                    firingTimer = 0;
                    LoadedAmmoCount += 1;
                    break;
                }
                
            }
            
        }
        hormingForcex = playerObject->Position.x - vulcanTargetPosition.x;
        hormingForcey = playerObject->Position.y - vulcanTargetPosition.y;
        distance = sqrtf((hormingForcex * hormingForcex)+ (hormingForcey * hormingForcey));
        if (distance > 0.3f)
        {
            vulcanTargetPosition = VAdd(VScale(VNorm(VGet(hormingForcex, hormingForcey, 0)), 0.12f), vulcanTargetPosition);
        }
        if (LoadedAmmoCount  >= 10)
        {
                
            isFiring = false;
            LoadedAmmoCount = 0;
            firingInterval = get_rand(5, 30) * 0.1f;
            firingCooldown = 0;
        }
        
    }
    bool isReticleShowUp = false;
    for (int i = 0; i < 10; i++)
    {

        if (bullets[i].isActivated == true)
        {
            
            if (bullets[i].mainProcess(playerObject->hitbox1, playerObject->hitbox2))
            {
                 bullets[i].isActivated = false;
                 playerObject->Health -= 5;
                 
            }
            isReticleShowUp = true;
        }
    }
    if (isReticleShowUp)
    {
        /*clsDx();
        printfDx("\n%f %f %f", VScale(VNorm(VGet(hormingForcex, hormingForcey, 0)), 0.07f).x, VScale(VNorm(VGet(hormingForcex, hormingForcey, 0)), 0.07f).y, VScale(VNorm(VGet(hormingForcex, hormingForcey, 0)), 0.07f).z);*/
        VECTOR GraphPosition = ConvWorldPosToScreenPos(VGet(vulcanTargetPosition.x, vulcanTargetPosition.y, BasePosition.z + 50));

        DrawExtendGraph(GraphPosition.x - 120, GraphPosition.y - 120, GraphPosition.x + 120, GraphPosition.y + 120, reticleHandle, true);
    }
}
int  Enemy::get_rand(int min,int max)
{
    static std::mt19937 mt(0);
    std::uniform_int_distribution<int> get_rand_uni_int(min, max);
    return get_rand_uni_int(mt);
}