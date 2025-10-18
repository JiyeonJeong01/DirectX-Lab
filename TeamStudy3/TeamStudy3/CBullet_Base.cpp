#include "pch.h"
#include "CBullet_Base.h"

CBullet_Base::CBullet_Base(): m_Damage(5.f)
{
}

CBullet_Base::~CBullet_Base()
{
    Release();
}

void CBullet_Base::Initialize()
{
    m_tInfo.vDir     = Vec3(0.f, -1.f, 0.f);
    m_tInfo.vSize  = Vec3(10.f, 10.f, 0.f);

    m_fSpeed = 5.f;

}

int CBullet_Base::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

    return OBJ_NOEVENT;
}

void CBullet_Base::Late_Update()
{

}

void CBullet_Base::Render(HDC _hDC)
{
    Ellipse(_hDC,
        (int)m_tInfo.vPos.x - m_tInfo.vSize.x,
        (int)m_tInfo.vPos.y - m_tInfo.vSize.y,
        (int)m_tInfo.vPos.x + m_tInfo.vSize.x,
        (int)m_tInfo.vPos.y + m_tInfo.vSize.y);
}

void CBullet_Base::Release()
{

}
