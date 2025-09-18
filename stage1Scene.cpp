#include "stage1Scene.h"
#include "DxLib.h"
#include "stage1Scene.h"
#include "Input.h"
#include "ui.h"
#include "main.h"
bool isStarted = false;
bool isEnding = false;
void test()
{
    DrawBox(30, 30, 320, 320, GetColor(0, 255, 122), 1);
}
void Stage1MainProcess()
{
    DrawBox(30, 30, 320, 320, GetColor(0, 255, 122), 1);
    if (isStarted)
    {
        if (fadein(0.5f))
        {
            isStarted = false;
        }
    }
    else
    {
        if (Input_GetKeyboardDown(KEY_INPUT_SPACE))
        {
            isEnding = true;
        }
        if (isEnding)
        {
            if(fadeout(1))
            {
                progress = 0;
                scene = SCENE_CLEAR;
            }
        }
    }
    
}