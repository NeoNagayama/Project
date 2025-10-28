#include "DxLib.h"
#include "Text.h"
int fontHandle;
int BiggerFontHandle;
int titleFontHandle;
int japaneseFontHandle;
int biggerJpFontHandle;
float TextAlpha = 0;
float ShadowAlpha = 0;
void fontLoad()
{
    fontHandle = LoadFontDataToHandle("fonts/Corner.dft", 0);
    BiggerFontHandle = LoadFontDataToHandle("fonts/CornerBigger.dft");
    titleFontHandle = LoadFontDataToHandle("fonts/Quantify.dft");
    japaneseFontHandle = LoadFontDataToHandle("fonts/NotoSans.dft");
    biggerJpFontHandle = CreateFontToHandle("fonts/NotoSansJP-VariableFont_wght.ttf",70,5,DX_FONTTYPE_ANTIALIASING);
}
void DrawTextWithSort(int xleft, int xright, std::string text, int FontHandle, int sort ,int y,bool shadow,unsigned int FontColor, unsigned int shadowcolor ,int value)
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
bool fadeInText(int xleft, int xright, std::string text, int FontHandle, int sort, int y, bool shadow, unsigned int FontColor, unsigned int shadowcolor, int value,float time)
{
    int width;
    TextAlpha += 255 / (time / 0.016f);
    ShadowAlpha += 128 / (time / 0.016f);
    if (sort == SORT_CENTER)
    {
        width = GetDrawFormatStringWidthToHandle(FontHandle, const_cast<char*>(text.c_str()), (int)strlen(const_cast<char*>(text.c_str())), value);
        width = (((xright - xleft) - width) / 2) + xleft;
        if (shadow)
        {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, ShadowAlpha);
            DrawFormatStringToHandle(width + 3, y + 2, shadowcolor, FontHandle, const_cast<char*>(text.c_str()), value);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, TextAlpha);
        DrawFormatStringToHandle(width, y, FontColor, FontHandle, const_cast<char*>(text.c_str()), value);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
    else if (sort == SORT_RIGHT)
    {
        width = GetDrawFormatStringWidthToHandle(FontHandle, const_cast<char*>(text.c_str()), (int)strlen(const_cast<char*>(text.c_str())), value);
        width = ((xright - xleft) - width) + xleft;
        if (shadow)
        {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, ShadowAlpha);
            DrawFormatStringToHandle(width + 3, y + 2, shadowcolor, FontHandle, const_cast<char*>(text.c_str()), value);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, TextAlpha);
        DrawFormatStringToHandle(width, y, FontColor, FontHandle, const_cast<char*>(text.c_str()), value);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
    else
    {
        if (shadow)
        {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, ShadowAlpha);
            DrawFormatStringToHandle(xleft + 3, y + 2, shadowcolor, FontHandle, const_cast<char*>(text.c_str()), value);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, TextAlpha);
        DrawFormatStringToHandle(xleft, y, FontColor, FontHandle, const_cast<char*>(text.c_str()), value);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
    if (TextAlpha >= 255)
    {
        return true;
    }
    return false;
}
void resetAlpha()
{
    TextAlpha = 0;
    ShadowAlpha = 0;
}
