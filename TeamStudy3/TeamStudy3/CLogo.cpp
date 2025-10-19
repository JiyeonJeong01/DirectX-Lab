#include "pch.h"
#include "CLogo.h"
#include "CBmpManager.h"
#include "CSceneManager.h"
#include "CButton.h"


CLogo::CLogo()
{
    for(int i = 0; i < 4; ++i)
    {
        pButton[i] = nullptr;
    }
}

CLogo::~CLogo()
{
    Release();
}

void CLogo::Initialize()
{
    pButton[0] = new CButton(179.f, 480.f, 0);
    pButton[0]->Initialize();
    dynamic_cast<CButton*>(pButton[0])->SetFrameKey(L"Stage1");

    pButton[1] = new CButton(325.f, 480.f, 1);
    pButton[1]->Initialize();
    dynamic_cast<CButton*>(pButton[1])->SetFrameKey(L"Stage2");

    pButton[2] = new CButton(471.f, 480.f, 2);
    pButton[2]->Initialize();
    dynamic_cast<CButton*>(pButton[2])->SetFrameKey(L"Stage3");

    pButton[3] = new CButton(617.f, 480.f, 3);
    pButton[3]->Initialize();
    dynamic_cast<CButton*>(pButton[3])->SetFrameKey(L"Stage4");
}

int CLogo::Update()
{
    return OBJ_NOEVENT;
}

void CLogo::Late_Update()
{
    int iNum = 0;
    for(int i = 0; i < 4; ++i)
    {
        pButton[i]->Late_Update();
    }
    for (int i = 0; i < 4; ++i)
    {
        if (dynamic_cast<CButton*>(pButton[i])->GetClicked(i, iNum))
        {
            if (iNum == 0)
            {
                CSceneManager::Get_Instance()->ChangeScene(SCENE01);
                break;
            }
            else if (iNum == 1)
            {
                CSceneManager::Get_Instance()->ChangeScene(SCENE02);
                break;
            }
            else if (iNum == 2)
            {
                CSceneManager::Get_Instance()->ChangeScene(SCENE03);
                break;
            }
            else if (iNum == 3)
            {
                CSceneManager::Get_Instance()->ChangeScene(SCENE04);
                break;
            }
        }
    }
}

void CLogo::Render(HDC _hDC)
{
    HDC	hMemDC = CBmpManager::Get_Instance()->Find_Img(L"Title");
    BitBlt(_hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
    for(int i = 0; i < 4; ++i)
    {
        pButton[i]->Render(_hDC);
    }
}

void CLogo::Release()
{
    for(int i = 0; i < 4; ++i)
    {
        Safe_Delete<CObject*>(pButton[i]);
    }
}
