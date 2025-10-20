#include "pch.h"
#include "CScene03.h"

#include "CAbstractFactory.h"
#include "CObjectManager.h"
#include "CBmpManager.h"
#include "CMonster.h"
#include "CMonster03_Base.h"
#include "CMonster03_DrumTong.h"
#include "CMonster03_Ghoul.h"
#include "CMonster03_Golem.h"
#include "CPlayer.h"
#include "CPlayer03.h"
#include "CSceneManager.h"
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
    CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Stage03_3DBack.bmp", L"Stage03");
    CObjectManager::Get_Instance()->AddObject(PLAYER, CAbstractFactory<CPlayer03>::Create());

    m_MinCooltime = m_StartMinCool;
    m_MaxCooltime = m_StartMaxCool;
    m_SpawnCooltime = m_MinCooltime + (float)rand() / RAND_MAX * (m_MaxCooltime - m_MinCooltime);

    m_Player = dynamic_cast<CPlayer03*>(CObjectManager::Get_Instance()->Get_Player()->front());

    m_ScoreFont = CreateFontW(-24, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, HANGUL_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH | FF_DONTCARE, L"Malgun Gothic");
    m_ScorePos = { 20, 20 };
    m_ScoreColor = RGB(255, 255, 0);

    m_TimerFont = CreateFontW(-36, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, HANGUL_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH | FF_DONTCARE, L"Malgun Gothic");
    m_TimerPos = { 320, 20 };
}

int CScene03::Update()
{
    if (m_SceneTimer >= m_MaxSceneTime)
    {
        CSceneManager::Get_Instance()->ChangeScene(LOGO);
        return 0;
    }

    m_SpawnTime += DELTA;
    m_SceneTimer += DELTA;

    if (!m_Player)
    {
        auto pList = CObjectManager::Get_Instance()->Get_Player();
        if (pList && !pList->empty())
            m_Player = dynamic_cast<CPlayer03*>(pList->front());
    }

    float t = m_SceneTimer / m_MaxSceneTime;
    if (t > 1.f) t = 1.f;

    m_MinCooltime = m_StartMinCool + (m_EndMinCool - m_StartMinCool) * t;
    if (m_MinCooltime < m_MinCoolFloor) m_MinCooltime = m_MinCoolFloor;

    float curMaxCool = m_StartMaxCool + (m_EndMaxCool - m_StartMaxCool) * t;
    if (curMaxCool < m_MinCooltime) curMaxCool = m_MinCooltime + 0.01f;

    int curSpawnCount = m_BaseSpawnCount + (int)((m_MaxSpawnCount - m_BaseSpawnCount) * t + 0.5f);
    if (curSpawnCount < 1) curSpawnCount = 1;
    if (curSpawnCount > m_MaxSpawnPerBurst) curSpawnCount = m_MaxSpawnPerBurst;

    int curAliveCap = m_StartAliveCap + (int)((m_EndAliveCap - m_StartAliveCap) * t + 0.5f);

    if (m_SpawnTime >= m_SpawnCooltime)
    {
        bool canSpawn = true;

        size_t alive = 0;
        if (auto monList = CObjectManager::Get_Instance()->Get_MonsterList())
            alive = monList->size();

        if (alive >= (size_t)curAliveCap)
            canSpawn = false;

        if (canSpawn)
        {
            for (int i = 0; i < curSpawnCount; ++i)
                SpawnMonster();
        }

        m_SpawnTime = 0.f;
        m_SpawnCooltime = m_MinCooltime + (float)rand() / RAND_MAX * (curMaxCool - m_MinCooltime);
        if (m_SpawnCooltime < m_MinCoolFloor) m_SpawnCooltime = m_MinCoolFloor;
    }

    if (m_Player)
        m_Score = m_Player->Get_Score();

    CObjectManager::Get_Instance()->Update();
    return OBJ_NOEVENT;
}

void CScene03::Late_Update()
{
    CObjectManager::Get_Instance()->Late_Update();
}

