#include "Instruction.h"
#include "ui.h"
void instruction::main()
{
    SetBackgroundColor(0, 10, 0, 255);
    DrawGraph(0, 0, instGraph, true);
    fadein(0.5f);
    if (showTimer.MeasureTimer(5))
    {
        progress = 255;
        scene = SCENE_INGAME;
        showTimer.RestartTimer();
    }
}