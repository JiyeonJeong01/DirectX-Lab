#include "pch.h"
#include "CMonster03_Base.h"

#include "CAbstractFactory.h"
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

    m_tInfo.vSize = { 30.f, 30.f, 0.f };
    m_tInfo.vPos = { 400.f, 100.f, 0.f };       
    m_fSpeed = 100.f;

    m_iHp = 10.f;

    m_vPoint[0] = Vec3(-m_tInfo.vSize.x, -m_tInfo.vSize.y, 0.f);
    m_vPoint[1] = Vec3(+m_tInfo.vSize.x, -m_tInfo.vSize.y, 0.f);
    m_vPoint[2] = Vec3(+m_tInfo.vSize.x, +m_tInfo.vSize.y, 0.f);
    m_vPoint[3] = Vec3(-m_tInfo.vSize.x, +m_tInfo.vSize.y, 0.f);

}

int CMonster03_Base::Update()
{
    if (m_bDead)
    {
        // 랜덤하게 아이템 스폰으로 바꾸기
        if (m_iHp <= 0)
        {
            CObjectManager::Get_Instance()->AddObject(ITEM, CAbstractFactory<CItem_Rifle>::Create(m_tInfo.vPos));
        }

        return OBJ_DEAD;
    }

    CMonster::Update();

    m_tInfo.vPos.y += m_fSpeed * DELTA;

    D3DXMATRIX S, R, T;
    D3DXMatrixScaling(&S, 1.f, 1.f, 1.f);
    D3DXMatrixRotationZ(&R, 0.f);        
    D3DXMatrixTranslation(&T, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

    m_tInfo.matWorld = S * R * T;        

    return OBJ_NOEVENT;
}

void CMonster03_Base::Late_Update()
{
    CMonster::Late_Update();

    if (CheckToBounds())
    {
        m_bDead = true; 
    }

}

void CMonster03_Base::Render(HDC hDC)
{
    Vec3 center = { 0.f, 0.f, 0.f };

    D3DXVec3TransformCoord(&center, &center, &m_tInfo.matWorld);

    const float radiusX = m_tInfo.vSize.x;
    const float radiusY = m_tInfo.vSize.y;

    Ellipse(hDC,
        int(center.x - radiusX), int(center.y - radiusY),
        int(center.x + radiusX), int(center.y + radiusY));

}

void CMonster03_Base::Release()
{
    CMonster::Release();
}

void CMonster03_Base::OnComponentBeginOverlap(CObject* _Dst)
{
    CMonster::OnComponentBeginOverlap(_Dst);

    if (!_Dst) return;

    TakeDamage(_Dst->Get_Attack());
}
