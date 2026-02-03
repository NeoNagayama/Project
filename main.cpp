#include "DxLib.h"
#include "TitleScene.h"
#include "Stage.h"
#include "Input.h"
#include"gameOver.h"
#include "Clear.h"
#include "Text.h"
#include "main.h"
#include "Player.h"
#include "Instruction.h"
#include "StageBuild.h"
#include "Stage_Endless.h"
#include <random>

/** @brief 現在のゲームの場面 */
int scene = 0;
/** @brief 現在プレイ中のステージ */
int stages =0;
/** @brief  照準用の画像ファイルのハンドル*/
int reticleHandle = 0;
/** @brief  シャドウマップ用のハンドル*/
int shadowHandle;
/** @brief  タイトル画面のシャドウマップ用のハンドル*/
int titleShadowHandle;
/** @brief  背景画像ファイルのハンドル*/
int backGroundHandle;
/** @brief  残弾数表示用のゲージの画像ハンドル*/
int reticleInsideGaugeHandle;
/** @brief  移動する障害物用のハンドル*/
int cargoModelOrigin;
/** @brief  弾のハンドル*/
int bulletHandle;
/** @brief  敵の弾のハンドル*/
int enemyBulletHandle;
/** @brief  空母のハンドル*/
int carrierHandle;
/** @brief  上下に配置される障害物のハンドル*/
int horizontalObstacleHandle;
/** @brief  ミサイルの火の画像ファイルのハンドル*/
int missileBurnerHandle;
/** @brief  ミサイルの煙の画像ファイルのハンドル*/
int smokeHandle;
/** @brief  爆発の画像ファイルのハンドル*/
int explosionHandle;
/** @brief  ステージ左右に配置される壁のハンドル*/
int wallHandle;
/** @brief  移動する障害物の経路の画像ファイルのハンドル*/
int guideHandle;
/** @brief  操作説明の画像ファイルのハンドル*/
int instGraph;
/** @brief  スペースキーの画像*/
int spaceGraph;
int buttonGraph;
int buttonGraphRed;
int menuBackground;
int gameOverBackGround;
int uiBox_01;
int uiBox_02;
int uiBox_03;
int playerHealthGauge;
int playerHealthBar;
/** @brief  ミサイルの警告の画像*/
int alertGraph;
/** @brief  クリアまでの距離を表示するゲージのハンドル*/
int gaugeHandle;
/** @brief  プレイヤーの進行度を表示するバーのハンドル*/
int barHandle;
/** @brief  敵の体力ゲージのメモリ*/
int E_gauge;
/** @brief  敵の体力ゲージの値*/
int E_bar;
/** @brief  エンドレスモードのハイスコア*/
int highScore;
/** @brief  決定した時の効果音*/
int interectSound;
/** @brief  選択した時の効果音*/
int selectSound;
/** @brief  ミサイルロック時の警報*/
int missileAlertSound;
/** @brief  ミサイルロック時の二段階目の警報*/
int pitbullSound;
/** @brief  フレア射出の効果音*/
int flareSound;
/** @brief  プレイヤーの射撃音*/
int playerShotSound;
/** @brief  敵の射撃音*/
int enemyShotSound;
/** @brief  敵がプレイヤーを追い越した時の効果音*/
int frybySound;
/** @brief  機体のエンジン音*/
int engineSound;
/** @brief  被弾時の効果音*/
int hitSound;
/** @brief  爆発の効果音*/
int explosionSound;
/** @brief  戦闘中のbgm*/
int ingameBgm;
/** @brief  タイトル画面のbgm*/
int titleBgm;
/** @brief  プレイヤーのライトハンドル*/
int playerLight;
/** @brief  敵のライトハンドル*/
int enemyLight;
/** @brief  左右に配置される障害物のハンドル*/
int sideObstacle;
/** @brief  プレイヤーがダメージを受けたか*/
bool isGetDamaged;
/** @brief  ゲーム全体の時間経過の速度*/
float timeScale = 1;
/** @brief  ゲームを終了するか*/
bool Quit = false;
int isSucceceed = 0;
int difficulty = 0;
/** @brief  ステージ1の障害物の位置*/
int stage1Obstacle[50] = {
    0,0,0,0,0,
    3,4,3,0,0,
    2,3,4,8,0,
    0,0,9,0,10,
    0,1,3,5,10,
    0,0,0,0,0,
    3,4,3,0,0,
    2,3,4,8,0,
    0,0,9,0,10,
    0,1,3,5,10
};
/** @brief  ステージ1の障害物の種類*/
int stage1ObstacleType[50] = {
        0,0,0,0,0,
        3,3,3,0,0,
        1,1,1,1,0,
        0,0,3,0,3,
        0,1,1,1,1,
        0,0,0,0,0,
        3,3,3,0,0,
        1,1,1,1,0,
        0,0,3,0,3,
        0,1,1,1,1
};
/** @brief  ステージ2の障害物の位置*/
int stage2Obstacle[50] = {
    0,0,0,0,0,
    1,0,6,3,7,
    4,5,5,8,9,
    8,9,0,0,0,
    6,8,6,8,0,
    0,10,10,5,5,
    0,0,0,2,2,
    8,8,2,2,9,
    9,3,3,2,9,
    2,9,0,0,0
};
/** @brief  ステージ2の障害物の種類*/
int stage2ObstacleType[50] = {
    0,0,0,0,0,
    1,1,1,1,1,
    1,1,1,1,1,
    1,1,0,0,0,
    3,3,1,1,0,
    0,3,1,3,1,
    0,0,0,3,3,
    3,3,1,1,1,
    1,3,3,1,1,
    1,1,0,0,0
};
/** @brief  ステージ3の障害物の位置*/
int stage3Obstacle[50] = {
    0,0,0,0,0,
    1,1,6,6,7,
    7,5,5,8,9,
    8,9,0,0,0,
    6,8,6,8,0,
    0,10,10,5,5,
    0,0,0,2,2,
    8,8,2,2,9,
    9,3,3,2,9,
    2,9,0,0,0
};
/** @brief  ステージ3の障害物の種類*/
int stage3ObstacleType[50] = {
    0,0,0,0,0,
    1,1,1,1,1,
    1,1,1,1,1,
    1,1,0,0,0,
    3,3,1,1,0,
    0,3,1,3,1,
    0,0,0,3,3,
    3,3,1,1,1,
    1,3,3,1,1,
    1,1,0,0,0
};
/** @brief  ステージ3の移動する障害物の位置*/
int stage3movewall[50];
/** @brief  ステージ1の移動する障害物の位置*/
int stage1movewall[50] = {
        3,1,5,3,2,
        1,4,5,2,1,
        1,3,5,2,3,
        1,5,1,2,4,
        1,5,3,2,4,
        1,2,3,4,5,
        0,1,2,3,4,
        5,0,1,2,3,
        4,5,0,1,2,
        3,4,5,0,1
};
/** @brief ステージ2の移動する障害物の位置 */
int stage2movewall[50] = {
        3,1,5,3,2,
        1,4,5,2,1,
        1,3,5,2,3,
        1,5,1,2,4,
        1,5,3,2,4,
        1,2,3,4,5,
        0,1,2,3,4,
        5,0,1,2,3,
        4,5,0,1,2,
        3,4,5,0,1
};

