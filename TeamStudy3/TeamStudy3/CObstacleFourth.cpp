#include "pch.h"
#include "CObstacleFourth.h"

CObstacleFourth::CObstacleFourth()
{
}

CObstacleFourth::~CObstacleFourth()
{
    Release();
}

void CObstacleFourth::Initialize()
{
    m_tInfo.vPos = { 400.f, 300.f, 0.f };

    m_vPoint[0] = { m_tInfo.vPos.x - 15.f, m_tInfo.vPos.y - 100.f, 0.f };
    m_vPoint[1] = { m_tInfo.vPos.x + 15.f, m_tInfo.vPos.y - 100.f, 0.f };
    m_vPoint[2] = { m_tInfo.vPos.x + 15.f, m_tInfo.vPos.y + 100.f, 0.f };
    m_vPoint[3] = { m_tInfo.vPos.x - 15.f, m_tInfo.vPos.y + 100.f, 0.f };
    for (int i = 0; i < 4; ++i)
        m_vOriginPoint[i] = m_vPoint[i];
}

int CObstacleFourth::Update()
{
    m_fAngle += 3.f;

    D3DXMATRIX matRotZ, matTrans;
    D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
    D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

    m_tInfo.matWorld = matRotZ * matTrans;

    for (int i = 0; i < 4; ++i)
    {
        m_vPoint[i] = m_vOriginPoint[i];
        m_vPoint[i] -= {400.f, 300.f, 0.f};
        D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
    }

    return OBJ_NOEVENT;
}

void CObstacleFourth::Render(HDC hDC)
{
    HPEN hRedPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));

    HPEN hOldPen = (HPEN)SelectObject(hDC, hRedPen);

    MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);
    for (int i = 0; i < 4; ++i)
    {
        LineTo(hDC, (int)m_vPoint[i].x, (int)m_vPoint[i].y);
    }
    LineTo(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y);

    SelectObject(hDC, hOldPen);
    DeleteObject(hRedPen);
}

void CObstacleFourth::Release()
{
}
