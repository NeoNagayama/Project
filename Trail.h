#pragma once
#include "main.h"

constexpr int SMOKE_SPAWN_INTERVAL = 2;
constexpr int FLARE_SMOKE_COUNT = 60;
constexpr int MISSILE_SMOKE_COUNT = 90;

class smoke
{
private:
    VECTOR Position = zeroVector;
    float progress = 0;
    const float LIFETIME = 3;
public:
    void DrawSmoke(float cameraZ);
    void SetPosition(VECTOR pos);
    bool isActive = false;
};
