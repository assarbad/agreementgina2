/******************************************************************************
 ******************************************************************************
 ***                                                                        ***
 ***   Application/DLL class implementation.                                ***
 ***   It contains all the utility functions and DLL initialization.        ***
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
#include <WinWlx.h>
// NOTE: This line is a hardcoded reference to an MFC header file
//  this path may need to be changed to refer to the location of your VC
//  install for successful compilation.
#include <..\src\occimpl.h>
#include "CustomClientSite.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "version.h"

/////////////////////////////////////////////////////////////////////////////
// CAgreementGINA2App

BEGIN_MESSAGE_MAP(CAgreementGINA2App, CWinApp)
	//{{AFX_MSG_MAP(CAgreementGINA2App)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAgreementGINA2App construction

CAgreementGINA2App::CAgreementGINA2App()
	: m_SocketsInitialised(FALSE),
	  m_threadUsername(LPCTSTR(NULL)),
	  m_threadDomain(LPCTSTR(NULL)),
	  m_threadToken(NULL),
	  m_threadIsGuest(FALSE),
	  m_threadIsAdmin(FALSE),
	  m_dllName(LPCTSTR(NULL)),
	  sGinaPath(_T("msgina.dll")),
	  m_MajorVer(0),
	  m_MinorVer(0),
	  m_ListenPortChanged(FALSE),
	  sServer(INVALID_SOCKET)
{
	GetModuleName(m_dllName);

	DWORD dwVersion = GetVersion();
	m_MajorVer = DWORD(LOBYTE(LOWORD(dwVersion)));
	m_MinorVer = DWORD(HIBYTE(LOWORD(dwVersion)));

	m_SocketsInitialised = WSAStartup(0x0202, &wsaData) == 0;

	// We commit suicide if we are on Windows 9x/Me
	if (dwVersion & 0x80000000)
		// Why is that?
		ExitProcess(0);
}

CAgreementGINA2App::~CAgreementGINA2App()
{
	if(m_SocketsInitialised)
		WSACleanup();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAgreementGINA2App object

CAgreementGINA2App theApp;

/////////////////////////////////////////////////////////////////////////////
// CAgreementGINA2App initialization

BOOL CAgreementGINA2App::InitInstance()
{
	// To override the client site
	CCustomOccManager *pMgr = new CCustomOccManager;

	CoInitialize(NULL);
	AfxEnableControlContainer(pMgr);

	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	
	// Restore taskman settings in case we couldn't do this due to powerdown or something
	RestoreTaskman();
	ReadConfig();
	ListenPortChangedReset();

	return TRUE;
}

BOOL CAgreementGINA2App::IsRequiredVersion()
{
	return (m_MajorVer >= 5);
}

HMODULE CAgreementGINA2App::GetModuleHandle()
{
	MEMORY_BASIC_INFORMATION mbi;
	static int iDummy;
	VirtualQuery(&iDummy, &mbi, sizeof(mbi));
	return HMODULE(mbi.AllocationBase);
}

void CAgreementGINA2App::GetModuleName(CString& str)
{
	DWORD dwRet = 0, dwSize = MAX_PATH;
	while(true)
	{
		LPTSTR buf = str.GetBuffer(dwSize  * sizeof(TCHAR));
		dwRet = ::GetModuleFileName(GetModuleHandle(), buf, dwSize);
		str.ReleaseBuffer();
		if(dwRet < dwSize)
			break;
		else
			dwSize *= 2;
	}
	int iPos = str.ReverseFind('\\');
	if (iPos != -1)
		str = str.Mid(iPos + 1);
}

void CAgreementGINA2App::RunDlg()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CAgreementDlg dlg;
	dlg.DoModal();
}

CString CAgreementGINA2App::GetDllName()
{
	return m_dllName;
}

BOOL CAgreementGINA2App::EncryptAndStorePassword(LPCTSTR key, LPCTSTR passwd)
{
// Assumes UNICODE is defined
	CString realkey = key;
	CString password = passwd;
	LSA_OBJECT_ATTRIBUTES lsaOA;
	LSA_HANDLE handle;
	ACCESS_MASK desiredAccess = POLICY_CREATE_SECRET | GENERIC_WRITE;
	NTSTATUS ret;
	LSA_UNICODE_STRING usKey, usPassword;

	memset(&lsaOA, 0, sizeof(lsaOA));
	ret = LsaOpenPolicy(NULL, &lsaOA, desiredAccess, &handle);

	if(LsaNtStatusToWinError(ret) == ERROR_SUCCESS)
	{
		usKey.Length = lstrlen(realkey) * sizeof(TCHAR);
		usKey.MaximumLength = usKey.Length;
		usKey.Buffer = realkey.GetBuffer(usKey.Length);
		usPassword.Length = (lstrlen(password) + 1) * sizeof(TCHAR);
		usPassword.MaximumLength = usPassword.Length;
		usPassword.Buffer = password.GetBuffer(usPassword.Length);

		LsaStorePrivateData(handle, &usKey, &usPassword);

		password.ReleaseBuffer();
		realkey.ReleaseBuffer();

		LsaClose(handle);
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CAgreementGINA2App::DecryptAndRetrievePassword(LPCTSTR key, CString&  password)
{
// Assumes UNICODE is defined
	CString realkey = key;
	LSA_OBJECT_ATTRIBUTES lsaOA;
	LSA_HANDLE handle;
	ACCESS_MASK desiredAccess = POLICY_GET_PRIVATE_INFORMATION | GENERIC_READ;
	NTSTATUS ret;
	LSA_UNICODE_STRING usKey, *usPassword = NULL;

	memset(&lsaOA, 0, sizeof(lsaOA));
	ret = LsaOpenPolicy(NULL, &lsaOA, desiredAccess, &handle);

	if(LsaNtStatusToWinError(ret) == ERROR_SUCCESS)
	{
		usKey.Length = lstrlen(realkey) * sizeof(TCHAR);
		usKey.MaximumLength = usKey.Length;
		usKey.Buffer = realkey.GetBuffer(usKey.Length / sizeof(TCHAR));

		LsaRetrievePrivateData(handle, &usKey, &usPassword);

		if(usPassword != NULL)
		{
			password = usPassword->Buffer;
		}
		else
			password = LPCTSTR(NULL);

		LsaFreeMemory(usPassword);

		realkey.ReleaseBuffer();

		LsaClose(handle);
		return TRUE;
	}
	else
		return FALSE;
}

void CAgreementGINA2App::ReadConfig(GinaCfg& cfg)
{
	CRegKeyEx key;
	key.Open(HKEY_LOCAL_MACHINE, WinlogonKey);
	key.Open(key.m_hKey, ThisName);

	cfg.AdminSkips = key.ReadBool(sAdminSkips);

	cfg.BtnNoText = key.ReadString(sBtnNoText);
	cfg.BtnYesText = key.ReadString(sBtnYesText);
	cfg.CheckBoxText = key.ReadString(sCheckBoxText);

	cfg.HTML_file = key.ReadString(sHTML_file);

	cfg.ListenPort = key.ReadDWORD(sListenPort);
	SetListenPort(cfg.ListenPort);

	cfg.MaintenanceMode = key.ReadBool(sMaintenanceMode);
	cfg.MaintenanceText = key.ReadString(sMaintenanceText);

	cfg.NewsActive = key.ReadBool(sNewsActive);
	cfg.NewsText = key.ReadString(sNewsText);

	cfg.ShowTimer = key.ReadBool(sShowTimer);
	cfg.TimerDuration = key.ReadDWORD(sTimerDuration);

// Override to admin logon holding down the shift key
	cfg.AllowOnlyGuest = key.ReadBool(sAllowOnlyGuest);
	// If the registry value for guest name and password exists, put into
	// password stash
	if (key.ValueExists(sGuestName))
		EncryptAndStorePassword(ThisName_User, key.ReadString(sGuestName));

	if (key.ValueExists(sGuestPassword))
		EncryptAndStorePassword(ThisName_Passwd, key.ReadString(sGuestPassword));

	if (key.ValueExists(sGuestDomain))
		EncryptAndStorePassword(ThisName_Domain, key.ReadString(sGuestDomain));

	// ... afterwards delete the registry values
	key.DeleteValue(sGuestName);
	key.DeleteValue(sGuestPassword);
	key.DeleteValue(sGuestDomain);

// Restrictions only apply to non-admin users
	cfg.DisableLockWorkstation = key.ReadBool(sDisableLockWorkstation);
	cfg.DisableChangePassword = key.ReadBool(sDisableChangePassword);
	cfg.DisableTaskMgr = key.ReadDWORD(sDisableTaskMgr);
	if (cfg.DisableTaskMgr > 2)
		cfg.DisableTaskMgr = 1;
	cfg.ReplacementTaskMgr = key.ReadString(sReplacementTaskMgr);

	key.Close();
}

void CAgreementGINA2App::ReadConfig()
{
	ReadConfig(m_Configuration);
}

void CAgreementGINA2App::WriteConfig(GinaCfg& cfg)
{
	CRegKeyEx key;
	key.Open(HKEY_LOCAL_MACHINE, WinlogonKey);
	key.Open(key.m_hKey, ThisName);

	key.SetValue(DWORD(cfg.AdminSkips), sAdminSkips);

	key.SetValue(cfg.BtnNoText, sBtnNoText);
	key.SetValue(cfg.BtnYesText, sBtnYesText);
	key.SetValue(cfg.CheckBoxText, sCheckBoxText);

	key.SetValue(cfg.HTML_file, sHTML_file);

	key.SetValue(DWORD(cfg.ListenPort), sListenPort);

	key.SetValue(DWORD(cfg.MaintenanceMode), sMaintenanceMode);
	key.SetValue(cfg.MaintenanceText, sMaintenanceText);

	key.SetValue(DWORD(cfg.NewsActive), sNewsActive);
	key.SetValue(cfg.NewsText, sNewsText);

	key.SetValue(DWORD(cfg.ShowTimer), sShowTimer);
	key.SetValue(DWORD(cfg.TimerDuration), sTimerDuration);

// Override to admin logon holding down the shift key
	key.SetValue(DWORD(cfg.AllowOnlyGuest), sAllowOnlyGuest);

// Restrictions only apply to non-admin users
	key.SetValue(DWORD(cfg.DisableLockWorkstation), sDisableLockWorkstation);
	key.SetValue(DWORD(cfg.DisableChangePassword), sDisableChangePassword);
	key.SetValue(DWORD(cfg.DisableTaskMgr), sDisableTaskMgr);
	key.SetValue(cfg.ReplacementTaskMgr, sReplacementTaskMgr);

	key.Close();
}

void CAgreementGINA2App::WriteConfig()
{
	WriteConfig(m_Configuration);
}

BOOL CAgreementGINA2App::IsAdmin(HANDLE hToken)
{
	PSID pAdminSid = NULL;
	PTOKEN_GROUPS pGroups;
	DWORD cbSize = 0;
	BOOL bSuccess = FALSE;
	SID_IDENTIFIER_AUTHORITY siaNtAuth = SECURITY_NT_AUTHORITY;

// Retrieve required size
    GetTokenInformation(hToken, TokenGroups, NULL, 0, &cbSize);
	pGroups = PTOKEN_GROUPS(malloc(cbSize));
// Check for successful allocation
	if(pGroups != NULL)
	__try
	{
// Get the token information
		if (!GetTokenInformation (hToken, TokenGroups, (LPVOID)pGroups, cbSize, &cbSize))
			return FALSE;
// Build generic admin SID
		if (!AllocateAndInitializeSid(&siaNtAuth,2, 
                                     SECURITY_BUILTIN_DOMAIN_RID,
                                     DOMAIN_ALIAS_RID_ADMINS,
                                     0,0,0,0,0,0, &pAdminSid))
			return FALSE;
// Compare each of the contained SIDs
		for (DWORD i = 0; (i < pGroups->GroupCount) && !bSuccess; i++)
			if (EqualSid(pAdminSid, pGroups->Groups[i].Sid))
				bSuccess = TRUE;
// Free the allocated SID
		FreeSid(pAdminSid);
	}
	__finally
	{
		free(pGroups);
	}
	return bSuccess;
}

BOOL CAgreementGINA2App::RetrieveOriginalGinaFunctions()
{
#define MSGINAPROC(y, x) m_GINA.pf.pf##x = (y)GetProcAddress(m_GINA.hOldGina, #x)

	if(m_GINA.hOldGina == NULL)
		m_GINA.hOldGina = LoadLibrary(sGinaPath);

	if (m_GINA.hOldGina != NULL)
	{
		memset(&m_GINA.pf, 0, sizeof(m_GINA.pf));
		MSGINAPROC(PFWLXNEGOTIATE, WlxNegotiate);
		MSGINAPROC(PFWLXINITIALIZE, WlxInitialize);
		MSGINAPROC(PFWLXDISPLAYSASNOTICE, WlxDisplaySASNotice);
		MSGINAPROC(PFWLXLOGGEDOUTSAS, WlxLoggedOutSAS);
		MSGINAPROC(PFWLXACTIVATEUSERSHELL, WlxActivateUserShell);
		MSGINAPROC(PFWLXLOGGEDONSAS, WlxLoggedOnSAS);
		MSGINAPROC(PFWLXDISPLAYLOCKEDNOTICE, WlxDisplayLockedNotice);
		MSGINAPROC(PFWLXWKSTALOCKEDSAS, WlxWkstaLockedSAS);
		MSGINAPROC(PFWLXISLOCKOK, WlxIsLockOk);
		MSGINAPROC(PFWLXISLOGOFFOK, WlxIsLogoffOk);
		MSGINAPROC(PFWLXLOGOFF, WlxLogoff);
		MSGINAPROC(PFWLXSHUTDOWN, WlxShutdown);
// New for version 1.1
		MSGINAPROC(PFWLXSCREENSAVERNOTIFY, WlxScreenSaverNotify);
		MSGINAPROC(PFWLXSTARTAPPLICATION, WlxStartApplication);
// New for 1.3
		MSGINAPROC(PFWLXNETWORKPROVIDERLOAD, WlxNetworkProviderLoad);
		MSGINAPROC(PFWLXDISPLAYSTATUSMESSAGE, WlxDisplayStatusMessage);
		MSGINAPROC(PFWLXGETSTATUSMESSAGE, WlxGetStatusMessage);
		MSGINAPROC(PFWLXREMOVESTATUSMESSAGE, WlxRemoveStatusMessage);
// New for 1.4
		MSGINAPROC(PFWLXGETCONSOLESWITCHCREDENTIALS, WlxGetConsoleSwitchCredentials);
		MSGINAPROC(PFWLXRECONNECTNOTIFY, WlxReconnectNotify);
		MSGINAPROC(PFWLXDISCONNECTNOTIFY, WlxDisconnectNotify);

		if (
			m_GINA.pf.pfWlxNegotiate != NULL &&
			m_GINA.pf.pfWlxInitialize != NULL &&
			m_GINA.pf.pfWlxDisplaySASNotice != NULL &&
			m_GINA.pf.pfWlxLoggedOutSAS != NULL &&
			m_GINA.pf.pfWlxActivateUserShell != NULL &&
			m_GINA.pf.pfWlxLoggedOnSAS != NULL &&
			m_GINA.pf.pfWlxDisplayLockedNotice != NULL &&
			m_GINA.pf.pfWlxWkstaLockedSAS != NULL &&
			m_GINA.pf.pfWlxIsLockOk != NULL &&
			m_GINA.pf.pfWlxIsLogoffOk != NULL &&
			m_GINA.pf.pfWlxLogoff != NULL &&
			m_GINA.pf.pfWlxShutdown != NULL 
			)
			m_GINA.dwSupportedVersion = WLX_VERSION_1_0;

		if (
			m_GINA.pf.pfWlxScreenSaverNotify != NULL &&
			m_GINA.pf.pfWlxStartApplication != NULL 
			)
			m_GINA.dwSupportedVersion = WLX_VERSION_1_2;

		if (
			m_GINA.pf.pfWlxNetworkProviderLoad != NULL &&
			m_GINA.pf.pfWlxDisplayStatusMessage != NULL &&
			m_GINA.pf.pfWlxGetStatusMessage != NULL &&
			m_GINA.pf.pfWlxRemoveStatusMessage != NULL 
			)
			m_GINA.dwSupportedVersion = WLX_VERSION_1_3;

		if (
			m_GINA.pf.pfWlxGetConsoleSwitchCredentials != NULL &&
			m_GINA.pf.pfWlxReconnectNotify != NULL &&
			m_GINA.pf.pfWlxDisconnectNotify != NULL 
			)
			m_GINA.dwSupportedVersion = WLX_VERSION_1_4;

		if(m_GINA.dwSupportedVersion == 0)
			return FALSE;

		return TRUE;
	}
	else
		return FALSE;
}

void CAgreementGINA2App::SetFunctions(HANDLE hWlx, LPCTSTR lpWinsta, PVOID pWinlogonFunctions)
{
	m_GINA.OrigWinlogonFunctions = PWLX_DISPATCH_VERSION_CURRENT(pWinlogonFunctions);
	m_GINA.hWinlogon = hWlx;
	m_GINA.sWindowStation = lpWinsta;
	// Temporary variable
	DWORD dwSize = 0;
	// Check the supported version
	switch(m_GINA.dwSupportedVersion)
	{
	case WLX_VERSION_1_0:
		dwSize = sizeof(WLX_DISPATCH_VERSION_1_0);
		break;
	case WLX_VERSION_1_1:
		dwSize = sizeof(WLX_DISPATCH_VERSION_1_1);
		break;
	case WLX_VERSION_1_2:
		dwSize = sizeof(WLX_DISPATCH_VERSION_1_2);
		break;
	case WLX_VERSION_1_3:
		dwSize = sizeof(WLX_DISPATCH_VERSION_1_3);
		break;
	case WLX_VERSION_1_4:
		dwSize = sizeof(WLX_DISPATCH_VERSION_1_4);
		break;
	}
	// Copy original dispatch table to private area
	memcpy(&m_GINA.PassWinlogonFunctions, m_GINA.OrigWinlogonFunctions, dwSize);
}

MyGINA& CAgreementGINA2App::GINA()
{
	return m_GINA;
}

GinaCfg& CAgreementGINA2App::GetCfg()
{
	return m_Configuration;
}

HANDLE CAgreementGINA2App::GetToken()
{
	return m_threadToken;
}

BOOL CAgreementGINA2App::IsStringURL(CString& str)
{
	if (str.IsEmpty())
	{
		str.LoadString(IDS_ABOUTBLANK);
		return TRUE;
	}

	return (str[0] != _T('<') && str.Find(_T('\n')) == -1);
}

void CAgreementGINA2App::ReplaceAutologonCredentials()
{
#define READREGCREDENTIALS(x)	if (m_BC.key->ValueExists(s##x)) \
								{ \
									m_BC.b##x = TRUE; \
									m_BC.x = m_BC.key->ReadString(s##x); \
								}

	// Check whether an old instance exists
	if(m_BC.key)
		delete m_BC.key;
	// Create new instance
	m_BC.key = new CRegKeyEx();
	if(!m_BC.key)
		return;

	m_BC.key->Open(HKEY_LOCAL_MACHINE, WinlogonKey);

	// Read registry values
	READREGCREDENTIALS(DefaultDomainName);
	READREGCREDENTIALS(DefaultUserName);
	READREGCREDENTIALS(AutoAdminLogon);
	READREGCREDENTIALS(ForceAutoLogon);

	// Try both: registry and secret stash
	if (m_BC.key->ValueExists(sDefaultPassword))
	{
		m_BC.bDefaultPasswordReg = TRUE;
		m_BC.DefaultPasswordReg = m_BC.key->ReadString(sDefaultPassword);
	}

	m_BC.bDefaultPasswordStash = DecryptAndRetrievePassword(sDefaultPassword, m_BC.DefaultPasswordStash);

	// Set the values for autologon!
	m_BC.key->DeleteValue(sDefaultPassword);
	m_BC.key->SetValue(_T("1"), sAutoAdminLogon);
	m_BC.key->SetValue(_T("1"), sForceAutoLogon);

	CString user, pass, domain;
	DecryptAndRetrievePassword(ThisName_User, user);
	DecryptAndRetrievePassword(ThisName_Passwd, pass);
	DecryptAndRetrievePassword(ThisName_Domain, domain);
	
	m_BC.key->SetValue(domain, sDefaultDomainName);
	m_BC.key->SetValue(user, sDefaultUserName);
	if (m_BC.bDefaultPasswordStash)
		// Set the value in the secret stash if a value existed there already!
		EncryptAndStorePassword(sDefaultPassword, pass);
	else
		// ... else set value in registry
		m_BC.key->SetValue(pass, sDefaultPassword);
}

void CAgreementGINA2App::RestoreAutologonCredentials()
{
#define WRITEREGCREDENTIALS(x)	if (m_BC.b##x) \
									m_BC.key->SetValue(m_BC.x, s##x); \
								else \
									m_BC.key->DeleteValue(s##x);

	if(!m_BC.key)
		return;

	WRITEREGCREDENTIALS(DefaultDomainName);
	WRITEREGCREDENTIALS(DefaultUserName);
	WRITEREGCREDENTIALS(AutoAdminLogon);
	WRITEREGCREDENTIALS(ForceAutoLogon);

	// Empty or restore value in registry
	if (m_BC.bDefaultPasswordReg)
		m_BC.key->SetValue(sDefaultPassword, m_BC.DefaultPasswordReg); \
	else
		m_BC.key->DeleteValue(sDefaultPassword);

	// Empty or restore value in secret stash
	if(m_BC.bDefaultPasswordStash)
		EncryptAndStorePassword(sDefaultPassword, m_BC.DefaultPasswordStash);

	m_BC.key->Close();
	delete m_BC.key;
	m_BC.key = NULL;
}

bool CAgreementGINA2App::ReplaceTaskman()
{
	if(IsReplacedTaskman())
		RestoreTaskman(); // Don't replace twice!

	CRegKeyEx TM_key, AG2key;
	// Forge string
	CString temp;
	temp.Format(_T("%s\\%s"), sImageFileExecution, sTaskMgr);

	// Open AgreementGINA key
	AG2key.Open(HKEY_LOCAL_MACHINE, WinlogonKey);
	AG2key.Open(AG2key.m_hKey, ThisName);
	

	// Try to open key for Image File Execution Options of taskmgr.exe
	if (ERROR_SUCCESS == TM_key.Open(HKEY_LOCAL_MACHINE, temp))
	{
		AG2key.Create(AG2key.m_hKey, sDisableTaskMgr);
		// Check if the value for "Debugger" exists
		// ... if so, save the old value!
		if(TM_key.ValueExists(sDebugger))
			AG2key.SetValue(TM_key.ReadString(sDebugger), sDebugger);
	}
	else
	{
		// Create the key for Image File Execution Options of taskmgr.exe
		TM_key.Create(HKEY_LOCAL_MACHINE, temp);
		AG2key.DeleteSubKey(sDisableTaskMgr);
	}

	// Set new value to be our "replacement"
	TM_key.SetValue(m_Configuration.ReplacementTaskMgr, sDebugger);

	// Close key
	TM_key.Close();
	AG2key.Close();

	AG2key.Open(HKEY_LOCAL_MACHINE, WinlogonKey);
	AG2key.Open(AG2key.m_hKey, ThisName);
	AG2key.SetValue(DWORD(true), sReplacedTaskman);
	AG2key.Close();

	return true;
}

bool CAgreementGINA2App::RestoreTaskman()
{
	if(!IsReplacedTaskman())
		return false;

	CRegKeyEx TM_key, AG2key;
	// Forge string
	CString temp;
	temp.Format(_T("%s\\%s"), sImageFileExecution, sTaskMgr);

	// Open AgreementGINA key
	AG2key.Open(HKEY_LOCAL_MACHINE, WinlogonKey);
	AG2key.Open(AG2key.m_hKey, ThisName);
	
	if(ERROR_SUCCESS == AG2key.Open(AG2key.m_hKey, sDisableTaskMgr))
	{
		// Try to open key for Image File Execution Options of taskmgr.exe
		TM_key.Create(HKEY_LOCAL_MACHINE, temp);
		// If the value did exist
		if(AG2key.ValueExists(sDebugger))
			TM_key.SetValue(AG2key.ReadString(sDebugger), sDebugger);
		else
			TM_key.DeleteValue(sDebugger);
		// Remove our persistent state value
		AG2key.DeleteValue(sDebugger);
	}
	else
	{
		if(ERROR_SUCCESS == TM_key.Open(HKEY_LOCAL_MACHINE, temp))
		{
			TM_key.DeleteValue(sDebugger);
			TM_key.Close();
		}
		TM_key.Open(HKEY_LOCAL_MACHINE, sImageFileExecution);
		TM_key.DeleteSubKey(sTaskMgr);
	}

	// Close key
	TM_key.Close();
	AG2key.Close();

	AG2key.Open(HKEY_LOCAL_MACHINE, WinlogonKey);
	AG2key.Open(AG2key.m_hKey, ThisName);
	AG2key.DeleteValue(sReplacedTaskman);
	AG2key.DeleteSubKey(sDisableTaskMgr);
	AG2key.Close();

	return true;
}

bool CAgreementGINA2App::IsReplacedTaskman()
{
	CRegKeyEx AG2key;

	// Open AgreementGINA key
	AG2key.Open(HKEY_LOCAL_MACHINE, WinlogonKey);
	AG2key.Open(AG2key.m_hKey, ThisName);
	bool result = AG2key.ValueExists(sReplacedTaskman) &
			AG2key.ReadBool(sReplacedTaskman);
	AG2key.Close();

	return result;
}

void CAgreementGINA2App::SetUserData(HANDLE hToken, LPCTSTR pszDomain, LPCTSTR pszUserName, BOOL IsGuest)
{
	m_UserinfoLock.Lock(); // BEGIN
	m_threadUsername = pszUserName;
	m_threadDomain = pszDomain;
	m_threadToken = hToken;
	m_threadIsGuest = IsGuest;
	if(m_threadToken != NULL)
	{
		GetLocalTime(&m_threadTime);
		m_threadIsAdmin = IsAdmin(hToken);
	}
	else
	{
		memset(&m_threadTime, 0, sizeof(m_threadTime));
		m_threadIsAdmin = FALSE;
	}

	// If the token is being set, check for admin
	// if not admin check whether the taskman should be replaced
	if(hToken && !IsAdmin(hToken) && (m_Configuration.DisableTaskMgr == 2))
		ReplaceTaskman();

	// If the token is NULL, restore taskman if it was replaced by us
	if(!hToken && IsReplacedTaskman())
		RestoreTaskman();
	m_UserinfoLock.Unlock(); // END
}

BOOL CAgreementGINA2App::WinsockInited()
{
	return m_SocketsInitialised;
}

BOOL CAgreementGINA2App::ListenPortChanged()
{
	m_PortLock.Lock(); // BEGIN
	BOOL ret = m_ListenPortChanged;
	m_PortLock.Unlock(); // END
	return ret;
}

BOOL CAgreementGINA2App::ListenPortChangedReset()
{
	m_PortLock.Lock(); // BEGIN
	BOOL ret = m_ListenPortChanged;
	if (ret)
	{
		m_ListenPortChanged = FALSE;
		ret = TRUE; // Yes, port changed
	}
	m_PortLock.Unlock(); // END
	return ret;
}

void CAgreementGINA2App::SetListenPort(DWORD newPort)
{
	m_PortLock.Lock(); // BEGIN
	BOOL bChanged = (m_ListenPort != newPort);
	if(bChanged)
	{
		DWORD oldPort = m_ListenPort;
		m_ListenPort = newPort;
		m_ListenPortChanged = bChanged;
		if(oldPort != 0)
		{
			// Forcibly close socket to cancel blocking accept
			closesocket(sServer);
			sServer = INVALID_SOCKET;
		}
	}
	m_PortLock.Unlock(); // END
}

WORD CAgreementGINA2App::GetListenPort()
{
	m_PortLock.Lock(); // BEGIN
	WORD ret = WORD(m_ListenPort);
	m_PortLock.Unlock(); // END
	return ret;
}

void CAgreementGINA2App::WaitPortLock()
{
	m_PortLock.Lock();
	m_PortLock.Unlock();
}

void CAgreementGINA2App::SendUserData(SOCKET& sClient)
{
	// Socket needs not to be validated before this is being called
	if(sClient != INVALID_SOCKET)
	{
		m_UserinfoLock.Lock(); // BEGIN
		ReadConfig();
		CString temp, temp2, temp3;

		temp3.Format(_T("%4.4d-%2.2d-%2.2d@%2.2d:%2.2d:%2.2d"),
			m_threadTime.wYear,
			m_threadTime.wMonth,
			m_threadTime.wDay,
			m_threadTime.wHour,
			m_threadTime.wMinute,
			m_threadTime.wSecond);
		if(m_threadIsAdmin)
			temp2 += _T("A");
		if(m_Configuration.MaintenanceMode)
			temp2 += _T("M");
		if(m_threadIsGuest)
			temp2 += _T("G");
		temp.Format(_T("%s#%s#%s#%s#%s"), m_threadUsername, m_threadDomain, temp3, temp2, _T(VERSION_STR));
		m_UserinfoLock.Unlock(); // END
		DWORD dwSize = temp.GetLength() * 2;
		LPSTR pc = LPSTR(malloc(dwSize));
		memset(pc, 0, dwSize);
		LPCTSTR uc = temp.GetBuffer(temp.GetLength());
		// Now convert from Unicode string to UTF8 string
		int len = WideCharToMultiByte(CP_UTF8, 0, uc, -1, pc, dwSize - 1, NULL, NULL);
		temp.ReleaseBuffer();
		URL_Encode(pc, len);
		send(sClient, pc, len, 0);
		free(pc);
	}
}

inline CHAR IntToHex(const CHAR x)
{
	return x < 0xA ? x + 0x30 : x + 0x37;
}

void CAgreementGINA2App::URL_Encode(LPSTR &pc, int &len)
{
#define myisalnum(x) ((x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z') || (x >= '0' && x <= '9') || (x == '#')) //  || x == ':' || x == '@' || x == '-'

	int newlen = len * 3;
	LPSTR tempbuf = pc;
	LPSTR stepbuf = pc = LPSTR(malloc(newlen));
	if(!pc)
	{
		pc = tempbuf;
		return;
	}
	memset(pc, 0, newlen);
	for(int i = 0; i < len - 1; i++)
	{
		if(myisalnum(tempbuf[i]))
			*stepbuf++ = tempbuf[i];
		else
		{
			*stepbuf++ = '%';
			*stepbuf++ = IntToHex((tempbuf[i] & 0xF0) >> 4);
			*stepbuf++ = IntToHex(tempbuf[i] & 0x0F);
		}
	}
	len = stepbuf - pc;

	free(tempbuf);
}

void CAgreementGINA2App::CheckAllowUrls(VARIANT FAR* URL, BOOL &Cancel)
{
	const LPCTSTR szHttp = _T("http://");
	const LPCTSTR szBlank = _T("about:");
	const LPCTSTR szRes = _T("res://%s/");
	
	CString temp = URL->bstrVal;
	temp = temp.Left(lstrlen(szBlank));
	if (temp.CompareNoCase(szBlank) == 0)
		return; // No action from our side

	temp = URL->bstrVal;
	CString temp2;
	temp2.Format(szRes, ThisApp->GetDllName());
	temp = temp.Left(lstrlen(temp2));
	if (temp.CompareNoCase(temp2) == 0)
		return; // No action from our side

	// Check for HTTP protocol
	temp = URL->bstrVal;
	temp = temp.Left(lstrlen(szHttp));
	if (temp.CompareNoCase(szHttp) != 0)
	{
		::Beep(200, 200);
		// We do not allow to visit non-HTTP URLs
		Cancel = TRUE;
		return;
	}
}
