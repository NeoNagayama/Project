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
float z = 80;
float x = -100;
Button Start;
Button Exit;
int modelhandle,modelHandle2,modelHandle3;
void TitleInitialProcess()
{
    Start.SetButtonPosition(VGet(1550,545,1),600,100,0.9f);
    Exit.SetButtonPosition(VGet(1550, 745, 1), 600, 100, 0.9f);
    modelhandle = MV1LoadModel("F-14Test.mv1");
    MV1SetPosition(modelhandle,VGet(-1, 0.19f, -18.3f));
    MV1SetRotationXYZ(modelhandle, VGet(0, 2.53f, 0));
    modelHandle2 = MV1LoadModel("F-14Test.mv1");
    modelHandle3 = MV1LoadModel("F-14Test.mv1");
}
void TitleMainProcess()
{

    SetShadowMapDrawArea(shadowHandle, VGet(-1000.0f, -2.0f, -1000.0f), VGet(1000.0f, 1000.0f, 1000.0f));
    ShadowMap_DrawSetup(shadowHandle);
    MV1DrawModel(modelHandle2);
    MV1DrawModel(modelHandle3);
    MV1DrawModel(modelhandle);
    DrawCube3D(VGet(-200.0f, -1.0f, -200.0f), VGet(200.0f, -1.1f, 200.0f), GetColor(120, 120, 120), GetColor(0, 0, 0), TRUE);
    ShadowMap_DrawEnd();
    SetUseShadowMap(0, shadowHandle);
    SetupCamera_Perspective(1.4f);
    SetCameraPositionAndTarget_UpVecY(VGet(0, 6, -22), VGet(0, 2.0f, -12));
    if (Input_GetKeyboardDown(KEY_INPUT_S)  && isStartSelected == true && !sceneChanging)
    {
        isStartSelected = false;
    }
    if (Input_GetKeyboardDown(KEY_INPUT_W) && isStartSelected == false && !sceneChanging)
    {
        isStartSelected = true;
    }
    z -= 0.2f;
    x += 0.23f;
    //x += 0.2f;
    clsDx();
    printfDx("%f", yaxis);
    MV1SetPosition(modelHandle2, VGet(x, 4, z));
    MV1SetPosition(modelHandle3, VGet(x -3, 4, z-2));
    MV1SetRotationXYZ(modelHandle2, VGet(0, 2.3f, 0));
    MV1SetRotationXYZ(modelHandle3, VGet(0, 2.3f, 0));
    MV1DrawModel(modelHandle2);
    MV1DrawModel(modelHandle3);
    MV1DrawModel(modelhandle);
    MATERIALPARAM Material;

    Material.Diffuse = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
    Material.Ambient = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
    Material.Specular = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
    Material.Emissive = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
    Material.Power = 20.0f;
    SetMaterialParam(Material);
    DrawCube3D(VGet(-200.0f, -1.0f, -200.0f), VGet(200.0f, -1.1f, 200.0f), GetColor(120, 120, 120), GetColor(0, 0, 0), TRUE);
    if (z < -60)
    {
        z = get_rand(80,90);
        x = -100;
    }
    Start.mainProcess(isStartSelected,true,30);
    Start.SetText("Start");
    Exit.mainProcess(!isStartSelected,true,30);
    Exit.SetText("Exit");
    textPositionSet(1000, 1920, "CANYON RUN", titleFontHandle, SORT_CENTER, 200, true, GetColor(255,255,255));
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
