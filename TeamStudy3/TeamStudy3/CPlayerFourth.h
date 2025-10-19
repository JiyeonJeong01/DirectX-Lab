#pragma once
#include "CObjectFourth.h"
#include "CWallFourth.h"
class CPlayerFourth : public CObjectFourth
{
private:
    void KeyInput();
    vector<CWallFourth*>* vecWall;
    bool isMove;
    bool isInvincible;
    bool isDead;
    short sHp;

    ULONGLONG dwInvincibleTime;

    float preAngle;
    Vec3 prePos;
public:
    CPlayerFourth();
    virtual ~CPlayerFourth();

public:
    void Initialize() override;
    int Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    const short GetHp() const { return sHp; }
    const bool GetInvincible() const { return isInvincible; }
    const bool GetDead() const { return isDead; }

    void SetWallVector(vector<CWallFourth*>* vecWall) { this->vecWall = vecWall; }
    void SetHpMinus(const short& sHp) { this->sHp -= sHp; }
    void SetHit() { isInvincible = true; dwInvincibleTime = GetTickCount64(); }
};

