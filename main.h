#pragma once
# define PI 3.14159265359f

extern int scene;
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