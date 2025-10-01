#include "Button.h"
#include "DxLib.h"
#include "fontLoader.h"

void Button::mainProcess(bool isSelected, bool shadow ,int yoffset)
{
    if (isSelected)
    {
        ActualPosition = VGet(BoxSizeChange(ActualPosition.x, SelectedPosition1.x, false, NotSelectedPosition1.x), BoxSizeChange(ActualPosition.y, SelectedPosition1.y, false, NotSelectedPosition1.y),1);
        ActualPosition2 = VGet(BoxSizeChange(ActualPosition2.x, SelectedPosition2.x, true, NotSelectedPosition2.x), BoxSizeChange(ActualPosition2.y, SelectedPosition2.y, true, NotSelectedPosition2.y), 1);
        DrawBox((int)Button::ActualPosition.x, (int)Button::ActualPosition.y, (int)Button::ActualPosition2.x, (int)Button::ActualPosition2.y, Button::SelectedColor, 1);
        DrawBox((int)Button::ActualPosition.x, (int)Button::ActualPosition.y, (int)Button::ActualPosition2.x, (int)Button::ActualPosition2.y, GetColor(255,255,255), 0,3);
        textPositionSet((int)ActualPosition.x, (int)ActualPosition2.x, buttonText, BiggerFontHandle, SORT_CENTER, (int)ActualPosition.y + (int)yoffset*0.6f, true, GetColor(255, 255, 255));
    }
    else
    {
        ActualPosition = VGet(BoxSizeChange(ActualPosition.x, NotSelectedPosition1.x, true, SelectedPosition1.x), BoxSizeChange(ActualPosition.y, NotSelectedPosition1.y, true, SelectedPosition1.y), 1);
        ActualPosition2 = VGet(BoxSizeChange(ActualPosition2.x, NotSelectedPosition2.x, false, SelectedPosition2.x), BoxSizeChange(ActualPosition2.y, NotSelectedPosition2.y, false, SelectedPosition2.y), 1);
        DrawBox((int)Button::ActualPosition.x, (int)Button::ActualPosition.y, (int)Button::ActualPosition2.x, (int)Button::ActualPosition2.y, Button::NotSelectedColor, 1);
        textPositionSet((int)ActualPosition.x, (int)ActualPosition2.x, buttonText, fontHandle, SORT_CENTER, (int)ActualPosition.y + (int)yoffset*0.6f, true, GetColor(122,122,122));
    }
    
}
void Button::SetButtonPosition(VECTOR CenterPosition, float width, float height, float reductionRatio)
{
    width /= 2;
    height /= 2;
    SelectedPosition1 = VGet(CenterPosition.x - width, CenterPosition.y - height, 1);
    SelectedPosition2 = VGet(CenterPosition.x + width, CenterPosition.y + height, 1);
    width *= reductionRatio;
    height *= reductionRatio;
    NotSelectedPosition1 = VGet(CenterPosition.x - width, CenterPosition.y - height, 1);
    NotSelectedPosition2 = VGet(CenterPosition.x + width, CenterPosition.y + height, 1);
    ActualPosition = NotSelectedPosition1;
    ActualPosition2 = NotSelectedPosition2;
}
float Button::BoxSizeChange(float actual, float target, bool mode ,float from)
{
    float rate;
    if (mode)
    {
        rate = (target - from) /4;
    }
    else
    {
        rate = (from - target) / 4;
    }
    if (mode && actual < target)
    {
        actual += rate;
    }
    else if (!mode && actual > target)
    {
        actual -= rate;
    }
    else
    {
        actual = target;
    }
    return actual;
}
void Button::SetText(std::string text)
{
    buttonText = text;
}