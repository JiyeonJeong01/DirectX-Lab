#include "pch.h"
#include "CScene04.h"
#include "CBmpManager.h"
#include "CCollisionMgr04.h"
#include "CSceneManager.h"
#define EPSILON 0.03f

CScene04::CScene04() : pPlayer(nullptr), pObstacle(nullptr), sScore(0)
{
    pGoal[0] = nullptr;
    pGoal[1] = nullptr;
}

CScene04::~CScene04()
{
	Release();
}

void CScene04::Initialize()
{
    CBmpManager::Get_Instance()->Insert_Bmp(L"../../Image/Ground.bmp", L"Ground");

    if (pPlayer == nullptr)
    {
        pPlayer = new CPlayerFourth;
        pPlayer->Initialize();
    }

    if (pObstacle == nullptr)
    {
        pObstacle = new CObstacleFourth;
        pObstacle->Initialize();
    }

    for (int i = 0; i < 2; ++i)
    {
        if (pGoal[i] == nullptr)
        {
            pGoal[i] = new CGoalFourth;
            pGoal[i]->Initialize();
        }
    }
    pGoal[1]->SetAllPoint({ 625.f, 425.f, 0.f }, 40.f);

    for (int i = 0; i < 2; ++i)
    {
        vecBox.push_back(new CBoxFourth);
        vecBox[i]->Initialize();
    }
    vecBox[0]->SetAllPoint({ 175.f, 250.f, 0.f }, 30.f);
    vecBox[1]->SetAllPoint({ 400.f, 450.f, 0.f }, 30.f);

    for(int i = 0; i < 10; ++i)
    {
        vecWall.push_back(new CWallFourth);
        vecWall[i]->Initialize();
    }
    vecWall[0]->SetPoint({ 100.f, 100.f, 0.f }, { 700.f, 100.f, 0.f });
    vecWall[1]->SetPoint({ 700.f, 100.f, 0.f }, { 700.f, 500.f, 0.f });
    vecWall[2]->SetPoint({ 700.f, 500.f, 0.f }, { 100.f, 500.f, 0.f });
    vecWall[3]->SetPoint({ 100.f, 500.f, 0.f }, { 100.f, 100.f, 0.f });

    vecWall[4]->SetPoint({ 500.f, 100.f, 0.f }, { 500.f, 250.f, 0.f });
    vecWall[5]->SetPoint({ 500.f, 250.f, 0.f }, { 550.f, 250.f, 0.f });
    vecWall[6]->SetPoint({ 550.f, 250.f, 0.f }, { 550.f, 100.f, 0.f });

    vecWall[7]->SetPoint({ 250.f, 500.f, 0.f }, { 250.f, 350.f, 0.f });
    vecWall[8]->SetPoint({ 250.f, 350.f, 0.f }, { 300.f, 350.f, 0.f });
    vecWall[9]->SetPoint({ 300.f, 350.f, 0.f }, { 300.f, 500.f, 0.f });

    dynamic_cast<CPlayerFourth*>(pPlayer)->SetWallVector(&vecWall);
}

int CScene04::Update()
{
    if (dynamic_cast<CPlayerFourth*>(pPlayer)->GetDead())
    {
        CSceneManager::Get_Instance()->ChangeScene(SCENEOVER04);
        return 0;
    }

    pPlayer->Update();
    pObstacle->Update();

    for (auto pBox : vecBox)
    {
        pBox->Update();
    }
	return OBJ_NOEVENT;
}

