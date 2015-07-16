#include "StdAfx.h"
#include "SkinFile.h"
#include <stdio.h>


CSkinFile::CSkinFile(void)
{
	m_pFile = NULL;
	m_strFileName = _T("");
	m_verSkinFileInfo.clear();

	TCHAR szPath [MAX_PATH] = _T("") ;		 // 获取当前路径
	GetModuleFileName( NULL, szPath, MAX_PATH ) ;
	PathRemoveFileSpec(szPath) ;
	m_strSavePath.Format(_T("%s\\dlna_player"), szPath);
	CreateDirectory(m_strSavePath, NULL);
}


CSkinFile::~CSkinFile(void)
{
}

BOOL CSkinFile::SkinFileParse(CString v_strFileName)
{
	if(v_strFileName.IsEmpty() || !PathFileExists(v_strFileName))
		return FALSE;

	m_pFile = fopen(v_strFileName.GetBuffer(0), _T("rb"));
	if(NULL == m_pFile)
		return FALSE;

	int nFileCount;		// 文件总数
	int nRecordCount;	// 记录长度
	int nFileNameLength;// 文件名长度
	int nRet;

	nRet = (int)fread(&nFileCount, 4, 1, m_pFile);
	for (int i = 0; i < nFileCount; i++) // 循环读取皮肤文件数据
	{
		SKINFILEINFO_T info;
		memset(&info, 0, sizeof(SKINFILEINFO_T));
		info.nIndex = i;
		nRet = (int)fread(&nRecordCount, 4, 1, m_pFile);
		char ch;
		nRet = (int)fread(&ch, 1, 1, m_pFile);
		nFileNameLength = ch;
		wchar_t wszFileName[MAX_PATH]={0};
		nRet = (int)fread(wszFileName, nFileNameLength, 1, m_pFile);
		int len = WideCharToMultiByte(CP_ACP, 0, wszFileName, -1, NULL, 0, NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, wszFileName, -1, info.szFileName, (len>1024)?1024:len, NULL, NULL);

		nRet = (int)fread(&info.nFilter, 4, 1, m_pFile);
		nRet = (int)fread(&info.nFileSize, 4, 1, m_pFile);
		m_verSkinFileInfo.push_back(info);
	}

	for (int j = 0; j < m_verSkinFileInfo.size(); j++)
	{
		char *pData = new char[m_verSkinFileInfo[j].nFileSize+1];
		nRet = (int)fread(pData, m_verSkinFileInfo[j].nFileSize, 1, m_pFile);
		SaveFile(m_verSkinFileInfo[j].szFileName, pData, m_verSkinFileInfo[j].nFileSize);
		delete [] pData;
	}

	return TRUE;
}
BOOL CSkinFile::SaveFile(CString v_strSaveName, void* v_pData, int nLength)
{
	if(v_strSaveName.IsEmpty() || !v_pData || m_strSavePath.IsEmpty())
		return FALSE;

	CString strFileName;
	strFileName.Format(_T("%s\\%s"), m_strSavePath, v_strSaveName);
	FILE* fp = fopen(strFileName.GetBuffer(0), "wb");
	strFileName.ReleaseBuffer();
	if(NULL == fp)
		return FALSE;

	fwrite(v_pData, nLength, 1, fp);
	fclose(fp);

	return TRUE;
}
