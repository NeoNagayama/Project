#include "Stage_Endless.h"

void stageEndless::SetUp()
{
    // ボタンの位置の設定
    resume.SetButtonPosition(VGet(960, 540, 1), 400, 100, 0.9f);
    restart.SetButtonPosition(VGet(960, 740, 1), 400, 100, 0.9f);
    Stage1ToTitle.SetButtonPosition(VGet(960, 940, 1), 400, 100, 0.9f);
    // ボタンを配列に入れる
    Buttons[0] = resume;
    Buttons[1] = restart;
    Buttons[2] = Stage1ToTitle;
    // ボタンのテキストの設定
    Buttons[0].SetText("Resume");
    Buttons[1].SetText("Restart");
    Buttons[2].SetText("Quit");
    // ボタンの画像の設定
    Buttons[0].SetGraph(buttonGraph);
    Buttons[1].SetGraph(buttonGraph);
    Buttons[2].SetGraph(buttonGraph);
    // プレイヤーと敵の初期設定
    player.SetUp();
    enemy.SetUp();
    // プレイヤーと敵のポインタをお互いに渡す
    player.EnemySet(&enemy);
    enemy.PlayerSet(&player);
    // 障害物の初期設定
    for (int i = 0; i < 50; i++)
    {
        moveWalls[i].SetUp();
        maps[i].BaseSetUp();
    }
    // 後方のマップの初期設定
    for (int i = 0; i < 30; i++)
    {
        backWards[i].BaseSetUp();
    }
    // ステージのランダム化
    StageRandomize();
}

void stageEndless::Init()
{
    // プレイヤーと敵の初期化
    player.Init();
    enemy.Init();
    // 各変数の初期化
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
    stageLength = 800;
    GoalRange = 0;
    baseAmmo = 200;
    baseHealth = 100;
    Round = 1;
    clearCameraOffsetx = 0;
    isSaved = false;
    startPosZ = 0;
    // ステージのランダム化
    StageRandomize();
}

void stageEndless::StartWave()
{
    // 制限時間用のタイマーをリセットする
    missionTimer.RestartTimer();
    // 敵の初期化
    enemy.Init();
    // ゲームを逃走フェーズに戻す
    gamePhase = PHASE_RUN;
    Round += 1;
    // 変数の初期化
    isCleared = false;
    isGameOver = false;
    isKilled = false;
    isDead = false;
    isPause = false;
    isRestarting = false;
    PauseControllable = true;
    isQuitting = false;
    isStarted = true;
    clearCameraOffsetx = 0;
    // 逃走フェーズのクリア地点の変更
    stageLength = player.Position.z + GoalRange + 200.0f;
    // ゲームの開始地点の変更
    startPosZ = player.Position.z + 200;
    // カメラ演出用の変数の設定
    player.camSetUp(startPosZ);
}

void stageEndless::StageRandomize()
{
    // 障害物の配列の値にランダムな値を入れる
    for (int i = 0; i < 50; i++)
    {
        obstacle[i] = get_rand(0, 17);
        obstacleType[i] = get_rand(0, 5);
        moveWallType[i] = get_rand(0, 12);
    }
}

