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

