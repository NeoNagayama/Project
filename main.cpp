#include "DxLib.h"
#include "TitleScene.h"
#include "Stage.h"
#include "Input.h"
#include"gameOver.h"
#include "Clear.h"
#include "Text.h"
#include "main.h"
#include "Player.h"
#include "Instruction.h"
#include "StageBuild.h"
#include "Stage_Endless.h"
#include <random>
//現在の場面
int scene = 0;
int stages =0;
//照準用の画像のハンドル
int reticleHandle = 0;
//インゲームのシャドウマップのハンドル
int shadowHandle;
//タイトル画面のシャドウマップのハンドル
int titleShadowHandle;
//背景画像のハンドル
int backGroundHandle;
//int skySphereHandle;
//照準内の残弾ゲージのハンドル
int reticleInsideGaugeHandle;
int cargoModelOrigin;
int bulletHandle;
int enemyBulletHandle;
int carrierHandle;
int lowerObstacleHandle;
int missileBurnerHandle;
int smokeHandle;
int explosionHandle;
int wallHandle;
int guideHandle;
int instGraph;
int spaceGraph;
int alertGraph;
int gaugeHandle;
int barHandle;
int E_gauge;
int E_bar;
int highScore;
int interectSound;
int selectSound;
int missileAlertSound;
int pitbullSound;
int flareSound;
int playerShotSound;
int enemyShotSound;
int frybySound;
int engineSound;
int hitSound;
int explosionSound;
int ingameBgm;
int titleBgm;
int playerLight;
int enemyLight;
int sideObstacle;
bool isGetDamaged;
float timeScale = 1;
//ゲームを終了するための条件用の変数
bool Quit = false;
int stage1Obstacle[50] = {
    0,0,0,0,0,
    3,4,3,0,0,
    2,3,4,8,0,
    0,0,9,0,10,
    0,1,3,5,10,
    0,0,0,0,0,
    3,4,3,0,0,
    2,3,4,8,0,
    0,0,9,0,10,
    0,1,3,5,10
};
int stage1ObstacleType[50] = {
        0,0,0,0,0,
        3,3,3,0,0,
        1,1,1,1,0,
        0,0,3,0,3,
        0,1,1,1,1,
        0,0,0,0,0,
        3,3,3,0,0,
        1,1,1,1,0,
        0,0,3,0,3,
        0,1,1,1,1
};
int stage2Obstacle[50] = {
    0,0,0,0,0,
    1,0,6,3,7,
    4,5,5,8,9,
    8,9,0,0,0,
    6,8,6,8,0,
    0,10,10,5,5,
    0,0,0,2,2,
    8,8,2,2,9,
    9,3,3,2,9,
    2,9,0,0,0
};
int stage2ObstacleType[50] = {
    0,0,0,0,0,
    1,1,1,1,1,
    1,1,1,1,1,
    1,1,0,0,0,
    3,3,1,1,0,
    0,3,1,3,1,
    0,0,0,3,3,
    3,3,1,1,1,
    1,3,3,1,1,
    1,1,0,0,0
};
int stage3Obstacle[50] = {
    0,0,0,0,0,
    1,1,6,6,7,
    7,5,5,8,9,
    8,9,0,0,0,
    6,8,6,8,0,
    0,10,10,5,5,
    0,0,0,2,2,
    8,8,2,2,9,
    9,3,3,2,9,
    2,9,0,0,0
};
int stage3ObstacleType[50] = {
    0,0,0,0,0,
    1,1,1,1,1,
    1,1,1,1,1,
    1,1,0,0,0,
    3,3,1,1,0,
    0,3,1,3,1,
    0,0,0,3,3,
    3,3,1,1,1,
    1,3,3,1,1,
    1,1,0,0,0
};
int stage3movewall[50];
int stage1movewall[50] = {
        3,1,5,3,2,
        1,4,5,2,1,
        1,3,5,2,3,
        1,5,1,2,4,
        1,5,3,2,4,
        1,2,3,4,5,
        0,1,2,3,4,
        5,0,1,2,3,
        4,5,0,1,2,
        3,4,5,0,1
};
int stage2movewall[50] = {
        3,1,5,3,2,
        1,4,5,2,1,
        1,3,5,2,3,
        1,5,1,2,4,
        1,5,3,2,4,
        1,2,3,4,5,
        0,1,2,3,4,
        5,0,1,2,3,
        4,5,0,1,2,
        3,4,5,0,1
};
stage stage1;
stage stage2;
stage stage3;
stageEndless endless;
instruction inst;
builder bil;

