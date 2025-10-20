#include "pch.h"
#include "CStage02Item.h"

#include "CPlayer02.h"

CStage02Item::CStage02Item()
{
}

CStage02Item::~CStage02Item()
{
    Release();
}

void CStage02Item::Initialize()
{
    m_tInfo.vLook = { 0.f, -1.f, 0.f };
    m_tInfo.vSize = { 20.f, 20.f, 0.f };

    m_bDead = false;
}

int CStage02Item::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    Detect_Player();

    return 0;
}

void CStage02Item::Late_Update()
{
}

void CStage02Item::Render(HDC hDC)
{
    Rectangle(hDC,
        m_tInfo.vPos.x - m_tInfo.vSize.x * 0.5f,
        m_tInfo.vPos.y - m_tInfo.vSize.y * 0.5f,
        m_tInfo.vPos.x + m_tInfo.vSize.x * 0.5f,
        m_tInfo.vPos.y + m_tInfo.vSize.y * 0.5f
        );
}

void CStage02Item::Release()
{

}

void CStage02Item::Detect_Player()
{
    INFO player = *pPlayer->Get_Info();
    bool bCollision = true;

#pragma region 단위벡터 구하기
    Vec3 vUnits[4];
    Vec3 vTmp;
    int iIndex = 0;

    // 플레이어 단위 벡터
    for (int i = 0; i < 2; i++)
    {
        Vec3 vTmpUnit = pPlayer->Get_Vertices()[i + 1] - pPlayer->Get_Vertices()[i];
        D3DXVec3Normalize(&vTmpUnit, &vTmpUnit);
        vUnits[iIndex++] = vTmpUnit;
    }

    // 아이템의 단위벡터
    vTmp = { m_tInfo.vSize.x,  0.f,   0.f };
    D3DXVec3Normalize(&vTmp, &vTmp);
    vUnits[iIndex++] = vTmp;

    vTmp = { 0.f, m_tInfo.vSize.y,  0.f };
    D3DXVec3Normalize(&vTmp, &vTmp);
    vUnits[iIndex++] = vTmp;
#pragma endregion

#pragma region 투영하기

    for (int i = 0; i < 4; i++)
    {
        // 투영된 길이 구하기
        // 플레이어
        // 0번 점
        vTmp = player.vPos - pPlayer->Get_Vertices()[0];
        float fDot1 = fabsf(D3DXVec3Dot(&vUnits[i], &vTmp));

        // 1번 점
        vTmp = player.vPos - pPlayer->Get_Vertices()[1];
        float fDot2 = fabsf(D3DXVec3Dot(&vUnits[i], &vTmp));

        float fMaxDotPlayer = fmaxf(fDot1, fDot2);

        // 아이템은 고정된 투영
        vTmp = { m_tInfo.vSize.x,  0.f,   0.f };
        float fDot3 = fabsf(D3DXVec3Dot(&vUnits[i], &vTmp));

        vTmp = { 0.f, m_tInfo.vSize.y,  0.f };
        float fDot4 = fabsf(D3DXVec3Dot(&vUnits[i], &vTmp));

        float fMaxDotItem= fmaxf(fDot3, fDot4);

        float fDotRes = fMaxDotPlayer + fMaxDotItem;

        // 원점 간 벡터를 투영하기
        vTmp = m_tInfo.vPos - player.vPos;
        float fDistDot = fabsf(D3DXVec3Dot(&vTmp, &vUnits[i]));

        if (fDistDot > fDotRes)
        {
            // 충돌 안 함
            bCollision = false;
            break;
        }

    }
#pragma endregion

    if (bCollision)
    {
        Apply_ItemEffect(pPlayer);
        //cout << "충돌 : " << GetTickCount() << endl;
    }
}
