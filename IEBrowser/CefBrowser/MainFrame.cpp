/*******************************
**FileName	： MainFrame.h
**Creator	： zwl	
**Date		： 2014-01-14	
**Modifier	： 
**ModifyDate： 
**Comment	： 主窗口类的实现
**Version	： 1.0.0
/*******************************/
#include "StdAfx.h"
#include "MainFrame.h"
#include "resource.h"
#include <io.h>


#define FADE_IN_TIMER 1
#define FADE_OUT_TIMER 2

#define FADE_STEP 10
#define TIMER_FREQUENCY 25


DUI_BEGIN_MESSAGE_MAP(CMainFrame, WindowImplBase)
// DUI_ON_MSGTYPE(DUI_MSGTYPE_TIMER, OnTimer)
DUI_END_MESSAGE_MAP()

CMainFrame::CMainFrame(LPCTSTR v_pStrSkinPath):CXMLWnd(v_pStrSkinPath),
m_strHomeUrl(_T("http://hao.360.cn/?1004"))
{
	m_strXMLName = v_pStrSkinPath;

	m_pBtnClose		= NULL;
	m_pBtnMin		= NULL;
	m_pBtnMax		= NULL;
	m_pBtnRestore	= NULL;

	m_pEdtAddr		= NULL;
	m_pHorLayAddr	= NULL;
	m_pActiveClient = NULL;
	m_pWebClient	= NULL;
	m_pBtnBrowser	= NULL;


	m_pBtnSkin		= NULL;
	m_pBtnBack		= NULL;
	m_pBtnForward	= NULL;
	m_pBtnRefresh	= NULL;
	m_pBtnHome		= NULL;
	m_pBtnSearch	= NULL;

	m_bExit = false;

}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
	delete this;
}


void CMainFrame::InitWindow(void)
{
	m_pBtnClose = static_cast<CFadeButtonUI*>(m_PaintManager.FindControl(_T("BtnClose")));
	if(m_pBtnClose) m_pBtnClose->OnNotify += MakeDelegate(this, &CMainFrame::OnBtnClose);

	m_pBtnMin   = static_cast<CFadeButtonUI*>(m_PaintManager.FindControl(_T("BtnMin")));
	if(m_pBtnMin)   m_pBtnMin->OnNotify += MakeDelegate(this, &CMainFrame::OnBtnMin);

	m_pBtnMax   = static_cast<CFadeButtonUI*>(m_PaintManager.FindControl(_T("BtnMax")));
	if(m_pBtnMax)   m_pBtnMax->OnNotify += MakeDelegate(this, &CMainFrame::OnBtnMax);

	m_pBtnRestore   = static_cast<CFadeButtonUI*>(m_PaintManager.FindControl(_T("BtnRestore")));
	if(m_pBtnRestore)   m_pBtnRestore->OnNotify += MakeDelegate(this, &CMainFrame::OnBtnRestore);

	m_pBtnBrowser	= static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("BtnBrowser")));
	if(m_pBtnBrowser)	m_pBtnBrowser->OnNotify += MakeDelegate(this, &CMainFrame::OnBtnBrowser);


	m_pBtnSkin	= static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("BtnSkin")));
	if(m_pBtnSkin)	m_pBtnSkin->OnNotify += MakeDelegate(this, &CMainFrame::OnBtnSkin);

	m_pBtnBack	= static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("BtnBack")));
	if(m_pBtnBack)	m_pBtnBack->OnNotify += MakeDelegate(this, &CMainFrame::OnBtnBack);

	m_pBtnForward	= static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("BtnForward")));
	if(m_pBtnForward)	m_pBtnForward->OnNotify += MakeDelegate(this, &CMainFrame::OnBtnForward);

	m_pBtnRefresh	= static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("BtnRefresh")));
	if(m_pBtnRefresh)	m_pBtnRefresh->OnNotify += MakeDelegate(this, &CMainFrame::OnBtnRefresh);

	m_pBtnHome	= static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("BtnHome")));
	if(m_pBtnHome)	m_pBtnHome->OnNotify += MakeDelegate(this, &CMainFrame::OnBtnHome);

	m_pBtnSearch	= static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("BtnSerach")));
	if(m_pBtnSearch)	m_pBtnSearch->OnNotify += MakeDelegate(this, &CMainFrame::OnBtnSearch);

	m_pEdtAddr	= static_cast<CEditUI*>(m_PaintManager.FindControl(_T("EditAddr")));
	if(m_pEdtAddr)
		m_pEdtAddr->SetText(m_strHomeUrl);

	m_pHorLayAddr = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("HorLayAddr2")));


	m_pWebClient = static_cast<CWebBrowserUI*>(m_PaintManager.FindControl(_T("ActiveClient")));
	if(m_pWebClient)
	{
		m_pWebClient->SetWebBrowserEventHandler(this);
		m_pWebClient->SetHomePage(m_strHomeUrl);
	}


	//阴影效果
	CWndShadow::Initialize(AfxGetInstanceHandle());
	m_wndShadow.Create(m_hWnd);
	m_wndShadow.SetSize(5);
	m_wndShadow.SetPosition(0,0);


	CenterWindow();

}

