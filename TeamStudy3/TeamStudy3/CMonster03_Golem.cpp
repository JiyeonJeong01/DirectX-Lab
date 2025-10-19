#include "pch.h"
#include "CMonster03_Golem.h"

#include "CAbstractFactory.h"
#include "CBmpManager.h"
#include "CItem_Rifle.h"
#include "CObjectManager.h"
#include "CPlayer03.h"

CMonster03_Golem::CMonster03_Golem()
{

}

CMonster03_Golem::~CMonster03_Golem()
{

}

void CMonster03_Golem::Initialize()
{
    CMonster03_Base::Initialize();

    m_tInfo.vSize = { 48.f, 64.f, 0.f };
    m_fSpeed = 50.f;

    m_iHp = 15.f;

    // 스프라이트
    {
        CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Monster/GolemWalk.bmp", L"Golem_Walk");
        CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Monster/GolemDeath.bmp", L"Golem_Dead");

        m_FrameKey = L"Golem_Walk";

        m_PrevState = m_MonsterState;

        m_tFrame.iStart = 0;
        m_tFrame.iEnd = 5;
        m_tFrame.iMotion = 0;
        m_tFrame.dwSpeed = 200;
        m_tFrame.dwTime = GetTickCount64();
    }
}

int CMonster03_Golem::Update()
{
    if (m_iHp <= 0 && m_MonsterState != EMonsterState::Dead)
    {
        m_MonsterState = EMonsterState::Dead;
        m_fSpeed = 0.f;
        m_DeadTimer = 0.f;

        Motion_Change();

        dynamic_cast<CPlayer03*>(CObjectManager::Get_Instance()->Get_Player()->front())->Add_Score(3);
    }

    if (m_MonsterState == EMonsterState::Dead)
    {
        __super::Move_Frame();
        m_DeadTimer += DELTA;

        if (m_DeadTimer >= m_DeadDuration)
        {
            if (!m_bDropped)
            {
                m_bDropped = true;
            }
            return OBJ_DEAD;
        }
    }

    CMonster03_Base::Update();
    __super::Move_Frame();

    m_tInfo.vPos.y += m_fSpeed * DELTA;

    D3DXMATRIX S, R, T;
    const float scale = m_MonsterSpawn.CurrentScale;
    D3DXMatrixScaling(&S, scale, scale, 0.f);
    D3DXMatrixRotationZ(&R, 0.f);
    D3DXMatrixTranslation(&T, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

    m_tInfo.matWorld = S * R * T;

    return OBJ_NOEVENT;
}

void CMonster03_Golem::Late_Update()
{
    CMonster03_Base::Late_Update();

    if (CheckToBounds())
    {
        m_bDead = true;
    }
}

void CMonster03_Golem::Render(HDC hDC)
{
    CMonster03_Base::Render(hDC);

    Vec3 center = { 0.f, 0.f, 0.f };
    D3DXVec3TransformCoord(&center, &center, &m_tInfo.matWorld);

    const float scale = m_MonsterSpawn.CurrentScale;
    const int destW = (int)(m_tInfo.vSize.x * 2.f * scale);
    const int destH = (int)(m_tInfo.vSize.y * 2.f * scale);

    const int destX = (int)(center.x - m_tInfo.vSize.x);
    const int destY = (int)(center.y - m_tInfo.vSize.y);

    // 키값 가져오기
    HDC hMemDC = CBmpManager::Get_Instance()->Find_Img(m_FrameKey);
    if (!hMemDC) return;

    HBITMAP hbmp = (HBITMAP)GetCurrentObject(hMemDC, OBJ_BITMAP);
    BITMAP bm{};
    GetObject(hbmp, sizeof(bm), &bm);

    const int cols = m_tFrame.iEnd + 1;   // 가로 프레임 수
    const int rows = 1;   // 세로 프레임 수

    const int frameW = bm.bmWidth / cols;
    const int frameH = bm.bmHeight / rows;

    const int srcX = m_tFrame.iStart * frameW;
    const int srcY = m_tFrame.iMotion * frameH;
    const int srcW = frameW;
    const int srcH = frameH;

    // 사이즈 조절 용 Stretch
    SetStretchBltMode(hDC, HALFTONE);

    GdiTransparentBlt(hDC,
        destX, destY, destW, destH,
        hMemDC,
        srcX, srcY, srcW, srcH,
        RGB(255, 255, 255));
}

void CMonster03_Golem::Release()
{
    CMonster03_Base::Release();
}

void CMonster03_Golem::OnComponentBeginOverlap(CObject* _Dst)
{
    CMonster03_Base::OnComponentBeginOverlap(_Dst);

    if (!_Dst) return;

    TakeDamage(_Dst->Get_Attack());
}

void CMonster03_Golem::Motion_Change()
{
    CMonster03_Base::Motion_Change();

    // Walk만
    switch (m_MonsterState)
    {
    case EMonsterState::Dead:
        m_FrameKey = L"Golem_Dead"; 

        m_tFrame.iStart = 0;
        m_tFrame.iEnd = 5;
        m_tFrame.iMotion = 0;
        m_tFrame.dwSpeed = 100;
        m_tFrame.dwTime = GetTickCount64();
        break;
    }
}
