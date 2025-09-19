#include "TitleScene.h"
#include "DxLib.h"
#include "Input.h"
#include "Button.h"
#include "fontLoader.h"
#include "main.h"
#include "ui.h"
#include "stage1Scene.h"

bool isStartSelected = true;
bool sceneChanging = false;
Button Start;
Button Exit;
void TitleInitialProcess()
{
    Start.SetButtonPosition(VGet(960,545,1),600,100,0.9f);
    Exit.SetButtonPosition(VGet(960, 745, 1), 600, 100, 0.9f);
}
void TitleMainProcess()
{
    if (Input_GetKeyboardDown(KEY_INPUT_S)  && isStartSelected == true && !sceneChanging)
    {
        isStartSelected = false;
    }
    if (Input_GetKeyboardDown(KEY_INPUT_W) && isStartSelected == false && !sceneChanging)
    {
        isStartSelected = true;
    }
    DrawBox(0, 0, 1920, 1080, GetColor(30,30,30),1);
    Start.mainProcess(isStartSelected,true,30);
    Start.SetText("Start");
    Exit.mainProcess(!isStartSelected,true,30);
    Exit.SetText("Exit");
    textPositionSet(0, 1920, "CANYON RUN", titleFontHandle, SORT_CENTER, 200, false, GetColor(255,255,255));
    if (isStartSelected && Input_GetKeyboardDown(KEY_INPUT_SPACE))
    {
        sceneChanging = true;
    }
    if (sceneChanging)
    {
        if (fadeout(0.5f))
        {
            Stage1Initialize();
            progress = 255;
            isStarted = true;
            scene = SCENE_STAGE1;
        }
    }
}
void Titleinitialize()
{
    isStartSelected = true;
    sceneChanging = false;
}
