#include "pch.h"
#include "CPlayer03.h"

CPlayer03::CPlayer03()
{

}

CPlayer03::~CPlayer03()
{
    Release();
}

void CPlayer03::Initialize()
{
    m_tInfo.vPos = { 400.f, 300.f, 0.f };

    m_tInfo.vLook = { 0.f, -1.f, 0.f };

    m_fSpeed = 5.f;

    m_vPoint[0] = { m_tInfo.vPos.x - 50.f, m_tInfo.vPos.y - 50.f, 0.f };
    m_vPoint[1] = { m_tInfo.vPos.x + 50.f, m_tInfo.vPos.y - 50.f, 0.f };
    m_vPoint[2] = { m_tInfo.vPos.x + 50.f, m_tInfo.vPos.y + 50.f, 0.f };
    m_vPoint[3] = { m_tInfo.vPos.x - 50.f, m_tInfo.vPos.y + 50.f, 0.f };

    for (int i = 0; i < 4; ++i)
        m_vOriginPoint[i] = m_vPoint[i];

    m_vPosin = { m_tInfo.vPos.x, m_tInfo.vPos.y - 100.f, 0.f };

    m_vOriginPosin = m_vPosin;

}

int CPlayer03::Update()
{
    Key_Input();

    D3DXMATRIX	 matScale, matRotZ, matTrans;

    D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
    D3DXMatrixRotationZ(&matRotZ, m_fAngle);
    D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

    m_tInfo.matWorld = matScale * matRotZ * matTrans;

    for (int i = 0; i < 4; ++i)
    {
        m_vPoint[i] = m_vOriginPoint[i];
        m_vPoint[i] -= {400.f, 300.f, 0.f};

        D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
    }
    // 포신

    m_vPosin = m_vOriginPosin;
    m_vPosin -= {400.f, 300.f, 0.f};

    D3DXVec3TransformCoord(&m_vPosin, &m_vPosin, &m_tInfo.matWorld);

    return OBJ_NOEVENT;
}

void CPlayer03::Late_Update()
{
    CPlayer::Late_Update();
}

void CPlayer03::Render(HDC hDC)
{
    MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);

    for (int i = 0; i < 4; ++i)
    {
        LineTo(hDC, (int)m_vPoint[i].x, (int)m_vPoint[i].y);

        if (i > 0)
            continue;

        Ellipse(hDC,
            int(m_vPoint[i].x - 5.f),
            int(m_vPoint[i].y - 5.f),
            int(m_vPoint[i].x + 5.f),
            int(m_vPoint[i].y + 5.f));
    }

    LineTo(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y);


    // 포신 그리기

    MoveToEx(hDC, (int)m_tInfo.vPos.x, (int)m_tInfo.vPos.y, nullptr);
    LineTo(hDC, (int)m_vPosin.x, (int)m_vPosin.y);
}

void CPlayer03::Release()
{
    CPlayer::Release();
}

void CPlayer03::Key_Input()
{
    Vec3 movdDir = { 0.f,0.f,0.f };

    if (GetAsyncKeyState('A'))
    {
        movdDir = { -1.f, 0.f, 0.f };
        D3DXVec3TransformNormal(&m_tInfo.vDir, &movdDir, &m_tInfo.matWorld);
        m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
        //m_fAngle -= D3DXToRadian(3.f);
    }

    if (GetAsyncKeyState('D'))
    {
        movdDir = { 1.f, 0.f, 0.f };
        D3DXVec3TransformNormal(&m_tInfo.vDir, &movdDir, &m_tInfo.matWorld);
        m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
        //m_fAngle += D3DXToRadian(3.f);
    }

    if (GetAsyncKeyState('W'))
    {
        movdDir = { 0.f, -1.f, 0.f };
        D3DXVec3TransformNormal(&m_tInfo.vDir, &movdDir, &m_tInfo.matWorld);
        m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

    }

    if (GetAsyncKeyState('S'))
    {
        movdDir = { 0.f, 1.f, 0.f };
        D3DXVec3TransformNormal(&m_tInfo.vDir, &movdDir, &m_tInfo.matWorld);
        m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
    }
}
