#pragma once
#include "CScene.h"

class CScene03 : public CScene
{
public:
	CScene03();
	virtual ~CScene03();

public:
	void		Initialize()	override;
	int			Update()		override;
	void		Late_Update()	override;
	void		Render(HDC _hDC)override;
	void		Release()		override;

public:
    void SpawnMonster();

private:
    int        m_Score = 0;

    int        m_SpawnMinX = 100;
    int        m_SpawnMaxX = 700;
    int        m_SpawnMinY = 50;
    int        m_SpawnMaxY = 100;

    float m_SpawnTime = 0.f;
    float m_SpawnCooltime = 0.f;

    const float m_MinCooltime = 0.1f; 
    const float m_MaxCooltime = 0.3f; 

};
