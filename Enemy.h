#pragma once
#include "base.h"
#include "stage1Scene.h"
#include "Bullet.h"
#include "Player.h"
#include "Missile.h"
#include "fontLoader.h"
//回避軌道のenum
enum evadeType
{
    TYPE_BARRELROLL,
    TYPE_HORIZONTAL_FLUCTUATING,
    TYPE_VERTICAL_FLUCTUATING

};
class Player;
class Enemy:public base
{
private:
    //プレイヤーのポインター
    Player* playerObject;
    //左右移動の速度
    float moveSpeed = 0.59f;
    //ロールの速度
    float rotateSpeed = 0.08f;
    //機銃の連射のレート
    float firingRate = 0.2f;
    //機銃の射撃の間隔
    float firingInterval = 2.0f;
    //機銃の到達する位置
    VECTOR vulcanTargetPosition;
    //機銃の弾のクラスの配列
    Bullet bullets[10];
    //画面上に表示されている弾数
    int LoadedAmmoCount;
    //ミサイルのロックするまでの時間
    float missileCooldown = 5.0f;
    //ミサイルが非表示になるまでの時間
    float DespawnTimer = 0.0f;
    //回避軌道の判別のための変数
    int evadetype = 0;
    //回避軌道が何段階目に進んだか
    int evadeCount = 0;
    //バレルロールをする関数
    void barrelRoll();
    //左右に蛇行する関数
    void H_Fluctuating();
    //上下に蛇行する関数
    void V_Fluctuating();
    //位置フレームあたりに上下左右に移動する速度
    float xSpeed = 0.0f, ySpeed = 0.0f;
public:
    //機銃を射撃中かどうか
    bool isFiring = false;
    //ミサイルが発射されたかどうか
    bool isLaunched = false;
    //前回ミサイルが着弾してからどれくらいたったか測る変数
    float missilecooldowntimer = 0.0f;
    //ミサイルが発射されてからの時間を測る変数
    float missileflyingTimer = 0.0f;
    //ミサイルのインスタンス
    Missile missileObject;
    //前回機銃で攻撃してからどれくらいたったか測る変数
    float firingCooldown = 0.0f;
    //機銃が発射されてからどれくらいたったか測る変数
    float firingTimer = 0.0f;
    //敵が移動できる範囲
    float moveRangeX = 10.0f;
    float minimumMoveRangeX = -10.0f;
    float moveRangeY = 10.0f;
    float minimumMoveRangeY = -10.0f;
    //ミサイルの発射に関する処理
    void missile();
    //起動時に呼び出される処理
    void InitialProcess();
    //機銃に関する処理
    void Vulcan();
    //毎フレーム呼ばれる処理
    void mainProcess(bool mode);
    //回避軌道を決定する関数
    void run();
    //進行方向に合わせてロールする関数
    void roll();
    //xy平面上の移動の処理
    void EnemyMoveXY();
    //プレイヤーのポインターを指定する
    void PlayerSet(Player* player)
    {
        playerObject = player;
    }
    //ミサイルが誘導されているか
    bool isGuideLost = false;
    //インゲーム中の遷移の処理
    bool Transition();
    //遷移中のプレイヤーの座標からのz座標のずれ
    float transitionMoveZaxis = -50.0f;
};