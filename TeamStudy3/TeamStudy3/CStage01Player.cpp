#include "pch.h"
#include "CStage01Player.h"
#include "CScrollManager.h"
#include "CKeyManager.h"
#include "CBmpManager.h"

CStage01Player::CStage01Player()
{
}

CStage01Player::~CStage01Player()
{
    Release();
}

void CStage01Player::Initialize()
{
    m_tInfo.vSize = { 20.f, 32.f, 0.f };
    m_tInfo.vPos = { 720.f , 2800.f, 0.f };

    CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Stage01/Stage01_Player_Left.bmp", L"Stage01_Player_Left");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Stage01/Stage01_Player_Right.bmp", L"Stage01_Player_Right");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Stage01/Stage01_Player_Crouch_Left.bmp", L"Stage01_Player_Crouch_Left");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Stage01/Stage01_Player_Crouch_Right.bmp", L"Stage01_Player_Crouch_Right");

    m_FrameKey = L"Stage01_Player_Left";

    m_eCurState = IDLE;
    m_ePreState = PA_END;

    m_tFrame.iStart = 0;
    m_tFrame.iEnd = 3;
    m_tFrame.iMotion = 0;
    m_tFrame.dwSpeed = 200;
    m_tFrame.dwTime = GetTickCount64();

    m_bPrevFaceRight = m_bFaceRight;

    Set_Point();

    m_fSpeed = 3.f;

    m_fGravity = 0.f;
    m_bGrounded = false;
}

int CStage01Player::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    Key_Input();

    const float fFall_Speed = 1.0f;
    const float fMax_Fall_Speed = 20.0f;
    
    m_bGrounded = false;
    
    m_fGravity += fFall_Speed;
    if (m_fGravity > fMax_Fall_Speed)
        m_fGravity = fMax_Fall_Speed;
    
    m_tInfo.vPos.y += m_fGravity;

    Set_Point();

    return OBJ_NOEVENT;
}

void CStage01Player::Late_Update()
{
    if (m_bFaceRight == true)
    {
        if (m_bFaceRight == false)
        {

        }
    }
}

void CStage01Player::Render(HDC hDC)
{
    int iScrollX = (int)CScrollManager::Get_Instance()->Get_ScrollX();
    int iScrollY = (int)CScrollManager::Get_Instance()->Get_ScrollY();

    POINT points[4];
    for (int i = 0; i < 4; ++i)
    {
        points[i].x = (int)m_Point[i].x + iScrollX;
        points[i].y = (int)m_Point[i].y + iScrollY;
    }

    HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
    Polygon(hDC, points, 4);
    SelectObject(hDC, hOldBrush);
    DeleteObject(hBrush);



    //const int destW = (int)(m_tInfo.vSize.x * 2.f);
    //const int destH = (int)(m_tInfo.vSize.y * 2.f);
    //
    //const int destX = (int)(m_tInfo.vPos.x - m_tInfo.vSize.x);
    //const int destY = (int)(m_tInfo.vPos.y - m_tInfo.vSize.y);
    //
    //HDC hMemDC = CBmpManager::Get_Instance()->Find_Img(m_FrameKey);
    //if (!hMemDC) return;
    //
    //HBITMAP hbmp = (HBITMAP)GetCurrentObject(hMemDC, OBJ_BITMAP);
    //BITMAP bm{}; GetObject(hbmp, sizeof(bm), &bm);
    //
    //const int cols = m_tFrame.iEnd + 1;
    //const int rows = 1;
    //
    //const int frameW = bm.bmWidth / cols;
    //const int frameH = bm.bmHeight / rows;
    //
    //const int srcX = m_tFrame.iStart * frameW;
    //const int srcY = m_tFrame.iMotion * frameH;
    //
    //SetStretchBltMode(hDC, HALFTONE);
    //GdiTransparentBlt(hDC,
    //    destX, destY, 40.f, 64.f,
    //    hMemDC,
    //    srcX, srcY, frameW, frameH,
    //    RGB(255, 0, 255));
    //
    //
    //
    //MoveToEx(hDC, (int)m_Point[0].x + iScrollX, (int)m_Point[0].y + iScrollY, nullptr);
    //
    //for (int i = 0; i < 4; ++i)
    //    LineTo(hDC, (int)m_Point[i].x + iScrollX, (int)m_Point[i].y + iScrollY);
    //
    //LineTo(hDC, (int)m_Point[0].x + iScrollX, (int)m_Point[0].y + iScrollY);
}

void CStage01Player::Release()
{
}

void CStage01Player::On_Collision(CObject* _pColObj, Vec3 _vColSize)
{
    if (_vColSize.y > 0.f)
    {
        if (m_fGravity > 0.f) {
            m_fGravity = 0.f;
            m_bGrounded = true;
        }
        else if (m_fGravity < 0.f) {
            m_fGravity = 0.f;
        }
    }
}

void CStage01Player::Key_Input()
{
    if (m_bGrounded && CKeyManager::Get_Instance()->Key_Down(VK_SPACE))
    {
        m_fGravity = -15.0f;
        m_bGrounded = false;
    }


    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
        m_tInfo.vPos.x += m_fSpeed;
    }

    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        m_tInfo.vPos.x -= m_fSpeed;
    }
}

void CStage01Player::Set_Point()
{
    m_Point[0] = { m_tInfo.vPos.x - m_tInfo.vSize.x, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.f };
    m_Point[1] = { m_tInfo.vPos.x + m_tInfo.vSize.x, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.f };
    m_Point[2] = { m_tInfo.vPos.x + m_tInfo.vSize.x, m_tInfo.vPos.y + m_tInfo.vSize.y, 0.f };
    m_Point[3] = { m_tInfo.vPos.x - m_tInfo.vSize.x, m_tInfo.vPos.y + m_tInfo.vSize.y, 0.f };
}
