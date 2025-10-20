#include "pch.h"
#include "COribiters.h"

#include "CEnemy.h"
#include "CPlayer02.h"
#include "CObjectManager.h"

COribiters::COribiters(CObject* pObj)
{

}

COribiters::~COribiters()
{
    Release();
}

void COribiters::Initialize()
{
    fDistToCenter = 70.f;
    fCenterToCenter = 7.f;

    m_vStartPos = { 0.f, -fDistToCenter, 0.f };
    m_vLocalDraw = { fDistToCenter, 0.f, 0.f };
    m_vDrawCenter = m_vLocalDraw;

    m_vLocalErase = { fCenterToCenter, 0.f, 0.f };
    m_vEraseCenter = { m_vDrawCenter.x + fCenterToCenter, m_vDrawCenter.y, 0.f };

    fOrbitAngle = 0.f;

    iPowerLevel = 0;

    m_tInfo.vLook = Vec3(0.f, -1.f, 0.f);
    m_tInfo.vSize = Vec3(30.f, 30.f, 0.f);

    m_fSpeed = 2.f;
}

int COribiters::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    Orbit_Center();
    Transform_LocalToWorld();

    Detect_Opponent();

    return OBJ_NOEVENT;
}

void COribiters::Late_Update()
{
}

void COribiters::Render(HDC _hDC)
{
#pragma region 초승달 만들기
    HRGN hDrawRgn = CreateEllipticRgn(
        m_vDrawCenter.x - m_tInfo.vSize.x * 0.5f,
        m_vDrawCenter.y - m_tInfo.vSize.y * 0.5f,
        m_vDrawCenter.x + m_tInfo.vSize.x * 0.5f,
        m_vDrawCenter.y + m_tInfo.vSize.y * 0.5f
    );

    HRGN hEraseRgn = CreateEllipticRgn(
        m_vEraseCenter.x - m_tInfo.vSize.x * 0.5f,
        m_vEraseCenter.y - m_tInfo.vSize.y * 0.5f,
        m_vEraseCenter.x + m_tInfo.vSize.x * 0.5f,
        m_vEraseCenter.y + m_tInfo.vSize.y * 0.5f
    );
    HRGN hCrescent = CreateRectRgn(0, 0, 0, 0);
    CombineRgn(hCrescent, hDrawRgn, hEraseRgn, RGN_DIFF);
#pragma endregion

#pragma region 색 지정하기
    HBRUSH hFillColor = NULL;

    switch (iPowerLevel)
    {
    case 0:
        hFillColor = CreateSolidBrush(RGB(255, 0, 0)); // 빨강
        break;
    case 1:
        hFillColor = CreateSolidBrush(RGB(255, 128, 0)); // 주황
        break;
    case 2:
        hFillColor = CreateSolidBrush(RGB(255, 255, 0)); // 노랑
        break;
    case 3:
        hFillColor = CreateSolidBrush(RGB(0, 255, 0)); // 초록
        break;
    case 4:
        hFillColor = CreateSolidBrush(RGB(0, 0, 255)); // 파랑
        break;
    case 5:
        hFillColor = CreateSolidBrush(RGB(0, 0, 128)); // 남색
        break;
    case 6:
        hFillColor = CreateSolidBrush(RGB(128, 0, 255)); // 보라
        break;
    default:
        hFillColor = CreateSolidBrush(RGB(128, 0, 255)); // 기본: 흰색
        break;
    }

    FillRgn(_hDC, hCrescent, hFillColor);
#pragma endregion

#pragma region 해제
    DeleteObject(hFillColor);

    DeleteObject(hDrawRgn);
    DeleteObject(hEraseRgn);
    DeleteObject(hCrescent);
#pragma endregion

}

void COribiters::Release()
{
}

void COribiters::Transform_LocalToWorld()
{
    D3DXMatrixIdentity(&m_tInfo.matWorld);

    // 로컬 좌표 변환
    D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
    D3DXMatrixRotationZ(&matRotZ, /*m_fAngle*/0);
    D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

    Vec3 vTmp = m_vLocalDraw;

    m_tInfo.matWorld = matScale * matRotZ * matTrans;

    // 부모 좌표 변환
    Vec3 vParentPos = pCenter->Get_Info()->vPos;
    D3DXMATRIX matParentTrans;
    D3DXMatrixTranslation(&matParentTrans, vParentPos.x - m_vLocalDraw.x, vParentPos.y - m_vLocalDraw.y, 0.f);

    // 월드 변환
    D3DXVec3TransformCoord(&vTmp, &vTmp, &m_tInfo.matWorld);
    D3DXVec3TransformCoord(&vTmp, &vTmp, &matParentTrans);

    m_vDrawCenter = vTmp;

    // 자전 
    D3DXMATRIX matEraseWorld, matEraseRotZ, matEraseTrans;
    D3DXMatrixIdentity(&matEraseWorld);

    D3DXMatrixRotationZ(&matEraseRotZ, fOrbitAngle);
    D3DXMatrixTranslation(&matEraseTrans, m_vDrawCenter.x, m_vDrawCenter.y, 0.f);

    matEraseWorld = matEraseRotZ * matEraseTrans;

    vTmp = m_vLocalErase;

    D3DXVec3TransformCoord(&vTmp, &vTmp, &matEraseWorld);

    m_vEraseCenter = vTmp;
}

