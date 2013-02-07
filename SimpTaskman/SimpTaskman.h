// SimpTaskman.h : main header file for the SIMPTASKMAN application
//

#if !defined(AFX_SIMPTASKMAN_H__FD32D779_5108_4332_87AA_E26D5517B12E__INCLUDED_)
#define AFX_SIMPTASKMAN_H__FD32D779_5108_4332_87AA_E26D5517B12E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSimpTaskmanApp:
// See SimpTaskman.cpp for the implementation of this class
//

#include <Ntsecapi.h>
#include "Tasklist.h"

class CSimpTaskmanApp : public CWinApp
{
public:
	CSimpTaskmanApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpTaskmanApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSimpTaskmanApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPTASKMAN_H__FD32D779_5108_4332_87AA_E26D5517B12E__INCLUDED_)
