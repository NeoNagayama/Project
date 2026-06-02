#include "DxLib.h"
float progress = 0;

bool fadeout(float time)
{
    // 一フレーム当たりの変更すべき透明度を求める
    float rate = 255 / (time / 0.016f);
    progress += rate;
    // 画面全体に黒い四角を描画する
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)progress);
    DrawBox(0, 0, 2000, 2000, GetColor(0, 0, 0), true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    // フェードアウトが終わるとtrueを返す
    if (progress >= 255)
    {
        progress = 255;
        return true;
    }
    return false;
}

bool fadein(float time)
{
    // 一フレーム当たりの変更すべき透明度を求める
    float rate = 255 / (time / 0.016f);
    progress -= rate;
    // 画面全体に黒い四角を描画する
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)progress);
    DrawBox(0, 0, 2000, 2000, GetColor(0, 0, 0), true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    // フェードアウトが終わるとtrueを返す
    if (progress <= 0)
    {
        progress = 0;
        return true;
    }
    return false;
}