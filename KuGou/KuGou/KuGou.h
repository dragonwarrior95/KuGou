
// KuGou.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CKuGouApp:
// �йش����ʵ�֣������ KuGou.cpp
//

class CKuGouApp : public CWinAppEx
{
public:
	CKuGouApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CKuGouApp theApp;