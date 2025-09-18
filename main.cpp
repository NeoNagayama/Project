#include "DxLib.h"
#include "TitleScene.h"
#include "stage1Scene.h"
#include "Input.h"
#include"gameOver.h"
#include "Clear.h"
#include "fontLoader.h"
#include "main.h"
int scene = 0;
// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    SetGraphMode(1920, 1080, 32) ,ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
    //SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_MAXIMUM);
    //奥行0.1～1000までをカメラの描画範囲とする
    SetCameraNearFar(0.1f, 1000.0f);
    SetUseLighting(true);
    COLOR_F col = { 1,1,1,1 };
    enum SCENES
    {
        SCENE_TITLE,
        SCENE_STAGE1,
        SCENE_GAMEOVER,
        SCENE_CLEAR
    };
    Stage1 stage;
    gameOver gameover;
    Clear clear;
    Title title;
    fontLoad();
    SetGlobalAmbientLight(GetColorF(1,0,0,1));
    //(0,10,-20)の視点から(0,10,0)のターゲットを見る角度にカメラを設置
    SetCameraPositionAndTarget_UpVecY(VGet(0, 0, -20), VGet(0.0f, 0.0f, 0.0f));
    title.initialProcess();
    while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {
        Input_UpdateKeyboard();
        switch (scene) {
        case SCENE_STAGE1:
           
            stage.test();
                break;
        case SCENE_GAMEOVER:
            gameover.test();
            break;
        case SCENE_CLEAR:
            clear.test();
            break;
        default:
            title.test();
            title.mainProcess();
        }
        WaitTimer(16);
    }

    DxLib_End();				// ＤＸライブラリ使用の終了処理

    return 0;				// ソフトの終了 
}

