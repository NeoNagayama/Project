#include "Clear.h"
#include "DxLib.h"
#include "Text.h"
#include "TitleScene.h"
#include "main.h"
#include "ui.h"
/** @brief 次のステージに進む用のボタン */
Button Next;
/** @brief タイトルに戻る用のボタン */
Button BackToTitle;
/** @brief クリア画面のテキスト */
UIText ClearText;
/** @brief ステージ3クリア画面のテキスト表示時間用のタイマー */
timer TextTimer;
/** @brief 次のステージに進むか */
bool isNextSelected = true;
/** @brief 場面の遷移を始めたか */
bool isSceneChanging = false;
/** @brief メニューを操作可能か */
bool controllable = false;
/** @brief ステージ1のポインタ */
stage *clear_stage1Instance;
/** @brief ステージ2のポインタ */
stage *clear_stage2Instance;
/** @brief ステージ3のポインタ */
stage *clear_stage3Instance;

void ClearGetStagePointers(stage *s1, stage *s2, stage *s3)
{
    // 各ステージのポインタを取得する
    clear_stage1Instance = s1;
    clear_stage2Instance = s2;
    clear_stage3Instance = s3;
};

void ClearSetUp()
{
    // 使用されるボタンの位置と画像の設定
    Next.SetButtonPosition(VGet(500, 500, 1), 800, 200, 0.8f, ANCHOR_LEFT);
    BackToTitle.SetButtonPosition(VGet(500, 800, 1), 800, 200, 0.8f, ANCHOR_LEFT);
    Next.SetGraph(buttonGraph);
    BackToTitle.SetGraph(buttonGraph);
}

void ClearMain()
{
    // メニューを操作可能な時
    if (controllable)
    {
        // WSキーで選択しているボタンを切り替える
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
        // ボタンの処理
        Next.Update(isNextSelected, true, 60);
        Next.SetText("Next Stage");
        BackToTitle.Update(!isNextSelected, true, 60);
        BackToTitle.SetText("Title");
        ClearText.DrawTextWithSort(200, 1920, "STAGE%.f CLEAR", titleFontHandle, SORT_LEFT, 200, true,
                                   GetColor(255, 255, 170), GetColor(50, 50, 50), (float)stages + 1);

        // SPACEキーで場面の遷移を始める
        if (Input_GetKeyboardDown(KEY_INPUT_SPACE))
        {
            isSceneChanging = true;
            PlaySoundMem(interectSound, DX_PLAYTYPE_BACK, true);
        }
    }
    // メニューを操作不能な時
    else
    {
        // フェードインさせて操作可能にする
        if (fadein(0.5f))
        {
            controllable = true;
            progress = 0;
        }
    }

    // タイトルに戻るが選択された時
    if (isSceneChanging && !isNextSelected)
    {
        // フェードアウトする
        if (fadeout(0.5f))
        {
            // タイトルに戻る処理
            Titleinitialize();
            scene = SCENE_TITLE;
            progress = 255;
            StopSoundMem(ingameBgm);
        }
    }
    // 次のステージに進むが選択された時
    else if (isNextSelected && isSceneChanging)
    {
        // フェードアウトする
        if (fadeout(0.5f))
        {
            stages += 1;

            // 次に進むステージ別に初期化する
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
            StopSoundMem(ingameBgm);
        }
    }
}

void ClearStage3()
{
    ClearText.DrawTextWithSort(200, 1920, "ALL STAGES CLEARED", titleFontHandle, SORT_LEFT, 200, true,
                               GetColor(255, 255, 170), GetColor(50, 50, 50));

    // テキストを4秒表示したら場面の遷移を始める
    if (TextTimer.MeasureTimer(4.0f))
    {
        isSceneChanging = true;
    }

    // 場面の遷移を始めたら
    if (isSceneChanging)
    {

        // フェードアウトが終わったら
        if (fadeout(0.5f))
        {
            // タイトル画面の初期化
            stages = 0;
            Titleinitialize();
            scene = SCENE_TITLE;
            progress = 255;
            StopSoundMem(ingameBgm);
            TextTimer.RestartTimer();
        }
    }
}

void ClearInitialize()
{
    // 各変数の初期化
    isSceneChanging = false;
    isNextSelected = true;
    controllable = false;
}