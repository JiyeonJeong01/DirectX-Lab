#include "pch.h"
#include "CScene01.h"
#include "CBmpManager.h"
#include "CAbstractFactory.h"
#include "CObjectManager.h"
#include "CPlatform.h"
#include "CStage01Player.h"

CScene01::CScene01()
{
}

CScene01::~CScene01()
{
	Release();
}

void CScene01::Initialize()
{
    CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Stage01/Stage01_BG.bmp", L"Stage01_BG");

    CObjectManager::Get_Instance()->Add_Platform({ 720.f, 3056.f, 0.f }, { 720.f, 163.f, 0.f });

    CObjectManager::Get_Instance()->AddObject(PLAYER, CAbstractFactory<CStage01Player>::Create());

    CObjectManager::Get_Instance()->Add_Platform({321.f, 2840.f, 0.f }, { 23.f, 23.f, 0.f });
    CObjectManager::Get_Instance()->Add_Platform({244.f, 2790.f, 0.f }, { 23.f, 23.f, 0.f });
    CObjectManager::Get_Instance()->Add_Platform({181.f, 2730.f, 0.f }, { 23.f, 23.f, 0.f });
    CObjectManager::Get_Instance()->Add_Platform({200.f, 150.f, 0.f }, { 23.f, 23.f, 0.f });
    CObjectManager::Get_Instance()->Add_Platform({600.f, 150.f, 0.f }, { 23.f, 23.f, 0.f });
}

int CScene01::Update()
{
    CObjectManager::Get_Instance()->Update(); 

    Late_Update();

    return OBJ_NOEVENT;
}

void CScene01::Late_Update()
{
    CObjectManager::Get_Instance()->Late_Update();

    auto pPlayerList = CObjectManager::Get_Instance()->Get_Player();
    if (pPlayerList && !pPlayerList->empty())
    {
        CObject* pPlayer = pPlayerList->front();
        const INFO* pInfo = pPlayer->Get_Info();
        const float playerX = pInfo->vPos.x;
        const float playerY = pInfo->vPos.y;

        const float targetScrollX = (WINCX * 0.5f) - playerX; 
        const float targetScrollY = (WINCY * 0.5f) - playerY;

        auto* pScroll = CScrollManager::Get_Instance(); 
        const float deltaX = targetScrollX - pScroll->Get_ScrollX();
        const float deltaY = targetScrollY - pScroll->Get_ScrollY();

        pScroll->Set_ScrollX(deltaX);
        pScroll->Set_ScrollY(deltaY);
    }

    CScrollManager::Get_Instance()->Stage01_Scroll_Lock();
}

void CScene01::Render(HDC _hDC)
{
    int iScrollX = (int)CScrollManager::Get_Instance()->Get_ScrollX();
    int iScrollY = (int)CScrollManager::Get_Instance()->Get_ScrollY();

    HDC	hGroundDC = CBmpManager::Get_Instance()->Find_Img(L"Stage01_BG");
    BitBlt(_hDC, iScrollX, iScrollY, 1440, 3223, hGroundDC, 0, 0, SRCCOPY);

    CObjectManager::Get_Instance()->Render(_hDC);
}

void CScene01::Release()
{
}
