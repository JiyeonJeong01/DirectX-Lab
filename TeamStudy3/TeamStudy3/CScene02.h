#pragma once
#include "CScene.h"

class CPlayer02;

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

#pragma region Item Parameter
private:
    void Should_SpawnItem();
    void Spawn_PowerUPItem();
    void Spawn_AddItem();

private:
    int iCurPowerUpItemCnt = 0;
    int iCurAddItemCnt = 0;

    int iMaxPowerUpItemCnt = 6;
    int iMaxAddItemCnt = 5;

    DWORD dwItemSpawnElapsedTime;
#pragma endregion
};
