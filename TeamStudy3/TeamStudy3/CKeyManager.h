#pragma once

#include "Define.h"

class CKeyManager
{
private:
	CKeyManager();
	~CKeyManager();

public:
	bool		Key_Pressing(int iKey);
	bool		Key_Up(int iKey);		// 눌렀다가 뗏을 때
	bool		Key_Down(int iKey);		// 누르자마자

	void		Key_Update();


public:
	static CKeyManager* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CKeyManager;

		return m_pInstance;
	}

	static void		Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CKeyManager* m_pInstance;
	bool		m_bKeyState[VK_MAX];

};

