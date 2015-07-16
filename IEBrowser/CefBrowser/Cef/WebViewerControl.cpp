#include "stdafx.h"
#include "WebViewerControl.h"

CWebViewerControl::CWebViewerControl(void)
{
	m_pWebDraw = NULL;
	m_pWebBrowserProvider = NULL;
}

CWebViewerControl::~CWebViewerControl(void)
{
}

void CWebViewerControl::PaintBkImage( HDC hDC )
{
	if (m_pWebDraw)
		m_pWebDraw->DoPaint(hDC, m_rcPaint);
}

void CWebViewerControl::SetWebDraw( IWebDraw * pWebDraw)
{
	m_pWebDraw = pWebDraw;
	m_pWebDraw->SetPos(GetPos());
}

void CWebViewerControl::SetPos( RECT rc )
{
	__super::SetPos(rc);
  	if (m_pWebDraw)
  		m_pWebDraw->SetPos(GetPos());
	if (m_pWebBrowserProvider)
	{
		CefWindowHandle hwnd = m_pWebBrowserProvider->GetBrowser()->GetWindowHandle();
		if (hwnd)
			::SetWindowPos(hwnd, 0, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top, SWP_NOZORDER);
	}
}

void CWebViewerControl::DoEvent( TEventUI& event )
{
	if( event.Type == UIEVENT_SETCURSOR )
	{
		if (m_pWebDraw)
			m_pWebDraw->SetCursor();
		return;
	}
	if( event.Type == UIEVENT_SETFOCUS ) 
	{
		if (m_pWebDraw)
			m_pWebDraw->SetFocus(true);
		m_bFocused = true;
		Invalidate();
		return;
	}
	if( event.Type == UIEVENT_KILLFOCUS ) 
	{
		if (m_pWebDraw)
			m_pWebDraw->SetFocus(false);
		m_bFocused = false;
		Invalidate();
		return;
	}
}

UINT CWebViewerControl::GetControlFlags() const
{
	 return  IsEnabled() ? UIFLAG_SETCURSOR : 0;
}

void CWebViewerControl::SetChildWnd( CWebBrowserProvider *pWebBrowserProvider )
{
	m_pWebBrowserProvider = pWebBrowserProvider;
}

void CWebViewerControl::PaintText( HDC hDC )
{
	RECT rc = m_rcItem;
	rc.left += 10;
	rc.top += 10;
	CRenderEngine::DrawText(hDC, m_pManager, rc, _T("Cef1Demo QQ:talkba@qq.com"), 0xff00ff00, 0, DT_SINGLELINE);
}
