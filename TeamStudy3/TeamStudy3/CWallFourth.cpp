#include "pch.h"
#include "CWallFourth.h"

CWallFourth::CWallFourth()
{

}

CWallFourth::~CWallFourth()
{
    Release();
}

void CWallFourth::Initialize()
{
    vPoint[0] = { 0.f, 0.f, 0.f };
    vPoint[1] = { 0.f, 0.f, 0.f };
}

int CWallFourth::Update()
{
    return 0;
}

void CWallFourth::Render(HDC hDC)
{
    MoveToEx(hDC, (int)vPoint[0].x, (int)vPoint[0].y, nullptr);
    LineTo(hDC, (int)vPoint[1].x, (int)vPoint[1].y);
}

void CWallFourth::Release()
{
}

void CWallFourth::SetPoint(D3DXVECTOR3 first, D3DXVECTOR3 last)
{
    vPoint[0] = first;
    vPoint[1] = last;
}
