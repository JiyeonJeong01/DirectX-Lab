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

    void Set_PlatformPos(Vec3 _vPlatformPos);
    void Set_PlatformSize(Vec3 _vPlatformSize);
    void Set_PlatformPoint();

private:
    Vec3 m_vPlatformPoint[4];
};

