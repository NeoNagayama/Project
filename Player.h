#pragma once
#include"DxLib.h"
#include "base.h"
#include"Input.h"
#include "bullet.h"
#include "Flare.h"
#include "Enemy.h"
#include "Text.h"
#include "VisualEffects.h"
class Enemy;
class explosionEffect;
/**
 * @brief プレイヤーのクラス
 * @details インゲームのプレイヤーの処理を行うクラス
 *
 * @author 永山音峰
 */
class Player: public base
{
private:
    /* @brief 機銃の残弾数を表示するテキスト */
    UIText VulcanText;
    /* @brief フレアの使用可能までの時間を表示するテキスト */
    UIText FlareText;
    /* @brief 爆発エフェクト */
    explosionEffect exp;
    explosionEffect exp2;
    /* @brief 敵のポインタ */
    Enemy* enemyObject;
    /* @brief 操作していないときの上方向 */
    static constexpr float NEUTRAL_ANGLE_Y = 0.99f;
    /* @brief 逃走フェーズ中のカメラの注視点のz軸方向のプレイヤーの座標からのずれ */
    static constexpr int TARGET_CAMERA_POSZ = 20;
    /* @brief 上下左右の移動速度の倍率 */
    static constexpr float moveSpeed= 0.4f;
    /* @brief 上下左右の移動速度の上限 */
    float speedLimit = 0.7f;
    /* @brief 上下左右の移動できる範囲 */
    static constexpr float moveRange = 11;
    /* @brief ロールの回転の速度 */
    static constexpr float rotateSpeed = 0.08f;
    /* @brief 入力で直接変化させる上下左右の移動速度 */
    float x, y = 0;
    /* @brief ピッチ方向の向くべく角度 */
    VECTOR targetAnglePitch;
    /* @brief 50フレーム分の弾の発射位置 */
    float bulletPositionX[50] = { 0 };
    float bulletPositionY[50] = { 0 };
    //機銃とフレア用の変数
    /* @brief 前回機銃が発射されてから経過した時間 */
    float firingTimer = 0;
    /* @brief 開始演出時のカメラの座標のマップ中央からのずれ */
    float startCameraOffsetx = 6;
    /* @brief カメラがプレイヤーの後ろについて移動し始める座標 */
    float cameraStartThleshold = 0;
    /* @brief フレアを使用してから経過した時間を計測する変数 */
    float FlareCoolDown = 0;
    /* @brief フレアが発射されてから経過した時間 */
    float FlareFiringTimer = 0;
    /* @brief カメラのズームの倍率 */
    float cameraZoom = 0.6f;
    /* @brief カメラの注視点のz座標 */
    float target = 0;
    /* @brief 機銃の発射の間隔 */
    static constexpr float firingRate = 0.07f;
    /* @brief フレアの発射の間隔 */
    static constexpr float FlareFiringRate = 0.1f;
    /* @brief フレアのクールダウンの時間 */
    static constexpr float FlareInterval = 5;
    /* @brief フレアを射出中かどうか */
    bool Launching = false;
    /* @brief 発射するフレアの数 */
    int FlareAmount = 10;
    /* @brief 機銃の最大の弾数 */
    static constexpr int maxAmmo = 200;
    /* @brief 機銃の弾の配列 */
    Bullet bullets[200];
    /* @brief フレアの配列 */
    Flare Flares[10];
    /* @brief 無敵時間計測用のタイマー */
    timer ImmortalTimer;
    /* @brief 無敵時の点滅用のタイマー */
    timer stroboTimer;
    /**
     * @brief  入力処理
     * @details プレイヤーの入力と反映
     */
    void KeyInput();
    /*
     * @brief プレイヤーのxy平面上の移動処理
     * @details プレイヤーの移動する座標を変数に入れ
     *          移動できる範囲から出ないようにする
     */
    void PlayerMoveXY();
    /*
     * @brief フレア射出時の処理
     * @details フレアの射出の間隔やインスタンス別に射出されたときの最初の処理を行う
     */
    void FlareLaunch();
    /*
     * @brief 機銃の弾の処理
     * @details 機銃の弾の移動,当たり判定等の処理を行う
     */
    void VulcanProjectile();
    /*
     * @brief 上方向に移動しているときの処理
     * @details 上方向に移動する操作をしているときの処理
     * 
     * @param[in] float speed 一フレーム当たりに移動速度を変化させる値
     */
    void InputUp(float speed);
    /*
     * @brief 下方向に移動しているときの処理
     * @details 下方向に移動する操作をしているときの処理
     *
     * @param[in] float speed 一フレーム当たりに移動速度を変化させる値
     */
    void InputDown(float speed);
    /*
     * @brief 操作していないときの処理
     * @details WSキー,ADキー,WASDキーそれぞれの操作していないときの処理
     *
     * @param float speed 1フレーム当たりの速度を減少させる値
     */
    void InputNeutral(float speed);
    /*
     * @brief プレイヤーのロールのみの処理
     * @details プレイヤーの回転処理からピッチに関するものを排除した関数
     */
    void rotateOnlyRoll();
    /*
     * @brief 移動速度が上限を超えないようにする
     * @details x軸y軸それぞれの移動速度が制限を超えると
     *          上限内に戻す
     */
    void Limit();
    /**
     * @brief 無敵時間の処理
     * @details 無敵時間の計測とモデルの表示非表示の切り替え
     */
    void Immortal();
public:
    /* @brief プレイヤーの移動速度の初期値 */
    static constexpr float DEFAULTSPEED = 2;
    /* @brief 機銃の残弾数 */
    float ammo = 200;
    /* @brief プレイヤーの移動速度 */
    float forwardSpeed = 2;
    /* @brief 死亡したか */
    bool isDead = false;
    /* @brief プレイヤーの後方に配置するライトのハンドル */
    int tailLight;
    /* @brief 無敵時間中か */
    bool isImmortal = false;
    /* @brief カメラの座標 */
    VECTOR CameraPosition = zeroVector;
    /**
     * @brief 起動時に1度だけ呼び出される処理
     * @details モデルのロード,初期座標の設定,モデルのスケール等の処理を行う
     */
    void Start();
    /*
     * @brief フレアの処理
     * @details フレアのクールダウン,UIの表示の処理を行う
     */
    void Flare();
    /*
     * @brief プレイヤーの機銃関連の処理
     * @details プレイヤーの機銃の残弾表示,照準の表示,弾の処理
     */
    void Vulcan();
    /**
     * @brief プレイヤーの毎フレーム呼ばれる処理
     * @details プレイヤーの毎フレーム呼ばれる処理
     *
     * @param bool mode ゲームが追跡フェーズに入っているか
     */
    void Update(bool mode);
    /*
     * @brief プレイヤーの回転
     * @details 操作しているキーやtargetAngleの数値をもとに
     *          機体を回転させ回転すべきピッチ方向の角度を出す
     */
    void rotatePlayer();
    void pitch();
    /**
     * @brief ゲームのフェーズが切り替わるときの演出
     * @details ゲームのフェーズが切り替わるときの演出のカメラやプレイヤーの処理
     *
     * @param bool mode 開始時の演出でない時はtrue
     *                  開始時の演出の時はfalse
     */
    void transitionProcess(bool mode);
    /**
     * @brief  クリア時の処理
     * @details クリア時のプレイヤーの移動と回転に関する処理
     */
    void clearProcess();
    /**
     * @brief  障害物をよける処理
     * @details 演出中に障害物に当たらないようにするためにステージの中央に移動する
     */
    void autoEvade();
    /**
     * @brief  敵のポインタを取得する
     * @details 敵のポインタを取得する
     * @param[in] Enemy* enemy 敵のポインタ
     */
    void EnemySet(Enemy* enemy)
    {
        enemyObject = enemy;
    }
    /**
     * @brief 逃走フェーズに遷移するときの演出
     * @details 演出中のカメラの移動の処理
     */
    bool Transition();
    /**
     * @brief プレイヤーの初期化
     * @details 座標や体力等の変数を初期値に戻す
     */
    void Init();
    /**
     * @brief 変数をゲーム開始時のカメラ演出用の数値に変更する
     * @details ゲーム開始時のカメラ演出に関連する変数の値を
     *          変更しゲーム開始時以外にもカメラの演出を行えるようにする
     *
     * @param int pos カメラ演出開始時のプレイヤーの座標
     *
     */
    void camSetUp(float pos);
};