void CScene04::Late_Update()
{
    D3DXVECTOR3* playerPoint = pPlayer->GetPoint();
    D3DXVECTOR3* obstaclePoint = pObstacle->GetPoint();
    D3DXVECTOR3* goalPoint[2] = {};
    for (int i = 0; i < 2; ++i)
    {
        goalPoint[i] = pGoal[i]->GetPoint();
    }
    vector<D3DXVECTOR3*> pBoxPoint(vecBox.size(), 0);
    for (int i = 0; i < vecBox.size(); ++i)
        pBoxPoint[i] = vecBox[i]->GetPoint();

    vector<pair<D3DXVECTOR3, D3DXVECTOR3>> wallLines;
    for (auto wall : vecWall)
        wallLines.push_back({ wall->GetStartPoint(), wall->GetEndPoint() });

    for (int i = 0; i < 4; ++i)
    {
        for (int s = 0; s < vecBox.size(); ++s)
        {
            for (int j = 0; j < 4; ++j)
            {
                if (CCollisionMgr04::CollisionLineToLine(playerPoint[i % 4], playerPoint[(i + 1) % 4],
                    pBoxPoint[s][j % 4], pBoxPoint[s][(j + 1) % 4]))
                {
                    float playerSpeed = pPlayer->GetSpeed();
                    D3DXVECTOR3 moveVec = { 0.f, 0.f, 0.f };

                    if (j == 0)
                    {
                        moveVec = { 0.f, playerSpeed + EPSILON, 0.f };
                    }
                    else if (j == 1)
                    {
                        moveVec = { -(playerSpeed + EPSILON), 0.f, 0.f };
                    }
                    else if (j == 2)
                    {
                        moveVec = { 0.f, -(playerSpeed + EPSILON), 0.f };
                    }
                    else if (j == 3)
                    {
                        moveVec = { playerSpeed + EPSILON, 0.f, 0.f };
                    }

                    bool willCollideWall = false;
                    for (auto& wall : wallLines)
                    {
                        for (int k = 0; k < 4; ++k)
                        {
                            D3DXVECTOR3 movedA = pBoxPoint[s][k] + moveVec;
                            D3DXVECTOR3 movedB = pBoxPoint[s][(k + 1) % 4] + moveVec;

                            if (CCollisionMgr04::CollisionLineToLine(movedA, movedB, wall.first, wall.second))
                            {
                                willCollideWall = true;
                                if (j == 0)
                                {
                                    playerPoint[0] -= {0.f, playerSpeed, 0.f};
                                    playerPoint[1] -= {0.f, playerSpeed, 0.f};
                                    playerPoint[2] -= {0.f, playerSpeed, 0.f};
                                    playerPoint[3] -= {0.f, playerSpeed, 0.f};
                                    pPlayer->SetPosY(pPlayer->GetPos().y - playerSpeed);
                                }
                                else if (j == 1)
                                {
                                    playerPoint[0] += { playerSpeed, 0.f, 0.f };
                                    playerPoint[1] += { playerSpeed, 0.f, 0.f };
                                    playerPoint[2] += { playerSpeed, 0.f, 0.f };
                                    playerPoint[3] += { playerSpeed, 0.f, 0.f };
                                    pPlayer->SetPosX(pPlayer->GetPos().x + playerSpeed);
                                }
                                else if (j == 2)
                                {
                                    playerPoint[0] -= {0.f, -playerSpeed, 0.f};
                                    playerPoint[1] -= {0.f, -playerSpeed, 0.f};
                                    playerPoint[2] -= {0.f, -playerSpeed, 0.f};
                                    playerPoint[3] -= {0.f, -playerSpeed, 0.f};
                                    pPlayer->SetPosY(pPlayer->GetPos().y + playerSpeed);
                                }
                                else if (j == 3)
                                {
                                    playerPoint[0] += { -playerSpeed, 0.f, 0.f };
                                    playerPoint[1] += { -playerSpeed, 0.f, 0.f };
                                    playerPoint[2] += { -playerSpeed, 0.f, 0.f };
                                    playerPoint[3] += { -playerSpeed, 0.f, 0.f };
                                    pPlayer->SetPosX(pPlayer->GetPos().x - playerSpeed);
                                }
                                break;
                            }
                        }
                        if (willCollideWall) break;
                    }

                    if (willCollideWall)
                    {
                        return;
                    }

                    for (int k = 0; k < 4; ++k)
                        pBoxPoint[s][k] += moveVec;

                    D3DXVECTOR3 boxPos = vecBox[s]->GetPos();
                    boxPos += moveVec;
                    vecBox[s]->SetPos(boxPos);
                }
            }
        }
    }

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (CCollisionMgr04::CollisionLineToLine(playerPoint[i % 4], playerPoint[(i + 1) % 4], obstaclePoint[j % 4], obstaclePoint[(j + 1) % 4]))
            {
                if(!dynamic_cast<CPlayerFourth*>(pPlayer)->GetInvincible())
                {
                    dynamic_cast<CPlayerFourth*>(pPlayer)->SetHpMinus(1);
                    dynamic_cast<CPlayerFourth*>(pPlayer)->SetHit();
                    break;
                }
            }
        }
    }

    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            for (auto& pBox : pBoxPoint)
            {
                for (int k = 0; k < 4; ++k)
                {
                    if (CCollisionMgr04::CollisionLineToLine(goalPoint[i][j], goalPoint[i][j + 1], pBox[k], pBox[k + 1]))
                    {
                        dynamic_cast<CGoalFourth*>(pGoal[i])->SetGoal(true);
                        break;
                    }
                }
                if (dynamic_cast<CGoalFourth*>(pGoal[i])->GetGoal())
                {
                    break;
                }
            }
            if (dynamic_cast<CGoalFourth*>(pGoal[i])->GetGoal())
            {
                break;
            }
        }
    }

    if (dynamic_cast<CGoalFourth*>(pGoal[0])->GetGoal() && dynamic_cast<CGoalFourth*>(pGoal[1])->GetGoal())
    {
        CSceneManager::Get_Instance()->ChangeScene(LOGO);
        return;
    }
    for (int i = 0; i < 2; ++i)
    {
        dynamic_cast<CGoalFourth*>(pGoal[i])->SetGoal(false);
    }
}

void CScene04::Render(HDC _hDC)
{
    HDC	hGroundDC = CBmpManager::Get_Instance()->Find_Img(L"Ground");
    BitBlt(_hDC, 0, 0, 1920, 1280, hGroundDC, 0, 0, SRCCOPY);
    pPlayer->Render(_hDC);
    for (int i = 0; i < 2; ++i)
    {
        pGoal[i]->Render(_hDC);
    }


    pObstacle->Render(_hDC);
    for (auto pBox : vecBox)
    {
        pBox->Render(_hDC);
    }
    for (auto pWall : vecWall)
    {
        pWall->Render(_hDC);
    }
}

void CScene04::Release()
{
    Safe_Delete<CObjectFourth*>(pPlayer);
    Safe_Delete<CObjectFourth*>(pObstacle);
    for (int i = 0; i < 2; ++i)
    {
        Safe_Delete<CObjectFourth*>(pGoal[i]);
    }
    for_each(vecBox.begin(), vecBox.end()
        , [](CObjectFourth* _p) -> void {
            if (_p)
            {
                delete _p;
                _p = nullptr;
            }
        });
    for_each(vecWall.begin(), vecWall.end()
        , [](CWallFourth* _p) -> void {
            if (_p)
            {
                delete _p;
                _p = nullptr;
            }
        });
}
