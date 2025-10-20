#pragma once
#include "CObject.h"

class CEnemy;
class CPlayer02;

class COribiters : public CObject
{
public:
    COribiters(CObject* pObj = nullptr);
    ~COribiters() override;

public:
    void Initialize() override;
    int  Update() override;
    void Late_Update() override;
    void Render(HDC _hDC) override;
    void Release() override;

private :
    void Transform_LocalToWorld();
    void Orbit_Center();

    void Detect_Opponent();
    void Detect_PlayerSide();
    void Detect_EnemySide();


public :
    void Set_Center(CObject* pObj) { pCenter = pObj; }
    CObject* Get_Center() { return pCenter; }

    void Set_OrbitAngle(float fAngle) { fOrbitAngle = fAngle; }
    float Get_OrbitAngle() { return fOrbitAngle; }

    void Set_DistToCenter(float fDist) { fDistToCenter = fDist; }
    float Get_DistToCenter() { return fDistToCenter; }

    void Set_PowerLevel(int iLv);
    int Get_PowerLevel();

    void Set_StartAngle(float fAngle) { m_fAngle = D3DXToRadian(fAngle); }
    void Set_RotationAngle(float fAngle) { fOrbitAngle = fAngle; }

    void Set_TeamID(OBJECT Id) { m_TeamID = Id; }

    // 충돌
public :
    const Vec3& Get_DrawPos() { return m_vDrawCenter; }

private:
    CObject* pCenter;

    float fOrbitAngle;
    float fDistToCenter;

    int iPowerLevel;
    HBRUSH hFillColor;

private:
    Vec3 m_vStartPos;
    Vec3 m_vLocalDraw;
    Vec3 m_vDrawCenter;

    Vec3 m_vLocalErase;
    Vec3 m_vEraseCenter;
    float fCenterToCenter;

    D3DXMATRIX matScale, matRotZ, matTrans;

private :

};

