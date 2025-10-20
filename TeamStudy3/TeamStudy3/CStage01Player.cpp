#include "pch.h"
#include "CStage01Player.h"
#include "CScrollManager.h"
#include "CKeyManager.h"
#include "CBmpManager.h"
#include "CStage01Trap01.h"
#include "CStage01Trap02.h"


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
    m_tInfo.vPos = { 720.f , 2900.f, 0.f };

    CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Stage01/Stage01_Player_Left.bmp", L"Stage01_Player_Left");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Stage01/Stage01_Player_Right.bmp", L"Stage01_Player_Right");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Stage01/Stage01_Player_Crouch_Left.bmp", L"Stage01_Player_Crouch_Left");
    CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Stage01/Stage01_Player_Crouch_Right.bmp", L"Stage01_Player_Crouch_Right");

    m_FrameKey = L"Stage01_Player_Left";

    m_eCurState = IDLE;
    m_ePreState = PA_END;

    m_tFrame.iStart = 0;
    m_tFrame.iEnd = 2;
    m_tFrame.iMotion = 0;
    m_tFrame.dwSpeed = 100;
    m_tFrame.dwTime = GetTickCount64();

    m_bFaceRight = true;
    m_bPrevFaceRight = true;

    Set_Point();

    m_fSpeed = 2.5f;

    m_fGravity = 0.f;
    m_bGrounded = false;
}

int CStage01Player::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    m_fPrevBottom = m_tInfo.vPos.y + m_tInfo.vSize.y;
    m_fPrevX = m_tInfo.vPos.x;

    const float fFall_Speed = 1.0f;
    const float fMax_Fall_Speed = 20.0f;
    
    m_fGravity += fFall_Speed;
    if (m_fGravity > fMax_Fall_Speed)
        m_fGravity = fMax_Fall_Speed;
    
    m_tInfo.vPos.y += m_fGravity;

    Key_Input();
    Set_Point();

    return OBJ_NOEVENT;
}

void CStage01Player::Late_Update()
{
    ULONGLONG curTime = GetTickCount64();
    if (curTime - m_tFrame.dwTime >= m_tFrame.dwSpeed)
    {
        m_tFrame.dwTime = curTime;

        switch (m_eCurState)
        {
        case IDLE:
            m_tFrame.iMotion = 0;
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 0;
            break;

        case JUMP:
            m_tFrame.iMotion = 1;
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 0;
            break;

        case WALK:
            m_tFrame.iMotion = 2;
            m_tFrame.iEnd = 2;
            ++m_tFrame.iStart;
            if (m_tFrame.iStart > m_tFrame.iEnd) m_tFrame.iStart = 0;
            break;

        case CROUCH:
            m_tFrame.iMotion = 0;
            m_tFrame.iStart = 0;
            m_tFrame.iEnd = 0;
            break;
        }
    }
}

void CStage01Player::Render(HDC hDC)
{
    int iScrollX = (int)CScrollManager::Get_Instance()->Get_ScrollX();
    int iScrollY = (int)CScrollManager::Get_Instance()->Get_ScrollY();

    const int destW = (int)(m_tInfo.vSize.x * 2.f);
    const int destH = (int)(m_tInfo.vSize.y * 2.f);
    const int destX = (int)(m_tInfo.vPos.x - m_tInfo.vSize.x) + iScrollX;
    const int destY = (int)(m_tInfo.vPos.y - m_tInfo.vSize.y) + iScrollY;

    HDC hMemDC = CBmpManager::Get_Instance()->Find_Img(m_FrameKey); 
    if (!hMemDC) return;

    HBITMAP hbmp = (HBITMAP)GetCurrentObject(hMemDC, OBJ_BITMAP);
    BITMAP bm{}; GetObject(hbmp, sizeof(bm), &bm); 

    const bool isCrouch = (m_eCurState == CROUCH);

    const int cols = (m_tFrame.iEnd + 1);
    const int rows = 1;
    const int frameW = isCrouch ? 64 : 40;
    const int frameH = isCrouch ? 36 : 64;
    const int srcX = (isCrouch ? 0 : m_tFrame.iStart * frameW);
    const int srcY = (isCrouch ? 0 : m_tFrame.iMotion * frameH);

    SetStretchBltMode(hDC, HALFTONE);
    GdiTransparentBlt(
        hDC,
        destX, destY, destW, destH,
        hMemDC,
        srcX, srcY, frameW, frameH,
        RGB(255, 0, 255)
    );
}

