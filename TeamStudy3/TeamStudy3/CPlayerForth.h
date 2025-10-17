#pragma once
#include "CObjectFourth.h"
class CPlayerForth : public CObjectFourth
{
private:
    void KeyInput();
public:
    CPlayerForth();
    virtual ~CPlayerForth();

public:
    void Initialize() override;
    int Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

