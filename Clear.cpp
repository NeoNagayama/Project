#include "Clear.h"
#include "DxLib.h"
#include "fontLoader.h"
#include "TitleScene.h"
#include "ui.h"
#include "main.h"
Button Next;
Button BackToTitle;
bool isNextSelected = true;
bool isSceneChanging = false;

void ClearInitialProcess()
{
    Next.SetButtonPosition(VGet(100, 600, 1), VGet(910, 800, 1), VGet(140, 620, 1), VGet(870, 780, 1));
    BackToTitle.SetButtonPosition(VGet(1010, 600, 1), VGet(1820, 800, 1), VGet(1050, 620, 1), VGet(1780, 780, 1));
}
void ClearMainProcess()
{
    if (Input_GetKeyboardDown(KEY_INPUT_D) && isNextSelected == true && !isSceneChanging)
    {
        isNextSelected = false;
    }
    if (Input_GetKeyboardDown(KEY_INPUT_A) && isNextSelected == false && !isSceneChanging)
    {
        isNextSelected = true;
    }
    SetBackgroundColor(150, 160, 180, 50);
    Next.mainProcess(isNextSelected, true,60);
    Next.SetText("Next Stage");
    BackToTitle.mainProcess(!isNextSelected, true,60);
    BackToTitle.SetText("Title");
    textPositionSet(0, 1920, "STAGE1 CLEAR", titleFontHandle, SORT_CENTER, 200, true, GetColor(255, 255, 170));
    if (!isNextSelected && Input_GetKeyboardDown(KEY_INPUT_SPACE))
    {
        isSceneChanging = true;
    }
    if (isSceneChanging && !isNextSelected)
    {
        if (fadeout(0.5f))
        {
            Titleinitialize();
            scene = SCENE_TITLE;
            progress = 255;
        }
    }
}
void ClearInitialize()
{
    isSceneChanging = false;
    isNextSelected = true;
}