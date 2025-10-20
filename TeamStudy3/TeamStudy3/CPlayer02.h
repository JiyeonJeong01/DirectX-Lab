#pragma once
#include "CPlayer.h"

class COribiters;
class CEnemy;

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

public :
    void Add_Orbiter(COribiters* pOribiter);
    void Remove_Orbiter(COribiters* pOribiter);

    void Set_OrbiterLv(int iLv);
    int Get_OrbiterLv() { return iOrbitCurLv; }

    Vec3* Get_Vertices() { return m_vPoint; }

public :
    list<COribiters*>* Get_OrbiterList() { return &m_OrbiterList;  }
    
public :
    const D3DXMATRIX& Get_WorldMatrix() { return m_tInfo.matWorld; }

private :
    void Progress_Knockback();

private:
#pragma region 변환
    Vec3    m_vStartPos;
    Vec3		m_vPoint[4];
    Vec3		m_vOriginPoint[4];

    D3DXMATRIX matScale, matRotZ, matTrans;
#pragma endregion

#pragma region 회전체
    list <COribiters*> m_OrbiterList;

    int iOrbitTotalCnt;
    int iOrbitCurLv;
#pragma endregion

#pragma region 클라이언트 입력
    float fVerticalInput;
    float fHorizontalIput;

    POINT pCursorPos;
    bool bLeftClicked;
#pragma endregion

#pragma region 이동
    bool bTransProgress;
    bool bTransDone;
    Vec3 vTransPos;

    bool bKnockback;
    Vec3 vKnockbackDir;
    DWORD dwKnockbackElpasedTime;
#pragma endregion
    const float fEpsilone = 1.f;
    
};

