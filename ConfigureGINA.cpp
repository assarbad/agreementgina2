/******************************************************************************
 ******************************************************************************
 ***                                                                        ***
 ***   Configuration dialog implementation.                                 ***
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
#include "ConfigureGINA.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigureGINA dialog

CConfigureGINA::CConfigureGINA(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigureGINA::IDD, pParent),
	  m_OptionsChanged(FALSE),
	  m_Inited(FALSE),
	  m_pwmatch(FALSE),
	  m_nullport(FALSE),
	  m_nulltime(FALSE),
	  m_isAgreeURL(FALSE),
	  m_isNewsURL(FALSE),
	  m_isMaintenanceURL(FALSE)

{
	//{{AFX_DATA_INIT(CConfigureGINA)
	//}}AFX_DATA_INIT
	m_DlgTitle.FormatMessage(IDS_CFGDLGTITLE, ThisName);
	m_PasswordsMatch.CreateSolidBrush(clLtGreen);
	m_PasswordsDontMatch.CreateSolidBrush(clLtRed);
	m_Red.CreateSolidBrush(clRed);
	m_Green.CreateSolidBrush(clGreen);
	m_Blue.CreateSolidBrush(clBlue);
	m_White.CreateSolidBrush(clWhite);
	m_Gray.CreateSolidBrush(clGray);
	m_LtBlue.CreateSolidBrush(clLtBlue);
}


void CConfigureGINA::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigureGINA)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigureGINA, CDialog)
	//{{AFX_MSG_MAP(CConfigureGINA)
	ON_BN_CLICKED(IDC_CHECK_SHOWTIMER, OnCheckShowtimer)
	ON_BN_CLICKED(IDC_CHECK_MAINTENANCE, OnCheckMaintenance)
	ON_BN_CLICKED(IDC_CHECK_NEWS, OnCheckNews)
	ON_BN_CLICKED(IDC_CHECK_LOCKWKSTA, OnCheckLockwksta)
	ON_BN_CLICKED(IDC_CHECK_CHANGEPASS, OnCheckChangepass)
	ON_BN_CLICKED(IDC_CHECK_TASKMAN, OnCheckTaskman)
	ON_BN_CLICKED(IDC_CHECK_TASKMAN2, OnCheckTaskman2)
	ON_BN_CLICKED(IDC_CHECK_ONLYGUEST, OnCheckOnlyguest)
	ON_BN_CLICKED(IDC_CHECK_ADMINSKIPS, OnCheckAdminskips)
	ON_EN_CHANGE(IDC_EDIT_GUESTUSER, OnChangeEditGuestuser)
	ON_EN_CHANGE(IDC_EDIT_GUESTPASSWORD, OnChangeEditGuestpassword)
	ON_EN_CHANGE(IDC_EDIT_PORTNUM, OnChangeEditPortnum)
	ON_EN_CHANGE(IDC_EDIT_YES, OnChangeEditYes)
	ON_EN_CHANGE(IDC_EDIT_NO, OnChangeEditNo)
	ON_EN_CHANGE(IDC_EDIT_CHECKBOX, OnChangeEditCheckbox)
	ON_EN_CHANGE(IDC_EDIT_MAINTENANCE, OnChangeEditMaintenance)
	ON_EN_CHANGE(IDC_EDIT_NEWS, OnChangeEditNews)
	ON_EN_CHANGE(IDC_EDIT_AGREEMENT, OnChangeEditAgreement)
	ON_EN_CHANGE(IDC_EDIT_TIMERDURATION, OnChangeEditTimerduration)
	ON_EN_CHANGE(IDC_EDIT_GUESTPASSWORD2, OnChangeEditGuestpassword2)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_ABOUT, OnButtonAbout)
	ON_WM_CTLCOLOR()
	ON_EN_UPDATE(IDC_EDIT_GUESTPASSWORD2, OnUpdateEditGuestpassword2)
	ON_EN_UPDATE(IDC_EDIT_GUESTPASSWORD, OnUpdateEditGuestpassword)
	ON_EN_UPDATE(IDC_EDIT_TIMERDURATION, OnUpdateEditTimerduration)
	ON_EN_UPDATE(IDC_EDIT_PORTNUM, OnUpdateEditPortnum)
	ON_EN_UPDATE(IDC_EDIT_GUESTUSER, OnUpdateEditGuestuser)
	ON_EN_CHANGE(IDC_EDIT_GUESTDOMAIN, OnChangeEditGuestdomain)
	ON_EN_UPDATE(IDC_EDIT_AGREEMENT, OnUpdateEditAgreement)
	ON_EN_UPDATE(IDC_EDIT_NEWS, OnUpdateEditNews)
	ON_EN_UPDATE(IDC_EDIT_MAINTENANCE, OnUpdateEditMaintenance)
	ON_BN_CLICKED(IDC_BUTTON_AGREEMENT, OnButtonAgreement)
	ON_BN_CLICKED(IDC_BUTTON_NEWS, OnButtonNews)
	ON_BN_CLICKED(IDC_BUTTON_MAINTENANCE, OnButtonMaintenance)
	ON_BN_CLICKED(IDC_BUTTON_REPLTASKMAN, OnButtonRepltaskman)
	ON_EN_CHANGE(IDC_EDIT_REPLTASKMAN, OnChangeEditRepltaskman)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigureGINA message handlers

BOOL CConfigureGINA::OnInitDialog() 
{
	BOOL ret = CDialog::OnInitDialog();
	ThisApp->ReadConfig(m_TempConfig);
	CfgToDialog(m_TempConfig);
	m_Inited = TRUE;
	InitTooltips(m_tooltip);
	static_cast<CEdit *>(GetDlgItem(IDC_EDIT_AGREEMENT)		)->SetLimitText(64 * 1024);
	static_cast<CEdit *>(GetDlgItem(IDC_EDIT_NEWS)			)->SetLimitText(64 * 1024);
	static_cast<CEdit *>(GetDlgItem(IDC_EDIT_MAINTENANCE)	)->SetLimitText(64 * 1024);
	static_cast<CEdit *>(GetDlgItem(IDC_EDIT_GUESTUSER)		)->SetLimitText(127);
	static_cast<CEdit *>(GetDlgItem(IDC_EDIT_GUESTDOMAIN)	)->SetLimitText(127);
	static_cast<CEdit *>(GetDlgItem(IDC_EDIT_GUESTPASSWORD)	)->SetLimitText(127);
	static_cast<CEdit *>(GetDlgItem(IDC_EDIT_GUESTPASSWORD2))->SetLimitText(127);

	static_cast<CEdit *>(GetDlgItem(IDC_EDIT_YES)			)->SetLimitText(15);
	static_cast<CEdit *>(GetDlgItem(IDC_EDIT_NO)			)->SetLimitText(15);
	static_cast<CEdit *>(GetDlgItem(IDC_EDIT_CHECKBOX)		)->SetLimitText(150);
	return m_Inited;
}

void CConfigureGINA::InitTooltips(CToolTipCtrl& tooltip)
{
#define ADDTOOLTIP(x)	tooltip.AddTool(GetDlgItem(x), x)
	
	tooltip.Create(this, TTS_ALWAYSTIP | TTS_BALLOON | TTS_NOPREFIX | TTS_NOFADE | TTS_NOANIMATE);
	tooltip.SetDelayTime(TTDT_INITIAL, 100); // take 1/10 of a second to show
	tooltip.SetDelayTime(TTDT_AUTOPOP, 10000); // show for 10 secs
//	tooltip.SetDelayTime(TTDT_RESHOW, 0); // reshow immediately
	tooltip.SetMaxTipWidth(200);

	ADDTOOLTIP(IDC_BUTTON_ABOUT);
	ADDTOOLTIP(IDCANCEL);
	ADDTOOLTIP(IDOK);
	ADDTOOLTIP(IDC_BUTTON_SAVE);
	ADDTOOLTIP(IDC_CHECK_ADMINSKIPS);
	ADDTOOLTIP(IDC_CHECK_CHANGEPASS);
	ADDTOOLTIP(IDC_CHECK_LOCKWKSTA);
	ADDTOOLTIP(IDC_CHECK_MAINTENANCE);
	ADDTOOLTIP(IDC_CHECK_NEWS);
	ADDTOOLTIP(IDC_CHECK_ONLYGUEST);
	ADDTOOLTIP(IDC_CHECK_SHOWTIMER);
	ADDTOOLTIP(IDC_CHECK_TASKMAN);
	ADDTOOLTIP(IDC_EDIT_AGREEMENT);
	ADDTOOLTIP(IDC_EDIT_CHECKBOX);
	ADDTOOLTIP(IDC_EDIT_GUESTPASSWORD);
	ADDTOOLTIP(IDC_EDIT_GUESTPASSWORD2);
	ADDTOOLTIP(IDC_EDIT_GUESTUSER);
	ADDTOOLTIP(IDC_EDIT_GUESTDOMAIN);
	ADDTOOLTIP(IDC_EDIT_MAINTENANCE);
	ADDTOOLTIP(IDC_EDIT_NEWS);
	ADDTOOLTIP(IDC_EDIT_NO);
	ADDTOOLTIP(IDC_EDIT_PORTNUM);
	ADDTOOLTIP(IDC_EDIT_TIMERDURATION);
	ADDTOOLTIP(IDC_EDIT_YES);
	ADDTOOLTIP(IDC_BUTTON_AGREEMENT);
	ADDTOOLTIP(IDC_BUTTON_NEWS);
	ADDTOOLTIP(IDC_BUTTON_MAINTENANCE);
	ADDTOOLTIP(IDC_CHECK_TASKMAN2);
	ADDTOOLTIP(IDC_EDIT_REPLTASKMAN);
	ADDTOOLTIP(IDC_BUTTON_REPLTASKMAN);

	tooltip.Activate(TRUE);
}

void CConfigureGINA::CfgToDialog(GinaCfg& cfg)
{
// Get string values
	SetDlgItemText(IDC_EDIT_AGREEMENT,		cfg.HTML_file);
	OnUpdateEditAgreement();

	SetDlgItemText(IDC_EDIT_NEWS,			cfg.NewsText);
	OnUpdateEditNews();

	SetDlgItemText(IDC_EDIT_MAINTENANCE,	cfg.MaintenanceText);
	OnUpdateEditMaintenance();

	SetDlgItemText(IDC_EDIT_YES,			cfg.BtnYesText);
	SetDlgItemText(IDC_EDIT_NO,				cfg.BtnNoText);
	SetDlgItemText(IDC_EDIT_CHECKBOX,		cfg.CheckBoxText);
	CheckDlgButton(IDC_CHECK_LOCKWKSTA,		cfg.DisableLockWorkstation	? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK_CHANGEPASS,	cfg.DisableChangePassword	? BST_CHECKED : BST_UNCHECKED);
	DWORD dwValue = cfg.DisableTaskMgr;
	CheckDlgButton(IDC_CHECK_TASKMAN,		dwValue						? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK_TASKMAN2,		--dwValue					? BST_CHECKED : BST_UNCHECKED);
	SetDlgItemText(IDC_EDIT_REPLTASKMAN, cfg.ReplacementTaskMgr);
	OnCheckTaskman();

	CheckDlgButton(IDC_CHECK_SHOWTIMER,		cfg.ShowTimer				? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK_MAINTENANCE,	cfg.MaintenanceMode			? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK_NEWS,			cfg.NewsActive				? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK_ONLYGUEST,		cfg.AllowOnlyGuest			? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(IDC_CHECK_ADMINSKIPS,	cfg.AdminSkips				? BST_CHECKED : BST_UNCHECKED);
	SendDlgItemMessage(IDC_SPIN_PORTNUM, UDM_SETRANGE32, 0, 0xFFFF);
	SendDlgItemMessage(IDC_SPIN_PORTNUM, UDM_SETPOS32, 0, cfg.ListenPort);
	m_nullport = (cfg.ListenPort == 0);
	GetDlgItem(IDC_EDIT_PORTNUM)->RedrawWindow();
	GetDlgItem(IDC_STATIC_PORTNUM)->RedrawWindow();
	SendDlgItemMessage(IDC_SPIN_TIMERDURATION, UDM_SETRANGE32, 0, 3600);
	SendDlgItemMessage(IDC_SPIN_TIMERDURATION, UDM_SETPOS32, 0, cfg.TimerDuration);
	m_nulltime = (cfg.TimerDuration == 0);
	GetDlgItem(IDC_EDIT_TIMERDURATION)->RedrawWindow();

// Get username and password
	CString pass, username, domain;
	ThisApp->DecryptAndRetrievePassword(ThisName_User, username);
	SetDlgItemText(IDC_EDIT_GUESTUSER,		username);
	ThisApp->DecryptAndRetrievePassword(ThisName_Passwd, pass);
	SetDlgItemText(IDC_EDIT_GUESTPASSWORD,	pass);
	SetDlgItemText(IDC_EDIT_GUESTPASSWORD2,	pass);
	ThisApp->DecryptAndRetrievePassword(ThisName_Domain, domain);
	SetDlgItemText(IDC_EDIT_GUESTDOMAIN,	domain);
	username.Empty();
	pass.Empty();
	domain.Empty();

	ResetPasswordChanged();
}

void CConfigureGINA::DialogToCfg(GinaCfg& cfg)
{
	GetDlgItemText(IDC_EDIT_AGREEMENT,		cfg.HTML_file);
	GetDlgItemText(IDC_EDIT_NEWS,			cfg.NewsText);
	GetDlgItemText(IDC_EDIT_MAINTENANCE,	cfg.MaintenanceText);
	GetDlgItemText(IDC_EDIT_YES,			cfg.BtnYesText);
	GetDlgItemText(IDC_EDIT_NO,				cfg.BtnNoText);
	GetDlgItemText(IDC_EDIT_CHECKBOX,		cfg.CheckBoxText);
	GetDlgItemText(IDC_EDIT_REPLTASKMAN,	cfg.ReplacementTaskMgr);
	cfg.DisableLockWorkstation =			IsDlgButtonChecked(IDC_CHECK_LOCKWKSTA) == BST_CHECKED;
	cfg.DisableChangePassword =				IsDlgButtonChecked(IDC_CHECK_CHANGEPASS) == BST_CHECKED;

	DWORD dwValue =							IsDlgButtonChecked(IDC_CHECK_TASKMAN) == BST_CHECKED;
	if(dwValue)
		dwValue +=							IsDlgButtonChecked(IDC_CHECK_TASKMAN2) == BST_CHECKED;
	cfg.DisableTaskMgr =					dwValue;
	cfg.ShowTimer =							IsDlgButtonChecked(IDC_CHECK_SHOWTIMER) == BST_CHECKED;
	cfg.MaintenanceMode =					IsDlgButtonChecked(IDC_CHECK_MAINTENANCE) == BST_CHECKED;
	cfg.NewsActive =						IsDlgButtonChecked(IDC_CHECK_NEWS) == BST_CHECKED;
	cfg.AllowOnlyGuest =					IsDlgButtonChecked(IDC_CHECK_ONLYGUEST) == BST_CHECKED;
	cfg.AdminSkips =						IsDlgButtonChecked(IDC_CHECK_ADMINSKIPS) == BST_CHECKED;
	cfg.ListenPort =						SendDlgItemMessage(IDC_SPIN_PORTNUM, UDM_GETPOS32, 0, 0);
	cfg.TimerDuration =						SendDlgItemMessage(IDC_SPIN_TIMERDURATION, UDM_GETPOS32, 0, 0);
}

void CConfigureGINA::SetOptionsChanged()
{
	if(!m_Inited || m_OptionsChanged)
		return;
	m_OptionsChanged = TRUE;
	SetWindowText(m_DlgTitle + _T(" *"));
	if(!GetDlgItem(IDC_BUTTON_SAVE)->IsWindowEnabled())
		GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(TRUE);
}

void CConfigureGINA::ResetOptionsChanged()
{
	m_OptionsChanged = FALSE;
	SetWindowText(m_DlgTitle);
	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);
}

void CConfigureGINA::SetPasswordChanged()
{
	if(!m_Inited || m_PasswordChanged)
		return;
	SetOptionsChanged();
	m_PasswordChanged = TRUE;
}

void CConfigureGINA::ResetPasswordChanged()
{
	ResetOptionsChanged();
	m_PasswordChanged = FALSE;
}

void CConfigureGINA::OnCheckShowtimer() 
{
	SetOptionsChanged();
	GetDlgItem(IDC_STATIC_SETTINGSAGREEMENT)->RedrawWindow();
}

void CConfigureGINA::OnCheckMaintenance() 
{
	SetOptionsChanged();
}

void CConfigureGINA::OnCheckNews() 
{
	SetOptionsChanged();
}

void CConfigureGINA::OnCheckLockwksta() 
{
	SetOptionsChanged();
}

void CConfigureGINA::OnCheckChangepass() 
{
	SetOptionsChanged();
}

void CConfigureGINA::OnCheckTaskman() 
{
	SetOptionsChanged();
	BOOL enablereplace = IsDlgButtonChecked(IDC_CHECK_TASKMAN) == BST_CHECKED;
	GetDlgItem(IDC_CHECK_TASKMAN2)->EnableWindow(enablereplace);
	GetDlgItem(IDC_EDIT_REPLTASKMAN)->EnableWindow(enablereplace);
	GetDlgItem(IDC_BUTTON_REPLTASKMAN)->EnableWindow(enablereplace);
	if(!enablereplace)
		CheckDlgButton(IDC_CHECK_TASKMAN2, BST_UNCHECKED);
}

void CConfigureGINA::OnCheckTaskman2() 
{
	SetOptionsChanged();
}

void CConfigureGINA::OnCheckOnlyguest() 
{
	SetOptionsChanged();
	GetDlgItem(IDC_STATIC_SETTINGSNEWS)->RedrawWindow();
	GetDlgItem(IDC_STATIC_SETTINGSAGREEMENT)->RedrawWindow();
}

void CConfigureGINA::OnCheckAdminskips() 
{
	SetOptionsChanged();
}

void CConfigureGINA::OnChangeEditGuestuser() 
{
	SetPasswordChanged();
}

void CConfigureGINA::OnChangeEditGuestpassword() 
{
	SetPasswordChanged();
}

void CConfigureGINA::OnChangeEditGuestpassword2() 
{
	SetPasswordChanged();
}

void CConfigureGINA::OnChangeEditPortnum() 
{
	SetOptionsChanged();
}

void CConfigureGINA::OnChangeEditYes() 
{
	SetOptionsChanged();
}

void CConfigureGINA::OnChangeEditNo() 
{
	SetOptionsChanged();
}

void CConfigureGINA::OnChangeEditCheckbox() 
{
	SetOptionsChanged();
}

void CConfigureGINA::OnChangeEditMaintenance() 
{
	SetOptionsChanged();
}

void CConfigureGINA::OnChangeEditNews() 
{
	SetOptionsChanged();
}

void CConfigureGINA::OnChangeEditAgreement() 
{
	SetOptionsChanged();
}

void CConfigureGINA::OnChangeEditTimerduration() 
{
	SetOptionsChanged();
}

void CConfigureGINA::OnChangeEditGuestdomain() 
{
	SetPasswordChanged();
}

void CConfigureGINA::OnChangeEditRepltaskman() 
{
	SetOptionsChanged();
}

void CConfigureGINA::OnButtonSave()
{
	if (m_OptionsChanged || m_PasswordChanged)
	{
		DialogToCfg(m_TempConfig);
		ThisApp->WriteConfig(m_TempConfig); // Write the configuration from the dialog
		if (m_PasswordChanged && m_pwmatch)
		{
			CString pass, username, domain;
			GetDlgItemText(IDC_EDIT_GUESTPASSWORD, pass);
			GetDlgItemText(IDC_EDIT_GUESTUSER, username);
			GetDlgItemText(IDC_EDIT_GUESTDOMAIN, domain);
			ThisApp->EncryptAndStorePassword(ThisName_User, username);
			ThisApp->EncryptAndStorePassword(ThisName_Passwd, pass);
			ThisApp->EncryptAndStorePassword(ThisName_Domain, domain);
		}
		ResetPasswordChanged(); // Reset the changed state
		ThisApp->ReadConfig(); // Read the configuration (main DLL)
		ThisApp->ReadConfig(m_TempConfig); // Read the configuration to the dialog
		CfgToDialog(m_TempConfig);
	}
}

void CConfigureGINA::OnOK() 
{
	OnButtonSave();
	CDialog::OnOK();
}

void CConfigureGINA::OnButtonAbout() 
{
	CString x;
	x.FormatMessage(IDS_RESOURCEURL, ThisApp->GetDllName(), IDR_HTML_ABOUT);
	CShowMessageDlg dlg;
	dlg.SetUrlOrText(x);
	dlg.DoModal();
}

void CConfigureGINA::OnUpdateEditGuestpassword() 
{
	BOOL oldmatch = m_pwmatch;
	CString pass1, pass2, username;
	GetDlgItemText(IDC_EDIT_GUESTUSER, username);
	GetDlgItemText(IDC_EDIT_GUESTPASSWORD, pass1);
	GetDlgItemText(IDC_EDIT_GUESTPASSWORD2, pass2);
	((pass1 != pass2) || pass1.IsEmpty() || username.IsEmpty()) ? m_pwmatch = FALSE : m_pwmatch = TRUE;
	if (oldmatch != m_pwmatch)
	{
		GetDlgItem(IDC_EDIT_GUESTUSER)->RedrawWindow();
		GetDlgItem(IDC_EDIT_GUESTPASSWORD)->RedrawWindow();
		GetDlgItem(IDC_EDIT_GUESTPASSWORD2)->RedrawWindow();
		GetDlgItem(IDC_EDIT_GUESTDOMAIN)->RedrawWindow();
	}
}

void CConfigureGINA::OnUpdateEditGuestpassword2() 
{
	OnUpdateEditGuestpassword();
}

void CConfigureGINA::OnUpdateEditGuestuser() 
{
	OnUpdateEditGuestpassword();
}

void CConfigureGINA::OnUpdateEditTimerduration() 
{
	UINT iPos = GetDlgItemInt(IDC_EDIT_TIMERDURATION);
	BOOL oldstat = m_nulltime;

	m_nulltime = (iPos == 0);

	if (m_nulltime && (IsDlgButtonChecked(IDC_CHECK_SHOWTIMER) == BST_CHECKED))
		CheckDlgButton(IDC_CHECK_SHOWTIMER, FALSE);
	else
	if (m_nulltime && (IsDlgButtonChecked(IDC_CHECK_SHOWTIMER) == BST_UNCHECKED))
		CheckDlgButton(IDC_CHECK_SHOWTIMER, TRUE);

	if(m_nulltime != oldstat)
		GetDlgItem(IDC_EDIT_TIMERDURATION)->RedrawWindow();
	GetDlgItem(IDC_STATIC_SETTINGSAGREEMENT)->RedrawWindow();
}

void CConfigureGINA::OnUpdateEditPortnum() 
{
	UINT iPos = GetDlgItemInt(IDC_EDIT_PORTNUM);
	BOOL oldstat = m_nullport;

	m_nullport = (iPos == 0);

	if (m_nullport != oldstat)
	{
		GetDlgItem(IDC_EDIT_PORTNUM)->RedrawWindow();
		GetDlgItem(IDC_STATIC_PORTNUM)->RedrawWindow();
	}
}

void CConfigureGINA::OnUpdateEditAgreement() 
{
	CString temp;
	BOOL old = m_isAgreeURL;
	GetDlgItemText(IDC_EDIT_AGREEMENT, temp);
	m_isAgreeURL = ThisApp->IsStringURL(temp);
	if (old != m_isAgreeURL)
		GetDlgItem(IDC_EDIT_AGREEMENT)->RedrawWindow();
}

void CConfigureGINA::OnUpdateEditNews() 
{
	CString temp;
	BOOL old = m_isNewsURL;
	GetDlgItemText(IDC_EDIT_NEWS, temp);
	m_isNewsURL = ThisApp->IsStringURL(temp);
	if (old != m_isNewsURL)
		GetDlgItem(IDC_EDIT_NEWS)->RedrawWindow();
}

void CConfigureGINA::OnUpdateEditMaintenance() 
{
	CString temp;
	BOOL old = m_isMaintenanceURL;
	GetDlgItemText(IDC_EDIT_MAINTENANCE, temp);
	m_isMaintenanceURL = ThisApp->IsStringURL(temp);
	if (old != m_isMaintenanceURL)
		GetDlgItem(IDC_EDIT_MAINTENANCE)->RedrawWindow();
}

void CConfigureGINA::OnButtonAgreement() 
{
	CString temp;
	GetDlgItemText(IDC_EDIT_AGREEMENT, temp);
	CAgreementDlg dlg;
	dlg.SetUrlOrText(temp);
	dlg.DoModal();
}

void CConfigureGINA::OnButtonNews() 
{
	CString temp;
	GetDlgItemText(IDC_EDIT_NEWS, temp);
	CShowMessageDlg dlg;
	dlg.SetUrlOrText(temp);
	dlg.DoModal();
}

void CConfigureGINA::OnButtonMaintenance() 
{
	CString temp;
	GetDlgItemText(IDC_EDIT_MAINTENANCE, temp);
	CShowMessageDlg dlg;
	dlg.SetUrlOrText(temp);
	dlg.DoModal();
}

HBRUSH CConfigureGINA::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(nCtlColor)
	{
	case CTLCOLOR_BTN: // Button control
	case CTLCOLOR_DLG: // Dialog box
	case CTLCOLOR_EDIT: // Edit control
		switch(pWnd->GetDlgCtrlID())
		{
		case IDC_EDIT_GUESTUSER:
		case IDC_EDIT_GUESTPASSWORD:
		case IDC_EDIT_GUESTPASSWORD2:
		case IDC_EDIT_GUESTDOMAIN:
			if(m_pwmatch)
			{
				pDC->SetBkColor(clLtGreen);
				return HBRUSH(m_PasswordsMatch);
			}
			else
			{
				pDC->SetBkColor(clLtRed);
				return HBRUSH(m_PasswordsDontMatch);
			}
			break;
		case IDC_EDIT_AGREEMENT:
			if(m_isAgreeURL)
			{
				pDC->SetBkColor(clLtBlue);
				return HBRUSH(m_LtBlue);
			}
			break;
		case IDC_EDIT_NEWS:
			if (m_isNewsURL)
			{
				pDC->SetBkColor(clLtBlue);
				return HBRUSH(m_LtBlue);
			}
			break;
		case IDC_EDIT_MAINTENANCE:
			if(m_isMaintenanceURL)
			{
				pDC->SetBkColor(clLtBlue);
				return HBRUSH(m_LtBlue);
			}
			break;
		default:
			break;
		}
		break;
	case CTLCOLOR_LISTBOX: // List-box control
	case CTLCOLOR_MSGBOX: // Message box
	case CTLCOLOR_SCROLLBAR: // Scroll-bar control
	case CTLCOLOR_STATIC: // Static control 
		switch(pWnd->GetDlgCtrlID())
		{
		case IDC_STATIC_GUESTUSER:
		case IDC_STATIC_PASSWORD:
		case IDC_STATIC_PASSWORD2:
		case IDC_STATIC_DOMAIN:
			pDC->SetTextColor(clBlue);
			break;
		case IDC_STATIC_PORTNUM:
			if(m_nullport)
				pDC->SetTextColor(GetSysColor(COLOR_GRAYTEXT));
			else
				pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
			break;
		case IDC_EDIT_PORTNUM: // read-only edit must be treated as static
			if(m_nullport)
			{
				pDC->SetBkColor(clGray);
				return HBRUSH(m_Gray);
			}
			else
			{
				pDC->SetBkColor(clWhite);
				return HBRUSH(m_White);
			}
			break;
		case IDC_EDIT_TIMERDURATION: // read-only edit must be treated as static
			if(m_nulltime)
			{
				pDC->SetBkColor(clGray);
				return HBRUSH(m_Gray);
			}
			else
			{
				pDC->SetBkColor(clWhite);
				return HBRUSH(m_White);
			}
			break;
		case IDC_STATIC_SETTINGSAGREEMENT:
			if((IsDlgButtonChecked(IDC_CHECK_ONLYGUEST) == BST_CHECKED) ||
				((GetDlgItemInt(IDC_EDIT_TIMERDURATION) == 0) && (IsDlgButtonChecked(IDC_CHECK_SHOWTIMER) == BST_CHECKED)))
				pDC->SetTextColor(GetSysColor(COLOR_GRAYTEXT));
			else
				pDC->SetTextColor(clLilac);
			break;
		case IDC_STATIC_SETTINGSNEWS:
			if(IsDlgButtonChecked(IDC_CHECK_ONLYGUEST) == BST_CHECKED)
				pDC->SetTextColor(GetSysColor(COLOR_GRAYTEXT));
			else
				pDC->SetTextColor(clLilac);
			break;
		case IDC_STATIC_SETTINGSRESTRICTIONS:
		case IDC_STATIC_SETTINGSCAPTIONS:
		case IDC_STATIC_GENERAL:
			pDC->SetTextColor(clLilac);
			break;
		default:
			break;
		}
		break;
	}
	return hbr;
}

BOOL CConfigureGINA::PreTranslateMessage(MSG* pMsg) 
{
	m_tooltip.RelayEvent(pMsg);
	return CDialog::PreTranslateMessage(pMsg);
}

void CConfigureGINA::OnButtonRepltaskman() 
{
	CString temp;
	temp.LoadString(IDS_EXEFILTER);

	CFileDialog* dlg = new CFileDialog(TRUE, NULL, m_TempConfig.ReplacementTaskMgr,
							OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_NOTESTFILECREATE | OFN_PATHMUSTEXIST,
							temp, this);
	if(dlg)
	{
		if (dlg->DoModal() == IDOK)
		{
			m_TempConfig.ReplacementTaskMgr = dlg->GetPathName();
			SetDlgItemText(IDC_EDIT_REPLTASKMAN, m_TempConfig.ReplacementTaskMgr);
			SetOptionsChanged();
		}
		delete dlg;
	}
}
