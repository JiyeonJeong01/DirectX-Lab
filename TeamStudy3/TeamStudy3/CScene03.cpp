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

    m_SpawnCooltime = m_MinCooltime + (float)rand() / RAND_MAX * (m_MaxCooltime - m_MinCooltime);

    m_Player = dynamic_cast<CPlayer03*>(CObjectManager::Get_Instance()->Get_Player()->front());

    // Font
    {
        m_ScoreFont = CreateFontW(
            -24, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
            HANGUL_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,
            ANTIALIASED_QUALITY, VARIABLE_PITCH | FF_DONTCARE,
            L"Malgun Gothic");

        m_ScorePos = { 20, 20 };
        m_ScoreColor = RGB(255, 255, 0);

        m_TimerFont = CreateFontW(
            -36, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
            HANGUL_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,
            ANTIALIASED_QUALITY, VARIABLE_PITCH | FF_DONTCARE,
            L"Malgun Gothic");

        m_TimerPos = { 320, 20 };
    }

    // Test
    SpawnMonster();
    SpawnMonster();
}

int CScene03::Update()
{
    if (m_SceneTimer >= 30.f)
    {
        // 바로 넘기지 말고, Clear 텍스트 보여주고, 넘기기
        CSceneManager::Get_Instance()->ChangeScene(LOGO);

        return 0;
    }

    m_SpawnTime += DELTA;
    m_SceneTimer += DELTA;

    if (m_SceneTimer >= 60.f)
    {
        m_SceneTimer = 0.f;

        // TODO : 게임 클리어 띄우고 메인 메뉴로 나가기
    }

    m_Score = m_Player->Get_Score();

    if (m_SpawnTime >= m_SpawnCooltime)
    {
        //SpawnMonster();

        m_SpawnTime = 0.0f;
        m_SpawnCooltime = m_MinCooltime + (float)rand() / RAND_MAX * (m_MaxCooltime - m_MinCooltime);
    }

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

    GdiTransparentBlt(_hDC,
        destX, destY, width, height,    
        hGroundDC,
        0, 0, width, height,
        RGB(255, 255, 255));

    CObjectManager::Get_Instance()->Render(_hDC);

    // 점수 출력 
    {
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
    }

    // 타이머 출력
    {
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
        //MONSTER, CAbstractFactory<CMonster03_Golem>::CreatePos(Vec3(x, y, 0.f)));
        MONSTER, CAbstractFactory<CMonster03_DrumTong>::CreatePos(Vec3(x, y, 0.f)));
}
