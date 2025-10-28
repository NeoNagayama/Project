#include "stage1Scene.h"
#include "Input.h"
#include "ui.h"
#include "main.h"
#include "Clear.h"
#include "GameOver.h"
#include "TitleScene.h"
#include "Player.h"
#include "Map.h"
#define CLOSEDMOVERANGE 4
#define MOVERANGE 10
bool isStarted = true;
bool isCleared = false;
bool isDead = false;
bool isPause = false;
bool isKilled = false;
bool PauseControllable = true;
bool isRestarting = false;
bool isQuitting = false;
bool isObjectiveAppeared = false;
bool isGetDamage = false;

int gamePhase = 0;
int choosedButton;
int countDown = 3;
Button resume;
Button restart;
Button Stage1ToTitle;
Button Buttons[3];
Player player;
Enemy enemy;
mapBase maps[25];
antiAir AAs[25];
timer objectiveShowTimer;
timer CountDownTimer;
timer damageRate;
int obstacle[25];
int obstacleType[25];
enum Phase
{
    PHASE_RUN,
    PHASE_OVERSHOOT,
    PHASE_CHASE
};
enum pause
{
    PAUSE_RESUME,
    PAUSE_RESTART,
    PAUSE_EXIT
};
void Stage1InitialProcess()
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
    SetBackgroundColor(150, 160, 180, 50);
    for (int i = 8; i < 25; i++)
    {
        obstacle[i] = get_rand(0,25);
    }
    for (int i = 0; i < 25; i++)
    {
        obstacleType[i] = get_rand(0, 8);
    }
}
void Stage1MainProcess()
{
    SetShadowMapDrawArea(shadowHandle, VGet(-120.0f, -1.0f, -20.0f + player.BasePosition.z), VGet(120.0f, 240.0f, 220.0f + player.BasePosition.z));
    ShadowMap_DrawSetup(shadowHandle);
    MV1DrawModel(player.ModelHandle);
    MV1DrawModel(enemy.ModelHandle);
    ObstacleShadowDraw();
    ShadowMap_DrawEnd();
    DrawGraph3D(0, 500, player.BasePosition.z + 1000, backGroundHandle, false);
    SetUseShadowMap(0, shadowHandle);
    SetupCamera_Perspective(1);
    DrawBase();
    DrawObstacles();
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
        if (!isPause)
        {
            Ingame();
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
void Stage1Initialize()
{
    isStarted = true;
    isCleared = false;
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
    for (int i = 0; i < 25; i++)
    {
        if (i < 8)
        {
            obstacle[i] = 0;
        }
        else
        {
            obstacle[i] = get_rand(0, 25);
        }
    }
}
void Obstacle_Draw(int i ,int pos, bool upper, bool lower, bool right, bool left) 
{
    if (maps[pos].DamageBox(upper, lower, right, left, false, player.hitbox1, player.hitbox2) && !isStarted)
    {
        isDead = true;
    }
    if (i == 1)
    {
        enemy.minimumMoveRangeX = left ? -CLOSEDMOVERANGE : -MOVERANGE;
        enemy.minimumMoveRangeY = lower ? -CLOSEDMOVERANGE : -MOVERANGE;
        enemy.moveRangeX = right ? CLOSEDMOVERANGE : MOVERANGE;
        enemy.moveRangeY = upper ? CLOSEDMOVERANGE : MOVERANGE;
    }
    if (i == 2)
    {
        enemy.minimumMoveRangeX = left ? -CLOSEDMOVERANGE : enemy.minimumMoveRangeX;
        enemy.minimumMoveRangeY = lower ? -CLOSEDMOVERANGE : enemy.minimumMoveRangeY;
        enemy.moveRangeX = right ? CLOSEDMOVERANGE : enemy.moveRangeX;
        enemy.moveRangeY = upper ? CLOSEDMOVERANGE : enemy.moveRangeY;
    }
}
void AAGun_Draw(int i ,int pos, bool upper, bool lower, bool right, bool left)
{
    if (AAs[pos].DamageZone(upper, lower, right, left,player.hitbox1, player.hitbox2) && !isGetDamage)
    {
        player.Health -= 5;
        isGetDamage = true;
    }
    if (i == 1)
    {
        enemy.minimumMoveRangeX = left ? -CLOSEDMOVERANGE : -MOVERANGE;
        enemy.minimumMoveRangeY = lower ? -CLOSEDMOVERANGE : -MOVERANGE;
        enemy.moveRangeX = right ? CLOSEDMOVERANGE : MOVERANGE;
        enemy.moveRangeY = upper ? CLOSEDMOVERANGE : MOVERANGE;
    }
    if (i == 2)
    {
        enemy.minimumMoveRangeX = left ? -CLOSEDMOVERANGE : enemy.minimumMoveRangeX;
        enemy.minimumMoveRangeY = lower ? -CLOSEDMOVERANGE : enemy.minimumMoveRangeY;
        enemy.moveRangeX = right ? CLOSEDMOVERANGE : enemy.moveRangeX;
        enemy.moveRangeY = upper ? CLOSEDMOVERANGE : enemy.moveRangeY;
    }
}
void ObstacleShadowDraw()
{
    for (int i = 0; i < 15; i++)
    {
        int pos = i + ((int)player.BasePosition.z % 2000) / 80;
        if (pos > 24)
        {
            pos -= 25;
        }
        maps[pos].position.z = 80 * (i + (int)player.BasePosition.z / 80);
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
void DrawBase()
{
    for (int i = 14; i > -1; i--)
    {
        int pos = i + ((int)player.BasePosition.z % 2000) / 80;
        if (pos > 24)
        {
            pos -= 25;
        }
        maps[pos].position.z = 80 * (i + (int)player.BasePosition.z / 80);
        maps[pos].DrawbaseOutline();
    }
}
void DrawObstacles()
{

    for (int i = 14; i > -1; i--)
    {
        int pos = i + ((int)player.BasePosition.z % 2000) / 80;
        if (pos > 24)
        {
            pos -= 25;
        }
        maps[pos].position.z = 80 * (i + (int)player.BasePosition.z / 80);
        AAs[pos].position.z = 80 * (i + (int)player.BasePosition.z / 80);
        if (obstacleType[pos] < 2)
        {
            Obstacles(pos, i);
        }
        else
        {
            AAGuns(pos,i);
        }
        if (i == 14)
        {
            int t = 15 + ((int)player.BasePosition.z % 2000) / 80;
            obstacle[t > 24 ? t - 25 : t] = get_rand(0, 25);
            obstacleType[t > 24 ? t - 25 : t] = get_rand(0, 8);
        }


    }
}
void AAGuns(int pos, int i)
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
void Obstacles(int pos, int i)
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
void Briefing()
{
    player.transitionProcess(false);
    player.SetHitBox(2, 2);
    MV1DrawModel(player.ModelHandle);
    if (fadein(0.5f) && !isObjectiveAppeared)
    {
        progress = 0;
        isObjectiveAppeared = true;
    }
    if (isObjectiveAppeared && fadeInText(0, 1920, "クリア目標:攻撃を避けて生き残れ", biggerJpFontHandle, SORT_CENTER, 300, true, GetColor(255, 255, 255), GetColor(50, 50, 50), 0, 0.2f))
    {
        DrawTextWithSort(0, 1920, "クリア目標:攻撃を避けて生き残れ", biggerJpFontHandle, SORT_CENTER, 300, true, GetColor(255, 255, 255), GetColor(50, 50, 50));
        DrawTextWithSort(0, 1920, "スタートまで%d", biggerJpFontHandle, SORT_CENTER, 380, true, GetColor(255, 255, 255), GetColor(50, 50, 50), countDown);
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
            resetAlpha();
        }
    }
    isDead = false;
}
void Ingame()
{
    MV1DrawModel(player.ModelHandle);
    MV1DrawModel(enemy.ModelHandle);
    IngameToClear();
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
    DrawTextWithSort(120, 1920, "PLAYER HP: %d", fontHandle, SORT_LEFT, 500, true, GetColor(0, 255, 0), GetColor(50, 50, 50), player.Health);
    DrawTextWithSort(0, 1800, "ENEMY HP: %d", fontHandle, SORT_RIGHT, 500, true, GetColor(255, 0, 0), GetColor(50, 50, 50), enemy.Health);
    if (player.BasePosition.z > 4000.0f && gamePhase == PHASE_RUN)
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
        if (fadeout(1))
        {
            GameOverInitialize();
            progress = 0;
            scene = SCENE_GAMEOVER;
        }
    }
    if (isKilled)
    {
        if (fadeout(1))
        {
            ClearInitialize();
            progress = 0;
            scene = SCENE_CLEAR;
        }
    }
}
void IngameToClear()
{
    if (isCleared)
    {
        if (fadeout(1))
        {
            ClearInitialize();
            progress = 0;
            scene = SCENE_CLEAR;
        }
    }
}
void RunPhase()
{
    DrawTextWithSort(70, 1920, "目標:攻撃を避けて生き残れ", japaneseFontHandle, SORT_LEFT, 60, true, GetColor(0, 255, 0), GetColor(50, 50, 50));
    DrawBox(1780, 100, 1850, 980, GetColor(180, 180, 180), true, 1);
    DrawBox(1800, 100 + 880 - (880 * (player.BasePosition.z / 4000)), 1830, 980, GetColor(0, 255, 0), true);
    player.mainProcess(false);
    enemy.mainProcess(false);
}
void OverShootPhase()
{
    if (enemy.Transition())
    {
        isObjectiveAppeared = true;
        gamePhase = PHASE_CHASE;
    }
}
void ChasePhase()
{
    if (isObjectiveAppeared)
    {
        player.transitionProcess(true);
        if (fadeInText(0, 1920, "クリア目標:敵機を撃墜しろ", biggerJpFontHandle, SORT_CENTER, 300, true, GetColor(255, 255, 255), GetColor(50, 50, 50), 0, 0.2f))
        {
            DrawTextWithSort(0, 1920, "クリア目標:敵機を撃墜しろ", biggerJpFontHandle, SORT_CENTER, 300, true, GetColor(255, 255, 255), GetColor(50, 50, 50), 0);
            DrawTextWithSort(0, 1920, "スタートまで%d", biggerJpFontHandle, SORT_CENTER, 380, true, GetColor(255, 255, 255), GetColor(50, 50, 50), countDown);
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
                resetAlpha();
            }
        }
    }
    else
    {
        player.mainProcess(true);
    }
    DrawTextWithSort(70, 1920, "目標:敵機を撃墜しろ", japaneseFontHandle, SORT_LEFT, 60, true, GetColor(0, 255, 0), GetColor(50, 50, 50));
    enemy.mainProcess(true);
}
void PauseScreen()
{
    MV1DrawModel(player.ModelHandle);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
    DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), 1);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    PauseControll();
    if (isRestarting)
    {
        if (fadeout(0.5f))
        {
            progress = 255;
            Stage1Initialize();
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
void PauseControll()
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