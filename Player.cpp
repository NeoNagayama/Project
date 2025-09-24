#include "Player.h"
void Player::mainProcess()
{
    KeyInput();
    PlayerMoveXY();

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
    xSpeed = x * moveSpeed;
    ySpeed = y * moveSpeed;
    /*if (Rotation.y == DegToRad(90))
    {
        offset=VAdd(VGet)
    }*/
}