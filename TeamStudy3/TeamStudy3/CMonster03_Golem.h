#pragma once
#include "CMonster03_Base.h"

class CMonster03_Golem : public CMonster03_Base
{
public:
    CMonster03_Golem();
    ~CMonster03_Golem() override;

public:
    void Initialize() override;
    int  Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    virtual void OnComponentBeginOverlap(CObject* _Dst) override;

    virtual void Motion_Change();

private:
};

