#include "pch.h"
#include "CObjectManager.h"
#include "CAbstractFactory.h"
#include "CCollisionManager.h"
#include "CObject.h"
#include "CPlatform.h"
#include "CStage01Trap01.h"
#include "CStage01Trap02.h"
#include "CStage01Goal.h"


CObjectManager* CObjectManager::m_pInstance = nullptr;

CObjectManager::CObjectManager()
{

}

CObjectManager::~CObjectManager()
{
	Release();
}

CObject* CObjectManager::AddObject(OBJECT _eID, CObject* _pObject)
{
	if (_eID >= OBJ_END || _pObject == nullptr)
		return 0;

	m_ObjectList[_eID].push_back(_pObject);

	return _pObject;
}

void CObjectManager::Initialize()
{

}

int CObjectManager::Update()
{
	bool bIsDestroy(false);
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjectList[i].begin(); iter != m_ObjectList[i].end();)
		{
			bIsDestroy = (*iter)->Update();

			if (bIsDestroy)
			{
				Safe_Delete<CObject*>((*iter));
				iter = m_ObjectList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	return 0;
}

void CObjectManager::Late_Update()
{
	for (auto& list : m_ObjectList)
		for (auto& obj : list)
			obj->Late_Update();

    CCollisionManager::Collision_Circle(m_ObjectList[BULLET], m_ObjectList[MONSTER]);
    CCollisionManager::Stage01_Collision_Platform(m_ObjectList[PLAYER], m_ObjectList[BLOCK]);
    CCollisionManager::Stage01_Collision_Trap(m_ObjectList[PLAYER], m_ObjectList[TRAP]);
    CCollisionManager::Stage01_Collision_Goal(m_ObjectList[PLAYER], m_ObjectList[GOAL]);
    CCollisionManager::Collision_Circle(m_ObjectList[ITEM], m_ObjectList[PLAYER]);
}

void CObjectManager::Render(HDC hdc)
{
	for (auto& list : m_ObjectList)
		for (auto& obj : list)
			obj->Render(hdc);
}

void CObjectManager::Release()
{
	for (int i = 0; i < OBJ_END; ++i)
		for_each(m_ObjectList[i].begin(), m_ObjectList[i].end()
			, [](CObject* _p) -> void {
				if (_p)
				{
					delete _p;
					_p = nullptr;
				}
			});

}

void CObjectManager::Add_Platform(Vec3 _vPos, Vec3 _vSize)
{
    CObject* pPlatform = CAbstractFactory<CPlatform>::Create(_vPos);
    static_cast<CPlatform*>(pPlatform)->Set_PlatformSize(_vSize);
    AddObject(BLOCK, pPlatform);
}

void CObjectManager::Add_Trap1(float y, float xA, float xB, float speed)
{
    auto* trap01 = static_cast<CStage01Trap01*>(
        CAbstractFactory<CStage01Trap01>::Create({ xA, y, 0.f })
        );
    trap01->Setup_Patrol(y, xA, xB, speed);
    AddObject(TRAP, trap01);
}

void CObjectManager::Add_Trap2(float x, float yA, float yB, float speed)
{
    auto* trap02 = static_cast<CStage01Trap02*>(
        CAbstractFactory<CStage01Trap02>::Create({ x, yA, 0.f })
        );
    trap02->Setup_Patrol(x, yA, yB, speed);
    AddObject(TRAP, trap02);
}

void CObjectManager::Add_Goal(Vec3 _vPos)
{
    CObject* pGoal = CAbstractFactory<CStage01Goal>::Create(_vPos);
    AddObject(GOAL, pGoal);
}
