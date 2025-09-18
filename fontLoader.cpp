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
void textPositionSet(int xleft, int xright, std::string text, int FontHandle, int sort ,int y,bool shadow,unsigned int FontColor, unsigned int shadowcolor)
{
    int width;
    if (sort == SORT_CENTER)
    {
        width = GetDrawStringWidthToHandle(const_cast<char*>(text.c_str()), strlen(const_cast<char*>(text.c_str())), FontHandle);
        width = (((xright - xleft) - width) / 2) + xleft;
        if (shadow)
        {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
            DrawStringToHandle(width + 3, y+2, const_cast<char*>(text.c_str()), shadowcolor, FontHandle);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }
        DrawStringToHandle(width, y, const_cast<char*>(text.c_str()), FontColor, FontHandle);
    }
    else if (sort == SORT_LEFT)
    {
        width = GetDrawStringWidthToHandle(const_cast<char*>(text.c_str()), strlen(const_cast<char*>(text.c_str())), FontHandle);
        width = ((xright - xleft) - width) + xleft;
        if (shadow)
        {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
            DrawStringToHandle(width + 3, y+2, const_cast<char*>(text.c_str()), shadowcolor, FontHandle);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }
        DrawStringToHandle(width, y, const_cast<char*>(text.c_str()), FontColor, FontHandle);
    }
    else
    {
        if (shadow)
        {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
            DrawStringToHandle(xleft + 3,y+2, const_cast<char*>(text.c_str()), shadowcolor, FontHandle);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }
        DrawStringToHandle(xleft,  y, const_cast<char*>(text.c_str()), FontColor, FontHandle);
    }
}