#include "pch.h"
#include "CMainGame.h"
#include "CObject.h"
#include "CSceneManager.h"
#include "CKeyManager.h"
#include "CBmpManager.h"
#include "CScrollManager.h"
#include "CObjectManager.h"
#include "CTimeManager.h"

CMainGame::CMainGame() : m_hDC(nullptr), m_dwTime(0), m_iFPS(0)
{
}

CMainGame::~CMainGame()
{
    Release();
}

void CMainGame::Initialize()
{
    m_hDC = GetDC(g_hWnd);

    CSceneManager::Get_Instance()->ChangeScene(SCENE03);
    CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Back.bmp", L"Back");
}

void CMainGame::Update()
{
    CSceneManager::Get_Instance()->Update();
    CKeyManager::Get_Instance()->Key_Update();
    CTimeManager::Get_Instance()->Update();

    // 스크롤 추가할사람은 각자 스테이지에서
    //SCROLL->Scroll_Lock();
}

void CMainGame::Late_Update()
{
    CSceneManager::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{
    HDC hBackDC = m_hDC;
    CSceneManager::Get_Instance()->Render(hBackDC);

    //HDC hBackDC = CBmpManager::Get_Instance()->Find_Img(L"Back");
    //
    //CSceneManager::Get_Instance()->Render(hBackDC);
    //
    //BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);
}

void CMainGame::Release()
{
    CSceneManager::DestroyInstance();
    CBmpManager::Destroy_Instance();
    CScrollManager::Destroy_Instance();
    CKeyManager::Destroy_Instance();
    CObjectManager::DestroyInstance();
    CTimeManager::DestroyInstance();

    ReleaseDC(g_hWnd, m_hDC);
}
