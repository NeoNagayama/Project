#include "Player.h"
#include "base.h"
#include <cmath>
int test;

/**
 * @brief 起動時に1度だけ呼び出される処理
 * @details モデルのロード,初期座標の設定,モデルのスケール等の処理を行う
 */

void Player::Start()
{
    // プレイヤーのモデルをロードする
    ModelHandle = MV1LoadModel("Resource/PlayerModel.mv1");
    // プレイヤーの初期座標を設定する
    MV1SetPosition(ModelHandle, VGet(0, -5, -0));
    // プレイヤーのスケールを設定する
    MV1SetScale(ModelHandle, VGet(6, 6, 6));
    // プレイヤーの座標を入れる変数に初期座標を入れる
    Position = VGet(0, -5, -0);
    // プレイヤーのモデルのすべてのマテリアルの設定を変更する
    for (int i = 0; i < MV1GetMaterialNum(ModelHandle); i++)
    {
        MV1SetMaterialDifColor(ModelHandle, i, GetColorF(0.7f, 0.7f, 0.5f, 1.0f));
        MV1SetMaterialAmbColor(ModelHandle, i, GetColorF(0.2f, 0.2f, 0.4f, 1.0f));
        MV1SetMaterialSpcColor(ModelHandle, i, GetColorF(0.4f, 0.4f, 0.4f, 1));
        MV1SetMaterialEmiColor(ModelHandle, i, GetColorF(0.8f, 0.8f, 0.8f, 0.2f));
        MV1SetMaterialSpcPower(ModelHandle, i, 6);
    }
    // プレイヤーが発射する弾のモデルのロード等の処理を行う
    for (int i = 0; i < 200; i++)
    {
        bullets[i].setUp();
    }
}

/**
 * @brief プレイヤーの初期化
 * @details 座標や体力等の変数を初期値に戻す
 */
void Player::Init()
{
    // 残弾数
    ammo = 200;
    // 開始時のカメラのx座標
    startCameraOffsetx = 6;
    // カメラのズーム倍率
    cameraZoom = 0.6f;
    // カメラの注視点のz座標
    target = 0;
    // 体力
    Health = 100;
    // プレイヤーのxy平面上の位置
    offset = VGet(0, -5, 0);
    // プレイヤーの開始位置のz座標
    BasePosition.z = -200;
    // プレイヤーの開始位置
    Position = VGet(0, 0, -200);
    // プレイヤーの移動速度
    forwardSpeed = DEFAULTSPEED;
    // プレイヤーの当たり判定の設定
    SetHitBox(2, 2);
    // カメラがプレイヤーの後ろについて移動し始める座標
    cameraStartThleshold = 0;
    // 死亡していない
    isDead = false;
}

/**
 * @brief 変数をゲーム開始時のカメラ演出用の数値に変更する
 * @details ゲーム開始時のカメラ演出に関連する変数の値を
 *          変更しゲーム開始時以外にもカメラの演出を行えるようにする
 *
 * @param int pos カメラ演出開始時のプレイヤーの座標
 *
 */
void Player::camSetUp(float pos)
{
    // カメラの位置をプレイヤーに追従させる位置を設定する
    cameraStartThleshold = pos;
    // カメラ演出時のカメラのx軸上のずれ
    startCameraOffsetx = 6;
    // カメラをズームさせる
    cameraZoom = 0.6f;
    // カメラの注視点のz座標をプレイヤーのz座標からずらさないようにする
    target = 0;
}

/**
 * @brief プレイヤーの毎フレーム呼ばれる処理
 * @details プレイヤーの毎フレーム呼ばれる処理
 *
 * @param bool mode ゲームが追跡フェーズに入っているか
 */
