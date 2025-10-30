#pragma once
#include "DxLib.h"
#include "Stage.h"
void GameOverInitialProcess();
void GameOverMainProcess();
void GameOverInitialize();
class stage;

    extern stage* G_stage1Instance;
    extern stage* G_stage2Instance;
    extern stage* G_stage3Instance;
    extern void GameOverGetStagePointers(stage* s1, stage* s2, stage* s3);