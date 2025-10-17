#include "pch.h"
#include "CBmpManager.h"

#include "CMyBmp.h"
#include "Define.h"

CBmpManager* CBmpManager::m_pInstance = nullptr;

CBmpManager::CBmpManager()
{
}

CBmpManager::~CBmpManager()
{
	Release();
}

void CBmpManager::Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey)
{
	auto		iter = find_if(m_mapBit.begin(), m_mapBit.end(), tagFinder(pImgKey));

	if (m_mapBit.end() == iter)
	{
		CMyBmp* pBmp = new CMyBmp;

		pBmp->Load_Bmp(pFilePath);

		m_mapBit.insert({ pImgKey, pBmp });
	}

}

HDC CBmpManager::Find_Img(const TCHAR* pImgKey)
{
	auto		iter = find_if(m_mapBit.begin(), m_mapBit.end(), tagFinder(pImgKey));

	if (iter == m_mapBit.end())
		return nullptr;

	return iter->second->Get_MemDC();
}

void CBmpManager::Release()
{
	for_each(m_mapBit.begin(), m_mapBit.end(), DeleteMap());
	m_mapBit.clear();
}
