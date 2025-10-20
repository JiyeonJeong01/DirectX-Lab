#pragma once
#include "CScene.h"

class CPlayer02;
class CEnemy;

class CScene02 : public CScene
{
public:
	CScene02();
	virtual ~CScene02();
public:
	void		Initialize()	override;
	int			Update()		override;
	void		Late_Update()	override;
	void		Render(HDC _hDC)override;
	void		Release()		override;

private :
    CPlayer02* pPlayer;
    bool bClear;

private :
    DWORD dwClearElapsedTime;


#pragma region Enemy Member
    void Should_SpawnEnemy();
    void Spawn_Enemy();

private:
    int iCurEnemyCnt = 0;
    int iMaxEnemyCnt = 2;
    int iTotalEnemyCnt = 10;
    int iSpawnedEnemyCnt = 0;

    DWORD dwEnemySpawnElapsedTime;
#pragma endregion

#pragma region Item Member
private:
    void Should_SpawnItem();
    void Spawn_PowerUPItem();
    void Spawn_AddItem();

private:
    int iCurPowerUpItemCnt = 0;
    int iCurAddItemCnt = 0;

    int iMaxPowerUpItemCnt = 7;
    int iMaxAddItemCnt = 5;

    DWORD dwItemSpawnElapsedTime;
#pragma endregion
};
