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

public:
    const INFO* Get_Info() const { return &m_tInfo; }

    void Set_Pos(Vec3 _Pos)
    {
        m_tInfo.vPos.x = _Pos.x;
        m_tInfo.vPos.y = _Pos.y;
    }

protected:
    INFO m_tInfo;

	float			m_fSpeed;
	float			m_fAngle;
	int				m_iHp;
	int				m_iAttack;	
	bool			m_bDead;

    CObject*        m_pTarget;

};
