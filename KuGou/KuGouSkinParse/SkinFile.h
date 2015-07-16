#pragma once

#include <vector>
using namespace std;

typedef struct SkinFileInfo_T
{
	int nIndex;			// ��ǵ�ǰ�ǵڼ����ļ�
	char szFileName[MAX_PATH];// �ļ���
	int nFilter;		// �ĸ�Ԥ���ֽ�
	int nFileSize;		// �ļ���С
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
	CString m_strFileName;// �ļ���
	CString m_strSavePath;// �ļ��洢·��
	vector<SKINFILEINFO_T> m_verSkinFileInfo;//�洢Ƥ���ļ���Ϣ
};

