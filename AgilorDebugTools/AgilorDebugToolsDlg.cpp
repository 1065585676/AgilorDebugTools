
// AgilorDebugToolsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AgilorDebugTools.h"
#include "AgilorDebugToolsDlg.h"
#include "afxdialogex.h"

#include "ACI_H.H"
#include "DeviceRtdbAPI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAgilorDebugToolsDlg �Ի���



CAgilorDebugToolsDlg::CAgilorDebugToolsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_AGILORDEBUGTOOLS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAgilorDebugToolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAgilorDebugToolsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_AGILOR_ACI_CONN_DISCONN, &CAgilorDebugToolsDlg::OnBnClickedButtonAgilorAciConnDisconn)
	ON_MESSAGE(WM_YYMSG_APPEND_LOGBOX, &CAgilorDebugToolsDlg::AppendTextToLogBox)
	ON_BN_CLICKED(IDC_BUTTON_AGILOR_RTDB_CONN, &CAgilorDebugToolsDlg::OnBnClickedButtonAgilorRtdbConn)
	ON_BN_CLICKED(IDC_BUTTON_AGILOR_RTDB_DISCONN, &CAgilorDebugToolsDlg::OnBnClickedButtonAgilorRtdbDisconn)
	ON_BN_CLICKED(IDC_BUTTON_AGILOR_RTDB_DISCONNECT_ALL, &CAgilorDebugToolsDlg::OnBnClickedButtonAgilorRtdbDisconnectAll)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_LOGS_BOX, &CAgilorDebugToolsDlg::OnBnClickedButtonClearLogsBox)
	ON_EN_CHANGE(IDC_EDIT_LOGS, &CAgilorDebugToolsDlg::OnEnChangeEditLogs)
	ON_BN_CLICKED(IDC_BUTTON_ACI_READ, &CAgilorDebugToolsDlg::OnBnClickedButtonAciRead)
	ON_BN_CLICKED(IDC_BUTTON_ACI_WRITE, &CAgilorDebugToolsDlg::OnBnClickedButtonAciWrite)
	ON_BN_CLICKED(IDC_BUTTON_RTDB_WRITE, &CAgilorDebugToolsDlg::OnBnClickedButtonRtdbWrite)
END_MESSAGE_MAP()


// CAgilorDebugToolsDlg ��Ϣ�������

BOOL CAgilorDebugToolsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	((CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS_AGILOR_ACI_IP))->SetWindowText("127.0.0.1");
	((CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS_AGILOR_RTDB_IP))->SetWindowText("127.0.0.1");
	((CEdit *)GetDlgItem(IDC_EDIT_AGILOR_ACI_PORT))->SetWindowText("900");
	((CEdit *)GetDlgItem(IDC_EDIT_AGILOR_RTDB_PORT))->SetWindowText("700");

	((CComboBox *)GetDlgItem(IDC_LIST_AGILOR_VALUE_TYPE))->AddString("Long");
	((CComboBox *)GetDlgItem(IDC_LIST_AGILOR_VALUE_TYPE))->AddString("Float");
	((CComboBox *)GetDlgItem(IDC_LIST_AGILOR_VALUE_TYPE))->AddString("String");
	((CComboBox *)GetDlgItem(IDC_LIST_AGILOR_VALUE_TYPE))->AddString("Bool");
	((CComboBox *)GetDlgItem(IDC_LIST_AGILOR_VALUE_TYPE))->SelectString(0, "Long");

	((CButton *)GetDlgItem(IDC_CHECK_ACI_WRITE_CTRL))->SetCheck(true);

	((CEdit *)GetDlgItem(IDC_EDIT_AUTO_CLEAR_ROWS_COUNT))->SetWindowText("50");
	((CButton *)GetDlgItem(IDC_CHECK_AUTO_CLEAR_CTRL))->SetCheck(true);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CAgilorDebugToolsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAgilorDebugToolsDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CAgilorDebugToolsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void __stdcall myOnNewTagNodeArriveFn(LPTAGNODE lptag, LPCTSTR deviceName) {
	CString logInfo;
	logInfo.Format("---myOnNewTagNodeArriveFn---\r\n");
	::SendMessage(::FindWindow(NULL, MAIN_WINDOW_NAME), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&logInfo);
}
void __stdcall myOnRemoveTagNode(LPTAGNODE lptag, LPCTSTR deviceName) {
	CString logInfo;
	logInfo.Format("---myOnRemoveTagNode---\r\n");
	::SendMessage(::FindWindow(NULL, MAIN_WINDOW_NAME), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&logInfo);
}
void __stdcall myOnSetDeviceTagValue(LPTAGVALUELOCAL lptagvalue, LPCTSTR deviceName) {
	CString logInfo;
	switch (lptagvalue->cTagType)
	{
	case 'R':
		logInfo.Format("Received, SourceTag:%s, TagType:Float, Value: %f\r\n", lptagvalue->szTagSource, lptagvalue->fValue);
		break;
	case 'S':
		logInfo.Format("Received, SourceTag:%s, TagType:String, Value: %s\r\n", lptagvalue->szTagSource, lptagvalue->szValue);
		break;
	case 'L':
		logInfo.Format("Received, SourceTag:%s, TagType:Long, Value: %ld\r\n", lptagvalue->szTagSource, lptagvalue->lValue);
		break;
	case 'B':
		logInfo.Format("Received, SourceTag:%s, TagType:Bool, Value: %d\r\n", lptagvalue->szTagSource, lptagvalue->bValue);
		break;
	default:
		logInfo.Format("Received, Unknown TagType: %c", lptagvalue->cTagType);
		break;
	}
	::SendMessage(::FindWindow(NULL, MAIN_WINDOW_NAME), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&logInfo);

	DRTDB_MD_SendNewValues((LPSTR)deviceName, lptagvalue, 1);
	DRTDB_MD_Flush((LPSTR)deviceName);
}
void __stdcall myOnGetDeviceTagValue(LPTAGNODE lptag, LPCTSTR deviceName) {
	CString logInfo;
	logInfo.Format("---myOnGetDeviceTagValue---\r\n");
	::SendMessage(::FindWindow(NULL, MAIN_WINDOW_NAME), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&logInfo);
}

