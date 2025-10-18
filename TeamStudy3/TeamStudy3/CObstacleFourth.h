#pragma once
#include "CObjectFourth.h"

class CObstacleFourth : public CObjectFourth
{
public:
    CObstacleFourth();
    virtual ~CObstacleFourth();

    void Initialize() override;
    int Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};
