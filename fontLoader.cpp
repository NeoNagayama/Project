#include "DxLib.h"
#include "fontLoader.h"
int fontHandle;
int BiggerFontHandle;
int titleFontHandle;
void fontLoad()
{
    fontHandle = LoadFontDataToHandle("Corner.dft", 0);
    BiggerFontHandle = LoadFontDataToHandle("CornerBigger.dft");
    titleFontHandle = LoadFontDataToHandle("Quantify.dft");
}
void textPositionSet(int xleft, int xright, std::string text, int FontHandle, int sort ,int y,bool shadow,unsigned int FontColor, unsigned int shadowcolor ,int value)
{
    int width;
    if (sort == SORT_CENTER)
    {
        width = GetDrawFormatStringWidthToHandle(FontHandle, const_cast<char*>(text.c_str()), (int)strlen(const_cast<char*>(text.c_str())),value);
        width = (((xright - xleft) - width) / 2) + xleft;
        if (shadow)
        {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
            DrawFormatStringToHandle(width + 3, y+2,shadowcolor, FontHandle, const_cast<char*>(text.c_str()), value);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }
        DrawFormatStringToHandle(width, y, FontColor, FontHandle, const_cast<char*>(text.c_str()), value);
    }
    else if (sort == SORT_RIGHT)
    {
        width = GetDrawFormatStringWidthToHandle(FontHandle,const_cast<char*>(text.c_str()), (int)strlen(const_cast<char*>(text.c_str())), value);
        width = ((xright - xleft) - width) + xleft;
        if (shadow)
        {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
            DrawFormatStringToHandle(width + 3, y+2, shadowcolor, FontHandle, const_cast<char*>(text.c_str()), value);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }
        DrawFormatStringToHandle(width, y, FontColor, FontHandle, const_cast<char*>(text.c_str()), value);
    }
    else
    {
        if (shadow)
        {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
            DrawFormatStringToHandle(xleft + 3,y+2, shadowcolor, FontHandle, const_cast<char*>(text.c_str()), value);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }
        DrawFormatStringToHandle(xleft,  y, FontColor, FontHandle, const_cast<char*>(text.c_str()), value);
    }
}