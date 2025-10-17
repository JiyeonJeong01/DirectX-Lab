#include "pch.h"
#include "CScene03.h"

#include "CAbstractFactory.h"
#include "CObjectManager.h"
#include "CBmpManager.h"
#include "CMonster.h"
#include "CPlayer.h"
#include "CPlayer03.h"
#include "CScrollManager.h"

CScene03::CScene03()
{

}

CScene03::~CScene03()
{
    Release();
}

void CScene03::Initialize()
{
    CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Ground.bmp", L"Ground");

    CObjectManager::Get_Instance()->AddObject(PLAYER, CAbstractFactory<CPlayer03>::Create());

    for (int i = 0; i < 6; ++i)
    {
        //CObjectManager::Get_Instance()->AddObject(MONSTER, CAbstractFactory<CMonster>::Create(rand() % WINCX, rand() % WINCY));
    }

}

int CScene03::Update()
{
    CObjectManager::Get_Instance()->Update();

    return OBJ_NOEVENT;
}

void CScene03::Late_Update()
{
    CObjectManager::Get_Instance()->Late_Update();
}

void CScene03::Render(HDC _hDC)
{
    int iScrollX = (int)CScrollManager::Get_Instance()->Get_ScrollX();
    int iScrollY = (int)CScrollManager::Get_Instance()->Get_ScrollY();

    HDC	hGroundDC = CBmpManager::Get_Instance()->Find_Img(L"Ground");
    BitBlt(_hDC, iScrollX, iScrollY, 1920, 1280, hGroundDC, 0, 0, SRCCOPY);

    CObjectManager::Get_Instance()->Render(_hDC);
}

void CScene03::Release()
{

}
