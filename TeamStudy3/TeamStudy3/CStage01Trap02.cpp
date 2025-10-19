#include "pch.h"
#include "CStage01Trap02.h"
#include "CBmpManager.h"

CStage01Trap02::CStage01Trap02()
{
}

CStage01Trap02::~CStage01Trap02()
{
    Release();
}

void CStage01Trap02::Initialize()
{
    CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Stage01/Stage01_Trap2.bmp", L"Stage01_Trap2");
    m_FrameKey = L"Stage01_Trap2";

    m_tInfo.vSize = { 25.f, 26.f, 0.f };

    Set_TrapPoint();
}

int CStage01Trap02::Update()
{
    if (m_iDir > 0) {
        m_tInfo.vPos.y += m_fSpeed;
        if (m_tInfo.vPos.y >= m_fYMax) { m_tInfo.vPos.y = m_fYMax; m_iDir = -1; }
    }
    else {
        m_tInfo.vPos.y -= m_fSpeed;
        if (m_tInfo.vPos.y <= m_fYMin) { m_tInfo.vPos.y = m_fYMin; m_iDir = +1; }
    }

    Set_TrapPoint();

    return OBJ_NOEVENT;
}

void CStage01Trap02::Late_Update()
{
}

void CStage01Trap02::Render(HDC hDC)
{
    HDC hMemDC = CBmpManager::Get_Instance()->Find_Img(m_FrameKey);
    if (!hMemDC) return;

    const int iScrollX = (int)CScrollManager::Get_Instance()->Get_ScrollX();
    const int iScrollY = (int)CScrollManager::Get_Instance()->Get_ScrollY();

    const int dstW = (int)(m_tInfo.vSize.x * 2.f);
    const int dstH = (int)(m_tInfo.vSize.y * 2.f);
    const int dx = (int)(m_tInfo.vPos.x - m_tInfo.vSize.x) + iScrollX;
    const int dy = (int)(m_tInfo.vPos.y - m_tInfo.vSize.y) + iScrollY;

    const int srcW = 50, srcH = 52;

    SetStretchBltMode(hDC, HALFTONE);
    GdiTransparentBlt(
        hDC, dx, dy, dstW, dstH,
        hMemDC, 0, 0, srcW, srcH,
        RGB(255, 255, 255)
    );

}

void CStage01Trap02::Release()
{
}

void CStage01Trap02::On_Collision(CObject* _pColObj, Vec3 _vColSize)
{
}

void CStage01Trap02::Set_TrapPos(Vec3 _vTrapPos)
{
    m_tInfo.vPos = _vTrapPos;
    Set_TrapPoint();
}

void CStage01Trap02::Set_TrapPoint()
{
    m_vTrapPoint[0] = { m_tInfo.vPos.x - m_tInfo.vSize.x, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.f };
    m_vTrapPoint[1] = { m_tInfo.vPos.x + m_tInfo.vSize.x, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.f };
    m_vTrapPoint[2] = { m_tInfo.vPos.x + m_tInfo.vSize.x, m_tInfo.vPos.y + m_tInfo.vSize.y, 0.f };
    m_vTrapPoint[3] = { m_tInfo.vPos.x - m_tInfo.vSize.x, m_tInfo.vPos.y + m_tInfo.vSize.y, 0.f };
}
