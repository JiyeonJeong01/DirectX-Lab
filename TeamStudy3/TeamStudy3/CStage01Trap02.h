#pragma once
#include "CObject.h"
#include "CScrollManager.h"

class CStage01Trap02 : public CObject
{
public:
    CStage01Trap02();
    virtual ~CStage01Trap02();

public:
    void Initialize() override;
    int  Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    void On_Collision(CObject* _pColObj, Vec3 _vColSize) override;

    void Set_TrapPos(Vec3 _vPlatformPos);
    void Set_TrapPoint();

    void Setup_Patrol(float x, float yA, float yB, float speed = 2.0f) {
        m_fX = x;
        m_fYMin = (yA < yB) ? yA : yB;
        m_fYMax = (yA < yB) ? yB : yA;
        m_fSpeed = (speed >= 0.f) ? speed : -speed;

        m_tInfo.vPos = { m_fX, m_fYMin, 0.f };
        m_iDir = +1;
        Set_TrapPoint();
    }

private:
    Vec3 m_vTrapPoint[4];

    float m_fYMin = 0.f;
    float m_fYMax = 0.f;
    float m_fX = 0.f;
    float m_fSpeed = 2.f;
    int   m_iDir = +1;
};

