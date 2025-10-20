#include "pch.h"
#include "CMonster03_Base.h"

#include "CAbstractFactory.h"
#include "CBmpManager.h"
#include "CItem.h"
#include "CItem_Rifle.h"
#include "CObjectManager.h"
#include "CScrollManager.h"

CMonster03_Base::CMonster03_Base()
{
}

CMonster03_Base::~CMonster03_Base()
{
    Release();
}

void CMonster03_Base::Initialize()
{
    CMonster::Initialize();

    // 소환 시 크기 조절
    {
        m_MonsterSpawn.SpawnScaleTime = 0.f;
        m_MonsterSpawn.SpawnScaleDuration = 1.f;
        m_MonsterSpawn.StartScale = 0.3f;
        m_MonsterSpawn.TargetScale = 1.0f;
        m_MonsterSpawn.CurrentScale = m_MonsterSpawn.StartScale;
    }
}

int CMonster03_Base::Update()
{
    CMonster::Update();

    // 점점 커지게
    if (m_MonsterState != EMonsterState::Dead)
    {
        m_MonsterSpawn.SpawnScaleTime += DELTA * 0.5f;

        float time = m_MonsterSpawn.SpawnScaleTime / m_MonsterSpawn.SpawnScaleDuration;
        if (time > 1.f) time = 1.f;

        m_MonsterSpawn.CurrentScale =
            m_MonsterSpawn.StartScale + (m_MonsterSpawn.TargetScale - m_MonsterSpawn.StartScale) * time;
    }

    return OBJ_NOEVENT;
}

void CMonster03_Base::Late_Update()
{
    CMonster::Late_Update();


}

void CMonster03_Base::Render(HDC hDC)
{
    // 부모 렌더 호출 X
}

void CMonster03_Base::Release()
{
    CMonster::Release();
}

void CMonster03_Base::OnComponentBeginOverlap(CObject* _Dst)
{
    CMonster::OnComponentBeginOverlap(_Dst);

   
}

bool CMonster03_Base::CheckToBounds()
{
    const float maxY = WINCY - m_tInfo.vSize.y;

    bool bCheck = false;
    bCheck |= m_tInfo.vPos.y > maxY;

    return bCheck;
}

void CMonster03_Base::Motion_Change()
{
    
}
