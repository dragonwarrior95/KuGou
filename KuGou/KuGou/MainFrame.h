/*******************************
**FileName	： MainFrame.h
**Creator	： zwl	
**Date		： 2014-01-14	
**Modifier	： 
**ModifyDate： 
**Comment	： 主窗口类的申明
**Version	： 1.0.0
/*******************************/

#pragma once
#include "Duilib/duilib.h"
#include "WndShadow.h"

class CMainFrame : public CXMLWnd
{
public:

	CMainFrame(LPCTSTR v_pStrSkinPath);
	~CMainFrame();

	/*
	**@brief: 初始化
	*/
	LPCTSTR GetWindowClassName() const
	{
		return _T("#32770 (Dialog)");
	}
	CDuiString GetSkinFolder()
	{
		return _T("skin");
	}

	CDuiString GetSkinFile()
	{
		return m_pStrSkinPath;
	}

	/*
	**@brief：处理事件通知
	*/
	void Notify(TNotifyUI & msg);
	virtual void InitWindow(void);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	void OnPrepare();
	virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);


	/**
	* @brief : 消息响应函数 
	*/

	DUI_DECLARE_MESSAGE_MAP()
// 	void OnTimer(TNotifyUI &msg);

	bool OnBtnClose(void *lParam);
	bool OnBtnMin(void *lParam);
	bool OnBtnMax(void *lParam);
	bool OnBtnRestore(void *lParam);

	void FadeIn() ;
	void FadeOut() ;

private:
	bool m_bExit;
	int m_nAlpha ;
	int m_nFadeTimer ;
	DWORD m_dwStyle;

	CFadeButtonUI	*m_pBtnClose;
	CFadeButtonUI	*m_pBtnMin;
	CFadeButtonUI	*m_pBtnMax;
	CFadeButtonUI	*m_pBtnRestore;



	CDuiString m_pStrSkinPath;
	CWndShadow m_wndShadow;
};
