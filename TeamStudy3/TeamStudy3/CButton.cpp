#include "pch.h"
#include "CButton.h"
#include "CBmpManager.h"
#include "CKeyManager.h"
#include "CSceneManager.h"

CButton::CButton() : m_iDrawID(0)
{
}

CButton::~CButton()
{
    Release();
}

void CButton::Initialize()
{
    m_tInfo.fCX = 150.f;
    m_tInfo.fCY = 150.f;
}

int CButton::Update()
{
    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CButton::Late_Update()
{
    POINT	ptMouse{};

    GetCursorPos(&ptMouse);

    ScreenToClient(g_hWnd, &ptMouse);

    if (PtInRect(&m_tRect, ptMouse))
    {
        if (CKeyManager::Get_Instance()->Key_Down(VK_LBUTTON))
        {
            if (!lstrcmp(L"Start", m_pFrameKey))
                CSceneManager::Get_Instance()->ChangeScene(SC_STAGE);

            else if (!lstrcmp(L"Edit", m_pFrameKey))
                CSceneManager::Get_Instance()->ChangeScene(SC_EDIT);

            else if (!lstrcmp(L"Exit", m_pFrameKey))
                DestroyWindow(g_hWnd);

            return;
        }

        m_iDrawID = 1;
    }
    else
    {
        m_iDrawID = 0;
    }
}

void CButton::Render(HDC hDC)
{
    HDC	hMemDC = CBmpManager::Get_Instance()->Find_Img(m_pFrameKey);

    GdiTransparentBlt(hDC,
        m_tRect.left,
        m_tRect.top,
        (int)m_tInfo.fCX,
        (int)m_tInfo.fCY,
        hMemDC,
        m_iDrawID * (int)m_tInfo.fCX,
        0,
        (int)m_tInfo.fCX,
        (int)m_tInfo.fCY,
        RGB(255, 255, 255));		// 제거할 픽셀의 색상
}

void CButton::Release()
{
}