void Player::Update(bool mode)
{
    Immortal();
    // 体力が0でないとき
    if (Health > 0)
    {
        // 当たり判定を設定する
        SetHitBox(2, 2);
        // DrawSphere3D(VAdd(VScale(VGet(-forward().x, forward().y, -forward().z), 5), Position), 0.2f, 6, GetColor(255,
        // 255, 255), GetColor(255, 255, 255), true); プレイヤーのz座標に移動速度にtimeScaleをかけた数値を足す
        BasePosition = VAdd(VGet(0, 0, forwardSpeed * timeScale), BasePosition);
        // プレイヤーの入力周りの処理
        KeyInput();
        // プレイヤーのxy平面の移動処理
        PlayerMoveXY();
        // プレイヤーの位置をモデルに反映する
        Move(VAdd(BasePosition, offset));
        // プレイヤーの回転処理
        rotatePlayer();
        // プレイヤーのピッチ方向の回転処理
        pitch();

        // ゲームが追跡フェーズの時
        if (mode)
        {
            // カメラの位置をセットする
            SetCameraPositionAndTarget_UpVecY(VAdd(VGet(offset.x, offset.y + 2, -16), BasePosition),
                                              VAdd(VGet(offset.x, offset.y, 20), BasePosition));
            // カメラの座標を変数に格納する
            CameraPosition = VAdd(VGet(offset.x, offset.y + 2, -16), BasePosition),
            VAdd(VGet(offset.x, offset.y, 20), BasePosition);
            // 機銃処理
            Vulcan();
        }
        // ゲームが逃走フェーズの時
        else
        {
            // カメラの位置をセットする
            SetCameraPositionAndTarget_UpVecY(VAdd(VGet(offset.x, offset.y + 2, -20), BasePosition),
                                              VAdd(VGet(offset.x, offset.y, TARGET_CAMERA_POSZ), BasePosition));
            // カメラの座標を変数に格納する
            CameraPosition = VAdd(VGet(offset.x, offset.y + 2, -20), BasePosition),
            VAdd(VGet(offset.x, offset.y, TARGET_CAMERA_POSZ), BasePosition);
            // フレアの処理
            Flare();
        }
    }
    // 体力が0以下の時
    else
    {
        // プレイヤーのy座標を下げる
        offset.y -= 0.2f;
        // プレイヤーのz座標を前に進める
        BasePosition.z += 1.2f;
        // プレイヤーの座標をモデルに反映させる
        MV1SetPosition(ModelHandle, VAdd(BasePosition, offset));
        // z軸で回転させ続ける
        MV1SetRotationXYZ(ModelHandle, VAdd(MV1GetRotationXYZ(ModelHandle), VGet(0, 0, 0.1f)));

        // プレイヤーの座標が一定以下になったら
        if (offset.y < -13)
        {
            exp2.SetPosition(MV1GetPosition(ModelHandle));
        }
    }

    // 体力が0になった後に一度だけ呼ばれる処理
    if (!isDead && Health <= 0)
    {
        // 爆発エフェクトの位置を設定する
        exp.SetPosition(Position);
        // 爆発音を流す
        PlaySoundMem(explosionSound, DX_PLAYTYPE_BACK);
        // 二度処理を行わないためのフラグをtrueにする
        isDead = true;
    }

    // 1回目の爆発エフェクトの処理
    exp.DrawExprosion();
    // 2回目の爆発エフェクトの処理
    exp2.DrawExprosion();
}

/**
 * @brief ゲームのフェーズが切り替わるときの演出
 * @details ゲームのフェーズが切り替わるときの演出のカメラやプレイヤーの処理
 *
 * @param bool mode 開始時の演出でない時はtrue
 *                  開始時の演出の時はfalse
 */
void Player::transitionProcess(bool mode)
{
    // プレイヤーのz座標に移動速度にtimeScaleをかけた数値を足す
    BasePosition = VAdd(VGet(0, 0, DEFAULTSPEED * timeScale), BasePosition);
    // プレイヤーの座標をモデルに反映する
    Move(VAdd(BasePosition, offset));
    // プレイヤーの回転の角度を正面にする
    targetAngle = VGet(0, -0.99f, 0);
    // プレイヤーの回転処理
    rotatePlayer();
    // プレイヤーのピッチ方向の角度を正面にする
    targetAnglePitch = VGet(0, 0, 1);
    // プレイヤーのピッチ方向の回転処理
    pitch();
    // ゲーム開始時でないとき
    if (mode)
    {
        // カメラの位置をセットする
        SetCameraPositionAndTarget_UpVecY(VAdd(VGet(offset.x, offset.y + 2, -16), BasePosition),
                                          VAdd(VGet(offset.x, offset.y, 20), BasePosition));
        // 変数にカメラの座標を格納する
        CameraPosition = VAdd(VGet(offset.x, offset.y + 2, -16), BasePosition),
        VAdd(VGet(offset.x, offset.y, 20), BasePosition);
    }
    // ゲーム開始時の時
    else
    {

        // カメラがプレイヤーの後ろを追従し始めるz座標の20先でかつx軸の座標が0よりも多いとき
        if (Position.z >= cameraStartThleshold + 20 && startCameraOffsetx > 0)
        {
            // カメラのx座標を減らし続ける
            startCameraOffsetx -= 0.1f;
        }

        // プレイヤーの座標がカメラがプレイヤーの後ろを追従し始めるz座標の20先よりも後ろの時
        if (Position.z >= cameraStartThleshold + 20)
        {
            // カメラの位置をセットする
            SetCameraPositionAndTarget_UpVecY(
                VAdd(VGet(offset.x + startCameraOffsetx, offset.y + 2, -20), BasePosition),
                VAdd(VGet(offset.x, offset.y, +target), BasePosition));
            // 変数にカメラの座標を格納する
            CameraPosition = VAdd(VGet(offset.x + startCameraOffsetx, offset.y + 2, -20), BasePosition);

            // カメラのズームが1未満の時
            if (cameraZoom < 1)
            {
                // カメラのズームを増やし続ける
                cameraZoom += 0.02f;
            }
            // カメラのズームが1以上の時
            else
            {
                // カメラのズームを1にする
                cameraZoom = 1;
            }

            // カメラの注視点のz座標が20未満の時
            if (target < 20)
            {
                // 注視点のz座標を増やし続ける
                target += 0.5f;
            }
            // そうでないときは20にする
            else
                target = 20;
        }
        // プレイヤーの座標がカメラがプレイヤーの後ろを追従し始めるz座標の20先よりも前の時
        else
        {
            // カメラの位置をセットする
            SetCameraPositionAndTarget_UpVecY(VGet(offset.x + startCameraOffsetx, offset.y + 2, cameraStartThleshold),
                                              VAdd(VGet(offset.x, offset.y, target), BasePosition));
            // 変数にカメラの座標を格納する
            CameraPosition = VGet(offset.x + startCameraOffsetx, offset.y + 2, cameraStartThleshold);
        }
        // カメラのズームの倍率を変更する
        SetupCamera_Perspective(cameraZoom);
    }
}

