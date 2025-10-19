#include "pch.h"
#include "CItem_Rifle.h"

#include "CBmpManager.h"
#include "CHelper.h"

CItem_Rifle::CItem_Rifle()
{
}

CItem_Rifle::~CItem_Rifle()
{
}

void CItem_Rifle::Initialize()
{
    CItem::Initialize();

    m_tInfo.vSize = { 42.6f, 64.f, 0.f };

    CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Object/China_Rifle.bmp", L"Item_Rifle");

    m_FrameKey = L"Item_Rifle";

    m_tFrame.iStart = 0;
    m_tFrame.iEnd = 2;
    m_tFrame.iMotion = 0;
    m_tFrame.dwSpeed = 200;
    m_tFrame.dwTime = GetTickCount64();

}

int CItem_Rifle::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    CItem::Update();

    __super::Move_Frame();


    return OBJ_NOEVENT;
}

void CItem_Rifle::Late_Update()
{
    CItem::Late_Update();
}

void CItem_Rifle::Render(HDC _hDC)
{
    //CItem::Render(_hDC);
    Vec3 center = { 0.f, 0.f, 0.f };
    D3DXVec3TransformCoord(&center, &center, &m_tInfo.matWorld);

    const int destW = (int)(m_tInfo.vSize.x * 1.35f);
    const int destH = (int)(m_tInfo.vSize.y * 1.35f);

    const int destX = (int)(center.x - m_tInfo.vSize.x);
    const int destY = (int)(center.y - m_tInfo.vSize.y);

    // 키값 가져오기
    HDC hMemDC = CBmpManager::Get_Instance()->Find_Img(m_FrameKey);
    if (!hMemDC) return;

    HBITMAP hbmp = (HBITMAP)GetCurrentObject(hMemDC, OBJ_BITMAP);
    BITMAP bm{};
    GetObject(hbmp, sizeof(bm), &bm);

    const int cols = 3;   // 가로 프레임 수
    const int rows = 1;   // 세로 프레임 수

    const int frameW = bm.bmWidth / cols;
    const int frameH = bm.bmHeight / rows;

    const int srcX = m_tFrame.iStart * frameW;
    const int srcY = m_tFrame.iMotion * frameH;
    const int srcW = frameW;
    const int srcH = frameH;

    // 사이즈 조절 용 Stretch
    SetStretchBltMode(_hDC, HALFTONE);

    GdiTransparentBlt(_hDC,
        destX, destY, destW, destH,
        hMemDC,
        srcX, srcY, srcW, srcH,
        RGB(255, 255, 255));

}

void CItem_Rifle::Release()
{
    CItem::Release();
}

void CItem_Rifle::OnComponentBeginOverlap(CObject* _HitObject)
{
    CItem::OnComponentBeginOverlap(_HitObject);

    Use_Item(_HitObject);

    Set_Dead();
}

void CItem_Rifle::Use_Item(CObject* _HitObject)
{
    CItem::Use_Item(_HitObject);

    if (!_HitObject) return;

    auto* weapon = ::GetComponent<CWeaponComponent>(_HitObject);
    weapon->Equip_Weapon(EWeaponType::Rifle);
}

