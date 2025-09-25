#include "DxLib.h"
#include "TitleScene.h"
#include "stage1Scene.h"
#include "Input.h"
#include"gameOver.h"
#include "Clear.h"
#include "fontLoader.h"
#include "main.h"
#include "Player.h"
int scene = 0;
// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    SetGraphMode(1920, 1080, 32) ,ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
    //SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_MAXIMUM);
    //奥行0.1～1000までをカメラの描画範囲とする
    SetCameraNearFar(0.1f, 1000.0f);
    SetUseLighting(true);
    SetLightEnable(true);
    
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

    while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {
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
            TitleMainProcess();
            break;
        }
        WaitTimer(16);
    }

    DxLib_End();				// ＤＸライブラリ使用の終了処理

    return 0;				// ソフトの終了 
}

float smooth(float from, float to, float t) 
{
    
    //n = n * ((middle - ((middle > n ? middle : n) - (middle < n ? middle : n))) / middle);
    float n = ((from > to ? from : to) - (from < to ? from : to)) / (t * 0.5f);
    return n;
}

