#pragma once

#include <vector>
using namespace std;

typedef struct SkinFileInfo_T
{
	int nIndex;			// 标记当前是第几个文件
	char szFileName[MAX_PATH];// 文件名
	int nFilter;		// 四个预留字节
	int nFileSize;		// 文件大小
} SKINFILEINFO_T;

class CSkinFile
{
public:
	CSkinFile(void);
	~CSkinFile(void);

	BOOL SkinFileParse(CString v_strFileName);
	BOOL SaveFile(CString v_strSaveName, void* v_pData, int nLength);

private:
	FILE* m_pFile;
	CString m_strFileName;// 文件名
	CString m_strSavePath;// 文件存储路径
	vector<SKINFILEINFO_T> m_verSkinFileInfo;//存储皮肤文件信息
};