int PlayerLightHandle;
// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    SetGraphMode(1920, 1080, 32) ,ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
    //SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_MAXIMUM);
    //奥行0.1～1000までをカメラの描画範囲とする
    SetCameraNearFar(0.1f, 5000.0f);
    SetUseLighting(TRUE);
    SetLightEnable(TRUE);
    SetUseZBuffer3D(TRUE);
    SetWriteZBuffer3D(TRUE);
    SetUseTransColorGraphCreateFlag(TRUE);
    //(0,10,-20)の視点から(0,10,0)のターゲットを見る角度にカメラを設置
    SetCameraPositionAndTarget_UpVecY(VGet(0, 0, -20), VGet(0.0f, 0.0f, 0.0f));
    LoadAssets();
    setVolume();
    setupShadowMap();
    Init();
    MATERIALPARAM Material;

    Material.Diffuse = GetColorF(0.2f, 0.2f, 0.2f, 0.2f);
    Material.Ambient = GetColorF(0.2f, 0.2f, 0.24f, 0.1f);
    Material.Specular = GetColorF(0.2f, 0.2f, 0.2f, 0.2f);
    Material.Emissive = GetColorF(0.1f, 0.1f, 0.1f, 0.0f);
    Material.Power = 0.1f;
    SetMaterialParam(Material);
    PlayerLightHandle = CreateDirLightHandle(VGet(0, 0.7f, -0.3f));
    SetLightEnableHandle(PlayerLightHandle, true);
    SetLightDifColorHandle(PlayerLightHandle, GetColorF(0.8f, 0.8f, 0.8f, 0.4f));
    SetLightSpcColorHandle(PlayerLightHandle, GetColorF(0.4f, 0.4f, 0.4f, 0.4f));
    enemyLight = CreatePointLightHandle(VGet(0,0,0), 5, 0.1f, 0.1f, 0.1f);
    playerLight = CreatePointLightHandle(VGet(0, 0, 0), 5, 0.1f, 0.1f, 0.1f);
    SetLightDifColorHandle(enemyLight, GetColorF(1, 0.3f, 0, 1));
    SetLightSpcColorHandle(enemyLight, GetColorF(1, 0.3f, 0, 1));
    SetLightAmbColorHandle(enemyLight, GetColorF(1, 0.3f, 0, 1));
    SetLightDifColorHandle(playerLight, GetColorF(0, 0.3f, 1, 1));
    SetLightSpcColorHandle(playerLight, GetColorF(0, 0.3f, 1, 1));
    SetLightAmbColorHandle(playerLight, GetColorF(0, 0.3f, 1, 1));

    while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !Quit) {
        Input_UpdateKeyboard();
        
       /* MV1SetPosition(skySphereHandle, GetCameraPosition());
        MV1DrawModel(skySphereHandle);*/
        //場面の切り替え
        switch (scene) {
            //場面別の毎フレーム呼ばれる処理
        case SCENE_INGAME:
            if (CheckSoundMem(ingameBgm) == 0)
            {
                PlaySoundMem(ingameBgm, DX_PLAYTYPE_LOOP);
            }
            switch (stages)
            {
            case STAGE1:
                stage1.MainProcess();
                break;
            case STAGE2:
                stage2.MainProcess();
                break;
            case STAGE3:
                stage3.MainProcess();
                break;
            }
            break;
        case SCENE_INSTRUCTION:
            inst.main();
            stage1.Initialize();
            stage2.Initialize();
            stage3.Initialize();
            StopSoundMem(ingameBgm);
            break;
        case SCENE_STAGEBUILD:
            bil.main();
            StopSoundMem(ingameBgm);
            break;
        case SCENE_EXTRA:
            endless.main(); 
            if (CheckSoundMem(ingameBgm) == 0)
            {
                PlaySoundMem(ingameBgm, DX_PLAYTYPE_LOOP);
            }
            break;
        default:
            //背景の描画
            DrawGraph3D(0, 600,  1800, backGroundHandle, false);
            TitleMainProcess();
            StopSoundMem(ingameBgm);
            break;
        }
        WaitTimer(16);
        SetUseShadowMap(0, -1);
        if (isGetDamaged)
        {
            CameraShake();
        }
    }
    DeleteShadowMap(shadowHandle);
    DeleteShadowMap(titleShadowHandle);
    DxLib_End();
    return 0;				// ソフトの終了 
}

