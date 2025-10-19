#pragma once

#include "CObject.h"
class CPlayer02;
class COribiters;
class CCollisionMgr02
{
public :
    void Collision_PlayerToOrbiter(CPlayer02* pPlayer, list<COribiters*>* orbiterList);
};

