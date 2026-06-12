#pragma once
#include "main.h"
class smoke
{
private:
    /* @brief 描画する位置 */
    VECTOR Position = zeroVector;
    /* @brief 描画し始めてからどれくらいたったか */
    float progress = 256;
    /* @brief 描画する時間 */
    const float LIFETIME = 3;
public:
    /* @brief 煙のエフェクトを描画する */
    void DrawSmoke();
    /* @brief 描画する位置を設定する */
    void SetPosition(VECTOR pos);
    bool isActive = false;
};