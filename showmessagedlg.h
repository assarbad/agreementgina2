//{{AFX_INCLUDES()
#include "webbrowser2.h"
//}}AFX_INCLUDES
#if !defined(AFX_CShowMessageDlg_H__357D05CC_2FBE_45AF_B08F_E74DDB130E27__INCLUDED_)
#define AFX_CShowMessageDlg_H__357D05CC_2FBE_45AF_B08F_E74DDB130E27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShowMessageDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShowMessageDlg dialog

class CShowMessageDlg : public CDialog
{
// Construction
public:
	CShowMessageDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CShowMessageDlg)
	enum { IDD = IDD_SHOWMESSAGEDLG };
	CWebBrowser2	m_IE;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowMessageDlg)
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
	//{{AFX_MSG(CShowMessageDlg)
	afx_msg void OnNavigateErrorExplorer1(LPDISPATCH pDisp, VARIANT FAR* URL, VARIANT FAR* Frame, VARIANT FAR* StatusCode, BOOL FAR* Cancel);
	afx_msg void OnFileDownloadExplorer1(BOOL FAR* ActiveDocument, BOOL FAR* Cancel);
	afx_msg void OnNewWindow2Explorer1(LPDISPATCH FAR* ppDisp, BOOL FAR* Cancel);
	afx_msg void OnTitleChangeExplorer1(LPCTSTR Text);
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnButtonOk();
	afx_msg void OnBeforeNavigate2Explorer1(LPDISPATCH pDisp, VARIANT FAR* URL, VARIANT FAR* Flags, VARIANT FAR* TargetFrameName, VARIANT FAR* PostData, VARIANT FAR* Headers, BOOL FAR* Cancel);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CShowMessageDlg_H__357D05CC_2FBE_45AF_B08F_E74DDB130E27__INCLUDED_)
