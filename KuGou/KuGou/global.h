#pragma once

#ifndef _GLOBAL_H
#define _GLOBAL_H

#define __DUILIB__

/************************************************************************/
/* 定义全局函数、成员                                                   */
/************************************************************************/

#include "MainFrame.h"

#define SEMAPHORE_MAINWND	 _T("duilib_mainframewnd")



extern CMainFrame*  g_pMainFrame;


//当前EXE文件的路径
extern  CString							g_szCurPath;
extern  CString							g_szLogPath;//日志文件路径	

//* @brief : 获取当前EXE所在的路径 
extern CString  G_GetCurrentPath();
//获取当前EXE所在的路径 下的文件路径
extern CString  G_GetCurrentFullPath(CString strPathName);

extern void G_DbgWrite(TCHAR * v_szFormat, ...);

#endif