#pragma once
#include "CObject.h"

class CObjectManager
{
private:

	CObjectManager();
	CObjectManager(const CObjectManager& rhs) = delete;
	CObjectManager& operator=(CObjectManager& rManager) = delete;
	~CObjectManager();

public:
	CObject* AddObject(OBJECT _eID, CObject* _pObject);
	void	 Initialize();
	int		 Update();
	void	 Late_Update();
	void	 Render(HDC hdc);
	void	 Release();

public:
	list<CObject*>* Get_MonsterList() { return  &m_ObjectList[MONSTER]; }
	list<CObject*>* Get_Player() { return &m_ObjectList[PLAYER]; }

public:
	static CObjectManager* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CObjectManager;
		}
		return m_pInstance;
	}


	static void DestroyInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}

	}

private:
	list<CObject*> m_ObjectList[OBJ_END];
	static CObjectManager* m_pInstance;
};