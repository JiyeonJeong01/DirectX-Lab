#include "pch.h"
#include "CScene01.h"
#include "CBmpManager.h"
#include "CAbstractFactory.h"
#include "CObjectManager.h"
#include "CPlatform.h"
#include "CStage01Player.h"
#include "CStage01Trap01.h"
//#include "CStage01Trap02.h"
//#include "CStage01Trap03.h"

CScene01::CScene01()
{
}

CScene01::~CScene01()
{
	Release();
}

void CScene01::Initialize()
{
    CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Stage01/Stage01_BG.bmp", L"Stage01_BG");

    CObjectManager::Get_Instance()->Add_Platform({ 720.f, 3056.f, 0.f }, { 720.f, 163.f, 0.f });
    CObjectManager::Get_Instance()->Add_Trap1({ 720.f, 2840.f, 0.f });

    CObjectManager::Get_Instance()->AddObject(PLAYER, CAbstractFactory<CStage01Player>::Create());

    CObjectManager::Get_Instance()->Add_Platform({321.f, 2840.f, 0.f }, { 23.f, 23.f, 0.f });
    CObjectManager::Get_Instance()->Add_Platform({244.f, 2790.f, 0.f }, { 23.f, 23.f, 0.f });
    CObjectManager::Get_Instance()->Add_Platform({181.f, 2730.f, 0.f }, { 23.f, 23.f, 0.f });
    CObjectManager::Get_Instance()->Add_Platform({265.f, 2674.f, 0.f }, { 23.f, 23.f, 0.f });
    CObjectManager::Get_Instance()->Add_Platform({351.f, 2674.f, 0.f }, { 23.f, 23.f, 0.f });
    CObjectManager::Get_Instance()->Add_Platform({478.f, 2617.f, 0.f }, { 69.f, 23.f, 0.f });
    CObjectManager::Get_Instance()->Add_Platform({615.f, 2617.f, 0.f }, { 23.f, 23.f, 0.f });
    CObjectManager::Get_Instance()->Add_Platform({704.f, 2675.f, 0.f }, { 23.f, 23.f, 0.f });
    CObjectManager::Get_Instance()->Add_Platform({796.f, 2617.f, 0.f }, { 23.f, 23.f, 0.f });
    CObjectManager::Get_Instance()->Add_Platform({885.f, 2554.f, 0.f }, { 23.f, 23.f, 0.f });
    CObjectManager::Get_Instance()->Add_Platform({976.f, 2617.f, 0.f }, { 23.f, 23.f, 0.f });
    CObjectManager::Get_Instance()->Add_Platform({1064.f, 2675.f, 0.f }, { 23.f, 23.f, 0.f });
    CObjectManager::Get_Instance()->Add_Platform({1154.f, 2617.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({1293.f, 2554.f, 0.f }, {69.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({1154.f, 2475.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({1065.f, 2418.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({971.f, 2357.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({885.f, 2414.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({795.f, 2355.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({705.f, 2296.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({616.f, 2235.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({525.f, 2296.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({435.f, 2235.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({345.f, 2175.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({255.f, 2116.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({164.f, 2056.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({285.f, 1993.f, 0.f }, {69.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({393.f, 1918.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({464.f, 1872.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({537.f, 1833.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({658.f, 1833.f, 0.f }, {69.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({838.f, 1833.f, 0.f }, {69.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({1020.f, 1833.f, 0.f }, {69.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({1194.f, 1833.f, 0.f }, {69.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({1335.f, 1835.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({1395.f, 1780.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({1395.f, 1704.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({1395.f, 1630.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({1274.f, 1621.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({1142.f, 1556.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({1219.f, 1496.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({1305.f, 1423.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({1384.f, 1353.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({1264.f, 1312.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({1371.f, 1257.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({1315.f, 1182.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({1246.f, 1115.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({1156.f, 1055.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({1063.f, 997.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({976.f, 1054.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({885.f, 995.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({795.f, 935.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({705.f, 877.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({616.f, 935.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({526.f, 877.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({437.f, 817.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({344.f, 754.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({253.f, 693.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({84.f, 664.f, 0.f }, {69.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({74.f, 576.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({165.f, 516.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({338.f, 476.f, 0.f }, {69.f, 23.f, 0.f });
    CObjectManager::Get_Instance()->Add_Platform({523.f, 396.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({613.f, 335.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({705.f, 277.f, 0.f }, {23.f, 23.f, 0.f});
    CObjectManager::Get_Instance()->Add_Platform({816.f, 228.f, 0.f }, {69.f, 23.f, 0.f });
    CObjectManager::Get_Instance()->Add_Platform({818.f, 181.f, 0.f }, {29.f, 32.f, 0.f });



}

int CScene01::Update()
{
    CObjectManager::Get_Instance()->Update(); 

    Late_Update();

    return OBJ_NOEVENT;
}

void CScene01::Late_Update()
{
    CObjectManager::Get_Instance()->Late_Update();

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
}
