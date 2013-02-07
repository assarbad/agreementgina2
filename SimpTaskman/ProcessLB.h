#if !defined(AFX_PROCESSLB_H__5F5726EA_E4DA_4461_9F48_22539E1EC112__INCLUDED_)
#define AFX_PROCESSLB_H__5F5726EA_E4DA_4461_9F48_22539E1EC112__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProcessLB.h : header file
//

#include "Tasklist.h"

/////////////////////////////////////////////////////////////////////////////
// CProcessLB window

class CProcessLB : public CListBox
{
// Construction
public:
	CProcessLB();
	virtual int VKeyToItem( UINT nKey, UINT nIndex );
	void SetFixedFont();
	void RefreshList();
private:
	CTasklist m_Tasklist;
	CFont font;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProcessLB)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CProcessLB();

	// Generated message map functions
protected:
	//{{AFX_MSG(CProcessLB)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROCESSLB_H__5F5726EA_E4DA_4461_9F48_22539E1EC112__INCLUDED_)
