#pragma once

#define	WINCX			800
#define	WINCY			600
#define PURE			= 0
#define OBJ_DEAD		1
#define OBJ_NOEVENT		0
#define	PI				3.14f
#define VK_MAX			0xff

extern HWND g_hWnd;

using Vec3 = D3DXVECTOR3;

typedef struct tagInfo
{
    D3DXVECTOR3		vPos;

    D3DXVECTOR3		vDir;
    D3DXVECTOR3		vLook;

    D3DXVECTOR3		vNormal;

    D3DXMATRIX		matWorld;

}INFO;

enum OBJECT
{
    PLAYER,
    MONSTER,
    MOUSE,
    OBJ_END
};

enum SCENENUMBER {
    SCENE01 = 1,
    SCENE02,
    SCENE03,
    SCENE04,
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
