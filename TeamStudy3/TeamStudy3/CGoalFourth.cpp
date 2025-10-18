#include "pch.h"
#include "CGoalFourth.h"

CGoalFourth::CGoalFourth() : isGoal(false)
{
}

CGoalFourth::~CGoalFourth()
{
    Release();
}

void CGoalFourth::Initialize()
{
    m_tInfo.vPos = { 625.f, 175.f, 0.f };
    m_fSpeed = 5.f;

    m_vPoint[0] = { m_tInfo.vPos.x - 40.f, m_tInfo.vPos.y - 40.f, 0.f };
    m_vPoint[1] = { m_tInfo.vPos.x + 40.f, m_tInfo.vPos.y - 40.f, 0.f };
    m_vPoint[2] = { m_tInfo.vPos.x + 40.f, m_tInfo.vPos.y + 40.f, 0.f };
    m_vPoint[3] = { m_tInfo.vPos.x - 40.f, m_tInfo.vPos.y + 40.f, 0.f };
    for (int i = 0; i < 4; ++i)
        m_vOriginPoint[i] = m_vPoint[i];
}

int CGoalFourth::Update()
{
    return 0;
}

void CGoalFourth::Render(HDC hDC)
{
    MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);
    for (int i = 0; i < 4; ++i)
    {
        LineTo(hDC, (int)m_vPoint[i].x, (int)m_vPoint[i].y);
    }
    LineTo(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y);
}

void CGoalFourth::Release()
{
}
