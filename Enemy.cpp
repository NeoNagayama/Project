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
        run();
        EnemyMoveXY();
        roll();
    }
    else
    {
        BasePosition = VAdd(playerObject->BasePosition, VGet(0, -5, -50));
        Vulcan();
        missile();
    }
        Move(VAdd(offset,BasePosition));

        MV1DrawModel(ModelHandle);
    Position = MV1GetPosition(ModelHandle);
    SetHitBox(4, 4);
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
            firingInterval = get_rand(2, 10) * 0.1f;
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

        DrawExtendGraph((int)GraphPosition.x - 120, (int)GraphPosition.y - 120, (int)GraphPosition.x + 120, (int)GraphPosition.y + 120, reticleHandle, true);
    }
}
void Enemy::missile()
{
    missilecooldowntimer += 0.016f;
    if (missileCooldown < missilecooldowntimer &&!isLaunched)
    {
        isLaunched = true;
        isGuideLost = false;
    }
    if (isLaunched && !isGuideLost)
    {
        textPositionSet(0, 1920, "!MISSILE ALERT!", BiggerFontHandle, SORT_CENTER, 750, false, GetColor(255, 0, 0));
        missileflyingTimer += 0.016f;
        if (missileflyingTimer > 1)
        {
            
            missileObject.mainProcess(playerObject->Position,3-missileflyingTimer);
        }
        else
        {
            missileObject.SetStartPosition(VGet(BasePosition.x, BasePosition.y, BasePosition.z + 25));
        }
        if (missileflyingTimer > 3)
        {
            isLaunched = false;
            missileflyingTimer = 0;
            missilecooldowntimer = 0;
            playerObject->Health -= 30;
            missileCooldown =  get_rand(50, 70) * 0.1f;
        }

    }
    if (isGuideLost &&missileflyingTimer > 1)
    {
        missileObject.guideLosted();
        DespawnTimer += 0.016f;
        if (DespawnTimer > 2)
        {
            isGuideLost = false;
            isLaunched = false;
            missileflyingTimer = 0;
            missilecooldowntimer = 0;
            missileCooldown = get_rand(50, 70) * 0.1f;
        }
    }
    else if (isGuideLost)
    {
        isGuideLost = false;
        isLaunched = false;
        missileflyingTimer = 0;
        missilecooldowntimer = 0;
        missileCooldown = get_rand(50, 70) * 0.1f;
    }
}