LRESULT CMainFrame::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if ( wParam == FADE_IN_TIMER )
	{
		m_nAlpha += FADE_STEP ;
	}
	else if ( wParam == FADE_OUT_TIMER )
	{
		m_bExit = true;
		m_nAlpha -= FADE_STEP ;

		if ( m_nAlpha <= 0 )
		{
			PostMessage(WM_CLOSE);

			return 0;
		}

	}

	if( (wParam == FADE_IN_TIMER) || (wParam == FADE_OUT_TIMER) )
	{
		if ( m_nAlpha >= 0 && m_nAlpha < 255 )
		{
			::SetLayeredWindowAttributes(*this, 0, m_nAlpha, LWA_ALPHA);
		}
		else
		{
			m_nAlpha = 255;
			::SetLayeredWindowAttributes(*this, 0, m_nAlpha, LWA_ALPHA);
			m_dwStyle &= (~WS_EX_LAYERED);
			::SetWindowLong(m_hWnd, GWL_EXSTYLE, m_dwStyle);

			KillTimer(m_hWnd, m_nFadeTimer);
			m_nFadeTimer = 0 ;
		}

		return 0;
	}

	return 1;
}

void CMainFrame::FadeIn()
{
	if ( m_nFadeTimer != 0 )
	{
		KillTimer(m_hWnd, m_nFadeTimer) ;
	}

	m_nAlpha = 0 ;

	//	ShowWindow(SW_HIDE) ;

	::SetLayeredWindowAttributes(*this, 0, m_nAlpha, LWA_ALPHA);

	m_nFadeTimer = SetTimer(m_hWnd, FADE_IN_TIMER, TIMER_FREQUENCY, NULL) ;


}

void CMainFrame::FadeOut()
{
	if ( m_nFadeTimer != 0 )
	{
		KillTimer(m_hWnd, m_nFadeTimer) ;
	}

	m_dwStyle |= WS_EX_LAYERED;
	::SetWindowLong(m_hWnd, GWL_EXSTYLE, m_dwStyle);

	m_nAlpha = 255 ;
	::SetLayeredWindowAttributes(*this, 0, m_nAlpha, LWA_ALPHA);

	m_nFadeTimer = SetTimer(m_hWnd, FADE_OUT_TIMER, TIMER_FREQUENCY, NULL) ;

	//	DestroyWindow() ;
}

void CMainFrame::OnPrepare()
{
	//窗口透明
	m_dwStyle = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
	m_dwStyle |= WS_EX_LAYERED;
	::SetWindowLong(m_hWnd, GWL_EXSTYLE, m_dwStyle);
// 	COLORREF rgbMask(RGB(0,0,0));
// 	::SetLayeredWindowAttributes(*this, rgbMask, 255, LWA_COLORKEY | LWA_ALPHA);

	CDuiRect rcWnd;
	::GetWindowRect(*this, &rcWnd);
	rcWnd.Offset(-rcWnd.left, -rcWnd.top);
	rcWnd.right++; rcWnd.bottom++;
	HRGN hRgn = ::CreateRoundRectRgn(rcWnd.left, rcWnd.top, rcWnd.right, rcWnd.bottom, 5, 5);
	::SetWindowRgn(*this, hRgn, TRUE);
	::DeleteObject(hRgn);

// 	FadeIn();
}

