#pragma once
#include "CDelegate.h"
#include "CWeaponComponent.h"

class CFire
{
public:
    CFire();
    virtual ~CFire();

public:
    void Initialize();
    void Update();
    void Release();

public:
    void BeginFire(bool bFlag = true);
    void EndFire();

    void  SetInterval(float sec) { m_Interval = sec; m_Acc = 0.f; }
    float GetInterval() const { return m_Interval; }


public:
    CDelegate<> FOnShoot;

private:
    void DoShoot() { FOnShoot.Broadcast(); }

private:
    float m_Interval = 0.2f;
    float m_Acc = 0.f;
    bool  m_Firing = true;

};
