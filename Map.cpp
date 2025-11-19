#include "Map.h"
void mapBase::DrawbaseOutline()
{
    VECTOR edgePosition1 = VGet(position.x - 15, position.y - 15, position.z - 40);
    VECTOR edgePosition2 = VGet(position.x + 15, position.y + 15, position.z + 40);/*
    DrawCube3D(edgePosition1, VGet(edgePosition1.x - 1, edgePosition2.y, edgePosition2.z), GetColor(100, 100, 100), GetColor(0, 0, 0), TRUE);*/
    DrawCube3D(edgePosition1, VGet(edgePosition2.x, edgePosition1.y-1, edgePosition2.z), GetColor(100, 100, 100), GetColor(0, 0, 0), TRUE);/*
    DrawCube3D(edgePosition2, VGet(edgePosition2.x + 1, edgePosition1.y, edgePosition1.z), GetColor(100, 100, 100), GetColor(0, 0, 0), TRUE);*/
    MV1SetPosition(BaseWallHandle,VGet(position.x - 20,position.y,position.z));
    MV1SetPosition(BaseWallHandleRight, VGet(position.x + 20, position.y, position.z));
    MV1DrawModel(BaseWallHandle);
    MV1DrawModel(BaseWallHandleRight);
}
bool mapBase::DamageBox(bool upper, bool lower, bool right, bool left, bool center, VECTOR hitbox1, VECTOR hitbox2)
{
    isHit = false;
    if (upper)
    {
        VECTOR edge1 = VGet(position.x - 15, position.y + 7, position.z - 40);
        VECTOR edge2 = VGet(position.x + 15, position.y + 15, position.z + 40);
        MV1SetPosition(upperHandle, VGet(position.x, position.y + 11, position.z));
        MV1DrawModel(upperHandle);
        isHit = checkHit(edge1, edge2, hitbox1, hitbox2, isHit);
    }
    if (lower)
    {
        VECTOR edge1 = VGet(position.x - 15, position.y -15, position.z - 40);
        VECTOR edge2 = VGet(position.x + 15, position.y -7, position.z + 40);
        MV1SetPosition (lowerHandle,VGet(position.x, position.y - 11, position.z));
        MV1DrawModel(lowerHandle);
        isHit = checkHit(edge1, edge2, hitbox1, hitbox2, isHit);
    }
    if (right)
    {
        VECTOR edge1 = VGet(position.x + 7, position.y - 15, position.z - 40);
        VECTOR edge2 = VGet(position.x + 15, position.y + 15, position.z + 40);
        MV1SetPosition(rightwallHandle, VGet(position.x + 11, position.y, position.z));
        MV1DrawModel(rightwallHandle);
        isHit = checkHit(edge1, edge2, hitbox1, hitbox2, isHit);
    }
    if (left)
    {
        VECTOR edge1 = VGet(position.x - 15, position.y - 15, position.z - 40);
        VECTOR edge2 = VGet(position.x - 7, position.y + 15, position.z + 40);
        MV1SetPosition(leftwallHandle, VGet(position.x-11, position.y, position.z));
        MV1DrawModel(leftwallHandle);
        isHit = checkHit(edge1, edge2, hitbox1, hitbox2, isHit);
    }
    if (center)
    {
        VECTOR edge1 = VGet( -7, position.y - 15, position.z - 40);
        VECTOR edge2 = VGet(7, position.y + 15, position.z + 40);
        DrawDamageBox(edge1, edge2);
        isHit = checkHit(edge1, edge2,hitbox1, hitbox2, isHit);
    }
    return isHit;
}
void mapBase::DrawDamageBox(VECTOR edge1, VECTOR edge2)
{
    DrawCube3D(edge1, edge2, GetColor(120, 120, 120), GetColor(60, 60, 60), TRUE);

}
bool mapBase::checkHit(VECTOR edge1, VECTOR edge2, VECTOR playerEdge1, VECTOR playerEdge2,bool current)
{
    if(((playerEdge1.x >= edge1.x && playerEdge1.x <= edge2.x) ||(playerEdge2 .x >= edge1.x && playerEdge2.x <= edge2.x))
        &&((playerEdge1.y >= edge1.y && playerEdge1.y <= edge2.y) || (playerEdge2.y >= edge1.y && playerEdge2.y <= edge2.y))
            && ((playerEdge1.z >= edge1.z && playerEdge1.z <= edge2.z) || (playerEdge2.z >= edge1.z && playerEdge2.z <= edge2.z)))
    {
        return true;
    }
    else
    {
        return current;
    }
}
void mapBase::BaseSetUp()
{

    lowerHandle = MV1DuplicateModel(lowerObstacleHandle);
    upperHandle = MV1DuplicateModel(lowerObstacleHandle);
    BaseWallHandle = MV1DuplicateModel(wallHandle);
    BaseWallHandleRight = MV1DuplicateModel(wallHandle);
    rightwallHandle = MV1DuplicateModel(lowerObstacleHandle);
    MV1SetRotationXYZ(rightwallHandle, VGet(0, 0, PI/2));
    leftwallHandle = MV1DuplicateModel(lowerObstacleHandle);
    MV1SetRotationXYZ(leftwallHandle, VGet(0, 0, PI/2));
    MV1SetScale(rightwallHandle, VGet(0.01f, 0.01f, 0.012f));
    MV1SetScale(leftwallHandle, VGet(0.01f, 0.01f, 0.012f));
    MV1SetScale(lowerHandle, VGet(0.01f, 0.01f, 0.01f));
    MV1SetScale(upperHandle, VGet(0.01f, 0.01f, 0.01f));
    for (int i = 0; i < MV1GetMaterialNum(lowerHandle); i++)
    {
        MV1SetMaterialDifColor(lowerHandle, i, GetColorF(1.0f, 0.7f, 0.7f, 1.0f));
        MV1SetMaterialAmbColor(lowerHandle, i, GetColorF(0.2f, 0.2f, 0.2f, 1.0f));
        MV1SetMaterialSpcColor(lowerHandle, i, GetColorF(0.4f, 0.4f, 0.4f, 1));
        MV1SetMaterialEmiColor(lowerHandle, i, GetColorF(0.8f, 0.8f, 0.8f, 0.2f));
        MV1SetMaterialSpcPower(lowerHandle, i, 6);
    }
    for (int i = 0; i < MV1GetMaterialNum(upperHandle); i++)
    {
        MV1SetMaterialDifColor(upperHandle, i, GetColorF(1.0f, 0.7f, 0.7f, 1.0f));
        MV1SetMaterialAmbColor(upperHandle, i, GetColorF(0.2f, 0.2f, 0.2f, 1.0f));
        MV1SetMaterialSpcColor(upperHandle, i, GetColorF(0.4f, 0.4f, 0.4f, 1));
        MV1SetMaterialEmiColor(upperHandle, i, GetColorF(0.8f, 0.8f, 0.8f, 0.2f));
        MV1SetMaterialSpcPower(upperHandle, i, 6);
    }
    materialSetUp(BaseWallHandle);
    materialSetUp(BaseWallHandleRight);
    materialSetUp(rightwallHandle);
    materialSetUp(leftwallHandle);
}
void mapBase::materialSetUp(int handle)
{
    for (int i = 0; i < MV1GetMaterialNum(handle); i++)
    {
        MV1SetMaterialDifColor(handle, i, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
        MV1SetMaterialAmbColor(handle, i, GetColorF(0.4f, 0.4f, 0.4f, 1.0f));
        MV1SetMaterialSpcColor(handle, i, GetColorF(0.4f, 0.4f, 0.4f, 1));
        MV1SetMaterialEmiColor(handle, i, GetColorF(0.8f, 0.8f, 0.8f, 0.4f));
        MV1SetMaterialSpcPower(handle, i, 2);
    }
}
bool antiAir::DamageZone(bool upper, bool lower, bool right, bool left, VECTOR hitbox1, VECTOR hitbox2)
{
    isHit = false;
    if (upper)
    {
        VECTOR edge1 = VGet(position.x - 15, position.y + 7, position.z - 40);
        VECTOR edge2 = VGet(position.x + 15, position.y + 15, position.z + 40);
        DrawDamageBoxTransparent(edge1, edge2);
        isHit = checkHit(edge1, edge2, hitbox1, hitbox2, isHit);
    }
    if (lower)
    {
        VECTOR edge1 = VGet(position.x - 15, position.y - 15, position.z - 40);
        VECTOR edge2 = VGet(position.x + 15, position.y - 7, position.z + 40);
        DrawDamageBoxTransparent(edge1, edge2);
        isHit = checkHit(edge1, edge2, hitbox1, hitbox2, isHit);
    }
    if (right)
    {
        VECTOR edge1 = VGet(position.x + 7, position.y - 15, position.z - 40);
        VECTOR edge2 = VGet(position.x + 15, position.y + 15, position.z + 40);
        DrawDamageBoxTransparent(edge1, edge2);
        isHit = checkHit(edge1, edge2, hitbox1, hitbox2, isHit);
    }
    if (left)
    {
        VECTOR edge1 = VGet(position.x - 15, position.y - 15, position.z - 40);
        VECTOR edge2 = VGet(position.x - 7, position.y + 15, position.z + 40);
        DrawDamageBoxTransparent(edge1, edge2);
        isHit = checkHit(edge1, edge2, hitbox1, hitbox2, isHit);
    }
    if (firingTimer.MeasureTimer(1.2f) &&count < 2)
    {
        count++;
        firingTimer.RestartTimer();
    }
    return isHit;
}
void antiAir::DrawDamageBoxTransparent(VECTOR edge1, VECTOR edge2)
{
    SetWriteZBuffer3D(FALSE);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
    DrawCube3D(edge1, edge2, GetColor(120, 0, 0), GetColor(120, 0, 0), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    SetWriteZBuffer3D( TRUE);
    for (int i = 0; i < count; i++)
    {
        if (expls[i].DrawSingleExplosion())
        {
            expls[i].SetPosition(VGet(get_rand(edge1.x, edge2.x), get_rand(edge1.y, edge2.y), get_rand(edge1.z, edge2.z)));
        }
    }

}

bool explosion::DrawExplosion()
{
    DrawSphere3D(position, radius, 4, GetColor(255, 100, 0), GetColor(255, 100, 0), true);
    radius -= damping;
    if (radius <= 0)
    {
        return true;
    }
    return false;
}
void explosion::SetPosition(VECTOR edge1, VECTOR edge2)
{
    radius = maxRadius;
}
void wallmove::MovePosition()
{
    position.x += moveSpeed * timeScale;
    if (position.x > returnThleshold)
    {
        position.x = returnPosition;
    }
}
bool wallmove::DrawMoveWall(bool high,bool mid, bool low, VECTOR hitbox1, VECTOR hitbox2)
{
    isHit = false;
    if (high)
    {
        VECTOR edge1 = VGet(position.x - 15, position.y + 7, position.z - 10);
        VECTOR edge2 = VGet(position.x + 23, position.y + 15, position.z + 10);
        MV1SetPosition(cargoHandle, VGet(position.x,position.y + 11,position.z));
        MV1DrawModel(cargoHandle);
        //DrawDamageBox(edge1, edge2);
        isHit = checkHit(edge1, edge2, hitbox1, hitbox2, isHit);
        DrawHole(edge1, edge2);
    }
    if (mid)
    {
        VECTOR edge1 = VGet(position.x - 15, position.y - 4, position.z - 10);
        VECTOR edge2 = VGet(position.x + 23, position.y + 4, position.z + 10);
        MV1SetPosition(cargoHandle, position);
        MV1DrawModel(cargoHandle);
        //DrawDamageBox(edge1, edge2);
        isHit = checkHit(edge1, edge2, hitbox1, hitbox2, isHit);
        DrawHole(edge1, edge2);
    }
    if (low)
    {
        VECTOR edge1 = VGet(position.x - 15, position.y - 7, position.z - 10);
        VECTOR edge2 = VGet(position.x + 23, position.y - 15, position.z + 10);
        MV1SetPosition(cargoHandle, VGet(position.x, position.y -11, position.z));
        MV1DrawModel(cargoHandle);
        //DrawDamageBox(edge1, edge2);
        isHit = checkHit(edge1, edge2, hitbox1, hitbox2, isHit);
        DrawHole(edge1, edge2);
    }
    return isHit;
}
void wallmove::DrawHole(VECTOR edge1, VECTOR edge2)
{
    SetUseLighting(false);
    DrawCube3D(VGet(-15, edge1.y, edge1.z), VGet(-14.7f, edge2.y, edge2.z), GetColor(0, 0, 0), GetColor(0, 0, 0), true);
    DrawCube3D(VGet(15, edge1.y, edge1.z), VGet(14.7f, edge2.y, edge2.z), GetColor(0, 0, 0), GetColor(0, 0, 0), true);
    SetUseLighting(true);
    SetWriteZBuffer3D(FALSE);
    DrawExtendGraph3D(0, edge1.y, edge1.z, 0.05, 0.05, guideHandle, TRUE);
    SetWriteZBuffer3D(TRUE);
}
void wallmove::SetUp()
{
    cargoHandle = MV1DuplicateModel(cargoModelOrigin);
    MV1SetRotationXYZ(cargoHandle, VGet(0, PI/2, 0));
    for (int i = 0; i < MV1GetMaterialNum(cargoHandle); i++)
    {
        MV1SetMaterialDifColor(cargoHandle, i, GetColorF(1.0f, 0.7f, 0.7f, 1.0f));
        MV1SetMaterialAmbColor(cargoHandle, i, GetColorF(0.2f, 0.2f, 0.2f, 1.0f));
        MV1SetMaterialSpcColor(cargoHandle, i, GetColorF(0.4f, 0.4f, 0.4f, 1));
        MV1SetMaterialEmiColor(cargoHandle, i, GetColorF(0.8f, 0.8f, 0.8f, 0.2f));
        MV1SetMaterialSpcPower(cargoHandle, i, 6);
    }
}