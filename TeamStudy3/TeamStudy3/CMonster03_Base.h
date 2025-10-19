#pragma once

#include "CMonster.h"

class CMonster03_Base : public CMonster
{
public:
    CMonster03_Base();
    ~CMonster03_Base() override;

public:
    void Initialize() override;
    int  Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    virtual void OnComponentBeginOverlap(CObject* _Dst) override;

private:
    void Motion_Change();

private:
    Vec3 m_vPoint[4];
    const TCHAR* m_FrameKey;

};

