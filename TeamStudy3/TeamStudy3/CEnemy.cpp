#include "pch.h"
#include "CEnemy.h"

#include "CAbstractFactory.h"
#include "CComponent.h"
#include "CKeyManager.h"
#include "CObjectManager.h"

#include "CPlayer02.h"
#include "COribiters.h"

CEnemy::CEnemy()
{
    pPlayer = nullptr;

    iOrbitCurLv = 0;
    iOrbitTotalCnt = 0;
}

CEnemy::~CEnemy()
{
    Release();
}

void CEnemy::Initialize()
{
    m_vStartPos = { 100.f, 100.f, 0.f };
    m_tInfo.vPos = m_vStartPos;
    m_tInfo.vDir = { 0.f, -1.f, 0.f };
    m_tInfo.vSize = { 18.f, 18.f, 0.f };

    // 변환 행렬 초기화
    D3DXMatrixIdentity(&matScale);
    D3DXMatrixIdentity(&matRotZ);
    D3DXMatrixIdentity(&matTrans);
    D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

    m_fSpeed = 1.f;

    m_vPoint[0] = { m_tInfo.vPos.x - m_tInfo.vSize.x, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.f };
    m_vPoint[1] = { m_tInfo.vPos.x + m_tInfo.vSize.x, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.f };
    m_vPoint[2] = { m_tInfo.vPos.x + m_tInfo.vSize.x, m_tInfo.vPos.y + m_tInfo.vSize.y, 0.f };
    m_vPoint[3] = { m_tInfo.vPos.x - m_tInfo.vSize.x, m_tInfo.vPos.y + m_tInfo.vSize.y, 0.f };

    for (int i = 0; i < 4; i++)
    {
        m_vOriginPoint[i] = m_vPoint[i];
    }

    int iOrbitStartCnt = 6;

    float fAngleStep = 360.f / (float)iOrbitStartCnt;
    for (int i = 0; i < iOrbitStartCnt; ++i)
    {
        COribiters* pOrbiter = static_cast<COribiters*>(CAbstractFactory<COribiters>::Create());
        pOrbiter->Set_Center(this);
        pOrbiter->Set_PowerLevel(iOrbitCurLv);
        pOrbiter->Set_StartAngle(i * fAngleStep);
        pOrbiter->Set_RotationAngle(i * fAngleStep);
        pOrbiter->Set_TeamID(MONBULLET);

        m_OrbiterList.push_back(pOrbiter);
        iOrbitTotalCnt = m_OrbiterList.size();

        CObjectManager::Get_Instance()->AddObject(MONBULLET, pOrbiter);
    }
}

int CEnemy::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    Transform_LocalToWorld();

    return 0;
}

void CEnemy::Late_Update()
{
}

void CEnemy::Render(HDC hDC)
{
    MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);

    for (int i = 0; i < 4; ++i)
    {
        LineTo(hDC, m_vPoint[i].x, m_vPoint[i].y);


        if (i > 1)
            continue;

        Ellipse(hDC,
            int(m_vPoint[i].x - 5.f),
            int(m_vPoint[i].y - 5.f),
            int(m_vPoint[i].x + 5.f),
            int(m_vPoint[i].y + 5.f));
    }

    LineTo(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y);
}

void CEnemy::Release()
{
}

void CEnemy::Transform_LocalToWorld()
{
    // 이동 
    INFO player = *pPlayer->Get_Info();
    Vec3 vEnemyToPlayer = player.vPos - m_tInfo.vPos;

    // 방향 구하기
    Vec3 vDirToPlayer = {};
    D3DXVec3Normalize(&vDirToPlayer, &vEnemyToPlayer);

    // 새 위치 구하기
    m_tInfo.vPos += vDirToPlayer * m_fSpeed;

    float fRadian = acosf(vDirToPlayer.x);

    if (vEnemyToPlayer.y < 0)
        fRadian = 2 * PI - fRadian;
    fRadian += D3DXToRadian(90.f);

    // 변환 행렬 만들기
    D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
    D3DXMatrixRotationZ(&matRotZ, fRadian);
    D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

    m_tInfo.matWorld = matScale * matRotZ * matTrans;

    for (int i = 0; i < 4; i++)
    {
        Vec3 vTmp = m_vOriginPoint[i];
        vTmp -= m_vStartPos;

        D3DXVec3TransformCoord(&vTmp, &vTmp, &m_tInfo.matWorld);

        m_vPoint[i] = vTmp;
    }
}

void CEnemy::Set_OrbiterLv(int iLv)
{
    for (COribiters* pOrbit : m_OrbiterList)
    {
        pOrbit->Set_PowerLevel(iLv);
    }

    iOrbitCurLv = iLv;
}
