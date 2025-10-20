#pragma once
#include "CObject.h"

class COribiters;
class CPlayer02;

class CEnemy :   public CObject
{
public:
    CEnemy();
    ~CEnemy() override;

public:
    void Initialize() override;
    int  Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    void Transform_LocalToWorld();

public:
    void Set_OrbiterLv(int iLv);
    int Get_OrbiterLv() { return iOrbitCurLv; }

    Vec3* Get_Vertices() { return m_vPoint; }

    void Set_Player(CPlayer02* pPlayer) { this->pPlayer = pPlayer; }

public:
    list<COribiters*>* Get_OrbiterList() { return &m_OrbiterList; }

public:
    const D3DXMATRIX& Get_WorldMatrix() { return m_tInfo.matWorld; }

private :
    CPlayer02* pPlayer;

private:
    Vec3    m_vStartPos;
    Vec3		m_vPoint[4];
    Vec3		m_vOriginPoint[4];

    // 회전체
    list <COribiters*> m_OrbiterList;

    int iOrbitTotalCnt;
    int iOrbitCurLv;

    // 클라이언트 입력

    D3DXMATRIX matScale, matRotZ, matTrans;

    const float fEpsilone = 1.f;
};

