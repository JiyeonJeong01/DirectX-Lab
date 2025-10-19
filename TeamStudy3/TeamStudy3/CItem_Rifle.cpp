#include "pch.h"
#include "CItem_Rifle.h"

#include "CHelper.h"

CItem_Rifle::CItem_Rifle()
{
}

CItem_Rifle::~CItem_Rifle()
{
}

void CItem_Rifle::Initialize()
{
    CItem::Initialize();
}

int CItem_Rifle::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    CItem::Update();




    return OBJ_NOEVENT;
}

void CItem_Rifle::Late_Update()
{
    CItem::Late_Update();
}

void CItem_Rifle::Render(HDC _hDC)
{
    CItem::Render(_hDC);
}

void CItem_Rifle::Release()
{
    CItem::Release();
}

void CItem_Rifle::OnComponentBeginOverlap(CObject* _HitObject)
{
    CItem::OnComponentBeginOverlap(_HitObject);

    Use_Item(_HitObject);

    Set_Dead();
}

void CItem_Rifle::Use_Item(CObject* _HitObject)
{
    CItem::Use_Item(_HitObject);

    if (!_HitObject) return;

    auto* weapon = ::GetComponent<CWeaponComponent>(_HitObject);
    weapon->Equip_Weapon(EWeaponType::Rifle);
}

