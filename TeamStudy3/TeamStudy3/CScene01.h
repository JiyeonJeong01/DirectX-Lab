#pragma once
#include "CScene.h"

class CScene01 : public CScene
{
public:
	CScene01();
	virtual ~CScene01();
public:
	void		Initialize()	override;
	int			Update()		override;
	void		Late_Update()	override;
	void		Render(HDC _hDC)override;
	void		Release()		override;

};