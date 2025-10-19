#include "pch.h"
#include "CLogo.h"
#include "CBmpManager.h"
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
    pButton[0] = new CButton(100.f, 450.f, 0);
    pButton[0]->Initialize();
    dynamic_cast<CButton*>(pButton[0])->SetFrameKey(L"Stage1");

    pButton[1] = new CButton(300.f, 450.f, 1);
    pButton[1]->Initialize();
    dynamic_cast<CButton*>(pButton[1])->SetFrameKey(L"Stage2");

    pButton[2] = new CButton(500.f, 450.f, 2);
    pButton[2]->Initialize();
    dynamic_cast<CButton*>(pButton[2])->SetFrameKey(L"Stage3");

    pButton[3] = new CButton(700.f, 450.f, 3);
    pButton[3]->Initialize();
    dynamic_cast<CButton*>(pButton[3])->SetFrameKey(L"Stage4");
}

int CLogo::Update()
{
    return OBJ_NOEVENT;
}

void CLogo::Late_Update()
{
    for(int i = 0; i < 4; ++i)
    {
        pButton[i]->Late_Update();
    }
}

void CLogo::Render(HDC _hDC)
{
    Rectangle(_hDC, -10, -10, WINCX + 10, WINCY + 10); 
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
