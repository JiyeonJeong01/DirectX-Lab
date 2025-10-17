#pragma once
#include "Define.h"

class CObject
{
public:
	CObject();
	virtual ~CObject();

public:
	virtual void		Initialize()		PURE;
	virtual int			Update()			PURE;
	virtual void		Late_Update()		PURE;
	virtual void		Render(HDC _hDC)	PURE;
	virtual void		Release()			PURE;
    virtual void		On_Collision(CObject* _pColObj, Vec3 _vColSize)	PURE;

public:
    const INFO* Get_Info() const { return &m_tInfo; }
    void	Set_Pos(const Vec3& _vPos) { m_tInfo.vPos = _vPos; }

protected:
    INFO m_tInfo;

	float			m_fSpeed;
	float			m_fAngle;
	int				m_iHp;
	int				m_iAttack;	
	bool			m_bDead;

};
