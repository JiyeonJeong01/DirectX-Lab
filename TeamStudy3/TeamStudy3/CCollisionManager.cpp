#include "pch.h"
#include "CCollisionManager.h"
#include "CHelper.h"
#include "CStage01Trap01.h"
#include "CStage01Trap02.h"
#include "CStage01Player.h"
#include "CStage01Goal.h"

static inline bool IsTrap(CObject* o) {
    return dynamic_cast<CStage01Trap01*>(o) != nullptr
        || dynamic_cast<CStage01Trap02*>(o) != nullptr;
}



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

				// Dst->Set_Dead();

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

bool CCollisionManager::Stage01_Check_Rect(CObject* _Dst, CObject* _Src, float* pX, float* pY)
{
    const INFO* A = _Dst->Get_Info();
    const INFO* B = _Src->Get_Info();

    float fDistanceX = fabsf(A->vPos.x - B->vPos.x);
    float fDistanceY = fabsf(A->vPos.y - B->vPos.y);

    float fRadiusX = A->vSize.x + B->vSize.x;
    float fRadiusY = A->vSize.y + B->vSize.y;

    if (fRadiusX >= fDistanceX && fRadiusY >= fDistanceY) {
        if (pX) *pX = (fRadiusX - fDistanceX);
        if (pY) *pY = (fRadiusY - fDistanceY);
        return true;
    }
    return false;
}

void CCollisionManager::Stage01_Collision_Platform(list<CObject*> _Dst, list<CObject*> _Src)
{
    for (auto& Dst : _Dst)
    {
        if (!Dst) continue;
        for (auto& Src : _Src)
        {
            if (!Src) continue;
    
            float pX = 0.f, pY = 0.f;
            if (!Stage01_Check_Rect(Dst, Src, &pX, &pY))
                continue;
    
            INFO* pA = const_cast<INFO*>(Dst->Get_Info());
            const INFO* pB = Src->Get_Info();
    
            if (pX < pY) {
                if (pA->vPos.x < pB->vPos.x) pA->vPos.x -= pX;
                else                         pA->vPos.x += pX;
    
                Dst->On_Collision(Src, { pX, 0.f, 0.f });
            }
            else {
                if (pA->vPos.y < pB->vPos.y) {
                    pA->vPos.y -= pY;
                }
                else {
                    pA->vPos.y += pY;
                }
                Dst->On_Collision(Src, { 0.f, pY, 0.f });
            }
        }
    }
}

void CCollisionManager::Stage01_Collision_Trap(list<CObject*> _Dst, list<CObject*> _Src)
{
    for (CObject* Dst : _Dst)
    {
        if (!Dst) continue;
        for (CObject* Src : _Src)
        {
            if (!Src || Src == Dst) continue;

            float pX = 0.f, pY = 0.f;
            if (!Stage01_Check_Rect(Dst, Src, &pX, &pY))
                continue;

            Vec3 pen = { 0.f, 0.f, 0.f };
            Dst->On_Collision(Src, pen);
            Src->On_Collision(Dst, pen);
        }
    }
}

void CCollisionManager::Stage01_Collision_Goal(list<CObject*> _Dst, list<CObject*> _Src)
{
    for (CObject* Dst : _Dst)
    {
        if (!Dst) continue;
        for (CObject* Src : _Src)
        {
            if (!Src || Src == Dst) continue;

            float pX = 0.f, pY = 0.f;
            if (!Stage01_Check_Rect(Dst, Src, &pX, &pY))
                continue;

            Vec3 pen = { 0.f, 0.f, 0.f };
            Dst->On_Collision(Src, pen);
            Src->On_Collision(Dst, pen);
        }
    }
}
