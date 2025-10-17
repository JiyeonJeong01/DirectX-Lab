#pragma once
#include "CScene.h"

class CScene04 : public CScene
{
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