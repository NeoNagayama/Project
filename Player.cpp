#include "Player.h"
#include "base.h"
#include<cmath>
int test;
/**
 * @brief 起動時に1度だけ呼び出される処理
 * @details モデルのロード,初期座標の設定,モデルのスケール等の処理を行う
 */

void Player::InitialProcess()
{
    //プレイヤーのモデルをロードする
    ModelHandle = MV1LoadModel("Resource/PlayerModel.mv1");
    //プレイヤーの初期座標を設定する
    MV1SetPosition(ModelHandle, VGet(0, -5, -0));
    //プレイヤーのスケールを設定する
    MV1SetScale(ModelHandle, VGet(6, 6, 6));
    //プレイヤーの座標を入れる変数に初期座標を入れる
    Position = VGet(0, -5, -0); 
    //プレイヤーのモデルのすべてのマテリアルの設定を変更する
    for (int i = 0; i < MV1GetMaterialNum(ModelHandle); i++)
    {
        MV1SetMaterialDifColor(ModelHandle, i, GetColorF(0.7f, 0.7f, 0.5f, 1.0f));
        MV1SetMaterialAmbColor(ModelHandle, i, GetColorF(0.2f, 0.2f, 0.4f, 1.0f));
        MV1SetMaterialSpcColor(ModelHandle, i, GetColorF(0.4f, 0.4f, 0.4f, 1));
        MV1SetMaterialEmiColor(ModelHandle, i, GetColorF(0.8f, 0.8f, 0.8f, 0.2f));
        MV1SetMaterialSpcPower(ModelHandle, i, 6);
    }
    //プレイヤーが発射する弾のモデルのロード等の処理を行う
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
    //残弾数
    ammo = 200;
    //開始時のカメラのx座標
    startCameraOffsetx = 6;
    //カメラのズーム倍率
    cameraZoom = 0.6f;
    //カメラの注視点のz座標
    target = 0;
    //体力
    Health = 100;
    //プレイヤーのxy平面上の位置
    offset = VGet(0, -5, 0);
    //プレイヤーの開始位置のz座標
    BasePosition.z = -200;
    //プレイヤーの開始位置
    Position = VGet(0, 0, -200);
    //プレイヤーの移動速度
    forwardSpeed = DEFAULTSPEED;
    //プレイヤーの当たり判定の設定
    SetHitBox(2, 2);
    //カメラがプレイヤーの後ろについて移動し始める座標
    cameraStartThleshold = 0;
    //死亡していない
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

void Player::camSetUp(int pos)
{
    //カメラの位置をプレイヤーに追従させる位置を設定する
    cameraStartThleshold = pos + 200;
    //カメラ演出時のカメラのx軸上のずれ
    startCameraOffsetx = 6;
    //カメラをズームさせる
    cameraZoom = 0.6f;
    //カメラの注視点のz座標をプレイヤーのz座標からずらさないようにする
    target = 0;

}
/**
 * @brief プレイヤーの毎フレーム呼ばれる処理
 * @details プレイヤーの毎フレーム呼ばれる処理
 *
 * @param bool mode ゲームが追跡フェーズに入っているか
 */

void Player::mainProcess(bool mode)
{
    //体力が0でないとき
    if (Health > 0)
    {
        //当たり判定を設定する
        SetHitBox(2, 2);
        //DrawSphere3D(VAdd(VScale(VGet(-forward().x, forward().y, -forward().z), 5), Position), 0.2f, 6, GetColor(255, 255, 255), GetColor(255, 255, 255), true);
        //プレイヤーのz座標に移動速度にtimeScaleをかけた数値を足す
        BasePosition = VAdd(VGet(0, 0, forwardSpeed *timeScale), BasePosition);
        //プレイヤーの入力周りの処理
        KeyInput();
        //プレイヤーのxy平面の移動処理
        PlayerMoveXY();
        //プレイヤーの位置をモデルに反映する
        Move(VAdd(BasePosition, offset));
        //プレイヤーの回転処理
        rotatePlayer();
        //プレイヤーのピッチ方向の回転処理
        pitch();
        //ゲームが追跡フェーズの時
        if (mode)
        {
            //カメラの位置をセットする
            SetCameraPositionAndTarget_UpVecY(VAdd(VGet(offset.x, offset.y + 2, -16), BasePosition), VAdd(VGet(offset.x, offset.y, 20), BasePosition));
            //カメラの座標を変数に格納する
            CameraPosition = VAdd(VGet(offset.x, offset.y + 2, -16), BasePosition), VAdd(VGet(offset.x, offset.y, 20), BasePosition);
            //機銃処理
            Vulcan();
        }
        //ゲームが逃走フェーズの時
        else
        {
            //カメラの位置をセットする
            SetCameraPositionAndTarget_UpVecY(VAdd(VGet(offset.x, offset.y + 2, -20), BasePosition), VAdd(VGet(offset.x, offset.y, 20), BasePosition));
            //カメラの座標を変数に格納する
            CameraPosition = VAdd(VGet(offset.x, offset.y + 2, -20), BasePosition), VAdd(VGet(offset.x, offset.y, 20), BasePosition);
            //フレアの処理
            Flare();

        }
    }
    //体力が0以下の時
    else
    {
        //プレイヤーのy座標を下げる
        offset.y -= 0.2f;
        //プレイヤーのz座標を前に進める
        BasePosition.z += 1.2f;
        //プレイヤーの座標をモデルに反映させる
        MV1SetPosition(ModelHandle, VAdd(BasePosition, offset));
        //z軸で回転させ続ける
        MV1SetRotationXYZ(ModelHandle, VAdd(MV1GetRotationXYZ(ModelHandle), VGet(0, 0, 0.1f)));
        //プレイヤーの座標が一定以下になったら
        if (offset.y < -13)
        {
            exp2.SetPosition(MV1GetPosition(ModelHandle));
        }
    }
    //体力が0になった後に一度だけ呼ばれる処理
    if (!isDead && Health <= 0)
    {
        //爆発エフェクトの位置を設定する
        exp.SetPosition(Position);
        //爆発音を流す
        PlaySoundMem(explosionSound, DX_PLAYTYPE_BACK);
        //二度処理を行わないためのフラグをtrueにする
        isDead = true;
    }
    //1回目の爆発エフェクトの処理
    exp.DrawExprosion();
    //2回目の爆発エフェクトの処理
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
    //プレイヤーのz座標に移動速度にtimeScaleをかけた数値を足す
    BasePosition = VAdd(VGet(0, 0, DEFAULTSPEED * timeScale), BasePosition);
    //プレイヤーの座標をモデルに反映する
    Move(VAdd(BasePosition, offset));
    //プレイヤーの回転の角度を正面にする
    targetAngle = VGet(0, -0.99f, 0);
    //プレイヤーの回転処理
    rotatePlayer();
    //プレイヤーのピッチ方向の角度を正面にする
    targetAnglePitch = VGet(0, 0, 1);
    //プレイヤーのピッチ方向の回転処理
    pitch();
    //ゲーム開始時でないとき
    if (mode)
    {
        //カメラの位置をセットする
        SetCameraPositionAndTarget_UpVecY(VAdd(VGet(offset.x, offset.y + 2, -16), BasePosition), VAdd(VGet(offset.x, offset.y, 20), BasePosition));
        //変数にカメラの座標を格納する
        CameraPosition = VAdd(VGet(offset.x, offset.y + 2, -16), BasePosition), VAdd(VGet(offset.x, offset.y, 20), BasePosition);
    }
    //ゲーム開始時の時
    else
    {
        //カメラがプレイヤーの後ろを追従し始めるz座標の20先でかつx軸の座標が0よりも多いとき
        if (Position.z >= cameraStartThleshold + 20 && startCameraOffsetx >0)
        {
            //カメラのx座標を減らし続ける
            startCameraOffsetx -= 0.1f;
            
        }
        //プレイヤーの座標がカメラがプレイヤーの後ろを追従し始めるz座標の20先よりも後ろの時
        if (Position.z >= cameraStartThleshold + 20)
        {
            //カメラの位置をセットする
            SetCameraPositionAndTarget_UpVecY(VAdd(VGet(offset.x + startCameraOffsetx, offset.y + 2, -20), BasePosition), VAdd(VGet(offset.x, offset.y,+target),BasePosition));
            //変数にカメラの座標を格納する
            CameraPosition = VAdd(VGet(offset.x + startCameraOffsetx, offset.y + 2, -20), BasePosition);
            //カメラのズームが1未満の時
            if (cameraZoom < 1)
            {
                //カメラのズームを増やし続ける
                cameraZoom += 0.02f;
            }
            //カメラのズームが1以上の時
            else
            {
                //カメラのズームを1にする
                cameraZoom = 1;
            }
            //カメラの注視点のz座標が20未満の時
            if (target < 20)
            {
                //注視点のz座標を増やし続ける
                target += 0.5f;
            }
            //そうでないときは20にする
            else target = 20;
        }
        //プレイヤーの座標がカメラがプレイヤーの後ろを追従し始めるz座標の20先よりも前の時
        else
        {
            //カメラの位置をセットする
            SetCameraPositionAndTarget_UpVecY(VGet(offset.x + startCameraOffsetx, offset.y + 2, cameraStartThleshold), VAdd(VGet(offset.x, offset.y, target), BasePosition));
            //変数にカメラの座標を格納する
            CameraPosition = VGet(offset.x + startCameraOffsetx, offset.y + 2, cameraStartThleshold);
        }
        //カメラのズームの倍率を変更する
        SetupCamera_Perspective(cameraZoom);
    }
}
/**
 * @brief  クリア時の処理
 * @details クリア時のプレイヤーの移動と回転に関する処理
 */

void Player::clearProcess()
{
    //障害物を回避する処理
    autoEvade();
    //targetAnglePitchに干渉しない回転処理
    rotateOnlyRoll();
    //ピッチ方向の回転を水平にする
    targetAnglePitch = VGet(0, 0, 1);
    //ピッチ方向の回転処理
    pitch();
    //プレイヤーのz座標に移動速度にtimeScaleをかけた数値を足す
    BasePosition = VAdd(VGet(0, 0, forwardSpeed * timeScale), BasePosition);
    //プレイヤーの座標をモデルに反映する
    Move(VAdd(BasePosition, offset));
    //ロール方向の回転を水平にする
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
    //Wを押したとき
    if (CheckHitKey(KEY_INPUT_W))
    {
        //上方向に移動する処理
        InputUp(speed);
    }
    //Sを押したとき
    else if (CheckHitKey(KEY_INPUT_S))
    {
        //下方向に移動する処理
        InputDown(speed);
    }
    //Dキーを押していてかつx座標の速度が0.7未満の時
    else if (CheckHitKey(KEY_INPUT_D) && x < 0.7f)
    {
        //x座標の移動速度を上げる
        x += speed;
        //移動速度の上限を0.7にする
        speedLimit = 0.7f;
        //プレイヤーの回転すべき角度を変更する
        targetAngle = VGet(0.6f, -0.4f, 0);
    }
    //Aキーを押していてかつx座標の速度が-0.7より多い時
    else if (CheckHitKey(KEY_INPUT_A) && x > -0.7f)
    {
        //x座標の移動速度を減らす
        x -= speed;
        //移動速度の上限を0.7にする
        speedLimit = 0.7f;
        //プレイヤーの回転すべき角度を変更する
        targetAngle = VGet(-0.6f, -0.4f, 0);
    }
    //x座標y座標別の操作していないときの処理
    InputNeutral(speed);
    //移動速度が上限を超えないようにする処理
    Limit();
}
/**
 * @brief 上方向に移動しているときの処理
 * @details 上方向に移動する捜査をしているときの
 */

void Player::InputUp(float speed)
{
    if (CheckHitKey(KEY_INPUT_D))
    {
        x += speed;
        speedLimit = 0.49f;
        targetAngle = VGet(0.5f, -0.5f, 0);
    }
    else if (CheckHitKey(KEY_INPUT_A))
    {
        x -= speed;
        speedLimit = 0.49f;
        targetAngle = VGet(-0.5f, -0.5f, 0);
    }
    else
    {
        speedLimit = 0.7f;
        targetAngle = VGet(0, -1, 0);
    }
    y += speed;
}
void Player::InputDown(float speed)
{
    if (CheckHitKey(KEY_INPUT_D))
    {
        x += speed;
        speedLimit = 0.49f;
        targetAngle = VGet(0.5f, 0.5f, 0);
    }
    else if (CheckHitKey(KEY_INPUT_A))
    {
        x -= speed;
        speedLimit = 0.49f;
        targetAngle = VGet(-0.5f, 0.5f, 0);
    }
    else
    {
        speedLimit = 0.7f;
        targetAngle = VGet(0, 0.99f, 0);
    }
    y -= speed;
}
void Player::InputNeutral(float speed)
{

    if (!CheckHitKey(KEY_INPUT_A) && !CheckHitKey(KEY_INPUT_S) && !CheckHitKey(KEY_INPUT_D) && !CheckHitKey(KEY_INPUT_W))
    {
        targetAngle = VGet(0, -0.99f, 0);
    }
    if (!CheckHitKey(KEY_INPUT_A) && !CheckHitKey(KEY_INPUT_D))
    {
        if (x > 0.1f)
        {
            x -= speed;
        }
        else if (x < -0.1f)
        {
            x += speed;
        }
        else
        {
            x = 0;
        }
    }
    if (!CheckHitKey(KEY_INPUT_S) && !CheckHitKey(KEY_INPUT_W))
    {
        if (y > 0.1f)
        {
            y -= speed;
        }
        else if (y < -0.1f)
        {
            y += speed;
        }
        else
        {
            y = 0;
        }
    }
}
void Player::Limit()
{
    if (x >= speedLimit)
    {
        x = speedLimit;
    }
    else if (x <= -speedLimit)
    {
        x = -speedLimit;
    }
    if (y >= speedLimit)
    {
        y = speedLimit;
    }
    else if (y <= -speedLimit)
    {
        y = -speedLimit;
    }
}
void Player::PlayerMoveXY()
{
    float xSpeed, ySpeed;
    xSpeed = (offset.x > moveRange || offset.x < -moveRange) ? 0 : x * moveSpeed;
    ySpeed = (offset.y > moveRange|| offset.y < -moveRange) ? 0:y * moveSpeed;
    if (Rotation.y == DegToRad(90))
    {
        offset = VAdd(VGet(0, ySpeed, -xSpeed), offset);
    }
    else if (Rotation.y == DegToRad(-90))
    {
        offset = VAdd(VGet(0, ySpeed, xSpeed), offset);
    }
    else
    {
        offset = VAdd(VGet(xSpeed, ySpeed, 0), offset);
    }
    if (offset.x > moveRange || offset.x < -moveRange)
    {
        offset.x = (offset.x > moveRange) ? moveRange : -moveRange;
    }
    if (offset.y > moveRange || offset.y < -moveRange)
    {
        offset.y = (offset.y > moveRange) ? moveRange : -moveRange;
    }
    if (offset.z > moveRange || offset.z < -moveRange)
    {
        offset.z = (offset.z > moveRange) ? moveRange : -moveRange;
    }
}
void Player::Vulcan()
{
    VulcanText.DrawTextWithSort(120, 1920, "機銃: %.f", japaneseFontHandle, SORT_LEFT, 600, true, GetColor(0, 255, 0), GetColor(50, 50, 50), ammo);
    Position = MV1GetPosition(ModelHandle);
    for (int i = 49; i >= 0; i--)
    {
        if (i == 0)
        {
            bulletPositionX[i] = Position.x;
            bulletPositionY[i] = Position.y;
        }
        else
        {
            bulletPositionX[i] = bulletPositionX[i - 1];
            bulletPositionY[i] = bulletPositionY[i - 1];
        }
    }
    VECTOR ReticleCenter = ConvWorldPosToScreenPos(VAdd(VGet(bulletPositionX[10], bulletPositionY[10], BasePosition.z), VGet(0, 0, 50)));
    DrawExtendGraph((int)ReticleCenter.x- 70, (int)ReticleCenter.y + 70, (int)ReticleCenter.x + 70, (int)ReticleCenter.y - 70, reticleHandle, true);


    DrawCircleGauge((int)ReticleCenter.x, (int)ReticleCenter.y, (double)((float)ammo / (float)maxAmmo) * 100, reticleInsideGaugeHandle, 0,0.1);
    VulcanProjectile();
   
}
void Player::VulcanProjectile()
{
    if (CheckHitKey(KEY_INPUT_SPACE) && firingTimer > firingRate && ammo > 0)
    {
        firingTimer = 0;
        ammo--;
        for (int i = 0; i < 200; i++)
        {
            if (!bullets[i].isActivated)
            {

                PlaySoundMem(playerShotSound, DX_PLAYTYPE_BACK);
                bullets[i].isActivated = true;
                bullets[i].target = VAdd(Position, VGet(0, 0, 90));
                bullets[i].forward = VGet(0, 0, forwardSpeed + 4);
                bullets[i].StartPosition = VAdd(Position, VGet(forward().x, -forward().y, forward().z));
                break;
            }
        }
    }
    firingTimer += oneFlame;
    for (int i = 0; i < 200; i++)
    {
        if (bullets[i].isActivated)
        {
            if (bullets[i].mainProcess(enemyObject->hitbox1, enemyObject->hitbox2))
            {
                enemyObject->Health -= 3;
                PlaySoundMem(hitSound, DX_PLAYTYPE_BACK);
            }
        }
    }
}
void Player::Flare()
{
    for (int i = 0; i < 10; i++)
    {
        Flares[i].Passive();
    }
    if (CheckHitKey(KEY_INPUT_SPACE) && FlareCoolDown > FlareInterval && !Launching)
    {
        FlareCoolDown = 0;
        Launching = true;
        FlareAmount = 10;
        enemyObject->isGuideLost = true;
    }
    if (FlareCoolDown > FlareInterval)
    {
        FlareText.DrawTextWithSort(120, 1920, "FLARE:READY", fontHandle, SORT_LEFT, 600, true, GetColor(0, 255, 0), GetColor(50, 50, 50));
    }
    else
    {
        FlareText.DrawTextWithSort(120, 1920, "FLARE: %.f", fontHandle, SORT_LEFT, 600, true, GetColor(0, 255, 0), GetColor(50, 50, 50),  5-FlareCoolDown);
    }
    if (Launching)
    {
        FlareLaunch();
    }
    for (int i = 0; i < 10; i++)
    {
        if (Flares[i].isActivated)
        {
            Flares[i].mainProcess();
        }
    }
    FlareCoolDown += 0.016f;
    
}
void Player::FlareLaunch()
{
    FlareFiringTimer += 0.016f;
    if (FlareFiringTimer > FlareFiringRate)
    {
        for (int i = 0; i < 10; i++)
        {
            if (!Flares[i].isActivated)
            {
                Flares[i].isActivated = true;
                Flares[i].forward = VScale(VGet(upper().x, -upper().y * 0.2f, 5.7f), 0.3f);
                Flares[i].position = Position;
                PlaySoundMem(flareSound, DX_PLAYTYPE_BACK);
                break;
            }
        }
        FlareFiringTimer = 0;
        FlareAmount--;
    }
    if (FlareAmount <= 0)
    {
        Launching = false;
    }
}
void Player::rotatePlayer()
{
    float x, y;
    x = cos(atan2(upper().y - 0, upper().x - 0));
    y = sin(atan2(upper().y - 0, upper().x - 0));
    float difInAngle = ((targetAngle.x * y) - (targetAngle.y * x));
    if (difInAngle > 0.05f)
    {
        Rotate(VGet(0, 0, -rotateSpeed * smooth(difInAngle, 0, 2)));
    }
    else if (difInAngle < -0.05f)
    {
        Rotate(VGet(0, 0, rotateSpeed * smooth(difInAngle, 0, 2)));
        
    }
    if (CheckHitKey(KEY_INPUT_A) || CheckHitKey(KEY_INPUT_S) || CheckHitKey(KEY_INPUT_D) || CheckHitKey(KEY_INPUT_W))
    {
        if (difInAngle < -0.5f || difInAngle > 0.5f)
        {
            targetAnglePitch = VGet(0, 0.3f* ((1-abs(difInAngle))/0.5f), 0.7f );
        }
        else
        {
            if (!CheckHitKey(KEY_INPUT_A) && CheckHitKey(KEY_INPUT_S) && !CheckHitKey(KEY_INPUT_D) && !CheckHitKey(KEY_INPUT_W))
            {
                targetAnglePitch = VGet(0, 0.3f, 0.7f);
            }
            else
            {
                targetAnglePitch = VGet(0, -0.3f*((0.5f-abs(difInAngle))/0.5f), 0.7f);
            }
        }
    }
    else
    {
        targetAnglePitch = VGet(0, 0, 1);
    }

    
}
void Player::rotateOnlyRoll()
{
    float x, y;
    x = cos(atan2(upper().y - 0, upper().x - 0));
    y = sin(atan2(upper().y - 0, upper().x - 0));
    float difInAngle = ((targetAngle.x * y) - (targetAngle.y * x));
    if (difInAngle > 0.05f)
    {
        Rotate(VGet(0, 0, -rotateSpeed * smooth(difInAngle, 0, 2)));
    }
    else if (difInAngle < -0.05f)
    {
        Rotate(VGet(0, 0, rotateSpeed * smooth(difInAngle, 0, 2)));

    }
}

void Player::pitch()
{
    float z, y;
    z = cos(atan2(forward().y - 0, forward().z - 0));
    y = sin(atan2(forward().y - 0, forward().z - 0));
    float difInAngle = (((targetAnglePitch.z*0.4f) * y) - ((targetAnglePitch.y * 0.4f) * z));
    if (Rotation.x <= 0.4f && Rotation.x >= -0.4f)
    {
        if (difInAngle > 0.005f && difInAngle < 0.5f)
        {
            Rotate(VGet(-rotateSpeed * smooth(difInAngle, 0, 1), 0, 0));
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
        else if(!CheckHitKey(KEY_INPUT_A) && !CheckHitKey(KEY_INPUT_S) && !CheckHitKey(KEY_INPUT_D) && !CheckHitKey(KEY_INPUT_W) )
        {
            Rotation = MV1GetRotationXYZ(ModelHandle);
            SetRotation(VGet(0, Rotation.y, Rotation.z));
        }
    }
    else if(Rotation.x > 0.4f)
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
    VECTOR targetCameraPosition = VAdd(VGet(offset.x , offset.y + 2 , -16), BasePosition);
    VECTOR cameraToTargetVector = VGet(targetCameraPosition.x - CameraPosition.x, targetCameraPosition.y - CameraPosition.y, targetCameraPosition.z - CameraPosition.z);
    float distance = sqrtf((cameraToTargetVector.x * cameraToTargetVector.x) + (cameraToTargetVector.y * cameraToTargetVector.y) + (cameraToTargetVector.z * cameraToTargetVector.z));
    BasePosition = VAdd(VGet(0, 0, forwardSpeed), BasePosition);
    pitch();
    Move(VAdd(BasePosition, offset));
    if (distance <1.5f)
    {
        rotatePlayer();
        CameraPosition = VAdd(VGet(offset.x, offset.y + 2, -16), BasePosition);
        SetCameraPositionAndTarget_UpVecY(VAdd(VGet(offset.x, offset.y + 2, -16), BasePosition), VAdd(VGet(offset.x, offset.y, TARGET_CAMERA_POSZ), BasePosition));
        return true;
    }
    else
    {
        CameraPosition = VAdd(VAdd(CameraPosition, VScale(VNorm(VGet(targetCameraPosition.x - CameraPosition.x, targetCameraPosition.y - CameraPosition.y, targetCameraPosition.z - CameraPosition.z)), 0.17f)), VGet(0, 0, forwardSpeed));
        SetCameraPositionAndTarget_UpVecY(VGet(offset.x, offset.y + 2, CameraPosition.z), VAdd(VGet(offset.x, offset.y, TARGET_CAMERA_POSZ), BasePosition));
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