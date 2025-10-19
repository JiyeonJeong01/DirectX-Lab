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

    //m_pFrameKey = L"Stage01_Player_Left";

    m_eCurState = IDLE;
    m_ePreState = PA_END;

    m_tFrame.iStart = 0;
    m_tFrame.iEnd = 0;
    m_tFrame.iMotion = 1;
    m_tFrame.ullSpeed = 200;
    m_tFrame.ullTime = GetTickCount64();

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

    HDC	hMemDC = CBmpManager::Get_Instance()->Find_Img(m_pFrameKey);

    const int srcW = 40;
    const int srcH = 64;

    const int dstW = (int)m_tInfo.vSize.x;
    const int dstH = (int)m_tInfo.vSize.y;

    const int srcX = m_tFrame.iStart * srcW;
    const int srcY = m_tFrame.iMotion * srcH;

    GdiTransparentBlt(hDC,
        (m_tInfo.vSize.x) + iScrollX,
        (m_tInfo.vSize.y) + iScrollY,
        dstW, dstH,
        hMemDC,
        srcX, srcY,
        srcW, srcH,
        RGB(255, 0, 255));



    MoveToEx(hDC, (int)m_Point[0].x + iScrollX, (int)m_Point[0].y + iScrollY, nullptr);

    for (int i = 0; i < 4; ++i)
        LineTo(hDC, (int)m_Point[i].x + iScrollX, (int)m_Point[i].y + iScrollY);

    LineTo(hDC, (int)m_Point[0].x + iScrollX, (int)m_Point[0].y + iScrollY);
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
        m_fGravity = -20.0f;
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
