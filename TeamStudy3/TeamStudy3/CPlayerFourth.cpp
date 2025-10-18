#include "pch.h"
#include "CPlayerFourth.h"

CPlayerFourth::CPlayerFourth()
{
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
}

int CPlayerFourth::Update()
{
    KeyInput();

    D3DXMATRIX matRotZ, matTrans;

    D3DXMatrixRotationZ(&matRotZ, m_fAngle);
    D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

    m_tInfo.matWorld = matRotZ * matTrans;

    for (int i = 0; i < 4; ++i)
    {
        m_vPoint[i] = m_vOriginPoint[i];
        m_vPoint[i] -= {175.f, 450.f, 0.f};
        D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
    }


    return OBJ_NOEVENT;
}

void CPlayerFourth::Render(HDC hDC)
{
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
}

void CPlayerFourth::Release()
{
}

void CPlayerFourth::KeyInput()
{
    if (GetAsyncKeyState('D'))
    {
        m_fAngle += D3DXToRadian(3.f);
    }
    else if (GetAsyncKeyState('A'))
    {
        m_fAngle -= D3DXToRadian(3.f);
    }

    if (GetAsyncKeyState('W'))
    {
        D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
        m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
    }
    else if (GetAsyncKeyState('S'))
    {
        D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
        m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
    }
}
