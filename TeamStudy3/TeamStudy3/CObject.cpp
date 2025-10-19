#include "pch.h"
#include "CObject.h"

CObject::CObject() : m_fSpeed(0.f), m_fAngle(0), m_iHp(0), m_iAttack(0), m_bDead(0), m_pTarget(nullptr),
                     m_Owner(nullptr), m_TeamID(0)
{
    ZeroMemory(&m_tInfo, sizeof(INFO));
    D3DXMatrixIdentity(&m_tInfo.matWorld);
}

CObject::~CObject()
{

}

void CObject::OnComponentBeginOverlap(CObject* _Dst)
{
    // 자식에서 처리 ex) TakeDamage, UseItem
}

void CObject::TakeDamage(int _iAttack)
{
    int currentHP = Get_Hp(); 

    Set_Hp(currentHP - _iAttack);

    if (Get_Hp() <= 0)
        Set_Dead();
}

bool CObject::CheckToBounds()
{
    const float minX = 0.f + m_tInfo.vSize.x;
    const float maxX = WINCX - m_tInfo.vSize.x;
    const float minY = 0.f + m_tInfo.vSize.y;
    const float maxY = WINCY - m_tInfo.vSize.y;

    bool bCheck = false;
    bCheck |= m_tInfo.vPos.x < minX;
    bCheck |= m_tInfo.vPos.y < minY;
    bCheck |= m_tInfo.vPos.x > maxX;
    bCheck |= m_tInfo.vPos.y > maxY;

    return bCheck;
}

void CObject::Move_Frame()
{
    if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount64())
    {
        ++m_tFrame.iStart;

        if (m_tFrame.iStart > m_tFrame.iEnd)
            m_tFrame.iStart = 0;

        m_tFrame.dwTime = GetTickCount64();
    }
}
