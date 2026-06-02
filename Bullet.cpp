#include "Bullet.h"

bool Bullet::Main(VECTOR hitbox1, VECTOR hitbox2)
{
    // 正面方向に移動する
    Position = VAdd(Position, VScale(VGet(forward.x, -forward.y, forward.z * timeScale), 1));
    // モデルの移動と描画
    MV1SetPosition(handle, Position);
    MV1DrawModel(handle);
    // 目標よりも前に飛んだら処理をやめる
    if (Position.z >= target.z)
    {
        isActivated = false;
    }
    // 引数のヒットボックスに入るとtrueを返して処理をやめる
    if (Position.x > hitbox1.x && Position.y > hitbox1.y && Position.z > hitbox1.z && Position.x < hitbox2.x &&
        Position.y < hitbox2.y && Position.z < hitbox2.z)
    {
        isActivated = false;
        return true;
    }
    return false;
}

void Bullet::setUp()
{
    handle = MV1DuplicateModel(bulletHandle);
    MV1SetRotationXYZ(handle, VGet(0, 0, 45.0f * DX_PI_F / 180.0f));
}