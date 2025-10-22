#pragma once
#include "DxLib.h"
extern bool isStarted;
void Stage1InitialProcess();
void Stage1MainProcess();
void Stage1Initialize();
void Obstacle_Draw(int i ,int pos, bool upper, bool lower, bool right, bool left);
void AAGun_Draw(int i ,int pos, bool upper, bool lower, bool right, bool left);