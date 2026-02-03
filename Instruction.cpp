#include "Instruction.h"
#include "ui.h"
void instruction::Init()
{
    normal.init(buttonGraph);
    normal.SetButtonPosition(VGet(960, 540, 1), 400, 100, 0.9f);
    hard.init(buttonGraph);
    hard.SetButtonPosition(VGet(960, 740, 1), 400, 100, 0.9f);
}
void instruction::main(int scene)
{
    if (Input_GetKeyboardDown(KEY_INPUT_SPACE))
    {
        pressSpace = true;
    }
    switch(phase){
    case 0:
        inst();
        break;
    default:
        choiceDifficulty(scene);
        break;
    }
}
void instruction::inst()
{
    SetBackgroundColor(0, 10, 0, 255);
    DrawGraph(0, 0, instGraph, true);
    fadein(0.5f);
    if (showTimer.MeasureTimer(0.5f))
    {
        if (pressSpace)
        {
            showTimer.RestartTimer();
            PlaySoundMem(interectSound, DX_PLAYTYPE_BACK, true);
            pressSpace = false;
            phase = 1;
        }
        text.DrawTextWithSort(0, 1920, "PRESS SPACE TO START", BiggerFontHandle, SORT_CENTER, 900, FALSE, GetColor(220, 255, 220));
    }
}
void instruction::choiceDifficulty(int scenea)
{
    normal.mainProcess(dif == 0, true, 30);
    normal.SetText("NORMAL");
    hard.mainProcess(dif == 1, true, 30);
    hard.SetText("HARD");
    if (Input_GetKeyboardDown(KEY_INPUT_S) || Input_GetKeyboardDown(KEY_INPUT_W))
    {
        dif = dif == 0 ? 1 : 0;
    }
    if (pressSpace)
    {
        difficulty = dif;
        progress = 255;
        scene = scenea;
        pressSpace = false;
        phase = 0;
    }
}