void CAgilorDebugToolsDlg::OnBnClickedButtonAgilorAciConnDisconn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString logInfo, aciIp, aciPort;
	CString btnName;
	((CButton *)GetDlgItem(IDC_BUTTON_AGILOR_ACI_CONN_DISCONN))->GetWindowText(btnName);
	if (btnName == "Connect") {
		if (!Agcn_Startup()) {
			logInfo.Format("Agcn_Startup Failed.\r\n");
			::SendMessage(::FindWindow(NULL, MAIN_WINDOW_NAME), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&logInfo);
			return;
		}
		if (!Agcn_CreateNode(ACI_SERVER_NAME_DEFAULT, this->m_hWnd, 0, FALSE)) {
			logInfo.Format("Agcn_CreateNode Failed.\r\n");
			::SendMessage(::FindWindow(NULL, MAIN_WINDOW_NAME), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&logInfo);
			return;
		}
		((CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS_AGILOR_ACI_IP))->GetWindowText(aciIp);
		if (Agcn_Connect(ACI_SERVER_NAME_DEFAULT, aciIp, "YYTEST", "YYTEST") != 0) {
			logInfo.Format("Agcn_Connect Failed.\r\n");
			::SendMessage(::FindWindow(NULL, MAIN_WINDOW_NAME), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&logInfo);
			return;
		}
		// devices
		long nRs = Agpt_QueryDeviceInfo(ACI_SERVER_NAME_DEFAULT);
		if (nRs > 0) {
			long nTagID;
			DEV_INFO di;
			CString str;
			while (Agpt_EnumDeviceInfo(nRs, &nTagID, &di)) {
				str.Format(_T("%s | %d\r\n"), di.szDeviceName, di.bIsOnline);
				((CComboBox *)GetDlgItem(IDC_COMBO_AGILOR_ALL_DEVICES))->AddString(di.szDeviceName);
				::SendMessage(::FindWindow(NULL, MAIN_WINDOW_NAME), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&str);
			}
			((CComboBox *)GetDlgItem(IDC_COMBO_AGILOR_ALL_DEVICES))->SetCurSel(0);
		}
		((CButton *)GetDlgItem(IDC_BUTTON_AGILOR_ACI_CONN_DISCONN))->SetWindowText("Disconnect");
		logInfo.Format("Connect finished.\r\n");
		::SendMessage(::FindWindow(NULL, MAIN_WINDOW_NAME), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&logInfo);
	}
	else if (btnName == "Disconnect") {
		if (Agcn_Disconnect(ACI_SERVER_NAME_DEFAULT) != 0) {
			logInfo.Format("Agcn_Disconnect Failed.\r\n");
			::SendMessage(::FindWindow(NULL, MAIN_WINDOW_NAME), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&logInfo);
		}
		Agcn_RemoveNode(ACI_SERVER_NAME_DEFAULT);
		Agcn_Cleanup();
		int count = ((CComboBox *)GetDlgItem(IDC_COMBO_AGILOR_ALL_DEVICES))->GetCount();
		while (count--) {
			((CComboBox *)GetDlgItem(IDC_COMBO_AGILOR_ALL_DEVICES))->DeleteString(0);
		}
		((CButton *)GetDlgItem(IDC_BUTTON_AGILOR_ACI_CONN_DISCONN))->SetWindowText("Connect");
		logInfo.Format("Disconnect finished.\r\n");
		::SendMessage(::FindWindow(NULL, MAIN_WINDOW_NAME), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&logInfo);
	}
}

