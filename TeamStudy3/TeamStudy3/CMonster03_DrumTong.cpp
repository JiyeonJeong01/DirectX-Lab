#include "pch.h"
#include "CMonster03_DrumTong.h"

#include "CAbstractFactory.h"
#include "CBmpManager.h"
#include "CHelper.h"
#include "CItem_Orb.h"
#include "CItem_Player.h"
#include "CItem_Rifle.h"
#include "CObjectManager.h"
#include "CPlayer03.h"

CMonster03_DrumTong::CMonster03_DrumTong()
{

}

CMonster03_DrumTong::~CMonster03_DrumTong()
{

}

void CMonster03_DrumTong::Initialize()
{
    CMonster03_Base::Initialize();

    m_tInfo.vSize = { 48.f, 64.f, 0.f };
    //m_fSpeed = 50.f;
    m_fSpeed = 15.f;

    m_iHp = 100.f;

    m_DeadDuration = 0.1f;

    m_MonsterSpawn.SpawnScaleDuration = 5.5f;
    m_MonsterSpawn.StartScale = 0.6f;
    m_MonsterSpawn.TargetScale = 1.5f;

    // 스프라이트
    {
        CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Object/DrumTong.bmp", L"DrumTong");

        m_FrameKey = L"DrumTong";

        m_MonsterState = EMonsterState::Walk;
        m_PrevState = m_MonsterState;
    }
}

int CMonster03_DrumTong::Update()
{
    //if (m_bDead)
    //    return OBJ_DEAD;

    if (m_iHp <= 0 && m_MonsterState != EMonsterState::Dead)
    {
        m_MonsterState = EMonsterState::Dead;

        m_fSpeed = 0.f;
        m_DeadTimer = 0.f;

        dynamic_cast<CPlayer03*>(CObjectManager::Get_Instance()->Get_Player()->front())->Add_Score(30);
    }

    if (m_MonsterState == EMonsterState::Dead)
    {
        m_DeadTimer += DELTA;

        if (m_DeadTimer >= m_DeadDuration)
        {
            if (!m_bDropped)
            {
                SpawnItem();

                m_bDropped = true;
            }

            return OBJ_DEAD;
        }
    }

    CMonster03_Base::Update();

    cout << "드럼통 현재 체력 : " << m_iHp << endl;

    m_tInfo.vPos.y += m_fSpeed * DELTA;

    D3DXMATRIX S, R, T;
    const float scale = m_MonsterSpawn.CurrentScale;
    D3DXMatrixScaling(&S, scale, scale, 1.f);
    D3DXMatrixRotationZ(&R, 0.f);
    D3DXMatrixTranslation(&T, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

    m_tInfo.matWorld = S * R * T;

    return OBJ_NOEVENT;
}

void CMonster03_DrumTong::Late_Update()
{
    CMonster03_Base::Late_Update();

    if (CheckToBounds())
    {
        m_bDead = true;
    }
}

void CMonster03_DrumTong::Render(HDC hDC)
{
    CMonster03_Base::Render(hDC);

    Vec3 center = { 0.f, 0.f, 0.f };
    D3DXVec3TransformCoord(&center, &center, &m_tInfo.matWorld);

    const float scale = m_MonsterSpawn.CurrentScale;
    const int destW = (int)(m_tInfo.vSize.x * 2.f * scale);
    const int destH = (int)(m_tInfo.vSize.y * 2.f * scale);

    const int destX = int(center.x - destW * 0.5f);
    const int destY = int(center.y - destH * 0.5f);

    HDC hMemDC = CBmpManager::Get_Instance()->Find_Img(m_FrameKey);
    if (!hMemDC) return;

    HBITMAP hbmp = (HBITMAP)GetCurrentObject(hMemDC, OBJ_BITMAP);
    BITMAP bm{}; GetObject(hbmp, sizeof(bm), &bm);

    const int srcX = 0;
    const int srcY = 0;
    const int srcW = bm.bmWidth;
    const int srcH = bm.bmHeight;

    SetStretchBltMode(hDC, HALFTONE);

    GdiTransparentBlt(hDC,
        destX, destY, destW, destH,
        hMemDC,
        srcX, srcY, srcW, srcH,
        RGB(255, 255, 255));

}

void CMonster03_DrumTong::Release()
{
    CMonster03_Base::Release();

}

void CMonster03_DrumTong::OnComponentBeginOverlap(CObject* _Dst)
{
    CMonster03_Base::OnComponentBeginOverlap(_Dst);

    if (!_Dst) return;

}

void CMonster03_DrumTong::SpawnItem()
{
    int randomValue = rand() % 3;

    if (randomValue == 0)
    {
        CObjectManager::Get_Instance()->AddObject(
            ITEM, CAbstractFactory<CItem_Orb>::Create(m_tInfo.vPos));
    }

    else if (randomValue == 1)
    {
        CObjectManager::Get_Instance()->AddObject(
            ITEM, CAbstractFactory<CItem_Player>::Create(m_tInfo.vPos));
        //ITEM, CAbstractFactory<CItem_Player>::Create(m_tInfo.vPos));
    }

    else if (randomValue == 2)
    {
        CObjectManager::Get_Instance()->AddObject(
            ITEM, CAbstractFactory<CItem_Rifle>::Create(m_tInfo.vPos));
        //ITEM, CAbstractFactory<CItem_Player>::Create(m_tInfo.vPos));
    }

}