void Enemy::run()
{
    switch (evadetype) {
    case TYPE_BARRELROLL:
        barrelRoll();
        break;
    case TYPE_HORIZONTAL_FLUCTUATING:
        H_Fluctuating();
        break;
    case TYPE_VERTICAL_FLUCTUATING:
        V_Fluctuating();
        break;
    default:
        evadetype = get_rand(-1, 2);
        break;
    }
}
void Enemy::EnemyMoveXY()
{
    if (targetAngle.x > 0.2f && xSpeed < 0.6f)
    {
        xSpeed += 0.1f;
        
    }
    else if (targetAngle.x < -0.2f && xSpeed > -0.6f)
    {
       
        xSpeed -= 0.1f;
       
    }
    else
    {
        xSpeed = 0;
    }
    if (targetAngle.y > 0.2f && ySpeed < 0.6f)
    {
        ySpeed += 0.1f;
    }
    else if (targetAngle.y < -0.2f && ySpeed > -0.6f)
    {
        ySpeed -= 0.1f;
    }
    else
    {
        ySpeed = 0;
    }

    
    xSpeed = (offset.x > moveRange || offset.x < -moveRange) ?0 : xSpeed *moveSpeed;
    
    ySpeed = (offset.y > moveRange || offset.y < -moveRange + 1) ? 0 : ySpeed * moveSpeed;
    
    if (Rotation.y == DegToRad(90))
    {
        offset = VAdd(VGet(0, ySpeed, -xSpeed), offset);
    }
    else if (Rotation.y == DegToRad(-90))
    {
        offset = VAdd(VGet(0, ySpeed, xSpeed), offset);
    }
    else
    {
        offset = VAdd(VGet(xSpeed, ySpeed, 0), offset);
    }
    if (offset.x > moveRange || offset.x < -moveRange)
    {
        offset.x = (offset.x > moveRange) ? moveRange -1 : -moveRange + 1;
    }
    if (offset.y > moveRange || offset.y < -moveRange)
    {
        offset.y = (offset.y > moveRange) ? moveRange -1 : -moveRange + 1;
    }
    if (offset.z > moveRange || offset.z < -moveRange)
    {
        offset.z = (offset.z > moveRange) ? moveRange -1 : -moveRange + 1;
    }
    
}
void Enemy::roll()
{
    float x, y;
    x = cos(atan2(upper().y - 0, upper().x - 0));
    y = sin(atan2(upper().y - 0, upper().x - 0));
    float difInAngle = ((targetAngle.x * y) - (-targetAngle.y  * x));
    if (difInAngle > 0.05f)
    {
        Rotate(VGet(0, 0, -rotateSpeed * smooth(difInAngle, 0, 2)));


    }
    else if (difInAngle < -0.05f)
    {
        Rotate(VGet(0, 0, rotateSpeed * smooth(difInAngle, 0, 2)));

    }
}
void Enemy::barrelRoll()
{
    
    float distance = 0;
    switch (evadeCount) {
    case 1:
        targetAngle = VGet(9 - offset.x, 9 - offset.y, 0);
        distance = sqrtf((targetAngle.x * targetAngle.x) + (targetAngle.y * targetAngle.y));
        targetAngle = VNorm(targetAngle);
        if (distance < 0.08f)
        {
            evadeCount = 2;
        }
        break;
    case 2:
        targetAngle = VGet(9 - offset.x, -5 - offset.y, 0);
        distance = sqrtf((targetAngle.x * targetAngle.x) + (targetAngle.y * targetAngle.y));
        targetAngle = VNorm(targetAngle);
        if (distance < 0.08f)
        {
            evadeCount = 3;
        }
        break;
    case 3:
        targetAngle = VGet(-9 - offset.x, -5 - offset.y, 0);
        distance = sqrtf((targetAngle.x * targetAngle.x) + (targetAngle.y * targetAngle.y));
        targetAngle = VNorm(targetAngle);
        if (distance < 0.08f)
        {
            evadeCount = 0;
            evadetype = 4;
        }
        break;
    default:
        targetAngle = VGet(-9 - offset.x, 9 - offset.y, 0);
        distance = sqrtf((targetAngle.x * targetAngle.x) + (targetAngle.y * targetAngle.y));
        targetAngle = VNorm(targetAngle);
        
        if (distance < 0.08f)
        {
            evadeCount = 1;
        }
        break;
    }
}
void Enemy::H_Fluctuating()
{
    float distance = 0;
    switch (evadeCount) {
    case 1:
        targetAngle = VGet(9 - offset.x, 2 - offset.y, 0);
        distance = sqrtf((targetAngle.x * targetAngle.x) + (targetAngle.y * targetAngle.y));
        targetAngle = VNorm(targetAngle);
        if (distance < 0.08f)
        {
            evadeCount = 2;
        }
        break;
    case 2:
        targetAngle = VGet(-9 - offset.x, -2 - offset.y, 0);
        distance = sqrtf((targetAngle.x * targetAngle.x) + (targetAngle.y * targetAngle.y));
        targetAngle = VNorm(targetAngle);
        if (distance < 0.08f)
        {
            evadeCount = 3;
        }
        break;
    case 3:
        targetAngle = VGet(9 - offset.x, -2 - offset.y, 0);
        distance = sqrtf((targetAngle.x * targetAngle.x) + (targetAngle.y * targetAngle.y));
        targetAngle = VNorm(targetAngle);
        if (distance < 0.08f)
        {
            evadeCount = 0;
            evadetype = 4;
        }
        break;
    default:
        targetAngle = VGet(-9 - offset.x, 2 - offset.y, 0);
        distance = sqrtf((targetAngle.x * targetAngle.x) + (targetAngle.y * targetAngle.y));
        targetAngle = VNorm(targetAngle);
        if (distance < 0.08f)
        {
            evadeCount = 1;
        }
        break;
    }
}
void Enemy::V_Fluctuating()
{
    float distance = 0;
    switch (evadeCount) {
    case 1:
        targetAngle = VGet(2 - offset.x, 9 - offset.y, 0);
        distance = sqrtf((targetAngle.x * targetAngle.x) + (targetAngle.y * targetAngle.y));
        targetAngle = VNorm(targetAngle);
        if (distance < 0.08f)
        {
            evadeCount = 2;
        }
        break;
    case 2:
        targetAngle = VGet(-2 - offset.x, -7 - offset.y, 0);
        distance = sqrtf((targetAngle.x * targetAngle.x) + (targetAngle.y * targetAngle.y));
        targetAngle = VNorm(targetAngle);
        if (distance < 0.08f)
        {
            evadeCount = 3;
        }
        break;
    case 3:
        targetAngle = VGet(-2 - offset.x, 9 - offset.y, 0);
        distance = sqrtf((targetAngle.x * targetAngle.x) + (targetAngle.y * targetAngle.y));
        targetAngle = VNorm(targetAngle);
        if (distance < 0.08f)
        {
            evadeCount = 0;
            evadetype = 4;
        }
        break;
    default:
        targetAngle = VGet(2 - offset.x, -7 - offset.y, 0);
        distance = sqrtf((targetAngle.x * targetAngle.x) + (targetAngle.y * targetAngle.y));
        targetAngle = VNorm(targetAngle);
        if (distance < 0.08f)
        {
            evadeCount = 1;
        }
        break;
    }
}
bool Enemy::Transition()
{
    /*playerObject->BasePosition.z += 1;
    playerObject->Move(VAdd(playerObject->BasePosition, playerObject->offset));*/
    
    MV1DrawModel(ModelHandle);
    if (playerObject->Transition() && transitionMoveZaxis >= 50.0f)
    {
        offset = VGet(playerObject->offset.x + 3, playerObject->offset.y - 2, 0);
        return true;
    }
    else
    {
        BasePosition = VAdd(playerObject->BasePosition, VGet(0, 0, transitionMoveZaxis));
        transitionMoveZaxis += 1.2f;
        Move(VAdd(VGet(playerObject->offset.x + 3, playerObject->offset.y - 2, 0), BasePosition));
        return false;
    }
}