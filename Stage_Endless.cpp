#include "Stage_Endless.h"
void stageEndless::SetUp()
{
    resume.SetButtonPosition(VGet(960, 540, 1), 400, 100, 0.9f);
    restart.SetButtonPosition(VGet(960, 740, 1), 400, 100, 0.9f);
    Stage1ToTitle.SetButtonPosition(VGet(960, 940, 1), 400, 100, 0.9f);
    Buttons[0] = resume;
    Buttons[1] = restart;
    Buttons[2] = Stage1ToTitle;
    Buttons[0].SetText("Resume");
    Buttons[1].SetText("Restart");
    Buttons[2].SetText("Quit");
    player.InitialProcess();
    enemy.InitialProcess();
    player.EnemySet(&enemy);
    enemy.PlayerSet(&player);
    for (int i = 0; i < 50; i++)
    {
        moveWalls[i].SetUp();
        maps[i].BaseSetUp();
    }
    for (int i = 0; i < 10; i++)
    {
        backWards[i].BaseSetUp();
    }
    StageRandomize();
}
void stageEndless::Init()
{
    player.Init();
    enemy.Init();
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
    stageLength = 4000;
    GoalRange = 0;
    baseAmmo = 200;
    baseHealth = 200;
    Round = 1;
    clearCameraOffsetx = 0;
    StageRandomize();
    isSaved = false;
    startPosZ = 0;
}
void stageEndless::StartWave()
{
    enemy.Init();
    gamePhase = PHASE_RUN;
    Round += 1;
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
    stageLength = player.Position.z + GoalRange;
    startPosZ = player.Position.z + 200;
    player.camSetUp(startPosZ);
}
void stageEndless::StageRandomize()
{
    for (int i = 0; i < 50; i++)
    {
        obstacle[i] = get_rand(0, 17);
        obstacleType[i] = get_rand(0, 5);
        moveWallType[i] = get_rand(0, 12);
    }
}
void stageEndless::main()
{
    SetShadowMapDrawArea(shadowHandle, VGet(-120.0f, -1.0f, -220.0f + player.CameraPosition.z), VGet(120.0f, 240.0f, 220.0f + player.CameraPosition.z));
    ShadowMap_DrawSetup(shadowHandle);
    MV1DrawModel(player.ModelHandle);
    MV1DrawModel(enemy.ModelHandle);
    if (isStarted)
    {
        DrawBackWards();
    }
    ObstacleShadowDraw();
    moveWallShadow();
    ShadowMap_DrawEnd();
    DrawGraph3D(0, 500, player.Position.z + 1000, backGroundHandle, false);
    MV1DrawModel(player.ModelHandle);
    MV1DrawModel(enemy.ModelHandle);
    SetUseShadowMap(0, shadowHandle);
    DrawBase();
    DrawObstacles();
    RoundCount.DrawTextWithSort(0, 1650, "ラウンド:%.f", japaneseFontHandle, SORT_RIGHT, 90, false, GetColor(0, 255, 0), GetColor(50, 50, 50), (float)Round);
    if (isGetDamage)
    {
        if (damageRate.MeasureTimer(0.5f))
        {
            isGetDamage = false;
            damageRate.RestartTimer();
        }
    }
    if (isStarted)
    {
        DrawGraph3D(0, 500, player.Position.z - 1000, backGroundHandle, false);
        DrawBackWards();
        enemy.Move(VGet(0, -3, player.Position.z - 120));
        Briefing();
        if (0 == CheckSoundMem(engineSound))
        {
            PlaySoundMem(engineSound, DX_PLAYTYPE_LOOP);
        }
    }
    else
    {
        SetupCamera_Perspective(1);
        if (!isPause && !isCleared && !isGameOver)
        {
            Ingame();
            if (0 == CheckSoundMem(engineSound))
            {
                PlaySoundMem(engineSound, DX_PLAYTYPE_LOOP);
            }
        }
        else if (isCleared)
        {
            enemy.mainProcess(true);
            player.clearProcess();
            WaveResult();
            if (0 == CheckSoundMem(engineSound))
            {
                PlaySoundMem(engineSound, DX_PLAYTYPE_LOOP);
            }
        }
        else if (isGameOver)
        {
            player.mainProcess(true);
            enemy.Position.z += 2;
            enemy.Move(enemy.Position);
            IngameToGameoverModified();

            if (1 == CheckSoundMem(engineSound))
            {
                StopSoundMem(engineSound);
            }
        }
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
    SetLightPositionHandle(playerLight, VAdd(VScale(VGet(-player.forward().x, player.forward().y, -player.forward().z), 5), player.Position));
    SetLightPositionHandle(enemyLight, VAdd(MV1GetPosition(enemy.ModelHandle), VGet(0, 0, -5)));
}
void stageEndless::IngameToGameoverModified()
{
    if (gameOverTimer.MeasureTimer(1.0f))
    {
        EndlessGameOver(Round);
    }
    if (!isSaved && highScore <= Round)
    {
        HighScore();
        isSaved = true;
    }
}
void stageEndless::WaveResult()
{
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
        if (clearCameraOffsetx > -9)
        {
            clearCameraOffsetx = clearCameraOffsetx - smooth(clearCameraOffsetx, -9, 120);
        }
        else
        {
            clearCameraOffsetx = -9;
        }
        //CameraTargetMove();
        cameraDirection = VAdd(VGet(0, 1, 8), player.BasePosition);
        SetCameraPositionAndTarget_UpVecY(VAdd(VGet(clearCameraOffsetx, player.offset.y + 2, -4), player.BasePosition),
            cameraDirection);
        ShowResult();
    }
    else
    {
        if (enemy.deadPosition.y < player.Position.y)
        {
            SetCameraPositionAndTarget_UpVecY(VAdd(VGet(enemy.offset.x + 3, 0, -15), enemy.BasePosition),
                VAdd(VGet(enemy.offset.x, enemy.offset.y, 0), enemy.BasePosition));
        }
        else
        {
            SetCameraPositionAndTarget_UpVecY(VAdd(VGet(enemy.offset.x + 3, 0, -15), enemy.BasePosition),
                VAdd(VGet(enemy.offset.x, enemy.offset.y, 0), enemy.BasePosition));
        }
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
        GoalRange = 40;
    }
    ReflectToText();
    if (R_Timer.MeasureTimer(0.5f) && resultStage < 4)
    {
        resultStage += 1;
        R_Timer.RestartTimer();
    }
    if (!isGetResult)
    {
        for (int i = 0; i < resultStage; i++)
        {
            R_Text[i].DrawTextWithSort(0, 1920, R_info[i], biggerJpFontHandle, SORT_LEFT, i * 120 + 200, true, GetColor(255, 255, 255), GetColor(50, 50, 50), R_Value[i]);

        }
    }
    if (isGetResult)
    {
        for (int i = 0; i < resultStage; i++)
        {
            if (i < 3)
            {
                R_Text[i].DrawTextWithSort(0, 1920, R_info2[i], biggerJpFontHandle, SORT_LEFT, i * 120 + 200, true, GetColor(255, 255, 255), GetColor(50, 50, 50), R_Value2[i]);
            }
            else if (i < 4)
            {
                ResultType();
            }
        }
        if (R_Timer.MeasureTimer(5.0f))
        {
            StartWave();
            isGetResult = false;
            resultStage = 0;
            R_Timer.RestartTimer();
        }
    }
    if (!isGetResult && R_Timer.MeasureTimer(10.0f))
    {
        baseHealthCache = 20 * (player.ammo / (baseAmmo-50));
        incleasedHealth = 20 * (player.ammo / (baseAmmo - 50));
        baseAmmoCache = 30 * (player.Health / baseHealth);
        incleasedAmmo = 30 * (player.Health / baseHealth);
        player.Health += (baseHealth * (player.ammo / (baseAmmo - 50)));
        healedHealth = (baseHealth * (player.ammo / (baseAmmo - 50)));
        baseHealth += baseHealthCache;
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
        R_Text[3].DrawTextWithSort(0, 1920, "移動速度増加＆ゴール距離増加", biggerJpFontHandle, SORT_LEFT, 480 + 200, true, GetColor(255, 0, 0));
        break;
    case 1:
        R_Text[3].DrawTextWithSort(0, 1920, "敵攻撃ダメージ増加", biggerJpFontHandle, SORT_LEFT, 480 + 200, true, GetColor(255, 0, 0));
        break;
    case 2:
        R_Text[3].DrawTextWithSort(0, 1920, "制限時間減少", biggerJpFontHandle, SORT_LEFT, 480 + 200, true, GetColor(255, 0, 0));
        break;
    default:
        R_Text[3].DrawTextWithSort(0, 1920, "なし", biggerJpFontHandle, SORT_LEFT, 480 + 200, true, GetColor(255, 255, 255));
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
        enemy.MISSILE_DAMAGE += 5;
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
    R_Value[0] = {timeLimit - missionTimer.GetElapsed(true) };
    R_Value[1] = { player.Health };
    R_Value[2] = { player.ammo };
    R_Value[3] = { enemy.Health };
    R_Value2[0] = { incleasedHealth };
    R_Value2[1] = { incleasedAmmo };
    R_Value2[2] = { healedHealth };
}
void stageEndless::HighScore()
{
    int score = Round-1;
    FILE* file;
    errno_t err = fopen_s(&file, "data/hs.dat", "wb");
    fwrite(&score, sizeof(float), 1, file);
    fclose(file);
    highScore = score;
}
void stageEndless::E_Pause()
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
    DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), 1);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    PauseControll();
    if (isRestarting)
    {
        StopSoundMem(ingameBgm);
        if (fadeout(0.5f))
        {
            progress = 255;
            Init();
        }
    }
    if (isQuitting)
    {
        StopSoundMem(ingameBgm);
        if (fadeout(0.5f))
        {
            progress = 255;
            Titleinitialize();
            scene = SCENE_TITLE;
        }
    }
}