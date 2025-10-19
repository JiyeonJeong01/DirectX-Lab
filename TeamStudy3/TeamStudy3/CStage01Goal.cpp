#include "pch.h"
#include "CStage01Goal.h"
#include "CStage01Player.h"
#include "CSceneManager.h"

CStage01Goal::CStage01Goal()
{
}

CStage01Goal::~CStage01Goal()
{
    Release();
}

void CStage01Goal::Initialize()
{

    m_tInfo.vSize = { 29.f, 32.f, 0.f };

    Set_GoalPoint();
}

int CStage01Goal::Update()
{
    return OBJ_NOEVENT;
}

void CStage01Goal::Late_Update()
{
}

void CStage01Goal::Render(HDC hDC)
{

    int iScrollX = (int)CScrollManager::Get_Instance()->Get_ScrollX();
    int iScrollY = (int)CScrollManager::Get_Instance()->Get_ScrollY();

    POINT points[4];
    for (int i = 0; i < 4; ++i)
    {
        points[i].x = (int)m_vGoalPoint[i].x + iScrollX;
        points[i].y = (int)m_vGoalPoint[i].y + iScrollY;
    }

    HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(WHITE_BRUSH));
    HPEN   hOldPen = (HPEN)SelectObject(hDC, GetStockObject(BLACK_PEN));

    Polygon(hDC, points, 4);

    SelectObject(hDC, hOldBrush);
    SelectObject(hDC, hOldPen);

    MoveToEx(hDC, (int)m_vGoalPoint[0].x + iScrollX, (int)m_vGoalPoint[0].y + iScrollY, nullptr);

    for (int i = 0; i < 4; ++i)
        LineTo(hDC, (int)m_vGoalPoint[i].x + iScrollX, (int)m_vGoalPoint[i].y + iScrollY);

    LineTo(hDC, (int)m_vGoalPoint[0].x + iScrollX, (int)m_vGoalPoint[0].y + iScrollY);

}

void CStage01Goal::Release()
{
}

void CStage01Goal::On_Collision(CObject* _pColObj, Vec3 _vColSize)
{
    if (dynamic_cast<CStage01Player*>(_pColObj))
    {
        CSceneManager::Get_Instance()->ChangeScene(SCENEOVER04);
    }
}

void CStage01Goal::Set_GoalPos(Vec3 _vGoalPos)
{
    m_tInfo.vPos = { _vGoalPos };
    Set_GoalPoint();
}

void CStage01Goal::Set_GoalPoint()
{
    m_vGoalPoint[0] = { m_tInfo.vPos.x - m_tInfo.vSize.x, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.f };
    m_vGoalPoint[1] = { m_tInfo.vPos.x + m_tInfo.vSize.x, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.f };
    m_vGoalPoint[2] = { m_tInfo.vPos.x + m_tInfo.vSize.x, m_tInfo.vPos.y + m_tInfo.vSize.y, 0.f };
    m_vGoalPoint[3] = { m_tInfo.vPos.x - m_tInfo.vSize.x, m_tInfo.vPos.y + m_tInfo.vSize.y, 0.f };
}
