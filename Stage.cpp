
#include "Stage.h"
#define CLOSEDMOVERANGE 4
#define MOVERANGE 10


void stage::SetUp(int obst[50],int type[50],int movewalls[50])
{
    //使用されるボタンの位置とサイズを設定する
    resume.SetButtonPosition(VGet(960, 540, 1), 400, 100, 0.9f);
    restart.SetButtonPosition(VGet(960, 740, 1), 400, 100, 0.9f);
    Stage1ToTitle.SetButtonPosition(VGet(960, 940, 1), 400, 100, 0.9f);
    //使用するボタンを配列に入れる
    Buttons[0] = resume;
    Buttons[1] = restart;
    Buttons[2] = Stage1ToTitle;
    //ボタンに表示される文字列の設定
    Buttons[0].SetText("Resume");
    Buttons[1].SetText("Restart");
    Buttons[2].SetText("Quit");
    //ボタンの画像の設定
    Buttons[0].SetGraph(buttonGraph);
    Buttons[1].SetGraph(buttonGraph);
    Buttons[2].SetGraph(buttonGraph);
    //プレイヤーと敵の初期設定
    player.SetUp();
    enemy.SetUp();
    //プレイヤーと敵にお互いのポインタを渡す
    player.EnemySet(&enemy);
    enemy.PlayerSet(&player);
    //障害物関連の初期化
    for (int i = 0; i < 50; i++)
    {
        //引数で受け取った配列の値を障害物の配列に入れる
        obstacleDefault[i] = obst[i];
        obstacle[i] = obst[i];
        obstacleTypeDefault[i] = type[i];
        obstacleType[i] = type[i];
        moveWallType[i] = movewalls[i];
        //障害物の初期化
        moveWalls[i].SetUp();
        maps[i].BaseSetUp();
    }
    for (int i = 0; i < 30; i++)
    {
        //プレイヤーよりも後ろのマップの初期化
        backWards[i].BaseSetUp();
    }
}
void stage::Main()
{
    //シャドウマップの設定
    SetShadowMapDrawArea(shadowHandle, VGet(-120.0f, -1.0f, -220.0f + player.CameraPosition.z), VGet(120.0f, 240.0f, 220.0f + player.CameraPosition.z));
    ShadowMap_DrawSetup(shadowHandle);
    //プレイヤーと敵の影の描画
    MV1DrawModel(player.ModelHandle);
    MV1DrawModel(enemy.ModelHandle);
    //各種マップ関連のモデルの影の描画
    if (isStarted)
    {
        DrawBackWards();
    }
    ObstacleShadowDraw();
    moveWallShadow();
    //シャドウマップへの描画をやめる
    ShadowMap_DrawEnd();
    //背景の描画
    DrawGraph3D(0, 500, player.Position.z + 1000, backGroundHandle, false);
    //プレイヤーの描画処理
    player.Draw();
    //敵の描画
    MV1DrawModel(enemy.ModelHandle);
    //描画するシャドウマップの設定
    SetUseShadowMap(0, shadowHandle);
    //マップと障害物の描画の描画
    DrawBase();
    DrawObstacles();
    //カメラ振動用のフラグを一定時間でfalseに戻す処理
    /*if (isGetDamage)
    {
        if (damageRate.MeasureTimer(0.5f))
        {
            isGetDamage = false;
            damageRate.RestartTimer();
        }
    }*/
    //ゲーム開始演出中の処理
    if (isStarted)
    {
        //プレイヤーの後ろを描画する処理
        DrawGraph3D(0, 500, player.Position.z - 1000, backGroundHandle, false);
        DrawBackWards();
        //敵の移動処理
        enemy.Move(VGet(0, -3, player.Position.z - 70));
        //敵が演出中も攻撃するようにする
        enemy.Vulcan(true);
        //ゲーム開始時のクリア目標の説明
        Briefing();
        //エンジン音が鳴っていなければ鳴らす
        if (0 == CheckSoundMem(engineSound))
        {
            PlaySoundMem(engineSound, DX_PLAYTYPE_LOOP);
        }
    }
    //ゲームが始まったら
    else
    {
        //カメラの視野角を設定する
        SetupCamera_Perspective(1);
        //インゲーム中の処理
        if (!isPause &&!isCleared && !isGameOver )
        {
            //インゲームの処理
            Ingame();
            //エンジン音が鳴っていなければ鳴らす
            if (0 == CheckSoundMem(engineSound))
            {
                PlaySoundMem(engineSound, DX_PLAYTYPE_LOOP);
            }
        }
        //クリア演出中の処理
        else if (isCleared)
        {
            //敵とプレイヤーの処理
            enemy.Main(true);
            player.clearProcess();
            //インゲームからクリア画面に移動するまでの処理
            IngameToClear();
            //エンジン音が鳴っていなければ鳴らす
            if (0 == CheckSoundMem(engineSound))
            {
                PlaySoundMem(engineSound, DX_PLAYTYPE_LOOP);
            }
        }
        //ゲームオーバー時の処理
        else if (isGameOver)
        {
            //敵とプレイヤーの処理
            MV1DrawModel(enemy.ModelHandle);
            player.Main(true);
            enemy.Position.z += 2;
            enemy.Move(enemy.Position);
            //インゲームからゲームオーバー画面に遷移するまでの処理
            IngameToGameover();
            //エンジン音が鳴っていなければ鳴らす
            if (1 == CheckSoundMem(engineSound))
            {
                StopSoundMem(engineSound);
            }
        }
        //ポーズメニュー中の処理
        else
        {
            //ポーズ画面の処理
            PauseScreen();
            //エンジン音が鳴っていなければ鳴らす
            if (1 == CheckSoundMem(engineSound))
            {
                StopSoundMem(engineSound);
            }
        }
        //ポーズ画面の切り替えの処理
        if (Input_GetKeyboardDown(KEY_INPUT_ESCAPE))
        {
            isPause = isPause ? false : true;
            choosedButton = 0;
        }
    }
    //ゲームフェーズ別の操作方法の表示
    if (gamePhase == PHASE_CHASE || gamePhase == PHASE_OVERSHOOT)
    {
        control.DrawTextWithSort(0, 1920, "操作方法　WASD:移動  SPACE:攻撃  ESC:中断", japaneseFontHandle, SORT_CENTER, 1000, true, GetColor(0, 255, 0));
    }
    else
    {
        control.DrawTextWithSort(0, 1920, "操作方法　WASD:移動  SPACE:ミサイルを回避  ESC:中断", japaneseFontHandle, SORT_CENTER, 1000, true, GetColor(0, 255, 0));
    }
    //プレイヤーと敵のエンジンのライトの位置
    SetLightPositionHandle(playerLight, VAdd(VScale(VGet(-player.forward().x, player.forward().y, -player.forward().z), 5), player.Position));
    SetLightPositionHandle(enemyLight, VAdd(MV1GetPosition(enemy.ModelHandle), VGet(0, 0, -5)));
    
}

