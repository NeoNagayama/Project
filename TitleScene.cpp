#include "TitleScene.h"
#include "Input.h"
#include "Text.h"
#include "main.h"
#include "ui.h"
#include "Stage_Endless.h"

bool isStartSelected = true;
bool sceneChanging = false;
int selected = 0;
float yaxis = 0;
float z = 80;
float x = -100;
VECTOR test = VGet(0,0,0);
Button Start;
Button Extra;
Button Exit;
UIText GameTitle;
int modelhandle[4];
smoke smokes1[180];
smoke smokes2[180];
int smokenum;
stage* stage1Instance;
stage* stage2Instance;
stage* stage3Instance;
stageEndless* Stage4;
void getStagePointers(stage* s1, stage* s2, stage* s3,stageEndless* s4) {
    stage1Instance = s1;
    stage2Instance = s2;
    stage3Instance = s3;
    Stage4 = s4;
}

void TitleInitialProcess()
{
    Start.SetButtonPosition(VGet(1550,445,1),600,100,0.9f);
    Extra.SetButtonPosition(VGet(1550, 645, 1), 600, 100, 0.9f);
    Exit.SetButtonPosition(VGet(1550, 845, 1), 600, 100, 0.9f);
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
    SetupCamera_Perspective(0.55f);
    SetCameraPositionAndTarget_UpVecY(VGet(0, 0.2f, -22), VGet(0, 1.2f, -12));
    if (CheckSoundMem(titleBgm) == 0)
    {
        PlaySoundMem(titleBgm, DX_PLAYTYPE_LOOP);
    }
    if ((Input_GetKeyboardDown(KEY_INPUT_S) || Input_GetKeyboardDown(KEY_INPUT_DOWN))  && !sceneChanging && selected <2)
    {
        selected++;
        PlaySoundMem(selectSound, DX_PLAYTYPE_BACK, true);
    }
    if ((Input_GetKeyboardDown(KEY_INPUT_W) || Input_GetKeyboardDown(KEY_INPUT_UP))  && !sceneChanging && selected >0)
    {
        selected--;
        PlaySoundMem(selectSound, DX_PLAYTYPE_BACK, true);
    }
    DrawModels();
    for (int i = 0; i < 180; i++)
    {
        smokes1[i].DrawSmoke();
        smokes2[i].DrawSmoke();
    }
    TitleMenu();
    if (Input_GetKeyboardDown(KEY_INPUT_P))
    {
        scene = SCENE_STAGEBUILD;
        StopSoundMem(titleBgm);
    }
}
void Titleinitialize()
{
    progress = 0;
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
    smokes1[smokenum].SetPosition(VGet(x - 0.24f, 3, z+0.2f));
    smokes2[smokenum].SetPosition(VGet(x - 3 - 0.24f, 3, z - 2 + 0.2f));
    smokenum++;
    if (smokenum >= 180)
    {
        smokenum = 0;
    }
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
    Start.mainProcess(selected == 0, true, 30);
    Start.SetText("Start");
    Extra.mainProcess(selected == 1, true, 30);
    Extra.SetText("Endless");
    Exit.mainProcess(selected == 2, true, 30);
    Exit.SetText("Exit");
}
void TitleMenu()
{
    TitleButtons();
    GameTitle.DrawTextWithSort(1000, 1920, "CANYON RUN", titleFontHandle, SORT_CENTER, 200, true, GetColor(255, 255, 255));
    if ((Input_GetKeyboardDown(KEY_INPUT_SPACE) || Input_GetKeyboardDown(KEY_INPUT_RETURN)))
    {
        sceneChanging = true;
        PlaySoundMem(interectSound, DX_PLAYTYPE_BACK, true);
        StopSoundMem(titleBgm);
        
    }
    switch (selected)
    {
    case 0:
        if (sceneChanging)
        {
            if (fadeout(0.5f))
            {
                stage1Instance->Initialize();
                progress = 255;
                stage1Instance->isStarted = true;
                scene = SCENE_INSTRUCTION;
            }
        }
        break;
    case 1:
        if (sceneChanging)
        {
            if (fadeout(0.5f))
            {
                Stage4->Init();
                progress = 255;
                Stage4->isStarted = true;
                scene = SCENE_EXTRA;
            }
        }
        break;
    default:
        if (sceneChanging)
        {
            Quit = true;
        }
        break;
    }
    
}