#pragma once
#include "Define.h"

class CComponent;

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

    virtual void		On_Collision(CObject* _pColObj, Vec3 _vColSize) {}

public:
    const INFO* Get_Info() const { return &m_tInfo; }
    void	Set_Pos(const Vec3& _vPos) { m_tInfo.vPos = _vPos; }

    void    Set_Dead() { m_bDead = true; }
    void    Set_Owner(CObject* _Owner) { m_Owner = _Owner; }

    CObject* Get_Owner()  { return m_Owner; }
    int      Get_TeamID() { return m_TeamID; }

public:
    virtual void AddComponent(CComponent* _Component) {}

protected:
    INFO            m_tInfo;

	float			m_fSpeed;
	float			m_fAngle;
	int				m_iHp;
	int				m_iAttack;	
	bool			m_bDead;

    CObject*        m_pTarget;
    CObject*        m_Owner;

    int             m_TeamID;

    std::vector<CComponent*> m_Components;

};
