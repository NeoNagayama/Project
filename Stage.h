#pragma once
#include "Input.h"
#include "ui.h"
#include "main.h"
#include "Clear.h"
#include "GameOver.h"
#include "TitleScene.h"
#include "Player.h"
#include "Map.h"
#include "DxLib.h"


class stage
{
protected:
    int obstacleDefault[50] = {
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
    int obstacleTypeDefault[50] = {
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
    int obstacle[50] = {
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
    int obstacleType[50] = {
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
    int moveWallType[50] = {
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
    
    bool isCleared = false;
    bool isDead = false;
    bool isGameOver = false;
    bool isPause = false;
    bool isKilled = false;
    bool PauseControllable = true;
    bool isRestarting = false;
    bool isQuitting = false;
    bool isObjectiveAppeared = false;
    bool isGetDamage = false;
    float clearCameraOffsetx;
    int gamePhase = 0;
    int choosedButton;
    int countDown = 3;
    Button resume;
    Button restart;
    Button Stage1ToTitle;
    Button Buttons[3];
    Player player;
    Enemy enemy;
    mapBase maps[50];
    antiAir AAs[50];
    wallmove moveWalls[50];
    timer objectiveShowTimer;
    timer CountDownTimer;
    timer damageRate;
    UIText objectiveText;
    UIText countDownText;
    UIText playerHealthText;
    UIText enemyHealthText;
    UIText missionTime;
    VECTOR cameraTarget;
    VECTOR cameraDirection;
    float remainingTime = 2;
    timer clearCameraTimer;
    timer gameOverTimer;
    timer missionTimer;
    int timeLimit = 5;
    void Obstacle_Draw(int i, int pos, bool upper, bool lower, bool right, bool left);
    void AAGun_Draw(int i, int pos, bool upper, bool lower, bool right, bool left);
    void ObstacleShadowDraw();
    void moveWallShadow();
    void DrawBase();
    void DrawObstacles();
    void AAGuns(int pos, int i);
    void Obstacles(int pos, int i);
    void MoveWalls(int pos, int i);
    void Briefing();
    void Ingame();
    void IngameToClear();
    void IngameToGameover();
    void RunPhase();
    void OverShootPhase();
    void ChasePhase();
    void PauseScreen();
    void CameraTargetMove();
    void PauseControll();
    void MoveWallDraw(int i, int pos, bool high, bool mid, bool low);
public:
    bool isStarted = true;
    void InitialProcess(int stage[50], int type[50]);
    void MainProcess();
    void Initialize();
};