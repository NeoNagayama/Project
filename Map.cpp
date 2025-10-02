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
void mapBase::DrawDamageBox(bool upper, bool lower, bool right, bool left, bool center)
{
    if (upper)
    {
        VECTOR edge1 = VGet(position.x - 15, position.y + 4, position.z - 40);
        VECTOR edge2 = VGet(position.x + 15, position.y + 15, position.z + 40);
        DamageBox(edge1, edge2);
    }
    if (lower)
    {
        VECTOR edge1 = VGet(position.x - 15, position.y -15, position.z - 40);
        VECTOR edge2 = VGet(position.x + 15, position.y -4, position.z + 40);
        DamageBox(edge1, edge2);
    }
    if (right)
    {
        VECTOR edge1 = VGet(position.x + 4, position.y - 15, position.z - 40);
        VECTOR edge2 = VGet(position.x + 14, position.y + 15, position.z + 40);
        DamageBox(edge1, edge2);
    }
    if (left)
    {
        VECTOR edge1 = VGet(position.x - 15, position.y - 15, position.z - 40);
        VECTOR edge2 = VGet(position.x -4, position.y + 15, position.z + 40);
        DamageBox(edge1, edge2);
    }
    if (center)
    {
        VECTOR edge1 = VGet( - 4, position.y - 15, position.z - 40);
        VECTOR edge2 = VGet( 4, position.y + 15, position.z + 40);
        DamageBox(edge1, edge2); 
    }
}
void mapBase::DamageBox(VECTOR edge1, VECTOR edge2)
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