LRESULT CAgilorDebugToolsDlg::AppendTextToLogBox(WPARAM wParam, LPARAM lParam)
{
	CString msg = CString(((CString *)lParam)->GetString());
	int nLength = ((CEdit *)GetDlgItem(IDC_EDIT_LOGS))->SendMessage(WM_GETTEXTLENGTH);
	((CEdit *)GetDlgItem(IDC_EDIT_LOGS))->SetSel(nLength, nLength);
	((CEdit *)GetDlgItem(IDC_EDIT_LOGS))->ReplaceSel(msg);
	return 0;
}

void CAgilorDebugToolsDlg::OnBnClickedButtonAgilorRtdbConn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString logInfo;
	CString rtdbIp, rtdbPort, deviceName;
	GetDlgItem(IDC_IPADDRESS_AGILOR_RTDB_IP)->GetWindowText(rtdbIp);
	GetDlgItem(IDC_EDIT_AGILOR_RTDB_PORT)->GetWindowText(rtdbPort);
	GetDlgItem(IDC_COMBO_AGILOR_ALL_DEVICES)->GetWindowText(deviceName);
	int res = DRTDB_RegisterDevice((LPSTR)(LPCSTR)rtdbIp, atoi(rtdbPort), (LPSTR)(LPCSTR)deviceName);
	if (res >= 0) {
		DRTDB_MD_SetCallBackFunction((LPSTR)(LPCSTR)deviceName, myOnNewTagNodeArriveFn, myOnRemoveTagNode, myOnSetDeviceTagValue, myOnGetDeviceTagValue);
		logInfo.Format("Register device:%s success.\r\n", deviceName);
		((CComboBox *)GetDlgItem(IDC_COMBO_AGILOR_RTDB_CONN_DEVICES))->AddString(deviceName);
		((CComboBox *)GetDlgItem(IDC_COMBO_AGILOR_RTDB_CONN_DEVICES))->SelectString(0, deviceName);
	}
	else {
		logInfo.Format("Register device:%s error.\r\n", deviceName);
	}
	::SendMessage(::FindWindow(NULL, MAIN_WINDOW_NAME), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&logInfo);
}


void CAgilorDebugToolsDlg::OnBnClickedButtonAgilorRtdbDisconn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString logInfo;
	CString deviceName;
	((CComboBox *)GetDlgItem(IDC_COMBO_AGILOR_RTDB_CONN_DEVICES))->GetWindowText(deviceName);
	if (DRTDB_MD_UnregisterDevice((LPSTR)(LPCSTR)deviceName, "Stop DA")) {
		logInfo.Format("Unregister device:%s error.\r\n", deviceName);
	}
	else {
		logInfo.Format("Unregister device:%s finished.\r\n", deviceName);
		((CComboBox *)GetDlgItem(IDC_COMBO_AGILOR_RTDB_CONN_DEVICES))->DeleteString(((CComboBox *)GetDlgItem(IDC_COMBO_AGILOR_RTDB_CONN_DEVICES))->FindString(0, deviceName));
		((CComboBox *)GetDlgItem(IDC_COMBO_AGILOR_RTDB_CONN_DEVICES))->SetCurSel(0);
	}
	::SendMessage(::FindWindow(NULL, MAIN_WINDOW_NAME), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&logInfo);
}


void CAgilorDebugToolsDlg::OnBnClickedButtonAgilorRtdbDisconnectAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString logInfo;
	int  excTimes = ((CComboBox *)GetDlgItem(IDC_COMBO_AGILOR_RTDB_CONN_DEVICES))->GetCount();
	while (excTimes--)
	{
		OnBnClickedButtonAgilorRtdbDisconn();
	}
	logInfo.Format("Unregister all device finished.\r\n");
	::SendMessage(::FindWindow(NULL, MAIN_WINDOW_NAME), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&logInfo);
}


void CAgilorDebugToolsDlg::OnBnClickedButtonClearLogsBox()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT_LOGS)->SetWindowText("");
}


