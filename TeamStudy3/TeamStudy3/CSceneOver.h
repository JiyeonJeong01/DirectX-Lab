#pragma once
#include "CScene.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

class CSceneOver : public CScene
{
private:
    float m_fTime;
    HFONT m_hFont;
    bool m_bSoundPlayed;
public:
    CSceneOver();
    virtual ~CSceneOver();
public:
    void		Initialize()	override;
    int			Update()		override;
    void		Late_Update()	override;
    void		Render(HDC _hDC)override;
    void		Release()		override;

};