float smooth(float from, float to, float t) 
{
    
    //n = n * ((middle - ((middle > n ? middle : n) - (middle < n ? middle : n))) / middle);
    float n = ((from > to ? from : to) - (from < to ? from : to)) / (t * 0.5f);
    return n;
}
float VectorLength(VECTOR from, VECTOR to)
{
    VECTOR difference = VGet(to.x - from.x, to.y - from.y, to.z - from.z);
    return sqrtf((difference.x * difference.x) + (difference.y * difference.y) + (difference.z * difference.z));
}
int  get_rand(int min, int max)
{
    static std::mt19937 mt(0);
    std::uniform_int_distribution<int> get_rand_uni_int(min, max);
    return get_rand_uni_int(mt);
}
VECTOR VectorDirectionNormalize(VECTOR to, VECTOR from)
{
    return VNorm(VGet(from.x - to.x, from.y - to.y, from.z - to.z));
}
void LoadAssets()
{
    carrierHandle = MV1LoadModel("Resource/AircraftCarrier.mv1");
    reticleHandle = LoadGraph("Resource/Reticle.png", false);
    reticleInsideGaugeHandle = LoadGraph("Resource/ReticleInsideGauge.png", false);
    backGroundHandle = LoadGraph("Resource/backGround.jpg");
    bulletHandle = MV1LoadModel("Resource/bullet.mv1");
    enemyBulletHandle = MV1LoadModel("Resource/bullet.mv1");
    //skySphereHandle = MV1LoadModel("SkySphereTest.mv1");
    cargoModelOrigin = MV1LoadModel("Resource/cargo.mv1");
    lowerObstacleHandle = MV1LoadModel("Resource/LowerObstacle.mv1");
    missileBurnerHandle = LoadGraph("Resource/missileBurner.png");
    smokeHandle = LoadGraph("Resource/smoke1.png");
    explosionHandle = LoadGraph("Resource/explosion.png");
    wallHandle = MV1LoadModel("Resource/wall.mv1");
    guideHandle = LoadGraph("Resource/guideBeacon.png");
    instGraph = LoadGraph("Resource/Instruction.png");
    spaceGraph = LoadGraph("Resource/Space.png");
    alertGraph = LoadGraph("Resource/MissileAlert.png");
    gaugeHandle = LoadGraph("Resource/ProgressGauge.png");
    barHandle = LoadGraph("Resource/ProgressBar.png");
    E_bar = LoadGraph("Resource/EnemyBar.png");
    E_gauge = LoadGraph("Resource/EnemyGauge.png");
    interectSound = LoadSoundMem("Resource/sfx/interect2.mp3");
    selectSound = LoadSoundMem("Resource/sfx/interect.mp3");
    missileAlertSound = LoadSoundMem("Resource/sfx/alert.mp3");
    pitbullSound = LoadSoundMem("Resource/sfx/pitbull.mp3");
    flareSound = LoadSoundMem("Resource/sfx/flare.mp3");
    playerShotSound = LoadSoundMem("Resource/sfx/shot2.mp3");
    enemyShotSound = LoadSoundMem("Resource/sfx/enemyShot.mp3");
    frybySound = LoadSoundMem("Resource/sfx/flyby.mp3");
    engineSound = LoadSoundMem("Resource/sfx/playerEngine.mp3");
    hitSound = LoadSoundMem("Resource/sfx/hit.mp3");
    explosionSound = LoadSoundMem("Resource/sfx/explosion.mp3");
    ingameBgm = LoadSoundMem("Resource/sfx/ingame.mp3");
    titleBgm = LoadSoundMem("Resource/sfx/title.mp3");
    sideObstacle = MV1LoadModel("Resource/sideObstacle.mv1");
    fontLoad();
}
void setupShadowMap()
{
    //インゲームのシャドウマップを作成
    shadowHandle = MakeShadowMap(4096, 4096);
    //タイトル画面のシャドウマップを作成
    titleShadowHandle = MakeShadowMap(4096, 4096);
    //インゲームとタイトルのシャドウマップ用のライトの方向を設定
    SetShadowMapLightDirection(shadowHandle, VGet(0, -0.7f, 0.3f));
    SetShadowMapLightDirection(titleShadowHandle, VGet(0.1f, -0.7f, 0.5f));
}
void Init()
{
    //タイトル画面で最初に一度だけ呼ばれる処理 
    TitleInitialProcess();
    //ステージ1で最初に一度だけ呼ばれる処理
    LoadStage1();
    LoadStage2();
    LoadStage3();
    stage1.InitialProcess(stage1Obstacle, stage1ObstacleType,stage1movewall);
    stage2.InitialProcess(stage2Obstacle, stage2ObstacleType, stage2movewall);
    stage3.InitialProcess(stage3Obstacle, stage3ObstacleType, stage3movewall);
    bil.InitialProcess(stage2Obstacle, stage2ObstacleType, stage2movewall);
    //クリア画面で最初に一度だけ呼ばれる処理
    ClearInitialProcess();
    //ゲームオーバー画面で最初に一度だけ呼ばれる処理
    GameOverInitialProcess();
    getStagePointers(&stage1, &stage2, &stage3,&endless);
    GameOverGetStagePointers(&stage1, &stage2, &stage3,&endless);
    ClearGetStagePointers(&stage1, &stage2, &stage3);
    bil.Init();
    endless.SetUp();
    endless.Init();
}
void LoadStage3()
{
    FILE* file;
    FILE* file1;
    FILE* file2;
    errno_t err;
    errno_t err1;
    errno_t err2;
    err = fopen_s(&file, "maps/defaultMaps/stage3type.dat", "rb");
    err1 = fopen_s(&file1, "maps/defaultMaps/stage3obs.dat", "rb");
    err2 = fopen_s(&file2, "maps/defaultMaps/stage3wall.dat", "rb");
    if (err == 0 || err1 == 0 || err2 == 0)
    {
        for (int i = 0; i < 50; i++)
        {
            stage3Obstacle[i] = 0;
            stage3ObstacleType[i] = 0;
            stage3movewall[i] = 0;
        }
        fread(stage3ObstacleType, sizeof(int), 50, file);
        fread(stage3Obstacle, sizeof(int), 50, file1);
        fread(stage3movewall, sizeof(int), 50, file2);
        fclose(file);
        fclose(file1);
        fclose(file2);
    }
}

