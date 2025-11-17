#include "Clear.h"
#include "DxLib.h"
#include "Text.h"
#include "TitleScene.h"
#include "ui.h"
#include "main.h"
Button Next;
Button BackToTitle;
UIText ClearText;
bool isNextSelected = true;
bool isSceneChanging = false;
bool controllable = false;
 stage* clear_stage1Instance;
 stage* clear_stage2Instance;
 stage* clear_stage3Instance;
 void ClearGetStagePointers(stage* s1, stage* s2, stage* s3)
 {
     clear_stage1Instance = s1;
     clear_stage2Instance = s2;
     clear_stage3Instance = s3;
 };
void ClearInitialProcess()
{
    Next.SetButtonPosition(VGet(500, 500, 1), 800, 200, 0.8f);
    BackToTitle.SetButtonPosition(VGet(500, 800, 1), 800, 200, 0.8f);
}
void ClearMainProcess()
{
    
    if (controllable)
    {

        if (Input_GetKeyboardDown(KEY_INPUT_S) && isNextSelected == true && !isSceneChanging)
        {
            isNextSelected = false;
            PlaySoundMem(selectSound, DX_PLAYTYPE_BACK, true);
        }
        if (Input_GetKeyboardDown(KEY_INPUT_W) && isNextSelected == false && !isSceneChanging)
        {
            isNextSelected = true;
            PlaySoundMem(selectSound, DX_PLAYTYPE_BACK, true);
        }
        Next.mainProcess(isNextSelected, true, 60);
        Next.SetText("Next Stage");
        BackToTitle.mainProcess(!isNextSelected, true, 60);
        BackToTitle.SetText("Title");
        ClearText.DrawTextWithSort(200, 1920, "STAGE%d CLEAR", titleFontHandle, SORT_LEFT, 200, true, GetColor(255, 255, 170), GetColor(50, 50, 50), stages + 1);
        if (Input_GetKeyboardDown(KEY_INPUT_SPACE))
        {
            isSceneChanging = true;
            PlaySoundMem(interectSound, DX_PLAYTYPE_BACK, true);
            StopSoundMem(ingameBgm);
        }

        
    }
    else
    {
        if (fadein(0.5f))
        {
            controllable = true;
            progress = 0;
        }
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
    else if (isNextSelected && isSceneChanging)
    {
        if (fadeout(0.5f))
        {
            stages += 1;
            switch (stages)
            {
            case STAGE2:
                clear_stage2Instance->Initialize();
                break;
            default:
                clear_stage3Instance->Initialize();
                break;
            }
            scene = SCENE_INGAME;
            progress = 255;
        }
    }
}
void ClearInitialize()
{
    isSceneChanging = false;
    isNextSelected = true;
    controllable = false;
}