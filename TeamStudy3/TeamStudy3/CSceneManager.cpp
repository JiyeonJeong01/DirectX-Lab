#include "pch.h"
#include "CSceneManager.h"
#include "CScene01.h"
#include "CScene02.h"
#include "CScene03.h"
#include "CScene04.h"
#include "CSceneOver04.h"

CSceneManager* CSceneManager::m_pInstance = nullptr;

CSceneManager::CSceneManager() : m_pScene(nullptr), m_SceneNumber(SCENE_END), m_bDead(false)
{
}

CSceneManager::~CSceneManager()
{
	Release();
}

void CSceneManager::Initialize()
{

}

void CSceneManager::Update()
{
	CObjectManager::Get_Instance()->Update();
	if (m_pScene)
	{
		m_bDead = m_pScene->Update();


		if (m_bDead)
		{
			switch (m_SceneNumber)
			{
			case SCENE01:
				CSceneManager::Get_Instance()->ChangeScene(SCENE02);
				break;
			case SCENE02:
				CSceneManager::Get_Instance()->ChangeScene(SCENE03);
				break;
			case SCENE03:
				CSceneManager::Get_Instance()->ChangeScene(SCENE04);
				break;
			case SCENE04:
				CSceneManager::Get_Instance()->ChangeScene(SCENE_END);
			}
		}

		else
		{
			return;
		}
	}
}

void CSceneManager::Late_Update()
{
	CObjectManager::Get_Instance()->Late_Update();
	if (m_pScene)
	{
		m_pScene->Late_Update();
	}
}

void CSceneManager::Render(HDC hdc)
{
    if (m_pScene)
    {
        m_pScene->Render(hdc);
    }

}

void CSceneManager::Release()
{
	Safe_Delete(m_pScene);
}

int CSceneManager::ChangeScene(SCENENUMBER _eSceneNumber)
{
	if (m_SceneNumber == _eSceneNumber)
		return 0;
	CScene* newScene = nullptr;

	switch (_eSceneNumber)
	{
	case SCENE01:
		newScene = new CScene01;
		m_SceneNumber = SCENE01;
		break;
	case SCENE02:
		newScene = new CScene02;
		m_SceneNumber = SCENE02;
		break;
	case SCENE03:
		newScene = new CScene03;
		m_SceneNumber = SCENE03;
		break;
	case SCENE04:
		newScene = new CScene04;
		m_SceneNumber = SCENE04;
		break;
    case SCENEOVER04:
        newScene = new CSceneOver04;
        m_SceneNumber = SCENEOVER04;
        break;
	case SCENE_END:
		m_SceneNumber = SCENE_END;
	}

	if (m_SceneNumber != SCENE_END)
	{
		Safe_Delete(m_pScene);
		m_pScene = newScene;

		m_pScene->Initialize();
	}
	return 0;
}
