#pragma once
#include "CPlayer.h"

class COribiters;

class CPlayer02 :  public CPlayer
{
public:
    CPlayer02();
    ~CPlayer02() override;

public:
    void Initialize() override;
    int  Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    virtual void AddComponent(CComponent* _Component) override;

public:
    void Handle_Input();
    void Apply_InputToPlayer();
    void Transform_LocalToWorld();
    void Fire();

public :
    void Add_Orbiter(COribiters* pOribiter);
    void Remove_Orbiter(COribiters* pOribiter);
    void Set_OrbiterLv(int iLv);


public :
    list<COribiters*>* Get_OrbiterList() { return &m_OrbiterList;  }

public :
    const D3DXMATRIX& Get_WorldMatrix() { return m_tInfo.matWorld; }

private:
    Vec3    m_vStartPos;
    Vec3		m_vPoint[4];
    Vec3		m_vOriginPoint[4];

    Vec3		m_vPosin;
    Vec3		m_vOriginPosin;

    float       m_FireHandler = 0.f;
    float       m_FireInterval = 0.5f;
    float       m_PosinLength = 50.f;

    // 회전체
    list <COribiters*> m_OrbiterList;

    int iOrbitTotalCnt;
    int iOrbitCurLv;

    // 클라이언트 입력
    float fVerticalInput;
    float fHorizontalIput;

    POINT pCursorPos;
    bool bLeftClicked;

    D3DXMATRIX matScale, matRotZ, matTrans;

    bool bTransProgress;
    bool bTransDone;
    Vec3 vTransPos;
    

    const float fEpsilone = 1.f;
};

