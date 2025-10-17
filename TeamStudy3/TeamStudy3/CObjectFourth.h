#pragma once

#include "Define.h"

class CObjectFourth
{
public:
    CObjectFourth();
    virtual ~CObjectFourth();

public:
    const INFO* Get_Info() const { return &m_tInfo; }

public:
    virtual void		Initialize()	PURE;
    virtual int			Update()		PURE;
    virtual void		Render(HDC hDC)	PURE;
    virtual void		Release()		PURE;


    D3DXVECTOR3* GetPoint() { return m_vPoint; }
    D3DXVECTOR3 GetPos() { return m_tInfo.vPos; }
    const float GetSpeed() const { return m_fSpeed; }

    void SetPosX(float vPosX) { m_tInfo.vPos.x = vPosX; }
    void SetPosY(float vPosY) { m_tInfo.vPos.y = vPosY; }
protected:
    INFO		m_tInfo;

    float		m_fSpeed;
    float m_fAngle;

    D3DXVECTOR3 m_vPoint[4];
    D3DXVECTOR3 m_vOriginPoint[4];
};

