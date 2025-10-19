#include "pch.h"
#include "CLogo.h"
#include "CBmpManager.h"
#define BUTTON_WIDTH  100
#define BUTTON_HEIGHT 100
#define BUTTON_GAP_X  10
#define BUTTON_GAP_Y  10

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
    HDC	hMemDC = CBmpManager::Get_Instance()->Find_Img(L"Button");
    Rectangle(_hDC, -10, -10, WINCX + 10, WINCY + 10); 

    for (int i = 0; i < 4; ++i)
    {
        GdiTransparentBlt(
            _hDC,
            50 + i * (BUTTON_WIDTH + BUTTON_GAP_X),
            450,
            100,
            100,
            hMemDC,
            i * BUTTON_WIDTH,
            0,
            100,
            100,
            RGB(255, 255, 255)
        );
    }
}

void CLogo::Release()
{
}
