#include "pch.h"
#include "CLogo.h"
#include "CBmpManager.h"

CLogo::CLogo()
{
}

CLogo::~CLogo()
{
    Release();
}

void CLogo::Initialize()
{
}

int CLogo::Update()
{
    return OBJ_NOEVENT;
}

void CLogo::Late_Update()
{
}

void CLogo::Render(HDC _hDC)
{
    //HDC	hGroundDC = CBmpManager::Get_Instance()->Find_Img(L"Logo");
    //BitBlt(_hDC, 0, 0, WINCX, WINCY, hGroundDC, 0, 0, SRCCOPY);

    Rectangle(_hDC, -10, -10, WINCX + 10, WINCY + 10);
}

void CLogo::Release()
{
}
