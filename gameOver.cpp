#include "gameOver.h"
#include "DxLib.h"
#include "Button.h"
#include "Input.h"
#include "ui.h"
#include "fontLoader.h"
#include "TitleScene.h"
#include "main.h"
#include "stage1Scene.h"
Button Retry;
Button GameOverToTitle;
bool isRetrySelected = true;
bool isSceneChangingFromGameOver = false;
void GameOverInitialProcess()
{
    Retry.SetButtonPosition(VGet(500, 700, 1), 800, 200, 0.8f);
    GameOverToTitle.SetButtonPosition(VGet(1410, 700, 1), 800, 200, 0.8f);
}
void GameOverMainProcess()
{
    if (Input_GetKeyboardDown(KEY_INPUT_D) && isRetrySelected == true && !isSceneChangingFromGameOver)
    {
        isRetrySelected = false;
    }
    if (Input_GetKeyboardDown(KEY_INPUT_A) && isRetrySelected == false && !isSceneChangingFromGameOver)
    {
        isRetrySelected = true;
    }
    SetBackgroundColor(150, 160, 180, 50);
    Retry.mainProcess(isRetrySelected, true, 60);
    Retry.SetText("Retry");
    GameOverToTitle.mainProcess(!isRetrySelected, true, 60);
    GameOverToTitle.SetText("Title");
    DrawTextWithSort(0, 1920, "Mission Failed", titleFontHandle, SORT_CENTER, 200, true, GetColor(170, 0, 0));
    if (Input_GetKeyboardDown(KEY_INPUT_SPACE))
    {
        isSceneChangingFromGameOver = true;
    }
    if (isSceneChangingFromGameOver && !isRetrySelected)
    {
        if (fadeout(0.5f))
        {
            Titleinitialize();
            scene = SCENE_TITLE;
            progress = 255;
        }
    }
    else if (isSceneChangingFromGameOver && isRetrySelected)
    {
        if (fadeout(0.5f))
        {
            Stage1Initialize();
            scene = SCENE_STAGE1;
            isStarted = true;
            progress = 255;
        }
    }
}
void GameOverInitialize()
{
    isRetrySelected = true;
    isSceneChangingFromGameOver = false;
}