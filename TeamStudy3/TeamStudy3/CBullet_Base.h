#pragma once

#include "CObject.h"

class CBullet_Base : public CObject
{
public:
    CBullet_Base();
    ~CBullet_Base() override;

public:
    void Initialize() override;
    int  Update() override;
    void Late_Update() override;
    void Render(HDC _hDC) override;
    void Release() override;

private:
    float m_Damage;

};

