#include "pch.h"
#include "CCollisionManager.h"

void CCollisionManager::Collision_Rect(list<CObject*> _Dst, list<CObject*> _Src)
{
	/*RECT	rcCol{};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rcCol, Dst->Get_Rect(), Src->Get_Rect()))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}*/

}

void CCollisionManager::Collision_Circle(list<CObject*> _Dst, list<CObject*> _Src)
{
	/*for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Circle(Dst, Src))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}*/
}

bool CCollisionManager::Check_Circle(CObject* _Dst, CObject* _Src)
{
	//float	fWidth  = fabsf(_Dst->Get_Info()->fX - _Src->Get_Info()->fX);
	//float	fHeight = fabsf(_Dst->Get_Info()->fY - _Src->Get_Info()->fY);

	//float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	//float	fRadius = (_Dst->Get_Info()->fCX + _Src->Get_Info()->fCX) * 0.5f;
	//
	//return fRadius >= fDiagonal;

    return false;
}

void CCollisionManager::Collision_RectEx(list<CObject*> _Dst, list<CObject*> _Src)
{
	//float fX(0.f), fY(0.f);

	//for (auto& Dst : _Dst)
	//{
	//	for (auto& Src : _Src)
	//	{
	//		if (Check_Rect(Dst, Src, &fX, &fY))
	//		{
	//			if (fX > fY)	// 상하 충돌
	//			{
	//				if (Dst->Get_Info()->fY < Src->Get_Info()->fY) // 상 충돌
	//				{
	//					Dst->Set_PosY(-fY);
	//				}
	//				else  // 하충돌
	//				{
	//					Dst->Set_PosY(fY);
	//				}

	//			}
	//			else			// 좌우 충돌
	//			{
	//				if (Dst->Get_Info()->fX < Src->Get_Info()->fX) // 좌 충돌
	//				{
	//					Dst->Set_PosX(-fX);
	//				}
	//				else  // 우 충돌
	//				{
	//					Dst->Set_PosX(fX);
	//				}
	//			}
	//		}
	//	}
	//}
}

bool CCollisionManager::Check_Rect(CObject* _Dst, CObject* _Src, float* pX, float* pY)
{
	/*float	fDistanceX = abs(_Dst->Get_Info()->fX - _Src->Get_Info()->fX);
	float	fDistanceY = abs(_Dst->Get_Info()->fY - _Src->Get_Info()->fY);

	float	fRadiusX = (_Dst->Get_Info()->fCX + _Src->Get_Info()->fCX) * 0.5f;
	float	fRadiusY = (_Dst->Get_Info()->fCY + _Src->Get_Info()->fCY) * 0.5f;

	if ((fRadiusX >= fDistanceX) && (fRadiusY >= fDistanceY))
	{
		*pX = fRadiusX - fDistanceX;
		*pY = fRadiusY - fDistanceY;

		return true;
	}


	return false;*/

    return false;
}
