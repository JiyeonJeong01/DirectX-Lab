#pragma once
#include "CStage02Item.h"
class CStage02PowerUpItem :   public CStage02Item
{
public :
    void Render(HDC hDC) override;
public :
    void Apply_ItemEffect(CObject* pObject);


};

