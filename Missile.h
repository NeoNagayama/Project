#pragma once
#include "Base.h"
#include "main.h"
#include "Trail.h"
class smoke;
class Missile :public base
{
private:
    /* @brief ミサイルの正面方向 */
	VECTOR Angle = VGet(0,0,1);
    /* @brief ミサイルのモデルのハンドル */
    int MissileHandle = 0;
    /* @brief 煙のエフェクトの配列 */
    smoke smokes[180];
    /* @brief そのフレームで新しく描画する煙のエフェクトの番号 */
    int smokeNum = 0;
public:
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
	void Main(VECTOR targetPosition, float remainingTime,float speed);
    /**
 * @brief ミサイルの開始地点を設定する
 * @details ミサイルの座標を引数の座標に設定する
 *
 * @param[in] VECTOR StartPosition ミサイルの移動を始める位置を設定する
 *
 * @note 基本的にミサイルを発射した敵の座標を引数に入れる
 *       ミサイルを発射した時のみ呼び出す
 */
	void SetStartPosition(VECTOR StartPosition);
    /**
 * @brief ミサイルが誘導をやめたときの処理
 * @details ミサイルが誘導をやめた後本来プレイヤーに当たっている時間までの処理
 */
	void guideLosted();
    /**
 * @brief ミサイルのモデルのロード
 * @details ミサイルのモデルのロードとマテリアルの設定
 */
    void SetUp();
    /**
 * @brief 煙の描画の処理
 * @details 煙のエフェクトの描画
 * @note ミサイルが当たった後に不自然に煙がすべて消えないように呼び出し続ける必要があるため
 *       この処理はほかのミサイル関連の処理とは別に毎フレーム呼び出す
 */
    void Passive();
};