void stageEndless::main()
{
    // シャドウマップ描画範囲の設定
    SetShadowMapDrawArea(shadowHandle, VGet(-120.0f, -1.0f, -220.0f + player.CameraPosition.z),
                         VGet(120.0f, 240.0f, 220.0f + player.CameraPosition.z));
    // シャドウマップへの書き込み
    ShadowMap_DrawSetup(shadowHandle);
    MV1DrawModel(player.ModelHandle);
    MV1DrawModel(enemy.ModelHandle);
    if (isStarted)
    {
        DrawBackWards();
    }
    ObstacleShadowDraw();
    moveWallShadow();
    // シャドウマップへの書き込みをやめる
    ShadowMap_DrawEnd();
    // 背景画像の描画
    DrawGraph3D(0, 500, player.Position.z + 1000, backGroundHandle, false);
    SetUseShadowMap(0, shadowHandle);
    // プレイヤーと敵の描画
    player.Draw();
    MV1DrawModel(enemy.ModelHandle);
    // マップと障害物の描画
    DrawBase();
    DrawObstacles();
    // プレイ中のラウンド数の描画
    RoundCount.DrawTextWithSort(0, 1650, "ラウンド:%.f", japaneseFontHandle, SORT_RIGHT, 90, false, GetColor(0, 255, 0),
                                GetColor(50, 50, 50), (float)Round);
    // カメラ振動用のフラグを一定時間でfalseに戻す処理
    if (isGetDamage)
    {
        if (damageRate.MeasureTimer(0.5f))
        {
            isGetDamage = false;
            damageRate.RestartTimer();
        }
    }
    //
    if (isStarted)
    {
        // プレイヤーの後方に背景画像とマップを描画
        DrawGraph3D(0, 500, player.Position.z - 1000, backGroundHandle, false);
        DrawBackWards();
        // 敵の移動処理
        enemy.Move(VGet(0, -3, player.Position.z - 120));
        // クリア目標の表示
        Briefing();
        if (0 == CheckSoundMem(engineSound))
        {
            PlaySoundMem(engineSound, DX_PLAYTYPE_LOOP);
        }
    }
    else
    {
        SetupCamera_Perspective(1);
        // インゲームの処理
        if (!isPause && !isCleared && !isGameOver)
        {
            Ingame();
            if (0 == CheckSoundMem(engineSound))
            {
                PlaySoundMem(engineSound, DX_PLAYTYPE_LOOP);
            }
        }
        // クリア画面の処理
        else if (isCleared)
        {
            enemy.Main(true);
            player.clearProcess();
            // ラウンドの結果の表示
            RoundResult();
            if (0 == CheckSoundMem(engineSound))
            {
                PlaySoundMem(engineSound, DX_PLAYTYPE_LOOP);
            }
        }
        // ゲームオーバー画面の処理
        else if (isGameOver)
        {
            player.Main(true);
            enemy.Position.z += 2;
            enemy.Move(enemy.Position);
            // ゲームオーバー画面への移行の処理
            IngameToGameoverModified();
            if (1 == CheckSoundMem(engineSound))
            {
                StopSoundMem(engineSound);
            }
        }
        // ポーズ画面の処理
        else
        {
            E_Pause();
            if (1 == CheckSoundMem(engineSound))
            {
                StopSoundMem(engineSound);
            }
        }
        if (Input_GetKeyboardDown(KEY_INPUT_ESCAPE))
        {
            isPause = isPause ? false : true;
            choosedButton = 0;
        }
    }
    SetLightPositionHandle(
        playerLight,
        VAdd(VScale(VGet(-player.forward().x, player.forward().y, -player.forward().z), 5), player.Position));
    SetLightPositionHandle(enemyLight, VAdd(MV1GetPosition(enemy.ModelHandle), VGet(0, 0, -5)));
}

void stageEndless::IngameToGameoverModified()
{
    // プレイヤーが死亡してから1秒後にゲームオーバー画面を表示する
    if (gameOverTimer.MeasureTimer(1.0f))
    {
        EndlessGameOver(Round);
    }
    // ハイスコアの保存
    if (!isSaved && highScore <= Round - 1)
    {
        HighScore();
        isSaved = true;
    }
}

void stageEndless::RoundResult()
{
    // 敵の死亡した位置がプレイヤーよりも前に来た時の処理
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
        // クリア演出のカメラが移動しきっていない時
        if (clearCameraOffsetx > -9)
        {
            clearCameraOffsetx = clearCameraOffsetx - smooth(clearCameraOffsetx, -9, 120);
        }
        else
        {
            clearCameraOffsetx = -9;
        }
        // カメラの向きの設定
        cameraDirection = VAdd(VGet(0, 1, 8), player.BasePosition);
        SetCameraPositionAndTarget_UpVecY(VAdd(VGet(clearCameraOffsetx, player.offset.y + 2, -4), player.BasePosition),
                                          cameraDirection);
        ShowResult();
    }
    // 敵が死亡した位置よりもプレイヤーが後ろにいるとき
    else
    {
        SetCameraPositionAndTarget_UpVecY(VAdd(VGet(enemy.offset.x + 3, 0, -15), enemy.BasePosition),
                                          VAdd(VGet(enemy.offset.x, enemy.offset.y, 0), enemy.BasePosition));
        // 時間経過の速度を落とす
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
}

