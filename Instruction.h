#pragma once
#include "main.h"
#include "Input.h"
#include "Text.h"
#include "Button.h"
class instruction
{
private:
    
    UIText text;
    /* @brief 難易度の説明を表示する用のテキスト */
    UIText info;
    /* @brief 操作説明から次に進めるようになるまでのタイマー */
    timer showTimer;
    /* @brief 難易度ノーマル用のボタン */
    Button normal;
    /* @brief 難易度ハード用のボタン */
    Button hard;
    /* @brief ボタンが押されたか */
    bool pressSpace = false;
    /* @brief 操作説明=0 難易度選択=1 */
    int phase = 0;
    /* @brief 選択中の難易度 ノーマル=0 ハード=1 */
    int dif = 0;
public:
    //ボタンの初期化
    void Init();
    //
    void Update(int scene);
    /* @brief 操作説明 */
    void inst();
    /* @brief 難易度の選択 */
    void choiceDifficulty(int scene);
};
