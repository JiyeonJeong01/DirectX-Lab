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
    CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Ground.bmp", L"Ground");

    CObjectManager::Get_Instance()->Add_Platform({ 400.f, 570.f, 0.f }, { 390.f, 25.f, 0.f });

    CObjectManager::Get_Instance()->AddObject(PLAYER, CAbstractFactory<CStage01Player>::Create());

    CObjectManager::Get_Instance()->Add_Platform({400.f, 450.f, 0.f }, { 25.f, 25.f, 0.f });
    CObjectManager::Get_Instance()->Add_Platform({300.f, 300.f, 0.f }, { 25.f, 25.f, 0.f });
    CObjectManager::Get_Instance()->Add_Platform({500.f, 300.f, 0.f }, { 25.f, 25.f, 0.f });
    CObjectManager::Get_Instance()->Add_Platform({200.f, 150.f, 0.f }, { 25.f, 25.f, 0.f });
    CObjectManager::Get_Instance()->Add_Platform({600.f, 150.f, 0.f }, { 25.f, 25.f, 0.f });
}

int CScene01::Update()
{
    CObjectManager::Get_Instance()->Update(); 

    return OBJ_NOEVENT;
}

void CScene01::Late_Update()
{
    CObjectManager::Get_Instance()->Late_Update();
}

void CScene01::Render(HDC _hDC)
{
    int iScrollX = (int)CScrollManager::Get_Instance()->Get_ScrollX();
    int iScrollY = (int)CScrollManager::Get_Instance()->Get_ScrollY();

    HDC	hGroundDC = CBmpManager::Get_Instance()->Find_Img(L"Ground");
    BitBlt(_hDC, iScrollX, iScrollY, 1920, 1280, hGroundDC, 0, 0, SRCCOPY);

    CObjectManager::Get_Instance()->Render(_hDC);
}

void CScene01::Release()
{
}
