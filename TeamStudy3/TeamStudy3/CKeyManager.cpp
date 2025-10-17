#include "pch.h"
#include "CKeyManager.h"

CKeyManager* CKeyManager::m_pInstance = nullptr;

CKeyManager::CKeyManager()
{
	ZeroMemory(m_bKeyState, sizeof(m_bKeyState));
}

CKeyManager::~CKeyManager()
{
}

bool CKeyManager::Key_Pressing(int iKey)
{
	if (GetAsyncKeyState(iKey) & 0x8000)
	{
		return true;
	}

	return false;
}

// 이전 누른 적이 없고 현재 눌렀을 경우
bool CKeyManager::Key_Down(int iKey)
{
	if ((!m_bKeyState[iKey]) && (GetAsyncKeyState(iKey) & 0x8000))
	{
		m_bKeyState[iKey] = !m_bKeyState[iKey];
		return true;
	}

	return false;
}

// 이전에 눌렀다가 지금 누르지 않은 상태
bool CKeyManager::Key_Up(int iKey)
{
	if ((m_bKeyState[iKey]) && !(GetAsyncKeyState(iKey) & 0x8000))
	{
		m_bKeyState[iKey] = !m_bKeyState[iKey];
		return true;
	}

	return false;
}


void CKeyManager::Key_Update()
{
	for (int i = 0; i < VK_MAX; ++i)
	{
		if ((m_bKeyState[i]) && !(GetAsyncKeyState(i) & 0x8000))
		{
			m_bKeyState[i] = !m_bKeyState[i];
		}

		if ((!m_bKeyState[i]) && (GetAsyncKeyState(i) & 0x8000))
		{
			m_bKeyState[i] = !m_bKeyState[i];
		}
	}

}
