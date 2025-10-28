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
        BasePosition = VAdd(playerObject->BasePosition, VGet(0, 0, 50));
        run();
        EnemyMoveXY();
        roll();
    }
    else
    {
        BasePosition = VAdd(playerObject->BasePosition, VGet(0, 0, -50));
        Vulcan();
        missile();
    }
        Move(VAdd(offset,BasePosition));
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
        FireVulcan(hormingForcex,hormingForcey,distance);
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
        VECTOR GraphPosition = ConvWorldPosToScreenPos(VGet(vulcanTargetPosition.x, vulcanTargetPosition.y, BasePosition.z + 50));
        DrawExtendGraph((int)GraphPosition.x - 70, (int)GraphPosition.y - 70, (int)GraphPosition.x + 70, (int)GraphPosition.y + 70, reticleHandle, true);
    }
}
void Enemy::FireVulcan(float hormingForcex,float hormingForcey,float distance)
{
    firingTimer += 0.016f;
    if (firingTimer > firingRate)
    {
        for (int i = 0; i < 10; i++)
        {
            if (bullets[i].isActivated == false)
            {
                bullets[i].isActivated = true;
                bullets[i].StartPosition = VGet(vulcanTargetPosition.x, vulcanTargetPosition.y, BasePosition.z);
                bullets[i].target = VGet(vulcanTargetPosition.x, vulcanTargetPosition.y, BasePosition.z + 220);
                bullets[i].forward = VGet(0, 0, 5);
                firingTimer = 0;
                LoadedAmmoCount += 1;
                break;
            }

        }

    }
    hormingForcex = playerObject->Position.x - vulcanTargetPosition.x;
    hormingForcey = playerObject->Position.y - vulcanTargetPosition.y;
    distance = sqrtf((hormingForcex * hormingForcex) + (hormingForcey * hormingForcey));
    if (distance > 0.3f)
    {
        vulcanTargetPosition = VAdd(VScale(VNorm(VGet(hormingForcex, hormingForcey, 0)), 0.12f), vulcanTargetPosition);
    }
    if (LoadedAmmoCount >= 10)
    {

        isFiring = false;
        LoadedAmmoCount = 0;
        firingInterval = get_rand(2, 10) * 0.1f;
        firingCooldown = 0;
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
        MissileLaunch();
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
void Enemy::MissileLaunch()
{
    DrawTextWithSort(0, 1920, "!MISSILE ALERT!", BiggerFontHandle, SORT_CENTER, 750, false, GetColor(255, 0, 0));
    DrawTextWithSort(0, 1920, "PRESS SPACE", fontHandle, SORT_CENTER, 790, false, GetColor(255, 255, 0));
    missileflyingTimer += 0.016f;
    if (missileflyingTimer > 1)
    {

        missileObject.mainProcess(playerObject->Position, 3 - missileflyingTimer);
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

    if (offset.x > moveRangeX || offset.x < minimumMoveRangeX)
    {
        targetAngle = VNorm(VGet(1-offset.x,1-offset.y,0));
    }
    if (offset.y > moveRangeY || offset.y < minimumMoveRangeY)
    {
        targetAngle = VNorm(VGet(1-offset.x, 1-offset.y, 0));
    }

    
    xSpeed =xSpeed *moveSpeed;
    
    ySpeed =  ySpeed * moveSpeed;
    
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
    
}
void Enemy::Acceleration()
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
    EvadePosDistance = 0;
    int x = 9 > moveRangeX ? moveRangeX : 9;
    int lowerX = -9 < minimumMoveRangeX ? minimumMoveRangeX : -9;
    int y = 9 > moveRangeY ? moveRangeY : 9;
    int lowerY = -5 < minimumMoveRangeY ? minimumMoveRangeY : -5;
    switch (evadeCount) {
    case 1:

        EvadeMove(x, y, 2);
        break;
    case 2:

        EvadeMove(x, lowerY, 3);
        break;
    case 3:

        EvadeMove(lowerX, lowerY, 0);
        break;
    default:

        EvadeMove(lowerX, y, 1);
        break;
    }
}
void Enemy::H_Fluctuating()
{
    EvadePosDistance = 0;
    int x = 9 > moveRangeX ? moveRangeX : 9;
    int lowerX = -9 < minimumMoveRangeX ? minimumMoveRangeX : -9;
    switch (evadeCount) {
    case 1:

        EvadeMove(x, 2, 2);
        break;
    case 2:

        EvadeMove(lowerX, -2, 3);
        break;
    case 3:
        EvadeMove(x, -2, 0);
        break;
    default:
        EvadeMove(lowerX, 2, 1);
        break;
    }
}
void Enemy::V_Fluctuating()
{
    EvadePosDistance = 0;
    int y = 9 > moveRangeY ? moveRangeY : 9;
    int lowerY = -5 < minimumMoveRangeY ? minimumMoveRangeY : -5;
    switch (evadeCount) {
    case 1:
        EvadeMove(2, y, 2);
        break;
    case 2:
        EvadeMove(-2, lowerY, 3);
        break;
    case 3:
        EvadeMove(-2, y, 0);
        break;
    default:
        EvadeMove(2, lowerY, 1);
        break;
    }
}
void Enemy::EvadeMove(int x,int y,int count)
{
    targetAngle = VGet(x - offset.x, y - offset.y, 0);
    EvadePosDistance = sqrtf((targetAngle.x * targetAngle.x) + (targetAngle.y * targetAngle.y));
    targetAngle = VNorm(targetAngle);
    if (EvadePosDistance < 0.08f)
    {
        evadeCount = count;
        if (count == 0)
        {
            evadetype = 4;
        }
    }
}
bool Enemy::Transition()
{
    /*playerObject->BasePosition.z += 1;
    playerObject->Move(VAdd(playerObject->BasePosition, playerObject->offset));*/
    
    MV1DrawModel(ModelHandle);
    if (playerObject->Transition() && transitionMoveZaxis >= 30.0f)
    {
        offset = VGet(playerObject->offset.x + 3, playerObject->offset.y - 2, 0);
        return true;
    }
    else if (transitionMoveZaxis >= 30.0f)
    {
        Move(VAdd(VGet(playerObject->offset.x + 3, playerObject->offset.y - 2, 0), BasePosition));
        return false;
    }
    else
    {
        BasePosition = VAdd(playerObject->BasePosition, VGet(0, 0, transitionMoveZaxis));
        transitionMoveZaxis += 1.2f;
        Move(VAdd(VGet(playerObject->offset.x + 3, playerObject->offset.y - 2, 0), BasePosition));
        return false;
    }
}