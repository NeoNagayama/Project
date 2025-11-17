#pragma once
#include "DxLib.h"
void GameOverInitialProcess();
void GameOverMainProcess();
void GameOverInitialize();
void EndlessGameOver(float round);
class stage;
class stageEndless;

    extern stage* G_stage1Instance;
    extern stage* G_stage2Instance;
    extern stage* G_stage3Instance;
    extern stageEndless* E_Stage;
    extern void GameOverGetStagePointers(stage* s1, stage* s2, stage* s3,stageEndless* s4);