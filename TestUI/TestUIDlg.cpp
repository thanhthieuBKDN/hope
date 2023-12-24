
// TestUIDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "TestUI.h"
#include "TestUIDlg.h"
#include "afxdialogex.h"
#include <Windows.h>
#include <atlstr.h>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CTestUIDlg dialog



CTestUIDlg::CTestUIDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TESTUI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NAME, edt_name_);
	DDX_Control(pDX, IDC_EDIT_AGE, m_edt_age_);
	DDX_Control(pDX, IDC_COMBOX_SEX, combo_sex_);
	DDX_Control(pDX, IDC_LIST_INFO, list_box_info_);
}

BEGIN_MESSAGE_MAP(CTestUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ADD, &CTestUIDlg::OnBnClickedBtnAdd)
END_MESSAGE_MAP()


// CTestUIDlg message handlers

BOOL CTestUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	//remove window borders and title bar
	ModifyStyleEx(0, WS_EX_TOPMOST);
	ModifyStyle(WS_CAPTION | WS_THICKFRAME, 0);

	//get screen resoltion
	int iScreenWid = GetSystemMetrics(SM_CXSCREEN);
	int iScreenHeigh = GetSystemMetrics(SM_CYSCREEN);

	SetWindowPos(NULL, 0, 0, iScreenWid, iScreenHeigh, SWP_NOZORDER);
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	combo_sex_.AddString(_T("Male"));
	combo_sex_.AddString(_T("Female"));

	TCHAR lpTargetPath[5000];
	DWORD test;
	bool gotPort = 0; //in case the port

	for (int i = 0; i < 255; i++)
	{
		CString str;
		str.Format(_T("%d"), i);
		CString ComName = CString("COM") + CString(str);
		//test = QueryDosDevice(ComName, (LPSTR) lpTargetPath, 5000);
		test = QueryDosDevice(ComName, lpTargetPath, 5000);
		// Test the return value and error if any
		if (test != 0) //QueryDosDevice returns zero if it didn't find an object
		{
			combo_sex_.AddString((CString)ComName); // add to the ComboBox
			gotPort = 1; // found port
		}

		if (::GetLastError() == ERROR_INSUFFICIENT_BUFFER)
		{
			lpTargetPath[5000]; // in case the buffer got filled, increase size of the buffer.
			continue;
		}
	}
	CString strr = L"heeelgfd";
	std::string str = CT2A(strr);


	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestUIDlg::OnBnClickedBtnAdd()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString strName;
	edt_name_.GetWindowTextW(strName);
	//edt_name_.GetLine(0, strName, 9);
	CString strAge;
	m_edt_age_.GetWindowTextW(strAge);
	CStringA x;
	CString strSex;
	int idx = combo_sex_.GetCurSel();
	combo_sex_.GetLBText(idx, strSex);

	CString str_info = _T(" ");
	str_info = strName + _T(" ");
	str_info += strAge + _T(" ");
	str_info += strSex;

	list_box_info_.AddString(str_info);

}
