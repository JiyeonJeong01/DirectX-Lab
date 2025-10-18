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
        pObject->Set_Pos(_Pos);
        pObject->Initialize();

        return pObject;
    }

    static CObject* Create(float x, float y, float z = 0.f) 
    {
        CObject* p = new T;
        p->Set_Pos(Vec3(x, y, z));
        p->Initialize();
        return p;
    }
};
