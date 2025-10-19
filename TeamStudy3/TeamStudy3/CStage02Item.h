#pragma once
#include "CObject.h"

class CPlayer02;

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
    virtual void Detect_Player();
    virtual void Apply_ItemEffect(CObject* pObject) {};

public :
    void Set_Player(CPlayer02* pPlayer) { this->pPlayer = pPlayer; }

private:
    CPlayer02* pPlayer;
};

