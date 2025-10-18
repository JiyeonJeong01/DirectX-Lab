#include "pch.h"
#include "CTimeManager.h"

CTimeManager* CTimeManager::m_pInstance = nullptr;

CTimeManager::CTimeManager()
{
    QueryPerformanceFrequency(&m_Freq);
    QueryPerformanceCounter(&m_Prev);
    m_fDelta = 0.f;
}

CTimeManager::~CTimeManager()
{

}

void CTimeManager::Update()
{
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);

    const LONGLONG diff = now.QuadPart - m_Prev.QuadPart;
    m_Prev = now;

    m_fDelta = static_cast<float>(static_cast<double>(diff) / static_cast<double>(m_Freq.QuadPart));

    if (m_fDelta < 0.f)   m_fDelta = 0.f;
    if (m_fDelta > 0.2f)  m_fDelta = 0.2f; 
}

bool CTimeManager::GetTick(float& acc, float interval)
{
    acc += m_fDelta;
    if (acc >= interval)
    {
        acc -= interval;     
        return true;
    }
    return false;
}
