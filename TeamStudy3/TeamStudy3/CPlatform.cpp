#include "pch.h"
#include "CPlatform.h"

CPlatform::CPlatform()
{
}

CPlatform::~CPlatform()
{
    Release();
}

void CPlatform::Initialize()
{
    m_vSize = { 128.f, 48.f, 0.f };
    m_fSpeed = 0.f;
    Update_Rect();
}

int CPlatform::Update()
{
    return OBJ_NOEVENT;
}

void CPlatform::Late_Update()
{
}

void CPlatform::Render(HDC hDC)
{

    int iScroll_fx = (int)CScrollManager::Get_Instance()->Get_ScrollX();
    int iScroll_fy = (int)CScrollManager::Get_Instance()->Get_ScrollY();
    //HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
    //HGDIOBJ obj = SelectObject(hDC, brush);
    //Rectangle(hDC, m_tRect.left + iScroll_fx, m_tRect.top + iScroll_fy, m_tRect.right + iScroll_fx, m_tRect.bottom + iScroll_fy);
    //SelectObject(hDC, obj);
    //DeleteObject(brush);

}

void CPlatform::Release()
{
}

void CPlatform::On_Collision(CObject* _pColObj, Vec3 _vColSize)
{
}

void CPlatform::Set_PlatformSize(float w, float h)
{
}

void CPlatform::Update_Rect()
{
    //m_tRect.left = static_cast<LONG>(m_vPos.x - (m_vSize.x * 0.5f));
    //m_tRect.top = static_cast<LONG>(m_vPos.y - (m_vSize.y * 0.5f));
    //m_tRect.right = static_cast<LONG>(m_vPos.x + (m_vSize.x * 0.5f));
    //m_tRect.bottom = static_cast<LONG>(m_vPos.y + (m_vSize.y * 0.5f));
}
