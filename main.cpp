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
#include <random>
//現在の場面
int scene = 0;
int stages = 0;
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
stage stage1;
stage stage2;
stage stage3;
instruction inst;

int PlayerLightHandle;
// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    SetGraphMode(1920, 1080, 32) ,ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
    //SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_MAXIMUM);
    //奥行0.1～1000までをカメラの描画範囲とする
    SetCameraNearFar(0.1f, 5000.0f);
    SetUseLighting(true);
    SetLightEnable(true);
    SetUseZBuffer3D(TRUE);
    SetWriteZBuffer3D(TRUE);
    //(0,10,-20)の視点から(0,10,0)のターゲットを見る角度にカメラを設置
    SetCameraPositionAndTarget_UpVecY(VGet(0, 0, -20), VGet(0.0f, 0.0f, 0.0f));
    LoadAssets();
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

    while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !Quit) {
        Input_UpdateKeyboard();
        
       /* MV1SetPosition(skySphereHandle, GetCameraPosition());
        MV1DrawModel(skySphereHandle);*/
        //場面の切り替え
        switch (scene) {
            //場面別の毎フレーム呼ばれる処理
        case SCENE_INGAME:
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
            break;
        default:
            //背景の描画
            DrawGraph3D(0, 600,  1800, backGroundHandle, false);
            TitleMainProcess();
            break;
        }
        WaitTimer(16);
        SetUseShadowMap(0, -1);
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
    carrierHandle = MV1LoadModel("AircraftCarrier.mv1");
    reticleHandle = LoadGraph("Reticle.png", false);
    reticleInsideGaugeHandle = LoadGraph("ReticleInsideGauge.png", false);
    backGroundHandle = LoadGraph("backGround.jpg");
    bulletHandle = LoadGraph("bullet.png");
    enemyBulletHandle = LoadGraph("enemyBullet.png");
    //skySphereHandle = MV1LoadModel("SkySphereTest.mv1");
    cargoModelOrigin = MV1LoadModel("cargo.mv1");
    lowerObstacleHandle = MV1LoadModel("LowerObstacle.mv1");
    missileBurnerHandle = LoadGraph("missileBurner.png");
    smokeHandle = LoadGraph("smoke1.png");
    explosionHandle = LoadGraph("explosion.png");
    wallHandle = MV1LoadModel("wall.mv1");
    guideHandle = LoadGraph("guideBeacon.png");
    instGraph = LoadGraph("Instruction.png");
    spaceGraph = LoadGraph("Space.png");
    alertGraph = LoadGraph("MissileAlert.png");
    gaugeHandle = LoadGraph("ProgressGauge.png");
    barHandle = LoadGraph("ProgressBar.png");
    E_bar = LoadGraph("EnemyBar.png");
    E_gauge = LoadGraph("EnemyGauge.png");
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
    stage1.InitialProcess(stage1Obstacle, stage1ObstacleType);
    stage2.InitialProcess(stage2Obstacle, stage2ObstacleType);
    stage3.InitialProcess(stage3Obstacle, stage3ObstacleType);
    //クリア画面で最初に一度だけ呼ばれる処理
    ClearInitialProcess();
    //ゲームオーバー画面で最初に一度だけ呼ばれる処理
    GameOverInitialProcess();
    getStagePointers(&stage1, &stage2, &stage3);
    GameOverGetStagePointers(&stage1, &stage2, &stage3);
    ClearGetStagePointers(&stage1, &stage2, &stage3);
}