/*******************************
** FunctionName：Notify
** @Param uMsg: 消息类型
** Comment:     处理事件通知
** return：
** Creator：    zwl
** Date：		2014-01-15
** Modifier：	 
** ModifyDate：  
** Version：    1.0.0
*******************************/
void CMainFrame::Notify(TNotifyUI & msg)
{
	if(msg.sType == DUI_MSGTYPE_WINDOWINIT)
	{
		OnPrepare();
	}
	if(msg.sType == DUI_MSGTYPE_CLICK)
	{		
		CHorSlidePageUI *pSlidePage = static_cast<CHorSlidePageUI*>(m_PaintManager.FindControl(_T("MainPage")));

		if(msg.pSender->GetName() == _T("BtnUpdate"))
		{
			if(pSlidePage)
			{
				pSlidePage->SelectItem(pSlidePage->GetItemIndex()+1);
			}
		}
		else if(msg.pSender->GetName() == _T("BtnOk"))
		{
			if(pSlidePage)
				pSlidePage->SelectItem(0);
		}
	}
}

// /*******************************
// ** FunctionName：OnCreate
// ** @Param uMsg:   消息类型
// ** @Param wParam：附加消息
// ** @Param lParam：附加消息
// ** @Param bHandled：
// ** Comment:     窗口创建消息响应
// ** return：     true :返回状态
// ** Creator：    zwl
// ** Date：		2014-01-15
// ** Modifier：	 
// ** ModifyDate：  
// ** Version：    1.0.0
// *******************************/

LRESULT CMainFrame::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	BOOL bHandled = 0;

	if(uMsg == WM_TIMER)
	{
		if (0 == OnTimer(uMsg, wParam, lParam, bHandled))
			return 0;
	}
	else if(uMsg == WM_NCLBUTTONDOWN)
	{
		m_PaintManager.SetFocus(NULL);
	}
	else if(uMsg == WM_NCLBUTTONDBLCLK)
	{
		BOOL bZoomed = ::IsZoomed(*this);
		if(bZoomed)
		{
			PostMessage(WM_SYSCOMMAND, SC_RESTORE);
		}
		else
		{
			PostMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
		}
	}

	return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CMainFrame::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	//处理键盘消息
	switch( uMsg ) 
	{
		case WM_KEYDOWN:
			{
				char sz = wParam;
				if (wParam == VK_ESCAPE)
				{
					PostMessage(WM_CLOSE);
					/*MessageBox(m_hWnd, _T("esc"), _T("cc"), MB_OK);*/
					return true;
				}
				else if(wParam == 'O')
				{
					if(GetKeyState(VK_CONTROL) < 0)
					{
						CFileDialog dlg(TRUE, NULL, NULL, OFN_NOTESTFILECREATE );
						dlg.DoModal();
					}
				}
				else if(wParam == VK_RETURN)
				{
					// 发送浏览消息
					if(m_pEdtAddr && m_pEdtAddr->IsFocused() && m_pBtnBrowser)
					{
						m_PaintManager.SendNotify(m_pBtnBrowser, DUI_MSGTYPE_CLICK);
					}
				}
			}
			break;
		case WM_SYSCHAR:
			{
				char sz = wParam;
			}
			break;
		case WM_SYSKEYDOWN:
			{
			}
			break;
	}
	return true;
}

 LRESULT CMainFrame::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
 {
 #if defined(WIN32) && !defined(UNDER_CE)
 	BOOL bZoomed = ::IsZoomed(*this);
 	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
 	if( ::IsZoomed(*this) != bZoomed )
 	{
 		// 切换最大化按钮和还原按钮的状态
 		if (m_pBtnMax && m_pBtnRestore)
 		{
 			m_pBtnMax->SetVisible(TRUE == bZoomed);       // 此处用表达式是为了避免编译器BOOL转换的警告
 			m_pBtnRestore->SetVisible(FALSE == bZoomed);
 		}
 	}
 #else
 	LRESULT lRes = WindowImplBase::HandleMessage(uMsg, wParam, lParam);
 #endif
 	return lRes;
 }

