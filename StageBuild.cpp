#include "StageBuild.h"
void builder::main()
{
    SetBackgroundColor(80, 80, 80, 255);
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
    if (CheckHitKey(KEY_INPUT_O))
    {
        save();
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
    FILE* fileobtype;
    FILE* fileobs;
    FILE* filewall;
    errno_t err = fopen_s(&fileobtype, "maps/defaultMaps/stage2type.dat", "wb");
    err = fopen_s(&fileobs, "maps/defaultMaps/stage2obs.dat", "wb");
    err = fopen_s(&filewall, "maps/defaultMaps/stage2wall.dat", "wb");
    int obtype[50];
    int obs[50];
    int wal[50];
    for (int i = 0; i < 50; i++)
    {
        obtype[i] = obstacleType[i];
        obs[i] = obstacle[i];
        wal[i] = moveWallType[i];
    }
    fwrite(obtype, sizeof(int), 50, fileobtype);
    fwrite(obs, sizeof(int), 50, fileobs);
    fwrite(wal, sizeof(int), 50, filewall);
    fclose(fileobtype);
    fclose(fileobs);
    fclose(filewall);
}