#pragma once
#include "main.h"
class explosionEffect
{
private:
    /* @brief 描画位置 */
    VECTOR BasePosition = zeroVector;
    /* @brief 追加のエフェクトの描画位置 */
    VECTOR Position1 = zeroVector;
    VECTOR Position2 = zeroVector;
    VECTOR Position3 = zeroVector;
    /* @brief 追加のエフェクトの拡散の方向 */
    VECTOR Direction1 = VNorm(VGet(3,1,0));
    VECTOR Direction2 = VNorm(VGet(-3,-4, 0));
    VECTOR Direction3 = VNorm(VGet(-6, -1, 0));
    /* @brief 描画した時間 */
    float progress = 256;
    /* @brief 追加のエフェクトのサイズ */
    float subExplSize = 0.7f;
    /* @brief メインのエフェクトのサイズ */
    float size = 0;
    /* @brief 追加のエフェクトの回転の角度 */
    float angle = 0;
    /* @brief 描画する時間 */
    const float LIFETIME = 3;
    /* @brief  */
    VECTOR MovePosition(VECTOR pos, VECTOR dir);
    /* @brief 追加のエフェクトの描画 */
    void DrawSubExpl(VECTOR pos, VECTOR dir);
public:
    /* @brief エフェクトの描画処理 */
    void DrawExprosion();
    /* @brief メインのエフェクトのみを描画 */
    bool DrawSingleExplosion();
    /* @brief エフェクトの位置を決める */
    void SetPosition(VECTOR pos);
    
};