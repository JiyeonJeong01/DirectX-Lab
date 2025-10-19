#include "pch.h"
#include "CItem.h"

CItem::CItem()
{

}

CItem::~CItem()
{
    Release();
}

void CItem::Initialize()
{
    m_tInfo.vSize = { 30.f, 30.f, 0.f };
    m_tInfo.vPos  = { 0.f, 0.f, 0.f };
    m_fSpeed = 50.f;

    m_vPoint[0] = Vec3(-m_tInfo.vSize.x, -m_tInfo.vSize.y, 0.f);
    m_vPoint[1] = Vec3(+m_tInfo.vSize.x, -m_tInfo.vSize.y, 0.f);
    m_vPoint[2] = Vec3(+m_tInfo.vSize.x, +m_tInfo.vSize.y, 0.f);
    m_vPoint[3] = Vec3(-m_tInfo.vSize.x, +m_tInfo.vSize.y, 0.f);
}

int CItem::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    m_tInfo.vPos.y += m_fSpeed * DELTA;

    D3DXMATRIX S, R, T;
    D3DXMatrixScaling(&S, 1.f, 1.f, 1.f);
    D3DXMatrixRotationZ(&R, 20.f);
    D3DXMatrixTranslation(&T, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

    m_tInfo.matWorld = S * R * T;

    return OBJ_NOEVENT;
}

void CItem::Late_Update()
{

}

void CItem::Render(HDC _hDC)
{
    POINT points[5];

    for (int i = 0; i < 4; ++i)
    {
        Vec3 pos = m_vPoint[i];

        D3DXVec3TransformCoord(&pos, &pos, &m_tInfo.matWorld);

        points[i] = { (LONG)pos.x, (LONG)pos.y };
    }

    points[4] = points[0];

    Polyline(_hDC, points, 5);
}

void CItem::Release()
{

}

void CItem::OnComponentBeginOverlap(CObject* _Dst)
{
    CObject::OnComponentBeginOverlap(_Dst);

}

void CItem::Use_Item(CObject* _HitObject)
{

}

