#include "pch.h"
#include "CStage02AddItem.h"

#include "CAbstractFactory.h"

#include "CPlayer02.h"
#include "COribiters.h"


void CStage02AddItem::Render(HDC hDC)
{
    CStage02Item::Render(hDC);

}

void CStage02AddItem::Apply_ItemEffect(CObject* pObject)
{
    CPlayer02* pPlayer = dynamic_cast<CPlayer02*>(pObject);

    for (int i = 0; i < 2; ++i)
        pPlayer->Add_Orbiter(static_cast<COribiters*>(CAbstractFactory<COribiters>::Create()));

    m_bDead = true;
}
