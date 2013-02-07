#if !defined(AFX_SIMPLETASKMAN_H__22EB8B38_C3A2_49FC_ADD9_B0F511CD6289__INCLUDED_)
#define AFX_SIMPLETASKMAN_H__22EB8B38_C3A2_49FC_ADD9_B0F511CD6289__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SimpleTaskman.h : header file
//

#include "ProcessLB.h"

/////////////////////////////////////////////////////////////////////////////
// CSimpleTaskman dialog

class CSimpleTaskman : public CDialog
{
// Construction
public:
	CSimpleTaskman(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSimpleTaskman)
	enum { IDD = IDD_DIALOG_TASKMAN };
	CProcessLB	m_Processlist;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleTaskman)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSimpleTaskman)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnButtonRefresh();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLETASKMAN_H__22EB8B38_C3A2_49FC_ADD9_B0F511CD6289__INCLUDED_)
