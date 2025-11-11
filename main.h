#pragma once
#include "DxLib.h"
#define PI 3.14159265359f
#define oneFlame 0.0166f
extern int scene;
extern int stages;
extern int shadowHandle;
extern int titleShadowHandle;
extern int reticleHandle;
extern int reticleInsideGaugeHandle;
extern int backGroundHandle;
extern int cargoModelOrigin;
extern int bulletHandle;
extern int enemyBulletHandle;
extern int carrierHandle;
extern int lowerObstacleHandle;
extern int missileBurnerHandle;
extern int smokeHandle;
extern int explosionHandle;
extern int wallHandle;
extern int guideHandle;
extern float timeScale;
extern int instGraph;
extern int spaceGraph;
extern int alertGraph;
extern int gaugeHandle;
extern int barHandle;
extern int E_gauge;
extern int E_bar;
enum SCENES
{
    SCENE_TITLE,
    SCENE_INGAME,
    SCENE_INSTRUCTION
};
enum STAGES
{
    STAGE1,
    STAGE2,
    STAGE3
};
extern float smooth(float min, float max, float n);
extern float VectorLength(VECTOR from, VECTOR to);
extern VECTOR VectorDirectionNormalize(VECTOR v1, VECTOR v2);
extern int get_rand(int min, int max);
extern bool Quit;
class timer
{
private:
    float Elapsed = 0;
public:
    bool MeasureTimer(float time)
    {
        Elapsed += oneFlame;
        if (Elapsed > time)
        {
            return true;
        }
        return false;
    }
    float GetElapsed()
    {
        return Elapsed += oneFlame;
    }
    void RestartTimer()
    {
        Elapsed = 0;
    }
};
void LoadAssets();
void setupShadowMap();
void Init();