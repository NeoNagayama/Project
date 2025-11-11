
#include "Stage.h"
#define CLOSEDMOVERANGE 4
#define MOVERANGE 10


void stage::InitialProcess(int obst[50],int type[50])
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
        obstacleDefault[i] = obst[i];
        obstacle[i] = obst[i];
        obstacleTypeDefault[i] = type[i];
        obstacleType[i] = type[i];
        moveWalls[i].SetUp();
        maps[i].BaseSetUp();
    }
}
void stage::MainProcess()
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
        if (!isPause &&!isCleared && !isGameOver )
        {
            Ingame();
        }
        else if (isCleared)
        {
            enemy.mainProcess(true);
            player.clearProcess();
            IngameToClear();
        }
        else if (isGameOver)
        {
            MV1DrawModel(enemy.ModelHandle);
            player.mainProcess(true);
            enemy.Position.z += 2;
            enemy.Move(enemy.Position);
            IngameToGameover();
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
void stage::Initialize()
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
    player.isDead = false;
    for (int i = 0; i < 50; i++)
    {
        obstacle[i] = obstacleDefault[i];
        obstacleType[i] = obstacleTypeDefault[i];
    }
    clearCameraOffsetx = 0;
    gameOverTimer.RestartTimer();
}
void stage::Obstacle_Draw(int i ,int pos, bool upper, bool lower, bool right, bool left)
{
    if (maps[pos].DamageBox(upper, lower, right, left, false, player.hitbox1, player.hitbox2) && !isStarted)
    {
        isDead = true;
        player.Health = 0;
    }
    if (i == 1 || i == 0)
    {
        enemy.minimumMoveRangeX = left ? -CLOSEDMOVERANGE : -MOVERANGE;
        enemy.minimumMoveRangeY = lower ? -CLOSEDMOVERANGE : -MOVERANGE;
        enemy.moveRangeX = right ? CLOSEDMOVERANGE : MOVERANGE;
        enemy.moveRangeY = upper ? CLOSEDMOVERANGE : MOVERANGE;
    }
    if (i == 2 || i == 3)
    {
        enemy.minimumMoveRangeX = left ? -CLOSEDMOVERANGE : enemy.minimumMoveRangeX;
        enemy.minimumMoveRangeY = lower ? -CLOSEDMOVERANGE : enemy.minimumMoveRangeY;
        enemy.moveRangeX = right ? CLOSEDMOVERANGE : enemy.moveRangeX;
        enemy.moveRangeY = upper ? CLOSEDMOVERANGE : enemy.moveRangeY;
    }
}
void stage::AAGun_Draw(int i ,int pos, bool upper, bool lower, bool right, bool left)
{
    if (AAs[pos].DamageZone(upper, lower, right, left,player.hitbox1, player.hitbox2) && !isGetDamage)
    {
        player.Health -= 5;
        isGetDamage = true;
    }
    if (i == 1 || i == 0)
    {
        enemy.minimumMoveRangeX = left ? -CLOSEDMOVERANGE : -MOVERANGE;
        enemy.minimumMoveRangeY = lower ? -CLOSEDMOVERANGE : -MOVERANGE;
        enemy.moveRangeX = right ? CLOSEDMOVERANGE : MOVERANGE;
        enemy.moveRangeY = upper ? CLOSEDMOVERANGE : MOVERANGE;
    }
    if (i == 2 || i==3)
    {
        enemy.minimumMoveRangeX = left ? -CLOSEDMOVERANGE : enemy.minimumMoveRangeX;
        enemy.minimumMoveRangeY = lower ? -CLOSEDMOVERANGE : enemy.minimumMoveRangeY;
        enemy.moveRangeX = right ? CLOSEDMOVERANGE : enemy.moveRangeX;
        enemy.moveRangeY = upper ? CLOSEDMOVERANGE : enemy.moveRangeY;
    }
}
void stage::MoveWallDraw(int i ,int pos, bool high,bool mid,bool low)
{
    if (moveWalls[pos].DrawMoveWall(high, mid, low, player.hitbox1, player.hitbox2))
    {
        isDead = true;
        player.Health = 0;
    }
    if (i == 1 || i == 0)
    {
        
        enemy.minimumMoveRangeY = low ? -CLOSEDMOVERANGE : -MOVERANGE;
        enemy.moveRangeY = high ? CLOSEDMOVERANGE : MOVERANGE;
    }
    if (i == 2 || i == 3)
    {
        enemy.minimumMoveRangeY = low ? -CLOSEDMOVERANGE : enemy.minimumMoveRangeY;
        enemy.moveRangeY = high ? CLOSEDMOVERANGE : enemy.moveRangeY;
    }
}
void stage::ObstacleShadowDraw()
{
    
    for (int i = 0; i < 15; i++)
    {
        int pos = i + ((int)player.Position.z % 4000) / 80;
        if (pos > 49)
        {
            pos -= 50;
        }
        maps[pos].position.z = 80 * (i + (int)player.Position.z / 80);
        maps[pos].DrawbaseOutline();

        if (obstacleType[pos] < 2)
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
void stage::moveWallShadow()
{
    for (int i = 0; i < 15; i++)
    {
        int pos = i + ((int)player.Position.z % 4000) / 80;
        if (pos > 49)
        {
            pos -= 50;
        }
        moveWalls[pos].position.z = 80 * (i + (int)player.Position.z / 80);
        moveWalls[pos].DrawbaseOutline();


        switch (obstacle[pos]) {
        case HIGH:
            moveWalls[pos].DrawMoveWall(true, false, false, player.hitbox1, player.hitbox2);
            break;
        case MID:
            moveWalls[pos].DrawMoveWall(false, true, false, player.hitbox1, player.hitbox2);
            break;
        case LOW:
            moveWalls[pos].DrawMoveWall(false, false, true, player.hitbox1, player.hitbox2);
            break;
        /*case HIGH_MID:
            moveWalls[pos].DrawMoveWall(true, true, false, player.hitbox1, player.hitbox2);
            break;
        case HIGH_LOW:
            moveWalls[pos].DrawMoveWall(true, false, true, player.hitbox1, player.hitbox2);
            break;*/
        default:
            moveWalls[pos].DrawMoveWall(false, false, false, player.hitbox1, player.hitbox2);
            break;
        }

    }
}
void stage::DrawBase()
{
    for (int i = 14; i > -1; i--)
    {
        int pos = i + ((int)player.Position.z % 4000) / 80;
        if (pos > 49)
        {
            pos -= 50;
        }
        maps[pos].position.z = 80 * (i + (int)player.Position.z / 80);
        maps[pos].DrawbaseOutline();
    }
}
void stage::DrawObstacles()
{

    for (int i = 14; i > -1; i--)
    {
        int pos = i + ((int)player.Position.z % 4000) / 80;
        if (pos > 49)
        {
            pos -= 50;
        }
        maps[pos].position.z = 80 * (i + (int)player.Position.z / 80);
        AAs[pos].position.z = 80 * (i + (int)player.Position.z / 80);
        moveWalls[pos].position.z = 80 * (i + (int)player.Position.z / 80);
        if (obstacleType[pos] < 2)
        {
            Obstacles(pos, i);
        }
        else
        {
            AAGuns(pos,i);
        }
        MoveWalls(pos, i);
        if (i == 14)
        {
            int t = 15 + ((int)player.Position.z % 4000) / 80;
            obstacle[t > 49 ? t - 50 : t] = get_rand(0, 25);
            obstacleType[t > 49 ? t - 50 : t] = get_rand(0, 8);
        }


    }
}
void stage::AAGuns(int pos, int i)
{

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
    switch (obstacle[pos]) {
    case HIGH:
        MoveWallDraw(i, pos, true, false, false);
        break;
    case MID:
        MoveWallDraw(i, pos, false, true, false);
        break;
    case LOW:
        MoveWallDraw(i, pos, false, false, true);
        break;
    /*case HIGH_MID:
        MoveWallDraw(i, pos, true, true, false);
        break;
    case HIGH_LOW:
        MoveWallDraw(i, pos, true, false, true);
        break;*/
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
    player.SetHitBox(2, 2);
    if (fadein(0.5f) && !isObjectiveAppeared)
    {
        progress = 0;
        isObjectiveAppeared = true;
    }
    if (isObjectiveAppeared && objectiveText.fadeInText(0, 1920, "クリア目標:攻撃を避けて生き残れ", biggerJpFontHandle, SORT_CENTER, 300, true, GetColor(255, 255, 255), GetColor(50, 50, 50), 0, 0.2f))
    {
        objectiveText.DrawTextWithSort(0, 1920, "クリア目標:攻撃を避けて生き残れ", biggerJpFontHandle, SORT_CENTER, 300, true, GetColor(255, 255, 255), GetColor(50, 50, 50));
        countDownText.DrawTextWithSort(0, 1920, "%d", CountDownFontHandle, SORT_CENTER, 450, true, GetColor(255, 255, 30), GetColor(50, 50, 50), countDown);
        if (CountDownTimer.MeasureTimer(1))
        {
            CountDownTimer.RestartTimer();
            countDown -= 1;
        }
        if (objectiveShowTimer.MeasureTimer(3))
        {
            isStarted = false;
            isObjectiveAppeared = false;
            objectiveShowTimer.RestartTimer();
            CountDownTimer.RestartTimer();
            countDown = 3;
            objectiveText.resetAlpha();
        }
    }
    isDead = false;
}
void stage::Ingame()
{
    //IngameToClear();
    if (player.ammo < 1 || player.Health <= 0)
    {
        player.Health = 0;
        isDead = true;
    }
    if (enemy.Health <= 0)
    {
        enemy.Health = 0;
        isKilled = true;
    }
    playerHealthText.DrawTextWithSort(120, 1920, "PLAYER HP: %d", fontHandle, SORT_LEFT, 500, true, GetColor(0, 255, 0), GetColor(50, 50, 50), player.Health);
    enemyHealthText.DrawTextWithSort(0, 1800, "ENEMY HP: %d", fontHandle, SORT_RIGHT, 500, true, GetColor(255, 0, 0), GetColor(50, 50, 50), enemy.Health);
    if (player.BasePosition.z > 400.0f && gamePhase == PHASE_RUN)
    {
        gamePhase = PHASE_OVERSHOOT;
    }
    else if (gamePhase == PHASE_RUN)
    {
        RunPhase();
    }
    if (gamePhase == PHASE_OVERSHOOT)
    {
        OverShootPhase();
    }
    if (gamePhase == PHASE_CHASE)
    {
        ChasePhase();
    }
    if (isDead)
    {
        isGameOver = true;
        GameOverInitialize();
    }
    if (isKilled)
    {
        isCleared = true;
        ClearInitialize();
        /*if (fadeout(3))
        {
            ClearInitialize();
            progress = 0;
            scene = SCENE_CLEAR;
        }*/
    }
}
void stage::IngameToClear()
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
        clsDx();
        printfDx("%f %f %f", cameraDirection.x, cameraDirection.y, cameraDirection.z);
        ClearMainProcess();
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
void stage::IngameToGameover()
{
    if (gameOverTimer.MeasureTimer(1.0f))
    {

        GameOverMainProcess();
    }
}
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
    objectiveText.DrawTextWithSort(70, 1920, "目標:攻撃を避けて生き残れ", japaneseFontHandle, SORT_LEFT, 60, true, GetColor(0, 255, 0), GetColor(50, 50, 50));
    DrawGraph(1400, 0, gaugeHandle, true);
    DrawRectGraph(1400, 43+(994-(994*(player.BasePosition.z / 4000))), 0, 43 + (994 - (994 * (player.BasePosition.z / 4000))), 300, 1080, barHandle, true);
    /*
    DrawBox(1780, 100, 1850, 980, GetColor(180, 180, 180), true, 1);
    DrawBox(1800, 100 + 880 - (880 * (player.BasePosition.z / 4000)), 1830, 980, GetColor(0, 255, 0), true);*/
    player.mainProcess(false);
    enemy.mainProcess(false);
}
void stage::OverShootPhase()
{
    if (enemy.Transition())
    {
        isObjectiveAppeared = true;
        gamePhase = PHASE_CHASE;
    }
}
void stage::ChasePhase()
{
    if (isObjectiveAppeared)
    {
        player.transitionProcess(true);
        if (objectiveText.fadeInText(0, 1920, "クリア目標:敵機を撃墜しろ", biggerJpFontHandle, SORT_CENTER, 300, true, GetColor(255, 255, 255), GetColor(50, 50, 50), 0, 0.2f))
        {
            objectiveText.DrawTextWithSort(0, 1920, "クリア目標:敵機を撃墜しろ", biggerJpFontHandle, SORT_CENTER, 300, true, GetColor(255, 255, 255), GetColor(50, 50, 50), 0);
            countDownText.DrawTextWithSort(0, 1920, "%d", CountDownFontHandle, SORT_CENTER, 450, true, GetColor(255, 255, 30), GetColor(50, 50, 50), countDown);
            if (CountDownTimer.MeasureTimer(1))
            {
                CountDownTimer.RestartTimer();
                countDown -= 1;
            }
            if (objectiveShowTimer.MeasureTimer(3))
            {
                isObjectiveAppeared = false;
                countDown = 3;
                objectiveShowTimer.RestartTimer();
                CountDownTimer.RestartTimer();
                objectiveText.resetAlpha();
            }
        }
    }
    else
    {
        DrawExtendGraph(300, 0,1620,206, E_gauge, true);
        DrawRectExtendGraph(300 + (1920 - (1920 * ((float)enemy.Health / 100))),0, 1620,206,71,0, 1920 * ((float)enemy.Health / 100), 300, E_bar, true);
        player.mainProcess(true);
    }
    objectiveText.DrawTextWithSort(70, 1920, "目標:敵機を撃墜しろ", japaneseFontHandle, SORT_LEFT, 60, true, GetColor(0, 255, 0), GetColor(50, 50, 50));
    enemy.mainProcess(true);
}
void stage::PauseScreen()
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
    DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), 1);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    PauseControll();
    if (isRestarting)
    {
        if (fadeout(0.5f))
        {
            progress = 255;
            Initialize();
        }
    }
    if (isQuitting)
    {
        if (fadeout(0.5f))
        {
            progress = 255;
            Titleinitialize();
            scene = SCENE_TITLE;
        }
    }
}
void stage::PauseControll()
{
    for (int i = 0; i < 3; i++)
    {
        Buttons[i].mainProcess(choosedButton == i, true, 40);
    }
    switch (choosedButton) {
    case PAUSE_RESUME:
        if (Input_GetKeyboardDown(KEY_INPUT_SPACE))
        {
            isPause = false;
            choosedButton = 0;
        }
        break;
    case PAUSE_RESTART:
        if (Input_GetKeyboardDown(KEY_INPUT_SPACE))
        {
            PauseControllable = false;
            isRestarting = true;
        }
        break;
    default:
        if (Input_GetKeyboardDown(KEY_INPUT_SPACE))
        {
            isQuitting = true;
            PauseControllable = false;
        }
        break;
    }
    if (PauseControllable)
    {
        if (Input_GetKeyboardDown(KEY_INPUT_W) && choosedButton > 0)
        {
            choosedButton--;
        }
        if (Input_GetKeyboardDown(KEY_INPUT_S) && choosedButton < 2)
        {
            choosedButton++;
        }
    }
}