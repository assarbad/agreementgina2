/******************************************************************************
 ******************************************************************************
 ***                                                                        ***
 ***   Agreement dialog class implementation.                               ***
 ***                                                                        ***
 ***                                                                        ***
 ******************************************************************************
 ******************************************************************************

                                 _\\|//_
                                (` * * ')
 ______________________________ooO_(_)_Ooo_____________________________________
 ******************************************************************************
 ******************************************************************************
 ***                                                                        ***
 ***                Copyright (c) 2003 - 2005 by -=Assarbad=-               ***
 ***                                                                        ***
 ***                                                                        ***
 ***   CONTACT TO THE AUTHOR(S):                                            ***
 ***    ____________________________________                                ***
 ***   |                                    |                               ***
 ***   | -=Assarbad=- aka Oliver            |                               ***
 ***   |____________________________________|                               ***
 ***   |                                    |                               ***
 ***   | Assarbad@gmx.info|.net|.com|.de    |                               ***
 ***   | ICQ: 281645                        |                               ***
 ***   | AIM: nixlosheute                   |                               ***
 ***   |      nixahnungnicht                |                               ***
 ***   | MSN: Assarbad@ePost.de             |                               ***
 ***   | YIM: sherlock_holmes_and_dr_watson |                               ***
 ***   |____________________________________|                               ***
 ***             ___                                                        ***
 ***            /   |                     ||              ||                ***
 ***           / _  |   ________ ___  ____||__    ___   __||                ***
 ***          / /_\ |  / __/ __//   |/  _/|   \  /   | /   |                ***
 ***         / ___  |__\\__\\  / /\ || |  | /\ \/ /\ |/ /\ | DOT NET        ***
 ***        /_/   \_/___/___/ /_____\|_|  |____/_____\\__/\|                ***
 ***       ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~        ***
 ***  [http://assarbad.net | http://assarbad.org | http://assarbad.info]    ***
 ***                                                                        ***
 ***   Notes:                                                               ***
 ***   - my first name is Oliver, you may well use this in your e-mails     ***
 ***   - for questions and/or proposals drop me a mail or instant message   ***
 ***                                                                        ***
 ***~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~***
 ***              May the source be with you, stranger ... ;)               ***
 ***    Snizhok, eto ne tolko fruktovij kefir, snizhok, eto stil zhizn.     ***
 ***                     Vsem Privet iz Germanij                            ***
 ***                                                                        ***
 *** Greets from -=Assarbad=- fly to YOU =)                                 ***
 *** Special greets fly 2 Nico, Casper, SA, Pizza, Navarion, Eugen, Zhenja, ***
 *** Xandros, Melkij, Strelok etc pp.                                       ***
 ***                                                                        ***
 *** Thanks to:                                                             ***
 *** W.A. Mozart, Vivaldi, Beethoven, Poeta Magica, Kurtzweyl, Manowar,     ***
 *** Blind Guardian, Weltenbrand, In Extremo, Wolfsheim, Carl Orff, Zemfira ***
 *** ... most of my work was done with their music in the background ;)     ***
 ***                                                                        ***
 ******************************************************************************
 ******************************************************************************

 LEGAL STUFF:
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

 Copyright (c) 2003-2005, -=Assarbad=- ["copyright holder(s)"]
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.
 3. The name(s) of the copyright holder(s) may not be used to endorse or
    promote products derived from this software without specific prior written
    permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                             .oooO     Oooo.
 ____________________________(   )_____(   )___________________________________
                              \ (       ) /
                               \_)     (_/

 ******************************************************************************/

#include "stdafx.h"
#include "AgreementGINA2.h"
#include "AgreementDlg.h"
#include <Exdisp.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAgreementDlg dialog


CAgreementDlg::CAgreementDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAgreementDlg::IDD, pParent),
	  m_Timeout(0)
{
	//{{AFX_DATA_INIT(CAgreementDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_sURL.LoadString(IDS_ABOUTBLANK);
	m_sErrorURL.FormatMessage(IDS_RESOURCEURL, ThisApp->GetDllName(), IDR_ERRORAGREEMENT);

	m_Green.CreateSolidBrush(clLtGreen);
	m_Red.CreateSolidBrush(clLtRed);
}

CAgreementDlg::~CAgreementDlg()
{
}

void CAgreementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAgreementDlg)
	DDX_Control(pDX, IDC_STATIC_TIMER, m_StaticTimer);
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
	DDX_Control(pDX, IDC_CHECK_AGREE, m_CheckAgree);
	DDX_Control(pDX, IDC_BUTTON_YES, m_ButtonYes);
	DDX_Control(pDX, IDC_BUTTON_NO, m_ButtonNo);
	DDX_Control(pDX, IDC_EXPLORER1, m_IE);
	//}}AFX_DATA_MAP
}

void CAgreementDlg::SetUrlOrText(LPCTSTR szURL)
{
	m_sURL = szURL;
}

void CAgreementDlg::SetErrorOrText(LPCTSTR szError)
{
	m_sErrorURL = szError;
}

