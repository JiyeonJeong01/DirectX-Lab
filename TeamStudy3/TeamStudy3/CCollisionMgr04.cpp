#include "pch.h"
#include "CCollisionMgr04.h"

bool CCollisionMgr04::CollisionLineToLine(const D3DXVECTOR3& firstLineA, const D3DXVECTOR3& firstLineB, const D3DXVECTOR3& secondLineA, const D3DXVECTOR3& secondLineB)
{
    float ab1 = Cross(firstLineA, firstLineB, secondLineA);
    float ab2 = Cross(firstLineA, firstLineB, secondLineB);
    float cd1 = Cross(secondLineA, secondLineB, firstLineA);
    float cd2 = Cross(secondLineA, secondLineB, firstLineB);
    return (ab1 * ab2 < 0 && cd1 * cd2 < 0);
}