/** @brief  stage型のstage1を宣言*/
stage stage1;
/** @brief  stage型のstage2を宣言*/
stage stage2;
/** @brief  stage型のstage3を宣言*/
stage stage3;
/** @brief  stageEndless型のendlessを宣言*/
stageEndless endless;
/** @brief  instruction型のinstを宣言*/
instruction inst;
/** @brief  builder型のbilを宣言*/
builder bil;

/** @brief  ゲーム全体に使用されるディレクショナルライトのハンドル*/
int DirectionalLightHandle;
// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    SetGraphMode(1920, 1080, 32) ,ChangeWindowMode(false), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
    //SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_MAXIMUM);
    //奥行0.1～1000までをカメラの描画範囲とする
    SetCameraNearFar(0.1f, 5000.0f);
    //ライティング処理を行う
    SetUseLighting(TRUE);
    //ライトを有効にする
    SetLightEnable(TRUE);
    //Zバッファを有効にする
    SetUseZBuffer3D(TRUE);
    //Zバッファに書き込み始める
    SetWriteZBuffer3D(TRUE);
    //
    SetUseTransColorGraphCreateFlag(TRUE);


    //(0,0,-20)の視点から(0,0,0)のターゲットを見る角度にカメラを設置
    SetCameraPositionAndTarget_UpVecY(VGet(0, 0, -20), VGet(0.0f, 0.0f, 0.0f));
    //使用される素材を読み込む
    LoadAssets();
    //音声素材の音量を変更する
    setVolume();
    //シャドウマップを使用するための処理
    setupShadowMap();
    //初期化
    Init();
    //Materialのパラメーターの宣言
    MATERIALPARAM Material;
    //ディフューズカラーの設定
    Material.Diffuse = GetColorF(0.2f, 0.2f, 0.2f, 0.2f);
    //アンビエントカラーの設定の設定
    Material.Ambient = GetColorF(0.2f, 0.2f, 0.24f, 0.1f);
    //スぺキュラカラーの設定
    Material.Specular = GetColorF(0.2f, 0.2f, 0.2f, 0.2f);
    //エミッシブカラーの設定
    Material.Emissive = GetColorF(0.1f, 0.1f, 0.1f, 0.0f);
    //スペキュラの強さの設定
    Material.Power = 0.1f;
    //使用されるマテリアルのパラメーターを設定する
    SetMaterialParam(Material);
    //ディレクショナルライトのハンドルを生成する
    DirectionalLightHandle = CreateDirLightHandle(VGet(0, 0.7f, -0.3f));
    //生成したライトを有効にする
    SetLightEnableHandle(DirectionalLightHandle, true);
    //ライトのディフューズカラーとスぺキュラカラーを設定する
    SetLightDifColorHandle(DirectionalLightHandle, GetColorF(0.8f, 0.8f, 0.8f, 0.4f));
    SetLightSpcColorHandle(DirectionalLightHandle, GetColorF(0.4f, 0.4f, 0.4f, 0.4f));
    //敵と自機の後方に配置されるライトのハンドルを生成する
    enemyLight = CreatePointLightHandle(VGet(0,0,0), 5, 0.1f, 0.1f, 0.1f);
    playerLight = CreatePointLightHandle(VGet(0, 0, 0), 5, 0.1f, 0.1f, 0.1f);
    //敵と自機のライトの各種カラーの設定をする
    SetLightDifColorHandle(enemyLight, GetColorF(1, 0.3f, 0, 1));
    SetLightSpcColorHandle(enemyLight, GetColorF(1, 0.3f, 0, 1));
    SetLightAmbColorHandle(enemyLight, GetColorF(1, 0.3f, 0, 1));
    SetLightDifColorHandle(playerLight, GetColorF(0, 0.3f, 1, 1));
    SetLightSpcColorHandle(playerLight, GetColorF(0, 0.3f, 1, 1));
    SetLightAmbColorHandle(playerLight, GetColorF(0, 0.3f, 1, 1));
    SetFogEnable(TRUE);					// フォグを有効にする
    SetFogColor(150, 160, 181);			// フォグの色にする
    SetFogStartEnd(600.0f, 800.0f);	// フォグの開始距離
    /*毎フレーム呼ばれる処理
      Bool型のQuitがTrueになると
      while文を抜けてゲームを終了する*/
    while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !Quit) {
        //キーボード操作がされているか判断する処理
        Input_UpdateKeyboard();

        //場面の切り替え
        switch (scene) {
            //場面別の毎フレーム呼ばれる処理
            //インゲーム中の処理
        case SCENE_INGAME:
            //bgmが流れていなければ再生する
            if (CheckSoundMem(ingameBgm) == 0)
            {
                PlaySoundMem(ingameBgm, DX_PLAYTYPE_LOOP);
            }
            //変数stagesの値に応じて処理を行うステージのインスタンスを変更する
            switch (stages)
            {
            case STAGE1:
                stage1.MainProcess();
                break;
            case STAGE2:
                stage2.MainProcess();
                break;
            case STAGE3:
                stage3.MainProcess();
                break;
            }
            break;
            //操作説明画面の処理
        case SCENE_INSTRUCTION:
            //操作説明画面のインスタンスのメインの処理
            inst.main(SCENE_INGAME);
            //操作説明終了後に処理を行う各ステージのインスタンスの初期化
            stage1.Initialize();
            stage2.Initialize();
            stage3.Initialize();
            //インゲームのbgmの再生を止める
            StopSoundMem(ingameBgm);
            break;
            //ステージ制作を行う時の処理
        case SCENE_STAGEBUILD:
            //ステージ制作画面の主要な処理
            bil.main();
            //インゲームのbgmを止める
            StopSoundMem(ingameBgm);
            break;
            //エンドレスモードの処理
        case SCENE_EXTRA:
            endless.main();
            //bgmが流れていなければ再生する
            if (CheckSoundMem(ingameBgm) == 0)
            {
                PlaySoundMem(ingameBgm, DX_PLAYTYPE_LOOP);
            }
            break;
            //タイトル画面の処理
        default:
            //背景の描画
            DrawGraph3D(0, 600,  1800, backGroundHandle, false);
            //タイトル画面の主要な処理
            TitleMainProcess();
            //インゲームのbgmを止める
            StopSoundMem(ingameBgm);
            break;
        }
        //ダメージを受けたらカメラの振動の処理を呼び出す
        if (isGetDamaged)
        {
            CameraShake();
        }
        //60fpsの1フレーム分待機する
        WaitTimer(16);
        //セットしたシャドウマップを解除する
        SetUseShadowMap(0, -1);
        
    }
    //使用したシャドウマップを削除する
    DeleteShadowMap(shadowHandle);
    DeleteShadowMap(titleShadowHandle);
    DxLib_End();
    return 0;				// ソフトの終了 
}
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

