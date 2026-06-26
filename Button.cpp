#include "Button.h"
#include "DxLib.h"
#include "Text.h"

void Button::SetGraph(int OriginGraphHandle)
{
    GraphHandle = OriginGraphHandle;
}

void Button::Update(bool isSelected, bool shadow, int yoffset)
{
    // ボタンが選択されているときの処理
    if (isSelected)
    {
        // ボタンのサイズを目標のサイズになるまで一定の速度で変更する
        ActualPosition = VGet(BoxSizeChange(ActualPosition.x, SelectedPosition1.x, false, NotSelectedPosition1.x),
                              BoxSizeChange(ActualPosition.y, SelectedPosition1.y, false, NotSelectedPosition1.y), 1);
        ActualPosition2 = VGet(BoxSizeChange(ActualPosition2.x, SelectedPosition2.x, true, NotSelectedPosition2.x),
                               BoxSizeChange(ActualPosition2.y, SelectedPosition2.y, true, NotSelectedPosition2.y), 1);
        // ボタンの画像を描画する
        DrawExtendGraph((int)Button::ActualPosition.x, (int)Button::ActualPosition.y, (int)Button::ActualPosition2.x,
                        (int)Button::ActualPosition2.y, GraphHandle, true);
        buttonTextDraw.DrawTextWithSort((int)ActualPosition.x, (int)ActualPosition2.x, buttonText, BiggerFontHandle,
                                        SORT_CENTER, (int)ActualPosition.y + (int)(yoffset * 0.6f), true,
                                        GetColor(255, 255, 255));
    }
    // 選択されていないときの処理
    else
    {
        // ボタンのサイズを目標のサイズになるまで一定の速度で変更する
        ActualPosition = VGet(BoxSizeChange(ActualPosition.x, NotSelectedPosition1.x, true, SelectedPosition1.x),
                              BoxSizeChange(ActualPosition.y, NotSelectedPosition1.y, true, SelectedPosition1.y), 1);
        ActualPosition2 = VGet(BoxSizeChange(ActualPosition2.x, NotSelectedPosition2.x, false, SelectedPosition2.x),
                               BoxSizeChange(ActualPosition2.y, NotSelectedPosition2.y, false, SelectedPosition2.y), 1);
        // ボタンの画像を描画する
        DrawExtendGraph((int)Button::ActualPosition.x, (int)Button::ActualPosition.y, (int)Button::ActualPosition2.x,
                        (int)Button::ActualPosition2.y, GraphHandle, true);
        buttonTextDraw.DrawTextWithSort((int)ActualPosition.x, (int)ActualPosition2.x, buttonText, fontHandle,
                                        SORT_CENTER, (int)ActualPosition.y + (int)(yoffset * 0.6f), true,
                                        GetColor(122, 122, 122));
    }
}

void Button::SetButtonPosition(VECTOR CenterPosition, float width, float height, float reductionRatio, int anchor)
{
    float reducedwidth;
    width /= 2;
    height /= 2;
    reducedwidth = width;
    // 選択された時のボタンの角の座標を設定する
    SelectedPosition1 = VGet(CenterPosition.x - width, CenterPosition.y - height, 1);
    SelectedPosition2 = VGet(CenterPosition.x + width, CenterPosition.y + height, 1);
    // 選択されていないときの縮小したボタンのサイズを設定する
    reducedwidth *= reductionRatio;
    height *= reductionRatio;
    // ボタンのサイズの縮小の基準別に縮小した時のボタンの角の位置を設定する
    switch (anchor)
    {
    case ANCHOR_LEFT: // 左側を基準に縮小する場合
        NotSelectedPosition1 = VGet(CenterPosition.x - width, CenterPosition.y - height, 1);
        NotSelectedPosition2 = VGet(CenterPosition.x + (reducedwidth / 2), CenterPosition.y + height, 1);
        break;
    case ANCHOR_CENTER: // 中央を基準にする場合
        NotSelectedPosition1 = VGet(CenterPosition.x - reducedwidth, CenterPosition.y - height, 1);
        NotSelectedPosition2 = VGet(CenterPosition.x + reducedwidth, CenterPosition.y + height, 1);
        break;
    default: // 右側を基準にする場合
        NotSelectedPosition1 = VGet(CenterPosition.x - (reducedwidth / 2), CenterPosition.y - height, 1);
        NotSelectedPosition2 = VGet(CenterPosition.x + width, CenterPosition.y + height, 1);
        break;
    }
    // ボタンの初期値を選択されていないときの状態にする
    ActualPosition = NotSelectedPosition1;
    ActualPosition2 = NotSelectedPosition2;
}

float Button::BoxSizeChange(float actual, float target, bool mode, float from)
{

    float rate;
    // 1フレーム当たりの変化する値を求める
    // 座標を増加させる方向で変化させるとき
    if (mode)
    {
        rate = (target - from) / 4;
    }
    // 座標を減少させる方向で変化させるとき
    else
    {
        rate = (from - target) / 4;
    }
    // 座標を増加させる方向で変化させるときに現在の座標が目標の座標を超えていないとき
    if (mode && actual < target)
    {
        actual += rate;
    }
    // 座標を減少させる方向で変化させるときに現在の座標が目標の座標を超えていないとき
    else if (!mode && actual > target)
    {
        actual -= rate;
    }
    // 現在の座標が目標の座標を超えたとき
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