#include "pch.h"
#include "COribiters.h"

COribiters::COribiters(CObject* pObj)
{

}

COribiters::~COribiters()
{
    Release();
}

void COribiters::Initialize()
{
    fDistToCenter = 80.f;
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

    return OBJ_NOEVENT;
}

void COribiters::Late_Update()
{
}

void COribiters::Render(HDC _hDC)
{
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

    DeleteObject(hDrawRgn);
    DeleteObject(hEraseRgn);
    DeleteObject(hCrescent);
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
    fOrbitAngle += D3DXToRadian(3.f);
}

void COribiters::Set_PowerLevel(int iLv)
{
    iPowerLevel = iLv;
}
