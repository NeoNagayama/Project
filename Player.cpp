#include "Player.h"
void Player::mainProcess(bool mode)
{
    /*KeyInput();
    PlayerMoveXY();
    Move(VAdd(BasePosition, offset));*/
    if (mode)
    {
        Vulcan();
    }
    else
    {
        Flare();
    }
    
}
void Player::KeyInput()
{
    float speed = 0.1f;
    if (Input_GetKeyboardDown(KEY_INPUT_W))
    {
        if (Input_GetKeyboardDown(KEY_INPUT_A))
        {
            x -=speed;
        }
        else if (Input_GetKeyboardDown(KEY_INPUT_D))
        {
            x += speed;
        }
            y += speed;
    }
    else if (Input_GetKeyboardDown(KEY_INPUT_S))
    {
        if (Input_GetKeyboardDown(KEY_INPUT_A))
        {
            x += speed;
        }
        else if (Input_GetKeyboardDown(KEY_INPUT_D))
        {
            x -= speed;
        }
        y -= speed;
    }
    else
    {
        x += (x > 0) ? -speed : 0;
        x += (x < 0) ? speed : 0;
        y+=(y > 0) ? -speed : 0;
        y+=(y < 0) ? speed : 0;
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
    if (offset.x > 400 || offset.x < 400)
    {
        offset.x = (offset.x > 400) ? 400 : -400;
    }
    if (offset.y > 400 || offset.y < 400)
    {
        offset.y = (offset.y > 400) ? 400.0f : -400.0f;
    }
    if (offset.z > 400 || offset.z < 400)
    {
        offset.z = (offset.z > 400) ? 400 : -400;
    }
}
void Player::Vulcan()
{
    clsDx();
    if (CheckHitKey(KEY_INPUT_SPACE) && firingTimer > firingRate &&ammo>0)
    {
        firingTimer = 0;
        ammo--;
        DrawBox(200, 200, 900, 900, GetColor(50, 55, 55), true);
    }
    firingTimer += 0.016f;
    printfDx("%d", ammo);
}
void Player::Flare()
{
    clsDx();
    if (CheckHitKey(KEY_INPUT_SPACE) && FlareCoolDown > FlareInterval && !Launching)
    {
        FlareCoolDown = 0;
        Launching = true;
        FlareAmount = 10;
    }
    if (Launching)
    {
        FlareFiringTimer += 0.016f;
        if (FlareFiringTimer > FlareFiringRate)
        {
            DrawBox(200, 200, 900, 900, GetColor(200, 160, 0), true);
            FlareFiringTimer = 0;
            FlareAmount--;
        }
        if (FlareAmount <= 0)
        {
            Launching = false;
        }
    }
    FlareCoolDown += 0.016f;
    printfDx("%d", FlareCoolDown);
}