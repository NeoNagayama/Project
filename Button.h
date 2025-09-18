#pragma once
#include "DxLib.h"
#include <string>
class Button
{
private:
    std::string buttonText;
    VECTOR ActualPosition;
    VECTOR ActualPosition2;
    COLOR16 NotSelectedColor = GetColor(1, 8, 60);
    COLOR16 SelectedColor = GetColor(4, 202, 206);
    bool isSelected = false;
public:
    void mainProcess(bool isSelected,bool shadow,int yoffset);
    void SetButtonPosition(VECTOR SelectedPos, VECTOR SelectedPos2, VECTOR NSelectedPos, VECTOR NSelectedPos2);
    float BoxSizeChange(float actual,float target,bool mode,float from);
    void SetText(std::string text);
    VECTOR NotSelectedPosition1 = VGet(1.0f, 1.0f, 2.0f);
    VECTOR NotSelectedPosition2 = VGet(1.0f, 1.0f, 2.0f);
    VECTOR SelectedPosition1 = VGet(1.0f, 1.0f, 2.0f);
    VECTOR SelectedPosition2 = VGet(1.0f, 1.0f, 2.0f);
};