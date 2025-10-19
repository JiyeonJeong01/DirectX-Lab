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
}

void CMonster03_Base::Initialize()
{
    CMonster::Initialize();

    
}

int CMonster03_Base::Update()
{
    CMonster::Update();
        
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
