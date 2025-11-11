#include"Enemy.h"
#include <cmath>
#include <random>
void Enemy::InitialProcess()
{
    ModelHandle = MV1LoadModel("EnemyModel.mv1");
    MV1SetPosition(ModelHandle, VGet(0,0, 0));
    MV1SetScale(ModelHandle, VGet(6, 6, 6));
    Position = VGet(0, 0, 0);
    missileObject.SetUp();
    for (int i = 0; i < MV1GetMaterialNum(ModelHandle); i++)
    {
        MV1SetMaterialDifColor(ModelHandle, i, GetColorF(0.7f, 0.7f, 0.7f, 1.0f));
        MV1SetMaterialAmbColor(ModelHandle, i, GetColorF(0.2f, 0.2f, 0.2f, 1.0f));
        MV1SetMaterialSpcColor(ModelHandle, i, GetColorF(0.4f, 0.4f, 0.4f, 1));
        MV1SetMaterialEmiColor(ModelHandle, i, GetColorF(0.8f, 0.8f, 0.8f, 0.2f));
        MV1SetMaterialSpcPower(ModelHandle, i, 6);
    }
}
void Enemy::mainProcess(bool mode)
{
    if (Health > 0)
    {
        if (mode)
        {
            BasePosition = VAdd(playerObject->BasePosition, VGet(0, 0, Z_OFFSET));
            run();
            EnemyMoveXY();
            roll();
        }
        else
        {
            BasePosition = VAdd(playerObject->BasePosition, VGet(0, 0, -Z_OFFSET));
            Vulcan();
            missile();
            missileObject.Passive();
        }
    }
    if (!isDead && Health <= 0)
    {
        exp.SetPosition(Position);
        deadPosition = Position;
        isDead = true;
    }
        Move(VAdd(offset,BasePosition));
    Position = MV1GetPosition(ModelHandle);
    SetHitBox(4, 4);
    exp.DrawExprosion();
}
void Enemy::Vulcan()
{
    firingCooldown += oneFlame;
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
            
            if (bullets[i].mainProcess(playerObject->hitbox1, playerObject->hitbox2,enemyBulletHandle))
            {
                 bullets[i].isActivated = false;
                 playerObject->Health -= BULLET_DAMAGE;
            }
            isReticleShowUp = true;
        }
    }
    if (isReticleShowUp)
    {
        VECTOR GraphPosition = ConvWorldPosToScreenPos(VGet(vulcanTargetPosition.x, vulcanTargetPosition.y, BasePosition.z + RETICLE_POS_Z));
        DrawExtendGraph((int)GraphPosition.x - RETICLE_SIZE, (int)GraphPosition.y - RETICLE_SIZE, (int)GraphPosition.x + RETICLE_SIZE, (int)GraphPosition.y + RETICLE_SIZE, reticleHandle, true);
    }
}
void Enemy::FireVulcan(float hormingForcex,float hormingForcey,float distance)
{
    firingTimer += oneFlame;
    if (firingTimer > firingRate)
    {
        for (int i = 0; i < 10; i++)
        {
            if (bullets[i].isActivated == false)
            {
                bullets[i].isActivated = true;
                bullets[i].StartPosition = VGet(vulcanTargetPosition.x, vulcanTargetPosition.y, BasePosition.z);
                bullets[i].target = VGet(vulcanTargetPosition.x, vulcanTargetPosition.y, BasePosition.z + BULLET_TARGET_Z);
                bullets[i].forward = VGet(0, 0, BULLET_FORWARD_VELOCITY);
                firingTimer = 0;
                LoadedAmmoCount += 1;
                break;
            }

        }

    }
    hormingForcex = playerObject->Position.x - vulcanTargetPosition.x;
    hormingForcey = playerObject->Position.y - vulcanTargetPosition.y;
    distance = sqrtf((hormingForcex * hormingForcex) + (hormingForcey * hormingForcey));
    if (distance > HORMING_THLESHOLD)
    {
        vulcanTargetPosition = VAdd(VScale(VNorm(VGet(hormingForcex, hormingForcey, 0)), HORMING_SPEED_SCALE), vulcanTargetPosition);
    }
    if (LoadedAmmoCount >= MAX_PROJECTILE)
    {

        isFiring = false;
        LoadedAmmoCount = 0;
        firingInterval = get_rand(2, 10) * 0.1f;
        firingCooldown = 0;
    }
}
void Enemy::missile()
{
    missilecooldowntimer += oneFlame;
    if (missileCooldown < missilecooldowntimer &&!isLaunched)
    {
        isLaunched = true;
        isGuideLost = false;
    }
    if (isLaunched && !isGuideLost)
    {
        MissileLaunch();
    }
    if (isGuideLost &&missileflyingTimer > MISSILE_SHOWUP)
    {
        missileObject.guideLosted();
        DespawnTimer += oneFlame;
        if (DespawnTimer > MISSILE_LIFETIME)
        {
            isGuideLost = false;
            isLaunched = false;
            missileflyingTimer = 0;
            missilecooldowntimer = 0;
            missileCooldown = get_rand(5, 7);
        }
    }
    else if (isGuideLost)
    {
        isGuideLost = false;
        isLaunched = false;
        missileflyingTimer = 0;
        missilecooldowntimer = 0;
        missileCooldown = get_rand(5, 7);
    }
}
void Enemy::MissileLaunch()
{
    if (strobo.MeasureTimer(0.3f))
    {
        strobo.RestartTimer();
        isHide = !isHide;
    }
    if (!isHide)
    {
        DrawExtendGraph(670, 630, 1250, 740, alertGraph, true);
    }
    DrawExtendGraph(670, 765, 1250, 900, spaceGraph, true);
    missileflyingTimer += oneFlame;
    if (missileflyingTimer > MISSILE_SHOWUP)
    {

        missileObject.mainProcess(playerObject->Position, MISSILE_HIT_TIME - missileflyingTimer);
    }
    else
    {
        missileObject.SetStartPosition(VGet(BasePosition.x, BasePosition.y, BasePosition.z + MISSILE_SPAWN_OFFSET));
    }
    if (missileflyingTimer > MISSILE_HIT_TIME)
    {
        isLaunched = false;
        missileflyingTimer = 0;
        missilecooldowntimer = 0;
        playerObject->Health -= MISSILE_DAMAGE;
        missileCooldown = get_rand(5, 7);
        exp.SetPosition(playerObject->Position);
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

    Acceleration();
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
    if (targetAngle.x > MOVE_ANGLE_THLESHOLD && xSpeed < MAX_SPEED)
    {
        xSpeed += SPEED;

    }
    else if (targetAngle.x < -MOVE_ANGLE_THLESHOLD && xSpeed > -MAX_SPEED)
    {

        xSpeed -= SPEED;

    }
    else
    {
        xSpeed = 0;
    }
    if (targetAngle.y > MOVE_ANGLE_THLESHOLD && ySpeed < MAX_SPEED)
    {
        ySpeed += SPEED;
    }
    else if (targetAngle.y < -MOVE_ANGLE_THLESHOLD && ySpeed > -MAX_SPEED)
    {
        ySpeed -= SPEED;
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
    if (difInAngle > ROLL_THLESHOLD)
    {
        Rotate(VGet(0, 0, -rotateSpeed * smooth(difInAngle, 0, 2)));


    }
    else if (difInAngle < -ROLL_THLESHOLD)
    {
        Rotate(VGet(0, 0, rotateSpeed * smooth(difInAngle, 0, 2)));

    }
}
void Enemy::barrelRoll()
{
    EvadePosDistance = 0;
    int x = MAX_MOVE_RANGE > moveRangeX ? moveRangeX : MAX_MOVE_RANGE;
    int lowerX = -MAX_MOVE_RANGE < minimumMoveRangeX ? minimumMoveRangeX : -MAX_MOVE_RANGE;
    int y = MAX_MOVE_RANGE > moveRangeY ? moveRangeY : MAX_MOVE_RANGE;
    int lowerY = -MAX_MOVE_RANGE < minimumMoveRangeY ? minimumMoveRangeY : -MAX_MOVE_RANGE;
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
    int x = MAX_MOVE_RANGE > moveRangeX ? moveRangeX : MAX_MOVE_RANGE;
    int lowerX = -MAX_MOVE_RANGE < minimumMoveRangeX ? minimumMoveRangeX : -MAX_MOVE_RANGE;
    switch (evadeCount) {
    case 1:

        EvadeMove(x, FLUC_RANGE, 2);
        break;
    case 2:

        EvadeMove(lowerX, -FLUC_RANGE, 3);
        break;
    case 3:
        EvadeMove(x, -FLUC_RANGE, 0);
        break;
    default:
        EvadeMove(lowerX, FLUC_RANGE, 1);
        break;
    }
}
void Enemy::V_Fluctuating()
{
    EvadePosDistance = 0;
    int y = MAX_MOVE_RANGE > moveRangeY ? moveRangeY : MAX_MOVE_RANGE;
    int lowerY = -MAX_MOVE_RANGE < minimumMoveRangeY ? minimumMoveRangeY : -MAX_MOVE_RANGE;
    switch (evadeCount) {
    case 1:
        EvadeMove(FLUC_RANGE, y, 2);
        break;
    case 2:
        EvadeMove(-FLUC_RANGE, lowerY, 3);
        break;
    case 3:
        EvadeMove(-FLUC_RANGE, y, 0);
        break;
    default:
        EvadeMove(FLUC_RANGE, lowerY, 1);
        break;
    }
}
void Enemy::EvadeMove(int x,int y,int count)
{
    targetAngle = VGet(x - offset.x, y - offset.y, 0);
    EvadePosDistance = sqrtf((targetAngle.x * targetAngle.x) + (targetAngle.y * targetAngle.y));
    targetAngle = VNorm(targetAngle);
    if (EvadePosDistance < EVADE_TARGET_DISTANCE)
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
    if (playerObject->Transition() && transitionMoveZaxis >= TRANSITION_TARGET_POSZ)
    {
        offset = VGet(playerObject->offset.x + TRANSITION_OFFSET_X, playerObject->offset.y - TRANSITION_OFFSET_Y, 0);
        return true;
    }
    else if (transitionMoveZaxis >= TRANSITION_TARGET_POSZ)
    {
        Move(VAdd(VGet(playerObject->offset.x + TRANSITION_OFFSET_X, playerObject->offset.y - TRANSITION_OFFSET_Y, 0), BasePosition));
        return false;
    }
    else
    {
        BasePosition = VAdd(playerObject->BasePosition, VGet(0, 0, transitionMoveZaxis));
        transitionMoveZaxis += TRANSITION_MOVE_SPEED;
        Move(VAdd(VGet(playerObject->offset.x + TRANSITION_OFFSET_X, playerObject->offset.y - TRANSITION_OFFSET_Y, 0), BasePosition));
        return false;
    }
}