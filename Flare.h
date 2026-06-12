#pragma once
#include "DxLib.h"
#include "Trail.h"
class smoke;

constexpr int INTERBAL_FRAME = 3;

class Flare
{
  private:
    /* @brief フレアの描画時間を計る変数 */
    float timer = 0;
    /* @brief 煙のエフェクトの配列 */
    smoke smokes[60];
    /* @brief そのフレームで新しく描画する煙のエフェクトの番号 */
    int smokeNum = 0;

    int interbal = INTERBAL_FRAME;

  public:
    /* @brief フレアを描画するか */
    bool isActivated = false;
    /* @brief フレアを移動させる方向 */
    VECTOR forward = zeroVector;
    /* @brief フレアを描画させる座標 */
    VECTOR position = zeroVector;
    /**
     * @brief フレアの主要な処理
     * @details 移動と描画
     * @note フレアの移動方向と初期座標を設定する分は含まれていないので
     *       プレイヤーのスクリプトに用意する必要がある
     */
    void Main();
    /**
     * @brief 煙の描画の処理
     * @details 煙のエフェクトの描画
     * @note フレアの描画を終えた後に不自然に煙がすべて消えないように呼び出し続ける必要があるため
     *       この処理はほかのミサイル関連の処理とは別に毎フレーム呼び出す
     */
    void Passive();
};