
// KuGouSkinParseDlg.h : ͷ�ļ�
//

#pragma once


// CKuGouSkinParseDlg �Ի���
class CKuGouSkinParseDlg : public CDialog
{
// ����
public:
	CKuGouSkinParseDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_KUGOUSKINPARSE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// ��ȡ��ִ���ļ��İ�װ·��
	CString GetExePath(CString v_strExeName);
};
