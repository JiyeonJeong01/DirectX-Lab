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
    void SetAnglesDeg(const vector<float>& angle) { m_AnglesDeg = angle; }
    const vector<float>& GetAnglesDeg() const { return m_AnglesDeg; }

public:
    CDelegate<float> FOnShoot;

private:
    void DoShoot();

private:
    float m_Interval = 0.5f;
    float m_Acc = 0.f;
    bool  m_Firing = true;
    vector<float> m_AnglesDeg; 

};
