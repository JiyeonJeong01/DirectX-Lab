#include "pch.h"
#include "CScene03.h"

#include "CAbstractFactory.h"
#include "CObjectManager.h"
#include "CBmpManager.h"
#include "CMonster.h"
#include "CMonster03_Base.h"
#include "CMonster03_Ghoul.h"
#include "CMonster03_Golem.h"
#include "CPlayer.h"
#include "CPlayer03.h"
#include "CScrollManager.h"

CScene03::CScene03()
{

}

CScene03::~CScene03()
{
    Release();
}

void CScene03::Initialize()
{
    CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Stage03.bmp", L"Stage03");

    CObjectManager::Get_Instance()->AddObject(PLAYER, CAbstractFactory<CPlayer03>::Create());

    m_SpawnCooltime = m_MinCooltime + (float)rand() / RAND_MAX * (m_MaxCooltime - m_MinCooltime);
}

int CScene03::Update()
{

    m_SpawnTime += DELTA;

    if (m_SpawnTime >= m_SpawnCooltime)
    {
        SpawnMonster();

        m_SpawnTime = 0.0f;
        m_SpawnCooltime = m_MinCooltime + (float)rand() / RAND_MAX * (m_MaxCooltime - m_MinCooltime);
    }

    CObjectManager::Get_Instance()->Update();
    CScrollManager::Get_Instance()->Set_ScrollY(2.2f);


    return OBJ_NOEVENT;
}

void CScene03::Late_Update()
{
    CObjectManager::Get_Instance()->Late_Update();
}

void CScene03::Render(HDC _hDC)
{
    const int iScrollY = (int)CScrollManager::Get_Instance()->Get_ScrollY();

    HDC hGroundDC = CBmpManager::Get_Instance()->Find_Img(L"Stage03");

    const int width = 768;
    const int height = 545;

    int ratio = iScrollY % height;

    if (ratio > 0)
        ratio -= height;

    BitBlt(_hDC, 0, ratio,     width, height, hGroundDC, 0, 0, SRCCOPY);
    BitBlt(_hDC, 0, ratio + height, width, height, hGroundDC, 0, 0, SRCCOPY);

    CObjectManager::Get_Instance()->Render(_hDC);
}

void CScene03::Release()
{

}

void CScene03::SpawnMonster()
{
    const float x = static_cast<float>(m_SpawnMinX + (rand() % (m_SpawnMaxX - m_SpawnMinX + 1)));
    const float y = static_cast<float>(m_SpawnMinY + (rand() % (m_SpawnMaxY - m_SpawnMinY + 1)));

    CObjectManager::Get_Instance()->AddObject(
        //MONSTER, CAbstractFactory<CMonster03_Ghoul>::CreatePos(Vec3(x, y, 0.f)));
        MONSTER, CAbstractFactory<CMonster03_Golem>::CreatePos(Vec3(x, y, 0.f)));
}
