#pragma once
#include "main.h"
#include "Input.h"
#include "Text.h"
#include "Button.h"
class instruction
{
private:
    UIText text;
    UIText info;
    timer showTimer;
    Button normal;
    Button hard;
    bool pressSpace = false;
    int phase = 0;
    int dif = 0;
public:
    void Init();
    void main(int nextScene);
    void inst();
    void choiceDifficulty(int nextScene);
};
