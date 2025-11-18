#pragma once
#include "main.h"
#include "Stage.h"
class stageEndless :public stage
{
private:
    UIText RoundCount;
    UIText R_Text[4];
    std::string R_info[4] = { 
        "残り時間      :%.f",
        "プレイヤーHP  :%.f",
        "残弾数        :%.f" ,
        "敵体力        :%.f" 
    };
    std::string R_info2[3]
    {
        "増加した最大体力:%.f",
        "増加した弾数    :%.f",
        "回復量          :%.f"
    };
    float R_Value[4];
    float R_Value2[3];
    timer R_Timer;
    int Round = 0;
    int resultStage = 0;
    int resultType = 0;
    int negativeResultType = 0;
    float baseHealth = 100;
    float baseHealthCache = 100;
    float baseAmmo = 200;
    float baseAmmoCache = 200;
    float incleasedAmmo = 0;
    float incleasedHealth = 0;
    float healedHealth = 1;
    bool isGetResult = false;
    bool isSaved = false;
    void StageRandomize();
    void StartWave();
    void WaveResult();
    void ShowResult();
    void ResultType();
    void EffectResult();
    void ReflectToText();
    void IngameToGameoverModified();
    void HighScore();
    void E_Pause();
public:
    void SetUp();
    void Init();
    void main();
};