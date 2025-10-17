#include "pch.h"
#include "CObject.h"

CObject::CObject() : m_fSpeed(0.f), m_bDead(0)
{
    ZeroMemory(&m_tInfo, sizeof(INFO));
    D3DXMatrixIdentity(&m_tInfo.matWorld);

}

CObject::~CObject()
{
}
