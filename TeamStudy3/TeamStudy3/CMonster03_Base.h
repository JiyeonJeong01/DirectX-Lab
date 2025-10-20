#pragma once

#include "CMonster.h"

enum class EMonsterState
{
    Walk, Dead, End
};

struct FMonsterSpawn
{
    float SpawnScaleTime = 0.f;
    float SpawnScaleDuration = 1.f;
    float StartScale = 0.3f;
    float TargetScale = 1.0f;
    float CurrentScale = 1.0f;
};

class CMonster03_Base : public CMonster
{
public:
    CMonster03_Base();
    ~CMonster03_Base() override;

public:
    void Initialize() override;
    int  Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    virtual void OnComponentBeginOverlap(CObject* _Dst) override;
    bool CheckToBounds() override;
    
    virtual void Motion_Change();

protected:
    EMonsterState m_MonsterState = EMonsterState::Walk;
    EMonsterState m_PrevState = EMonsterState::Walk;

    bool  m_bDropped = false; 
    float m_DeadTimer = 0.f;  
    float m_DeadDuration = 1.0f;

    FMonsterSpawn m_MonsterSpawn;

};

