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
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Circle(Dst, Src))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

bool CCollisionManager::Check_Circle(CObject* _Dst, CObject* _Src)
{
	float	fWidth  = fabsf(_Dst->Get_Info()->vPos.x - _Src->Get_Info()->vPos.x);
	float	fHeight = fabsf(_Dst->Get_Info()->vPos.y - _Src->Get_Info()->vPos.y);

	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (_Dst->Get_Info()->vSize.x + _Src->Get_Info()->vSize.y) * 0.5f;
	
	return fRadius >= fDiagonal;
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

void CCollisionManager::Stage01_Collision_Rect(list<CObject*> _Dst, list<CObject*> _Src)
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
