#pragma once
#include "CObject.h"
#include "CScrollManager.h"

class CStage01Trap01 : public CObject
{
public:
    CStage01Trap01();
    virtual ~CStage01Trap01();

public:
    void Initialize() override;
    int  Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    void On_Collision(CObject* _pColObj, Vec3 _vColSize) override;

    void Set_TrapPos(Vec3 _vPlatformPos);
    void Set_TrapPoint();

    void Setup_Patrol(float y, float xA, float xB, float speed = 2.0f) {
        m_fY = y;
        m_fXMin = (xA < xB) ? xA : xB;
        m_fXMax = (xA < xB) ? xB : xA;
        m_fSpeed = (speed >= 0.f) ? speed : -speed;

        m_tInfo.vPos = { m_fXMin, m_fY, 0.f };
        m_iDir = +1;
        Set_TrapPoint();
    }

private:
    Vec3 m_vTrapPoint[4];

    float m_fXMin = 0.f;
    float m_fXMax = 0.f;
    float m_fY = 0.f;
    float m_fSpeed = 2.f;
    int   m_iDir = +1;
};

