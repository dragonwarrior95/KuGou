#pragma once

struct ResourceProviderItem
{
	CString strFile;
	DWORD	dwSize;
	LPBYTE	pBytes;
};
typedef std::vector<ResourceProviderItem*> VEC_ResourceProviderItem;

class CResourceProvider : public IResourceProvider
{
public:
	CResourceProvider();
	~CResourceProvider();

public:
	void ReadData(LPCTSTR pszFile, DWORD &dwSize, LPBYTE &pBytes);
	void FreeData(const LPBYTE pData);

protected:
	ResourceProviderItem *FindItem(LPCTSTR pszFile);
	void Clear();

protected:
	VEC_ResourceProviderItem m_vecItem;
};

