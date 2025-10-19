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
};