/**
 * @brief  クリア時の処理
 * @details クリア時のプレイヤーの移動と回転に関する処理
 */
void Player::clearProcess()
{
    // 障害物を回避する処理
    autoEvade();
    // targetAnglePitchに干渉しない回転処理
    rotateOnlyRoll();
    // ピッチ方向の回転を水平にする
    targetAnglePitch = VGet(0, 0, 1);
    // ピッチ方向の回転処理
    pitch();
    // プレイヤーのz座標に移動速度にtimeScaleをかけた数値を足す
    BasePosition = VAdd(VGet(0, 0, forwardSpeed * timeScale), BasePosition);
    // プレイヤーの座標をモデルに反映する
    Move(VAdd(BasePosition, offset));
    // ロール方向の回転を水平にする
    targetAngle = VGet(0, -0.99f, 0);
}

/**
 * @brief  入力処理
 * @details プレイヤーの入力と反映
 */
void Player::KeyInput()
{
    /** @brief キーボード操作したときに毎フレーム増やす値 */
    float speed = 0.1f;

    // Wを押したとき
    if (CheckHitKey(KEY_INPUT_W))
    {
        // 上方向に移動する処理
        InputUp(speed);
    }
    // Sを押したとき
    else if (CheckHitKey(KEY_INPUT_S))
    {
        // 下方向に移動する処理
        InputDown(speed);
    }
    // Dキーを押していてかつx座標の速度が0.7未満の時
    else if (CheckHitKey(KEY_INPUT_D) && x < 0.7f)
    {
        // x軸の移動速度を上げる
        x += speed;
        // 移動速度の上限を0.7にする
        speedLimit = 0.7f;
        // プレイヤーの回転すべき角度を変更する
        targetAngle = VGet(0.6f, -0.4f, 0);
    }
    // Aキーを押していてかつx座標の速度が-0.7より多い時
    else if (CheckHitKey(KEY_INPUT_A) && x > -0.7f)
    {
        // x軸の移動速度を減らす
        x -= speed;
        // 移動速度の上限を0.7にする
        speedLimit = 0.7f;
        // プレイヤーの回転すべき角度を変更する
        targetAngle = VGet(-0.6f, -0.4f, 0);
    }
    // x座標y座標別の操作していないときの処理
    InputNeutral(speed);
    // 移動速度が上限を超えないようにする処理
    Limit();
}

/*
 * @brief 上方向に移動しているときの処理
 * @details 上方向に移動する操作をしているときの処理
 *
 * @param[in] float speed 一フレーム当たりに移動速度を変化させる値
 */
