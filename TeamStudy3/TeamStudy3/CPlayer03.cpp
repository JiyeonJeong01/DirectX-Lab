#include "pch.h"
#include "CPlayer03.h"

#include "CAbstractFactory.h"
#include "CBmpManager.h"
#include "CBullet_Base.h"
#include "CComponent.h"
#include "CKeyManager.h"
#include "CObjectManager.h"
#include "CHelper.h"
#include "CWeaponComponent.h"

CPlayer03::CPlayer03()
{
    m_Weapon = CreateComponent<CWeaponComponent>(this);

}

CPlayer03::~CPlayer03()
{
    Release();
}

void CPlayer03::Initialize()
{
    for (auto component : m_Components)
        component->BeginPlay();

    m_Weapon->Equip_Weapon(EWeaponType::Base);


    m_tInfo.vPos = { 400.f, 300.f, 0.f };
    m_tInfo.vLook = { 0.f, -1.f, 0.f };
    m_tInfo.vSize = { 30.f, 80.f, 0.f};

    m_fSpeed = 5.f;

    m_vPoint[0] = { m_tInfo.vPos.x - m_tInfo.vSize.x, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.f };
    m_vPoint[1] = { m_tInfo.vPos.x + m_tInfo.vSize.x, m_tInfo.vPos.y - m_tInfo.vSize.y, 0.f };
    m_vPoint[2] = { m_tInfo.vPos.x + m_tInfo.vSize.x, m_tInfo.vPos.y + m_tInfo.vSize.y, 0.f };
    m_vPoint[3] = { m_tInfo.vPos.x - m_tInfo.vSize.x, m_tInfo.vPos.y + m_tInfo.vSize.y, 0.f };

    for (int i = 0; i < 4; ++i)
        m_vOriginPoint[i] = m_vPoint[i];

    m_vPosin = { m_tInfo.vPos.x, m_tInfo.vPos.y - m_PosinLength, 0.f };
    m_vOriginPosin = m_vPosin;

    // 스프라이트
    {
        CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Player/Player03.bmp", L"Player03");

        m_FrameKey = L"Player03";
        m_tFrame.iStart = 0;
        m_tFrame.iEnd = 4;
        m_tFrame.iMotion = 0;
        m_tFrame.dwSpeed = 200;
        m_tFrame.dwTime = GetTickCount64();
    }


    m_Weapon->FOnFire.Add([this](EWeaponType _Type)
        {
            switch (_Type)
            {
                // 이거 그냥 Bullet 클래스 하나로 다 처리하는거로 변경하기
            case EWeaponType::Base:
                CObjectManager::Get_Instance()->AddObject(
                    BULLET, CAbstractFactory<CBullet_Base>::Create(m_vPosin));
                break;

            case EWeaponType::Rifle:
                CObjectManager::Get_Instance()->AddObject(
                    BULLET, CAbstractFactory<CBullet_Base>::Create(m_vPosin));
                break;

            }
        });
}

int CPlayer03::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    for (auto component : m_Components)
        component->TickComponent();

    cout << ::CurWeaponType(m_Weapon) << endl;

    Key_Input();
	__super::Move_Frame();

    D3DXMATRIX	 matScale, matRotZ, matTrans;

    D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
    D3DXMatrixRotationZ(&matRotZ, m_fAngle);
    D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

    m_tInfo.matWorld = matScale * matRotZ * matTrans;

    for (int i = 0; i < 4; ++i)
    {
        m_vPoint[i] = m_vOriginPoint[i];
        m_vPoint[i] -= Vec3(400.f, 300.f, 0.f);

        D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
    }

    // 포신
    m_vPosin = m_vOriginPosin;
    m_vPosin -= Vec3(380.f, 340.f, 0.f);

    D3DXVec3TransformCoord(&m_vPosin, &m_vPosin, &m_tInfo.matWorld);

    return OBJ_NOEVENT;
}

void CPlayer03::Late_Update()
{
    CPlayer::Late_Update();
}

void CPlayer03::Render(HDC hDC)
{
	Vec3 center = { 0.f, 0.f, 0.f };
	D3DXVec3TransformCoord(&center, &center, &m_tInfo.matWorld);

	const int destW = (int)(m_tInfo.vSize.x * 2.f);
	const int destH = (int)(m_tInfo.vSize.y * 2.f);

	const int destX = (int)(center.x - m_tInfo.vSize.x);
	const int destY = (int)(center.y - m_tInfo.vSize.y);

	HDC hMemDC = CBmpManager::Get_Instance()->Find_Img(m_FrameKey);
	if (!hMemDC) return;

	HBITMAP hbmp = (HBITMAP)GetCurrentObject(hMemDC, OBJ_BITMAP);
	BITMAP bm{}; GetObject(hbmp, sizeof(bm), &bm);

	const int cols = m_tFrame.iEnd + 1;
	const int rows = 1;

	const int frameW = bm.bmWidth / cols;
	const int frameH = bm.bmHeight / rows;

	const int srcX = m_tFrame.iStart * frameW;
	const int srcY = m_tFrame.iMotion * frameH;

	SetStretchBltMode(hDC, HALFTONE);
	GdiTransparentBlt(hDC,
		destX, destY, destW, destH,
		hMemDC,
		srcX, srcY, frameW, frameH,
		RGB(255, 255, 255));

	//::DrawRect(hDC, m_vPoint, RGB(0, 255, 0));
}

void CPlayer03::Release()
{
    CPlayer::Release();
}

void CPlayer03::AddComponent(CComponent* _Component)
{
    CPlayer::AddComponent(_Component);

    m_Components.push_back(_Component);
}

void CPlayer03::OnComponentBeginOverlap(CObject* _Dst)
{
    CPlayer::OnComponentBeginOverlap(_Dst);

    if (!_Dst) return;

    //TakeDamage(_Dst->Get_Attack());
}

void CPlayer03::MoveToBounds()
{
    const float minX = 0.f + m_tInfo.vSize.x;
    const float maxX = WINCX - m_tInfo.vSize.x;
    const float minY = 0.f + m_tInfo.vSize.y;
    const float maxY = WINCY - m_tInfo.vSize.y;

    if (m_tInfo.vPos.x < minX) m_tInfo.vPos.x = minX;
    if (m_tInfo.vPos.x > maxX) m_tInfo.vPos.x = maxX;
    if (m_tInfo.vPos.y < minY) m_tInfo.vPos.y = minY;
    if (m_tInfo.vPos.y > maxY) m_tInfo.vPos.y = maxY;
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

    MoveToBounds();
}
