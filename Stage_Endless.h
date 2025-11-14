#pragma once
#include "main.h"
#include "Stage.h"
class stageEndless :public stage
{
private:
    void StageRandomize();
    void StartWave();
public:
    void SetUp();
    void Init();
    void main();
};