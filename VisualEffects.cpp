#include "VisualEffects.h"
void explosionEffect::DrawExprosion()
{
    
    angle += 0.02f;//追加のエフェクトを回転する
    progress += oneFlame;//描画した時間に一フレーム分の秒数を足す
    size += 20 * oneFlame;//サイズを毎フレーム増やす
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * (1 - progress / LIFETIME)));//描画した時間に応じて透過度を上げる
    DrawBillboard3D(BasePosition, 0.5f, 0.5f, size, progress, explosionHandle, TRUE);//メインの爆発エフェクトを描画する
    //追加のエフェクトを描画する
    DrawSubExpl(Position1, Direction1);
    DrawSubExpl(Position2, Direction2);
    DrawSubExpl(Position3, Direction3);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//透過をやめる
}
bool explosionEffect::DrawSingleExplosion()
{
    progress += oneFlame * timeScale;//描画した時間に一フレーム分の秒数を足す
    size += (20 * oneFlame) * timeScale;//サイズを毎フレーム増やす
    SetWriteZBuffer3D(FALSE);//ｚバッファの書き込みをやめる
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * (1 - progress / (LIFETIME-1.5f))));//描画した時間に応じて透過度を上げる
    DrawBillboard3D(BasePosition, 0.5f, 0.5f, size, progress, explosionHandle, TRUE);//メインの爆発エフェクトを描画する
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);;//透過をやめる
    SetWriteZBuffer3D(TRUE);//ｚバッファの書き込みをやめる
    return (progress > LIFETIME ? true : false);//描画する時間を超えたらtrueを返す
}
void explosionEffect::SetPosition(VECTOR pos)
{
    size = 2;//サイズをリセットする
    progress = 0;//経過した時間をリセットする
    BasePosition = pos;//描画する位置に引数posを入れる
    //追加のエフェクトに描画する位置を入れる
    Position1 = BasePosition;
    Position2 = BasePosition;
    Position3 = BasePosition;
    //角度をリセットする
    angle = 0;
}
VECTOR explosionEffect::MovePosition(VECTOR pos ,VECTOR dir)
{
    return VAdd(pos, VScale(dir,3));
}
void explosionEffect::DrawSubExpl(VECTOR pos,VECTOR dir)
{
    pos = MovePosition(pos, dir);//描画位置を拡散する方向にずらした座標を入れる
    DrawBillboard3D(pos, 0.5f, 0.5f, size * subExplSize, angle, explosionHandle, TRUE);//描画する
}