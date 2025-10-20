#pragma once

#include "CObject.h"

class CWeaponComponent;

class COrb03 : public CObject
{
public:
    COrb03();
    ~COrb03() override;

public:
    void Initialize() override;
    int  Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void OnComponentBeginOverlap(CObject* _Dst) override;

private:
    Vec3  m_OffsetBase = { 0.f, 0.f, 0.f }; 
    float m_AngleRad = 0.f;               
    float m_AngularRad = D3DXToRadian(90.f);

    float m_DamageInterval = 0.3f; 
    float m_DamageAcc = 0.f;
    bool  m_Overlapping = false;
    CObject* m_LastTarget = nullptr;
};

