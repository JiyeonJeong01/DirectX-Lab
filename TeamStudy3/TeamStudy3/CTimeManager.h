#pragma once

class CTimeManager
{
private:
    CTimeManager();
    CTimeManager(const CTimeManager& rhs) = delete;
    CTimeManager& operator=(CTimeManager& rManager) = delete;
    ~CTimeManager();

public:
    static CTimeManager* Get_Instance()
    {
        if (m_pInstance == nullptr)
        {
            m_pInstance = new CTimeManager;

        }

        return m_pInstance;
    }
    static void DestroyInstance()
    {
        if (m_pInstance)
        {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }

    void Update();

    float Get_Delta() const { return m_fDelta; }

    bool GetTick(float& acc, float interval);

private:
    static CTimeManager* m_pInstance;

    LARGE_INTEGER m_Freq{};  
    LARGE_INTEGER m_Prev{};  
    float         m_fDelta{};

};

