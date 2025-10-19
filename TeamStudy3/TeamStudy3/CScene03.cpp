#include "pch.h"
#include "CScene03.h"

#include "CAbstractFactory.h"
#include "CObjectManager.h"
#include "CBmpManager.h"
#include "CMonster.h"
#include "CMonster03_Base.h"
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

    CObjectManager::Get_Instance()->AddObject(MONSTER, CAbstractFactory<CMonster03_Base>::Create());
    CObjectManager::Get_Instance()->AddObject(MONSTER, CAbstractFactory<CMonster03_Base>::Create(Vec3(200.f, 100.f, 0.f)));
    //CObjectManager::Get_Instance()->AddObject(MONSTER, CAbstractFactory<CMonster03_Base>::Create());

}

int CScene03::Update()
{
    CObjectManager::Get_Instance()->Update();

    CScrollManager::Get_Instance()->Set_ScrollY(2.2f);

    return OBJ_NOEVENT;
}

void CScene03::Late_Update()
{
    CObjectManager::Get_Instance()->Late_Update();
}

void CScene03::Render(HDC _hDC)
{
    const int iScrollY = (int)CScrollManager::Get_Instance()->Get_ScrollY();

    HDC hGroundDC = CBmpManager::Get_Instance()->Find_Img(L"Ground");

    const int width = 1920;
    const int height = 1280;

    int ratio = iScrollY % height;

    if (ratio > 0)
        ratio -= height;

    BitBlt(_hDC, 0, ratio,     width, height, hGroundDC, 0, 0, SRCCOPY);
    BitBlt(_hDC, 0, ratio + height, width, height, hGroundDC, 0, 0, SRCCOPY);

    CObjectManager::Get_Instance()->Render(_hDC);
}

void CScene03::Release()
{

}
