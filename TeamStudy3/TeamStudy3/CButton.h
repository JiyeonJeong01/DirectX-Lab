#pragma once
#include "CObject.h"
class CButton : public CObject
{
public:
    CButton(float fX, float fY, int ID);
    virtual ~CButton();

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void SetFrameKey(const TCHAR* m_pFrameKey) {
        this->m_pFrameKey = m_pFrameKey;
    }

private:
    int		m_iDrawID;
    const TCHAR* m_pFrameKey;
    RECT rct;
};
