#pragma once

class CWebViewerControl : public CControlUI
{
public:
	CWebViewerControl(void);
	~CWebViewerControl(void);

	UINT GetControlFlags() const;

// 	void SetWebDraw(IWebDraw *);
// 	void SetChildWnd(CWebBrowserProvider *pWebBrowserProvider);
	void PaintBkImage(HDC hDC);
	void PaintText(HDC hDC);
	void SetPos(RECT rc);
	void DoEvent(TEventUI& event);
	void OSRSetFocus(bool bFocus);

protected:
// 	IWebDraw *m_pWebDraw;
// 	CWebBrowserProvider	 *m_pWebBrowserProvider;
};

