#pragma once

#include "CObject.h"
#include "CPlayer03.h"
#include "CWeaponComponent.h"

static const char* ToString(EWeaponType _Type)
{
    switch (_Type)
    {
    case EWeaponType::Base:  return "Base";
    case EWeaponType::Rifle: return "Rifle";
    default:                 return "Unknown";
    }
}

static const char* CurWeaponType(CWeaponComponent* weapon)
{
    return (weapon) ? ToString(weapon->Get_WeaponType()) : "null-weapon";
}

static bool IsSameTeam(CObject* Dst, CObject* Src)
{
    return Dst->Get_TeamID() == Src->Get_TeamID();
}

static bool IsSameOwner(CObject* Dst, CObject* Src)
{
    return Dst->Get_Owner() == Src->Get_Owner();
}

static bool IsSameOwnerTeam(CObject* Dst, CObject* Src)
{
    return Dst->Get_Owner()->Get_TeamID() == Src->Get_Owner()->Get_TeamID();
}

static  Vec3 RotateZ_Deg(const Vec3& v, float deg)
{
    const float radian = D3DXToRadian(deg);
    return Vec3(v.x * cosf(radian) - v.y * sinf(radian), v.x * sinf(radian) + v.y * cosf(radian), v.z);
}

static void DrawRect(HDC hDC, const Vec3 pts[4], COLORREF color = RGB(0, 255, 255))
{
    HPEN hPen = CreatePen(PS_SOLID, 1, color);
    HBRUSH hBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

    HPEN   hOldPen = (HPEN)SelectObject(hDC, hPen);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

    MoveToEx(hDC, (int)pts[0].x, (int)pts[0].y, nullptr);
    LineTo(hDC, (int)pts[1].x, (int)pts[1].y);
    LineTo(hDC, (int)pts[2].x, (int)pts[2].y);
    LineTo(hDC, (int)pts[3].x, (int)pts[3].y);
    LineTo(hDC, (int)pts[0].x, (int)pts[0].y);

    SelectObject(hDC, hOldBrush);
    SelectObject(hDC, hOldPen);
    DeleteObject(hPen);
}

template<typename T>
static T* CreateComponent(CObject* _Owner)
{
    if (_Owner == nullptr)
        return nullptr;

    CComponent* component = new T();
    //component->BeginPlay();
    component->Set_Owner(_Owner);

    auto componentType = dynamic_cast<T*>(component);

    if (componentType)
        _Owner->AddComponent(componentType);

    return componentType;
}

template<typename T>
static T* GetComponent(CObject* _Owner)
{
    if (_Owner == nullptr)
        return nullptr;

    const auto& components
        = dynamic_cast<CPlayer03*>(_Owner)->GetAllComponents();

    for (const auto& component : components)
    {
        T* foundComponent = dynamic_cast<T*>(component);
        if (foundComponent)
        {
            return foundComponent;
        }
    }

    return nullptr;
}