float smooth(float from, float to, float t) 
{
    float n = ((from > to ? from : to) - (from < to ? from : to)) / (t * 0.5f);
    return n;
}
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

float VectorLength(VECTOR from, VECTOR to)
{
    VECTOR difference = VGet(to.x - from.x, to.y - from.y, to.z - from.z);
    return sqrtf((difference.x * difference.x) + (difference.y * difference.y) + (difference.z * difference.z));
}
/**
 * @brief　乱数を取得する
 * @details　最大値と最小値を指定して乱数を取得する
 *
 * @param[in] int min 最小値
 * @param[in] int max 最大値
 *
 * @return int 取得した乱数
 */

int  get_rand(int min, int max)
{
    static std::mt19937 mt(0);
    std::uniform_int_distribution<int> get_rand_uni_int(min, max);
    return get_rand_uni_int(mt);
}
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
VECTOR VectorDirectionNormalize(VECTOR to, VECTOR from)
{
    return VNorm(VGet(from.x - to.x, from.y - to.y, from.z - to.z));
}
/**
 * @brief ゲームに使用されるアセットをロードする
 * @details ゲームに使用される画像,音声素材,3dモデル,フォントをロードする
 *          Resourceフォルダに格納されている
 *
 */

void LoadAssets()
{
    carrierHandle = MV1LoadModel("Resource/AircraftCarrier.mv1");
    reticleHandle = LoadGraph("Resource/Reticle.png", false);
    reticleInsideGaugeHandle = LoadGraph("Resource/ReticleInsideGauge.png", false);
    backGroundHandle = LoadGraph("Resource/backGround.jpg");
    bulletHandle = MV1LoadModel("Resource/bullet.mv1");
    enemyBulletHandle = MV1LoadModel("Resource/bullet.mv1");
    cargoModelOrigin = MV1LoadModel("Resource/cargo.mv1");
    horizontalObstacleHandle = MV1LoadModel("Resource/LowerObstacle.mv1");
    missileBurnerHandle = LoadGraph("Resource/missileBurner.png");
    smokeHandle = LoadGraph("Resource/smoke1.png");
    explosionHandle = LoadGraph("Resource/explosion.png");
    wallHandle = MV1LoadModel("Resource/wall.mv1");
    guideHandle = LoadGraph("Resource/guideBeacon.png");
    instGraph = LoadGraph("Resource/Instruction.png");
    spaceGraph = LoadGraph("Resource/Space.png");
    buttonGraph = LoadGraph("Resource/Buttons/ButtonLarge.png");
    buttonGraphRed = LoadGraph("Resource/Buttons/ButtonLargeRed.png");
    menuBackground = LoadGraph("Resource/Buttons/Back.png");
    gameOverBackGround = LoadGraph("Resource/Buttons/Back2.png");
    uiBox_01 = LoadGraph("Resource/Buttons/Box_01.png");
    uiBox_02 = LoadGraph("Resource/Buttons/Box_02.png");
    uiBox_03 = LoadGraph("Resource/Buttons/Box_03.png");
    playerHealthGauge = LoadGraph("Resource/Buttons/gauge.png");
    playerHealthBar = LoadGraph("Resource/Buttons/bar.png");
    alertGraph = LoadGraph("Resource/MissileAlert.png");
    gaugeHandle = LoadGraph("Resource/ProgressGauge.png");
    barHandle = LoadGraph("Resource/ProgressBar.png");
    E_bar = LoadGraph("Resource/EnemyBar.png");
    E_gauge = LoadGraph("Resource/EnemyGauge.png");
    interectSound = LoadSoundMem("Resource/sfx/interect2.mp3");
    selectSound = LoadSoundMem("Resource/sfx/interect.mp3");
    missileAlertSound = LoadSoundMem("Resource/sfx/alert.mp3");
    pitbullSound = LoadSoundMem("Resource/sfx/pitbull.mp3");
    flareSound = LoadSoundMem("Resource/sfx/flare.mp3");
    playerShotSound = LoadSoundMem("Resource/sfx/shot2.mp3");
    enemyShotSound = LoadSoundMem("Resource/sfx/enemyShot.mp3");
    frybySound = LoadSoundMem("Resource/sfx/flyby.mp3");
    engineSound = LoadSoundMem("Resource/sfx/playerEngine.mp3");
    hitSound = LoadSoundMem("Resource/sfx/hit.mp3");
    explosionSound = LoadSoundMem("Resource/sfx/explosion.mp3");
    ingameBgm = LoadSoundMem("Resource/sfx/ingame.mp3");
    titleBgm = LoadSoundMem("Resource/sfx/title.mp3");
    sideObstacle = MV1LoadModel("Resource/sideObstacle.mv1");
    fontLoad();
}
/**
 * @brief シャドウマップを設定する
 * @details シャドウマップを作成して影の方向を設定する
 *
 */

