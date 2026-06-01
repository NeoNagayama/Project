#include "gameOver.h"
#include "DxLib.h"
#include "Button.h"
#include "Input.h"
#include "ui.h"
#include "Text.h"
#include "TitleScene.h"
#include "main.h"
#include "Stage_Endless.h"
/* @brief リトライ用のボタン */
Button Retry;
/* @brief タイトルに戻る用のボタン */
Button GameOverToTitle;
/* @brief ゲームオーバーで表示されるテキスト */
UIText GameOverText;
/* @brief エンドレスモードのハイスコア用のテキスト */
UIText HighScoreText;
/* @brief リトライが選択されたか */
bool isRetrySelected = true;
/* @brief 場面の遷移を始めたか */
bool isSceneChangingFromGameOver = false;
/* @brief ステージ1のポインタ */
stage* G_stage1Instance;
/* @brief ステージ2のポインタ */
stage* G_stage2Instance;
/* @brief ステージ3のポインタ */
stage* G_stage3Instance;
/* @brief エンドレスモードのポインタ */
stageEndless* E_Stage;
void GameOverGetStagePointers(stage* s1, stage* s2, stage* s3 ,stageEndless* s4)
{
    G_stage1Instance = s1;
    G_stage2Instance = s2;
    G_stage3Instance = s3;
    E_Stage = s4;
};
void GameOverSetUp()
{
    //ボタンの位置と使用する画像の設定
    Retry.SetButtonPosition(VGet(500, 700, 1), 800, 200, 0.8f);
    GameOverToTitle.SetButtonPosition(VGet(1410, 700, 1), 800, 200, 0.8f);
    Retry.SetGraph(buttonGraphRed);
    GameOverToTitle.SetGraph(buttonGraphRed);
}
void GameOverMain()
{
    //背景画像の描画
    DrawExtendGraph(-8, 139, 1928, 941, gameOverBackGround, true);
    //ADキーで選択しているボタンを切り替える
    if (Input_GetKeyboardDown(KEY_INPUT_D) && isRetrySelected == true && !isSceneChangingFromGameOver)
    {
        isRetrySelected = false;
        PlaySoundMem(selectSound, DX_PLAYTYPE_BACK, true);
    }
    if (Input_GetKeyboardDown(KEY_INPUT_A) && isRetrySelected == false && !isSceneChangingFromGameOver)
    {
        isRetrySelected = true;
        PlaySoundMem(selectSound, DX_PLAYTYPE_BACK, true);
    }
    //ボタンの処理
    //isRetrySelectedの値によってどちらのボタンが選ばれているかを判断する
    Retry.Main(isRetrySelected, true, 60);
    Retry.SetText("Retry");
    GameOverToTitle.Main(!isRetrySelected, true, 60);
    GameOverToTitle.SetText("Title");
    //テキストの描画
    GameOverText.DrawTextWithSort(0, 1920, "Mission Failed", titleFontHandle, SORT_CENTER, 350, true, GetColor(255, 0, 0));
    //スペースキーが押されたら
    if (Input_GetKeyboardDown(KEY_INPUT_SPACE))
    {
        //場面の遷移を始める
        isSceneChangingFromGameOver = true;
        PlaySoundMem(interectSound, DX_PLAYTYPE_BACK, true);
    }
    //リトライが選ばれずに場面の遷移を始めたら
    if (isSceneChangingFromGameOver && !isRetrySelected)
    {
        //フェードアウトする
        if (fadeout(0.5f))
        {
            //タイトルを初期化する
            Titleinitialize();
            scene = SCENE_TITLE;
            progress = 255;
            StopSoundMem(ingameBgm);
        }
    }
    //リトライを選んで場面の遷移を始めたら
    else if (isSceneChangingFromGameOver && isRetrySelected)
    {
        //フェードアウトする
        if (fadeout(0.5f))
        {
            //各ステージの初期化を行う
            switch (stages)
            {
            case STAGE1:
                G_stage1Instance->Initialize();
                G_stage1Instance->isStarted = true;
                break;
            case STAGE2:
                G_stage2Instance->Initialize();
                G_stage2Instance->isStarted = true;
                break;
            default:
                G_stage3Instance->Initialize();
                G_stage3Instance->isStarted = true;
                break;
            }
            scene = SCENE_INGAME;
            progress = 255;
            StopSoundMem(ingameBgm);
        }
    }
}
void GameOverInitialize()
{
    isRetrySelected = true;
    isSceneChangingFromGameOver = false;
}
void EndlessGameOver(float round)
{
    //背景画像の描画
    DrawExtendGraph(-8, 139, 1928, 941, gameOverBackGround, true);
    //ADキーで選択しているボタンを切り替える
    if (Input_GetKeyboardDown(KEY_INPUT_D) && isRetrySelected == true && !isSceneChangingFromGameOver)
    {
        isRetrySelected = false;
        PlaySoundMem(selectSound, DX_PLAYTYPE_BACK, true);
    }
    if (Input_GetKeyboardDown(KEY_INPUT_A) && isRetrySelected == false && !isSceneChangingFromGameOver)
    {
        isRetrySelected = true;
        PlaySoundMem(selectSound, DX_PLAYTYPE_BACK, true);
    }
    //ボタンの処理
    Retry.Main(isRetrySelected, true, 60);
    Retry.SetText("Retry");
    GameOverToTitle.Main(!isRetrySelected, true, 60);
    GameOverToTitle.SetText("Title");
    //テキストの描画
    GameOverText.DrawTextWithSort(0, 1920, "You Survived %.f Round", titleFontHandle, SORT_CENTER, 350, true, GetColor(255, 255, 0),GetColor(50,50,50),round-1);
    HighScoreText.DrawTextWithSort(0, 1920, "HighScore:%.fRound", fontHandle, SORT_CENTER, 550, true, GetColor(255, 255, 0), GetColor(50, 50, 50),highScore);
    //スペースキーが押されたら
    if (Input_GetKeyboardDown(KEY_INPUT_SPACE))
    {
        //場面の遷移を始める
        isSceneChangingFromGameOver = true;
        PlaySoundMem(interectSound, DX_PLAYTYPE_BACK, true);
        StopSoundMem(ingameBgm);
    }
    //リトライが選ばれずに場面の遷移を始めたら
    if (isSceneChangingFromGameOver && !isRetrySelected)
    {
        //フェードアウトする
        if (fadeout(0.5f))
        {
            //タイトルの初期化
            Titleinitialize();
            scene = SCENE_TITLE;
            progress = 255;
        }
    }
    //リトライを選んで場面の遷移を始めたら
    else if (isSceneChangingFromGameOver && isRetrySelected)
    {
        //フェードアウトする
        if (fadeout(0.5f))
        {
            //ステージの初期化
            E_Stage->Init();
            scene = SCENE_EXTRA;
            progress = 255;
        }
    }
}