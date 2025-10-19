#pragma once

#include "CObject.h"

class CCollisionManager
{
public:
	static void	Collision_Rect(list<CObject*> _Dst, list<CObject*> _Src);
	
	static void	Collision_Circle(list<CObject*> _Dst, list<CObject*> _Src);
	static bool	Check_Circle(CObject* _Dst, CObject* _Src);

	static void	Collision_RectEx(list<CObject*> _Dst, list<CObject*> _Src);
	static bool	Check_Rect(CObject* _Dst, CObject* _Src, float* pX, float* pY);

    static bool Stage01_Check_Rect(CObject* _Dst, CObject* _Src, float* pPenX, float* pPenY);
    static void Stage01_Collision_Platform(list<CObject*> _Dst, list<CObject*> _Src);
    static void Stage01_Collision_Trap(list<CObject*> _Dst, list<CObject*> _Src);
    static void Stage01_Collision_Goal(list<CObject*> _Dst, list<CObject*> _Src);
};

