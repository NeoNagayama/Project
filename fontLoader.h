#pragma once
#include "DxLib.h"
#include <string>
extern int fontHandle;
extern int BiggerFontHandle;
extern int titleFontHandle;
enum sortType
{
    SORT_LEFT,
    SORT_CENTER,
    SORT_RIGHT
};
void fontLoad();
void textPositionSet(int xleft, int xright, std::string text, int FontHandle, int sort, int y, bool shadow, unsigned int FontColor, unsigned int shadowcolor = GetColor(50, 50, 50),int value = 0);