void COribiters::Orbit_Center()
{
    m_tInfo.vDir.x = m_tInfo.vLook.x * cosf(m_fAngle) - m_tInfo.vLook.y * sinf(m_fAngle);
    m_tInfo.vDir.y = m_tInfo.vLook.x * sinf(m_fAngle) + m_tInfo.vLook.y * cosf(m_fAngle);

    D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

    m_tInfo.vPos = m_tInfo.vDir * fDistToCenter;

    m_fAngle += D3DXToRadian(1.5f);

    // 자전
    if (m_TeamID == BULLET)
        fOrbitAngle += D3DXToRadian(3.f);
    else
        fOrbitAngle = 0;
}

void COribiters::Detect_Opponent()
{
#pragma region Player Orbiter
    if (m_TeamID == BULLET)
    {
        // 플레이어의 회전체인 경우
        Detect_EnemySide();
    }
#pragma endregion
#pragma region Enemy Orbiter
    else if (m_TeamID == MONBULLET)
    {
        // 적의 회전체인 경우
        Detect_PlayerSide();
    }
#pragma endregion
}

void COribiters::Detect_PlayerSide()
{
    // 적이 플레이어와의 충돌 확인
    CPlayer02* pPlayer = static_cast<CPlayer02*>(CObjectManager::Get_Instance()->Get_Player()->front());

    // 적 회전체(this) <-> 플레이어
    INFO player = *pPlayer->Get_Info();
    bool bCollision = true;

#pragma region 투영할 단위 벡터 구하기
    Vec3 vUnits[4];
    Vec3 vTmp;
    int iIndex = 0;

    // 플레이어의 단위 벡터
    for (int i = 0; i < 2; i++)
    {
        Vec3 vTmpUnit = pPlayer->Get_Vertices()[i + 1] - pPlayer->Get_Vertices()[i];
        D3DXVec3Normalize(&vTmpUnit, &vTmpUnit);
        vUnits[iIndex++] = vTmpUnit;
    }

    // 회전체의 단위 벡터
    vTmp = { m_tInfo.vSize.x, 0.f, 0.f };
    D3DXVec3Normalize(&vTmp, &vTmp);
    vUnits[iIndex++] = vTmp;

    vTmp = { 0.f, m_tInfo.vSize.y, 0.f };
    D3DXVec3Normalize(&vTmp, &vTmp);
    vUnits[iIndex++] = vTmp;
#pragma endregion

#pragma region 단위 벡터에 투영하기
    for (int i = 0; i < 4; i++)
    {
        // 투영된 길이 구하기
        // 적
        // 0번 점
        vTmp = player.vPos - pPlayer->Get_Vertices()[0];
        float fDot1 = fabsf(D3DXVec3Dot(&vUnits[i], &vTmp));

        // 1번 점
        vTmp = player.vPos - pPlayer->Get_Vertices()[0];
        float fDot2 = fabsf(D3DXVec3Dot(&vUnits[i], &vTmp));

        float fMaxDotEnemy = fmaxf(fDot1, fDot2);

        // 회전체의 콜라이더는 고정된 투영
        vTmp = { m_tInfo.vSize.x,  0.f,   0.f };
        float fDot3 = fabsf(D3DXVec3Dot(&vUnits[i], &vTmp));

        vTmp = { 0.f, m_tInfo.vSize.y,  0.f };
        float fDot4 = fabsf(D3DXVec3Dot(&vUnits[i], &vTmp));

        float fMaxDotItem = fmaxf(fDot3, fDot4);

        float fDotRes = fMaxDotEnemy + fMaxDotItem;

        // 원점 간 벡터를 투영하기
        vTmp = m_vDrawCenter - player.vPos;
        float fDistDot = fabsf(D3DXVec3Dot(&vTmp, &vUnits[i]));

        if (fDistDot > fDotRes)
        {
            bCollision = false;
            break;
        }
    }

#pragma endregion

#pragma region 적 회전체 <-> 플레이어 몸체 충돌
    if (bCollision)
    {
        if (pPlayer->Get_Hp() > 2)
        {
            pPlayer->Set_Hp(pPlayer->Get_Hp()-1);
        }
        m_bDead = true;
    }
#pragma endregion
}

