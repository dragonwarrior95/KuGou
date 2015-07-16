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

CMainFrame::CMainFrame(LPCTSTR v_pStrSkinPath):CXMLWnd(v_pStrSkinPath)
{
	m_pStrSkinPath = v_pStrSkinPath;

	m_pBtnClose		= NULL;
	m_pBtnMin		= NULL;
	m_pBtnMax		= NULL;
	m_pBtnRestore	= NULL;

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


	//阴影效果
	m_wndShadow.Create(m_hWnd);
	m_wndShadow.SetSize(7);
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
// 			PostMessage(WM_CLOSE);
			::PostQuitMessage(0L);
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
	}

	return 0;
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
		return OnTimer(uMsg, wParam, lParam, bHandled);
	}
	else if(uMsg == WM_NCLBUTTONDOWN)
	{
		m_PaintManager.SetFocus(NULL);
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
// 					PostMessage(WM_CLOSE);
					::PostQuitMessage(0L);
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
	if (wParam == SC_CLOSE)
	{
		bHandled = TRUE;
		::PostQuitMessage(0L);
		return 0;
	}
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
	return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
#endif
	return lRes;
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