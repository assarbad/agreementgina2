//{{AFX_INCLUDES()
#include "webbrowser2.h"
//}}AFX_INCLUDES
#if !defined(AFX_AGREEMENTDLG_H__6DBEA814_E5A9_4FDD_A03C_EBFC13F53965__INCLUDED_)
#define AFX_AGREEMENTDLG_H__6DBEA814_E5A9_4FDD_A03C_EBFC13F53965__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AgreementDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAgreementDlg dialog

class CAgreementDlg : public CDialog
{
// Construction
public:
	CAgreementDlg(CWnd* pParent = NULL);   // standard constructor
	~CAgreementDlg();   // standard destructor

// Dialog Data
	//{{AFX_DATA(CAgreementDlg)
	enum { IDD = IDD_AGREEMENTDLG_DIALOG };
	CStatic	m_StaticTimer;
	CProgressCtrl	m_Progress;
	CButton	m_CheckAgree;
	CButton	m_ButtonYes;
	CButton	m_ButtonNo;
	CWebBrowser2	m_IE;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAgreementDlg)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

public:
	void SetUrlOrText(LPCTSTR szURL);
	void SetErrorOrText(LPCTSTR szError);
private:
	CString m_sURL;
	CString m_sErrorURL;
	CToolTipCtrl m_tooltip;
	CBrush m_Green;
	CBrush m_Red;
	DWORD m_Timeout;
	void InitTooltips(CToolTipCtrl& tooltip);
	void UpdateTimerProgress(DWORD Timeout);

// Implementation
protected:

	/* 
	 * NOTE: standard implementation is wrong, it looks like:
	 *
	 * afx_msg void OnFileDownloadExplorer1(BOOL FAR* Cancel);
	 * 
	 * Change it like I did to reflect the real method of the interface.
	 */
	// Generated message map functions
	//{{AFX_MSG(CAgreementDlg)
	afx_msg void OnButtonNo();
	afx_msg void OnButtonYes();
	afx_msg void OnCheckAgree();
	virtual BOOL OnInitDialog();
	afx_msg void OnNewWindow2Explorer1(LPDISPATCH FAR* ppDisp, BOOL FAR* Cancel);
	afx_msg void OnFileDownloadExplorer1(BOOL FAR* ActiveDocument, BOOL FAR* Cancel);
	afx_msg void OnNavigateErrorExplorer1(LPDISPATCH pDisp, VARIANT FAR* URL, VARIANT FAR* Frame, VARIANT FAR* StatusCode, BOOL FAR* Cancel);
	afx_msg void OnTitleChangeExplorer1(LPCTSTR Text);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBeforeNavigate2Explorer1(LPDISPATCH pDisp, VARIANT FAR* URL, VARIANT FAR* Flags, VARIANT FAR* TargetFrameName, VARIANT FAR* PostData, VARIANT FAR* Headers, BOOL FAR* Cancel);
	afx_msg void OnDocumentCompleteExplorer1(LPDISPATCH pDisp, VARIANT FAR* URL);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AGREEMENTDLG_H__6DBEA814_E5A9_4FDD_A03C_EBFC13F53965__INCLUDED_)
