#pragma once
#include "CMonster03_Base.h"

class CMonster03_DrumTong : public CMonster03_Base
{
public:
    CMonster03_DrumTong();
    ~CMonster03_DrumTong() override;

public:
    void Initialize() override;
    int  Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    virtual void OnComponentBeginOverlap(CObject* _Dst) override;

private:
    float m_Timer = 0.f;

};

