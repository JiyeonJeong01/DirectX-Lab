#pragma once

class CWallFourth
{
private:
    D3DXVECTOR3 vPoint[2];
public:
    CWallFourth();
    virtual ~CWallFourth();

    void Initialize();
    int Update();
    void Render(HDC hDC);
    void Release();

    D3DXVECTOR3 GetStartPoint() { return vPoint[0]; }
    D3DXVECTOR3 GetEndPoint() { return vPoint[1]; }
    void SetPoint(D3DXVECTOR3 first, D3DXVECTOR3 last);
};