bool CMainFrame::OnBtnBrowser(void *lParam)
{
	TNotifyUI* pNotify = (TNotifyUI*)lParam;
	if(pNotify->sType == DUI_MSGTYPE_CLICK)
	{
		if(m_pWebClient && m_pEdtAddr)
		{
			m_pWebClient->Navigate2(m_pEdtAddr->GetText());
		}
	}

	return true;
}


bool CMainFrame::OnBtnClose(void *lParam)
{
	TNotifyUI* pNotify = (TNotifyUI*)lParam;
	if(pNotify->sType == DUI_MSGTYPE_CLICK)
	{
// 		if(m_bExit)
// 			return 0;
// 
// 		FadeOut();
		PostMessage(WM_CLOSE);
	}

	return true;
}

bool CMainFrame::OnBtnMin(void *lParam)
{
	TNotifyUI* pNotify = (TNotifyUI*)lParam;
	if(pNotify->sType == DUI_MSGTYPE_CLICK)
	{
		PostMessage(WM_SYSCOMMAND, SC_MINIMIZE);
	}

	return true;
}

bool CMainFrame::OnBtnMax(void *lParam)
{
	TNotifyUI* pNotify = (TNotifyUI*)lParam;
	if(pNotify->sType == DUI_MSGTYPE_CLICK)
	{
		PostMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
	}

	return true;
}

bool CMainFrame::OnBtnRestore(void *lParam)
{
	TNotifyUI* pNotify = (TNotifyUI*)lParam;
	if(pNotify->sType == DUI_MSGTYPE_CLICK)
	{
		PostMessage(WM_SYSCOMMAND, SC_RESTORE);
	}

	return true;
}

bool CMainFrame::OnBtnSkin(void *lParam)
{
	TNotifyUI* pNotify = (TNotifyUI*)lParam;
	if(pNotify->sType == DUI_MSGTYPE_CLICK)
	{
	}

	return true;
}

bool CMainFrame::OnBtnBack(void *lParam)
{
	TNotifyUI* pNotify = (TNotifyUI*)lParam;
	if(pNotify->sType == DUI_MSGTYPE_CLICK)
	{
		m_pWebClient->GoBack();	
	}

	return true;
}

bool CMainFrame::OnBtnForward(void *lParam)
{
	TNotifyUI* pNotify = (TNotifyUI*)lParam;
	if(pNotify->sType == DUI_MSGTYPE_CLICK)
	{
		m_pWebClient->GoForward();
	}

	return true;
}

bool CMainFrame::OnBtnRefresh(void *lParam)
{
	TNotifyUI* pNotify = (TNotifyUI*)lParam;
	if(pNotify->sType == DUI_MSGTYPE_CLICK)
	{
		m_pWebClient->Refresh();
	}

	return true;
}

bool CMainFrame::OnBtnHome(void *lParam)
{
	TNotifyUI* pNotify = (TNotifyUI*)lParam;
	if(pNotify->sType == DUI_MSGTYPE_CLICK)
	{

		if(m_pEdtAddr)
			m_pEdtAddr->SetText(m_pWebClient->GetHomePage());

		m_pWebClient->Navigate2(m_pWebClient->GetHomePage());
	}

	return true;
}

bool CMainFrame::OnBtnSearch(void *lParam)
{
	TNotifyUI* pNotify = (TNotifyUI*)lParam;
	if(pNotify->sType == DUI_MSGTYPE_CLICK)
	{
		
	}

	return true;
}

void CMainFrame::NewWindow3(IDispatch **pDisp, VARIANT_BOOL *&Cancel, DWORD dwFlags, BSTR bstrUrlContext, BSTR bstrUrl)
{
	*Cancel = TRUE;

	CString strText(bstrUrl);
	if(m_pEdtAddr)
		m_pEdtAddr->SetText(strText);

	m_pWebClient->Navigate2(strText);
}