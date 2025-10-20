#pragma once

#include "CPlayer.h"

class CWeaponComponent;

class CPlayer_Item : public CPlayer
{
public:
    CPlayer_Item();
    ~CPlayer_Item() override;

public:
    void Initialize() override;
    int  Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    virtual void AddComponent(CComponent* _Component) override;
    const std::vector<CComponent*>& GetAllComponents() const { return m_Components; }

    virtual void OnComponentBeginOverlap(CObject* _Dst) override;

    void SpawnBullet(const Vec3& pos);

private:
    CWeaponComponent* m_Weapon;

private:
    Vec3		m_vPosin;
    Vec3		m_vOriginPosin;

    float       m_FireHandler = 0.f;
    float       m_FireInterval = 0.5f;
    float       m_PosinLength = 50.f;

    int         m_Score = 0;

    Vec3 m_PosinLocal = { 0.f, -60.f, 0.f };
    Vec3 m_OffsetPos;
};

