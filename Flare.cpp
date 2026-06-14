#include "Flare.h"

/**
 * @brief フレアの主要な処理
 * @details 移動と描画
 * @note フレアの移動方向と初期座標を設定する分は含まれていないので
 *       プレイヤーのスクリプトに用意する必要がある
 */
void Flare::Main()
{
    timer += oneFlame;
    // 煙の位置の設定
    if (interbal < 0)
    {
        smokes[smokeNum].SetPosition(position);
        smokeNum++;
        hasActiveSmoke = true;
        interbal = INTERBAL_FRAME;
    }
    else
    {
        interbal--;
    }
    // フレアを移動させる
    position = VAdd(position, forward);
    DrawBillboard3D(position, 0.5f, 0.5f, 10, 0, missileBurnerHandle, true);
    // 描画し始めてから4秒たつと描画をやめる
    if (timer > 4)
    {
        isActivated = false;
        timer = 0;
    }
    if (smokeNum >= FLARE_SMOKE_COUNT)
    {
        smokeNum = 0;
    }
}

/**
 * @brief 煙の描画の処理
 * @details 煙のエフェクトの描画
 * @note フレアの描画を終えた後に不自然に煙がすべて消えないように呼び出し続ける必要があるため
 *       この処理はほかのミサイル関連の処理とは別に毎フレーム呼び出す
 */
void Flare::Passive(float cameraZ)
{
    if (!hasActiveSmoke)
    {
        return;
    }

    bool anyActive = false;
    for (int i = 0; i < FLARE_SMOKE_COUNT; i++)
    {
        if (smokes[i].isActive)
        {
            smokes[i].DrawSmoke(cameraZ);
            anyActive = true;
        }
    }
    hasActiveSmoke = anyActive;
}