#pragma once

#include "CComponent.h"
#include "CDelegate.h"
#include "CFire.h"

class CFire;

enum class EWeaponType { Base, Rifle, END };

struct FWeaponPreset
{
    EWeaponType type = EWeaponType::Base;

    float       fireInterval = 0.25f; 
    int         magSize = -1;        
};

class CWeaponComponent : public CComponent
{
public:
    CWeaponComponent();
    ~CWeaponComponent() override;

public:
    void BeginPlay() override;
    void TickComponent() override;
    void Release() override;

public:
    void Equip_Weapon(EWeaponType _Type);
    EWeaponType Get_WeaponType() { return m_WeaponType; }

    void BeginFire();
    void EndFire();

public:
    CDelegate<EWeaponType, EWeaponType> FOnWeaponChanged;
    CDelegate<EWeaponType> FOnFire;

    FWeaponPreset Preset_Base();
    FWeaponPreset Preset_Rifle();

private:
    void ChangeWeaponType(EWeaponType _Type);

    FWeaponPreset m_Preset;

private:
    EWeaponType m_WeaponType = EWeaponType::Base;
    CFire*      m_Fire = nullptr;
};
