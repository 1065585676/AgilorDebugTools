
// AgilorDebugToolsDlg.h : ͷ�ļ�
//

#pragma once

#define WM_YYMSG_APPEND_LOGBOX	WM_USER+2017
#define MAIN_WINDOW_NAME "AgilorDebugTools"
#define ACI_SERVER_NAME_DEFAULT "Agilor"

// CAgilorDebugToolsDlg �Ի���
class CAgilorDebugToolsDlg : public CDialogEx
{
// ����
public:
	CAgilorDebugToolsDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AGILORDEBUGTOOLS_DIALOG };
#endif

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
