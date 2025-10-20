#include "pch.h"
#include "CPlayer02.h"

#include "CAbstractFactory.h"
#include "CComponent.h"
#include "CKeyManager.h"
#include "CObjectManager.h"

#include "COribiters.h"

CPlayer02::CPlayer02()
{
    fVerticalInput = 0.f;
    fHorizontalIput = 0.f;
    m_vStartPos = {0.f, 0.f, 0.f};

    bTransProgress = false;
    bTransDone = false;
}

CPlayer02::~CPlayer02()
{
    Release();
}

void CPlayer02::Initialize()
{
    m_vStartPos = { 400.f, 300.f, 0.f };
    m_tInfo.vPos = m_vStartPos;
    m_tInfo.vLook = { 0.f, - 1.f, 0.f };
    m_tInfo.vSize = { 25.f, 25.f, 0.f };

    // 변환 행렬 초기화
    D3DXMatrixIdentity(&matScale);
    D3DXMatrixIdentity(&matRotZ);
    D3DXMatrixIdentity(&matTrans);
    D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

    m_fSpeed = 3.f;

    m_iHp = 10;

    m_vPoint[0] = { m_tInfo.vPos.x - m_tInfo.vSize.x, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.f };
    m_vPoint[1] = { m_tInfo.vPos.x + m_tInfo.vSize.x, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.f };
    m_vPoint[2] = { m_tInfo.vPos.x + m_tInfo.vSize.x, m_tInfo.vPos.y + m_tInfo.vSize.y, 0.f };
    m_vPoint[3] = { m_tInfo.vPos.x - m_tInfo.vSize.x, m_tInfo.vPos.y + m_tInfo.vSize.y, 0.f };

    for (int i = 0; i < 4; i++)
    {
        m_vOriginPoint[i] = m_vPoint[i];
    }

    iOrbitCurLv = 0;

    int iOrbitStartCnt = 3;

    // 무기 생성
    float fAngleStep = 360.f / (float)iOrbitTotalCnt;
    for (int i = 0; i < iOrbitStartCnt; ++i)
    {
        COribiters* pOrbiter = static_cast<COribiters*>(CAbstractFactory<COribiters>::Create());
        Add_Orbiter(pOrbiter);
    }

    bKnockback = true;
}

int CPlayer02::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    Handle_Input();
    Apply_InputToPlayer();
    Transform_LocalToWorld();

    return 0;
}

void CPlayer02::Late_Update()
{

}

void CPlayer02::Render(HDC hDC)
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

#pragma region Print HUID
    wchar_t szTmp[64];
    wsprintf(szTmp, L"Player HP: %d", m_iHp);

    HFONT hFont = CreateFont(
        30, 0, 0, 0, FW_BOLD,
        FALSE, FALSE, FALSE,
        HANGEUL_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY,
        VARIABLE_PITCH | FF_SWISS,
        L"Segoe UI"
    );

    HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

    SetTextColor(hDC, RGB(0, 0, 0));
    SetBkMode(hDC, TRANSPARENT);

    SIZE textSize;
    GetTextExtentPoint32(hDC, szTmp, lstrlen(szTmp), &textSize);

    int x = 20;
    int y = 20;
    TextOut(hDC, x, y, szTmp, lstrlen(szTmp));

    SelectObject(hDC, hOldFont);
    DeleteObject(hFont);
#pragma endregion
}

void CPlayer02::Release()
{
}

void CPlayer02::AddComponent(CComponent* _Component)
{
}


void CPlayer02::Handle_Input()
{
    // 값 초기화
    fVerticalInput = fHorizontalIput = 0.f;
    pCursorPos = {};
    bLeftClicked = false;

    // 키 입력

    // 마우스 입력
    GetCursorPos(&pCursorPos);
    ScreenToClient(g_hWnd, &pCursorPos);
    bLeftClicked = (GetAsyncKeyState(VK_LBUTTON));
}

void CPlayer02::Apply_InputToPlayer()
{
    // 값 초기화



    // 넉백
    if (bKnockback)
    {
        if (dwKnockbackElpasedTime + 300 < GetTickCount())
        {
            bKnockback = false;
        }

    }

    // 바라보는 방향 구하기
    Vec3 vCursorPos = { (float)pCursorPos.x, (float)pCursorPos.y, 0.f };
    Vec3 vDiff = vCursorPos - m_tInfo.vPos;

    float fRadPlayerToCursor = acosf(vDiff.x / D3DXVec3Length(&vDiff));

    if (vDiff.y < 0)
        fRadPlayerToCursor = 2 * PI - fRadPlayerToCursor;

    fRadPlayerToCursor += D3DXToRadian(90.f);

    D3DXMatrixRotationZ(&matRotZ, (fRadPlayerToCursor));

    // 이동 변환 행렬
    // 이동 시작 시 설정
    if (bLeftClicked)
    {
        bTransProgress = true;
        bTransDone = false;

        vTransPos = { (float)pCursorPos.x, (float)pCursorPos.y, 0.f };
    }

    // 이동 중 
    if (bTransProgress && !bTransDone)
    {
        Vec3 vNromDir{};
        Vec3 vTransDiff = vTransPos - m_tInfo.vPos;
        D3DXVec3Normalize(&vNromDir, &vTransDiff);

        m_tInfo.vPos += vNromDir * m_fSpeed;

        D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

        if (D3DXVec3Length(&vTransDiff) < fEpsilone)
        {
            bTransDone = true;
            bTransProgress = false;
        }
    }


}

void CPlayer02::Transform_LocalToWorld()
{
    // 행렬 초기화
    D3DXMatrixIdentity(&m_tInfo.matWorld);

    m_tInfo.matWorld = matScale * matRotZ * matTrans;

    for (int i = 0; i < 4; i++)
    {
        m_vPoint[i] = m_vOriginPoint[i];
        m_vPoint[i] -= m_vStartPos;

        D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
    }
}

void CPlayer02::Add_Orbiter(COribiters* pOribiter)
{
    if (pOribiter == nullptr) return;

    m_OrbiterList.push_back(pOribiter);
    iOrbitTotalCnt = m_OrbiterList.size();

    pOribiter->Set_Center(this);
    pOribiter->Set_PowerLevel(iOrbitCurLv);

    CObjectManager::Get_Instance()->AddObject(  BULLET, pOribiter  );

    float fAngleStep = 360.f / (float)iOrbitTotalCnt;
    int iIdx = 0;
    for (COribiters* pOrbit : m_OrbiterList)
    {
        pOrbit->Set_StartAngle(iIdx * fAngleStep);
        pOrbit->Set_RotationAngle(iIdx++ * fAngleStep);
        pOrbit->Set_TeamID(BULLET);
    }
}

void CPlayer02::Remove_Orbiter(COribiters* pOrbiter)
{
    list<COribiters*>::iterator it = find_if(m_OrbiterList.begin(), m_OrbiterList.end(), [&](COribiters* pTarget)-> bool
        {
            return pTarget == pOrbiter;
        });

    m_OrbiterList.erase(it); // 삭제

    iOrbitTotalCnt = m_OrbiterList.size();

    float fAngleStep = 360.f / (float)iOrbitTotalCnt;
    int iIdx = 0;
    for (COribiters* pOrbit : m_OrbiterList)
    {
        pOrbit->Set_StartAngle(iIdx++ * fAngleStep);
    }
}

void CPlayer02::Set_OrbiterLv(int iLv)
{
    for (COribiters* pOrbit : m_OrbiterList)
    {
        pOrbit->Set_PowerLevel(iLv);
    }

    iOrbitCurLv = iLv;
}

void CPlayer02::Progress_Knockback()
{

}