void setupShadowMap()
{
    //インゲームのシャドウマップを作成
    shadowHandle = MakeShadowMap(4096, 4096);
    //タイトル画面のシャドウマップを作成
    titleShadowHandle = MakeShadowMap(4096, 4096);
    //インゲームとタイトルのシャドウマップ用のライトの方向を設定
    SetShadowMapLightDirection(shadowHandle, VGet(0, -0.7f, 0.3f));
    SetShadowMapLightDirection(titleShadowHandle, VGet(0.1f, -0.7f, 0.5f));
}
/**
 * @brief 一括で初期化処理を行う
 * @details 
 */

void Init()
{
    inst.Init();
    //タイトル画面で最初に一度だけ呼ばれる処理 
    TitleInitialProcess();
    //各ステージの障害物の配置をロードする
    LoadStage1();
    LoadStage2();
    LoadStage3();
    LoadScore();
    //各ステージの初期化
    stage1.InitialProcess(stage1Obstacle, stage1ObstacleType,stage1movewall);
    stage2.InitialProcess(stage2Obstacle, stage2ObstacleType, stage2movewall);
    stage3.InitialProcess(stage3Obstacle, stage3ObstacleType, stage3movewall);
    //ステージ制作画面の初期化 ステージクラスの初期化と同じ内容
    bil.InitialProcess(stage2Obstacle, stage2ObstacleType, stage2movewall);
    //クリア画面で最初に一度だけ呼ばれる処理
    ClearInitialProcess();
    //ゲームオーバー画面で最初に一度だけ呼ばれる処理
    GameOverInitialProcess();
    //各ステージのインスタンスのポインターを指定する
    getStagePointers(&stage1, &stage2, &stage3,&endless);
    GameOverGetStagePointers(&stage1, &stage2, &stage3,&endless);
    ClearGetStagePointers(&stage1, &stage2, &stage3);
    //ステージ制作画面特有の要素の初期化
    bil.Init();
    //エンドレスモードの一度だけ呼ばれる処理
    endless.SetUp();
    //エンドレスモードの初期化
    endless.Init();
}
/**
 * @brief ステージ3の障害物の配置をロードする
 * @details ステージ3の障害物の配置が記録されているバイナリファイルを読み取り
 *          配列に入れる
 */
