#pragma once

#include "CObject.h"

class CStage01Player : public CObject
{
public:
    enum PLAYERANIMATION { IDLE, WALK, JUMP, CROUCH, PA_END };

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

    float Get_PrevX() const { return m_fPrevX; }

private:
    void		Key_Input();
    void        Set_Point();

private:
    float		m_fGravity = 0.f;
    bool		m_bGrounded = false;
    float		m_fPrevBottom = 0.f;
    float       m_fPrevX = 0.f;

    PLAYERANIMATION m_eCurState;
    PLAYERANIMATION m_ePreState;

    static constexpr float kCrouchW = 64.f;
    static constexpr float kCrouchH = 36.f;

    bool            m_bPrevFaceRight = true;
    bool		    m_bFaceRight;

    Vec3 m_Point[4];
};
