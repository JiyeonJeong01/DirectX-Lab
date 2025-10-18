#include "pch.h"
#include "CScene04.h"
#include "CBmpManager.h"
#include "CCollisionMgr04.h"
#define EPSILON 0.03f

CScene04::CScene04() : pPlayer(nullptr)
{
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

    vecBox.push_back(new CBoxFourth);
    vecBox[0]->Initialize();
    vecBox[0]->SetAllPoint({ 400.f, 100.f, 0.f }, 30.f);

    vecWall.push_back(new CWallFourth);
    vecWall[0]->SetPoint({ 0.f, 50.f, 0.f }, { 600.f, 50.f, 0.f });
}

int CScene04::Update()
{
    pPlayer->Update();

    for (auto pBox : vecBox)
    {
        pBox->Update();
    }
	return OBJ_NOEVENT;
}

void CScene04::Late_Update()
{
    D3DXVECTOR3* playerPoint = pPlayer->GetPoint();
    vector<D3DXVECTOR3*> pBoxPoint(vecBox.size(), 0);
    for (int i = 0; i < vecBox.size(); ++i)
        pBoxPoint[i] = vecBox[i]->GetPoint();

    vector<pair<D3DXVECTOR3, D3DXVECTOR3>> wallLines;
    for (auto wall : vecWall)
        wallLines.push_back({ wall->GetStartPoint(), wall->GetEndPoint() });

    for (int i = 0; i < 3; ++i)
    {
        for (int s = 0; s < vecBox.size(); ++s)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (CCollisionMgr04::CollisionLineToLine(playerPoint[i], playerPoint[i + 1],
                    pBoxPoint[s][j], pBoxPoint[s][j + 1]))
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
                                    playerPoint[0] -= {0.f, playerSpeed + EPSILON, 0.f};
                                    playerPoint[1] -= {0.f, playerSpeed + EPSILON, 0.f};
                                    playerPoint[2] -= {0.f, playerSpeed + EPSILON, 0.f};
                                    playerPoint[3] -= {0.f, playerSpeed + EPSILON, 0.f};
                                }
                                else if (j == 1)
                                {
                                    moveVec = { -(playerSpeed + EPSILON), 0.f, 0.f };
                                }
                                else if (j == 2)
                                {
                                    playerPoint[0] -= {0.f, -(playerSpeed), 0.f};
                                    playerPoint[1] -= {0.f, -(playerSpeed), 0.f};
                                    playerPoint[2] -= {0.f, -(playerSpeed), 0.f};
                                    playerPoint[3] -= {0.f, -(playerSpeed), 0.f};
                                    pPlayer->SetPosY(pPlayer->GetPos().y + playerSpeed);
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
            if (CCollisionMgr04::CollisionLineToLine(playerPoint[i], playerPoint[i + 1],
                pBoxPoint[s][3], pBoxPoint[s][0]))
            {
                float playerSpeed = pPlayer->GetSpeed();
                D3DXVECTOR3 moveVec = { playerSpeed + EPSILON, 0.f, 0.f };

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
                            break;
                        }
                    }
                    if (willCollideWall)
                    {
                        break;
                    }
                }

                if (willCollideWall)
                {
                    return;
                }

                for (int k = 0; k < 4; ++k)
                {
                    pBoxPoint[s][k] += moveVec;
                }

                D3DXVECTOR3 boxPos = vecBox[s]->GetPos();
                boxPos += moveVec;
                vecBox[s]->SetPos(boxPos);
            }
        }
    }
}



//void CScene04::Late_Update()
//{
//    D3DXVECTOR3* playerPoint = pPlayer->GetPoint();
//    vector<D3DXVECTOR3*> pBoxPoint(vecBox.size(), 0);
//    for(int i = 0; i < vecBox.size(); ++i)
//    {
//        pBoxPoint[i] = vecBox[i]->GetPoint();
//    }
//
//    for (int i = 0; i < 3; ++i)
//    {
//        for(int s = 0; s < vecBox.size(); ++s)
//        {
//            for (int j = 0; j < 3; ++j)
//            {
//                if (CCollisionMgr04::CollisionLineToLine(playerPoint[i], playerPoint[i + 1], pBoxPoint[s][j], pBoxPoint[s][j + 1]))
//                {
//                    if (j == 0)
//                    {
//                        float playerSpeed = pPlayer->GetSpeed();
//                        pBoxPoint[s][0].y += playerSpeed + EPSILON;
//                        pBoxPoint[s][1].y += playerSpeed + EPSILON;
//                        pBoxPoint[s][2].y += playerSpeed + EPSILON;
//                        pBoxPoint[s][3].y += playerSpeed + EPSILON;
//                        vecBox[s]->SetPosY(vecBox[s]->GetPos().y + playerSpeed);
//                    }
//                    else if (j == 1)
//                    {
//                        float playerSpeed = pPlayer->GetSpeed();
//                         pBoxPoint[s][0].x -= playerSpeed - EPSILON;
//                         pBoxPoint[s][1].x -= playerSpeed - EPSILON;
//                         pBoxPoint[s][2].x -= playerSpeed - EPSILON;
//                         pBoxPoint[s][3].x -= playerSpeed - EPSILON;
//                         vecBox[s]->SetPosY(vecBox[s]->GetPos().x - playerSpeed);
//                    }
//                    else if (j == 2)
//                    {
//                        float playerSpeed = pPlayer->GetSpeed();
//                        pBoxPoint[s][0].y -= playerSpeed - EPSILON;
//                        pBoxPoint[s][1].y -= playerSpeed - EPSILON;
//                        pBoxPoint[s][2].y -= playerSpeed - EPSILON;
//                        pBoxPoint[s][3].y -= playerSpeed - EPSILON;
//                        vecBox[s]->SetPosY(vecBox[s]->GetPos().y - playerSpeed);
//                    }
//                }
//            }
//            if (CCollisionMgr04::CollisionLineToLine(playerPoint[i], playerPoint[i + 1], pBoxPoint[s][3], pBoxPoint[s][0]))
//            {
//                float playerSpeed = pPlayer->GetSpeed();
//                pBoxPoint[s][0].x += playerSpeed + EPSILON;
//                pBoxPoint[s][1].x += playerSpeed + EPSILON;
//                pBoxPoint[s][2].x += playerSpeed + EPSILON;
//                pBoxPoint[s][3].x += playerSpeed + EPSILON;
//                vecBox[s]->SetPosY(vecBox[s]->GetPos().x + playerSpeed);
//            }
//        }
//    }
//}

void CScene04::Render(HDC _hDC)
{
    HDC	hGroundDC = CBmpManager::Get_Instance()->Find_Img(L"Ground");
    BitBlt(_hDC, 0, 0, 1920, 1280, hGroundDC, 0, 0, SRCCOPY);
    pPlayer->Render(_hDC);
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
