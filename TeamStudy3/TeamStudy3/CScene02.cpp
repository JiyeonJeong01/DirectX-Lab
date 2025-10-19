#include "pch.h"
#include "CScene02.h"

#include "CAbstractFactory.h"
#include "CObjectManager.h"
#include "CBmpManager.h"
#include "CMonster.h"
#include "CPlayer.h"
#include "CPlayer02.h"
#include "CScrollManager.h"

#include "CStage02PowerUpItem.h"
#include "CStage02AddItem.h"

CScene02::CScene02()
{
    dwItemSpawnElapsedTime = 0;
    pPlayer = nullptr;
}

CScene02::~CScene02()
{
	Release();
}

void CScene02::Initialize()
{
    CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Ground.bmp", L"Ground");

    pPlayer = static_cast<CPlayer02*>(CAbstractFactory<CPlayer02>::Create());
    CObjectManager::Get_Instance()->AddObject(PLAYER, pPlayer);

    // CObjectManager::Get_Instance()->AddObject(MONSTER, CAbstractFactory<CMonster>::Create());

    dwItemSpawnElapsedTime = GetTickCount();
}

int CScene02::Update()
{
    Should_SpawnItem();

    CObjectManager::Get_Instance()->Update();

	return OBJ_NOEVENT;
}

void CScene02::Late_Update()
{
    CObjectManager::Get_Instance()->Late_Update();
}

void CScene02::Render(HDC _hDC)
{
    int iScrollX = (int)CScrollManager::Get_Instance()->Get_ScrollX();
    int iScrollY = (int)CScrollManager::Get_Instance()->Get_ScrollY();

    HDC	hGroundDC = CBmpManager::Get_Instance()->Find_Img(L"Ground");
    BitBlt(_hDC, iScrollX, iScrollY, 1920, 1280, hGroundDC, 0, 0, SRCCOPY);

    CObjectManager::Get_Instance()->Render(_hDC);
}

void CScene02::Release()
{
}

void CScene02::Should_SpawnItem()
{
    if (dwItemSpawnElapsedTime + 5000 < GetTickCount())
    {
        dwItemSpawnElapsedTime = GetTickCount();

        // 아이템 스폰
        int iRand = rand() % 2;

        if (iRand == 0 && iCurPowerUpItemCnt < iMaxPowerUpItemCnt)
        {
            // 파워업
            Spawn_PowerUPItem();
        }
        else if (iRand == 1 && iCurAddItemCnt < iMaxAddItemCnt)
        {
            // 회전체 개수 증가
            Spawn_AddItem();
        }
    }
}

void CScene02::Spawn_PowerUPItem()
{
    iCurPowerUpItemCnt++;

    float fRandX = float(rand() % (WINCX - 200) + 100);
    float fRandY = float(rand() % (WINCY - 200) + 100);

    CStage02PowerUpItem* pPowerItem = static_cast<CStage02PowerUpItem*>(CAbstractFactory<CStage02PowerUpItem>::Create());
    CObjectManager::Get_Instance()->AddObject(ITEM, pPowerItem);
    pPowerItem->Set_Player(pPlayer);
    pPowerItem->Set_Pos({ fRandX, fRandY, 0.f });
}

void CScene02::Spawn_AddItem()
{
    iCurAddItemCnt++;

    float fRandX = float(rand() % (WINCX - 200) + 100);
    float fRandY = float(rand() % (WINCY - 200) + 100);

    CStage02AddItem* pPowerItem = static_cast<CStage02AddItem*>(CAbstractFactory<CStage02AddItem>::Create());
    CObjectManager::Get_Instance()->AddObject(ITEM, pPowerItem);
    pPowerItem->Set_Player(pPlayer);
    pPowerItem->Set_Pos({ fRandX, fRandY, 0.f });
}
