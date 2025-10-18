#pragma once

#include "CObject.h"
#include "CPlayer03.h"

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
