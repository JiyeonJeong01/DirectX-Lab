#pragma once
#include "CObjectFourth.h"
class CPlayerFourth : public CObjectFourth
{
private:
    void KeyInput();
public:
    CPlayerFourth();
    virtual ~CPlayerFourth();

public:
    void Initialize() override;
    int Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

