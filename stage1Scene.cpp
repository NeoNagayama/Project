#include "stage1Scene.h"
#include "DxLib.h"
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
int gamePhase = 0;
int choosedButton;
Button resume;
Button restart;
Button Stage1ToTitle;
Button Buttons[3];
Player player;
Enemy enemy;
mapBase maps[25];
int obstacle[25];
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
    for (int i = 4; i < 25; i++)
    {
        obstacle[i] = get_rand(0,25);
    }
}
void Stage1MainProcess()
{
    
    for (int i = 0; i <  15; i++)
    {
        int pos = i + ((int)player.BasePosition.z % 2000) / 80;
        if (pos > 24)
        {
            pos -= 25;
        }
        maps[pos].position.z = 80*(i + (int)player.BasePosition.z/80);
        maps[pos].DrawbaseOutline();
        switch (obstacle[pos]){
        case CENTER:
            if (maps[pos].DamageBox(false, false, false, false, false,player.hitbox1,player.hitbox2) && !isStarted)
            {
                isDead = true;
            }
            if (i == 1)
            {
                enemy.moveRangeX = MOVERANGE;
                enemy.minimumMoveRangeX = -MOVERANGE;
                enemy.moveRangeY = MOVERANGE;
                enemy.minimumMoveRangeY = -MOVERANGE;
            }
            break;
        case UPPER:
            if (maps[pos].DamageBox(true, false, false, false, false, player.hitbox1, player.hitbox2) && !isStarted)
            {

                isDead = true;
            }
            if (i == 1)
            {
                enemy.moveRangeX = MOVERANGE;
                enemy.minimumMoveRangeX = -MOVERANGE;
                enemy.moveRangeY = CLOSEDMOVERANGE;
                enemy.minimumMoveRangeY = -MOVERANGE;
            }
            if (i == 2)
            {
                enemy.moveRangeY = CLOSEDMOVERANGE;
            }
            break;
        case LOWER:
            if (maps[pos].DamageBox(false, true, false, false, false, player.hitbox1, player.hitbox2) && !isStarted)
            {

                isDead = true;
            }
            if (i == 1)
            {
                enemy.moveRangeX = MOVERANGE;
                enemy.minimumMoveRangeX = -MOVERANGE;
                enemy.moveRangeY = MOVERANGE;
                enemy.minimumMoveRangeY = -CLOSEDMOVERANGE;
            }
            if (i == 2)
            {
                enemy.minimumMoveRangeY = -CLOSEDMOVERANGE;
            }
            break;
        case RIGHT:
            if (maps[pos].DamageBox(false, false, true, false, false, player.hitbox1, player.hitbox2) && !isStarted)
            {

                isDead = true;
            }
            if (i == 1)
            {
                enemy.moveRangeX = CLOSEDMOVERANGE;
                enemy.minimumMoveRangeX = -MOVERANGE;
                enemy.moveRangeY = MOVERANGE;
                enemy.minimumMoveRangeY = -MOVERANGE;
            }
            if (i == 2)
            {
                enemy.moveRangeX = CLOSEDMOVERANGE;
            }
            break;
        case LEFT:
            if (maps[pos].DamageBox(false, false, false, true, false, player.hitbox1, player.hitbox2) && !isStarted)
            {

                isDead = true;
            }
            if (i == 1)
            {
                enemy.moveRangeX = MOVERANGE;
                enemy.minimumMoveRangeX = -CLOSEDMOVERANGE;
                enemy.moveRangeY = MOVERANGE;
                enemy.minimumMoveRangeY = -MOVERANGE;
            }
            if (i == 2)
            {
                enemy.minimumMoveRangeX = -CLOSEDMOVERANGE;
            }
            break;
        case UPPER_LOWER:
            if (maps[pos].DamageBox(true, true, false, false, false, player.hitbox1, player.hitbox2) && !isStarted)
            {

                isDead = true;
            }
            if (i == 1)
            {
                enemy.moveRangeX = MOVERANGE;
                enemy.minimumMoveRangeX = -MOVERANGE;
                enemy.moveRangeY = CLOSEDMOVERANGE;
                enemy.minimumMoveRangeY = -CLOSEDMOVERANGE;
            }
            if (i == 2)
            {
                enemy.moveRangeY = CLOSEDMOVERANGE;
                enemy.minimumMoveRangeY = -CLOSEDMOVERANGE;
            }
            break;
        case UPPER_RIGHT:
            if (maps[pos].DamageBox(true, false, true, false, false, player.hitbox1, player.hitbox2) && !isStarted)
            {

                isDead = true;
            }
            if (i == 1)
            {
                enemy.moveRangeX = CLOSEDMOVERANGE;
                enemy.minimumMoveRangeX = -MOVERANGE;
                enemy.moveRangeY = CLOSEDMOVERANGE;
                enemy.minimumMoveRangeY = -MOVERANGE;
            }
            if (i == 2)
            {
                enemy.moveRangeX = CLOSEDMOVERANGE;
                enemy.moveRangeY = CLOSEDMOVERANGE;
            }
            break;
        case UPPER_LEFT:
            if (maps[pos].DamageBox(true, false, false, true, false, player.hitbox1, player.hitbox2) && !isStarted)
            {

                isDead = true;
            }
            if (i == 1)
            {
                enemy.moveRangeX = MOVERANGE;
                enemy.minimumMoveRangeX = -CLOSEDMOVERANGE;
                enemy.moveRangeY = CLOSEDMOVERANGE;
                enemy.minimumMoveRangeY = -MOVERANGE;
            }
            if (i == 2)
            {
                enemy.minimumMoveRangeX = -CLOSEDMOVERANGE;
                enemy.moveRangeY = CLOSEDMOVERANGE;
            }
            break;
        case UPPER_CENTER:
            if (maps[pos].DamageBox(true, false, false, false, false, player.hitbox1, player.hitbox2) && !isStarted)
            {

                isDead = true;
            }
            if (i == 1)
            {
                enemy.moveRangeX = MOVERANGE;
                enemy.minimumMoveRangeX = -MOVERANGE;
                enemy.moveRangeY = CLOSEDMOVERANGE;
                enemy.minimumMoveRangeY = -MOVERANGE;
            }
            if (i == 2)
            {
                enemy.moveRangeY = CLOSEDMOVERANGE;
            }
            break;
        case LOWER_RIGHT:
            if (maps[pos].DamageBox(false, true, true, false, false, player.hitbox1, player.hitbox2) && !isStarted)
            {

                isDead = true;
            }
            if (i == 1)
            {
                enemy.moveRangeX = CLOSEDMOVERANGE;
                enemy.minimumMoveRangeX = -MOVERANGE;
                enemy.moveRangeY = MOVERANGE;
                enemy.minimumMoveRangeY = -CLOSEDMOVERANGE;
            }
            if (i == 2)
            {
                enemy.moveRangeX = CLOSEDMOVERANGE;
                enemy.minimumMoveRangeY = -CLOSEDMOVERANGE;
            }
            break;
        case LOWER_LEFT:
            if (maps[pos].DamageBox(false, true, false, true, false, player.hitbox1, player.hitbox2) && !isStarted)
            {

                isDead = true;
            }
            if (i == 1)
            {
                enemy.moveRangeX = MOVERANGE;
                enemy.minimumMoveRangeX = -CLOSEDMOVERANGE;
                enemy.moveRangeY = MOVERANGE;
                enemy.minimumMoveRangeY = -CLOSEDMOVERANGE;
            }
            if (i == 2)
            {
                enemy.minimumMoveRangeX = -CLOSEDMOVERANGE;
                enemy.minimumMoveRangeY = -CLOSEDMOVERANGE;
            }
            break;
        case LOWER_CENTER:
            if (maps[pos].DamageBox(false, true, false, false, false, player.hitbox1, player.hitbox2) && !isStarted)
            {

                isDead = true;
            }
            if (i == 1)
            {
                enemy.moveRangeX = MOVERANGE;
                enemy.minimumMoveRangeX = -MOVERANGE;
                enemy.moveRangeY = MOVERANGE;
                enemy.minimumMoveRangeY = -CLOSEDMOVERANGE;
            }
            if (i == 2)
            {
                enemy.minimumMoveRangeY = -CLOSEDMOVERANGE;
            }
            break;
        case RIGHT_LEFT:
            if (maps[pos].DamageBox(false, false, true, true, false, player.hitbox1, player.hitbox2) && !isStarted)
            {

                isDead = true;
            }
            if (i == 1)
            {
                enemy.moveRangeX = CLOSEDMOVERANGE;
                enemy.minimumMoveRangeX = -CLOSEDMOVERANGE;
                enemy.moveRangeY = MOVERANGE;
                enemy.minimumMoveRangeY = -MOVERANGE;
            }
            if (i == 2)
            {
                enemy.moveRangeX = CLOSEDMOVERANGE;
                enemy.minimumMoveRangeX = -CLOSEDMOVERANGE;
            }
            break;
        case RIGHT_CENTER:
            if (maps[pos].DamageBox(false, false, true, false, false, player.hitbox1, player.hitbox2) && !isStarted)
            {

                isDead = true;
            }
            if (i == 1)
            {
                enemy.moveRangeX = CLOSEDMOVERANGE;
                enemy.minimumMoveRangeX = -MOVERANGE;
                enemy.moveRangeY = MOVERANGE;
                enemy.minimumMoveRangeY = -MOVERANGE;
            }
            if (i == 2)
            {
                enemy.moveRangeX = CLOSEDMOVERANGE;
            }
            break;
        case LEFT_CENTER:
            if (maps[pos].DamageBox(false, false, false, true, false, player.hitbox1, player.hitbox2) && !isStarted)
            {

                isDead = true;
            }
            if (i == 1)
            {
                enemy.moveRangeX = MOVERANGE;
                enemy.minimumMoveRangeX = -CLOSEDMOVERANGE;
                enemy.moveRangeY = MOVERANGE;
                enemy.minimumMoveRangeY = -MOVERANGE;
            }
            if (i == 2)
            {
                enemy.minimumMoveRangeX = -CLOSEDMOVERANGE;
            }
            break;
        default:
            if (i == 1)
            {
                enemy.moveRangeX = MOVERANGE;
                enemy.minimumMoveRangeX = -MOVERANGE;
                enemy.moveRangeY = MOVERANGE;
                enemy.minimumMoveRangeY = -MOVERANGE;
            }
            break;
        }
        if (i == 14)
        {
            int t = 15 + ((int)player.BasePosition.z % 2000) / 80;
            obstacle[t > 24 ? t - 25 : t] = get_rand(0, 20);
        }
    }
    if (isStarted)
    {
        MV1SetPosition(player.ModelHandle, VGet(0, -5, 0));
        SetCameraPositionAndTarget_UpVecY(VGet(0, 0, -25), VGet(0, 0, 0));
        MV1DrawModel(player.ModelHandle);
        if (fadein(0.5f))
        {
            progress = 0;
            isStarted = false;
        }
        isDead = false;

        player.Position = VGet(0, -5, 0);
        player.SetHitBox(2, 2);
    }
    
    else
    {
        
        if (!isPause)
        {
            MV1DrawModel(player.ModelHandle);
            /*if (Input_GetKeyboardDown(KEY_INPUT_SPACE))
            {
                isCleared = true;
            }*/
            if (isCleared)
            {
                if (fadeout(1))
                {
                    ClearInitialize();
                    progress = 0;
                    scene = SCENE_CLEAR;
                }
            }
            if (player.ammo < 1)
            {
                isDead = true;
            }
            if (enemy.Health < 0)
            {
                enemy.Health = 0;
                isKilled = true;
            }
            if (player.Health < 0)
            {
                player.Health = 0;
                isDead = true;
            }
            textPositionSet(120, 1920, "PLAYER HP: %d", fontHandle, SORT_LEFT, 500, true, GetColor(0, 255, 0), GetColor(50, 50, 50), player.Health);
            textPositionSet(0, 1800, "ENEMY HP: %d", fontHandle, SORT_RIGHT,500, true, GetColor(255, 0, 0), GetColor(50, 50, 50), enemy.Health);
            if (player.BasePosition.z > 2000.0f && gamePhase == PHASE_RUN)
            {
                gamePhase = PHASE_OVERSHOOT;
            }
            else if(gamePhase == PHASE_RUN)
            {
                DrawBox(1780, 100, 1850, 980, GetColor(180, 180, 180), true, 1);
                DrawBox(1800, 100 + 880 - (880 * (player.BasePosition.z/2000)), 1830, 980, GetColor(0, 255, 0), true);
                player.mainProcess(false);
                enemy.mainProcess(false);
            }
            if (gamePhase == PHASE_OVERSHOOT)
            {
                if (enemy.Transition())
                {
                    gamePhase = PHASE_CHASE;
                }
            }
            if (gamePhase == PHASE_CHASE)
            {
                player.mainProcess(true);
                enemy.mainProcess(true);
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
        else
        {
            MV1DrawModel(player.ModelHandle);
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
            DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), 1);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
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
                if (Input_GetKeyboardDown(KEY_INPUT_W) && choosedButton>0)
                {
                     choosedButton--;
                }
                if (Input_GetKeyboardDown(KEY_INPUT_S) && choosedButton < 2)
                {
                    choosedButton++;
                }
            }
            if (isRestarting)
            {
                if(fadeout(0.5f))
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

}