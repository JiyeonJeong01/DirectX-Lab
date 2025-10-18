#pragma once

#include "CObject.h"

class CItem : public CObject
{
public:
    CItem();
    virtual ~CItem();

public:
    void Initialize() override;
    int  Update() override;
    void Late_Update() override;
    void Render(HDC _hDC) override;
    void Release() override;

public:
    virtual void OnComponentBeginOverlap(CObject* _Dst) override;
    virtual void Use_Item(CObject* _HitObject);

private:
    Vec3		m_vPoint[4];
};