void LoadStage3()
{
    /** @brief  開いたファイルを入れるポインタ*/
/** @brief  障害物の種類のファイル*/
    FILE* file;

    /** @brief  障害物の配置のファイル*/
    FILE* file1;
    /** @brief  移動する障害物の配置のファイル*/
    FILE* file2;
    /** @brief  障害物の種類のファイルを開いたときにステータスを入れる*/
    errno_t err;
    /** @brief  障害物の配置のファイルを開いたときにステータスを入れる*/
    errno_t err1;
    /** @brief  移動する障害物の配置のファイルを開いたときにステータスを入れる*/
    errno_t err2;
    //各ファイルを開いて対応するポインタに入れる
    err = fopen_s(&file, "maps/defaultMaps/stage3type.dat", "rb");
    err1 = fopen_s(&file1, "maps/defaultMaps/stage3obs.dat", "rb");
    err2 = fopen_s(&file2, "maps/defaultMaps/stage3wall.dat", "rb");
    //各ファイルを開いたときにエラーが起きていなかったら
    if (err == 0 || err1 == 0 || err2 == 0)
    {
        //ステージ3関連の配列の値をゼロにする
        for (int i = 0; i < 50; i++)
        {
            stage3Obstacle[i] = 0;
            stage3ObstacleType[i] = 0;
            stage3movewall[i] = 0;
        }
        //開いたファイルを読み値を配列に入れる
        fread(stage3ObstacleType, sizeof(int), 50, file);
        fread(stage3Obstacle, sizeof(int), 50, file1);
        fread(stage3movewall, sizeof(int), 50, file2);
        //ファイルを閉じる
        fclose(file);
        fclose(file1);
        fclose(file2);
    }
}
/**
 * @brief ステージ2の障害物の配置をロードする
 * @details ステージ2の障害物の配置が記録されているバイナリファイルを読み取り
 *          配列に入れる
 */
