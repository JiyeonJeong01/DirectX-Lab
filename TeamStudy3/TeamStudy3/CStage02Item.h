#pragma once
#include "CObject.h"
class CStage02Item :    public CObject
{
public :
    CStage02Item();
    ~CStage02Item() override;

public :
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

public :
    virtual void On_Collision(CObject* pObject);
    virtual void Apply_ItemEffect(CObject* pObject);

};

