#pragma once
#include "DxLib.h"
#include "Button.h"
#include <string>
class Title
{
private:
    int color = 255;
    bool isStartSelected = true;
    bool sceneChanging = false;
    Button Start;
    Button Exit;
public:
    void test();
    void initialProcess();
    void mainProcess();
};