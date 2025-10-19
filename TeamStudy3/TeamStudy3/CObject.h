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
    virtual void        OnComponentBeginOverlap(CObject* _Dst);

public:
    const INFO* Get_Info() const { return &m_tInfo; }
    void	 Set_Pos(const Vec3& _vPos) { m_tInfo.vPos = _vPos; }

    void     Set_Dead() { m_bDead = true; }
    void     Set_Owner(CObject* _Owner) { m_Owner = _Owner; }
    void     Set_Hp(int _Hp) { m_iHp = _Hp; }

    CObject*    Get_Owner()  { return m_Owner; }
    int         Get_TeamID() { return m_TeamID; }
    int         Get_Hp()     { return m_iHp; }
    int         Get_Attack() { return m_iAttack; }
    const Vec3& Get_Pos() { return m_tInfo.vPos; }
    bool        IsDead()     { return m_bDead; }
     
    void             TakeDamage(int _iAttack);
    virtual bool     CheckToBounds();

public:
    virtual void AddComponent(CComponent* _Component) {}

public:
    virtual RECT Get_CollisionRect() const {
        RECT rc = {
            LONG(m_tInfo.vPos.x - m_tInfo.vSize.x),
            LONG(m_tInfo.vPos.y - m_tInfo.vSize.y),
            LONG(m_tInfo.vPos.x + m_tInfo.vSize.x),
            LONG(m_tInfo.vPos.y + m_tInfo.vSize.y)
        };
        return rc;
    }

    void Move_Frame();

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

    FRAME	    	m_tFrame;
    const TCHAR*    m_FrameKey;

};
