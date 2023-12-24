
// TestUIDlg.h : header file
//

#pragma once


// CTestUIDlg dialog
class CTestUIDlg : public CDialogEx
{
// Construction
public:
	CTestUIDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit edt_name_;
	CEdit m_edt_age_;
	CComboBox combo_sex_;
	CListBox list_box_info_;
	afx_msg void OnBnClickedBtnAdd();
};
