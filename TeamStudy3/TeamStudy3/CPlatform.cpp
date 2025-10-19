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
    m_vPlatformPoint[0] = { m_tInfo.vPos.x - m_tInfo.vSize.x, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.f };
    m_vPlatformPoint[1] = { m_tInfo.vPos.x + m_tInfo.vSize.x, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.f };
    m_vPlatformPoint[2] = { m_tInfo.vPos.x + m_tInfo.vSize.x, m_tInfo.vPos.y + m_tInfo.vSize.y, 0.f };
    m_vPlatformPoint[3] = { m_tInfo.vPos.x - m_tInfo.vSize.x, m_tInfo.vPos.y + m_tInfo.vSize.y, 0.f };
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

    int iScrollX = (int)CScrollManager::Get_Instance()->Get_ScrollX();
    int iScrollY = (int)CScrollManager::Get_Instance()->Get_ScrollY();

    POINT points[4];
    for (int i = 0; i < 4; ++i)
    {
        points[i].x = (int)m_vPlatformPoint[i].x + iScrollX;
        points[i].y = (int)m_vPlatformPoint[i].y + iScrollY;
    }

    // 흰색 브러시 생성 및 선택
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(WHITE_BRUSH));
    HPEN   hOldPen = (HPEN)SelectObject(hDC, GetStockObject(BLACK_PEN));

    // 내부를 흰색으로 채운 사각형(폴리곤) 그리기
    Polygon(hDC, points, 4);

    // 이전 브러시/펜 복원
    SelectObject(hDC, hOldBrush);
    SelectObject(hDC, hOldPen);

    //MoveToEx(hDC, (int)m_vPlatformPoint[0].x + iScrollX, (int)m_vPlatformPoint[0].y + iScrollY, nullptr);
    //
    //for (int i = 0; i < 4; ++i)
    //    LineTo(hDC, (int)m_vPlatformPoint[i].x + iScrollX, (int)m_vPlatformPoint[i].y + iScrollY);
    //
    //LineTo(hDC, (int)m_vPlatformPoint[0].x + iScrollX, (int)m_vPlatformPoint[0].y + iScrollY);

}

void CPlatform::Release()
{
}

void CPlatform::On_Collision(CObject* _pColObj, Vec3 _vColSize)
{
}

void CPlatform::Set_PlatformPos(Vec3 _vPlatformPos)
{
    m_tInfo.vPos = { _vPlatformPos };
    Set_PlatformPoint();
}

void CPlatform::Set_PlatformSize(Vec3 _vPlatformSize)
{
    m_tInfo.vSize = { _vPlatformSize };
    Set_PlatformPoint();
}

void CPlatform::Set_PlatformPoint()
{
    m_vPlatformPoint[0] = { m_tInfo.vPos.x - m_tInfo.vSize.x, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.f };
    m_vPlatformPoint[1] = { m_tInfo.vPos.x + m_tInfo.vSize.x, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.f };
    m_vPlatformPoint[2] = { m_tInfo.vPos.x + m_tInfo.vSize.x, m_tInfo.vPos.y + m_tInfo.vSize.y, 0.f };
    m_vPlatformPoint[3] = { m_tInfo.vPos.x - m_tInfo.vSize.x, m_tInfo.vPos.y + m_tInfo.vSize.y, 0.f };
}
