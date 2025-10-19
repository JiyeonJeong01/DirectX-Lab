#include "pch.h"
#include "CStage02Item.h"

#include "CPlayer02.h"
#include "CStage02PowerUpItem.h"

CStage02Item::CStage02Item()
{
}

CStage02Item::~CStage02Item()
{
    Release();
}

void CStage02Item::Initialize()
{
    m_tInfo.vSize = { 20.f, 20.f, 0.f };
}

int CStage02Item::Update()
{
    return 0;
}

void CStage02Item::Late_Update()
{
}

void CStage02Item::Render(HDC hDC)
{
}

void CStage02Item::Release()
{

}

void CStage02Item::On_Collision(CObject* pObject)
{
    if (pObject->Get_TeamID() == PLAYER)
    {
        Apply_ItemEffect(pObject);
    }
}

void CStage02PowerUpItem::Render(HDC hDC)
{

}

void CStage02Item::Apply_ItemEffect(CObject* pObject)
{
    CPlayer02* pPlayer = dynamic_cast<CPlayer02*>(pObject);
}