void CAgilorDebugToolsDlg::OnEnChangeEditLogs()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString rowsLimit;
	GetDlgItem(IDC_EDIT_AUTO_CLEAR_ROWS_COUNT)->GetWindowText(rowsLimit);
	if (((CButton *)GetDlgItem(IDC_CHECK_AUTO_CLEAR_CTRL))->GetCheck() &&
		((CEdit *)GetDlgItem(IDC_EDIT_LOGS))->GetLineCount() >= atol(rowsLimit)) {
		GetDlgItem(IDC_EDIT_LOGS)->SetWindowText("");
	}
}


void CAgilorDebugToolsDlg::OnBnClickedButtonAciRead()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString logInfo;
	CString tagName;
	GetDlgItem(IDC_EDIT_VALUE_CTRL_NAME)->GetWindowText(tagName);
	TAG_INFO tagInfo;
	if (Agpt_GetTagInfo(CString(ACI_SERVER_NAME_DEFAULT) + "." + tagName, &tagInfo)) {
		logInfo.Format("Agpt_GetTagInfo failed.\r\n");
		::SendMessage(::FindWindow(NULL, MAIN_WINDOW_NAME), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&logInfo);
		return;
	}

	switch (tagInfo.TagType)
	{
	case 'R':
		logInfo.Format("TagName:%s, SourceTag:%s, TagType:%c, Value: %f\r\n", tagInfo.TagName, tagInfo.SourceTag, tagInfo.TagType, tagInfo.rval);
		break;
	case 'S':
		logInfo.Format("TagName:%s, SourceTag:%s, TagType:%c, Value: %s\r\n", tagInfo.TagName, tagInfo.SourceTag, tagInfo.TagType, tagInfo.sval);
		break;
	case 'L':
		logInfo.Format("TagName:%s, SourceTag:%s, TagType:%c, Value: %ld\r\n", tagInfo.TagName, tagInfo.SourceTag, tagInfo.TagType, tagInfo.lval);
		break;
	case 'B':
		logInfo.Format("TagName:%s, SourceTag:%s, TagType:%c, Value: %d\r\n", tagInfo.TagName, tagInfo.SourceTag, tagInfo.TagType, tagInfo.bval);
		break;
	default:
		break;
	}
	::SendMessage(::FindWindow(NULL, MAIN_WINDOW_NAME), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&logInfo);
}


void CAgilorDebugToolsDlg::OnBnClickedButtonAciWrite()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString logInfo;
	CString tagName;
	GetDlgItem(IDC_EDIT_VALUE_CTRL_NAME)->GetWindowText(tagName);

	CString newValue;
	GetDlgItem(IDC_EDIT_AGILOR_VALUE_CTRL_VALUE)->GetWindowText(newValue);

	VALUE val;
	CString tagType;
	GetDlgItem(IDC_LIST_AGILOR_VALUE_TYPE)->GetWindowText(tagType);
	if (tagType == "Long") {
		val.Type = 'L';
		val.lval = atol(newValue);
	}
	else if (tagType == "Bool") {
		val.Type = 'B';
		val.bval = atoi(newValue);
	}
	else if (tagType == "Float") {
		val.Type = 'R';
		val.rval = atof(newValue);
	}
	else if (tagType == "String") {
		val.Type = 'S';
		strcpy(val.sval, newValue);
	}
	else {
		logInfo.Format("Error Value Type: %s\r\n", tagType);
		::SendMessage(::FindWindow(NULL, MAIN_WINDOW_NAME), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&logInfo);
		return;
	}
	if (Agda_SetTagValue(CString(ACI_SERVER_NAME_DEFAULT) + "." + tagName, &val, ((CButton *)GetDlgItem(IDC_CHECK_ACI_WRITE_CTRL))->GetCheck(), "Set Value From AgilorACITool.") != 0) {
		logInfo.Format("Set Value Failed\r\n");
		::SendMessage(::FindWindow(NULL, MAIN_WINDOW_NAME), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&logInfo);
		return;
	}
	logInfo.Format("Set Value Finished. TagName: %s, TagType: %s, Value: %s\r\n", CString(ACI_SERVER_NAME_DEFAULT) + "." + tagName, tagType, newValue);
	::SendMessage(::FindWindow(NULL, MAIN_WINDOW_NAME), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&logInfo);
}


void CAgilorDebugToolsDlg::OnBnClickedButtonRtdbWrite()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString logInfo;
	logInfo.Format("No Work, Replace OP: Uncheck ACI Write Ctrl, Click ACI Write.");
	::SendMessage(::FindWindow(NULL, MAIN_WINDOW_NAME), WM_YYMSG_APPEND_LOGBOX, 0, (LPARAM)&logInfo);
}
