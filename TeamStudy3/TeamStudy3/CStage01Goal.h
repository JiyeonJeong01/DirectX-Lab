#pragma once
#include "CObject.h"
#include "CScrollManager.h"

class CStage01Goal : public CObject
{
public:
    CStage01Goal();
    virtual ~CStage01Goal();

public:
    void Initialize() override;
    int  Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    void On_Collision(CObject* _pColObj, Vec3 _vColSize) override;

    void Set_GoalPos(Vec3 _vPlatformPos);
    void Set_GoalPoint();

private:
    Vec3 m_vGoalPoint[4];
};

