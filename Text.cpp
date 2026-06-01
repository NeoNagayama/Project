#include "DxLib.h"
#include "Text.h"
/* @brief 通常用の英語フォント */
int fontHandle;
/* @brief サイズを大きくした英語フォント */
int BiggerFontHandle;
/* @brief タイトル用のフォント */
int titleFontHandle;
/* @brief 日本語フォント */
int japaneseFontHandle;
/* @brief サイズを大きくした日本語フォント */
int biggerJpFontHandle;
/* @brief カウントダウン用のフォント */
int CountDownFontHandle;
/* @brief フェードイン用のアルファ */
float TextAlpha = 0;
/* @brief 影用のアルファ */
float ShadowAlpha = 0;
void fontLoad()
{
    //各フォントのロード
    fontHandle = LoadFontDataToHandle("fonts/Corner.dft", 0);
    BiggerFontHandle = LoadFontDataToHandle("fonts/CornerBigger.dft");
    titleFontHandle = LoadFontDataToHandle("fonts/Quantify.dft");
    japaneseFontHandle = LoadFontDataToHandle("fonts/NotoSans.dft");
    biggerJpFontHandle = CreateFontToHandle("fonts/NotoSansJP-VariableFont_wght.ttf",70,5,DX_FONTTYPE_ANTIALIASING);
    CountDownFontHandle = CreateFontToHandle("fonts/NotoSansJP-VariableFont_wght.ttf", 150, 5, DX_FONTTYPE_ANTIALIASING);
}
void UIText::DrawTextWithSort(int xleft, int xright, std::string text, int FontHandle, int sort ,int y,bool shadow,unsigned int FontColor, unsigned int shadowcolor ,float value)
{
    /* @brief テキストの描画幅 */
    int width;
    //テキストのそろえ方別の処理
    //中央ぞろえの処理
    if (sort == SORT_CENTER)
    {
        //描画幅を求める
        width = GetDrawFormatStringWidthToHandle(FontHandle, const_cast<char*>(text.c_str()), (int)strlen(const_cast<char*>(text.c_str())),value);
        //中央ぞろえにするための左端からのずれを計算する
        width = (((xright - xleft) - width) / 2) + xleft;
        //影を描画するとき
        if (shadow)
        {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
            DrawFormatStringToHandle(width + 3, y+2,shadowcolor, FontHandle, const_cast<char*>(text.c_str()), value);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }
        DrawFormatStringToHandle(width, y, FontColor, FontHandle, const_cast<char*>(text.c_str()), value);
    }
    //右揃えの処理
    else if (sort == SORT_RIGHT)
    {
        //描画幅を求める
        width = GetDrawFormatStringWidthToHandle(FontHandle,const_cast<char*>(text.c_str()), (int)strlen(const_cast<char*>(text.c_str())), value);
        //右揃えにするための左端からのずれを計算する
        width = ((xright - xleft) - width) + xleft;
        //影を描画するとき
        if (shadow)
        {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
            DrawFormatStringToHandle(width + 3, y+2, shadowcolor, FontHandle, const_cast<char*>(text.c_str()), value);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }
        DrawFormatStringToHandle(width, y, FontColor, FontHandle, const_cast<char*>(text.c_str()), value);
    }
    //左揃えの処理
    else
    {
        //影を描画するとき
        if (shadow)
        {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
            DrawFormatStringToHandle(xleft + 3,y+2, shadowcolor, FontHandle, const_cast<char*>(text.c_str()), value);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }
        DrawFormatStringToHandle(xleft,  y, FontColor, FontHandle, const_cast<char*>(text.c_str()), value);
    }
}
bool UIText::fadeInText(int xleft, int xright, std::string text, int FontHandle, int sort, int y, bool shadow, unsigned int FontColor, unsigned int shadowcolor, float value,float time)
{
    int width;
    //一フレーム当たりに変化するアルファ値を変数に入れる
    TextAlpha += 255 / (time / 0.016f);
    ShadowAlpha += 128 / (time / 0.016f);
    //テキストのそろえ方別の処理
    //中央ぞろえの処理
    if (sort == SORT_CENTER)
    {
        //描画幅を求める
        width = GetDrawFormatStringWidthToHandle(FontHandle, const_cast<char*>(text.c_str()), (int)strlen(const_cast<char*>(text.c_str())), value);
        //中央ぞろえにするための左端からのずれを計算する
        width = (((xright - xleft) - width) / 2) + xleft;
        //影を描画するとき
        if (shadow)
        {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)ShadowAlpha);
            DrawFormatStringToHandle(width + 3, y + 2, shadowcolor, FontHandle, const_cast<char*>(text.c_str()), value);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)TextAlpha);
        DrawFormatStringToHandle(width, y, FontColor, FontHandle, const_cast<char*>(text.c_str()), value);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
    //右揃えの処理
    else if (sort == SORT_RIGHT)
    {
        //描画幅を求める
        width = GetDrawFormatStringWidthToHandle(FontHandle, const_cast<char*>(text.c_str()), (int)strlen(const_cast<char*>(text.c_str())), value);
        //右ぞろえにするための左端からのずれを計算する
        width = ((xright - xleft) - width) + xleft;
        //影を描画するとき
        if (shadow)
        {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)ShadowAlpha);
            DrawFormatStringToHandle(width + 3, y + 2, shadowcolor, FontHandle, const_cast<char*>(text.c_str()), value);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)TextAlpha);
        DrawFormatStringToHandle(width, y, FontColor, FontHandle, const_cast<char*>(text.c_str()), value);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
    //左揃えの処理
    else
    {
        //影を描画するとき
        if (shadow)
        {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)ShadowAlpha);
            DrawFormatStringToHandle(xleft + 3, y + 2, shadowcolor, FontHandle, const_cast<char*>(text.c_str()), value);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)TextAlpha);
        DrawFormatStringToHandle(xleft, y, FontColor, FontHandle, const_cast<char*>(text.c_str()), value);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
    //フェードインが終わったらtrueを返す
    if (TextAlpha >= 255)
    {
        return true;
    }
    return false;
}
void UIText::resetAlpha()
{
    TextAlpha = 0;
    ShadowAlpha = 0;
}
