#include "DxLib.h"
#include "TitleScene.h"
#include "stage1Scene.h"
#include "Input.h"
#include"gameOver.h"
#include "Clear.h"
#include "fontLoader.h"
#include "main.h"
#include "Player.h"
#include <random>
//現在の場面
int scene = 0;
//照準用の画像のハンドル
int reticleHandle = 0;
//インゲームのシャドウマップのハンドル
int shadowHandle;
//タイトル画面のシャドウマップのハンドル
int titleShadowHandle;
//背景画像のハンドル
int backGroundHandle;
//照準内の残弾ゲージのハンドル
int reticleInsideGaugeHandle;
//ゲームを終了するための条件用の変数
bool Quit = false;
// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    SetGraphMode(1920, 1080, 32) ,ChangeWindowMode(FALSE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
    //SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_MAXIMUM);
    //奥行0.1～1000までをカメラの描画範囲とする
    SetCameraNearFar(0.1f, 5000.0f);
    SetUseLighting(true);
    SetLightEnable(true);
    SetUseZBuffer3D(TRUE);
    SetWriteZBuffer3D(TRUE);
    reticleHandle = LoadGraph("Reticle.png", false);
    reticleInsideGaugeHandle = LoadGraph("ReticleInsideGauge.png", false);
    backGroundHandle = LoadGraph("backGround.jpg");
    fontLoad();
    //(0,10,-20)の視点から(0,10,0)のターゲットを見る角度にカメラを設置
    SetCameraPositionAndTarget_UpVecY(VGet(0, 0, -20), VGet(0.0f, 0.0f, 0.0f));
    //タイトル画面で最初に一度だけ呼ばれる処理 
    TitleInitialProcess();
    //ステージ1で最初に一度だけ呼ばれる処理
    Stage1InitialProcess();
    //クリア画面で最初に一度だけ呼ばれる処理
    ClearInitialProcess();
    //ゲームオーバー画面で最初に一度だけ呼ばれる処理
    GameOverInitialProcess();
    //インゲームのシャドウマップを作成
    shadowHandle = MakeShadowMap(4096, 4096);
    //タイトル画面のシャドウマップを作成
    titleShadowHandle = MakeShadowMap(4096, 4096);
    //インゲームとタイトルのシャドウマップ用のライトの方向を設定
    SetShadowMapLightDirection(shadowHandle, VGet(0.1f, -0.7f, 0.5f));
    SetShadowMapLightDirection(titleShadowHandle, VGet(0.1f, -0.7f, 0.5f));

    MATERIALPARAM Material;

    Material.Diffuse = GetColorF(0, 0, 0, 0.2f);
    Material.Ambient = GetColorF(0.2f, 0.2f, 0.24f, 0.2f);
    Material.Specular = GetColorF(0.2f, 0.2f, 0.2f, 0.2f);
    Material.Emissive = GetColorF(0.1f, 0.1f, 0.1f, 0.0f);
    Material.Power = 3.0f;
    SetMaterialParam(Material);

    while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !Quit) {
        Input_UpdateKeyboard();
        //場面の切り替え
        switch (scene) {
            //場面別の毎フレーム呼ばれる処理
        case SCENE_STAGE1:
            Stage1MainProcess();
            break;
        case SCENE_GAMEOVER:
            GameOverMainProcess();
            break;
        case SCENE_CLEAR:
            ClearMainProcess();
            break;
        default:
            //背景の描画
            DrawGraph3D(0, 650,  1800, backGroundHandle, false);
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

