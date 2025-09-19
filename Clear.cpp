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
    Next.SetButtonPosition(VGet(500, 700, 1), 800, 200, 0.8f);
    BackToTitle.SetButtonPosition(VGet(1410, 700, 1), 800, 200, 0.8f);
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