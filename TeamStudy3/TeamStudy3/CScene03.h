#pragma once
#include "CScene.h"

class CScene03 : public CScene
{
public:
	CScene03();
	virtual ~CScene03();

public:
	void		Initialize()	override;
	int			Update()		override;
	void		Late_Update()	override;
	void		Render(HDC _hDC)override;
	void		Release()		override;

private:
    int         m_Score = 0;
};
