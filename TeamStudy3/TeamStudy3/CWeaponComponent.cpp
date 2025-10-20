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

	m_Fire->FOnShoot.Add([this](float angleDeg)
		{
			m_ShotAngleDeg = angleDeg;

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
   preset.fireInterval = 0.5f;

   return preset;
}

FWeaponPreset CWeaponComponent::Preset_Rifle()
{
    FWeaponPreset preset;

    preset.type = EWeaponType::Rifle;
    preset.fireInterval = 0.2f;

    return preset;
}

FWeaponPreset CWeaponComponent::Preset_Rifle2()
{
    FWeaponPreset preset;

    preset.type = EWeaponType::Rifle2;
    preset.fireInterval = 0.15f;

	preset.multiAnglesDeg.clear();
	const int count = 3;
	const float step = 0.f;
	const int half = count / 2;

	// -45 ~ 0 ~ 45
	for (int i = -half; i <= half; ++i)
		preset.multiAnglesDeg.push_back(i * step);

    return preset;
}

void CWeaponComponent::ChangeWeaponType(EWeaponType _Type)
{
    if (m_WeaponType == _Type) return;

    EWeaponType prev = m_WeaponType;
    m_WeaponType = _Type;

    switch (_Type)
    {
    case EWeaponType::Base: m_Preset = Preset_Base();     break;
    case EWeaponType::Rifle: m_Preset = Preset_Rifle();   break; 
	case EWeaponType::Rifle2: m_Preset = Preset_Rifle2(); break;
    }

	if (m_Fire)
	{
		m_Fire->SetInterval(m_Preset.fireInterval);
		m_Fire->SetAnglesDeg(m_Preset.multiAnglesDeg); 
	}

	if (FOnWeaponChanged.IsBound())
		FOnWeaponChanged.Broadcast(prev, m_WeaponType);
}
