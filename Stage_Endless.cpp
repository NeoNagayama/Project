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
    StageRandomize();
}
void stageEndless::StartWave()
{

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