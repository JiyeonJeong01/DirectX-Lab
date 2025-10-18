#pragma once
#include "CScene.h"
#include "CPlayerFourth.h"
#include "CBoxFourth.h"
#include "CWallFourth.h"

class CScene04 : public CScene
{
private:
    CObjectFourth* pPlayer;
    vector<CObjectFourth*> vecBox;
    vector<CWallFourth*> vecWall;
public:
	CScene04();
	virtual ~CScene04();
public:
	void		Initialize()	override;
	int			Update()		override;
	void		Late_Update()	override;
	void		Render(HDC _hDC)override;
	void		Release()		override;
};
