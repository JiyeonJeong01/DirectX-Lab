#include "pch.h"
#include "CItem_Player.h"

#include "CAbstractFactory.h"
#include "CBmpManager.h"
#include "CHelper.h"
#include "CObjectManager.h"
#include "CPlayer_Item.h"

CItem_Player::CItem_Player()
{
}

CItem_Player::~CItem_Player()
{
}

void CItem_Player::Initialize()
{
    CItem::Initialize();

    m_tInfo.vSize = { 64.f, 64.f, 0.f };

    CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Object/Item_Player2.bmp", L"Item_Player");

    m_FrameKey = L"Item_Player";

    m_tFrame.iStart = 0;
    m_tFrame.iEnd = 3;
    m_tFrame.iMotion = 0;
    m_tFrame.dwSpeed = 200;
    m_tFrame.dwTime = GetTickCount64();
}

int CItem_Player::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    CItem::Update();
    __super::Move_Frame();


    return OBJ_NOEVENT;
}

void CItem_Player::Late_Update()
{
    CItem::Late_Update();
}

void CItem_Player::Render(HDC _hDC)
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

void CItem_Player::Release()
{
    CItem::Release();
}

void CItem_Player::OnComponentBeginOverlap(CObject* _HitObject)
{
    CItem::OnComponentBeginOverlap(_HitObject);

    Use_Item(_HitObject);

    Set_Dead();
}

void CItem_Player::Use_Item(CObject* _HitObject)
{
    CItem::Use_Item(_HitObject);

    if (!_HitObject) return;

    auto& players = *CObjectManager::Get_Instance()->Get_Player();
    if (players.empty()) return;

    auto player = dynamic_cast<CPlayer03*>(players.front());

    if (player->GetTestNumber() > 3)
        return;

    Vec3 pos = players.front()->Get_Pos();
    Vec3 spawnPos;

    if (player->GetTestNumber() == 0)
        spawnPos = Vec3(pos.x - 80.f, pos.y + 60.f, 0.f);

    else if (player->GetTestNumber() == 1)
        spawnPos = Vec3(pos.x + 80.f, pos.y + 60.f, 0.f);

    auto itemPlayer = static_cast<CPlayer_Item*>(CAbstractFactory<CPlayer_Item>::CreateTarget(spawnPos, player));
    CObjectManager::Get_Instance()->AddObject(PLAYER, itemPlayer);

    player->SetTestNumber(player->GetTestNumber() + 1);
}

