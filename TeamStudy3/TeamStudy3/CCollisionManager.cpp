#include "pch.h"
#include "CCollisionManager.h"
#include "CHelper.h"

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
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Circle(Dst, Src))
			{
                bool bCheck = false;
                //bCheck |= ::IsSameOwner(Dst, Src);
                //bCheck |= ::IsSameTeam(Dst, Src);
                //bCheck |= ::IsSameOwnerTeam(Dst, Src);

                if (bCheck) return;
                if (Dst->IsDead() || Src->IsDead()) continue;

                // Dst 총알
				Dst->Set_Dead();

                //Src->TakeDamage(Dst->Get_Attack());
                Src->OnComponentBeginOverlap(Dst);
                Dst->OnComponentBeginOverlap(Src);
			}
		}
	}
}

bool CCollisionManager::Check_Circle(CObject* _Dst, CObject* _Src)
{
    const auto& d_Info = *_Dst->Get_Info();
    const auto& s_Info = *_Src->Get_Info();

    const float dx = d_Info.vPos.x - s_Info.vPos.x;
    const float dy = d_Info.vPos.y - s_Info.vPos.y;

    const float dist2 = dx * dx + dy * dy;

    const float ra = sqrtf(d_Info.vSize.x * d_Info.vSize.x + d_Info.vSize.y * d_Info.vSize.y);
    const float rb = sqrtf(s_Info.vSize.x * s_Info.vSize.x + s_Info.vSize.y * s_Info.vSize.y);
    const float rs = ra + rb;

    return dist2 <= rs * rs;
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
