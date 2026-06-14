#include "TitleScene.h"
#include "Input.h"
#include "Stage_Endless.h"
#include "Text.h"
#include "main.h"
#include "ui.h"
#include <codecvt>
#include <string>
bool isStartSelected = true;
bool sceneChanging = false;
int selected = 0;
int prog = 0;
float yaxis = 0;
float z = 80;
float x = -100;
timer timeerrrr;
VECTOR test = VGet(0, 0, 0);
Button Start;
Button Extra;
Button Exit;
UIText GameTitle;
UIText info;
int modelhandle[4];
smoke smokes1[MISSILE_SMOKE_COUNT];
smoke smokes2[MISSILE_SMOKE_COUNT];
int smokenum;
int titleSmokeInterval = 0;
stage *stage1Instance;
stage *stage2Instance;
stage *stage3Instance;
stageEndless *Stage4;

std::string WStringToString(std::wstring oWString)
{
    // wstring → SJIS
    int iBufferSize = WideCharToMultiByte(CP_OEMCP, 0, oWString.c_str(), -1, (char *)NULL, 0, NULL, NULL);

    // バッファの取得
    CHAR *cpMultiByte = new CHAR[iBufferSize];

    // wstring → SJIS
    WideCharToMultiByte(CP_OEMCP, 0, oWString.c_str(), -1, cpMultiByte, iBufferSize, NULL, NULL);

    // stringの生成
    std::string oRet(cpMultiByte, cpMultiByte + iBufferSize - 1);

    // バッファの破棄
    delete[] cpMultiByte;

    // 変換結果を返す
    return (oRet);
}

void getStagePointers(stage *s1, stage *s2, stage *s3, stageEndless *s4)
{
    // 各ステージのポインタを受け取る
    stage1Instance = s1;
    stage2Instance = s2;
    stage3Instance = s3;
    Stage4 = s4;
}

void TitleSetUp()
{
    // 各ボタンの位置を設定する
    Start.SetButtonPosition(VGet(1550, 445, 1), 600, 150, 0.9f, ANCHOR_RIGHT);
    Extra.SetButtonPosition(VGet(1550, 645, 1), 600, 150, 0.9f, ANCHOR_RIGHT);
    Exit.SetButtonPosition(VGet(1550, 845, 1), 600, 150, 0.9f, ANCHOR_RIGHT);
    // 各ボタンの画像を設定する
    Start.SetGraph(buttonGraph);
    Extra.SetGraph(buttonGraph);
    Exit.SetGraph(buttonGraph);
    // 使用されるモデルのロードと位置と角度の設定
    modelhandle[0] = MV1LoadModel("Resource/PlayerModel.mv1");
    MV1SetPosition(modelhandle[0], VGet(-0.4f, 0.2f, -19.2f));
    MV1SetRotationXYZ(modelhandle[0], VGet(0, 2.53f, 0));
    modelhandle[1] = MV1DuplicateModel(modelhandle[0]);
    modelhandle[2] = MV1DuplicateModel(modelhandle[0]);
    modelhandle[3] = MV1DuplicateModel(carrierHandle);
    MV1SetPosition(modelhandle[3], VGet(0.78f, -1.28f, -18.3f));
    MV1SetRotationXYZ(modelhandle[3], VGet(0, PI, 0));
    // 使用される各モデルのマテリアルの設定
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < MV1GetMaterialNum(modelhandle[j]); i++)
        {
            MV1SetMaterialDifColor(modelhandle[j], i, GetColorF(0.7f, 0.7f, 0.7f, 1.0f));
            MV1SetMaterialAmbColor(modelhandle[j], i, GetColorF(0.4f, 0.4f, 0.4f, 1.0f));
            MV1SetMaterialSpcColor(modelhandle[j], i, GetColorF(0.4f, 0.4f, 0.4f, 1));
            MV1SetMaterialEmiColor(modelhandle[j], i, GetColorF(0.3f, 0.3f, 0.3f, 0.2f));
            MV1SetMaterialSpcPower(modelhandle[j], i, 6);
        }
    }
}

