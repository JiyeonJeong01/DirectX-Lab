#include "pch.h"
#include "CButton.h"
#include "CBmpManager.h"
#include "CKeyManager.h"
#include "CSceneManager.h"

CButton::CButton(float fX, float fY, int ID) : m_iDrawID(0), m_pFrameKey(nullptr)
{
    ZeroMemory(&rct, sizeof(RECT));
    m_tInfo.vPos.x = fX;
    m_tInfo.vPos.y = fY;
    m_iDrawID = ID;
}

CButton::~CButton()
{
    Release();
}

void CButton::Initialize()
{
    m_tInfo.vSize = { 146.f, 151.f, 0.f };
    rct = {(long)m_tInfo.vPos.x - (long)m_tInfo.vSize.x / 2,
        (long)m_tInfo.vPos.y - (long)m_tInfo.vSize.y / 2,
    (long)m_tInfo.vPos.x + (long)m_tInfo.vSize.x / 2,
    (long)m_tInfo.vPos.y + (long)m_tInfo.vSize.y / 2 };
}

int CButton::Update()
{
    return OBJ_NOEVENT;
}

void CButton::Late_Update()
{
    POINT	ptMouse{};

    GetCursorPos(&ptMouse);

    ScreenToClient(g_hWnd, &ptMouse);

    if (PtInRect(&rct, ptMouse))
    {
        if (GetAsyncKeyState(VK_LBUTTON))
        {
            if (!lstrcmp(L"Stage1", m_pFrameKey))
                CSceneManager::Get_Instance()->ChangeScene(SCENE01);

            else if (!lstrcmp(L"Stage2", m_pFrameKey))
                CSceneManager::Get_Instance()->ChangeScene(SCENE02);

            else if (!lstrcmp(L"Stage3", m_pFrameKey))
                CSceneManager::Get_Instance()->ChangeScene(SCENE03);
            else if (!lstrcmp(L"Stage4", m_pFrameKey))
                CSceneManager::Get_Instance()->ChangeScene(SCENE04);
            return;
        }
    }
}

void CButton::Render(HDC hDC)
{
    HDC	hMemDC = CBmpManager::Get_Instance()->Find_Img(L"Button");

    GdiTransparentBlt(hDC,
        rct.left,
        rct.top,
        (int)m_tInfo.vSize.x,
        (int)m_tInfo.vSize.y,
        hMemDC,
        m_iDrawID * (int)m_tInfo.vSize.x + (m_iDrawID * 2),
        0,
        (int)m_tInfo.vSize.x,
        (int)m_tInfo.vSize.y,
        RGB(0, 0, 0));
}

void CButton::Release()
{
}
