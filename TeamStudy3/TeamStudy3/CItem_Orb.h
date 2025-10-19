#pragma once

#include "CItem.h"

class CItem_Orb : public CItem
{
public:
    CItem_Orb();
    ~CItem_Orb() override;

public:
    void Initialize() override;
    int  Update() override;
    void Late_Update() override;
    void Render(HDC _hDC) override;
    void Release() override;

    void OnComponentBeginOverlap(CObject* _HitObject) override;
    void Use_Item(CObject* _HitObject) override;

public:


private:


};

