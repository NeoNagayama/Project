#include "Map.h"
void mapBase::DrawbaseOutline()
{
    VECTOR edgePosition1 = VGet(position.x - 15, position.y - 15, position.z - 40);
    VECTOR edgePosition2 = VGet(position.x + 15, position.y + 15, position.z + 40);
    DrawTriangle3D(edgePosition1, VGet(edgePosition1.x, edgePosition1.y, edgePosition2.z), VGet(edgePosition1.x, edgePosition2.y, edgePosition2.z), GetColor(120, 120, 120), true);
    DrawTriangle3D(edgePosition1, VGet(edgePosition1.x, edgePosition2.y, edgePosition2.z), VGet(edgePosition1.x, edgePosition2.y, edgePosition1.z), GetColor(120, 120, 120), true);
    DrawTriangle3D(edgePosition1, VGet(edgePosition2.x, edgePosition1.y, edgePosition1.z), VGet(edgePosition2.x, edgePosition1.y, edgePosition2.z), GetColor(90, 90, 90), true);
    DrawTriangle3D(edgePosition1, VGet(edgePosition1.x, edgePosition1.y, edgePosition2.z), VGet(edgePosition2.x, edgePosition1.y, edgePosition2.z), GetColor(90, 90, 90), true);
    DrawTriangle3D(edgePosition2, VGet(edgePosition2.x, edgePosition1.y, edgePosition2.z), VGet(edgePosition2.x, edgePosition1.y, edgePosition1.z), GetColor(120, 120, 120), true);
    DrawTriangle3D(edgePosition2, VGet(edgePosition2.x, edgePosition2.y, edgePosition1.z), VGet(edgePosition2.x, edgePosition1.y, edgePosition1.z), GetColor(120, 120, 120), true);

}
bool mapBase::DamageBox(bool upper, bool lower, bool right, bool left, bool center, VECTOR hitbox1, VECTOR hitbox2)
{
    bool isHit = false;
    if (upper)
    {
        VECTOR edge1 = VGet(position.x - 15, position.y + 7, position.z - 40);
        VECTOR edge2 = VGet(position.x + 15, position.y + 15, position.z + 40);
        DrawDamageBox(edge1, edge2);
        isHit = checkHit(edge1,edge2,hitbox1,hitbox2);
    }
    if (lower)
    {
        VECTOR edge1 = VGet(position.x - 15, position.y -15, position.z - 40);
        VECTOR edge2 = VGet(position.x + 15, position.y -7, position.z + 40);
        DrawDamageBox(edge1, edge2);
        isHit = checkHit(edge1, edge2, hitbox1, hitbox2);
    }
    if (right)
    {
        VECTOR edge1 = VGet(position.x + 7, position.y - 15, position.z - 40);
        VECTOR edge2 = VGet(position.x + 15, position.y + 15, position.z + 40);
        DrawDamageBox(edge1, edge2);
        isHit = checkHit(edge1, edge2, hitbox1, hitbox2);
    }
    if (left)
    {
        VECTOR edge1 = VGet(position.x - 15, position.y - 15, position.z - 40);
        VECTOR edge2 = VGet(position.x - 7, position.y + 15, position.z + 40);
        DrawDamageBox(edge1, edge2);
        isHit = checkHit(edge1, edge2, hitbox1, hitbox2);
    }
    if (center)
    {
        VECTOR edge1 = VGet( -7, position.y - 15, position.z - 40);
        VECTOR edge2 = VGet(7, position.y + 15, position.z + 40);
        DrawDamageBox(edge1, edge2);
        isHit = checkHit(edge1, edge2,hitbox1, hitbox2);
    }
    return isHit;
}
void mapBase::DrawDamageBox(VECTOR edge1, VECTOR edge2)
{
    DrawTriangle3D(edge1, VGet(edge1.x, edge2.y, edge1.z), VGet(edge2.x, edge2.y, edge1.z), GetColor(20, 20, 20), true);
    DrawTriangle3D(edge1, VGet(edge2.x, edge1.y, edge1.z), VGet(edge2.x, edge2.y, edge1.z), GetColor(20, 20, 20), true);
    DrawTriangle3D(edge1, VGet(edge2.x, edge1.y, edge1.z), VGet(edge2.x, edge1.y, edge2.z), GetColor(120, 120, 120), true);
    DrawTriangle3D(edge1, VGet(edge1.x, edge1.y, edge2.z), VGet(edge2.x, edge1.y, edge2.z), GetColor(120, 120, 120), true);
    DrawTriangle3D(edge2, VGet(edge1.x, edge2.y, edge2.z), VGet(edge1.x, edge1.y, edge2.z), GetColor(20, 20, 20), true);
    DrawTriangle3D(edge2, VGet(edge2.x, edge1.y, edge2.z), VGet(edge1.x, edge1.y, edge2.z), GetColor(20, 20, 20), true);
    DrawTriangle3D(edge2, VGet(edge2.x, edge2.y, edge1.z), VGet(edge1.x, edge2.y, edge1.z), GetColor(120, 120, 120), true);
    DrawTriangle3D(edge2, VGet(edge1.x, edge2.y, edge2.z), VGet(edge1.x, edge2.y, edge1.z), GetColor(120, 120, 120), true);
    DrawTriangle3D(edge1, VGet(edge1.x, edge2.y, edge1.z), VGet(edge1.x, edge2.y, edge2.z), GetColor(120, 120, 120), true);
    DrawTriangle3D(edge1, VGet(edge1.x, edge1.y, edge2.z), VGet(edge1.x, edge2.y, edge2.z), GetColor(120, 120, 120), true);
    DrawTriangle3D(edge2, VGet(edge2.x, edge2.y, edge1.z), VGet(edge2.x, edge1.y, edge1.z), GetColor(120, 120, 120), true);
    DrawTriangle3D(edge2, VGet(edge2.x, edge1.y, edge2.z), VGet(edge2.x, edge1.y, edge1.z), GetColor(120, 120, 120), true);
}
bool mapBase::checkHit(VECTOR edge1, VECTOR edge2, VECTOR playerEdge1, VECTOR playerEdge2)
{
    if(((playerEdge1.x >= edge1.x && playerEdge1.x <= edge2.x) ||(playerEdge2 .x >= edge1.x && playerEdge2.x <= edge2.x))
        &&((playerEdge1.y >= edge1.y && playerEdge1.y <= edge2.y) || (playerEdge2.y >= edge1.y && playerEdge2.y <= edge2.y))
            && ((playerEdge1.z >= edge1.z && playerEdge1.z <= edge2.z) || (playerEdge2.z >= edge1.z && playerEdge2.z <= edge2.z)))
    {
        return true;
    }
    else
    {
        return false;
    }
}