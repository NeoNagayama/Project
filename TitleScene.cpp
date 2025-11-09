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
VECTOR test = VGet(0,0,0);
Button Start;
Button Exit;
UIText GameTitle;
int modelhandle[4];
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
    modelhandle[0] = MV1LoadModel("PlayerModel.mv1");
    MV1SetPosition(modelhandle[0], VGet(-0.4, 0.2f, -19.2f));
    MV1SetRotationXYZ(modelhandle[0], VGet(0, 2.53f, 0));
    modelhandle[1] = MV1DuplicateModel(modelhandle[0]);
    modelhandle[2] = MV1DuplicateModel(modelhandle[0]);
    modelhandle[3] = MV1DuplicateModel(carrierHandle);
    MV1SetPosition(modelhandle[3], VGet(0.78, -1.28f, -18.3));
    MV1SetRotationXYZ(modelhandle[3], VGet(0, PI, 0));
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < MV1GetMaterialNum(modelhandle[j]); i++)
        {
            MV1SetMaterialDifColor(modelhandle[j], i, GetColorF(0.7f, 0.7f, 0.7f, 1.0f));
            MV1SetMaterialAmbColor(modelhandle[j], i, GetColorF(0.2f, 0.2f, 0.2f, 1.0f));
            MV1SetMaterialSpcColor(modelhandle[j], i, GetColorF(0.4f, 0.4f, 0.4f, 1));
            MV1SetMaterialEmiColor(modelhandle[j], i, GetColorF(0.3f, 0.3f, 0.3f, 0.2f));
            MV1SetMaterialSpcPower(modelhandle[j], i, 6);
        }
    }
    
}
void TitleMainProcess()
{
    
    DrawShadow();
    SetUseShadowMap(0, titleShadowHandle);
    if (CheckHitKey(KEY_INPUT_I))
    {
        test.z += 1 * oneFlame;
    }
    if (CheckHitKey(KEY_INPUT_K))
    {
        test.z -= 1 * oneFlame;
    }
    if (CheckHitKey(KEY_INPUT_L))
    {
        test.x += 1 * oneFlame;
    }
    if (CheckHitKey(KEY_INPUT_J))
    {
        test.x -= 1 * oneFlame;
    }
    if (CheckHitKey(KEY_INPUT_O))
    {
        test.y += 1 * oneFlame;
    }
    if (CheckHitKey(KEY_INPUT_U))
    {
        test.y -= 1 * oneFlame;
    }
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
    MV1DrawModel(modelhandle[1]);
    MV1DrawModel(modelhandle[2]);
    MV1DrawModel(modelhandle[0]);
    MV1DrawModel(modelhandle[3]);
    ShadowMap_DrawEnd();
}
void DrawModels()
{
    z -= 0.2f;
    x += 0.24f;

    //MV1SetPosition(carrierHandle,test);
    MV1SetPosition(modelhandle[1], VGet(x, 3, z));
    MV1SetPosition(modelhandle[2], VGet(x - 3, 3, z - 2));
    MV1SetRotationXYZ(modelhandle[1], VGet(0, 2.1f, 0));
    MV1SetRotationXYZ(modelhandle[2], VGet(0, 2.1f, 0));
    MV1DrawModel(modelhandle[1]);
    MV1DrawModel(modelhandle[2]);
    MV1DrawModel(modelhandle[0]);
    MV1DrawModel(modelhandle[3]);
    //DrawCube3D(VGet(-200.0f, -0.01f, -200.0f), VGet(200.0f, -1.1f, 200.0f), GetColor(120, 120, 120), GetColor(120, 120, 120), TRUE);
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