void CStage01Player::Release()
{
}

void CStage01Player::On_Collision(CObject* _pColObj, Vec3 _vColSize)
{
    if (dynamic_cast<CStage01Trap01*>(_pColObj) ||
        dynamic_cast<CStage01Trap02*>(_pColObj))
    {
        static ULONGLONG s_lastHit = 0;
        ULONGLONG now = GetTickCount64();
        if (now - s_lastHit >= 1000) {
            s_lastHit = now;

            const INFO* pTrap = _pColObj->Get_Info();
            const float dir = (m_tInfo.vPos.x < pTrap->vPos.x) ? -1.f : +1.f;

            const float fKnockX = 100.f;
            const float fJump = -17.f;

            m_tInfo.vPos.x += dir * fKnockX;
            m_fGravity = fJump;
            m_bGrounded = false;
            m_eCurState = JUMP;
        }
        return;
    }

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
    if (CKeyManager::Get_Instance()->Key_Down('S'))
    {
        m_tInfo.vPos = { 1350.f, 950.f, 0.f };
        m_fGravity = 0.f;
        m_bGrounded = false;
        m_eCurState = IDLE;
        Set_Point();
    }

    if (m_bGrounded && CKeyManager::Get_Instance()->Key_Down(VK_SPACE))
    {
        m_fGravity = -17.0f;
        m_bGrounded = false;
    }

    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
        m_bFaceRight = true;
        if (m_bPrevFaceRight != m_bFaceRight) {
            m_FrameKey = (m_eCurState == CROUCH) ? L"Stage01_Player_Crouch_Right" : L"Stage01_Player_Right";
            m_bPrevFaceRight = m_bFaceRight;
        }
        if (m_eCurState != CROUCH)
        m_tInfo.vPos.x += m_fSpeed;
    }

    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        m_bFaceRight = false;
        if (m_bPrevFaceRight != m_bFaceRight) {
            m_FrameKey = (m_eCurState == CROUCH) ? L"Stage01_Player_Crouch_Left" : L"Stage01_Player_Left";
            m_bPrevFaceRight = m_bFaceRight;
        }
        if (m_eCurState != CROUCH)
        m_tInfo.vPos.x -= m_fSpeed;
    }

    const bool wantCrouch = (GetAsyncKeyState(VK_DOWN) & 0x8000) != 0;
    const float halfStandH = 32.f;
    const float halfCrouchH = 18.f;
    const float deltaBottomY = (halfStandH - halfCrouchH);

    if (wantCrouch)
    {
        if (m_eCurState != CROUCH)
        {
            if (m_bGrounded) m_tInfo.vPos.y += deltaBottomY;

            m_tInfo.vSize = { 32.f, 18.f, 0.f };
            m_eCurState = CROUCH;
            m_FrameKey = m_bFaceRight ? L"Stage01_Player_Crouch_Right"
                : L"Stage01_Player_Crouch_Left";
        }
    }
    else
    {
        if (m_eCurState == CROUCH)
        {
            if (m_bGrounded) m_tInfo.vPos.y -= deltaBottomY;

            m_tInfo.vSize = { 20.f, 32.f, 0.f }; 
            m_FrameKey = m_bFaceRight ? L"Stage01_Player_Right"
                : L"Stage01_Player_Left";
        }

        if (!m_bGrounded)
            m_eCurState = JUMP;
        else if ((GetAsyncKeyState(VK_LEFT) | GetAsyncKeyState(VK_RIGHT)) & 0x8000)
            m_eCurState = WALK;
        else
            m_eCurState = IDLE;
    }
    
}

void CStage01Player::Set_Point()
{
    m_Point[0] = { m_tInfo.vPos.x - m_tInfo.vSize.x, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.f };
    m_Point[1] = { m_tInfo.vPos.x + m_tInfo.vSize.x, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.f };
    m_Point[2] = { m_tInfo.vPos.x + m_tInfo.vSize.x, m_tInfo.vPos.y + m_tInfo.vSize.y, 0.f };
    m_Point[3] = { m_tInfo.vPos.x - m_tInfo.vSize.x, m_tInfo.vPos.y + m_tInfo.vSize.y, 0.f };
}
