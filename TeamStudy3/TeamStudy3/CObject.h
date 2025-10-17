#pragma once
#include "Define.h"

class CObject
{
public:
	CObject();
	virtual ~CObject();

public:
	virtual void		Initialize()										PURE;
	virtual int			Update()											PURE;
	virtual void		Late_Update()										PURE;
	virtual void		Render(HDC _hDC)									PURE;
	virtual void		Release()											PURE;

private:
	float			m_fSpeed;
	float			m_fAngle;
	int				m_iHp;
	int				m_iAttack;	
	bool			m_bDead;

};