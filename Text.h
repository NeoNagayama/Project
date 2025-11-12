#pragma once
#include "DxLib.h"
#include <string>
extern int fontHandle;
extern int BiggerFontHandle;
extern int titleFontHandle;
extern int japaneseFontHandle;
extern int biggerJpFontHandle;
extern int CountDownFontHandle;
enum sortType
{
    SORT_LEFT,
    SORT_CENTER,
    SORT_RIGHT
};
class UIText
{
private:
public:
    void DrawTextWithSort(int xleft, int xright, std::string text, int FontHandle, int sort, int y, bool shadow, unsigned int FontColor, unsigned int shadowcolor = GetColor(50, 50, 50), int value = 0);
    bool fadeInText(int xleft, int xright, std::string text, int FontHandle, int sort, int y, bool shadow, unsigned int FontColor, unsigned int shadowcolor = GetColor(50, 50, 50), int value = 0, float time = 1.5f);
    void resetAlpha();
};
void fontLoad();
