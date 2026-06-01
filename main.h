#pragma once
#include "DxLib.h"
/** @brief  円周率*/
#define PI 3.14159265359f
/** @brief  一フレーム当たりの秒数*/
#define oneFlame 0.016f
extern VECTOR zeroVector;
/** @brief 現在のゲームの場面
           これの数値を変えることでゲームの場面が変わる */
extern int scene;
/** @brief 現在プレイ中のステージ
           これの数値を変えることでステージが変わる*/
extern int stages;
/** @brief  シャドウマップ用のハンドル*/
extern int shadowHandle;
/** @brief  タイトル画面のシャドウマップ用のハンドル*/
extern int titleShadowHandle;
/** @brief  照準用の画像ファイルのハンドル*/
extern int reticleHandle;
/** @brief  残弾数表示用のゲージの画像ハンドル*/
extern int reticleInsideGaugeHandle;
/** @brief  背景画像ファイルのハンドル*/
extern int backGroundHandle;
/** @brief  移動する障害物用のハンドル*/
extern int cargoModelOrigin;
/** @brief  弾のハンドル*/
extern int bulletHandle;
/** @brief  敵の弾のハンドル*/
extern int enemyBulletHandle;
/** @brief  空母のハンドル*/
extern int carrierHandle;
/** @brief  上下に配置される障害物のハンドル*/
extern int horizontalObstacleHandle;
/** @brief  ミサイルの火の画像ファイルのハンドル*/
extern int missileBurnerHandle;
/** @brief  ミサイルの煙の画像ファイルのハンドル*/
extern int smokeHandle;
/** @brief  爆発の画像ファイルのハンドル*/
extern int explosionHandle;
/** @brief  ステージ左右に配置される壁のハンドル*/
extern int wallHandle;
/** @brief  移動する障害物の経路の画像ファイルのハンドル*/
extern int guideHandle;
/** @brief  ゲーム全体の時間経過の速度*/
extern float timeScale;
/** @brief  操作説明の画像ファイルのハンドル*/
extern int instGraph;
/** @brief  スペースキーの画像*/
extern int spaceGraph;
extern int buttonGraph;
extern int buttonGraphRed;
extern int menuBackground;
extern int gameOverBackGround;
extern int uiBox_01;
extern int uiBox_02;
extern int uiBox_03;
extern int playerHealthGauge;
extern int playerHealthBar;
/** @brief  ミサイルの警告の画像*/
extern int alertGraph;
/** @brief  クリアまでの距離を表示するゲージのハンドル*/
extern int gaugeHandle;
/** @brief  プレイヤーの進行度を表示するバーのハンドル*/
extern int barHandle;
/** @brief  敵の体力ゲージのメモリ*/
extern int E_gauge;
/** @brief  敵の体力ゲージの値*/
extern int E_bar;
/** @brief  エンドレスモードのハイスコア*/
extern float highScore;
/** @brief  決定した時の効果音*/
extern int interectSound;
/** @brief  選択した時の効果音*/
extern int selectSound;
/** @brief  ミサイルロック時の警報*/
extern int missileAlertSound;
/** @brief  ミサイルロック時の二段階目の警報*/
extern int pitbullSound;
/** @brief  プレイヤーの射撃音*/
extern int flareSound;
/** @brief  プレイヤーの射撃音*/
extern int playerShotSound;
/** @brief  敵の射撃音*/
extern int enemyShotSound;
/** @brief  敵がプレイヤーを追い越した時の効果音*/
extern int frybySound;
/** @brief  機体のエンジン音*/
extern int engineSound;
/** @brief  被弾時の効果音*/
extern int hitSound;
/** @brief  爆発の効果音*/
extern int explosionSound;
/** @brief  戦闘中のbgm*/
extern int ingameBgm;
/** @brief  タイトル画面のbgm*/
extern int titleBgm;
/** @brief  プレイヤーのライトハンドル*/
extern int playerLight;
/** @brief  敵のライトハンドル*/
extern int enemyLight;
/** @brief  左右に配置される障害物のハンドル*/
extern int sideObstacle;
/** @brief  プレイヤーがダメージを受けたか*/
extern bool isGetDamaged;
extern int difficulty;
extern float shakeScale;
/** @brief 画面識別用のenum */
enum SCENES
{
    SCENE_TITLE,        //タイトル画面
    SCENE_INGAME,       //インゲーム
    SCENE_INSTRUCTION,  //操作説明画面
    SCENE_STAGEBUILD,   //ステージ制作画面
    SCENE_EXTRA,        //エンドレスモード画面
    SCENE_INST_EX
};
/** @brief ステージのenum */
enum STAGES
{
    STAGE1,             //ステージ1
    STAGE2,             //ステージ2
    STAGE3              //ステージ3
};

/**
 * @brief 特定の値から別の値まで一定時間かけて増やすときの一フレーム当たりの増やすべき値を返す
 * @details 二つの引数から差を出して目標のフレーム数で割った値を返す
 *
 * @param[in] float from 元の値
 * @param[in] float to 目標の値
 * @param[in] float t 何フレームで目標の値に到達させるか
 *
 * @return float 一フレーム当たりに増やすべき値
 *
 * @note fromとtoが逆でも動作する
 *       fromとtoの内大きいほうの値から小さいほうの値を引いて差を求めるので
 *       減らすべき値を出せない
 */
