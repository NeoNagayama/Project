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
    Retry.SetButtonPosition(VGet(100, 600, 1), VGet(910, 800, 1), VGet(140, 620, 1), VGet(870, 780, 1));
    GameOverToTitle.SetButtonPosition(VGet(1010, 600, 1), VGet(1820, 800, 1), VGet(1050, 620, 1), VGet(1780, 780, 1));
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
    textPositionSet(0, 1920, "Mission Failed", titleFontHandle, SORT_CENTER, 200, true, GetColor(255, 255, 170));
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