void COribiters::Detect_EnemySide()
{
    // 플레이어가 적과의 충돌 확인할 때 사용
    for (CObject* pObj : *CObjectManager::Get_Instance()->Get_MonsterList())
    {
        CEnemy* pEnemy = dynamic_cast<CEnemy*>(pObj);

        // 플레이어 회전체(this) <-> 적
        INFO enemy = *pEnemy->Get_Info();
        bool bCollision = true;

#pragma region 투영할 단위 벡터 구하기
        Vec3 vUnits[4];
        Vec3 vTmp;
        int iIndex = 0;

        // 적의 단위 벡터
        for (int i = 0; i < 2; i++)
        {
            Vec3 vTmpUnit = pEnemy->Get_Vertices()[i + 1] - pEnemy->Get_Vertices()[i];
            D3DXVec3Normalize(&vTmpUnit, &vTmpUnit);
            vUnits[iIndex++] = vTmpUnit;
        }

        // 회전체의 단위 벡터
        vTmp = { m_tInfo.vSize.x, 0.f, 0.f };
        D3DXVec3Normalize(&vTmp, &vTmp);
        vUnits[iIndex++] = vTmp;

        vTmp = { 0.f, m_tInfo.vSize.y, 0.f };
        D3DXVec3Normalize(&vTmp, &vTmp);
        vUnits[iIndex++] = vTmp;
#pragma endregion

#pragma region 단위 벡터에 투영하기
        for (int i = 0; i < 4; i++)
        {
            // 투영된 길이 구하기
            // 적
            // 0번 점
            vTmp = enemy.vPos - pEnemy->Get_Vertices()[0];
            float fDot1 = fabsf(D3DXVec3Dot(&vUnits[i], &vTmp));

            // 1번 점
            vTmp = enemy.vPos - pEnemy->Get_Vertices()[0];
            float fDot2 = fabsf(D3DXVec3Dot(&vUnits[i], &vTmp));

            float fMaxDotEnemy = fmaxf(fDot1, fDot2);

            // 회전체의 콜라이더는 고정된 투영
            vTmp = { m_tInfo.vSize.x,  0.f,   0.f };
            float fDot3 = fabsf(D3DXVec3Dot(&vUnits[i], &vTmp));

            vTmp = { 0.f, m_tInfo.vSize.y,  0.f };
            float fDot4 = fabsf(D3DXVec3Dot(&vUnits[i], &vTmp));

            float fMaxDotItem = fmaxf(fDot3, fDot4);

            float fDotRes = fMaxDotEnemy + fMaxDotItem;

            // 원점 간 벡터를 투영하기
            vTmp = m_vDrawCenter - enemy.vPos;
            float fDistDot = fabsf(D3DXVec3Dot(&vTmp, &vUnits[i]));

            if (fDistDot > fDotRes)
            {
                bCollision = false;
                break;
            }
        }

#pragma endregion

#pragma region 플레이어 회전체 <-> 적 몸체 충돌
        if (bCollision)
        {
            pEnemy->Set_Hp(0);
            pEnemy->Set_Dead();
            for_each(pEnemy->Get_OrbiterList()->begin(), pEnemy->Get_OrbiterList()->end(), [&](COribiters* pOrbiter)->void {
                pOrbiter->Set_Dead();
                });
        }

#pragma endregion

        // 플레이어 회전체(this) <-> 적의 회전체
        list<COribiters*> pOrbitList = *pEnemy->Get_OrbiterList();
        for (COribiters* pOrbiter : pOrbitList)
        {
            INFO enemy = *pOrbiter->Get_Info();
            // 거리 먼저 확인 후 일정 범위 안에 들어오면
            Vec3 vDiff = m_vDrawCenter - pOrbiter->Get_DrawPos();

            // 충돌 확인하기 - AABA
            float fDist = D3DXVec3Length(&vDiff) - 2.f; // epsilon
            float fRadiusSum = (m_tInfo.vSize.x + enemy.vSize.x) * 0.5f;

            if (fDist > fRadiusSum)
            {
                // 충돌 아님
                bCollision = false;
                continue;
            }
            else
            {
                // 충돌
                bCollision = true;
                if (iPowerLevel > pOrbiter->Get_PowerLevel())
                {
                    pOrbiter->Set_Dead();
                    pEnemy->Get_OrbiterList()->remove(pOrbiter);
                }
                else if (iPowerLevel < pOrbiter->Get_PowerLevel())
                {
                    m_bDead = true;
                    dynamic_cast<CPlayer02*>(CObjectManager::Get_Instance()->Get_Player()->front())
                        ->Get_OrbiterList()->remove(this);
                }
                else
                {
                    //pOrbiter->Set_Dead();
                    //m_bDead = true;
                    //dynamic_cast<CPlayer02*>(CObjectManager::Get_Instance()->Get_Player()->front())
                    //    ->Set_Pos()
                }
            }
        }
    }
}

void COribiters::Set_PowerLevel(int iLv)
{
    iPowerLevel = iLv;
}

int COribiters::Get_PowerLevel() {
    return iPowerLevel;
}
