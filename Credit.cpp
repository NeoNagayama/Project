#include "Credit.h"
#include "Input.h"
#include "TitleScene.h"
void CreditScene::start()
{
    Exit.SetButtonPosition(BUTTON_CENTER, BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON_REDUCTION, ANCHOR_CENTER);
    Exit.SetText(BUTTON_TEXT);
    Exit.SetGraph(buttonGraph);
}
void CreditScene::update()
{
    TextBox.DrawTextWithSort(TEXT_X_L, TEXT_X_R, text, japaneseFontHandle, SORT_LEFT, TEXT_Y, false, fontColor);
    Exit.Main(true, false, BUTTON_OFFSET);
    if (Input_GetKeyboardDown(KEY_INPUT_ESCAPE))
    {
        scene = SCENE_TITLE;
        Titleinitialize();
    }
}