#include "pch.h"
#include "CObjectFourth.h"

CObjectFourth::CObjectFourth() : m_fSpeed(0.f), m_fAngle(0.f)
{
    ZeroMemory(&m_tInfo, sizeof(INFO));
    D3DXMatrixIdentity(&m_tInfo.matWorld);
}

CObjectFourth::~CObjectFourth()
{
}

void CObjectFourth::SetAllPoint(D3DXVECTOR3 vPosInput, float fSize)
{
    m_tInfo.vPos = vPosInput;
    m_vPoint[0] = { m_tInfo.vPos.x - fSize, m_tInfo.vPos.y - fSize, 0.f };
    m_vPoint[1] = { m_tInfo.vPos.x + fSize, m_tInfo.vPos.y - fSize, 0.f };
    m_vPoint[2] = { m_tInfo.vPos.x + fSize, m_tInfo.vPos.y + fSize, 0.f };
    m_vPoint[3] = { m_tInfo.vPos.x - fSize, m_tInfo.vPos.y + fSize, 0.f };
    for (int i = 0; i < 4; ++i)
        m_vOriginPoint[i] = m_vPoint[i];
}
