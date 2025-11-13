#include "StageBuild.h"
void builder::main()
{
    SetBackgroundColor(80, 80, 80, 255);
    clsDx();
    printfDx("%d", pos * 80);
    if (Input_GetKeyboardDown(KEY_INPUT_W))
    {
        if (pos < 49)
        {
            pos += 1;
        }
    }
    if(Input_GetKeyboardDown(KEY_INPUT_S))
    {
        if (pos > 0)
        {
            pos -= 1;
        }
    }
    if (Input_GetKeyboardDown(KEY_INPUT_E))
    {
        obstacleType[pos] = 3;
    }
    if (Input_GetKeyboardDown(KEY_INPUT_Q))
    {
        obstacleType[pos] = 1;
    }
    if (Input_GetKeyboardDown(KEY_INPUT_R))
    {
        obstacle[pos]++;
    }
    if (Input_GetKeyboardDown(KEY_INPUT_F))
    {
        obstacle[pos]--;
    }
    if (Input_GetKeyboardDown(KEY_INPUT_T))
    {
        moveWallType[pos]++;
    }
    if (Input_GetKeyboardDown(KEY_INPUT_G))
    {
        moveWallType[pos]--;
    }
    if (CheckHitKey(KEY_INPUT_UP))
    {
        cam.y += camSpeed;
    }
    if (CheckHitKey(KEY_INPUT_DOWN))
    {
        cam.y -= camSpeed;
    }
    if (CheckHitKey(KEY_INPUT_RIGHT))
    {
        cam.x += camSpeed;
    }
    if (CheckHitKey(KEY_INPUT_LEFT))
    {
        cam.x -= camSpeed;
    }
    if (CheckHitKey(KEY_INPUT_LSHIFT))
    {
        cam.z += camSpeed;
    }
    if (CheckHitKey(KEY_INPUT_LCONTROL))
    {
        cam.z -= camSpeed;
    }
    for (int i = 0; i <= pos; i++)
    {
        maps[i].position.z = 80*i;
        AAs[i].position.z = 80*i;
        moveWalls[i].position.z = 80*i;
        maps[i].DrawbaseOutline();
        if (obstacleType[i] < 2)
        {
            Obstacles(i, i);
        }
        else
        {
            AAGuns(i, i);
        }
        MoveWalls(i, i);
    }
    SetCameraPositionAndTarget_UpVecY(VGet(cam.x,cam.y, (pos*80) +cam.z), VGet(0, 0, pos * 80));
    SetupCamera_Perspective(1.2f);
}
void builder::Init()
{
    for (int i = 0; i < 50; i++)
    {
        moveWalls[i].SetUp();
        maps[i].BaseSetUp();
    }
}
void builder::save()
{
    FILE* fp;
    fp = fopen("stage3.dat", "wb");
}