BEGIN_MESSAGE_MAP(CAgreementDlg, CDialog)
	//{{AFX_MSG_MAP(CAgreementDlg)
	ON_BN_CLICKED(IDC_BUTTON_NO, OnButtonNo)
	ON_BN_CLICKED(IDC_BUTTON_YES, OnButtonYes)
	ON_BN_CLICKED(IDC_CHECK_AGREE, OnCheckAgree)
	ON_WM_SYSCOMMAND()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAgreementDlg message handlers

BOOL CAgreementDlg::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::Create(IDD, pParentWnd);
}

void CAgreementDlg::OnButtonNo() 
{
	EndDialog(IDNO);
}

void CAgreementDlg::OnButtonYes() 
{
	EndDialog(IDYES);
}

void CAgreementDlg::OnCheckAgree() 
{
	m_ButtonYes.EnableWindow(BOOL(m_CheckAgree.GetCheck()));
	m_CheckAgree.RedrawWindow();
}

BOOL CAgreementDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Check whether this dialog should be shown anyway?
	// (Note: this is a second, perhaps obsolete check, one of them may diminish).
	if (ThisApp->GetCfg().ShowTimer && (ThisApp->GetCfg().TimerDuration == 0))
		EndDialog(IDYES);

	// Set button labels
	m_ButtonYes.SetWindowText(ThisApp->GetCfg().BtnYesText);
	m_ButtonNo.SetWindowText(ThisApp->GetCfg().BtnNoText);
	m_CheckAgree.SetWindowText(ThisApp->GetCfg().CheckBoxText);

	// Disable YES button
	m_ButtonYes.EnableWindow(FALSE);

	// Check whether the timer should be shown
	if (ThisApp->GetCfg().ShowTimer)
	{
		m_CheckAgree.EnableWindow(FALSE);
		m_Timeout = ThisApp->GetCfg().TimerDuration;
		m_Progress.SetRange32(0, m_Timeout);
		UpdateTimerProgress(m_Timeout);
//		OnTimer(IDC_STATIC_TIMER); // first update
	}
	else
	{
		// Disable and hide progress bar and static with time left
		m_Progress.EnableWindow(FALSE);
		m_Progress.ShowWindow(SW_HIDE);
		m_StaticTimer.EnableWindow(FALSE);
		m_StaticTimer.ShowWindow(SW_HIDE);

		RECT rect_IE, rect_static;

		m_IE.GetWindowRect(&rect_IE);
		m_StaticTimer.GetWindowRect(&rect_static);
		// Resize IE control to hide the gap between checkbox and IE control
		m_IE.SetHeight(m_IE.GetHeight() + (rect_static.bottom - rect_IE.bottom));
	}
	
	if(ThisApp->IsStringURL(m_sURL))
		m_IE.Navigate(m_sURL);
	else
	{
		m_IE.Clear();
		m_IE.PutStringContents(m_sURL);
	}

	InitTooltips(m_tooltip);

	return TRUE;
}

void CAgreementDlg::UpdateTimerProgress(DWORD Timeout)
{
	CString temp;

	temp.Format(_T("%.2d:%.2d"), Timeout / 60, Timeout % 60);
	m_StaticTimer.SetWindowText(temp);
	m_Progress.SetPos(Timeout);
}

void CAgreementDlg::OnTimer(UINT nIDEvent) 
{
	m_Timeout--;
	UpdateTimerProgress(m_Timeout);

	if (m_Timeout == 0)
	{
		KillTimer(IDC_STATIC_TIMER);
		m_CheckAgree.EnableWindow(TRUE);
		m_Progress.EnableWindow(FALSE);
		m_StaticTimer.EnableWindow(FALSE);
	}
	CDialog::OnTimer(nIDEvent);
}

void CAgreementDlg::InitTooltips(CToolTipCtrl& tooltip)
{
#define ADDTOOLTIP(x)	tooltip.AddTool(GetDlgItem(x), x)
	
	tooltip.Create(this, /*TTS_BALLOON | */ TTS_NOPREFIX | TTS_NOFADE | TTS_NOANIMATE);
//	tooltip.SetDelayTime(TTDT_INITIAL, 100); // take 1/10 of a second to show
	tooltip.SetDelayTime(TTDT_AUTOPOP, 10000); // show for 10 secs
//	tooltip.SetDelayTime(TTDT_RESHOW, 0); // reshow immediately
	tooltip.SetMaxTipWidth(150);

	ADDTOOLTIP(IDC_CHECK_AGREE);
	ADDTOOLTIP(IDC_BUTTON_YES);
	ADDTOOLTIP(IDC_BUTTON_NO);
	ADDTOOLTIP(IDC_PROGRESS);

	tooltip.Activate(TRUE);
}

/* 
 * NOTE: standard implementation is wrong, it looks like:
 *
 * ON_EVENT(CAgreementDlg, IDC_EXPLORER1, 270, OnFileDownloadExplorer1, VTS_PBOOL)
 * 
 * Change it like I did to reflect the real method of the interface.
 */
