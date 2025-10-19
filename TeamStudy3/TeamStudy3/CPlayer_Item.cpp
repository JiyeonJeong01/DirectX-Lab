#include "pch.h"
#include "CPlayer_Item.h"

#include "CAbstractFactory.h"
#include "CBmpManager.h"
#include "CBullet_Base.h"
#include "CComponent.h"
#include "CKeyManager.h"
#include "CObjectManager.h"
#include "CHelper.h"
#include "CWeaponComponent.h"

CPlayer_Item::CPlayer_Item()
{
    m_Weapon = CreateComponent<CWeaponComponent>(this);

}

CPlayer_Item::~CPlayer_Item()
{
    Release();
}

void CPlayer_Item::Initialize()
{
    for (auto component : m_Components)
        component->BeginPlay();

    m_Weapon->Equip_Weapon(EWeaponType::Base);

    m_tInfo.vLook = { 0.f, -1.f, 0.f };
    m_tInfo.vSize = { 30.f, 80.f, 0.f};

    if (Get_Target())
        m_OffsetPos = m_tInfo.vPos - Get_Target()->Get_Pos();
    else
        m_OffsetPos = Vec3(0.f, 0.f, 0.f);

    m_fSpeed = 250.f;
    m_PosinLocal = { 0.f, -80.f, 0.f };

    // 스프라이트
    {
        CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Player/Player03.bmp", L"Player03");

        m_FrameKey = L"Player03";
        m_tFrame.iStart = 0;
        m_tFrame.iEnd = 4;
        m_tFrame.iMotion = 0;
        m_tFrame.dwSpeed = 200;
        m_tFrame.dwTime = GetTickCount64();
    }

    m_Weapon->FOnFire.Add([this](EWeaponType _Type)
        {
            switch (_Type)
            {
            case EWeaponType::Base:
                SpawnBullet(m_vPosin);
                break;

            default: break;
            }
        });
}

int CPlayer_Item::Update()
{
    for (auto component : m_Components)
        component->TickComponent();

    if (Get_Target())
    {
        m_tInfo.vPos = Get_Target()->Get_Pos() + m_OffsetPos;
    }

	__super::Move_Frame();

    D3DXMATRIX	 matScale, matRotZ, matTrans;

    D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
    D3DXMatrixRotationZ(&matRotZ, m_fAngle);
    D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

    m_tInfo.matWorld = matScale * matRotZ * matTrans;

    m_vPosin = m_PosinLocal;
    D3DXVec3TransformCoord(&m_vPosin, &m_vPosin, &m_tInfo.matWorld);

    return OBJ_NOEVENT;
}

void CPlayer_Item::Late_Update()
{
    CPlayer::Late_Update();
}

void CPlayer_Item::Render(HDC hDC)
{
	Vec3 center = { 0.f, 0.f, 0.f };
	D3DXVec3TransformCoord(&center, &center, &m_tInfo.matWorld);

	const int destW = (int)(m_tInfo.vSize.x * 2.f);
	const int destH = (int)(m_tInfo.vSize.y * 2.f);

	const int destX = (int)(center.x - m_tInfo.vSize.x);
	const int destY = (int)(center.y - m_tInfo.vSize.y);

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

void CPlayer_Item::Release()
{
    CPlayer::Release();
}

void CPlayer_Item::AddComponent(CComponent* _Component)
{
    CPlayer::AddComponent(_Component);

    m_Components.push_back(_Component);
}

void CPlayer_Item::OnComponentBeginOverlap(CObject* _Dst)
{
    CPlayer::OnComponentBeginOverlap(_Dst);

    if (!_Dst) return;

    //TakeDamage(_Dst->Get_Attack());
}

void CPlayer_Item::SpawnBullet(const Vec3& pos)
{
    CObjectManager::Get_Instance()->AddObject(
        BULLET, CAbstractFactory<CBullet_Base>::Create(pos));
}
