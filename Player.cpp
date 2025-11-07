#include "Player.h"
#include "base.h"
#include<cmath>
int test;
void Player::InitialProcess()
{
    ModelHandle = MV1LoadModel("PlayerModel.mv1");
    MV1SetPosition(ModelHandle, VGet(0, -5, -0));
    MV1SetScale(ModelHandle, VGet(6, 6, 6));
    Position = VGet(0, -5, -0); 
    for (int i = 0; i < MV1GetMaterialNum(ModelHandle); i++)
    {
        MV1SetMaterialDifColor(ModelHandle, i, GetColorF(0.7f, 0.7f, 0.7f, 1.0f));
        MV1SetMaterialAmbColor(ModelHandle, i, GetColorF(0.2f, 0.2f, 0.2f, 1.0f));
        MV1SetMaterialSpcColor(ModelHandle, i, GetColorF(0.4f, 0.4f, 0.4f, 1));
        MV1SetMaterialEmiColor(ModelHandle, i, GetColorF(0.8f, 0.8f, 0.8f, 0.2f));
        MV1SetMaterialSpcPower(ModelHandle, i, 6);
    }
}
void Player::mainProcess(bool mode)
{
    SetHitBox(2, 2);

    
    BasePosition = VAdd(VGet(0, 0, 2*timeScale),BasePosition);
    if (Health > 0)
    {
        KeyInput();
        PlayerMoveXY();
        Move(VAdd(BasePosition, offset));
        rotatePlayer();
        pitch();
        if (mode)
        {
            SetCameraPositionAndTarget_UpVecY(VAdd(VGet(offset.x, offset.y + 2, -16), BasePosition), VAdd(VGet(offset.x, offset.y, 20), BasePosition));
            Vulcan();
        }
        else
        {
            SetCameraPositionAndTarget_UpVecY(VAdd(VGet(offset.x, offset.y + 2, -30), BasePosition), VAdd(VGet(offset.x, offset.y, 20), BasePosition));
            CameraPosition = VAdd(VGet(offset.x, offset.y + 2, -20), BasePosition), VAdd(VGet(offset.x, offset.y, 20), BasePosition);
            Flare();

        }
    }
    if (!isDead && Health <= 0)
    {
        exp.SetPosition(Position);
        isDead = true;
    }
    exp.DrawExprosion();
}
void Player::transitionProcess(bool mode)
{
    BasePosition = VAdd(VGet(0, 0, 2* timeScale), BasePosition);
    Move(VAdd(BasePosition, offset));
    targetAngle = VGet(0, -0.99f, 0);
    rotatePlayer();
    targetAnglePitch = VGet(0, 0, 1);
    pitch();
    if (mode)
    {
        SetCameraPositionAndTarget_UpVecY(VAdd(VGet(offset.x, offset.y + 2, -16), BasePosition), VAdd(VGet(offset.x, offset.y, 20), BasePosition));
    }
    else
    {
        SetCameraPositionAndTarget_UpVecY(VAdd(VGet(offset.x, offset.y + 2, -20), BasePosition), VAdd(VGet(offset.x, offset.y, 20), BasePosition));
    }
    
    CameraPosition = VAdd(VGet(offset.x, offset.y + 2, -20), BasePosition), VAdd(VGet(offset.x, offset.y, 20), BasePosition);
}
void Player::clearProcess()
{
    autoEvade();
    rotateOnlyRoll();
    targetAnglePitch = VGet(0, 0, 1);
    pitch();
    BasePosition = VAdd(VGet(0, 0, 2 * timeScale), BasePosition);
    Move(VAdd(BasePosition, offset));
    targetAngle = VGet(0, -0.99f, 0);
}
void Player::KeyInput()
{
    float speed = 0.1f;
    if (CheckHitKey(KEY_INPUT_W))
    {
        InputUp(speed);
    }
    else if (CheckHitKey(KEY_INPUT_S))
    {
        InputDown(speed);
    }
    else if (CheckHitKey(KEY_INPUT_D) && x < 0.7f)
    {
        x += speed;
        speedLimit = 0.7f;
        targetAngle = VGet(0.6f, -0.4f, 0);

       
    }
    else if (CheckHitKey(KEY_INPUT_A) && x > -0.7f)
    {
        x -= speed;
        speedLimit = 0.7f;
        targetAngle = VGet(-0.6f, -0.4f, 0);
    }
    else
    {
        InputNeutral(speed);
    }
    Limit();
}
void Player::InputUp(float speed)
{
    if (CheckHitKey(KEY_INPUT_D))
    {
        x += speed;
        speedLimit = 0.49f;
        targetAngle = VGet(0.5f, -0.5f, 0);
    }
    else if (CheckHitKey(KEY_INPUT_A))
    {
        x -= speed;
        speedLimit = 0.49f;
        targetAngle = VGet(-0.5f, -0.5f, 0);
    }
    else
    {
        speedLimit = 0.7f;
        targetAngle = VGet(0, -1, 0);
    }
    y += speed;
}
void Player::InputDown(float speed)
{
    if (CheckHitKey(KEY_INPUT_D))
    {
        x += speed;
        speedLimit = 0.49f;
        targetAngle = VGet(0.5f, 0.5f, 0);
    }
    else if (CheckHitKey(KEY_INPUT_A))
    {
        x -= speed;
        speedLimit = 0.49f;
        targetAngle = VGet(-0.5f, 0.5f, 0);
    }
    else
    {
        speedLimit = 0.7f;
        targetAngle = VGet(0, 0.99f, 0);
    }
    y -= speed;
}
void Player::InputNeutral(float speed)
{

    if (!CheckHitKey(KEY_INPUT_A) && !CheckHitKey(KEY_INPUT_S) && !CheckHitKey(KEY_INPUT_D) && !CheckHitKey(KEY_INPUT_W))
    {
        targetAngle = VGet(0, -0.99f, 0);
    }
    if (x > 0.1f)
    {
        x -= speed;
    }
    else if (x < -0.1f)
    {
        x += speed;
    }
    else
    {
        x = 0;
    }
    if (y > 0.1f)
    {
        y -= speed;
    }
    else if (y < -0.1f)
    {
        y += speed;
    }
    else
    {
        y = 0;
    }
}
void Player::Limit()
{
    if (x >= speedLimit)
    {
        x = speedLimit;
    }
    else if (x <= -speedLimit)
    {
        x = -speedLimit;
    }
    if (y >= speedLimit)
    {
        y = speedLimit;
    }
    else if (y <= -speedLimit)
    {
        y = -speedLimit;
    }
}
void Player::PlayerMoveXY()
{
    float xSpeed, ySpeed;
    xSpeed = (offset.x > moveRange || offset.x < -moveRange) ? 0 : x * moveSpeed;
    ySpeed = (offset.y > moveRange|| offset.y < -moveRange) ? 0:y * moveSpeed;
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
        offset.x = (offset.x > moveRange) ? moveRange : -moveRange;
    }
    if (offset.y > moveRange || offset.y < -moveRange)
    {
        offset.y = (offset.y > moveRange) ? moveRange : -moveRange;
    }
    if (offset.z > moveRange || offset.z < -moveRange)
    {
        offset.z = (offset.z > moveRange) ? moveRange : -moveRange;
    }
}
void Player::Vulcan()
{
    VulcanText.DrawTextWithSort(120, 1920, "VULCAN: %d", fontHandle, SORT_LEFT, 600, true, GetColor(0, 255, 0), GetColor(50, 50, 50), ammo);
    Position = MV1GetPosition(ModelHandle);
    for (int i = 49; i >= 0; i--)
    {
        if (i == 0)
        {
            bulletPositionX[i] = Position.x;
            bulletPositionY[i] = Position.y;
        }
        else
        {
            bulletPositionX[i] = bulletPositionX[i - 1];
            bulletPositionY[i] = bulletPositionY[i - 1];
        }
    }
    VECTOR ReticleCenter = ConvWorldPosToScreenPos(VAdd(VGet(bulletPositionX[10], bulletPositionY[10], BasePosition.z), VGet(0, 0, 50)));
    DrawExtendGraph((int)ReticleCenter.x- 70, (int)ReticleCenter.y + 70, (int)ReticleCenter.x + 70, (int)ReticleCenter.y - 70, reticleHandle, true);

    clsDx();
    printfDx("%d", (ammo / maxAmmo) * 100);
    DrawCircleGauge((int)ReticleCenter.x, (int)ReticleCenter.y, (double)((float)ammo / (float)maxAmmo) * 100, reticleInsideGaugeHandle, 0,0.1);
    VulcanProjectile();
   
}
void Player::VulcanProjectile()
{
    if (CheckHitKey(KEY_INPUT_SPACE) && firingTimer > firingRate && ammo > 0)
    {
        firingTimer = 0;
        ammo--;
        for (int i = 0; i < 200; i++)
        {
            if (!bullets[i].isActivated)
            {

                bullets[i].isActivated = true;
                bullets[i].target = VAdd(Position, VGet(0, 0, 90));
                bullets[i].forward = VGet(0, 0, 6);
                bullets[i].StartPosition = VAdd(Position, VGet(forward().x, -forward().y, forward().z));
                break;
            }
        }
    }
    firingTimer += oneFlame;
    for (int i = 0; i < 200; i++)
    {
        if (bullets[i].isActivated)
        {
            if (bullets[i].mainProcess(enemyObject->hitbox1, enemyObject->hitbox2,bulletHandle))
            {
                enemyObject->Health -= 3;
            }
        }
    }
}
void Player::Flare()
{
    for (int i = 0; i < 10; i++)
    {
        Flares[i].Passive();
    }
    if (CheckHitKey(KEY_INPUT_SPACE) && FlareCoolDown > FlareInterval && !Launching)
    {
        FlareCoolDown = 0;
        Launching = true;
        FlareAmount = 10;
        enemyObject->isGuideLost = true;
    }
    if (FlareCoolDown > FlareInterval)
    {
        FlareText.DrawTextWithSort(120, 1920, "FLARE:READY", fontHandle, SORT_LEFT, 600, true, GetColor(0, 255, 0), GetColor(50, 50, 50));
    }
    else
    {
        FlareText.DrawTextWithSort(120, 1920, "FLARE: %d", fontHandle, SORT_LEFT, 600, true, GetColor(0, 255, 0), GetColor(50, 50, 50),  5-FlareCoolDown);
    }
    if (Launching)
    {
        FlareLaunch();
    }
    for (int i = 0; i < 10; i++)
    {
        if (Flares[i].isActivated)
        {
            Flares[i].mainProcess();
        }
    }
    FlareCoolDown += 0.016f;
    
}
void Player::FlareLaunch()
{
    FlareFiringTimer += 0.016f;
    if (FlareFiringTimer > FlareFiringRate)
    {
        for (int i = 0; i < 10; i++)
        {
            if (!Flares[i].isActivated)
            {
                Flares[i].isActivated = true;
                Flares[i].forward = VScale(VGet(upper().x, -upper().y * 0.2f, 5.7f), 0.3f);
                Flares[i].position = Position;
                break;
            }
        }
        FlareFiringTimer = 0;
        FlareAmount--;
    }
    if (FlareAmount <= 0)
    {
        Launching = false;
    }
}
void Player::rotatePlayer()
{
    float x, y;
    x = cos(atan2(upper().y - 0, upper().x - 0));
    y = sin(atan2(upper().y - 0, upper().x - 0));
    float difInAngle = ((targetAngle.x * y) - (targetAngle.y * x));
    if (difInAngle > 0.05f)
    {
        Rotate(VGet(0, 0, -rotateSpeed * smooth(difInAngle, 0, 2)));
    }
    else if (difInAngle < -0.05f)
    {
        Rotate(VGet(0, 0, rotateSpeed * smooth(difInAngle, 0, 2)));
        
    }
    if (CheckHitKey(KEY_INPUT_A) || CheckHitKey(KEY_INPUT_S) || CheckHitKey(KEY_INPUT_D) || CheckHitKey(KEY_INPUT_W))
    {
        if (difInAngle < -0.5f || difInAngle > 0.5f)
        {
            targetAnglePitch = VGet(0, 0.3f* ((1-abs(difInAngle))/0.5f), 0.7f );
        }
        else
        {
            if (!CheckHitKey(KEY_INPUT_A) && CheckHitKey(KEY_INPUT_S) && !CheckHitKey(KEY_INPUT_D) && !CheckHitKey(KEY_INPUT_W))
            {
                targetAnglePitch = VGet(0, 0.3f, 0.7f);
            }
            else
            {
                targetAnglePitch = VGet(0, -0.3f*((0.5f-abs(difInAngle))/0.5f), 0.7f);
            }
        }
    }
    else
    {
        targetAnglePitch = VGet(0, 0, 1);
    }

    
}
void Player::rotateOnlyRoll()
{
    float x, y;
    x = cos(atan2(upper().y - 0, upper().x - 0));
    y = sin(atan2(upper().y - 0, upper().x - 0));
    float difInAngle = ((targetAngle.x * y) - (targetAngle.y * x));
    if (difInAngle > 0.05f)
    {
        Rotate(VGet(0, 0, -rotateSpeed * smooth(difInAngle, 0, 2)));
    }
    else if (difInAngle < -0.05f)
    {
        Rotate(VGet(0, 0, rotateSpeed * smooth(difInAngle, 0, 2)));

    }
}