void CScene03::Render(HDC _hDC)
{
    HDC hGroundDC = CBmpManager::Get_Instance()->Find_Img(L"Stage03");
    if (!hGroundDC) return;

    const int width = 1024;
    const int height = 1536;

    const int destX = (int)m_vMapPos.x - 100;
    const int destY = (int)m_vMapPos.y;

    int iScrollY = CScrollManager::Get_Instance()->Get_ScrollY();

    GdiTransparentBlt(_hDC, destX, destY, width, height, hGroundDC, 0, 0, width, height, RGB(255, 255, 255));

    CObjectManager::Get_Instance()->Render(_hDC);

    if (m_ScoreFont)
    {
        wchar_t buf[64];
        swprintf_s(buf, L"SCORE : %d", m_Score);

        HGDIOBJ oldFont = SelectObject(_hDC, m_ScoreFont);
        int oldBk = SetBkMode(_hDC, TRANSPARENT);

        SetTextColor(_hDC, RGB(0, 0, 0));
        TextOutW(_hDC, m_ScorePos.x + 1, m_ScorePos.y + 1, buf, (int)wcslen(buf));

        SetTextColor(_hDC, m_ScoreColor);
        TextOutW(_hDC, m_ScorePos.x, m_ScorePos.y, buf, (int)wcslen(buf));

        SetBkMode(_hDC, oldBk);
        SelectObject(_hDC, oldFont);
    }

    if (m_TimerFont)
    {
        wchar_t buf[64];
        swprintf_s(buf, L"Timer : %d", (int)m_SceneTimer);

        HGDIOBJ oldFont = SelectObject(_hDC, m_TimerFont);
        int oldBk = SetBkMode(_hDC, TRANSPARENT);

        SetTextColor(_hDC, RGB(0, 0, 0));
        TextOutW(_hDC, m_TimerPos.x + 1, m_TimerPos.y + 1, buf, (int)wcslen(buf));

        SetTextColor(_hDC, m_TimerColor);
        TextOutW(_hDC, m_TimerPos.x, m_TimerPos.y, buf, (int)wcslen(buf));

        SetBkMode(_hDC, oldBk);
        SelectObject(_hDC, oldFont);
    }
}

void CScene03::Release()
{
    if (m_ScoreFont) { DeleteObject(m_ScoreFont); m_ScoreFont = nullptr; }
    if (m_TimerFont) { DeleteObject(m_TimerFont); m_TimerFont = nullptr; }
}

void CScene03::SpawnMonster()
{
    const float x = static_cast<float>(m_SpawnMinX + (rand() % (m_SpawnMaxX - m_SpawnMinX + 1)));
    const float y = static_cast<float>(m_SpawnMinY + (rand() % (m_SpawnMaxY - m_SpawnMinY + 1)));

    int randomValue = rand() % 100;

    CMonster03_Base* pMonster = nullptr;

    if (m_SceneTimer < 20.f)
    {
        if (randomValue < 60)
            pMonster = dynamic_cast<CMonster03_Ghoul*>(CAbstractFactory<CMonster03_Ghoul>::CreatePos(Vec3(x, y, 0.f)));
        else if (randomValue < 80)
            pMonster = dynamic_cast<CMonster03_Golem*>(CAbstractFactory<CMonster03_Golem>::CreatePos(Vec3(x, y, 0.f)));
        else
            pMonster = dynamic_cast<CMonster03_DrumTong*>(CAbstractFactory<CMonster03_DrumTong>::CreatePos(Vec3(x, y, 0.f)));
    }
    else
    {
        if (randomValue < 70)
            pMonster = dynamic_cast<CMonster03_Ghoul*>(CAbstractFactory<CMonster03_Ghoul>::CreatePos(Vec3(x, y, 0.f)));
        else
            pMonster = dynamic_cast<CMonster03_Golem*>(CAbstractFactory<CMonster03_Golem>::CreatePos(Vec3(x, y, 0.f)));
    }

    if (pMonster)
        CObjectManager::Get_Instance()->AddObject(MONSTER, pMonster);
}
