#include "pch.h"
#include "CWeaponComponent.h"
#include "CFire.h"
#include "Define.h"

CWeaponComponent::CWeaponComponent()
{
    
}

CWeaponComponent::~CWeaponComponent()
{
    Release();

}

void CWeaponComponent::BeginPlay()
{
    m_Fire = new CFire();
    m_WeaponType = EWeaponType::Base;

    m_Fire->FOnShoot.Add([this]()
        {
            FOnFire.Broadcast(m_WeaponType);
        });

    
}

void CWeaponComponent::TickComponent()
{
    if (m_Fire)
    {
        m_Fire->Update();
    }

}

void CWeaponComponent::Release()
{
    // 델리게이트에 Reset 구현하기?

    Safe_Delete(m_Fire);
}

void CWeaponComponent::Equip_Weapon(EWeaponType _Type)
{
    ChangeWeaponType(_Type);
}

void CWeaponComponent::BeginFire()
{
    if (m_Fire)
        m_Fire->BeginFire();
}

void CWeaponComponent::EndFire()
{
    if (m_Fire)
        m_Fire->EndFire();
}

FWeaponPreset CWeaponComponent::Preset_Base()
{
   FWeaponPreset preset;

   preset.type = EWeaponType::Base;
   preset.fireInterval = 0.35f;

   return preset;
}

FWeaponPreset CWeaponComponent::Preset_Rifle()
{
    FWeaponPreset preset;

    preset.type = EWeaponType::Rifle;
    preset.fireInterval = 0.08f;

    return preset;
}

void CWeaponComponent::ChangeWeaponType(EWeaponType _Type)
{
    if (m_WeaponType == _Type) return;

    EWeaponType prev = m_WeaponType;
    m_WeaponType = _Type;

    switch (_Type)
    {
    case EWeaponType::Base:
        m_Preset = Preset_Base();
        break;

    case EWeaponType::Rifle:
        m_Preset = Preset_Rifle();
        break;
    }

    if (m_Fire)
    {
        m_Fire->SetInterval(m_Preset.fireInterval);

    }

    if (FOnWeaponChanged.IsBound())
        FOnWeaponChanged.Broadcast(prev, m_WeaponType);
}
