#pragma once
#include "CObjectFourth.h"
#include "CWallFourth.h"
class CPlayerFourth : public CObjectFourth
{
private:
    void KeyInput();
    vector<CWallFourth*>* vecWall;
    bool isMove;
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

    void SetWallVector(vector<CWallFourth*>* vecWall) { this->vecWall = vecWall; }
};

