#pragma once

#include "Cobject.h"
#include "Define.h"

class CPlayer : public CObject
{
public:
    CPlayer();
    virtual ~CPlayer();

public:
    void Initialize() override;
    int  Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    void		On_Collision(CObject* _pColObj, Vec3 _vColSize)	override;

private:
    void		Key_Input();

private:
    Vec3		m_vPoint[4];
    Vec3		m_vOriginPoint[4];

    Vec3		m_vPosin;
    Vec3		m_vOriginPosin;
};