BEGIN_EVENTSINK_MAP(CAgreementDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CAgreementDlg)
	ON_EVENT(CAgreementDlg, IDC_EXPLORER1, 251 /* NewWindow2 */, OnNewWindow2Explorer1, VTS_PDISPATCH VTS_PBOOL)
	ON_EVENT(CAgreementDlg, IDC_EXPLORER1, 270 /* FileDownload */, OnFileDownloadExplorer1, VTS_PBOOL VTS_PBOOL)
	ON_EVENT(CAgreementDlg, IDC_EXPLORER1, 271 /* NavigateError */, OnNavigateErrorExplorer1, VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)
	ON_EVENT(CAgreementDlg, IDC_EXPLORER1, 113 /* TitleChange */, OnTitleChangeExplorer1, VTS_BSTR)
	ON_EVENT(CAgreementDlg, IDC_EXPLORER1, 250 /* BeforeNavigate2 */, OnBeforeNavigate2Explorer1, VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)
	ON_EVENT(CAgreementDlg, IDC_EXPLORER1, 259 /* DocumentComplete */, OnDocumentCompleteExplorer1, VTS_DISPATCH VTS_PVARIANT)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CAgreementDlg::OnNewWindow2Explorer1(LPDISPATCH FAR* ppDisp, BOOL FAR* Cancel) 
{
	// Do not allow new windows
	::Beep(200, 200);
	*Cancel = TRUE;
}

/* 
 * NOTE: standard implementation is wrong, it looks like:
 *
 * void CAgreementDlg::OnFileDownloadExplorer1(BOOL FAR* Cancel)
 * 
 * Change it like I did to reflect the real method of the interface.
 */
void CAgreementDlg::OnFileDownloadExplorer1(BOOL FAR* ActiveDocument, BOOL FAR* Cancel) 
{
	// Do not allow downloads
	*Cancel = TRUE;
	*ActiveDocument = FALSE;
}

void CAgreementDlg::OnNavigateErrorExplorer1(LPDISPATCH pDisp, VARIANT FAR* URL, VARIANT FAR* Frame, VARIANT FAR* StatusCode, BOOL FAR* Cancel) 
{
	// Do not show error page
	*Cancel = TRUE;
// Navigate to the error page contained as resource IDR_ERRORAGREEMENT (default)
	if(ThisApp->IsStringURL(m_sErrorURL))
		m_IE.Navigate(m_sErrorURL);
	else
	{
		m_IE.Clear();
		m_IE.PutStringContents(m_sErrorURL);
	}
}

void CAgreementDlg::OnTitleChangeExplorer1(LPCTSTR Text) 
{
	// Set dialog title from the HTML page title ;)
	SetWindowText(Text);
}

void CAgreementDlg::OnSysCommand(UINT nID, LPARAM lParam) 
{
	switch(nID)
	{
	case SC_CONTEXTHELP:
	case SC_DEFAULT:
	case SC_HOTKEY:
	case SC_KEYMENU:
	case SC_MOUSEMENU:
	case SC_SCREENSAVE:
	case SC_TASKLIST:
	case SC_SIZE:
	case SC_RESTORE:
	case SC_MINIMIZE:
	case SC_CLOSE:
		return;
		break;
	default:
		CDialog::OnSysCommand(nID, lParam);
		break;
	}
}

BOOL CAgreementDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	switch(wParam)
	{
	case IDCANCEL:
	case IDOK:
		// Don't close if ESC or ENTER are pressed
		// dialogs handle these by simulating IDCANCEL and IDOK, we block this
		return TRUE;
		break;
	default:
		return CDialog::OnCommand(wParam, lParam);
	}
}

BOOL CAgreementDlg::PreTranslateMessage(MSG* pMsg) 
{
	m_tooltip.RelayEvent(pMsg);
	return CDialog::PreTranslateMessage(pMsg);
}

HBRUSH CAgreementDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	switch(nCtlColor)
	{
	case CTLCOLOR_BTN:
	case CTLCOLOR_DLG:
	case CTLCOLOR_EDIT:
	case CTLCOLOR_LISTBOX:
	case CTLCOLOR_MSGBOX:
	case CTLCOLOR_SCROLLBAR:
	case CTLCOLOR_STATIC:
		switch(pWnd->GetDlgCtrlID())
		{
		case IDC_CHECK_AGREE:
			if (!m_CheckAgree.IsWindowEnabled())
				return hbr;
			BOOL IsChecked = BOOL(m_CheckAgree.GetCheck());
			pDC->SetBkColor(IsChecked ? clLtGreen : clLtRed);
			return IsChecked ? m_Green : m_Red;
			break;
		}
		break;
	}
	
	return hbr;
}

void CAgreementDlg::OnBeforeNavigate2Explorer1(LPDISPATCH pDisp, VARIANT FAR* URL, VARIANT FAR* Flags, VARIANT FAR* TargetFrameName, VARIANT FAR* PostData, VARIANT FAR* Headers, BOOL FAR* Cancel) 
{
	ThisApp->CheckAllowUrls(URL, *Cancel);
}

void CAgreementDlg::OnDocumentCompleteExplorer1(LPDISPATCH pDisp, VARIANT FAR* URL) 
{
	SetTimer(IDC_STATIC_TIMER, 1000, NULL);
}
