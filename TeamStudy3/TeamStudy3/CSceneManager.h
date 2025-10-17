#pragma once

#include "CScene.h"
#include "CAbstractFactory.h"

class CSceneManager
{
public:
	CSceneManager();
	CSceneManager(const CSceneManager& rhs) = delete;
	CSceneManager& operator=(CSceneManager& rManager) = delete;
	~CSceneManager();

public:
	static CSceneManager* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CSceneManager;

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



public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC hdc);
	void Release();


public:
	int ChangeScene(SCENENUMBER _eSceneNumber);
	SCENENUMBER Get_SceneNumber() { return m_SceneNumber; }
private:
	static CSceneManager* m_pInstance;

	CScene* m_pScene;
	SCENENUMBER m_SceneNumber;
	BOOL	m_bDead;
};