extern float smooth(float min, float max, float n);
/**
 * @brief 二つのVECTORの距離を求める
 * @details 座標として使用しているVECTOR型を引数に入れ、
 *          距離を割り出す
 *
 * @param[in] VECTOR from 一つ目の座標
 * @param[in] VECTOR to 二つ目の座標
 *
 * @return float 二つの座標間の距離
 */
extern float VectorLength(VECTOR from, VECTOR to);
/**
 * @brief 二つのVECTORの角度を求めて単位化する
 * @details 引数に二つのVECTOR型の変数を渡して一つ目のベクトルから二つ目のベクトルまでの方向を出して
 *          単位化する
 *
 * @param[in] VECTOR to 方向を求めたいベクトル　
 * @param[in]  VECTOR from 元のベクトル
 *
 * @return VECTOR 単位化された方向を表す
 */
extern VECTOR VectorDirectionNormalize(VECTOR v1, VECTOR v2);
/**
 * @brief　乱数を取得する
 * @details　最大値と最小値を指定して乱数を取得する
 *
 * @param[in] int min 最小値
 * @param[in] int max 最大値
 *
 * @return int 取得した乱数
 */
extern int get_rand(int min, int max);
/** @brief  ゲームを終了するか*/
extern bool Quit;
/**
 * @brief 時間を計測するクラス
 * @details このクラスは時間の計測と
 *          経過時間を取得します
 *
 * @author 永山音峰
 *
 * 使用例：
 * @code
 *  timer time
 *  int count = 0
 *  float target = 2.5f;
 *  time.Elapsed = 0;
 *  if(time.MeasureTime(target))
 *  {
 *      time.Elapsed = 0;
 *      count++;
 *  }
 *
 * @endcode
 */
class timer
{
private:
    /** @brief 経過した時間を入れる変数 */
    float Elapsed = 0;
public:
    /**
    * @brief 指定した時間が経過したかどうかを返す
    * @details 引数で指定した時間が経過したら真
    *          経過していなければ偽を返す
    *
    * @param float time 測る時間を入れる
    *
    * @return bool 引数で入れた時間に達したら真、
    *              そうでなければ偽
    *
    * @note 関数内に経過した時間を測る分があるので
    *       毎フレーム呼び出さないと正しく動作しません
    */

    bool MeasureTimer(float time)
    {
        //一フレーム当たりの秒数を経過した時間に足す
        Elapsed += oneFlame;
        //引数の秒数よりも大きくなったら
        if (Elapsed > time)
        {
            //trueを返す
            return true;
        }
        //falseを返す
        return false;
    }
    /**
    * @brief 経過した時間を返す
    * @details 経過した秒数を返す
    *
    * @param bool mode 毎フレーム一フレーム当たりの秒数を足す処理を行うか
    *
    * @return float 経過した時間を秒数で返す
    *
    * @note MeasureTimer関数と併用するときは
    *       引数のmodeをfalseにする
    */
    float GetElapsed(bool mode = false)
    {
        //modeがfalseの時
        if (mode)
        {
            //経過した時間を返す
            return Elapsed;
        }
        //経過した時間に1フレーム当たりの秒数を足して返す
        return Elapsed += oneFlame;
    }
    /**
    * @brief 経過した時間を初期化する
    * @details Elapsed変数を0にする
    */
    void RestartTimer()
    {
        //経過した時間を0にする
        Elapsed = 0;
    }
};
/**
 * @brief ゲームに使用されるアセットをロードする
 * @details ゲームに使用される画像,音声素材,3dモデル,フォントをロードする
 *          Resourceフォルダに格納されている
 *
 */
void LoadAssets();
/**
 * @brief シャドウマップを設定する
 * @details シャドウマップを作成して影の方向を設定する
 *
 */
void setupShadowMap();
/**
 * @brief 一括で初期化処理を行う
 * @details
 */
void Init();
/**
 * @brief ステージ2の障害物の配置をロードする
 * @details ステージ2の障害物の配置が記録されているバイナリファイルを読み取り
 *          配列に入れる
 */
void LoadStage1();
/**
 * @brief ステージ2の障害物の配置をロードする
 * @details ステージ2の障害物の配置が記録されているバイナリファイルを読み取り
 *          配列に入れる
 */
void LoadStage2();
/**
 * @brief ステージ3の障害物の配置をロードする
 * @details ステージ3の障害物の配置が記録されているバイナリファイルを読み取り
 *          配列に入れる
 */
void LoadStage3();
/**
 * @brief エンドレスモードのハイスコアをロードする
 * @details エンドレスモードのハイスコアが記録されたバイナリファイルを読み取り
 *          変数highScoreに入れる
 */
void LoadScore();
/**
 * @brief 効果音の音量を調整する
 * @details ロードした効果音の音量を調整する
 */
void setVolume();
/**
 * @brief カメラを揺らす
 * @details カメラの座標を1フレームだけずらして視界を揺らす
 */
void CameraShake();