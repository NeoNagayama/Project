#pragma once
#include "DxLib.h"
#include "Button.h"
#include "Stage.h"
#include <string>
class stage;
class stageEndless;
void TitleSetUp();
void TitleMain();
void Titleinitialize();
void DrawShadow();
void DrawModels();
void TitleButtons();
void TitleMenu();


    extern stage* stage1Instance;
    extern stage* stage2Instance;
    extern stage* stage3Instance;
    extern stageEndless* Stage4;
    extern void getStagePointers(stage* s1, stage* s2, stage* s3,stageEndless* s4);