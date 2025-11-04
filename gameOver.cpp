#include "gameOver.h"
#include "DxLib.h"
#include "Button.h"
#include "Input.h"
#include "ui.h"
#include "Text.h"
#include "TitleScene.h"
#include "main.h"
Button Retry;
Button GameOverToTitle;
UIText GameOverText;
bool isRetrySelected = true;
bool isSceneChangingFromGameOver = false;
stage* G_stage1Instance;
stage* G_stage2Instance;
stage* G_stage3Instance;
void GameOverGetStagePointers(stage* s1, stage* s2, stage* s3)
{
    G_stage1Instance = s1;
    G_stage2Instance = s2;
    G_stage3Instance = s3;
};
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
    GameOverText.DrawTextWithSort(0, 1920, "Mission Failed", titleFontHandle, SORT_CENTER, 200, true, GetColor(170, 0, 0));
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
            switch (stages)
            {
            case STAGE1:
                G_stage1Instance->Initialize();
                G_stage1Instance->isStarted = true;
                break;
            case STAGE2:
                G_stage2Instance->Initialize();
                G_stage2Instance->isStarted = true;
                break;
            default:
                G_stage3Instance->Initialize();
                G_stage3Instance->isStarted = true;
                break;
            }
            scene = SCENE_STAGE1;
            progress = 255;
        }
    }
}
void GameOverInitialize()
{
    isRetrySelected = true;
    isSceneChangingFromGameOver = false;
}