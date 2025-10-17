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
};