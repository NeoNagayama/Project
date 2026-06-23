#pragma once
#include"main.h"
#include"Button.h"
#include"Text.h"
constexpr int TEXT_Y = 20;
constexpr int TEXT_X_L = 20;
constexpr int TEXT_X_R = 1900;
constexpr int BUTTON_WIDTH = 600;
constexpr int BUTTON_HEIGHT = 120;
constexpr float BUTTON_REDUCTION = 0.9f;
constexpr int BUTTON_OFFSET = 30;

class CreditScene
{
  private:
    Button Exit;
    UIText TextBox;
    VECTOR BUTTON_CENTER = VGet(960, 980, 0);
    unsigned int fontColor = GetColor(255, 255, 255);
    std::string BUTTON_TEXT = "Press Escape to Exit";
    std::string text = "Music from https://www.fesliyanstudios.com\nUI Assets by SunGraphica(https://sungraphica.itch.io/)\nModular_sci_Fi Wall 1x1_previewScene copyright Christian RudorffÇâ¸ïœÇµÇƒçÏê¨\nhttps://sketchfab.com/3dmodels/modular-sci-fi-wall-\n1x1-previewscene-f5b5f2c068f74b3aa1e8790926fd9b9d";
  public:
    void start();
    void update();
};