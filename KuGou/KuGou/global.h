#pragma once

#ifndef _GLOBAL_H
#define _GLOBAL_H

#define __DUILIB__

/************************************************************************/
/* ����ȫ�ֺ�������Ա                                                   */
/************************************************************************/

#include "MainFrame.h"

#define SEMAPHORE_MAINWND	 _T("duilib_mainframewnd")



extern CMainFrame*  g_pMainFrame;


//��ǰEXE�ļ���·��
extern  CString							g_szCurPath;
extern  CString							g_szLogPath;//��־�ļ�·��	

//* @brief : ��ȡ��ǰEXE���ڵ�·�� 
extern CString  G_GetCurrentPath();
//��ȡ��ǰEXE���ڵ�·�� �µ��ļ�·��
extern CString  G_GetCurrentFullPath(CString strPathName);

extern void G_DbgWrite(TCHAR * v_szFormat, ...);

#endif