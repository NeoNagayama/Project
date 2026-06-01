#include "Instruction.h"
#include "ui.h"
void instruction::Init()
{
    normal.SetGraph(buttonGraph);//難易度ノーマルのボタンの初期化
    normal.SetButtonPosition(VGet(1550, 540, 1), 600, 150, 0.9f);//難易度ノーマルのボタンの位置とサイズの設定
    hard.SetGraph(buttonGraphRed);//難易度ハードのボタンの初期化
    hard.SetButtonPosition(VGet(1550, 740, 1), 600, 150, 0.9f);//難易度ハードの位置とサイズの設定
}
void instruction::main(int scene)
{
    if (Input_GetKeyboardDown(KEY_INPUT_SPACE))//スペースキーが押されたら
    {
        pressSpace = true;//ボタンが押されたかをtrueにする
    }
    switch(phase){
    case 0://phaseが０のとき
        inst();//操作説明を表示する
        break;
    default://phaseが1のとき
        choiceDifficulty(scene);//難易度選択を表示する
        break;
    }
}
void instruction::inst()
{
    SetBackgroundColor(0, 10, 0, 255);//背景色の設定
    DrawGraph(0, 0, instGraph, true);//操作説明の画像を描画
    fadein(0.5f);//フェードインする
    if (showTimer.MeasureTimer(0.5f))//0.5秒たったら
    {
        if (pressSpace)//ボタンが押されたとき
        {
            showTimer.RestartTimer();//タイマーをリセット
            PlaySoundMem(interectSound, DX_PLAYTYPE_BACK, true);//ボタンの効果音を鳴らす
            pressSpace = false;//ボタンが押されたかをfalseに
            phase = 1;//難易度選択を表示する
        }
        //次に進むための操作を表示
        text.DrawTextWithSort(0, 1920, "PRESS SPACE TO START", BiggerFontHandle, SORT_CENTER, 900, FALSE, GetColor(220, 255, 220));
    }
}
void instruction::choiceDifficulty(int scenea)
{
    //難易度選択を画面上部に表示する
    text.DrawTextWithSort(0, 1920, "難易度選択", biggerJpFontHandle, SORT_CENTER, 180, true, GetColor(255, 255, 255));
    normal.Main(dif == 0, true, 30);//ノーマルのボタンを描画
    normal.SetText("NORMAL");//ボタンのテキストを描画
    hard.Main(dif == 1, true, 30);//ハードのボタンを描画
    hard.SetText("HARD");//ボタンのテキスト描画
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
    if (dif == 0)
    {
        info.DrawTextWithSort(90, 1920, "障害物にぶつかっても即死しません\nハードよりもダメージが少なくなっています", biggerJpFontHandle, SORT_LEFT, 800, true, GetColor(255, 255, 255));
    }
    else
    {
        info.DrawTextWithSort(90, 1920, "障害物にぶつかると即死します\n受けるダメージが多くなっています", biggerJpFontHandle, SORT_LEFT, 800, true, GetColor(255, 255, 255));

    }
}