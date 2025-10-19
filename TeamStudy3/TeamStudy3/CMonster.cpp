#include "pch.h"
#include "CMonster.h"
#include "CObjectManager.h"

CMonster::CMonster()
{
    m_TeamID = 1;
}

CMonster::~CMonster()
{
    Release();
}

void CMonster::Initialize()
{
    m_tInfo.vPos = { 400.f, 100.f, 0.f };
    m_tInfo.vDir = { 0.f, 0.f, 0.f };

    m_pPlayer = CObjectManager::Get_Instance()->Get_Player()->front();

    m_iHp = 100.f;
    m_fSpeed = 10.f;
}

int CMonster::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    if (m_pPlayer)
    {
        m_tInfo.vDir = m_pPlayer->Get_Info()->vPos - m_tInfo.vPos;
    }

    float fLength = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y);

    // 벡터의 정규화
    m_tInfo.vDir.x /= fLength;
    m_tInfo.vDir.y /= fLength;
    m_tInfo.vDir.z = 0.f;

    //m_tInfo.vPos += m_tInfo.vDir;

    return OBJ_NOEVENT;
}

void CMonster::Late_Update()
{
    cout << m_iHp << endl;
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
