#include "TitleScene.h"
#include "DxLib.h"
#include "Input.h"
#include "Button.h"
#include "Text.h"
#include "main.h"
#include "ui.h"

bool isStartSelected = true;
bool sceneChanging = false;
float yaxis = 0;
float z = 80;
float x = -100;
Button Start;
Button Exit;
UIText GameTitle;
int modelhandle,modelHandle2,modelHandle3;
stage* stage1Instance;
stage* stage2Instance;
stage* stage3Instance;
void getStagePointers(stage* s1, stage* s2, stage* s3) {
    stage1Instance = s1;
    stage2Instance = s2;
    stage3Instance = s3;
}

void TitleInitialProcess()
{
    Start.SetButtonPosition(VGet(1550,545,1),600,100,0.9f);
    Exit.SetButtonPosition(VGet(1550, 745, 1), 600, 100, 0.9f);
    modelhandle = MV1LoadModel("F-14Test.mv1");
    MV1SetPosition(modelhandle,VGet(-0.4, 0.04f, -19.2f));
    MV1SetRotationXYZ(modelhandle, VGet(0, 2.53f, 0));
    modelHandle2 = MV1LoadModel("F-14Test.mv1");
    modelHandle3 = MV1LoadModel("F-14Test.mv1");
}
void TitleMainProcess()
{
    DrawShadow();
    SetUseShadowMap(0, titleShadowHandle);
    SetupCamera_Perspective(0.55f);
    SetCameraPositionAndTarget_UpVecY(VGet(0, 0.2f, -22), VGet(0, 1.2f, -12));
    if ((Input_GetKeyboardDown(KEY_INPUT_S) || Input_GetKeyboardDown(KEY_INPUT_DOWN))  && isStartSelected == true && !sceneChanging)
    {
        isStartSelected = false;
    }
    if ((Input_GetKeyboardDown(KEY_INPUT_W) || Input_GetKeyboardDown(KEY_INPUT_UP)) && isStartSelected == false && !sceneChanging)
    {
        isStartSelected = true;
    }
    DrawModels();
    TitleMenu();
}
void Titleinitialize()
{
    isStartSelected = true;
    sceneChanging = false;
}
void DrawShadow()
{
    SetShadowMapDrawArea(titleShadowHandle, VGet(-200.0f, -100.0f, -200.0f), VGet(200.0f, 100.0f, 200.0f));
    ShadowMap_DrawSetup(titleShadowHandle);
    MV1DrawModel(modelHandle2);
    MV1DrawModel(modelHandle3);
    MV1DrawModel(modelhandle);
    ShadowMap_DrawEnd();
}
void DrawModels()
{
    z -= 0.3f;
    x += 0.34f;
    MV1SetPosition(modelHandle2, VGet(x, 4, z));
    MV1SetPosition(modelHandle3, VGet(x - 3, 4, z - 2));
    MV1SetRotationXYZ(modelHandle2, VGet(0, 2.1f, 0));
    MV1SetRotationXYZ(modelHandle3, VGet(0, 2.1f, 0));
    MV1DrawModel(modelHandle2);
    MV1DrawModel(modelHandle3);
    MV1DrawModel(modelhandle);
    DrawCube3D(VGet(-200.0f, -0.01f, -200.0f), VGet(200.0f, -1.1f, 200.0f), GetColor(120, 120, 120), GetColor(0, 0, 0), TRUE);
    if (z < -60)
    {
        z = get_rand(80, 90);
        x = -100;
    }
}
void TitleButtons()
{
    Start.mainProcess(isStartSelected, true, 30);
    Start.SetText("Start");
    Exit.mainProcess(!isStartSelected, true, 30);
    Exit.SetText("Exit");
}
void TitleMenu()
{
    TitleButtons();
    GameTitle.DrawTextWithSort(1000, 1920, "CANYON RUN", titleFontHandle, SORT_CENTER, 200, true, GetColor(255, 255, 255));
    if (isStartSelected && (Input_GetKeyboardDown(KEY_INPUT_SPACE) || Input_GetKeyboardDown(KEY_INPUT_RETURN)))
    {
        sceneChanging = true;
    }
    else if (!isStartSelected && (Input_GetKeyboardDown(KEY_INPUT_SPACE) || Input_GetKeyboardDown(KEY_INPUT_RETURN)))
    {
        Quit = true;
    }
    if (sceneChanging)
    {
        if (fadeout(0.5f))
        {
            stage1Instance->Initialize();
            progress = 255;
            stage1Instance->isStarted = true;
            scene = SCENE_STAGE1;
        }
    }
}