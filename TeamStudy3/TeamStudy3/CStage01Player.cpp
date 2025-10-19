#include "pch.h"
#include "CStage01Player.h"
#include "CScrollManager.h"
#include "CKeyManager.h"

CStage01Player::CStage01Player()
{
}

CStage01Player::~CStage01Player()
{
    Release();
}

void CStage01Player::Initialize()
{
    m_tInfo.vSize = { 25.f, 25.f, 0.f };
    m_tInfo.vPos = { 200.f , 300.f, 0.f };

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
}

void CStage01Player::Render(HDC hDC)
{
    int iScrollX = (int)CScrollManager::Get_Instance()->Get_ScrollX();
    int iScrollY = (int)CScrollManager::Get_Instance()->Get_ScrollY();

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
