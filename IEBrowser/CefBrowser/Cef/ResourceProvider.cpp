#include "StdAfx.h"

CResourceProvider::CResourceProvider()
{
}

CResourceProvider::~CResourceProvider()
{
	//Clear();
}

void CResourceProvider::ReadData( LPCTSTR pszFile, DWORD &dwSize, LPBYTE &pBytes )
{
// 	ResourceProviderItem *pItem = FindItem(pszFile);
// 	if (pItem)
// 	{
// 		dwSize = pItem->dwSize;
// 		pBytes = pItem->pBytes;
// 		return ;
// 	}
// 	CRenderEngine::LoadBuffer(pszFile, NULL, pBytes, dwSize);
// 	pItem = new ResourceProviderItem;
// 	pItem->strFile = pszFile;
// 	pItem->pBytes = pBytes;
// 	pItem->dwSize = dwSize;
// 	m_vecItem.push_back(pItem);
}

void CResourceProvider::FreeData( const LPBYTE pData )
{
// 	CRenderEngine::FreeBuffer(pData);
}

ResourceProviderItem * CResourceProvider::FindItem( LPCTSTR pszFile )
{
	for (int i=0; i<m_vecItem.size(); ++i)
	{
		if (m_vecItem[i]->strFile == pszFile)
			return m_vecItem[i];
	}
	return NULL;
}

void CResourceProvider::Clear()
{
	for (int i=0; i<m_vecItem.size(); ++i)
	{
// 		CRenderEngine::FreeBuffer(m_vecItem[i]->pBytes);
		delete m_vecItem[i];
	}
	m_vecItem.clear();
}
