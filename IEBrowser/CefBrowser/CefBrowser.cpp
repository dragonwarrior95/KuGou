
// CefBrowser.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "CefBrowser.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCefBrowserApp

BEGIN_MESSAGE_MAP(CCefBrowserApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCefBrowserApp ����

CCefBrowserApp::CCefBrowserApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CCefBrowserApp ����

CCefBrowserApp theApp;


// CCefBrowserApp ��ʼ��

BOOL CCefBrowserApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	//////////////////////////////////////////////////////////////////////////
	/// Add your codes here.
// 	CCefBrowserDlg dlg;
// 	m_pMainWnd = &dlg;
	// 	INT_PTR nResponse = dlg.DoModal();
// 	if (WebDrawInit() != -1) return 0;

	HRESULT Hr = ::CoInitialize(NULL);
	if( FAILED(Hr) ) 
		return 0;

	CPaintManagerUI::SetInstance(m_hInstance);
#ifdef __STATIC_LIB__
	CPaintManagerUI::SetResourceZip(CPaintManagerUI::GetInstancePath()+_T("Skins"));
#else
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath()+_T("Skins"));
#endif

	INT_PTR nResponse = 0;
	g_pMainFrame = new CMainFrame(_T("MainFrame.xml"));
	g_pMainFrame->Create(NULL, _T("CefBrowser"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	nResponse = g_pMainFrame->ShowModal();
	::CoUninitialize();
// 	WebDrawFinal();

	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
