#include "pch.h"
#include "CScene01.h"
#include "CBmpManager.h"
#include "CAbstractFactory.h"
#include "CKeyManager.h"
#include "CObjectManager.h"
#include "CPlatform.h"
#include "CStage01Player.h"
#include "CStage01Trap01.h"
#include "CStage01Trap02.h"
#include "CStage01Goal.h"
#include "CSceneManager.h"

CScene01::CScene01() : m_fTime(0.f), m_bSoundPlayed(false)
{
}

CScene01::~CScene01()
{
	Release();
}

void CScene01::Initialize()
{
    if (!m_bSoundPlayed)
    {
        PlaySound(L"../../Music/Stage01_BGM.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        m_bSoundPlayed = true;
    }
    m_fTime += 0.05f;

    CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Stage01/Stage01_BG.bmp", L"Stage01_BG");

    {
        CObjectManager::Get_Instance()->Add_Platform({ 720.f, 2913.f, 0.f }, { 720.f, 20.f, 0.f });
        CObjectManager::Get_Instance()->Add_Trap1(2020.f, 140.f, 500.f, 2.f);
        CObjectManager::Get_Instance()->Add_Trap1(912.f, 480.f, 1300.f, 2.f);
        CObjectManager::Get_Instance()->Add_Trap1(2530.f, 720.f, 1200.f, 1.5f);
        CObjectManager::Get_Instance()->Add_Trap2(614.f, 250.f, 1020.f, 2.f);
        CObjectManager::Get_Instance()->Add_Trap2(795.f, 2240.f, 2700.f, 2.f);

        CObjectManager::Get_Instance()->AddObject(PLAYER, CAbstractFactory<CStage01Player>::Create());

        CObjectManager::Get_Instance()->Add_Platform({ 321.f, 2822.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 244.f, 2770.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 176.f, 2710.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 283.f, 2644.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 382.f, 2604.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 537.f, 2608.f, 0.f }, { 69.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 672.f, 2658.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 770.f, 2602.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 860.f, 2550.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 958.f, 2610.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 1066.f, 2660.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 1155.f, 2600.f, 0.f }, { 23.f, 3.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 1288.f, 2540.f, 0.f }, { 69.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 1380.f, 2447.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 1280.f, 2370.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 1175.f, 2310.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 1067.f, 2256.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 972.f, 2340.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 882.f, 2280.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 797.f, 2340.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 705.f, 2270.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 616.f, 2218.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 525.f, 2280.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 434.f, 2220.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 344.f, 2154.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 252.f, 2100.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 156.f, 2100.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 72.f, 2015.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 155.f, 1937.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 326.f, 1935.f, 0.f }, { 69.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 447.f, 1872.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 532.f, 1822.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 658.f, 1822.f, 0.f }, { 69.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 840.f, 1822.f, 0.f }, { 69.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 1020.f, 1822.f, 0.f }, { 69.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 1194.f, 1822.f, 0.f }, { 69.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 1336.f, 1822.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 1395.f, 1760.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 1309.f, 1692.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 1168.f, 1624.f, 0.f }, { 69.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 1022.f, 1539.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 1122.f, 1453.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 1225.f, 1370.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 1122.f, 1281.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 1220.f, 1190.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 1364.f, 1188.f, 0.f }, { 69.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 1395.f, 1088.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 1300.f, 1006.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 1215.f, 943.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 1155.f, 1038.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 1062.f, 980.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 976.f, 1038.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 885.f, 978.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 795.f, 915.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 705.f, 857.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 616.f, 915.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 526.f, 857.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 437.f, 797.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 344.f, 734.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 253.f, 673.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 90.f, 622.f, 0.f }, { 87.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 74.f, 560.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 165.f, 496.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 338.f, 440.f, 0.f }, { 96.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 523.f, 376.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 613.f, 315.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 705.f, 257.f, 0.f }, { 23.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Platform({ 816.f, 208.f, 0.f }, { 69.f, 2.f, 0.f });
        CObjectManager::Get_Instance()->Add_Goal({ 818.f, 181.f, 0.f });
    }
    

}

int CScene01::Update()
{
    CObjectManager::Get_Instance()->Update();

    return OBJ_NOEVENT;
}

void CScene01::Late_Update()
{
    CObjectManager::Get_Instance()->Late_Update();

    if (CKeyManager::Get_Instance()->Key_Pressing('G'))
    {
        CSceneManager::Get_Instance()->ChangeScene(CLEAR);
    }

    auto pPlayerList = CObjectManager::Get_Instance()->Get_Player();
    if (pPlayerList && !pPlayerList->empty())
    {
        CObject* pPlayer = pPlayerList->front();
        const INFO* pInfo = pPlayer->Get_Info();

        float x = pInfo->vPos.x;
        float y = pInfo->vPos.y;

            const float targetScrollX = (WINCX * 0.5f) - x;
            const float targetScrollY = (WINCY * 0.5f) - y;

            auto* pScroll = CScrollManager::Get_Instance();
            const float deltaX = targetScrollX - pScroll->Get_ScrollX();
            const float deltaY = targetScrollY - pScroll->Get_ScrollY();

            pScroll->Set_ScrollX(deltaX);
            pScroll->Set_ScrollY(deltaY);

        CScrollManager::Get_Instance()->Stage01_Scroll_Lock();
    }
}

void CScene01::Render(HDC _hDC)
{
    int iScrollX = (int)CScrollManager::Get_Instance()->Get_ScrollX();
    int iScrollY = (int)CScrollManager::Get_Instance()->Get_ScrollY();

    HDC	hGroundDC = CBmpManager::Get_Instance()->Find_Img(L"Stage01_BG");
    BitBlt(_hDC, iScrollX, iScrollY, 1440, 3223, hGroundDC, 0, 0, SRCCOPY);

    CObjectManager::Get_Instance()->Render(_hDC);
}

void CScene01::Release()
{
    PlaySound(NULL, 0, 0);
}
