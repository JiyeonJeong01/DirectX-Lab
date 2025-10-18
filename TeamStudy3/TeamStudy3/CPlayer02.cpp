#include "pch.h"
#include "CPlayer02.h"

#include "CAbstractFactory.h"
#include "CBullet_Base.h"
#include "CComponent.h"
#include "CKeyManager.h"
#include "CObjectManager.h"

CPlayer02::CPlayer02()
{
}

CPlayer02::~CPlayer02()
{
    Release();
}

void CPlayer02::Initialize()
{
    m_tInfo.vPos = { 400.f, 300.f, 0.f };
    m_tInfo.vLook = { 0.f, - 1.f, 0.f };
    m_tInfo.vSize = { 25.f, 25.f, 0.f };

    m_fSpeed = 5.f;

    m_vPoint[0] = { m_tInfo.vPos.x - m_tInfo.vSize.x, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.f };
    m_vPoint[1] = { m_tInfo.vPos.x + m_tInfo.vSize.x, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.f };
    m_vPoint[2] = { m_tInfo.vPos.x + m_tInfo.vSize.x, m_tInfo.vPos.y + m_tInfo.vSize.y, 0.f };
    m_vPoint[3] = { m_tInfo.vPos.x - m_tInfo.vSize.x, m_tInfo.vPos.y + m_tInfo.vSize.y, 0.f };

    for (int i = 0; i < 4; i++)
    {
        m_vOriginPoint[i] = m_vPoint[i];
    }

    m_vOriginPosin = { m_tInfo.vPos.x, m_tInfo.vPos.y - m_PosinLength, 0.f };
    m_vPosin = m_vOriginPosin;
}

int CPlayer02::Update()
{
  


    return 0;
}

void CPlayer02::Late_Update()
{



}

void CPlayer02::Render(HDC hDC)
{
}

void CPlayer02::Release()
{
}

void CPlayer02::AddComponent(CComponent* _Component)
{
}
