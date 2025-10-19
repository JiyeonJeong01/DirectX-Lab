#include "pch.h"
#include "CScene02.h"

#include "CAbstractFactory.h"
#include "CObjectManager.h"
#include "CBmpManager.h"
#include "CMonster.h"
#include "CPlayer.h"
#include "CPlayer02.h"
#include "CScrollManager.h"

CScene02::CScene02()
{
}

CScene02::~CScene02()
{
	Release();
}

void CScene02::Initialize()
{
    CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Ground.bmp", L"Ground");

    CObjectManager::Get_Instance()->AddObject(PLAYER, CAbstractFactory<CPlayer02>::Create());

    // CObjectManager::Get_Instance()->AddObject(MONSTER, CAbstractFactory<CMonster>::Create());

}

int CScene02::Update()
{
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