void TitleMain()
{
    // シャドウマップ関連の処理
    DrawShadow();
    SetUseShadowMap(0, titleShadowHandle);
    // カメラの設定
    SetupCamera_Perspective(0.55f);
    SetCameraPositionAndTarget_UpVecY(VGet(0, 0.2f, -22), VGet(0, 1.2f, -12));
    // bgmが流れていなければ流す
    if (CheckSoundMem(titleBgm) == 0)
    {
        PlaySoundMem(titleBgm, DX_PLAYTYPE_LOOP);
    }
    // WSキーで選択しているボタンを切り替える
    if ((Input_GetKeyboardDown(KEY_INPUT_S) || Input_GetKeyboardDown(KEY_INPUT_DOWN)) && !sceneChanging && selected < 2)
    {
        selected++;
        PlaySoundMem(selectSound, DX_PLAYTYPE_BACK, true);
    }
    if ((Input_GetKeyboardDown(KEY_INPUT_W) || Input_GetKeyboardDown(KEY_INPUT_UP)) && !sceneChanging && selected > 0)
    {
        selected--;
        PlaySoundMem(selectSound, DX_PLAYTYPE_BACK, true);
    }
    // モデルの描画
    DrawModels();
    const float cameraZ = GetCameraPosition().z;
    for (int i = 0; i < MISSILE_SMOKE_COUNT; i++)
    {
        if (smokes1[i].isActive)
        {
            smokes1[i].DrawSmoke(cameraZ);
        }
        if (smokes2[i].isActive)
        {
            smokes2[i].DrawSmoke(cameraZ);
        }
    }
    DrawExtendGraph(1000, -200, 2131, 1832, menuBackground, true);
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
    // シャドウマップの描画範囲の設定をする
    SetShadowMapDrawArea(titleShadowHandle, VGet(-200.0f, -100.0f, -200.0f), VGet(200.0f, 100.0f, 200.0f));
    ShadowMap_DrawSetup(titleShadowHandle);
    // 各モデルの描画
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

    // MV1SetPosition(carrierHandle,test);
    // 背景で飛んでいる機体の移動の処理
    MV1SetPosition(modelhandle[1], VGet(x, 3, z));
    MV1SetPosition(modelhandle[2], VGet(x - 3, 3, z - 2));
    // ?????u????
    if (titleSmokeInterval <= 0)
    {
        smokes1[smokenum].SetPosition(VGet(x - 0.24f, 3, z + 0.2f));
        smokes2[smokenum].SetPosition(VGet(x - 3 - 0.24f, 3, z - 2 + 0.2f));
        smokenum++;
        titleSmokeInterval = SMOKE_SPAWN_INTERVAL;
        if (smokenum >= MISSILE_SMOKE_COUNT)
        {
            smokenum = 0;
        }
    }
    else
    {
        titleSmokeInterval--;
    }
    // ???f????p?x????
    MV1SetRotationXYZ(modelhandle[1], VGet(0, 2.1f, 0));
    MV1SetRotationXYZ(modelhandle[2], VGet(0, 2.1f, 0));
    // モデルの描画
    MV1DrawModel(modelhandle[1]);
    MV1DrawModel(modelhandle[2]);
    MV1DrawModel(modelhandle[0]);
    MV1DrawModel(modelhandle[3]);
    // 背景で飛んでいる機体が特定の位置まで行ったら元の位置からランダムにずらした位置に戻る
    if (z < -60)
    {
        z = (float)get_rand(80, 90);
        x = -100.0f;
    }
}

void TitleButtons()
{
    // ボタンの処理
    Start.Main(selected == 0, true, 30);
    Start.SetText("Start");
    Extra.Main(selected == 1, true, 30);
    Extra.SetText("Endless");
    Exit.Main(selected == 2, true, 30);
    Exit.SetText("Exit");
}

void TitleMenu()
{
    // ボタンの処理
    TitleButtons();
    GameTitle.DrawTextWithSort(1000, 1920, "CANYON RUN", titleFontHandle, SORT_CENTER, 200, true,
                               GetColor(255, 255, 255));
    // spaceキーで場面の遷移を始める
    if ((Input_GetKeyboardDown(KEY_INPUT_SPACE) || Input_GetKeyboardDown(KEY_INPUT_RETURN)))
    {
        sceneChanging = true;
        PlaySoundMem(interectSound, DX_PLAYTYPE_BACK, true);
        StopSoundMem(titleBgm);
    }
    // 選択されているボタンに応じた処理
    switch (selected)
    {
    case 0:
        // ステージ1への遷移
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
        info.DrawTextWithSort(90, 1920, "ゲームをステージ1から開始します", biggerJpFontHandle, SORT_LEFT, 800, true,
                              GetColor(255, 255, 255));
        break;
    case 1:
        // エンドレスモードへの遷移
        if (sceneChanging)
        {
            if (fadeout(0.5f))
            {
                Stage4->Init();
                progress = 255;
                Stage4->isStarted = true;
                scene = SCENE_INST_EX;
            }
        }
        info.DrawTextWithSort(90, 1920, "エンドレスモードを開始します\n高難易度です", biggerJpFontHandle, SORT_LEFT,
                              800, true, GetColor(255, 255, 255));
        break;
    default:
        // ゲームを終了する
        if (sceneChanging)
        {
            Quit = true;
        }
        info.DrawTextWithSort(90, 1920, "ゲームを終了します", biggerJpFontHandle, SORT_LEFT, 800, true,
                              GetColor(255, 255, 255));
        break;
    }
}