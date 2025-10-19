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

    m_tInfo.vSize = { 48.f, 64.f, 0.f };
    m_tInfo.vPos = { 400.f, 100.f, 0.f };       
    m_fSpeed = 100.f;

    m_iHp = 10.f;

    m_vPoint[0] = Vec3(-m_tInfo.vSize.x, -m_tInfo.vSize.y, 0.f);
    m_vPoint[1] = Vec3(+m_tInfo.vSize.x, -m_tInfo.vSize.y, 0.f);
    m_vPoint[2] = Vec3(+m_tInfo.vSize.x, +m_tInfo.vSize.y, 0.f);
    m_vPoint[3] = Vec3(-m_tInfo.vSize.x, +m_tInfo.vSize.y, 0.f);

    CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Monster/GoulKingWalk.bmp", L"Monster_Walk");

    m_FrameKey = L"Monster_Walk";

    m_tFrame.iStart = 0;
    m_tFrame.iEnd = 4;
    m_tFrame.iMotion = 0;
    m_tFrame.dwSpeed = 200;
    m_tFrame.dwTime = GetTickCount64();
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

    __super::Move_Frame();

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

    //Motion_Change();
}

void CMonster03_Base::Render(HDC hDC)
{
    Vec3 center = { 0.f, 0.f, 0.f };
    D3DXVec3TransformCoord(&center, &center, &m_tInfo.matWorld);

    const int destW = (int)(m_tInfo.vSize.x * 2.f);
    const int destH = (int)(m_tInfo.vSize.y * 2.f);

    const int destX = (int)(center.x - m_tInfo.vSize.x);
    const int destY = (int)(center.y - m_tInfo.vSize.y);

    // 키값 가져오기
    HDC hMemDC = CBmpManager::Get_Instance()->Find_Img(m_FrameKey);
    if (!hMemDC) return;

    HBITMAP hbmp = (HBITMAP)GetCurrentObject(hMemDC, OBJ_BITMAP);
    BITMAP bm{};
    GetObject(hbmp, sizeof(bm), &bm);

    const int cols = 5;   // 가로 프레임 수
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

void CMonster03_Base::Motion_Change()
{
    // Walk만
    m_tFrame.iStart = 0;
    m_tFrame.iEnd = 4;
    m_tFrame.iMotion = 0;
    m_tFrame.dwSpeed = 200;
    m_tFrame.dwTime = GetTickCount64();
}
