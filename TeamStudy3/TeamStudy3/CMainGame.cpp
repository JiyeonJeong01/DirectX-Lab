#include "pch.h"
#include "CMainGame.h"
#include "CObject.h"
#include "CAbstractFactory.h"

CMainGame::CMainGame() : m_hDC(nullptr)
{
}

CMainGame::~CMainGame()
{
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

}

void CMainGame::Update()
{
}

void CMainGame::Late_Update()
{
}

void CMainGame::Render()
{
}

void CMainGame::Release()
{
}