void LoadStage2()
{
    /** @brief  開いたファイルを入れるポインタ*/
/** @brief  障害物の種類のファイル*/
    FILE* file;

    /** @brief  障害物の配置のファイル*/
    FILE* file1;
    /** @brief  移動する障害物の配置のファイル*/
    FILE* file2;
    /** @brief  障害物の種類のファイルを開いたときにステータスを入れる*/
    errno_t err;
    /** @brief  障害物の配置のファイルを開いたときにステータスを入れる*/
    errno_t err1;
    /** @brief  移動する障害物の配置のファイルを開いたときにステータスを入れる*/
    errno_t err2;
    //各ファイルを開いて対応するポインタに入れる
    err = fopen_s(&file, "maps/defaultMaps/stage2type.dat", "rb");
    err1 = fopen_s(&file1, "maps/defaultMaps/stage2obs.dat", "rb");
    err2 = fopen_s(&file2, "maps/defaultMaps/stage2wall.dat", "rb");
    //各ファイルを開いたときにエラーが起きていなかったら
    if (err == 0 || err1 == 0 || err2 == 0)
    {
        //ステージ3関連の配列の値をゼロにする
        for (int i = 0; i < 50; i++)
        {
            stage2Obstacle[i] = 0;
            stage2ObstacleType[i] = 0;
            stage2movewall[i] = 0;
        }
        //開いたファイルを読み値を配列に入れる
        fread(stage2ObstacleType, sizeof(int), 50, file);
        fread(stage2Obstacle, sizeof(int), 50, file1);
        fread(stage2movewall, sizeof(int), 50, file2);
        //ファイルを閉じる
        fclose(file);
        fclose(file1);
        fclose(file2);
    }
}
/**
 * @brief ステージ2の障害物の配置をロードする
 * @details ステージ2の障害物の配置が記録されているバイナリファイルを読み取り
 *          配列に入れる
 */
