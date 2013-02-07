// SimpTaskmanDlg.h : header file
//

#if !defined(AFX_SIMPTASKMANDLG_H__1101FB33_972C_42F7_9981_CF621BFDD7C7__INCLUDED_)
#define AFX_SIMPTASKMANDLG_H__1101FB33_972C_42F7_9981_CF621BFDD7C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSimpTaskmanDlg dialog

class CSimpTaskmanDlg : public CDialog
{
// Construction
public:
	CSimpTaskmanDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSimpTaskmanDlg)
	enum { IDD = IDD_SIMPTASKMAN_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpTaskmanDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSimpTaskmanDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPTASKMANDLG_H__1101FB33_972C_42F7_9981_CF621BFDD7C7__INCLUDED_)
