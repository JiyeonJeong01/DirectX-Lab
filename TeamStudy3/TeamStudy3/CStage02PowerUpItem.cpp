#include "pch.h"
#include "CStage02PowerUpItem.h"

#include "CPlayer02.h"

void CStage02PowerUpItem::Render(HDC hDC)
{
    CStage02Item::Render(hDC);


}


void CStage02PowerUpItem::Apply_ItemEffect(CObject* pObject)
{
    CPlayer02* pPlayer = dynamic_cast<CPlayer02*>(pObject);
    
    pPlayer->Set_OrbiterLv(pPlayer->Get_OrbiterLv() + 1);

    m_bDead = true;
}
