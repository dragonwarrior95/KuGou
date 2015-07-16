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
// #include "explorer1.h"

class CMainFrame : public CXMLWnd,public CWebBrowserEventHandler
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
		return m_strXMLName;
	}

	/*
	**@brief：处理事件通知
	*/
	void OnFinalMessage(HWND hWnd);
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

	bool OnBtnBrowser(void *lParam);

	bool OnBtnSkin(void* lParam);
	bool OnBtnBack(void* lParam);
	bool OnBtnForward(void* lParam);
	bool OnBtnRefresh(void* lParam);
	bool OnBtnHome(void* lParam);
	bool OnBtnSearch(void* lParam);


	void FadeIn() ;
	void FadeOut() ;

	virtual void NewWindow3(IDispatch **pDisp, VARIANT_BOOL *&Cancel, DWORD dwFlags, BSTR bstrUrlContext, BSTR bstrUrl);

private:
	bool m_bExit;
	int m_nAlpha ;
	int m_nFadeTimer ;
	DWORD m_dwStyle;

// 	CExplorer1 m_WebBrowers;

	CString		m_strHomeUrl;//主页地址

	CFadeButtonUI	*m_pBtnClose;
	CFadeButtonUI	*m_pBtnMin;
	CFadeButtonUI	*m_pBtnMax;
	CFadeButtonUI	*m_pBtnRestore;
	CEditUI		*m_pEdtAddr;//地址栏控件

	CHorizontalLayoutUI	*m_pHorLayAddr;//

	CWebBrowserUI *m_pWebClient;
	vector<CWebBrowserUI*> m_vetWebBrowser;//存放浏览器控件

	CButtonUI	*m_pBtnBrowser;

	CButtonUI	*m_pBtnSkin;
	CButtonUI	*m_pBtnBack;
	CButtonUI	*m_pBtnForward;
	CButtonUI	*m_pBtnRefresh;
	CButtonUI	*m_pBtnHome;
	CButtonUI	*m_pBtnSearch;

	CDuiString m_pStrSkinPath;
	CWndShadow m_wndShadow;

	//Tab button区
	CButtonUI	*m_pBtnLeft;
	CButtonUI	*m_pBtnRight;
	CButtonUI	*m_pBtnNewItem;
	CButtonUI	*m_pBtnTabClose;
	CButtonUI	*m_pBtnTabAll;
	CButtonUI	*m_pBtnRecycle;

	CHorizontalLayoutUI		*m_pHoriTabSwitch;	// Tab页父控件
	CHorizontalLayoutUI		*m_pHoriTabHome;	// 主页
	CHorizontalLayoutUI		*m_pHoriNewItem;	// 添加新页面
	CTabLayoutUI			*m_pTabSwitch;		// 网页Tab页面

	int m_nCurPage;	// 标记当前页
};
