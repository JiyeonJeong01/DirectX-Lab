#include "pch.h"
#include "COrb03.h"

#include "CAbstractFactory.h"
#include "CBmpManager.h"
#include "CBullet_Base.h"
#include "CComponent.h"
#include "CKeyManager.h"
#include "CObjectManager.h"
#include "CHelper.h"
#include "CWeaponComponent.h"

COrb03::COrb03()
{

}

COrb03::~COrb03()
{
    Release();
}

void COrb03::Initialize()
{
    m_tInfo.vLook = { 0.f, -1.f, 0.f };
    m_tInfo.vSize = { 42.6f, 64.f, 0.f };

    m_fSpeed = 250.f;

    m_iAttack = 2.f;

    // 스프라이트
    {
        CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Object/Player03_Orb.bmp", L"Item_Orb");

        m_FrameKey = L"Item_Orb";
        m_tFrame.iStart = 0;
        m_tFrame.iEnd = 3;
        m_tFrame.iMotion = 0;
        m_tFrame.dwSpeed = 200;
        m_tFrame.dwTime = GetTickCount64();
    }

    if (Get_Target())
        m_OffsetBase = m_tInfo.vPos - Get_Target()->Get_Pos(); 
}

int COrb03::Update()
{
	__super::Move_Frame();

    if (Get_Target())
    {
        m_AngleRad += m_AngularRad * DELTA * 50.f; 
        Vec3 offset = RotateZ_Deg(m_OffsetBase, m_AngleRad);
        m_tInfo.vPos = Vec3(Get_Target()->Get_Pos().x + offset.x, Get_Target()->Get_Pos().y + 5.f + offset.y, 0.f);
    }

    m_DamageAcc += DELTA;
    if (m_Overlapping && m_LastTarget && m_DamageAcc >= m_DamageInterval)
    {
        m_DamageAcc = 0.f;

        TakeDamage(m_LastTarget, m_iAttack);
    }

    D3DXMATRIX	 matScale, matRotZ, matTrans;

    D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
    D3DXMatrixRotationZ(&matRotZ, m_fAngle);
    D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

    m_tInfo.matWorld = matScale * matRotZ * matTrans;

    return OBJ_NOEVENT;
}

void COrb03::Late_Update()
{
    //CObject::Late_Update();
}

void COrb03::Render(HDC hDC)
{
	Vec3 center = { 0.f, 0.f, 0.f };
	D3DXVec3TransformCoord(&center, &center, &m_tInfo.matWorld);

	const int destW = (int)(m_tInfo.vSize.x * 1.f);
	const int destH = (int)(m_tInfo.vSize.y * 1.f);

    const int destX = (int)(center.x - destW / 2);
    const int destY = (int)(center.y - destH / 2);

	HDC hMemDC = CBmpManager::Get_Instance()->Find_Img(m_FrameKey);
	if (!hMemDC) return;

	HBITMAP hbmp = (HBITMAP)GetCurrentObject(hMemDC, OBJ_BITMAP);
	BITMAP bm{}; GetObject(hbmp, sizeof(bm), &bm);

	const int cols = m_tFrame.iEnd + 1;
	const int rows = 1;

	const int frameW = bm.bmWidth / cols;
	const int frameH = bm.bmHeight / rows;

	const int srcX = m_tFrame.iStart * frameW;
	const int srcY = m_tFrame.iMotion * frameH;

	SetStretchBltMode(hDC, HALFTONE);
	GdiTransparentBlt(hDC,
		destX, destY, destW, destH,
		hMemDC,
		srcX, srcY, frameW, frameH,
		RGB(255, 255, 255));

	//::DrawRect(hDC, m_vPoint, RGB(0, 255, 0));
}

void COrb03::Release()
{
    //CObject::Release();
}

void COrb03::OnComponentBeginOverlap(CObject* _Dst)
{
    CObject::OnComponentBeginOverlap(_Dst);

    if (!_Dst) return;

    if (!_Dst) return;
    if (_Dst == Get_Target()) return;
    m_Overlapping = true;
    m_LastTarget = _Dst;

    //TakeDamage(_Dst, m_iAttack);
}
