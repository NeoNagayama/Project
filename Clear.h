#pragma once
#include "DxLib.h"
#include "Button.h"
#include "Input.h"

void ClearInitialProcess();
void ClearMainProcess();
void ClearInitialize();
class stage;

extern stage* clear_stage1Instance;
extern stage* clear_stage2Instance;
extern stage* clear_stage3Instance;

extern void ClearGetStagePointers(stage* s1, stage* s2, stage* s3);