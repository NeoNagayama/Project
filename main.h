#pragma once
# define PI 3.14159265359f
#define oneFlame 0.0166f

extern int scene;
extern int shadowHandle;
extern int titleShadowHandle;
extern int reticleHandle;
enum SCENES
{
    SCENE_TITLE,
    SCENE_STAGE1,
    SCENE_GAMEOVER,
    SCENE_CLEAR
};
extern float smooth(float min, float max, float n);
extern float VectorLength(VECTOR from, VECTOR to);
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
    void RestartTimer()
    {
        Elapsed = 0;
    }
};