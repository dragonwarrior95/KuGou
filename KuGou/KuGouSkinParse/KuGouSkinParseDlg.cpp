
// KuGouSkinParseDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KuGouSkinParse.h"
#include "KuGouSkinParseDlg.h"

#include "SkinFile.h"


#pragma comment(lib, "advapi32")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CKuGouSkinParseDlg �Ի���




CKuGouSkinParseDlg::CKuGouSkinParseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKuGouSkinParseDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKuGouSkinParseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CKuGouSkinParseDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CKuGouSkinParseDlg ��Ϣ�������

BOOL CKuGouSkinParseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	// ��ȡ�ṷͼƬƤ��
	CString strExePath = GetExePath("");
	MessageBox(strExePath, strExePath,  0);
	char* pszExePath = NULL;
	pszExePath = strExePath.GetBuffer(0);
	strExePath.ReleaseBuffer();
	PathRemoveFileSpec(pszExePath) ;
	strExePath.Format(_T("%s\\kugou.skn"), pszExePath);
	CSkinFile skinFile;
	skinFile.SkinFileParse(strExePath);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CKuGouSkinParseDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CKuGouSkinParseDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CKuGouSkinParseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// ��ȡ��ִ���ļ��İ�װ·��
CString CKuGouSkinParseDlg::GetExePath(CString v_strExeName)
{		
	// Dynamic allocation will be used.
	HKEY hKey;
	TCHAR szExePath[MAX_PATH];
	memset(szExePath,0,sizeof(szExePath));
	DWORD dwBufLen = MAX_PATH;
	LONG lRet;

	// �����Ǵ�ע���, ֻ�д򿪺�������������� 
	lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE,					// Ҫ�򿪵ĸ��� 
						TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\�ṷ����"),	// Ҫ�򿪵����Ӽ� 
						0,									// ���һ��ҪΪ0 
						KEY_QUERY_VALUE,					//  ָ���򿪷�ʽ,��Ϊ�� 
						&hKey);								// �������ؾ�� 

	if(lRet != ERROR_SUCCESS)// �ж��Ƿ�򿪳ɹ� 
		return _T("");

	//���濪ʼ��ѯ 
	lRet = RegQueryValueEx( hKey,					// ��ע���ʱ���صľ�� 
							TEXT("UninstallString"),		//Ҫ��ѯ������,qq��װĿ¼��¼��������� 
							NULL,					// һ��ΪNULL����0 
							NULL,
							(LPBYTE)szExePath,	// ����Ҫ�Ķ����������� 
							&dwBufLen);

	if(lRet != ERROR_SUCCESS)  // �ж��Ƿ��ѯ�ɹ� 
	{
		RegCloseKey(hKey);
		return _T("");
	}
	
	RegCloseKey(hKey);

	return szExePath;
}
