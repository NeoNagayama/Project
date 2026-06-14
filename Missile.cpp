#include "Missile.h"

void Missile::SpawnSmoke()
{
    if (smokeInterval > 0)
    {
        smokeInterval--;
        return;
    }

    smokes[smokeNum].SetPosition(Position);
    smokeNum++;
    hasActiveSmoke = true;
    smokeInterval = SMOKE_SPAWN_INTERVAL;

    if (smokeNum >= MISSILE_SMOKE_COUNT)
    {
        smokeNum = 0;
    }
}

/**
 * @brief ミサイルの主要な処理
 * @details 移動とモデル、エフェクトの描画
 *
 * @param[in] VECTOR targetPosition 目標のプレイヤーの位置
 * @param[in] float remainingTime ミサイルがプレイヤーに当たるまでの残り時間
 * @param[in] float speed 敵とプレイヤーの進行速度
 *
 * @note 残り時間が0になると同時にプレイヤーの位置に到達するように速度を計算している
 *       ミサイルを飛ばしてから着弾するまでは毎フレーム呼び出す必要がある
 *
 */
void Missile::Main(VECTOR targetPosition, float remainingTime, float speed)
{
    remainingTime = remainingTime / 0.016f;
    Angle =
        VScale(VNorm(VGet(targetPosition.x - Position.x, targetPosition.y - Position.y, targetPosition.z - Position.z)),
               (speed + 0.3f) * timeScale);
    Position = VAdd(Position, Angle);
    MV1SetPosition(MissileHandle, Position);
    MV1SetRotationXYZ(MissileHandle, VNorm(VGet(targetPosition.x - Position.x, targetPosition.y - Position.y,
                                                targetPosition.z - Position.z)));
    MV1DrawModel(MissileHandle);
    DrawBillboard3D(VAdd(VScale(MV1GetRotationXYZ(MissileHandle), -2.6f), Position), 0.5f, 0.49f, 4, 0,
                    missileBurnerHandle, true);
    SpawnSmoke();
}

/**
 * @brief ミサイルの開始地点を設定する
 * @details ミサイルの座標を引数の座標に設定する
 *
 * @param[in] VECTOR StartPosition ミサイルの移動を始める位置を設定する
 *
 * @note 基本的にミサイルを発射した敵の座標を引数に入れる
 *       ミサイルを発射した時のみ呼び出す
 */
void Missile::SetStartPosition(VECTOR StartPosition)
{
    Position = StartPosition;
}

/**
 * @brief ミサイルが誘導をやめたときの処理
 * @details ミサイルが誘導をやめた後本来プレイヤーに当たっている時間までの処理
 */
void Missile::guideLosted()
{
    Position = VAdd(Position, Angle);
    MV1SetPosition(MissileHandle, Position);
    MV1DrawModel(MissileHandle);
    SpawnSmoke();
}

/**
 * @brief ミサイルのモデルのロード
 * @details ミサイルのモデルのロードとマテリアルの設定
 */
void Missile::SetUp()
{
    MissileHandle = MV1LoadModel("Resource/MissileModel.mv1");
    for (int i = 0; i < MV1GetMaterialNum(MissileHandle); i++)
    {
        MV1SetMaterialDifColor(MissileHandle, i, GetColorF(0.7f, 0.7f, 0.7f, 1.0f));
        MV1SetMaterialAmbColor(MissileHandle, i, GetColorF(0.2f, 0.2f, 0.2f, 1.0f));
        MV1SetMaterialSpcColor(MissileHandle, i, GetColorF(0.4f, 0.4f, 0.4f, 1));
        MV1SetMaterialEmiColor(MissileHandle, i, GetColorF(0.8f, 0.8f, 0.8f, 0.2f));
        MV1SetMaterialSpcPower(MissileHandle, i, 6);
    }
}

/**
 * @brief 煙の描画の処理
 * @details 煙のエフェクトの描画
 * @note ミサイルが当たった後に不自然に煙がすべて消えないように呼び出し続ける必要があるため
 *       この処理はほかのミサイル関連の処理とは別に毎フレーム呼び出す
 */
void Missile::Passive(float cameraZ)
{
    if (!hasActiveSmoke)
    {
        return;
    }

    bool anyActive = false;
    for (int i = 0; i < MISSILE_SMOKE_COUNT; i++)
    {
        if (smokes[i].isActive)
        {
            smokes[i].DrawSmoke(cameraZ);
            anyActive = true;
        }
    }
    hasActiveSmoke = anyActive;
}
