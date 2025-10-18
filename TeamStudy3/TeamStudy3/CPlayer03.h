#pragma once
#include "CPlayer.h"
class CPlayer03 :
    public CPlayer
{
public:
    CPlayer03();
    ~CPlayer03() override;

public:
    void Initialize() override;
    int  Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    virtual void AddComponent(CComponent* _Component) override;

public:
    void Key_Input();
    void Fire();


private:
    Vec3		m_vPoint[4];
    Vec3		m_vOriginPoint[4];

    Vec3		m_vPosin;
    Vec3		m_vOriginPosin;

    float       m_FireHandler = 0.f;
    float       m_FireInterval = 0.5f;
    float       m_PosinLength = 50.f;
};