void Player::InputUp(float speed)
{
    // Dキーが押されているとき
    if (CheckHitKey(KEY_INPUT_D))
    {
        // x軸の移動速度を上げる
        x += speed;
        // 移動速度の上限を0.49にする
        speedLimit = 0.49f;
        // プレイヤーの回転すべき角度を変更する
        targetAngle = VGet(0.5f, -0.5f, 0);
    }
    // Aキーが押されているとき
    else if (CheckHitKey(KEY_INPUT_A))
    {
        // x軸の移動速度を下げる
        x -= speed;
        // 移動速度の上限を0.49にする
        speedLimit = 0.49f;
        // プレイヤーの回転すべき角度を変更する
        targetAngle = VGet(-0.5f, -0.5f, 0);
    }
    // Wキーのみが押されているとき
    else
    {
        // 移動速度の上限を0.7にする
        speedLimit = 0.7f;
        // プレイヤーの回転すべき角度を水平に変更する
        targetAngle = VGet(0, -1, 0);
    }
    // y軸の移動速度を上げる
    y += speed;
}

/*
 * @brief 下方向に移動しているときの処理
 * @details 下方向に移動する操作をしているときの処理
 *
 * @param[in] float speed 一フレーム当たりに移動速度を変化させる値
 */
void Player::InputDown(float speed)
{
    // Dキーが押されているとき
    if (CheckHitKey(KEY_INPUT_D))
    {
        // x軸の移動速度を上げる
        x += speed;
        // 移動速度の上限を0.49にする
        speedLimit = 0.49f;
        // プレイヤーの回転すべき角度を変更する
        targetAngle = VGet(0.5f, 0.5f, 0);
    }
    // Aキーが押されているとき
    else if (CheckHitKey(KEY_INPUT_A))
    {
        // x軸の移動速度を下げる
        x -= speed;
        // 移動速度の上限を0.49にする
        speedLimit = 0.49f;
        // プレイヤーの回転すべき角度を変更する
        targetAngle = VGet(-0.5f, 0.5f, 0);
    }
    // Sキーのみが押されているとき
    else
    {
        // 移動速度の上限を0.7にする
        speedLimit = 0.7f;
        // プレイヤーの回転すべき角度を変更する
        targetAngle = VGet(0, 0.99f, 0);
    }
    // y軸の移動速度を下げる
    y -= speed;
}

/*
 * @brief 操作していないときの処理
 * @details WSキー,ADキー,WASDキーそれぞれの操作していないときの処理を行う
 *
 * @param float speed 1フレーム当たりの速度を減少させる値
 */
void Player::InputNeutral(float speed)
{
    // WASDキー全てが押されていない場合
    if (!CheckHitKey(KEY_INPUT_A) && !CheckHitKey(KEY_INPUT_S) && !CheckHitKey(KEY_INPUT_D) &&
        !CheckHitKey(KEY_INPUT_W))
    {
        // 機体が回転すべき角度を水平にする
        targetAngle = VGet(0, -0.99f, 0);
    }
    // ADキーが押されていない場合
    if (!CheckHitKey(KEY_INPUT_A) && !CheckHitKey(KEY_INPUT_D))
    {
        // x軸の移動速度が0.1よりも多い場合
        if (x > 0.1f)
        {
            // x軸の移動速度を減少させ0に近づける
            x -= speed;
        }
        // x軸の移動速度が-0.1未満の場合
        else if (x < -0.1f)
        {
            // x軸の移動速度を増加させ0に近づける
            x += speed;
        }
        // x軸の移動速度が-0.1以上0.1以下の場合
        else
        {
            // x軸の移動速度を0にする
            x = 0;
        }
    }

    // WSキーが押されていない場合
    if (!CheckHitKey(KEY_INPUT_S) && !CheckHitKey(KEY_INPUT_W))
    {
        // y軸の移動速度が0.1よりも多い場合
        if (y > 0.1f)
        {
            // y軸の移動速度を減少させ0に近づける
            y -= speed;
        }
        // y軸の移動速度が-0.1よりも少ない場合
        else if (y < -0.1f)
        {
            // y軸の移動速度を増加させ0に近づける
            y += speed;
        }
        // y軸の移動速度が-0.1以上0.1以下の場合
        else
        {
            // y軸の移動速度を0にする
            y = 0;
        }
    }
}

/*
 * @brief 移動速度が上限を超えないようにする
 * @details x軸y軸それぞれの移動速度が制限を超えると
 *          上限内に戻す
 */
void Player::Limit()
{
    if (x >= speedLimit) // x軸の移動速度が上限を超えた場合
    {
        x = speedLimit; // x軸の移動速度に上限の値を入れる
    }
    else if (x <= -speedLimit) // x軸の移動速度が下限を超えた場合
    {
        x = -speedLimit; // x軸の移動速度に下限の値を入れる
    }
    if (y >= speedLimit) // y軸の移動速度が上限を超えた場合
    {
        y = speedLimit; // y軸の移動速度に上限の値を入れる
    }
    else if (y <= -speedLimit) // y軸の移動速度が下限を超えた場合
    {
        y = -speedLimit; // y軸の移動速度に下限の値を入れる
    }
}

