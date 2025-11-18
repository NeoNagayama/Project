#include "Instruction.h"
#include "ui.h"
void instruction::main()
{
    SetBackgroundColor(0, 10, 0, 255);
    DrawGraph(0, 0, instGraph, true);
    fadein(0.5f);
    if (showTimer.MeasureTimer(0.5f))
    {
        if (Input_GetKeyboardDown(KEY_INPUT_SPACE))
        {
            progress = 255;
            scene = SCENE_INGAME;
            showTimer.RestartTimer();
            PlaySoundMem(interectSound, DX_PLAYTYPE_BACK, true);
        }
        text.DrawTextWithSort(0, 1920, "PRESS SPACE TO START", BiggerFontHandle, SORT_CENTER, 900, FALSE, GetColor(220, 255, 220));
    }
}