
// KuGouSkinParseDlg.h : 头文件
//

#pragma once


// CKuGouSkinParseDlg 对话框
class CKuGouSkinParseDlg : public CDialog
{
// 构造
public:
	CKuGouSkinParseDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_KUGOUSKINPARSE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 获取可执行文件的安装路径
	CString GetExePath(CString v_strExeName);
};
