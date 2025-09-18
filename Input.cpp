#include "Input.h"
#include "DxLib.h"
int Input_Keyboard[256];
void Input_UpdateKeyboard() {
    int i;
    char tmpKey[256];   //現在のキーボードの入力状態を格納する
    // 全てのキーの入力状態を得る
    GetHitKeyStateAll(tmpKey);
    for (i = 0; i < 256; i++) {
        if (tmpKey[i] != 0) { // i番のキーコードに対応するキーが押されていたら
            Input_Keyboard[i]++;     // 加算
        }
        else {              // 押されていなければ
            if (Input_Keyboard[i] > 0) {    //前フレームで対応するキーが押されていれば
                Input_Keyboard[i] = -1;   // -1にする。-1はキーが離された時用の値
            }
            else {
                Input_Keyboard[i] = 0;   // 0にする
            }
        }
    }
}
bool Input_GetKeyboardDown(int KeyCode) {
    if (Input_Keyboard[KeyCode] == 1) return true;
    return false;
}