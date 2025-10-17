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
    Vec3 m_vSize = { 50.f, 50.f, 0.f };
    Vec3 m_vPos = { 400.f , 600.f, 0.f };

    m_fSpeed = 6.f;

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

    m_vPos.y += m_fGravity;

    return OBJ_NOEVENT;
}

void CStage01Player::Late_Update()
{
}

void CStage01Player::Render(HDC hDC)
{
    int iScrollX = (int)CScrollManager::Get_Instance()->Get_ScrollX();
    int iScrollY = (int)CScrollManager::Get_Instance()->Get_ScrollY();
}

void CStage01Player::Release()
{
}

void CStage01Player::On_Collision(CObject* _pColObj, Vec3 _vColSize)
{
}

void CStage01Player::Key_Input()
{
    if (CKeyManager::Get_Instance()->Key_Down(VK_SPACE) && m_bGrounded)
    {
        m_fGravity = -6.0f;
        m_bGrounded = false;
    }


    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {

    }

    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {

    }
}