/*
 * @brief プレイヤーのxy平面上の移動処理
 * @details プレイヤーの移動する座標を変数に入れ
 *          移動できる範囲から出ないようにする
 */
void Player::PlayerMoveXY()
{
    /* @brief 1フレーム当たりの実際に移動する距離 */
    float xSpeed, ySpeed;
    // プレイヤーの位置が移動可能範囲から出ていると0,出ていなければ移動すべき距離を入れる
    xSpeed = (offset.x > moveRange || offset.x < -moveRange) ? 0 : x * moveSpeed;
    ySpeed = (offset.y > moveRange || offset.y < -moveRange) ? 0 : y * moveSpeed;
    offset =
        VAdd(VGet(xSpeed * timeScale, ySpeed * timeScale, 0), offset); // プレイヤーの現在の位置に移動すべき距離を足す
    if (offset.x > moveRange || offset.x < -moveRange) // プレイヤーのx座標が移動可能範囲から出ていたら
    {
        offset.x = (offset.x > moveRange) ? moveRange : -moveRange; // 範囲内に戻す
    }
    if (offset.y > moveRange || offset.y < -moveRange) // プレイヤーのy座標が移動可能範囲から出ていたら
    {
        offset.y = (offset.y > moveRange) ? moveRange : -moveRange; // 範囲内に戻す
    }
    if (offset.z > moveRange || offset.z < -moveRange) // プレイヤーのz座標が移動可能範囲から出ていたら
    {
        offset.z = (offset.z > moveRange) ? moveRange : -moveRange; // 範囲内に戻す
    }
}

/*
 * @brief プレイヤーの機銃関連の処理
 * @details プレイヤーの機銃の残弾表示,照準の表示,弾の処理
 */
void Player::Vulcan()
{
    DrawExtendGraph(580, 640, 850, 700, uiBox_01, true);
    /*機銃の残弾を表示する*/
    VulcanText.DrawTextWithSort(600, 850, "機銃: %.f", japaneseFontHandle, SORT_LEFT, 645, true, GetColor(0, 255, 0),
                                GetColor(50, 50, 50), ammo);
    Position = MV1GetPosition(ModelHandle); // プレイヤーのモデルの座標を取得する

    for (int i = 49; i >= 0; i--) // 50フレーム分のxy座標を配列に入れる,49から初めて0まで1づつ減らす
    {
        if (i == 0) // iが0のとき
        {
            // 現在の座標を配列に入れる
            bulletPositionX[i] = Position.x;
            bulletPositionY[i] = Position.y;
        }
        else // iが0以外のとき
        {
            // 値を1づつずらす
            bulletPositionX[i] = bulletPositionX[i - 1];
            bulletPositionY[i] = bulletPositionY[i - 1];
        }
    }
    // xy座標が10フレーム前でz座標が50前の位置を取得する
    VECTOR ReticleCenter =
        ConvWorldPosToScreenPos(VAdd(VGet(bulletPositionX[10], bulletPositionY[10], BasePosition.z), VGet(0, 0, 50)));
    // 取得した位置に照準を表示する
    DrawExtendGraph((int)ReticleCenter.x - 70, (int)ReticleCenter.y + 70, (int)ReticleCenter.x + 70,
                    (int)ReticleCenter.y - 70, reticleHandle, true);
    // 取得した位置に残弾のゲージを表示する
    DrawCircleGauge((int)ReticleCenter.x, (int)ReticleCenter.y, (double)((float)ammo / (float)maxAmmo) * 100,
                    reticleInsideGaugeHandle, 0, 0.1);
    // 機銃の弾の処理
    VulcanProjectile();
}

/*
 * @brief 機銃の弾の処理
 * @details 機銃の弾の移動,当たり判定等の処理を行う
 */