void LoadStage2()
{
    FILE* file;
    FILE* file1;
    FILE* file2;
    errno_t err;
    errno_t err1;
    errno_t err2;
    err = fopen_s(&file, "maps/defaultMaps/stage2type.dat", "rb");
    err1 = fopen_s(&file1, "maps/defaultMaps/stage2obs.dat", "rb");
    err2 = fopen_s(&file2, "maps/defaultMaps/stage2wall.dat", "rb");
    if (err == 0 || err1 == 0 || err2 == 0)
    {
        for (int i = 0; i < 50; i++)
        {
            stage2Obstacle[i] = 0;
            stage2ObstacleType[i] = 0;
            stage2movewall[i] = 0;
        }
        fread(stage2ObstacleType, sizeof(int), 50, file);
        fread(stage2Obstacle, sizeof(int), 50, file1);
        fread(stage2movewall, sizeof(int), 50, file2);
        fclose(file);
        fclose(file1);
        fclose(file2);
    }
}
void LoadStage1()
{
    FILE* file;
    FILE* file1;
    FILE* file2;
    errno_t err;
    errno_t err1;
    errno_t err2;
    err = fopen_s(&file, "maps/defaultMaps/stage1type.dat", "rb");
    err1 = fopen_s(&file1, "maps/defaultMaps/stage1obs.dat", "rb");
    err2 = fopen_s(&file2, "maps/defaultMaps/stage1wall.dat", "rb");
    if (err == 0 || err1 == 0 || err2 == 0)
    {
        for (int i = 0; i < 50; i++)
        {
            stage1Obstacle[i] = 0;
            stage1ObstacleType[i] = 0;
            stage1movewall[i] = 0;
        }
        fread(stage1ObstacleType, sizeof(int), 50, file);
        fread(stage1Obstacle, sizeof(int), 50, file1);
        fread(stage1movewall, sizeof(int), 50, file2);
        fclose(file);
        fclose(file1);
        fclose(file2);
    }
}
void LoadScore()
{
    FILE* file;
    errno_t err = fopen_s(&file, "data/hs.dat", "rb");
    if (err == 0)
    {
        fread(&highScore, sizeof(float), 1, file);
        fclose(file);
    }
    else
    {
        highScore = 0;
    }
}
void setVolume()
{
    ChangeVolumeSoundMem(120, selectSound);
    ChangeVolumeSoundMem(120, interectSound);
    ChangeVolumeSoundMem(60, engineSound);
}
void CameraShake()
{
    int range = 3;
    int mult = 10;
    VECTOR camPos = GetCameraPosition();
    VECTOR targetPos = GetCameraTarget();
    VECTOR offset = VGet((float)get_rand(-range, range) / mult,(float)get_rand(-range, range) / mult, 0);
    SetCameraPositionAndTarget_UpVecY(VAdd(camPos, offset), VAdd(targetPos, offset));
    isGetDamaged = false;
}

