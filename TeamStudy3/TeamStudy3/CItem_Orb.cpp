#include "pch.h"
#include "CItem_Orb.h"

#include "CAbstractFactory.h"
#include "CBmpManager.h"
#include "CHelper.h"
#include "CObjectManager.h"
#include "COrb03.h"

CItem_Orb::CItem_Orb()
{
}

CItem_Orb::~CItem_Orb()
{
}

void CItem_Orb::Initialize()
{
    CItem::Initialize();

    m_tInfo.vSize = { 42.6f, 64.f, 0.f };

    CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Object/Player03_Orb.bmp", L"Item_Orb");

    m_FrameKey = L"Item_Orb";

    m_tFrame.iStart = 0;
    m_tFrame.iEnd = 3;
    m_tFrame.iMotion = 0;
    m_tFrame.dwSpeed = 200;
    m_tFrame.dwTime = GetTickCount64();

}

int CItem_Orb::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    CItem::Update();

    __super::Move_Frame();


    return OBJ_NOEVENT;
}

void CItem_Orb::Late_Update()
{
    CItem::Late_Update();
}

void CItem_Orb::Render(HDC _hDC)
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

    const int cols = m_tFrame.iEnd + 1;   // 가로 프레임 수
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

void CItem_Orb::Release()
{
    CItem::Release();
}

void CItem_Orb::OnComponentBeginOverlap(CObject* _HitObject)
{
    CItem::OnComponentBeginOverlap(_HitObject);

    Use_Item(_HitObject);

    Set_Dead();
}

void CItem_Orb::Use_Item(CObject* _HitObject)
{
    CItem::Use_Item(_HitObject);

    if (!_HitObject) return;

    auto player = dynamic_cast<CPlayer03*>(CObjectManager::Get_Instance()->Get_Player()->front());
    if (player->IsOrbFirst()) return;

    Vec3  center = player->Get_Pos();
    float radius = 100.f;

    auto spawnAtAngle = [&](float deg) {
        float radian = D3DXToRadian(deg);
        Vec3 offset(radius * cosf(radian), radius * sinf(radian), 0.f);
        Vec3 pos = center + offset;

        auto orb = static_cast<COrb03*>(CAbstractFactory<COrb03>::CreateTarget(pos, player));
        CObjectManager::Get_Instance()->AddObject(BULLET, orb);
        };

    spawnAtAngle(45.f);
    spawnAtAngle(135.f);
    spawnAtAngle(225.f);
    spawnAtAngle(315.f);

    player->SetOrbFirst(true);
}