void Player::VulcanProjectile()
{

    // スペースキーが押されていて発射の間隔をあいていて残弾が0より多い
    if (CheckHitKey(KEY_INPUT_SPACE) && firingTimer > firingRate && ammo > 0)
    {
        // 時間計測用の変数を0にする
        firingTimer = 0;
        ammo--; // 残弾を1減らす

        for (int i = 0; i < 200; i++) // 弾のインスタンスの分繰り返す
        {
            // 弾が発射されていなかったら
            if (!bullets[i].isActivated)
            {
                PlaySoundMem(playerShotSound, DX_PLAYTYPE_BACK); // 射撃音を鳴らす
                bullets[i].isActivated = true; // 発射された状態か判断するflagをtrueにする
                bullets[i].target = VAdd(Position, VGet(0, 0, 90)); // 弾が到達すべき場所を指定する
                bullets[i].forward = VGet(0, 0, forwardSpeed + 4);  // 弾が前進する速度を指定する
                bullets[i].Position =
                    VAdd(Position, VGet(forward().x, -forward().y, forward().z)); // 弾が発射された位置を指定する
                break;                                                            // for文を抜ける
            }
        }
    }
    firingTimer += oneFlame; // 時間計測用の変数に1フレーム分の秒数を足す

    for (int i = 0; i < 200; i++) // 弾のインスタンスの分繰り返す
    {
        if (bullets[i].isActivated) // 弾が発射された場合
        {
            if (bullets[i].Update(
                    enemyObject->hitbox1,
                    enemyObject->hitbox2)) // 弾の毎フレーム呼ばれる処理を行い敵ののヒットボックスに当たった場合
            {
                if (difficulty == 0)
                {
                    enemyObject->Health -= 6;
                }
                else
                {
                    enemyObject->Health -= 3; // 敵の体力を3減らす
                }
                PlaySoundMem(hitSound, DX_PLAYTYPE_BACK); // 被弾時の効果音を鳴らす
            }
        }
    }
}

/*
 * @brief フレアの処理
 * @details フレアのクールダウン,UIの表示の処理を行う
 */
void Player::Flare()
{
    for (int i = 0; i < 10; i++) // フレアのインスタンスの数繰り返す
    {
        Flares[i].Passive(); // 射出されていないときも常に呼ばれる処理
    }

    // スペースキーが押されていてクールダウンが終わっていてすでに発射されていないとき
    if (CheckHitKey(KEY_INPUT_SPACE) && FlareCoolDown > FlareInterval && !Launching)
    {
        FlareCoolDown = 0;               // 時間計測用の変数に0を入れる
        Launching = true;                // フレアを射出しているかどうかのflagをtrueにする
        FlareAmount = 10;                // 発射するフレアの数の変数に10を入れる
        enemyObject->isGuideLost = true; // 敵がミサイルのロックを失ったかどうかのflagをtrueにする
    }

    if (FlareCoolDown > FlareInterval) // クールダウンが終わっているとき
    {
        DrawExtendGraph(580, 640, 850, 700, uiBox_01, true);
        // UIにフレアが使用可能と表示する
        FlareText.DrawTextWithSort(600, 850, "FLARE:READY", fontHandle, SORT_LEFT, 645, true, GetColor(0, 255, 0),
                                   GetColor(50, 50, 50));
    }
    else // クールダウンが終わっていないとき
    {
        DrawExtendGraph(580, 640, 850, 700, uiBox_02, true);
        // フレアが再使用可能になるまでの時間を表示する
        FlareText.DrawTextWithSort(600, 850, "FLARE: %.f", fontHandle, SORT_LEFT, 645, true, GetColor(255, 0, 0),
                                   GetColor(50, 50, 50), 5 - FlareCoolDown);
    }

    // フレアを射出中のとき
    if (Launching)
    {
        // フレアの射出の処理
        FlareLaunch();
    }

    for (int i = 0; i < 10; i++) // フレアのインスタンスの数繰り返す
    {
        if (Flares[i].isActivated) // 射出されているとき
        {
            // フレアの毎フレーム呼ばれる処理を行う
            Flares[i].Update();
        }
    }
    FlareCoolDown += oneFlame; // 時間計測用の変数に1フレーム分の秒数を足す
}

/*
 * @brief フレア射出時の処理
 * @details フレアの射出の間隔やインスタンス別に射出されたときの最初の処理を行う
 */
void Player::FlareLaunch()
{
    FlareFiringTimer += oneFlame; // 時間計測用の変数に1フレーム分の秒数を足す

    if (FlareFiringTimer > FlareFiringRate) // 前回の射出から十分な時間がたったら
    {
        for (int i = 0; i < 10; i++) // フレアのインスタンスの数繰り返す
        {
            if (!Flares[i].isActivated) // まだ射出されていないとき
            {
                Flares[i].isActivated = true; // 射出されたかどうかのflagをtrueにする
                Flares[i].forward =
                    VScale(VGet(upper().x, -upper().y * 0.2f, 5.7f), 0.3f); // フレアが進むべき方向と速度を入れる
                Flares[i].position = Position; // フレアの初期位置にプレイヤーの位置を入れる
                PlaySoundMem(flareSound, DX_PLAYTYPE_BACK); // フレアの射出音を再生する
                break;
            }
        }
        FlareFiringTimer = 0; // 時間計測用の変数に0を入れる
        FlareAmount--;        // 残りの射出すべきフレアの数を減らす
    }

    if (FlareAmount <= 0) // フレアを射出しきったら
    {
        Launching = false; // 射出中のflagをfalseにする
    }
}

