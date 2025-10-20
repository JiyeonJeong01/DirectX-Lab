#include "pch.h"
#include "CScene02.h"

#include "CAbstractFactory.h"
#include "CObjectManager.h"
#include "CBmpManager.h"
#include "CEnemy.h"
#include "CPlayer.h"
#include "CPlayer02.h"
#include "CScrollManager.h"
#include "CSceneManager.h"

#include "CStage02PowerUpItem.h"
#include "CStage02AddItem.h"

CScene02::CScene02()
{
    dwEnemySpawnElapsedTime = 0;
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

    dwEnemySpawnElapsedTime = GetTickCount();
    dwItemSpawnElapsedTime = GetTickCount();

    bClear = false;
}

int CScene02::Update()
{
    if (bClear) return 0;
    Should_SpawnEnemy();
    Should_SpawnItem();

    CObjectManager::Get_Instance()->Update();

	return OBJ_NOEVENT;
}

void CScene02::Late_Update()
{

    if (iSpawnedEnemyCnt >= iTotalEnemyCnt &&
        (CObjectManager::Get_Instance()->Get_MonsterList()->size() == 0) && !bClear)
    {
        bClear = true;
        dwClearElapsedTime = GetTickCount();
    }

    if (bClear && (dwClearElapsedTime + 2000 < GetTickCount()))
    {
        // 씬 전환 요청
        for (int i = 0; i < OBJ_END; i++)
        {
            list<CObject*>& objList = *CObjectManager::Get_Instance()->Get_ObjList((OBJECT)i);

            for_each(objList.begin(), objList.end(), [&](CObject* pObj)->void {
                pObj->Set_Dead();
                });

            // 임시로 설정 
            CSceneManager::Get_Instance()->ChangeScene(LOGO);
        }

    }

    if (bClear) return;

    CObjectManager::Get_Instance()->Late_Update();

}

void CScene02::Render(HDC _hDC)
{
    int iScrollX = (int)CScrollManager::Get_Instance()->Get_ScrollX();
    int iScrollY = (int)CScrollManager::Get_Instance()->Get_ScrollY();

    HDC	hGroundDC = CBmpManager::Get_Instance()->Find_Img(L"Ground");
    BitBlt(_hDC, iScrollX, iScrollY, 1920, 1280, hGroundDC, 0, 0, SRCCOPY);

    if (!bClear)
        CObjectManager::Get_Instance()->Render(_hDC);

#pragma region Print Clear
    if (!bClear) return;
    HFONT hFont = CreateFont(
        80, 0, 0, 0, FW_BOLD,    
        FALSE, FALSE, FALSE,      
        HANGEUL_CHARSET,          
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY,       
        VARIABLE_PITCH | FF_SWISS, 
        L"Segoe UI"   
    );

    HFONT hOldFont = (HFONT)SelectObject(_hDC, hFont);

    SetTextColor(_hDC, RGB(0, 0, 0)); 
    SetBkMode(_hDC, TRANSPARENT);

    const wchar_t* szText = L"Clear";
    SIZE textSize;
    GetTextExtentPoint32(_hDC, szText, 5, &textSize);

    int x = (WINCX - textSize.cx) / 2;
    int y = 100;

    TextOut(_hDC, x, y, szText, 5);

    SelectObject(_hDC, hOldFont);
    DeleteObject(hFont);
#pragma endregion

    if (bClear) return ;

}

void CScene02::Release()
{
}

void CScene02::Should_SpawnEnemy()
{
    if (dwEnemySpawnElapsedTime + 3000 < GetTickCount() &&
        (CObjectManager::Get_Instance()->Get_MonsterList()->size() < iMaxEnemyCnt))
    {
        dwEnemySpawnElapsedTime = GetTickCount();
        Spawn_Enemy();
    }
}

void CScene02::Spawn_Enemy()
{
    float fRandX = float(rand() % (WINCX - 100) + 50);
    float fRandY = float(rand() % (WINCY - 100) + 50);

    CEnemy* pEnemy = static_cast<CEnemy*>(CAbstractFactory<CEnemy>::Create());

    pEnemy->Set_Player(pPlayer);
    pEnemy->Set_Pos({ fRandX, fRandY, 0.f });

    pEnemy->Set_OrbiterLv(max(iSpawnedEnemyCnt / 2 - 1, 0));

    CObjectManager::Get_Instance()->AddObject(MONSTER, pEnemy);

    iSpawnedEnemyCnt++;
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
