
// KuGouSkinParse.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CKuGouSkinParseApp:
// �йش����ʵ�֣������ KuGouSkinParse.cpp
//

class CKuGouSkinParseApp : public CWinAppEx
{
public:
	CKuGouSkinParseApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CKuGouSkinParseApp theApp;