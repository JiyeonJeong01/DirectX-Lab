#include "pch.h"
#include "CScene04.h"
#include "CBmpManager.h"

CScene04::CScene04() : pPlayer(nullptr)
{
}

CScene04::~CScene04()
{
	Release();
}

void CScene04::Initialize()
{
    CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Ground.bmp", L"Ground");

    if (pPlayer == nullptr)
    {
        pPlayer = new CPlayerFourth;
        pPlayer->Initialize();
    }

    vecBox.push_back(new CBoxFourth);
    vecBox[0]->Initialize();
}

int CScene04::Update()
{
    pPlayer->Update();

    for (auto pBox : vecBox)
    {
        pBox->Update();
    }
	return OBJ_NOEVENT;
}

void CScene04::Late_Update()
{
    
}

void CScene04::Render(HDC _hDC)
{
    HDC	hGroundDC = CBmpManager::Get_Instance()->Find_Img(L"Ground");
    BitBlt(_hDC, 0, 0, 1920, 1280, hGroundDC, 0, 0, SRCCOPY);
    pPlayer->Render(_hDC);
    for (auto pBox : vecBox)
    {
        pBox->Render(_hDC);
    }
}

void CScene04::Release()
{
    Safe_Delete<CObjectFourth*>(pPlayer);
    for_each(vecBox.begin(), vecBox.end()
        , [](CObjectFourth* _p) -> void {
            if (_p)
            {
                delete _p;
                _p = nullptr;
            }
        });
}
