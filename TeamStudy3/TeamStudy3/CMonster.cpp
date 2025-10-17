#include "pch.h"
#include "CMonster.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
    Release();
}

void CMonster::Initialize()
{
    m_tInfo.vPos = { 100.f, 100.f, 0.f };

    m_fSpeed = 10.f;
}

int CMonster::Update()
{
    m_tInfo.vDir = m_pPlayer->Get_Info()->vPos - m_tInfo.vPos;

    float fLength = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y);

    // 벡터의 정규화
    m_tInfo.vDir.x /= fLength;
    m_tInfo.vDir.y /= fLength;
    m_tInfo.vDir.z = 0.f;

    m_tInfo.vPos += m_tInfo.vDir;

    return 0;
}

void CMonster::Render(HDC hDC)
{
    Ellipse(hDC,
        int(m_tInfo.vPos.x - 50.f),
        int(m_tInfo.vPos.y - 50.f),
        int(m_tInfo.vPos.x + 50.f),
        int(m_tInfo.vPos.y + 50.f));
}

void CMonster::Release()
{
}
