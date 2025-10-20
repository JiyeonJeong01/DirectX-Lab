#include "pch.h"
#include "CSceneOver04.h"
#include "CSceneManager.h"
#include "CBmpManager.h"

CSceneOver04::CSceneOver04() : m_fTime(0.f), m_hFont(NULL), m_bSoundPlayed(false)
{
}

CSceneOver04::~CSceneOver04()
{
    Release();
}

void CSceneOver04::Initialize()
{

}

int CSceneOver04::Update()
{
    if (!m_bSoundPlayed)
    {
        PlaySound(L"../../Music/GameOver.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        m_bSoundPlayed = true;
    }
    if (GetAsyncKeyState(VK_RETURN))
    {
        PlaySound(NULL, 0, 0);
        CSceneManager::Get_Instance()->ChangeScene(LOGO);
        return 0;
    }
    m_fTime += 0.05f;

    return OBJ_NOEVENT;
}

void CSceneOver04::Late_Update()
{
}

void CSceneOver04::Render(HDC _hDC)
{
    HDC hGroundDC = CBmpManager::Get_Instance()->Find_Img(L"Ground");
    BitBlt(_hDC, 0, 0, 800, 600, hGroundDC, 0, 0, SRCCOPY);

    SetBkMode(_hDC, TRANSPARENT);
    SetTextColor(_hDC, RGB(255, 0, 0));

    float scale = 1.0f + 0.4f * sinf(m_fTime);
    int baseSize = 80;
    int fontSize = (int)(baseSize * scale);

    if (m_hFont)
        DeleteObject(m_hFont);

    m_hFont = CreateFontW(
        -fontSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
        HANGUL_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY, VARIABLE_PITCH, L"맑은 고딕");

    SelectObject(_hDC, m_hFont);

    LPCWSTR text = L"Game Over";

    SIZE textSize;
    GetTextExtentPoint32W(_hDC, text, lstrlenW(text), &textSize);

    int centerX = WINCX / 2;
    int centerY = WINCY / 2;
    int textX = centerX - (textSize.cx / 2);
    int textY = centerY - (textSize.cy / 2);

    TextOutW(_hDC, textX, textY, text, lstrlenW(text));
}

void CSceneOver04::Release()
{
    PlaySound(NULL, 0, 0);
    if (m_hFont)
    {
        DeleteObject(m_hFont);
        m_hFont = NULL;
    }
}