void LoadStage1()
{
    /** @brief  開いたファイルを入れるポインタ*/
/** @brief  障害物の種類のファイル*/
    FILE* file;
    /** @brief  障害物の配置のファイル*/
    FILE* file1;
    /** @brief  移動する障害物の配置のファイル*/
    FILE* file2;
    /** @brief  障害物の種類のファイルを開いたときにステータスを入れる*/
    errno_t err;
    /** @brief  障害物の配置のファイルを開いたときにステータスを入れる*/
    errno_t err1;
    /** @brief  移動する障害物の配置のファイルを開いたときにステータスを入れる*/
    errno_t err2;
    //
    err = fopen_s(&file, "maps/defaultMaps/stage1type.dat", "rb");
    err1 = fopen_s(&file1, "maps/defaultMaps/stage1obs.dat", "rb");
    err2 = fopen_s(&file2, "maps/defaultMaps/stage1wall.dat", "rb");
    //各ファイルを開いたときにエラーが起きていなかったら
    if (err == 0 || err1 == 0 || err2 == 0)
    {
        //ステージ1関連の配列の値をゼロにする
        for (int i = 0; i < 50; i++)
        {
            stage1Obstacle[i] = 0;
            stage1ObstacleType[i] = 0;
            stage1movewall[i] = 0;
        }
        //開いたファイルを読み値を配列に入れる
        fread(stage1ObstacleType, sizeof(int), 50, file);
        fread(stage1Obstacle, sizeof(int), 50, file1);
        fread(stage1movewall, sizeof(int), 50, file2);
        //ファイルを閉じる
        fclose(file);
        fclose(file1);
        fclose(file2);
    }
}
/**
 * @brief エンドレスモードのハイスコアをロードする
 * @details エンドレスモードのハイスコアが記録されたバイナリファイルを読み取り
 *          変数highScoreに入れる
 */

void LoadScore()
{
    FILE* file;
    errno_t err = fopen_s(&file, "data/hs.dat", "rb");
    if (err == 0)
    {
        isSucceceed = 1;
        fread(&highScore, sizeof(float), 1, file);
        fclose(file);
    }
    else
    {
        isSucceceed = 0;
        highScore = 0;
    }
}

/**
 * @brief 効果音の音量を調整する
 * @details ロードした効果音の音量を調整する
 */

void setVolume()
{
    ChangeVolumeSoundMem(120, selectSound);
    ChangeVolumeSoundMem(120, interectSound);
    ChangeVolumeSoundMem(60, engineSound);
}

/**
 * @brief カメラを揺らす
 * @details カメラの座標を1フレームだけずらして視界を揺らす
 */

void CameraShake()
{
    /** @brief  乱数を取得する際の上限と下限に使用する数値*/
    int range = 3;
    /** @brief  乱数を取得する関数が整数のみを返すためこの変数の数値で割る*/
    int mult = 10;
    /** @brief  カメラの座標*/
    VECTOR camPos = GetCameraPosition();
    /** @brief  カメラの向いている座標*/
    VECTOR targetPos = GetCameraTarget();
    /** @brief  カメラが移動する座標*/
    VECTOR offset = VGet((float)get_rand(-range, range) / mult,(float)get_rand(-range, range) / mult, 0);
    //カメラの座標をセットする
    SetCameraPositionAndTarget_UpVecY(VAdd(camPos, offset), VAdd(targetPos, offset));
    //この関数を呼び出す条件のflagを偽にする
    isGetDamaged = false;
}

