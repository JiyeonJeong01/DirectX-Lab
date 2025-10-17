#pragma once

#include "CObject.h"
#include "CScrollManager.h"

class CPlatform : public CObject
{
public:
    CPlatform();
    virtual ~CPlatform();

public:
    void Initialize() override;
    int  Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    void On_Collision(CObject* _pColObj, Vec3 _vColSize) override;

    void Set_PlatformSize(float w, float h);
    void Update_Rect();

private:
    Vec3 m_vSize = { 0.f, 0.f, 0.f };
};

