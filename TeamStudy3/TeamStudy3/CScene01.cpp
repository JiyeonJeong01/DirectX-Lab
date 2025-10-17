#include "pch.h"
#include "CScene01.h"

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
    CObjectManager::Get_Instance()->AddObject(PLAYER, CAbstractFactory<CStage01Player>::Create());
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
    CObjectManager::Get_Instance()->Render(_hDC);
}

void CScene01::Release()
{
}
