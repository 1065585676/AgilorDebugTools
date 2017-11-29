
// AgilorDebugToolsDlg.h : 头文件
//

#pragma once

#define WM_YYMSG_APPEND_LOGBOX	WM_USER+2017
#define MAIN_WINDOW_NAME "AgilorDebugTools"
#define ACI_SERVER_NAME_DEFAULT "Agilor"

// CAgilorDebugToolsDlg 对话框
class CAgilorDebugToolsDlg : public CDialogEx
{
// 构造
public:
	CAgilorDebugToolsDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AGILORDEBUGTOOLS_DIALOG };
#endif

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
	afx_msg void OnBnClickedButtonAgilorAciConnDisconn();
	afx_msg LRESULT AppendTextToLogBox(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtonAgilorRtdbConn();
	afx_msg void OnBnClickedButtonAgilorRtdbDisconn();
	afx_msg void OnBnClickedButtonAgilorRtdbDisconnectAll();
	afx_msg void OnBnClickedButtonClearLogsBox();
	afx_msg void OnEnChangeEditLogs();
	afx_msg void OnBnClickedButtonAciRead();
	afx_msg void OnBnClickedButtonAciWrite();
	afx_msg void OnBnClickedButtonRtdbWrite();
};
