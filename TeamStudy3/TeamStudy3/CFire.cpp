#include "pch.h"
#include "CFire.h"
#include "CTimeManager.h"

CFire::CFire()
{
}

CFire::~CFire()
{
}

void CFire::Initialize()
{

}

void CFire::Update()
{
    if (!m_Firing) return;
    if (m_Interval <= 0.f) return;

    if (CTimeManager::Get_Instance()->GetTick(m_Acc, m_Interval))
        DoShoot();
}

void CFire::Release()
{

}

void CFire::BeginFire(bool bFlag)
{
    m_Firing = true;

    if (bFlag)
    {
        DoShoot();
    }
}

void CFire::EndFire()
{
    m_Firing = false;
}
