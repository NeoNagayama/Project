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
    StageRandomize();
}
void stageEndless::Init()
{
    isStarted = true;
    isCleared = false;
    isGameOver = false;
    isDead = false;
    isPause = false;
    isRestarting = false;
    PauseControllable = true;
    isQuitting = false;
    player.ammo = 200;
    choosedButton = 0;
    player.Health = 100;
    enemy.Health = 100;
    player.offset = VGet(0, -5, 0);
    player.BasePosition.z = 0;
    gamePhase = 0;
    isKilled = false;
    enemy.transitionMoveZaxis = -50.0f;
    enemy.missilecooldowntimer = 0;
    enemy.missileflyingTimer = 0;
    enemy.isLaunched = false;
    enemy.isFiring = false;
    enemy.cobraSpeed = 0;
    player.isDead = false;
    stageLength = 4000;
    enemy.Health = 2;
    player.forwardSpeed = 2;
    enemy. forwardSpeed = 2;
    baseAmmo = 200;
    baseHealth = 200;
    Round = 1;
    clearCameraOffsetx = 0;
    StageRandomize();
}
void stageEndless::StartWave()
{
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
    enemy.Health = 2;
    enemy.transitionMoveZaxis = -50.0f;
    enemy.missilecooldowntimer = 0;
    enemy.missileflyingTimer = 0;
    enemy.isLaunched = false;
    enemy.isFiring = false;
    enemy.cobraSpeed = 0;
    clearCameraOffsetx = 0;
    stageLength += player.Position.z + GoalRange;
}
void stageEndless::StageRandomize()
{
    for (int i = 0; i < 50; i++)
    {
        obstacle[i] = get_rand(0, 25);
        obstacleType[i] = get_rand(0, 8);
        moveWallType[i] = get_rand(0, 10);
    }
}
void stageEndless::main()
{
    
    SetShadowMapDrawArea(shadowHandle, VGet(-120.0f, -1.0f, -20.0f + player.Position.z), VGet(120.0f, 240.0f, 220.0f + player.Position.z));
    ShadowMap_DrawSetup(shadowHandle);
    if (player.Health > 0)
    {
        MV1DrawModel(player.ModelHandle);
    }
    if (enemy.Health > 0 && !isStarted)
    {
        MV1DrawModel(enemy.ModelHandle);
    }
    ObstacleShadowDraw();
    moveWallShadow();
    ShadowMap_DrawEnd();
    DrawGraph3D(0, 500, player.Position.z + 1000, backGroundHandle, false);
    SetUseShadowMap(0, shadowHandle);
    SetupCamera_Perspective(1);
    DrawBase();
    DrawObstacles();
    RoundCount.DrawTextWithSort(0, 1850, "ラウンド:%.f", japaneseFontHandle, SORT_RIGHT, 90, false, GetColor(0, 255, 0), GetColor(50, 50, 50), (float)Round);
    if (player.Health > 0 && !isCleared)
    {
        MV1DrawModel(player.ModelHandle);
    }
    if (enemy.Health > 0 && !isStarted)
    {
        MV1DrawModel(enemy.ModelHandle);
    }
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
        Briefing();
    }
    else
    {
        if (!isPause && !isCleared && !isGameOver)
        {
            Ingame();
        }
        else if (isCleared)
        {
            enemy.mainProcess(true);
            player.clearProcess();
            WaveResult();
        }
        else if (isGameOver)
        {
            MV1DrawModel(enemy.ModelHandle);
            player.mainProcess(true);
            enemy.Position.z += 2;
            enemy.Move(enemy.Position);
            IngameToGameoverModified();
        }
        else
        {
            PauseScreen();
        }
        if (Input_GetKeyboardDown(KEY_INPUT_ESCAPE))
        {
            isPause = isPause ? false : true;
            choosedButton = 0;
        }
    }
}
void stageEndless::IngameToGameoverModified()
{
    if (gameOverTimer.MeasureTimer(1.0f))
    {
        EndlessGameOver(Round);
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
        MV1DrawModel(player.ModelHandle);
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
        MV1DrawModel(player.ModelHandle);
        if (enemy.deadPosition.y < player.Position.y)
        {
            SetCameraPositionAndTarget_UpVecY(VAdd(VGet(player.offset.x, player.offset.y - 2, -5), player.BasePosition),
                enemy.deadPosition);
        }
        else
        {
            SetCameraPositionAndTarget_UpVecY(VAdd(VGet(player.offset.x, player.offset.y + 2, -5), player.BasePosition),
                enemy.deadPosition);
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