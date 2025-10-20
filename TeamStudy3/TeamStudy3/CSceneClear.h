﻿#pragma once
#include "CScene.h"
#include <math.h>

class CSceneClear : public CScene
{
private:
public:
    CSceneClear();
    virtual ~CSceneClear();
public:
    void		Initialize()	override;
    int			Update()		override;
    void		Late_Update()	override;
    void		Render(HDC _hDC)override;
    void		Release()		override;

};
