#include "Player.h"
#include "base.h"
#include<cmath>
int test;
void Player::InitialProcess()
{
    ModelHandle = MV1LoadModel("F-14Test.mv1");
    MV1SetPosition(ModelHandle, VGet(0, -5, -0));
    MV1SetScale(ModelHandle, VGet(3, 3, 3));
    Position = VGet(0, -5, -0);
    PlayerLightHandle = CreateDirLightHandle(VGet(0.5f,1,0));
    SetLightEnableHandle(PlayerLightHandle, true);
    SetLightDifColorHandle(PlayerLightHandle, GetColorF(0.9, 0.9, 1, 1));
}
void Player::mainProcess(bool mode)
{
    SetHitBox(4, 4);

    
    BasePosition = VAdd(VGet(0, 0, 1),BasePosition);
    KeyInput();
    PlayerMoveXY();
    Move(VAdd(BasePosition, offset));
    rotatePlayer();
    pitch();
    if (mode)
    {
        SetCameraPositionAndTarget_UpVecY(VAdd(VGet(offset.x/2, offset.y/2, -20), BasePosition),  BasePosition);
        Vulcan();
    }
    else
    {
        SetCameraPositionAndTarget_UpVecY(VAdd(VGet(0, 0, -25), BasePosition), BasePosition);
        CameraPosition = VAdd(VGet(0, 0, -25), BasePosition);
        Flare();
    }
    
}
void Player::KeyInput()
{
    float speed = 0.1f;
    if (CheckHitKey(KEY_INPUT_W)&&y <0.7f)
    {
        if (CheckHitKey(KEY_INPUT_D)&& x <0.7f)
        {
            x += speed;
            targetAngle = VGet(0.5f, -0.5f, 0);
            //targetAnglePitch = VGet(1, -1, 1);
        }
        else if (CheckHitKey(KEY_INPUT_A)&& x > -0.7f)
        {
            x -= speed;
            targetAngle = VGet(-0.5f, -0.5f, 0);
            //targetAnglePitch = VGet(-1, -1, 0);
        }
        else
        {
            targetAngle = VGet(0, -1, 0);
            //targetAnglePitch = VGet(0, -1, 1);
        }
            y += speed;
    }
    else if (CheckHitKey(KEY_INPUT_S)&&y>-0.7f)
    {
        if (CheckHitKey(KEY_INPUT_D) && x < 0.7f)
        {
            x += speed;
            targetAngle = VGet(0.5f, 0.5f, 0);
            //targetAnglePitch = VGet(1, -1, 1);
        }
        else if (CheckHitKey(KEY_INPUT_A) && x > -0.7f)
        {
            x -= speed;
            targetAngle = VGet(-0.5f, 0.5f, 0);
            //targetAnglePitch = VGet(-1, -1, 1);
        }
        else
        {
            targetAngle = VGet(0, 0.99f, 0);
            //targetAnglePitch = VGet(0, 0.99f, 1);
        }
        y -= speed;
    }
    else if (CheckHitKey(KEY_INPUT_D) && x < 0.7f)
    {
        x += speed;
        targetAngle = VGet(0.6f, -0.4f, 0);
        //targetAnglePitch = VGet(1, -0.4f, 1);

       
    }
    else if (CheckHitKey(KEY_INPUT_A) && x > -0.7f)
    {
        x -= speed;
        targetAngle = VGet(-0.6f, -0.4f, 0);
        //targetAnglePitch = VGet(-1, -0.4f, 1);
    }
    else
    {
        if (!CheckHitKey(KEY_INPUT_A) && !CheckHitKey(KEY_INPUT_S) && !CheckHitKey(KEY_INPUT_D) && !CheckHitKey(KEY_INPUT_W))
        {
            targetAngle = VGet(0, -0.99, 0);
            //targetAnglePitch = VGet(0, 0, 1);
            /*if (rotateSpeed > 0)
            {
                rotateSpeed -= 0.005f;
            }
            else
            {
                rotateSpeed = 0;
            }*/
        }
        /*else
        {
            
        }*/
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
    DrawExtendGraph(ConvWorldPosToScreenPos(VAdd(VGet(bulletPositionX[20],bulletPositionY[20],BasePosition.z), VGet(0, 0, 50))).x - 120, ConvWorldPosToScreenPos(VAdd(VGet(bulletPositionX[20], bulletPositionY[20], BasePosition.z), VGet(0, 0, 50))).y - 120, ConvWorldPosToScreenPos(VAdd(VGet(bulletPositionX[20], bulletPositionY[20], BasePosition.z), VGet(0, 0, 50))).x + 120, ConvWorldPosToScreenPos(VAdd(VGet(bulletPositionX[20], bulletPositionY[20], BasePosition.z), VGet(0, 0, 50))).y + 120, reticleHandle, true);
    if (CheckHitKey(KEY_INPUT_SPACE) && firingTimer > firingRate &&ammo>0)
    {
        firingTimer = 0;
        ammo--;
        for (int i = 0; i < 200; i++)
        {
            if (!bullets[i].isActivated)
            {
                
                bullets[i].isActivated = true;
                bullets[i].target = VAdd(Position, VGet(0,0,90));
                bullets[i].forward = VGet(0,0,4);
                bullets[i].StartPosition = VAdd(Position,VGet(forward().x,-forward().y,forward().z ));
                break;
            }
        }
    }
    firingTimer += 0.016f;
    for (int i = 0; i < 200; i++)
    {
        if (bullets[i].isActivated)
        {
            if (bullets[i].mainProcess(enemyObject->hitbox1, enemyObject->hitbox2))
            {
                enemyObject->Health -= 3;
            }
        }
    }
   
}
void Player::Flare()
{
    if (CheckHitKey(KEY_INPUT_SPACE) && FlareCoolDown > FlareInterval && !Launching)
    {
        FlareCoolDown = 0;
        Launching = true;
        FlareAmount = 10;
        enemyObject->isGuideLost = true;
    }
    if (Launching)
    {
        FlareFiringTimer += 0.016f;
        if (FlareFiringTimer > FlareFiringRate)
        {
            for (int i = 0; i < 10; i++)
            {
                if (!Flares[i].isActivated)
                {
                    Flares[i].isActivated = true;
                    Flares[i].forward = VScale(VGet(upper().x, -upper().y * 0.2f, 2.7f),0.3f);
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
    for (int i = 0; i < 10; i++)
    {
        if (Flares[i].isActivated)
        {
            Flares[i].mainProcess();
        }
    }
    FlareCoolDown += 0.016f;
    
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
        else if(!CheckHitKey(KEY_INPUT_A) && !CheckHitKey(KEY_INPUT_S) && !CheckHitKey(KEY_INPUT_D) && !CheckHitKey(KEY_INPUT_W))
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
    rotatePlayer();
    BasePosition = VAdd(VGet(0, 0, 1), BasePosition);
    VECTOR targetCameraPosition = VAdd(VGet(offset.x / 2, offset.y / 2, -20), BasePosition);
    CameraPosition = VAdd(VAdd(CameraPosition,VScale(VNorm(VGet(targetCameraPosition.x - CameraPosition.x, targetCameraPosition.y - CameraPosition.y, targetCameraPosition.z - CameraPosition.z)),0.4f)),VGet(0, 0, 1.0f));
    VECTOR cameraToTargetVector = VGet(targetCameraPosition.x - CameraPosition.x, targetCameraPosition.y - CameraPosition.y, targetCameraPosition.z - CameraPosition.z);
    float distance = sqrtf((cameraToTargetVector.x * cameraToTargetVector.x) + (cameraToTargetVector.y * cameraToTargetVector.y) + (cameraToTargetVector.z * cameraToTargetVector.z));
    SetCameraPositionAndTarget_UpVecY(CameraPosition, BasePosition);
    Move(VAdd(BasePosition, offset));
    if (distance <=1.0f)
    {
        return true;
    }
    return false;
}