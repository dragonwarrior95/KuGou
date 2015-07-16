#include "StdAfx.h"
#include "global.h"
#include <Shlwapi.h>




CMainFrame* g_pMainFrame = NULL;


wchar_t* Utf8ToUnicode(const char* pUtf8)
{
	ASSERT(pUtf8);
	int nChar = MultiByteToWideChar(CP_UTF8, 0, pUtf8, -1, NULL, 0);

	int nSize = nChar*sizeof(wchar_t) + 1;
	wchar_t* pwchBuffer = new wchar_t[nSize];

	nChar = MultiByteToWideChar(CP_UTF8, 0, pUtf8, -1, pwchBuffer, nSize);
	if(nChar == 0)
	{
		delete []pwchBuffer;
		return NULL;
	}

	pwchBuffer[nChar] = 0;
	return pwchBuffer;
}


#include <fstream>
using namespace std;
CString	 g_szCurPath=_T("");
CString  g_szLogPath=_T("");//日志文件


CString  G_GetCurrentPath()
{
	CString szCurrentPath=_T("");
	TCHAR szPath [MAX_PATH] = _T("") ;		 // 获取当前路径
	GetModuleFileName( NULL, szPath, MAX_PATH ) ;
	PathRemoveFileSpec(szPath) ;
	g_szCurPath = szPath ;
	return g_szCurPath;
}
CString  G_GetCurrentFullPath(CString strPathName)
{
	if(g_szCurPath.IsEmpty())
		G_GetCurrentPath();

	CString szFullPath=_T("");
	if (strPathName==_T(""))
		szFullPath=g_szCurPath;	
	else
		szFullPath=g_szCurPath+_T("\\")+strPathName;	

	return  szFullPath;
}

void G_DbgWrite(TCHAR * v_szFormat, ...)
{
	TCHAR szBuffer [1024] = {0};
	va_list pArgList ;

	va_start (pArgList, v_szFormat) ;

	_vsntprintf ( szBuffer, sizeof (szBuffer) / sizeof (char), v_szFormat, pArgList) ;

	va_end (pArgList) ;

	char szTmp[2048] = {0};
#ifdef UNICODE
	WideCharToMultiByte(CP_ACP, 0, szBuffer, -1, szTmp, 2048, NULL, NULL);
#else
	strcpy(szTmp, szBuffer);
#endif
	char szTime[MAX_PATH] = {0};
	char szBuf[2048*2] = {0};
	
	time_t curtime=time(0); 
	tm tim =*localtime(&curtime); 

	sprintf(szBuf, "[%04d:%02d:%02d-%02d:%02d:%02d]%s\r\n", tim.tm_year+1900, tim.tm_mon+1, tim.tm_mday, tim.tm_hour, tim.tm_min, tim.tm_sec, szTmp);
	g_szLogPath = G_GetCurrentFullPath(_T("dbg.log"));//获取日志文件
	CFileStatus fileStatus;
	if( CFile::GetStatus(g_szLogPath, fileStatus) )
	{
		if(fileStatus.m_size > 1024*1024)
			DeleteFile(g_szLogPath);
	}
	fstream fout(g_szLogPath, ios::binary|ios::app);
	fout.write(szBuf, strlen(szBuf));
	fout.close();
}