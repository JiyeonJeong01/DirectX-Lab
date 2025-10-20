#include "pch.h"
#include "CSceneClear.h"
#include "CSceneManager.h"
#include "CBmpManager.h"

CSceneClear::CSceneClear()
{
}

CSceneClear::~CSceneClear()
{
    Release();
}

void CSceneClear::Initialize()
{

}

int CSceneClear::Update()
{
    if (GetAsyncKeyState(VK_RETURN))
    {
        CSceneManager::Get_Instance()->ChangeScene(LOGO);
        return 0;
    }

    return OBJ_NOEVENT;
}

void CSceneClear::Late_Update()
{
}

void CSceneClear::Render(HDC _hDC)
{
    Rectangle(_hDC, 0, 0, WINCX, WINCY);
    HDC	hMemDC = CBmpManager::Get_Instance()->Find_Img(L"Clear");
    BitBlt(_hDC, 0, 100, 800, 600, hMemDC, 0, 0, SRCCOPY);
}

void CSceneClear::Release()
{

}
