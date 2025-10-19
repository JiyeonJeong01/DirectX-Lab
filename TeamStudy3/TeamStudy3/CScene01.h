#pragma once
#include "CScene.h"
#include <mmsystem.h>
#include <math.h>
#pragma comment(lib, "winmm.lib")

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

private:
    float   m_fTime;
    bool    m_bSoundPlayed;
};
