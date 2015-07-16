
// IEBrowser.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "IEBrowser.h"
#include "MainFrame.h"
#include "WndShadow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIEBrowserApp

BEGIN_MESSAGE_MAP(CIEBrowserApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CIEBrowserApp ����

CIEBrowserApp::CIEBrowserApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CIEBrowserApp ����

CIEBrowserApp theApp;


// CIEBrowserApp ��ʼ��

BOOL CIEBrowserApp::InitInstance()
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

// 	CIEBrowserDlg dlg;
// 	m_pMainWnd = &dlg;
// 	INT_PTR nResponse = dlg.DoModal();
// 	CWndShadow::Initialize(m_hInstance);

	HRESULT Hr = ::CoInitialize(NULL);
	if( FAILED(Hr) ) 
		return 0;

	CPaintManagerUI::SetInstance(m_hInstance);
#ifdef __STATIC_LIB__
	CPaintManagerUI::SetResourceZip(CPaintManagerUI::GetInstancePath()+_T("Skins"));
#else
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath()+_T("Skins"));
#endif
// 	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath()+_T("Update"));

	INT_PTR nResponse = 0;


	g_pMainFrame = new CMainFrame(_T("MainFrame.xml"));
// 	g_pMainFrame = new CMainFrame(_T("Main.xml"));z
	g_pMainFrame->Create(NULL, _T("Update"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	nResponse = g_pMainFrame->ShowModal();


	::CoUninitialize();


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
