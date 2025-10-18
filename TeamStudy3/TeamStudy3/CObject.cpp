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

void CObject::TakeDamage(int _iAttack)
{
    int currentHP = Get_Hp(); 

    Set_Hp(currentHP - _iAttack);

    if (Get_Hp() <= 0)
        Set_Dead();
}