void Player::pitch()
{
    float z, y;
    z = cos(atan2(forward().y - 0, forward().z - 0));
    y = sin(atan2(forward().y - 0, forward().z - 0));
    float difInAngle = (((targetAnglePitch.z*0.4f) * y) - ((targetAnglePitch.y * 0.4f) * z));
    if (Rotation.x <= 0.4f && Rotation.x >= -0.4f)
    {
        if (difInAngle > 0.005f && difInAngle < 0.5f)
        {
            Rotate(VGet(-rotateSpeed * smooth(difInAngle, 0, 1), 0, 0));
        }
        else if (difInAngle < -0.005f && difInAngle > -0.5f)
        {
            Rotate(VGet(rotateSpeed * smooth(difInAngle, 0, 1), 0, 0));
        }
        else if (difInAngle < -0.5f)
        {
            Rotate(VGet(-rotateSpeed * smooth(difInAngle, 0, 1), 0, 0));
        }
        else if (difInAngle > 0.5f)
        {
            Rotate(VGet(rotateSpeed * smooth(difInAngle, 0, 1), 0, 0));
        }
        else if(!CheckHitKey(KEY_INPUT_A) && !CheckHitKey(KEY_INPUT_S) && !CheckHitKey(KEY_INPUT_D) && !CheckHitKey(KEY_INPUT_W) )
        {
            Rotation = MV1GetRotationXYZ(ModelHandle);
            SetRotation(VGet(0, Rotation.y, Rotation.z));
        }
    }
    else if(Rotation.x > 0.4f)
    {
        Rotation = MV1GetRotationXYZ(ModelHandle);
        SetRotation(VGet(0.4f, Rotation.y, Rotation.z));
    }
    else
    {
        Rotation = MV1GetRotationXYZ(ModelHandle);
        SetRotation(VGet(-0.4f, Rotation.y, Rotation.z));
    }
        
}
bool Player::Transition()
{
    autoEvade();
    VECTOR targetCameraPosition = VAdd(VGet(offset.x , offset.y + 2 , -16), BasePosition);
    VECTOR cameraToTargetVector = VGet(targetCameraPosition.x - CameraPosition.x, targetCameraPosition.y - CameraPosition.y, targetCameraPosition.z - CameraPosition.z);
    float distance = sqrtf((cameraToTargetVector.x * cameraToTargetVector.x) + (cameraToTargetVector.y * cameraToTargetVector.y) + (cameraToTargetVector.z * cameraToTargetVector.z));
    BasePosition = VAdd(VGet(0, 0, 2), BasePosition);
    pitch();
    Move(VAdd(BasePosition, offset));
    if (distance <1.5f)
    {
        rotatePlayer();
        CameraPosition = VAdd(VGet(offset.x, offset.y + 2, -16), BasePosition);
        SetCameraPositionAndTarget_UpVecY(VAdd(VGet(offset.x, offset.y + 2, -16), BasePosition), VAdd(VGet(offset.x, offset.y, TARGET_CAMERA_POSZ), BasePosition));
        return true;
    }
    else
    {
        CameraPosition = VAdd(VAdd(CameraPosition, VScale(VNorm(VGet(targetCameraPosition.x - CameraPosition.x, targetCameraPosition.y - CameraPosition.y, targetCameraPosition.z - CameraPosition.z)), 0.17f)), VGet(0, 0, 2.0f));
        SetCameraPositionAndTarget_UpVecY(VGet(offset.x, offset.y + 2, CameraPosition.z), VAdd(VGet(offset.x, offset.y, TARGET_CAMERA_POSZ), BasePosition));
        return false;
    }
}
void Player::autoEvade()
{
    float distance = sqrtf((-offset.x * -offset.x) + (-offset.y * -offset.y));
    if (distance >= 1)
    {
        targetAngle = VNorm(VGet(-offset.x, -offset.y, 0));
        offset = VAdd(VScale(targetAngle, moveSpeed * timeScale), offset);
        targetAngle.y = -targetAngle.y;
        rotatePlayer();
    }
    else
    {
        targetAngle = VGet(0, -NEUTRAL_ANGLE_Y, 0);
        rotatePlayer();
    }
}