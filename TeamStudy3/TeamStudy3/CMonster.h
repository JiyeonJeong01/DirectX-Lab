#pragma once

#include "CObject.h"
#include "CPlayer.h"

class CMonster : public CObject
{
public:
    CMonster();
    virtual ~CMonster();

public:
    void    Set_Player(CObject* pPlayer) { m_pPlayer = pPlayer; }

public:
    void Initialize() override;
    int  Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    

private:
    CObject* m_pPlayer;
};