/*
 * @brief プレイヤーの回転
 * @details 操作しているキーやtargetAngleの数値をもとに
 *          機体を回転させ回転すべきピッチ方向の角度を出す
 */
void Player::rotatePlayer()
{
    /* @brief 現在のプレイヤーのモデルの上方向の二次元ベクトルを取得するための変数 */
    float x, y;
    // 現在のプレイヤーのモデルの上方向の二次元ベクトルを取得する
    x = cos(atan2(upper().y, upper().x));
    y = sin(atan2(upper().y, upper().x));
    // 現在の角度と向くべき角度の差を求める
    float difInAngle = ((targetAngle.x * y) - (targetAngle.y * x));

    if (difInAngle > 0.05f) // 求めた差が0.05より大きい場合
    {
        Rotate(VGet(0, 0, -rotateSpeed * smooth(difInAngle, 0, 2))); // z軸を-方向に回転させる
    }
    else if (difInAngle < -0.05f) // 求めた差が-0.05未満場合
    {
        Rotate(VGet(0, 0, rotateSpeed * smooth(difInAngle, 0, 2))); // z軸を+方向に回転させる
    }

    // WASDキーのどれかが押されている場合
    if (CheckHitKey(KEY_INPUT_A) || CheckHitKey(KEY_INPUT_S) || CheckHitKey(KEY_INPUT_D) || CheckHitKey(KEY_INPUT_W))
    {
        if (difInAngle < -0.5f || difInAngle > 0.5f) // 求めた差が0.5より大きいか-0.5より小さいとき
        {
            targetAnglePitch = VGet(0, 0.3f * ((1 - abs(difInAngle)) / 0.5f),
                                    0.7f); // 求めた差をもとにピッチ方向の向くべき角度を求める
        }
        else
        {
            // Sキーだけが押されているとき
            if (!CheckHitKey(KEY_INPUT_A) && CheckHitKey(KEY_INPUT_S) && !CheckHitKey(KEY_INPUT_D) &&
                !CheckHitKey(KEY_INPUT_W))
            {
                targetAnglePitch = VGet(0, 0.3f, 0.7f); // 機体が下を向くようにする
            }
            else
            {
                targetAnglePitch = VGet(0, -0.3f * ((0.5f - abs(difInAngle)) / 0.5f),
                                        0.7f); // 求めた差をもとにピッチ方向の向くべき角度を求める
            }
        }
    }
    else // 何も操作されていないとき
    {
        targetAnglePitch = VGet(0, 0, 1); // 機体が正面を向くようにする
    }
}

/*
 * @brief プレイヤーのロールのみの処理
 * @details プレイヤーの回転処理からピッチに関するものを排除した関数
 */
void Player::rotateOnlyRoll()
{
    /* @brief 現在のプレイヤーのモデルの上方向の二次元ベクトルを取得するための変数 */
    float x, y;
    // 現在のプレイヤーのモデルの上方向の二次元ベクトルを取得する
    x = cos(atan2(upper().y - 0, upper().x - 0));
    y = sin(atan2(upper().y - 0, upper().x - 0));
    // 現在の角度と向くべき角度の差を求める
    float difInAngle = ((targetAngle.x * y) - (targetAngle.y * x));
    if (difInAngle > 0.05f) // 求めた差が0.05より大きい場合
    {
        Rotate(VGet(0, 0, -rotateSpeed * smooth(difInAngle, 0, 2))); // 求めた差をもとにピッチ方向の向くべき角度を求める
    }
    else if (difInAngle < -0.05f) // 機体が下を向くようにする
    {
        Rotate(VGet(0, 0, rotateSpeed * smooth(difInAngle, 0, 2))); // 求めた差をもとにピッチ方向の向くべき角度を求める
    }
}

