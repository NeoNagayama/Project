#include "TitleScene.h"
#include "DxLib.h"
#include "Input.h"
#include "Button.h"
#include "fontLoader.h"
#include "main.h"
#include "ui.h"
#include "stage1Scene.h"

bool isStartSelected = true;
bool sceneChanging = false;
float yaxis = 0;
float z = 40;
float x = 25;
Button Start;
Button Exit;
int modelhandle,modelHandle2,modelHandle3;
void TitleInitialProcess()
{
    Start.SetButtonPosition(VGet(1550,545,1),600,100,0.9f);
    Exit.SetButtonPosition(VGet(1550, 745, 1), 600, 100, 0.9f);
    modelhandle = MV1LoadModel("F-14Test.mv1");
    MV1SetPosition(modelhandle,VGet(-2, 0, -19));
    MV1SetRotationXYZ(modelhandle, VGet(0, 2.53f, 0));
    modelHandle2 = MV1LoadModel("F-14Test.mv1");
    modelHandle3 = MV1LoadModel("F-14Test.mv1");
}
void TitleMainProcess()
{
    SetCameraPositionAndTarget_UpVecY(VGet(-1, 0, -20), VGet(2, 6.7f, -12));
    if (Input_GetKeyboardDown(KEY_INPUT_S)  && isStartSelected == true && !sceneChanging)
    {
        isStartSelected = false;
    }
    if (Input_GetKeyboardDown(KEY_INPUT_W) && isStartSelected == false && !sceneChanging)
    {
        isStartSelected = true;
    }
    if (CheckHitKey(KEY_INPUT_D))
    {
        yaxis += 0.01f;
    }
    if(CheckHitKey(KEY_INPUT_A))
    {
        yaxis -= 0.01f;
    }
    z -= 0.2f;
    x -= 0.09f;
    clsDx();
    printfDx("%f", yaxis);
    MV1SetPosition(modelHandle2, VGet(x, 7, z));
    MV1SetPosition(modelHandle3, VGet(x -3, 7, z-2));
    MV1SetRotationXYZ(modelHandle2, VGet(0, -2.70f, 0.4f));
    MV1SetRotationXYZ(modelHandle3, VGet(0, -2.70f, 0.4f));
    MV1DrawModel(modelHandle2);
    MV1DrawModel(modelHandle3);
    MV1SetPosition(modelhandle, VGet(-1, 0.19f, -18.3f));
    MV1DrawModel(modelhandle);
    if (z < -60 && x < -60)
    {
        z = get_rand(35, 40);
        x = z - 15;
    }
    Start.mainProcess(isStartSelected,true,30);
    Start.SetText("Start");
    Exit.mainProcess(!isStartSelected,true,30);
    Exit.SetText("Exit");
    textPositionSet(1000, 1920, "CANYON RUN", titleFontHandle, SORT_CENTER, 200, false, GetColor(255,255,255));
    if (isStartSelected && Input_GetKeyboardDown(KEY_INPUT_SPACE))
    {
        sceneChanging = true;
    }
    else if (!isStartSelected && Input_GetKeyboardDown(KEY_INPUT_SPACE))
    {
        Quit = true;
    }
    if (sceneChanging)
    {
        if (fadeout(0.5f))
        {
            Stage1Initialize();
            progress = 255;
            isStarted = true;
            scene = SCENE_STAGE1;
        }
    }
}
void Titleinitialize()
{
    isStartSelected = true;
    sceneChanging = false;
}
