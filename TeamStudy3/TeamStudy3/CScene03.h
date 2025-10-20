#pragma once
#include "CScene.h"

class CScene03 : public CScene
{
public:
    CScene03();
    virtual ~CScene03();

public:
    void Initialize() override;
    int  Update() override;
    void Late_Update() override;
    void Render(HDC _hDC) override;
    void Release() override;

public:
    void SpawnMonster();

private:
    Vec3    m_vMapPos = { 0.f, 0.f, 0.f };

    int     m_Score = 0;

    int     m_SpawnMinX = 170;
    int     m_SpawnMaxX = 650;
    int     m_SpawnMinY = 50;
    int     m_SpawnMaxY = 100;

    float   m_SpawnTime = 0.f;
    float   m_SpawnCooltime = 0.f;

    float   m_MinCooltime = 1.0f;
    float   m_MaxCooltime = 2.0f;

    float   m_SceneTimer = 0.f;

    class CPlayer03* m_Player = nullptr;

    HFONT    m_ScoreFont = nullptr;
    COLORREF m_ScoreColor = RGB(255, 255, 255);
    POINT    m_ScorePos = { 20, 20 };

    HFONT    m_TimerFont = nullptr;
    COLORREF m_TimerColor = RGB(255, 255, 255);
    POINT    m_TimerPos = { 80, 20 };

    float   m_MaxSceneTime = 40.f;
    float   m_StartMinCool = 0.5f;
    float   m_EndMinCool = 0.22f;
    float   m_StartMaxCool = 0.9f;
    float   m_EndMaxCool = 0.35f;

    float   m_MinCoolFloor = 0.14f;
    int     m_BaseSpawnCount = 1;
    int     m_MaxSpawnCount = 4;
    int     m_MaxSpawnPerBurst = 4;

    int     m_StartAliveCap = 24;
    int     m_EndAliveCap = 48;
};
