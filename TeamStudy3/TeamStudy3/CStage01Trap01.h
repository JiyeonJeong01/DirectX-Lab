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

private:
    Vec3 m_vTrapPoint[4];
};

