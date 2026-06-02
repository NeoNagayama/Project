#pragma once
#include "Button.h"
#include "DxLib.h"
#include "Input.h"

void ClearSetUp();
void ClearMain();
void ClearInitialize();
void ClearStage3();
class stage;

extern stage *clear_stage1Instance;
extern stage *clear_stage2Instance;
extern stage *clear_stage3Instance;

extern void ClearGetStagePointers(stage *s1, stage *s2, stage *s3);