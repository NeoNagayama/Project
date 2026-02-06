#include "Instruction.h"
#include "ui.h"
void instruction::Init()
{
    normal.init(buttonGraph);
    normal.SetButtonPosition(VGet(1500, 540, 1), 400, 100, 0.9f,ANCHOR_RIGHT);
    hard.init(buttonGraphRed);
    hard.SetButtonPosition(VGet(1500, 740, 1), 400, 100, 0.9f, ANCHOR_RIGHT);
}
void instruction::main(int nextScene)
{
    DrawGraph(0, 0, instBackGraph, true);
    if (Input_GetKeyboardDown(KEY_INPUT_SPACE))
    {
        pressSpace = true;
    }
    switch(phase){
    case 0:
        inst();
        break;
    default:
        choiceDifficulty(nextScene);
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
void instruction::choiceDifficulty(int nextScene)
{
    text.DrawTextWithSort(0, 1920, "難易度選択", biggerJpFontHandle, SORT_CENTER, 200, true, GetColor(255, 255, 255),GetColor(10,10,10));
    if (dif == 0)
    {
        info.DrawTextWithSort(90, 1920, "おすすめ", biggerJpFontHandle, SORT_LEFT, 600, true, GetColor(255, 255, 255), GetColor(10, 10, 10));
    }
    else
    {
        info.DrawTextWithSort(90, 1920, "ノーマルに比べダメージが大きくなり\n壁にぶつかると即ゲームオーバー", biggerJpFontHandle, SORT_LEFT, 600, true, GetColor(255, 255, 255), GetColor(10, 10, 10));
    }
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
        scene = nextScene;
        pressSpace = false;
        phase = 0;
    }
}