void stage::Initialize()
{
    //変数の値を初期化する
    isStarted = true;
    isCleared = false;
    isGameOver = false;
    isDead = false;
    isPause = false;
    isRestarting = false;
    PauseControllable = true;
    isQuitting = false; 
    choosedButton = 0;
    gamePhase = 0;
    isKilled = false;
    //プレイヤーと敵を初期化する
    enemy.Init();
    player.Init();
    //障害物の初期化
    for (int i = 0; i < 50; i++)
    {
        obstacle[i] = obstacleDefault[i];
        obstacleType[i] = obstacleTypeDefault[i];
    }
    //クリア演出のカメラのx座標を0にする
    clearCameraOffsetx = 0;
    //ゲームに使用されるタイマーのリスタート
    gameOverTimer.RestartTimer();
    missionTimer.RestartTimer();
    enemy.firingCooldown = 1.8f;
}
void stage::Obstacle_Draw(int i ,int pos, bool upper, bool lower, bool right, bool left)
{
    //プレイヤーのヒットボックスが障害物の当たり判定に当たったら
    if (maps[pos].DamageBox(upper, lower, right, left, false, player.hitbox1, player.hitbox2) && !isStarted && player.Health > 0 && !player.isImmortal && !isObjectiveAppeared)
    {
        //難易度がノーマルの場合
        if (difficulty == 0)
        {
            player.Health -= 20;
            player.isImmortal = true;
            isGetDamaged = true;
        }
        //難易度がハードの時
        else
        {
            isDead = true;
            player.Health = 0;
            isGetDamaged = true;
        }
    }
    //障害物の位置に応じて敵が移動できる範囲を設定する
    if (i == 0 || i == 2 || i == 1)
    {
        enemy.minimumMoveRangeX = left ? -CLOSEDMOVERANGE : enemy.minimumMoveRangeX;
        enemy.minimumMoveRangeY = lower ? -CLOSEDMOVERANGE : enemy.minimumMoveRangeY;
        enemy.moveRangeX = right ? CLOSEDMOVERANGE : enemy.moveRangeX;
        enemy.moveRangeY = upper ? CLOSEDMOVERANGE : enemy.moveRangeY;
    }
}
void stage::AAGun_Draw(int i ,int pos, bool upper, bool lower, bool right, bool left)
{
    //対空砲の当たり判定にあたっていたら
    if (AAs[pos].DamageZone(upper, lower, right, left,player.hitbox1, player.hitbox2) && !isGetDamage && player.Health > 0 && !isPause && !player.isImmortal && !isObjectiveAppeared)
    {
        player.Health -= 5;
        isGetDamage = true;
        isGetDamaged = true;
        PlaySoundMem(hitSound, DX_PLAYTYPE_BACK);
    }
    //障害物の位置に応じて敵が移動できる範囲を設定する
    if (i==0||i == 2 || i==1)
    {
        enemy.minimumMoveRangeX = left ? -CLOSEDMOVERANGE : enemy.minimumMoveRangeX;
        enemy.minimumMoveRangeY = lower ? -CLOSEDMOVERANGE : enemy.minimumMoveRangeY;
        enemy.moveRangeX = right ? CLOSEDMOVERANGE : enemy.moveRangeX;
        enemy.moveRangeY = upper ? CLOSEDMOVERANGE : enemy.moveRangeY;
    }
}
void stage::MoveWallDraw(int i ,int pos, bool high,bool mid,bool low)
{
    //動く障害物の当たり判定にあたっていたら
    if (moveWalls[pos].DrawMoveWall(high, mid, low, player.hitbox1, player.hitbox2) && !isStarted && player.Health > 0 && !player.isImmortal && !isObjectiveAppeared)
    {
        //難易度がノーマルの場合
        if (difficulty == 0)
        {
            player.Health -= 20;
            player.isImmortal = true;
            isGetDamaged = true;
        }
        //難易度がハードの時
        else
        {
            isDead = true;
            player.Health = 0;
            isGetDamaged = true;
        }
    }
    //障害物の位置に応じて敵が移動できる範囲を設定する
    if (i == 0 || i == 1 || i== 2)
    {
        enemy.minimumMoveRangeY = low ? -CLOSEDMOVERANGE : enemy.minimumMoveRangeY;
        enemy.moveRangeY = high ? CLOSEDMOVERANGE : enemy.moveRangeY;
    }
}
void stage::ObstacleShadowDraw()
{
    //プレイヤーの位置に応じて障害物の配列から15個描画する
    for (int i = 0; i < 15; i++)
    {
        //プレイヤーの座標を配列全体分のモデルの長さ4000で割った余りをマップのモデルの長さ80で割った数値をiに足す
        int pos = i + ((int)player.Position.z % 4000) / 80;
        //配列の範囲外に出ないようにする
        if (pos > 49)
        {
            pos -= 50;
        }
        //描画の処理
        if (pos >= 0)
        {
            //プレイヤーの座標をマップのモデルの長さ80で割りiを足し80をかける
            maps[pos].position.z = (float)(80 * (i + (int)player.Position.z / 80));
            //壁と床の描画
            maps[pos].DrawbaseMap();
            //障害物を描画する
            if (obstacleType[pos] < 2 && maps[pos].position.z >= startPosZ)
            {
                switch (obstacle[pos]) {
                case UPPER:
                    maps[pos].DamageBox(true, false, false, false, false, player.hitbox1, player.hitbox2);
                    break;
                case LOWER:
                    maps[pos].DamageBox(false, true, false, false, false, player.hitbox1, player.hitbox2);
                    break;
                case RIGHT:
                    maps[pos].DamageBox(false, false, true, false, false, player.hitbox1, player.hitbox2);
                    break;
                case LEFT:
                    maps[pos].DamageBox(false, false, false, true, false, player.hitbox1, player.hitbox2);
                    break;
                case UPPER_LOWER:
                    maps[pos].DamageBox(true, true, false, false, false, player.hitbox1, player.hitbox2);
                    break;
                case UPPER_RIGHT:
                    maps[pos].DamageBox(true, false, true, false, false, player.hitbox1, player.hitbox2);
                    break;
                case UPPER_LEFT:
                    maps[pos].DamageBox(true, false, false, true, false, player.hitbox1, player.hitbox2);
                    break;
                case LOWER_RIGHT:
                    maps[pos].DamageBox(false, true, true, false, false, player.hitbox1, player.hitbox2);
                    break;
                case LOWER_LEFT:
                    maps[pos].DamageBox(false, true, false, true, false, player.hitbox1, player.hitbox2);
                    break;
                case RIGHT_LEFT:
                    maps[pos].DamageBox(false, false, true, true, false, player.hitbox1, player.hitbox2);
                    break;
                default:
                    break;
                }
            }
        }
    }
}
void stage::moveWallShadow()
{
    //プレイヤーの位置に応じて障害物の配列から15個描画する
    for (int i = 0; i < 15; i++)
    {
        //プレイヤーの座標を配列全体分のモデルの長さ4000で割った余りをマップのモデルの長さ80で割った数値をiに足す
        int pos = i + ((int)player.Position.z % 4000) / 80;
        //配列の範囲外に出ないようにする
        if (pos > 49)
        {
            pos -= 50;
        }
        //描画の処理
        if (pos >= 0)
        {
            //プレイヤーの座標をマップのモデルの長さ80で割りiを足し80をかける
            moveWalls[pos].position.z = (float)(80 * (i + (int)player.Position.z / 80));
            //壁と床の描画
            moveWalls[pos].DrawbaseMap();
            //障害物を描画する
            if (moveWalls[pos].position.z >= startPosZ)
            {
                switch (moveWallType[pos]) {
                case HIGH:
                    moveWalls[pos].DrawMoveWall(true, false, false, player.hitbox1, player.hitbox2);
                    break;
                case MID:
                    moveWalls[pos].DrawMoveWall(false, true, false, player.hitbox1, player.hitbox2);
                    break;
                case LOW:
                    moveWalls[pos].DrawMoveWall(false, false, true, player.hitbox1, player.hitbox2);
                    break;
                default:
                    moveWalls[pos].DrawMoveWall(false, false, false, player.hitbox1, player.hitbox2);
                    break;
                }
            }
        }
    }
}
void stage::DrawBase()
{
    //プレイヤーの位置に応じて障害物の配列から15個描画する
    for (int i = 14; i > -1; i--)
    {
        //プレイヤーの座標を配列全体分のモデルの長さ4000で割った余りをマップのモデルの長さ80で割った数値をiに足す
        int pos = i + ((int)player.Position.z % 4000) / 80;
        //配列の範囲外に出ないようにする
        if (pos > 49)
        {
            pos -= 50;
        }
        //描画の処理
        if (pos >= 0)
        {
            //プレイヤーの座標をマップのモデルの長さ80で割りiを足し80をかける
            maps[pos].position.z = (float)(80 * (i + (int)player.Position.z / 80));
            if (maps[pos].position.z >= startPosZ)
                maps[pos].DrawbaseMap();
        }
    }
}
void stage::DrawBackWards()
{
    //開始地点から後ろに30回マップを描画する
    for (int i = 0; i < 30; i++)
    {
        int pos =-(i - 2);
        backWards[i].position.z = 80 * pos + startPosZ;
        backWards[i].DrawbaseMap();
        
    }
}
void stage::DrawObstacles()
{
    //敵が移動できる範囲を初期化する
    enemy.minimumMoveRangeX = -MOVERANGE;
    enemy.minimumMoveRangeY = -MOVERANGE;
    enemy.moveRangeX = MOVERANGE;
    enemy.moveRangeY = MOVERANGE;
    //プレイヤーの位置に応じて障害物の配列から15個描画する
    for (int i = 14; i > -1; i--)
    {
        //プレイヤーの座標を配列全体分のモデルの長さ4000で割った余りをマップのモデルの長さ80で割った数値をiに足す
        int pos = i + ((int)player.Position.z % 4000) / 80;
        //配列の範囲外に出ないようにする
        if (pos > 49)
        {
            pos -= 50;
            //すでに描画されたものをランダムにする
            int t = 15 + ((int)player.Position.z % 4000) / 80;
            obstacle[t-50] = get_rand(0, 25);
            obstacleType[t-50] = get_rand(0, 8);
        }
        //描画の処理
        if (pos >= 0)
        {
            //プレイヤーの座標をマップのモデルの長さ80で割りiを足し80をかけた値を障害物の座標に入れる
            maps[pos].position.z = (float)(80 * (i + (int)player.Position.z / 80));
            AAs[pos].position.z = (float)(80 * (i + (int)player.Position.z / 80));
            moveWalls[pos].position.z = (float)(80 * (i + (int)player.Position.z / 80));
            //障害物の種類に応じて処理を行う
            if (maps[pos].position.z >= startPosZ)
            {
                if (obstacleType[pos] < 2)
                {
                    Obstacles(pos, i);
                }
                else
                {
                    AAGuns(pos, i);
                }

                MoveWalls(pos, i);
            }
        }
    }
}
void stage::AAGuns(int pos, int i)
{
    //位置別に異なる引数を与える処理
    switch (obstacle[pos]) {
    case UPPER:
        AAGun_Draw(i, pos, true, false, false, false);
        break;
    case LOWER:
        AAGun_Draw(i, pos, false, true, false, false);
        break;
    case RIGHT:
        AAGun_Draw(i, pos, false, false, true, false);
        break;
    case LEFT:
        AAGun_Draw(i, pos, false, false, false, true);
        break;
    case UPPER_LOWER:
        AAGun_Draw(i, pos, true, true, false, false);
        break;
    case UPPER_RIGHT:
        AAGun_Draw(i, pos, true, false, true, false);
        break;
    case UPPER_LEFT:
        AAGun_Draw(i, pos, true, false, false, true);
        break;
    case LOWER_RIGHT:
        AAGun_Draw(i, pos, false, true, true, false);
        break;
    case LOWER_LEFT:
        AAGun_Draw(i, pos, false, true, false, true);
        break;
    case RIGHT_LEFT:
        AAGun_Draw(i, pos, false, false, true, true);
        break;
    default:
        AAGun_Draw(i, pos, false, false, false, false);
        break;
    }
}
void stage::Obstacles(int pos, int i)
{
    //位置別に異なる引数を与える処理
    switch (obstacle[pos]) {
    case UPPER:
        Obstacle_Draw(i, pos, true, false, false, false);
        break;
    case LOWER:
        Obstacle_Draw(i, pos, false, true, false, false);
        break;
    case RIGHT:
        Obstacle_Draw(i, pos, false, false, true, false);
        break;
    case LEFT:
        Obstacle_Draw(i, pos, false, false, false, true);
        break;
    case UPPER_LOWER:
        Obstacle_Draw(i, pos, true, true, false, false);
        break;
    case UPPER_RIGHT:
        Obstacle_Draw(i, pos, true, false, true, false);
        break;
    case UPPER_LEFT:
        Obstacle_Draw(i, pos, true, false, false, true);
        break;
    case LOWER_RIGHT:
        Obstacle_Draw(i, pos, false, true, true, false);
        break;
    case LOWER_LEFT:
        Obstacle_Draw(i, pos, false, true, false, true);
        break;
    case RIGHT_LEFT:
        Obstacle_Draw(i, pos, false, false, true, true);
        break;
    default:
        Obstacle_Draw(i, pos, false, false, false, false);
        break;
    }
}
void stage::MoveWalls(int pos,int i)
{
    //位置別に異なる引数を与える処理
    switch (moveWallType[pos]) {
    case HIGH:
        MoveWallDraw(i, pos, true, false, false);
        break;
    case MID:
        MoveWallDraw(i, pos, false, true, false);
        break;
    case LOW:
        MoveWallDraw(i, pos, false, false, true);
        break;
    default:
        MoveWallDraw(i, pos, false, false, false);
        break;
    }
    if (!isPause)
    {
        moveWalls[pos].MovePosition();
    }
}
void stage::Briefing()
{
    player.transitionProcess(false);
    //フェードインが終わったらクリア目標を表示する
    if (fadein(0.5f) && !isObjectiveAppeared)
    {
        progress = 0;
        isObjectiveAppeared = true;
    }
    //クリア目標をフェードインさせる
    if (isObjectiveAppeared && objectiveText.fadeInText(0, 1920, "クリア目標:攻撃を避けて生き残れ", biggerJpFontHandle, SORT_CENTER, -300, true, GetColor(255, 255, 255), GetColor(50, 50, 50), 0, 0.2f))
    {
        //クリア目標と開始までのカウントダウンを表示
        objectiveText.DrawTextWithSort(0, 1920, "クリア目標:攻撃を避けて生き残れ", biggerJpFontHandle, SORT_CENTER, 300, true, GetColor(0, 255, 0), GetColor(50, 50, 50));
        countDownText.DrawTextWithSort(0, 1920, "%.f", CountDownFontHandle, SORT_CENTER, 450, true, GetColor(255, 255, 30), GetColor(50, 50, 50), (float)countDown);
        //カウントダウン用の変数を一秒ごとに減らす
        if (CountDownTimer.MeasureTimer(1))
        {
            CountDownTimer.RestartTimer();
            countDown -= 1;
        }
        //クリア目標を三秒表示したら
        if (objectiveShowTimer.MeasureTimer(3))
        {

            isStarted = false;
            isObjectiveAppeared = false;
            objectiveShowTimer.RestartTimer();
            CountDownTimer.RestartTimer();
            countDown = 3;
            objectiveText.resetAlpha();
            enemy.isFiring = false;
            enemy.firingCooldown = -2.0f;
            player.isImmortal = true;
        }
    }
    isDead = false;
}
void stage::Ingame()
{
    //プレイヤーの体力が0以下になったら
    if (player.Health <= 0)
    {
        isDead = true;
        player.Health = 0;
    }
    //敵の体力が0以下になったら
    if (enemy.Health <= 0)
    {
        enemy.Health = 0;
        isKilled = true;
    }
    //プレイヤーの体力ゲージを表示する
    DrawExtendGraph(54, 830, 410, 905, uiBox_03, true);
    playerHealthText.DrawTextWithSort(90, 1920, "PLAYER HP", fontHandle, SORT_LEFT, 850, true, GetColor(0, 255, 0));
    playerHealthIndi.DrawTextWithSort(290, 1920, "%.f", fontHandle, SORT_LEFT, 850, true, GetColor(0, 255, 0),GetColor(50,50,50),player.Health);
    DrawExtendGraph(50, 900, 720, 986, playerHealthGauge, true);
    DrawRectExtendGraph(74, 913, (int)(74 + (622 * (player.Health / 100))), 973, 0, 0, (int)(2122*(player.Health/100)) , 176, playerHealthBar,true);
    //プレイヤーがゴールにたどり着いたら逃走フェーズから追跡フェーズへの遷移に移る
    if (player.BasePosition.z > stageLength && gamePhase == PHASE_RUN)
    {
        gamePhase = PHASE_OVERSHOOT;
    }
    //逃走フェーズの処理
    else if (gamePhase == PHASE_RUN)
    {
        RunPhase();
    }
    //追跡フェーズへの遷移の処理
    if (gamePhase == PHASE_OVERSHOOT)
    {
        OverShootPhase();
    }
    //追跡フェーズの処理
    if (gamePhase == PHASE_CHASE)
    {
        ChasePhase();
    }
    //プレイヤーが死亡した時
    if (isDead)
    {
        //ゲームオーバー処理
        isGameOver = true;
        GameOverInitialize();
    }
    //敵が死亡した時
    if (isKilled)
    {
        //クリア処理
        isCleared = true;
        ClearInitialize();
    }
}
void stage::IngameToClear()
{
    //敵の死亡した位置がプレイヤーよりも前に来た時の処理
    if (enemy.deadPosition.z < player.Position.z + 2)
    {
        if (timeScale < 1)
        {
            timeScale += 0.05f;
        }
        else
        {
            timeScale = 1;
        }
        //クリア演出のカメラが移動しきっていない時
        if (clearCameraOffsetx > -7)
        {
            clearCameraOffsetx = clearCameraOffsetx - smooth(clearCameraOffsetx, -7, 120);
        }
        else
        {
            clearCameraOffsetx = -7;
        }
        //カメラの向きの設定
        cameraDirection = VAdd(VGet(0, 1, 8), player.BasePosition);
        SetCameraPositionAndTarget_UpVecY(VAdd(VGet(clearCameraOffsetx, player.offset.y + 2, -5), player.BasePosition),
            cameraDirection);
        //現在のステージが2以外の場合クリア画面を表示する
        if (stages != 2)
        {
            ClearMain();
        }
        //そうでなければ3ステージ目のクリア画面を表示する
        else
        {
            ClearStage3();
        }
    }
    //敵が死亡した位置よりもプレイヤーが後ろにいるとき
    else
    {
        SetCameraPositionAndTarget_UpVecY(VAdd(VGet(enemy.offset.x+3, 0 , -15), enemy.BasePosition),
            VAdd(VGet(enemy.offset.x, enemy.offset.y,0), enemy.BasePosition));
        //時間経過の速度を落とす
        if (timeScale > 0.2f)
        {
            timeScale -= 0.05f;
        }
        else
        {
            timeScale = 0.2f;
        }
        cameraDirection = enemy.deadPosition;
        
    }
    player.CameraPosition.z = player.Position.z;
}
void stage::IngameToGameover()
{
    //プレイヤーが死亡してから1秒後にメニューを表示する
    if (gameOverTimer.MeasureTimer(1.0f))
    {
        GameOverMain();
    }
}
//未使用
void stage::CameraTargetMove()
{
    VECTOR dir = VectorDirectionNormalize(cameraDirection, cameraTarget);
    float  dis = VectorLength(cameraDirection, cameraTarget);
    if (remainingTime > 0 && dis > 0.3f)
    {
        cameraTarget = VAdd(VGet(player.offset.x, player.offset.y + 1, 8), player.BasePosition);
        cameraDirection = VAdd(cameraDirection, VScale(dir, (dis / remainingTime)));
    }
    else
    {
        remainingTime = 0;
        cameraDirection = VAdd(VGet(0, 1, 8), player.BasePosition);
    }

    remainingTime = 2 - clearCameraTimer.GetElapsed();
    
}
void stage::RunPhase()
{
    //逃走フェーズのUIの描画
    objectiveText.DrawTextWithSort(70, 1920, "目標:攻撃を避けて生き残れ", japaneseFontHandle, SORT_LEFT, 60, true, GetColor(0, 255, 0), GetColor(50, 50, 50));
    DrawExtendGraph(1716, 100, 1820, 980, gaugeHandle, true);
    DrawRectExtendGraph(1738, (int)(135 + (810 -810* ((player.BasePosition.z - startPosZ) / (stageLength - startPosZ)))), 1798, 945, 0, (int)(2097 - (2097 * (player.BasePosition.z - startPosZ) / (stageLength - startPosZ))), 156, (int)(2097 * (player.BasePosition.z - startPosZ) / (stageLength - startPosZ)), barHandle, true);
    //プレイヤーと敵の処理
    player.Main(false);
    enemy.Main(false);
}
void stage::OverShootPhase()
{
    //追跡フェーズへの遷移の処理
    if (enemy.Transition())
    {
        //遷移が終わったらクリア目標を表示して追跡フェーズに移る
        isObjectiveAppeared = true;
        gamePhase = PHASE_CHASE;
    }
}
void stage::ChasePhase()
{

    if (isObjectiveAppeared)
    {
        player.transitionProcess(true);
        //クリア目標をフェードインさせる
        if (objectiveText.fadeInText(0, 1920, "クリア目標:敵機を撃墜しろ", biggerJpFontHandle, SORT_CENTER, 300, true, GetColor(255, 255, 255), GetColor(50, 50, 50), 0, 0.2f))
        {
            //クリア目標をとカウントダウンを表示する
            objectiveText.DrawTextWithSort(0, 1920, "クリア目標:敵機を撃墜しろ", biggerJpFontHandle, SORT_CENTER, 300, true, GetColor(255, 255, 255), GetColor(50, 50, 50), 0);
            countDownText.DrawTextWithSort(0, 1920, "%.f", CountDownFontHandle, SORT_CENTER, 450, true, GetColor(255, 255, 30), GetColor(50, 50, 50), (float)countDown);
            if (CountDownTimer.MeasureTimer(1))
            {
                CountDownTimer.RestartTimer();
                countDown -= 1;
            }
            //三秒経過したらクリア目標の表示をやめる
            if (objectiveShowTimer.MeasureTimer(3))
            {
                isObjectiveAppeared = false;
                player.isImmortal = true;
                countDown = 3;
                objectiveShowTimer.RestartTimer();
                CountDownTimer.RestartTimer();
                objectiveText.resetAlpha();
            }
        }
    }
    else
    {
        //敵の体力を表示する
        DrawExtendGraph(450, 50,1470,241, E_gauge, true);
        DrawRectExtendGraph(476 ,65, (int)(476  + (968 * ((float)enemy.Health / 100))),165,0,0, (int)(3305 * ((float)enemy.Health / 100)), 376, E_bar, true);
        enemyHealthText.DrawTextWithSort(0, 1920, "ENEMY HP", BiggerFontHandle, SORT_CENTER, 180, true, GetColor(255, 0, 0));
        player.Main(true);
    }
    //クリア目標の表示
    objectiveText.DrawTextWithSort(70, 1920, "目標:敵機を撃墜しろ", japaneseFontHandle, SORT_LEFT, 60, true, GetColor(0, 255, 0), GetColor(50, 50, 50));
    //時間切れの時の処理
    if (missionTimer.MeasureTimer((float)timeLimit) || player.ammo <= 0)
    {
        enemy.Cobra();
    }
    //時間切れでないときの処理
    else
    {
        enemy.Main(true);
        //残り時間の表示
        missionTime.DrawTextWithSort(0, 1920, "Remaining time : %.f/120 sec", fontHandle, SORT_CENTER, 230, false, GetColor(0, 255, 0), GetColor(0, 255, 0),(float)(timeLimit-(int)missionTimer.GetElapsed(true)));
    }
}
void stage::PauseScreen()
{
    //背景を少し暗くする
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
    DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), 1);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    //ポーズメニューの操作
    PauseControll();
    //リスタートが選ばれた時
    if (isRestarting)
    {
        StopSoundMem(ingameBgm);
        //フェードアウトさせる
        if (fadeout(0.5f))
        {
            progress = 255;
            //現在のステージを初期化する
            Initialize();
        }
    }
    //ゲームを終了するとき
    if (isQuitting)
    {
        StopSoundMem(ingameBgm);
        //フェードアウトさせる
        if (fadeout(0.5f))
        {
            progress = 255;
            //タイトルを初期化する
            Titleinitialize();
            scene = SCENE_TITLE;
        }
    }
}
void stage::PauseControll()
{
    //ポーズメニューのボタンを描画する
    for (int i = 0; i < 3; i++)
    {
        Buttons[i].Main(choosedButton == i, true, 40);
    }
    //選択されたボタン別の処理
    switch (choosedButton) {
    case PAUSE_RESUME://続行が選択された時
        if (Input_GetKeyboardDown(KEY_INPUT_SPACE))
        {
            //ポーズ画面からインゲームに移る
            isPause = false;
            choosedButton = 0;
            PlaySoundMem(interectSound, DX_PLAYTYPE_BACK, true);
        }
        break;
    case PAUSE_RESTART://リスタートが選択された時
        if (Input_GetKeyboardDown(KEY_INPUT_SPACE))
        {
            PauseControllable = false;
            isRestarting = true;
            PlaySoundMem(interectSound, DX_PLAYTYPE_BACK, true);
        }
        break;
    default://タイトルに戻るとき
        if (Input_GetKeyboardDown(KEY_INPUT_SPACE))
        {
            isQuitting = true;
            PauseControllable = false;
            PlaySoundMem(interectSound, DX_PLAYTYPE_BACK, true);
        }
        break;
    }
    //ポーズ画面を操作可能な時
    if (PauseControllable)
    {
        //WSキーで選択しているボタンを上下に変更する
        if (Input_GetKeyboardDown(KEY_INPUT_W) && choosedButton > 0)
        {
            choosedButton--;
            PlaySoundMem(selectSound, DX_PLAYTYPE_BACK, true);
        }
        if (Input_GetKeyboardDown(KEY_INPUT_S) && choosedButton < 2)
        {
            choosedButton++;
            PlaySoundMem(selectSound, DX_PLAYTYPE_BACK, true);
        }
    }
}