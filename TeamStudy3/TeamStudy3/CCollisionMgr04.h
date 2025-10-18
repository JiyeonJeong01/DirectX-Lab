#pragma once

#include "CObjectFourth.h"

class CCollisionMgr04
{
private:
    static float Cross(const D3DXVECTOR3& a, const D3DXVECTOR3& b, const D3DXVECTOR3& c)
    {
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    }
public:
    static bool CollisionLineToLine(const D3DXVECTOR3& firstLineA, const D3DXVECTOR3& firstLineB, const D3DXVECTOR3& secondLineA, const D3DXVECTOR3& secondLineB);
};
