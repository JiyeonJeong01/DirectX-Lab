#pragma once

#include "CObject.h"

class CStage01Player : public CObject
{
public:
    CStage01Player();
    virtual ~CStage01Player();

public:
    void Initialize() override;
    int  Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    void On_Collision(CObject* _pColObj, Vec3 _vColSize)	override;
    void Set_Gravity(float g) { m_fGravity = g; }

    float Get_PrevBottom() const { return m_fPrevBottom; }
    float Get_Gravity() const { return m_fGravity; }

private:
    void		Key_Input();

private:
    float		m_fGravity = 0.f;
    bool		m_bGrounded = false;
    bool		m_bMovingHoriz = false;
    float		m_fPrevBottom = 0.f;

    Vec3 m_vSize;
    Vec3 m_vPos;

};
