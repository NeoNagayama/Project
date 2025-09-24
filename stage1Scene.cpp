#include "stage1Scene.h"
#include "DxLib.h"
#include "stage1Scene.h"
#include "Input.h"
#include "ui.h"
#include "main.h"
#include "Clear.h"
#include "GameOver.h"
#include "TitleScene.h"
bool isStarted = true;
bool isCleared = false;
bool isDead = false;
bool isPause = false;
bool PauseControllable = true;
bool isRestarting = false;
bool isQuitting = false;
int choosedButton;
Button resume;
Button restart;
Button Stage1ToTitle;
Button Buttons[3];
enum pause
{
    PAUSE_RESUME,
    PAUSE_RESTART,
    PAUSE_EXIT
};
void Stage1InitialProcess()
{
    resume.SetButtonPosition(VGet(960, 540, 1), 400, 100, 0.9f);
    restart.SetButtonPosition(VGet(960, 740, 1), 400, 100, 0.9f);
    Stage1ToTitle.SetButtonPosition(VGet(960, 940, 1), 400, 100, 0.9f);
    Buttons[0] = resume;
    Buttons[1] = restart;
    Buttons[2] = Stage1ToTitle;
    Buttons[0].SetText("Resume");
    Buttons[1].SetText("Restart");
    Buttons[2].SetText("Quit");
}
void Stage1MainProcess()
{
    DrawBox(30, 30, 320, 320, GetColor(0, 255, 122), 1);
    if (isStarted)
    {
        if (fadein(0.5f))
        {
            progress = 0;
            isStarted = false;
        }
    }
    else
    {
        if (!isPause)
        {
            if (Input_GetKeyboardDown(KEY_INPUT_SPACE))
            {
                isCleared = true;
            }
            if (isCleared)
            {
                if (fadeout(1))
                {
                    ClearInitialize();
                    progress = 0;
                    scene = SCENE_CLEAR;
                }
            }
            if (Input_GetKeyboardDown(KEY_INPUT_F))
            {
                isDead = true;
            }
            if (isDead)
            {
                if (fadeout(1))
                {
                    GameOverInitialize();
                    progress = 0;
                    scene = SCENE_GAMEOVER;
                }
            }
        }
        else
        {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
            DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), 1);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
            for (int i = 0; i < 3; i++)
            {
                Buttons[i].mainProcess(choosedButton == i, true, 40);
            }
            switch (choosedButton) {
            case PAUSE_RESUME:
                if (Input_GetKeyboardDown(KEY_INPUT_SPACE))
                {
                    isPause = false;
                    choosedButton = 0;
                }
                break;
            case PAUSE_RESTART:
                if (Input_GetKeyboardDown(KEY_INPUT_SPACE))
                {
                    PauseControllable = false;
                    isRestarting = true;
                }
                break;
            default:
                if (Input_GetKeyboardDown(KEY_INPUT_SPACE))
                {
                    isQuitting = true;
                    PauseControllable = false;
                }
                break;
            }
            if (PauseControllable)
            {
                if (Input_GetKeyboardDown(KEY_INPUT_W) && choosedButton>0)
                {
                     choosedButton--;
                }
                if (Input_GetKeyboardDown(KEY_INPUT_S) && choosedButton < 2)
                {
                    choosedButton++;
                }
            }
            if (isRestarting)
            {
                if(fadeout(0.5f))
                {
                    progress = 255;
                    Stage1Initialize();
                }
            }
            if (isQuitting)
            {
                if (fadeout(0.5f))
                {
                    progress = 255;
                    Titleinitialize();
                    scene = SCENE_TITLE;
                }
            }
        }
        if (Input_GetKeyboardDown(KEY_INPUT_ESCAPE))
        {
            isPause = isPause ? false : true;
            choosedButton = 0;
        }
    }
}
void Stage1Initialize()
{
    isStarted = true;
    isCleared = false;
    isDead = false;
    isPause = false;
    isRestarting = false;
    PauseControllable = true;
    isQuitting = false;
    choosedButton = 0;
}