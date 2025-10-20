#pragma once

#include "CObject.h"

template<typename T>
class CAbstractFactory
{
public:
	static CObject* Create()
	{
		CObject* pObject = new T;
		pObject->Initialize();

		return pObject;
	}

    static CObject* Create(const Vec3& _Pos)
    {
        CObject* pObject = new T;
        pObject->Initialize();
        pObject->Set_Pos(_Pos);

        return pObject;
    }
        
    static CObject* CreatePos(const Vec3& _Pos)
    {
        CObject* pObject = new T;
        pObject->Set_Pos(_Pos);
        pObject->Initialize();

        return pObject;
    }

    static CObject* CreateDir(const Vec3& _Pos, const Vec3& _Dir)
    {
        CObject* pObject = new T;
        pObject->Set_Pos(_Pos);
        pObject->Set_Dir(_Dir);
        pObject->Initialize();

        return pObject;
    }

    static CObject* CreateTarget(const Vec3& _Pos, CObject* _Target)
    {
        CObject* pObject = new T;
        pObject->Set_Pos(_Pos);
        pObject->Set_Target(_Target);
        pObject->Initialize();

        return pObject;
    }
};
