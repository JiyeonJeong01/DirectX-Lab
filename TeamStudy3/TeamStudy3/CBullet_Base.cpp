#include "pch.h"
#include "CBullet_Base.h"

#include "CBmpManager.h"

CBullet_Base::CBullet_Base()
{
}

CBullet_Base::~CBullet_Base()
{
    Release();
}

void CBullet_Base::Initialize()
{
    m_tInfo.vDir     = Vec3(0.f, -1.f, 0.f);
    m_tInfo.vSize  = Vec3(30.f, 30.f, 0.f);

    m_iAttack = 5.f;
    m_fSpeed = 5.f;

    CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Object/HeavyMachineGunProjectile_Up.bmp", L"HeavyBullet");

    m_FrameKey = L"HeavyBullet";

    // 첫프레임 씹힘 방지
    D3DXMATRIX S, R, T;
    D3DXMatrixScaling(&S, 1.f, 1.f, 1.f);
    D3DXMatrixRotationZ(&R, 0.f); 
    D3DXMatrixTranslation(&T, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
    m_tInfo.matWorld = S * R * T;
}

int CBullet_Base::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

    D3DXMATRIX S, R, T;
    D3DXMatrixScaling(&S, 1.f, 1.f, 1.f);
    D3DXMatrixRotationZ(&R, 20.f);
    D3DXMatrixTranslation(&T, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
    m_tInfo.matWorld = S * R * T;

    return OBJ_NOEVENT;
}

void CBullet_Base::Late_Update()
{
    if (CheckToBounds())
        m_bDead = true;
}

void CBullet_Base::Render(HDC _hDC)
{
    Vec3 center = { 0.f, 0.f, 0.f };
    D3DXVec3TransformCoord(&center, &center, &m_tInfo.matWorld);

    const int destW = (int)(m_tInfo.vSize.x * 1.65f);
    const int destH = (int)(m_tInfo.vSize.y * 1.65f);

    const int destX = (int)(center.x - destW / 2);
    const int destY = (int)(center.y - destH / 2);

    HDC hMemDC = CBmpManager::Get_Instance()->Find_Img(m_FrameKey);
    if (!hMemDC) return;

    HBITMAP hbmp = (HBITMAP)GetCurrentObject(hMemDC, OBJ_BITMAP);
    BITMAP bm{}; GetObject(hbmp, sizeof(bm), &bm);

    const int srcX = 0;
    const int srcY = 0;
    const int srcW = bm.bmWidth;
    const int srcH = bm.bmHeight;

    SetStretchBltMode(_hDC, HALFTONE);

    GdiTransparentBlt(_hDC,
        destX, destY, destW, destH,   
        hMemDC,
        srcX, srcY, srcW, srcH,      
        RGB(255, 255, 255));
}

void CBullet_Base::Release()
{

}

void CBullet_Base::OnComponentBeginOverlap(CObject* _Dst)
{
    CObject::OnComponentBeginOverlap(_Dst);

    Set_Dead();
}


bool CBullet_Base::CheckToBounds()
{
   const float minX = 0.f + m_tInfo.vSize.x;
   const float maxX = WINCX - m_tInfo.vSize.x;
   const float minY = 0.f + m_tInfo.vSize.y;
   const float maxY = WINCY - m_tInfo.vSize.y;

   bool bCheck = false;
   bCheck |= m_tInfo.vPos.x < minX;
   bCheck |= m_tInfo.vPos.y < minY;
   bCheck |= m_tInfo.vPos.x > maxX;
   bCheck |= m_tInfo.vPos.y > maxX;

   return bCheck;
}
