#pragma once
#include "CObjectFourth.h"

class CBoxFourth :
    public CObjectFourth
{
public:
    CBoxFourth();
    virtual ~CBoxFourth();

    void Initialize() override;
    int Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};
