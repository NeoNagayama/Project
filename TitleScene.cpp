#include "TitleScene.h"
#include "DxLib.h"
#include "Input.h"
#include "Button.h"
#include "fontLoader.h"
#include "main.h"
#include "ui.h"
#include "stage1Scene.h"

void Title::test()
{
    clsDx();
    DrawBox(20, 20, 320, 320, GetColor(255, 255, color), 1);
    printfDx("%d", color);
}
void Title::initialProcess()
{
    Start.SetButtonPosition(VGet(560, 490,1),VGet(1360, 590,1),VGet(610, 505,1),VGet(1310, 575,1));
    Exit.SetButtonPosition(VGet(560, 690, 1), VGet(1360, 790, 1), VGet(610, 705, 1), VGet(1310, 775, 1));
}
void Title::mainProcess()
{
    if (Input_GetKeyboardDown(KEY_INPUT_S)  && isStartSelected == true)
    {
        isStartSelected = false;
    }
    if (Input_GetKeyboardDown(KEY_INPUT_W) && isStartSelected == false)
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
            progress = 255;
            isStarted = true;
            scene = SCENE_STAGE1;
        }
    }
}