void Player::pitch()
{
    /* @brief 現在のプレイヤーのモデルの正面方向の二次元ベクトルを取得するための変数 */
    float z, y;
    // 現在のプレイヤーのモデルの正面方向の二次元ベクトルを取得する
    z = cos(atan2(forward().y - 0, forward().z - 0));
    y = sin(atan2(forward().y - 0, forward().z - 0));
    // 現在の角度と向くべき角度の差を求める
    float difInAngle = (((targetAnglePitch.z * 0.4f) * y) - ((targetAnglePitch.y * 0.4f) * z));
    if (Rotation.x <= 0.4f && Rotation.x >= -0.4f) // x軸の回転が+-0.4以内か
    {
        // 差が0.005よりも大きく0.5未満の場合
        if (difInAngle > 0.005f && difInAngle < 0.5f)
        {
            Rotate(VGet(-rotateSpeed * smooth(difInAngle, 0, 1), 0, 0)); //
        }
        else if (difInAngle < -0.005f && difInAngle > -0.5f)
        {
            Rotate(VGet(rotateSpeed * smooth(difInAngle, 0, 1), 0, 0));
        }
        else if (difInAngle < -0.5f)
        {
            Rotate(VGet(-rotateSpeed * smooth(difInAngle, 0, 1), 0, 0));
        }
        else if (difInAngle > 0.5f)
        {
            Rotate(VGet(rotateSpeed * smooth(difInAngle, 0, 1), 0, 0));
        }
        else if (!CheckHitKey(KEY_INPUT_A) && !CheckHitKey(KEY_INPUT_S) && !CheckHitKey(KEY_INPUT_D) &&
                 !CheckHitKey(KEY_INPUT_W))
        {
            Rotation = MV1GetRotationXYZ(ModelHandle);
            SetRotation(VGet(0, Rotation.y, Rotation.z));
        }
    }
    else if (Rotation.x > 0.4f)
    {
        Rotation = MV1GetRotationXYZ(ModelHandle);
        SetRotation(VGet(0.4f, Rotation.y, Rotation.z));
    }
    else
    {
        Rotation = MV1GetRotationXYZ(ModelHandle);
        SetRotation(VGet(-0.4f, Rotation.y, Rotation.z));
    }
}

bool Player::Transition()
{
    autoEvade();
    VECTOR targetCameraPosition = VAdd(VGet(offset.x, offset.y + 2, -16), BasePosition);
    VECTOR cameraToTargetVector =
        VGet(targetCameraPosition.x - CameraPosition.x, targetCameraPosition.y - CameraPosition.y,
             targetCameraPosition.z - CameraPosition.z);
    float distance =
        sqrtf((cameraToTargetVector.x * cameraToTargetVector.x) + (cameraToTargetVector.y * cameraToTargetVector.y) +
              (cameraToTargetVector.z * cameraToTargetVector.z));
    BasePosition = VAdd(VGet(0, 0, forwardSpeed), BasePosition);
    pitch();
    Move(VAdd(BasePosition, offset));
    if (distance < 1.5f)
    {
        rotatePlayer();
        CameraPosition = VAdd(VGet(offset.x, offset.y + 2, -16), BasePosition);
        SetCameraPositionAndTarget_UpVecY(VAdd(VGet(offset.x, offset.y + 2, -16), BasePosition),
                                          VAdd(VGet(offset.x, offset.y, TARGET_CAMERA_POSZ), BasePosition));
        return true;
    }
    else
    {
        CameraPosition = VAdd(VAdd(CameraPosition, VScale(VNorm(VGet(targetCameraPosition.x - CameraPosition.x,
                                                                     targetCameraPosition.y - CameraPosition.y,
                                                                     targetCameraPosition.z - CameraPosition.z)),
                                                          0.17f)),
                              VGet(0, 0, forwardSpeed));
        SetCameraPositionAndTarget_UpVecY(VGet(offset.x, offset.y + 2, CameraPosition.z),
                                          VAdd(VGet(offset.x, offset.y, TARGET_CAMERA_POSZ), BasePosition));
        return false;
    }
}

void Player::autoEvade()
{
    float distance = sqrtf((-offset.x * -offset.x) + (-offset.y * -offset.y));
    if (distance >= 1)
    {
        targetAngle = VNorm(VGet(-offset.x, -offset.y, 0));
        offset = VAdd(VScale(targetAngle, moveSpeed * timeScale), offset);
        targetAngle.y = -targetAngle.y;
        rotatePlayer();
    }
    else
    {
        targetAngle = VGet(0, -NEUTRAL_ANGLE_Y, 0);
        rotatePlayer();
    }
}

void Player::Immortal()
{
    if (isImmortal && ImmortalTimer.MeasureTimer(2))
    {
        isImmortal = false;
        isInvisible = false;
        ImmortalTimer.RestartTimer();
    }
    if (isImmortal && stroboTimer.MeasureTimer(0.2f))
    {
        isInvisible = isInvisible ? false : true;
        stroboTimer.RestartTimer();
    }
}