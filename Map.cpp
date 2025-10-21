#include "Map.h"
void mapBase::DrawbaseOutline()
{
    MATERIALPARAM Material;

    Material.Diffuse = GetColorF(0.2f, 0.2f, 0.2f, 0.2f);
    Material.Ambient = GetColorF(0.4f, 0.4f, 0.4f, 1.0f);
    Material.Specular = GetColorF(0.2f, 0.2f, 0.2f, 0.2f);
    Material.Emissive = GetColorF(0.1f, 0.1f, 0.1f, 0.0f);
    Material.Power = 1.0f;
    SetMaterialParam(Material);
    VECTOR edgePosition1 = VGet(position.x - 15, position.y - 15, position.z - 40);
    VECTOR edgePosition2 = VGet(position.x + 15, position.y + 15, position.z + 40);
    DrawCube3D(edgePosition1, VGet(edgePosition1.x - 1, edgePosition2.y, edgePosition2.z), GetColor(100, 100, 100), GetColor(0, 0, 0), TRUE);
    DrawCube3D(edgePosition1, VGet(edgePosition2.x, edgePosition1.y-1, edgePosition2.z), GetColor(100, 100, 100), GetColor(0, 0, 0), TRUE);
    DrawCube3D(edgePosition2, VGet(edgePosition2.x + 1, edgePosition1.y, edgePosition1.z), GetColor(100, 100, 100), GetColor(0, 0, 0), TRUE);

}
bool mapBase::DamageBox(bool upper, bool lower, bool right, bool left, bool center, VECTOR hitbox1, VECTOR hitbox2)
{
    bool isHit = false;
    if (upper)
    {
        VECTOR edge1 = VGet(position.x - 15, position.y + 7, position.z - 40);
        VECTOR edge2 = VGet(position.x + 15, position.y + 15, position.z + 40);
        DrawDamageBox(edge1, edge2);
        isHit = checkHit(edge1,edge2,hitbox1,hitbox2,isHit);
    }
    if (lower)
    {
        VECTOR edge1 = VGet(position.x - 15, position.y -15, position.z - 40);
        VECTOR edge2 = VGet(position.x + 15, position.y -7, position.z + 40);
        DrawDamageBox(edge1, edge2);
        isHit = checkHit(edge1, edge2, hitbox1, hitbox2, isHit);
    }
    if (right)
    {
        VECTOR edge1 = VGet(position.x + 7, position.y - 15, position.z - 40);
        VECTOR edge2 = VGet(position.x + 15, position.y + 15, position.z + 40);
        DrawDamageBox(edge1, edge2);
        isHit = checkHit(edge1, edge2, hitbox1, hitbox2, isHit);
    }
    if (left)
    {
        VECTOR edge1 = VGet(position.x - 15, position.y - 15, position.z - 40);
        VECTOR edge2 = VGet(position.x - 7, position.y + 15, position.z + 40);
        DrawDamageBox(edge1, edge2);
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
    MATERIALPARAM Material;

    Material.Diffuse = GetColorF(0, 0, 0, 0.2f);
    Material.Ambient = GetColorF(0.2f, 0.2f, 0.2f, 0.2f);
    Material.Specular = GetColorF(0.2f, 0.2f, 0.2f, 0.2f);
    Material.Emissive = GetColorF(0.1f, 0.1f, 0.1f, 0.0f);
    Material.Power = 3.0f;
    SetMaterialParam(Material);
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

bool antiAir::DamageZone(bool upper, bool lower, bool right, bool left, VECTOR hitbox1, VECTOR hitbox2)
{
    bool isHit = false;
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
    MATERIALPARAM Material;

    Material.Diffuse = GetColorF(0, 0, 0, 0.2f);
    Material.Ambient = GetColorF(0.2f, 0.2f, 0.2f, 0.2f);
    Material.Specular = GetColorF(0.2f, 0.2f, 0.2f, 0.2f);
    Material.Emissive = GetColorF(0.2f, 0.0f, 0.0f, 0.0f);
    Material.Power = 3.0f;
    SetMaterialParam(Material);
    SetWriteZBuffer3D(FALSE);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 90);
    DrawCube3D(edge1, edge2, GetColor(120, 0, 0), GetColor(120, 0, 0), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    SetWriteZBuffer3D( TRUE);
    for (int i = 0; i < count; i++)
    {
        if (expls[i].DrawExplosion())
        {
            expls[i].SetPosition(edge1,edge2);
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
    position = VGet(get_rand(edge1.x, edge2.x), get_rand(edge1.y, edge2.y), get_rand(edge1.z, edge2.z));
    radius = maxRadius;
}