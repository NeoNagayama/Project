#include "Trail.h"

void smoke::DrawSmoke()
{
    
    if (progress > LIFETIME) // 描画する時間を超えたら
    {
        isActive = false;
        return; // 描画する処理を行わずに終わる
    }
    if (Position.z > GetCameraPosition().z)
    {
        progress += oneFlame; // 描画した時間に一フレーム分の秒数を足す
        float alpha = (255 * (1 - progress / LIFETIME));
        SetDrawBlendMode(DX_BLENDMODE_ALPHA,(int)alpha); // 表示された時間に応じて透過度を上げる
        DrawBillboard3D(Position, 0.5f, 0.5f, 0.8f, progress, smokeHandle, true); // 煙のエフェクト用の画像を描画する
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);                                // 透過をやめる
    }
    return;
}

void smoke::SetPosition(VECTOR pos)
{
    Position = pos; // 描画する位置に引数のposを入れる
    progress = 0;   // 描画した時間をリセットする
    isActive = true;
}