#include "pch.h"
#include "CScrollManager.h"

CScrollManager* CScrollManager::m_pInstance = nullptr;

CScrollManager::CScrollManager() : m_fScrollX(0.f), m_fScrollY(0.f)
{
}

CScrollManager::~CScrollManager()
{
}

void CScrollManager::Scroll_Lock()
{
	if (0.f < m_fScrollX)
		m_fScrollX = 0.f;

	if (0.f < m_fScrollY)
		m_fScrollY = 0.f;

	if (WINCX - 1920 > m_fScrollX)
		m_fScrollX = WINCX - 1920;

	if (WINCY - 1280 > m_fScrollY)
		m_fScrollY = WINCY - 1280;

}

void CScrollManager::Stage01_Scroll_Lock()
{
    if (0.f < m_fScrollX)
        m_fScrollX = 0.f;

    if (0.f < m_fScrollY)
        m_fScrollY = 0.f;

    if (WINCX - 1440.f > m_fScrollX)
        m_fScrollX = WINCX - 1440.f;

    if (WINCY - 3223.f > m_fScrollY)
        m_fScrollY = WINCY - 3223.f;

}
