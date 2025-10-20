#include "pch.h"
#include "CPlayerFourth.h"
#include "CCollisionMgr04.h"

CPlayerFourth::CPlayerFourth() : isMove(true), preAngle(0.f), vecWall(nullptr), sHp(5), isInvincible(false), dwInvincibleTime(0), isDead(false)
{
    ZeroMemory(&prePos, sizeof(D3DXVECTOR3));
}

CPlayerFourth::~CPlayerFourth()
{
    Release();
}

void CPlayerFourth::Initialize()
{
    m_tInfo.vPos = { 175.f, 450.f, 0.f };
    m_tInfo.vDir = { 1.f, 0.f, 0.f };
    m_tInfo.vLook = { 0.f, -1.f, 0.f };
    m_fSpeed = 5.f;
    

    m_vPoint[0] = { m_tInfo.vPos.x - 15.f, m_tInfo.vPos.y - 15.f, 0.f };
    m_vPoint[1] = { m_tInfo.vPos.x + 15.f, m_tInfo.vPos.y - 15.f, 0.f };
    m_vPoint[2] = { m_tInfo.vPos.x + 15.f, m_tInfo.vPos.y + 15.f, 0.f };
    m_vPoint[3] = { m_tInfo.vPos.x - 15.f, m_tInfo.vPos.y + 15.f, 0.f };
    for (int i = 0; i < 4; ++i)
        m_vOriginPoint[i] = m_vPoint[i];

    prePos = m_tInfo.vPos;
}

int CPlayerFourth::Update()
{
    if (sHp <= 0)
    {
        isDead = true;
        return OBJ_DEAD;
    }
    if (isInvincible)
    {
        if (dwInvincibleTime + 2000 < GetTickCount64())
        {
            isInvincible = false;
        }
    }

    KeyInput();

    D3DXMATRIX matRotZ, matTrans;

    D3DXMATRIX matPreWorld = m_tInfo.matWorld;
    D3DXVECTOR3 prePoint[4];

    D3DXMatrixRotationZ(&matRotZ, preAngle);
    D3DXMatrixTranslation(&matTrans, prePos.x, prePos.y, prePos.z);

    matPreWorld = matRotZ * matTrans;

    for (int i = 0; i < 4; ++i)
    {
        prePoint[i] = m_vOriginPoint[i];
        prePoint[i] -= {175.f, 450.f, 0.f};
        D3DXVec3TransformCoord(&prePoint[i], &prePoint[i], &matPreWorld);
    }

    for(int i = 0; i < 3; ++i)
    {
        for (auto& pWall : *vecWall)
        {
            if (CCollisionMgr04::CollisionLineToLine(prePoint[i], prePoint[i + 1], pWall->GetStartPoint(), pWall->GetEndPoint()))
            {
                isMove = false;
                break;
            }
        }
        if (!isMove)
        {
            break;
        }
    }

    for (auto& pWall : *vecWall)
    {
        if (!isMove)
        {
            break;
        }
        if (CCollisionMgr04::CollisionLineToLine(prePoint[3], prePoint[0], pWall->GetStartPoint(), pWall->GetEndPoint()))
        {
            isMove = false;
            break;
        }
    }

    if (isMove)
    {
        m_tInfo.matWorld = matPreWorld;
        for (int i = 0; i < 4; ++i)
        {
            m_vPoint[i] = prePoint[i];
        }
        m_fAngle = preAngle;
        m_tInfo.vPos = prePos;
    }
    isMove = true;

    return OBJ_NOEVENT;
}

void CPlayerFourth::Render(HDC hDC)
{
    HPEN hRedPen = nullptr, hOldPen = nullptr;
    if(isInvincible)
    {
        hRedPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 0));

        hOldPen = (HPEN)SelectObject(hDC, hRedPen);
    }

    MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);
    for (int i = 0; i < 4; ++i)
    {
        LineTo(hDC, (int)m_vPoint[i].x, (int)m_vPoint[i].y);

        if (i > 1)
            continue;

        Ellipse(hDC,
            int(m_vPoint[i].x - 5.f),
            int(m_vPoint[i].y - 5.f),
            int(m_vPoint[i].x + 5.f),
            int(m_vPoint[i].y + 5.f));
    }
    LineTo(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y);

    if(isInvincible)
    {
        SelectObject(hDC, hOldPen);
        DeleteObject(hRedPen);
    }
}

void CPlayerFourth::Release()
{
}

void CPlayerFourth::KeyInput()
{
    if (GetAsyncKeyState('D'))
    {
        preAngle = m_fAngle;
        preAngle += D3DXToRadian(3.f);
    }
    else if (GetAsyncKeyState('A'))
    {
        preAngle = m_fAngle;
        preAngle -= D3DXToRadian(3.f);
    }

    if (GetAsyncKeyState('W'))
    {
        D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
        prePos = m_tInfo.vPos + m_tInfo.vDir * m_fSpeed;
    }
    else if (GetAsyncKeyState('S'))
    {
        D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
        prePos = m_tInfo.vPos - m_tInfo.vDir * m_fSpeed;
    }

    if (GetAsyncKeyState('H'))
    {
        sHp = 10;
    }
}
