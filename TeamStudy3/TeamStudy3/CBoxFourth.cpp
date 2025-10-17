#include "pch.h"
#include "CBoxFourth.h"

CBoxFourth::CBoxFourth()
{
}

CBoxFourth::~CBoxFourth()
{
    Release();
}

void CBoxFourth::Initialize()
{
    m_tInfo.vPos = { 100.f, 100.f, 0.f };
    m_fSpeed = 5.f;

    m_vPoint[0] = { m_tInfo.vPos.x - 50.f, m_tInfo.vPos.y - 50.f, 0.f };
    m_vPoint[1] = { m_tInfo.vPos.x + 50.f, m_tInfo.vPos.y - 50.f, 0.f };
    m_vPoint[2] = { m_tInfo.vPos.x + 50.f, m_tInfo.vPos.y + 50.f, 0.f };
    m_vPoint[3] = { m_tInfo.vPos.x - 50.f, m_tInfo.vPos.y + 50.f, 0.f };
    for (int i = 0; i < 4; ++i)
        m_vOriginPoint[i] = m_vPoint[i];
}

int CBoxFourth::Update()
{
    return 0;
}

void CBoxFourth::Render(HDC hDC)
{
    MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);
    for (int i = 0; i < 4; ++i)
    {
        LineTo(hDC, (int)m_vPoint[i].x, (int)m_vPoint[i].y);
    }
    LineTo(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y);
}

void CBoxFourth::Release()
{
}
