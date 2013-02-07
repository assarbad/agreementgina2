/******************************************************************************
 ******************************************************************************
 ***                                                                        ***
 ***   Dialog class to show a dialog with a WebBrowser control.             ***
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
#include "agreementgina2.h"
#include "ShowMessageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowMessageDlg dialog


CShowMessageDlg::CShowMessageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShowMessageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShowMessageDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_sURL.LoadString(IDS_ABOUTBLANK);
	m_sErrorURL.FormatMessage(IDS_RESOURCEURL, ThisApp->GetDllName(), IDR_ERRORGENERIC);
}


void CShowMessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowMessageDlg)
	DDX_Control(pDX, IDC_EXPLORER1, m_IE);
	//}}AFX_DATA_MAP
}

void CShowMessageDlg::SetUrlOrText(LPCTSTR szURL)
{
	m_sURL = szURL;
}

void CShowMessageDlg::SetErrorOrText(LPCTSTR szError)
{
	m_sErrorURL = szError;
}

BEGIN_MESSAGE_MAP(CShowMessageDlg, CDialog)
	//{{AFX_MSG_MAP(CShowMessageDlg)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_BUTTON_OK, OnButtonOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CShowMessageDlg::OnOK() 
{
	EndDialog(0);
}

BOOL CShowMessageDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if(ThisApp->IsStringURL(m_sURL))
		m_IE.Navigate(m_sURL);
	else
	{
		m_IE.Clear();
		m_IE.PutStringContents(m_sURL);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CShowMessageDlg message handlers

/* 
 * NOTE: standard implementation is wrong, it looks like:
 *
 * ON_EVENT(CShowMessageDlg, IDC_EXPLORER1, 270, OnFileDownloadExplorer1, VTS_PBOOL)
 * 
 * Change it like I did to reflect the real method of the interface.
 */
BEGIN_EVENTSINK_MAP(CShowMessageDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CShowMessageDlg)
	ON_EVENT(CShowMessageDlg, IDC_EXPLORER1, 271 /* NavigateError */, OnNavigateErrorExplorer1, VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)
	ON_EVENT(CShowMessageDlg, IDC_EXPLORER1, 270 /* FileDownload */, OnFileDownloadExplorer1, VTS_PBOOL VTS_PBOOL)
	ON_EVENT(CShowMessageDlg, IDC_EXPLORER1, 251 /* NewWindow2 */, OnNewWindow2Explorer1, VTS_PDISPATCH VTS_PBOOL)
	ON_EVENT(CShowMessageDlg, IDC_EXPLORER1, 113 /* TitleChange */, OnTitleChangeExplorer1, VTS_BSTR)
	ON_EVENT(CShowMessageDlg, IDC_EXPLORER1, 250 /* BeforeNavigate2 */, OnBeforeNavigate2Explorer1, VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CShowMessageDlg::OnNewWindow2Explorer1(LPDISPATCH FAR* ppDisp, BOOL FAR* Cancel) 
{
	// Do not allow new windows
	::Beep(200, 200);
	*Cancel = TRUE;
}

/* 
 * NOTE: standard implementation is wrong, it looks like:
 *
 * void CShowMessageDlg::OnFileDownloadExplorer1(BOOL FAR* Cancel) 
 * 
 * Change it like I did to reflect the real method of the interface.
 */
void CShowMessageDlg::OnFileDownloadExplorer1(BOOL FAR* ActiveDocument, BOOL FAR* Cancel) 
{
	// Do not allow downloads
	*Cancel = TRUE;
	*ActiveDocument = FALSE;
}

void CShowMessageDlg::OnNavigateErrorExplorer1(LPDISPATCH pDisp, VARIANT FAR* URL, VARIANT FAR* Frame, VARIANT FAR* StatusCode, BOOL FAR* Cancel) 
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

void CShowMessageDlg::OnTitleChangeExplorer1(LPCTSTR Text) 
{
	// Set dialog title from the HTML page title ;)
	SetWindowText(Text);
}

void CShowMessageDlg::OnSysCommand(UINT nID, LPARAM lParam) 
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

BOOL CShowMessageDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	switch(wParam)
	{
	case IDCANCEL:
		return TRUE;
		break;
	default:
		return CDialog::OnCommand(wParam, lParam);
	}
}

void CShowMessageDlg::OnButtonOk() 
{
	EndDialog(0);
}

void CShowMessageDlg::OnBeforeNavigate2Explorer1(LPDISPATCH pDisp, VARIANT FAR* URL, VARIANT FAR* Flags, VARIANT FAR* TargetFrameName, VARIANT FAR* PostData, VARIANT FAR* Headers, BOOL FAR* Cancel) 
{
	ThisApp->CheckAllowUrls(URL, *Cancel);
}