void stageEndless::ShowResult()
{
    if (GoalRange == 0)
    {
        GoalRange = 4000;
    }
    // リザルトに表示する情報をテキストに反映させる
    ReflectToText();
    // 0.5秒おきにリザルトで表示する要素を増やす
    if (R_Timer.MeasureTimer(0.5f) && resultStage < 4)
    {
        resultStage += 1;
        R_Timer.RestartTimer();
    }
    // ラウンドの結果を表示
    if (!isGetResult)
    {
        for (int i = 0; i < resultStage; i++)
        {
            R_Text[i].DrawTextWithSort(0, 1920, R_info[i], biggerJpFontHandle, SORT_LEFT, i * 120 + 200, true,
                                       GetColor(255, 255, 255), GetColor(50, 50, 50), R_Value[i]);
        }
    }
    // 次のラウンドで変化する数値を表示
    if (isGetResult)
    {
        for (int i = 0; i < resultStage; i++)
        {
            if (i < 3)
            {
                R_Text[i].DrawTextWithSort(0, 1920, R_info2[i], biggerJpFontHandle, SORT_LEFT, i * 120 + 200, true,
                                           GetColor(255, 255, 255), GetColor(50, 50, 50), R_Value2[i]);
            }
            else if (i < 4)
            {
                ResultType();
            }
        }
        // 五秒経過すると
        if (R_Timer.MeasureTimer(5.0f))
        {
            // 次のラウンドを始める
            StartWave();
            // リザルト用の変数の初期化
            isGetResult = false;
            resultStage = 0;
            R_Timer.RestartTimer();
        }
    }
    // ラウンドの結果を表示してから10秒後
    if (!isGetResult && R_Timer.MeasureTimer(10.0f))
    {
        // 次のラウンドで変化する値の計算
        // 残弾数から上昇する体力の計算
        baseHealthCache = 20 * (player.ammo / (baseAmmo - 50));
        // 難易度別の上昇する体力の計算
        if (difficulty == 0)
        {
            incleasedHealth = (20 * (player.ammo / (baseAmmo - 50))) / 2;
        }
        else
        {
            incleasedHealth = 20 * (player.ammo / (baseAmmo - 50));
        }
        baseAmmoCache = 30 * (player.Health / baseHealth);
        incleasedAmmo = 30 * (player.Health / baseHealth);
        player.Health += (baseHealth * (player.ammo / (baseAmmo - 50)));
        healedHealth = (baseHealth * (player.ammo / (baseAmmo - 50)));
        if (difficulty == 0)
        {
            baseHealth += baseHealthCache / 2;
        }
        else
        {
            baseHealth += baseHealthCache;
        }
        baseAmmo += baseAmmoCache;
        if (player.Health > baseHealth)
        {
            player.Health = baseHealth;
        }
        player.ammo = baseAmmo;
        negativeResultType = get_rand(0, 5);
        EffectResult();
        isGetResult = true;
        resultStage = 0;
    }
}

void stageEndless::ResultType()
{

    switch (negativeResultType)
    {
    case 0:
        R_Text[3].DrawTextWithSort(0, 1920, "移動速度増加＆ゴール距離増加", biggerJpFontHandle, SORT_LEFT, 480 + 200,
                                   true, GetColor(255, 0, 0));
        break;
    case 1:
        R_Text[3].DrawTextWithSort(0, 1920, "敵攻撃ダメージ増加", biggerJpFontHandle, SORT_LEFT, 480 + 200, true,
                                   GetColor(255, 0, 0));
        break;
    case 2:
        R_Text[3].DrawTextWithSort(0, 1920, "制限時間減少", biggerJpFontHandle, SORT_LEFT, 480 + 200, true,
                                   GetColor(255, 0, 0));
        break;
    default:
        R_Text[3].DrawTextWithSort(0, 1920, "なし", biggerJpFontHandle, SORT_LEFT, 480 + 200, true,
                                   GetColor(255, 255, 255));
        break;
    }
}

void stageEndless::EffectResult()
{
    switch (negativeResultType)
    {
    case 0:
        GoalRange += 300;
        player.forwardSpeed += 0.2f;
        enemy.forwardSpeed += 0.2f;
        break;
    case 1:
        enemy.BULLET_DAMAGE += 1;
        // enemy.MISSILE_DAMAGE += 5.0f;
        break;
    case 2:
        timeLimit -= 10;
        break;
    default:
        break;
    }
}

void stageEndless::ReflectToText()
{
    R_Value[0] = {timeLimit - missionTimer.GetElapsed(true)};
    R_Value[1] = {player.Health};
    R_Value[2] = {player.ammo};
    R_Value[3] = {enemy.Health};
    R_Value2[0] = {incleasedHealth};
    R_Value2[1] = {incleasedAmmo};
    R_Value2[2] = {healedHealth};
}

void stageEndless::HighScore()
{

    float score = Round - 1;
    FILE *file;
    // ハイスコア記録用のhs.datを開く
    errno_t err = fopen_s(&file, "data/hs.dat", "wb");
    // 問題なく開かれていれば書き込む
    if (err == 0)
    {
        fwrite(&score, sizeof(float), 1, file);
        fclose(file);
    }
    highScore = score;
}

void stageEndless::E_Pause()
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
    DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), 1);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    PauseControll();
    // リスタートが選ばれていたら
    if (isRestarting)
    {
        StopSoundMem(ingameBgm);
        // フェードアウトして初期化する
        if (fadeout(0.5f))
        {
            progress = 255;
            Init();
        }
    }
    // タイトルにもドルが選ばれていたら
    if (isQuitting)
    {
        StopSoundMem(ingameBgm);
        // フェードアウトしてタイトル画面を初期化する
        if (fadeout(0.5f))
        {
            progress = 255;
            Titleinitialize();
            scene = SCENE_TITLE;
        }
    }
}