#pragma once

#include "CTimeManager.h"

#define	WINCX			800
#define	WINCY			600
#define PURE			= 0
#define OBJ_DEAD		1
#define OBJ_NOEVENT		0
#define	PI				3.14f
#define VK_MAX			0xff

#define DELTA CTimeManager::Get_Instance()->Get_Delta()
#define TIME  CTimeManager::Get_Instance()

extern HWND g_hWnd;

using Vec2 = D3DXVECTOR2;
using Vec3 = D3DXVECTOR3;


typedef struct tagInfo
{
    Vec3		vPos;
    Vec3        vSize;

    Vec3		vDir;
    Vec3		vLook;

    Vec3		vNormal;

    D3DXMATRIX		matWorld;

}INFO;

enum OBJECT
{
    PLAYER,
    MONSTER,
    BULLET,
    ITEM,
    MOUSE,
    BLOCK,
    OBJ_END
};

enum SCENENUMBER {
    SCENE01 = 1,
    SCENE02,
    SCENE03,
    SCENE04,
    SCENEOVER04,
    SCENE_END
};

template<typename T>
void	Safe_Delete(T& P)
{
    if (P)
    {
        delete P;
        P = nullptr;
    }
}

struct DeleteObj
{
    template<typename T>
    void	operator()(T& p)
    {
        if (p)
        {
            delete p;
            p = nullptr;
        }
    }
};

struct DeleteMap
{
    template<typename T>
    void	operator()(T& MyPair)
    {
        if (MyPair.second)
        {
            delete MyPair.second;
            MyPair.second = nullptr;
        }
    }
};


struct tagFinder
{
    tagFinder(const TCHAR* pTag) : m_pTag(pTag)
    {}

    template<typename T>
    bool operator()(T& MyPair)
    {
        return !lstrcmp(MyPair.first, m_pTag);
    }


    const TCHAR* m_pTag;
};


