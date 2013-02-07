/******************************************************************************
 ******************************************************************************
 ***                                                                        ***
 ***   The exported functions and their supplement of the replacement.      ***
 ***   It makes heavy use of the original GINA's functions.                 ***
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

/*

  NOTE:

	"AFX_MANAGE_STATE(AfxGetStaticModuleState())" is required in any exported
	function which uses MFC implicitly or explicitly. If it is not present in
	these functions, the GINA will fail to load and Windows will not finish the
	bootup process.

*/

#include "stdafx.h"
#include "AgreementGINA2.h"

UINT RegistryThread(LPVOID pParam)
{
	CRegKey key;
	key.Open(HKEY_LOCAL_MACHINE, WinlogonKey);
	key.Open(key.m_hKey, ThisName);
	while(ERROR_SUCCESS == RegNotifyChangeKeyValue(key.m_hKey, FALSE, REG_NOTIFY_CHANGE_LAST_SET, NULL, FALSE))
	{
		ThisApp->ReadConfig();
		::Sleep(5000);
	}
	key.Close();
	return 0;
}

UINT ServerThread(LPVOID pParam)
{
	sockaddr_in saServer, saClient;
	SOCKET sClient = INVALID_SOCKET;

	CString temps;
	temps.Format(_T("Global\\%s"), ThisName_User);
	// Try to find another instance
	HANDLE hMutex = ::OpenMutex(MUTEX_ALL_ACCESS, FALSE, temps);
	if(hMutex)
		// Found one, bail out ...
		return 0;
	else
		// Found none, create a mutex to tell everyone we were first here
		hMutex = ::CreateMutex(NULL, TRUE, temps);

	// "Infinite" loop
	while(ThisApp->WinsockInited())
	{
		// We won't listen if the port is set to zero
		while (ThisApp->GetListenPort() == 0)
		{
			Sleep(0);
			// Poll every 5 secs
			Sleep(5000);
		}
		// Try to init the listening socket
		while(ThisApp->sServer == INVALID_SOCKET)
		{
			ThisApp->sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			Sleep(0);
			if (ThisApp->sServer == INVALID_SOCKET)
				Sleep(1000);
		}
		saServer.sin_addr.s_addr = htonl(INADDR_ANY);
		saServer.sin_family = AF_INET;
		saServer.sin_port = htons(ThisApp->GetListenPort());
		if (saServer.sin_port != 0 && bind(ThisApp->sServer, (sockaddr *)&saServer, sizeof(saServer)) == 0)
		{
			// Listen for incoming connections
			listen(ThisApp->sServer, 0);
			// As long as the port to listen on did not change, we are going
			// to simply stay inside this inner loop
			while(!ThisApp->ListenPortChangedReset())
			{
				int iAddrSize = sizeof(saClient);
				// Accept an incoming connection
				sClient = accept(ThisApp->sServer, (sockaddr *)&saClient, &iAddrSize);
				ThisApp->WaitPortLock();
				// If everything went fine, go on ...
				ThisApp->SendUserData(sClient);
				// Close the client socket
				closesocket(sClient);
				sClient = INVALID_SOCKET;
			}
		}
		if (ThisApp->sServer != INVALID_SOCKET)
		{
			closesocket(ThisApp->sServer);
			ThisApp->sServer = INVALID_SOCKET;
		}
	}

	::CloseHandle(hMutex);
	return 0;
}

INT_PTR CALLBACK WinSec_DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Dbg(_T("[%.5d] WinSec_DialogProc(hwndDlg == %.8X, uMsg == %.8X, wParam == %.8X, lParam == %.8X)"), ::GetCurrentProcessId(), hwndDlg, uMsg, wParam, lParam);
	// Necessary if we refer to MFC instances
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(ThisApp->GINA().pfWlxWinSecDlgProc == NULL)
		exit(0);

	// Disable items according to registry settings
	EnableWindow(GetDlgItem(hwndDlg, IDX_BTN_LOCK), ThisApp->IsAdmin(ThisApp->GetToken()) || !(ThisApp->GetCfg().DisableLockWorkstation || ThisApp->GetCfg().AllowOnlyGuest));
	EnableWindow(GetDlgItem(hwndDlg, IDX_BTN_CHANGEPASS), ThisApp->IsAdmin(ThisApp->GetToken()) || !(ThisApp->GetCfg().DisableChangePassword || ThisApp->GetCfg().AllowOnlyGuest));
	EnableWindow(GetDlgItem(hwndDlg, IDX_BTN_TASKMAN), ThisApp->IsAdmin(ThisApp->GetToken()) || !(ThisApp->GetCfg().DisableTaskMgr == 1));
	// If the Taskman button is disabled we'll not show the description either ;)
	ShowWindow(GetDlgItem(hwndDlg,	IDX_STATIC_TASKMANDESC), IsWindowEnabled(GetDlgItem(hwndDlg, IDX_BTN_TASKMAN)) ? SW_SHOW : SW_HIDE);

	INT_PTR ret = TRUE;

	// The admin gets to see a different dialog ;)
	if (ThisApp->IsAdmin(ThisApp->GetToken()))
	{
		// The admin is allowed to configure our GINA via a dialog.
		// This dialog is provided when clicking on the button which
		// previously provided "Logoff" functionality. IDCANCEL must
		// not be used as it is responsible for Alt+F4 and ESC as well.
		switch(uMsg)
		{
		case WM_INITDIALOG:
			{
				CString temp;
				temp.LoadString(IDS_CONFIGURE);
				::SetDlgItemText(hwndDlg, IDX_BTN_LOGOFF, temp);
				ret = ThisApp->GINA().pfWlxWinSecDlgProc(hwndDlg, uMsg, wParam, lParam);
			}
			break;
		case WM_COMMAND:
			if (WORD(wParam) == IDX_BTN_LOGOFF)
			{
				CConfigureGINA dlg;
				dlg.DoModal();
				ThisApp->ReadConfig();
			}
			else
				// Pass on to the original dialog function
				ret = ThisApp->GINA().pfWlxWinSecDlgProc(hwndDlg, uMsg, wParam, lParam);
			break;
		default:
			ret = ThisApp->GINA().pfWlxWinSecDlgProc(hwndDlg, uMsg, wParam, lParam);
			break;
		}
	}
	else
		ret = ThisApp->GINA().pfWlxWinSecDlgProc(hwndDlg, uMsg, wParam, lParam);
	
// Disable items according to registry settings
	EnableWindow(GetDlgItem(hwndDlg, IDX_BTN_LOCK), ThisApp->IsAdmin(ThisApp->GetToken()) || !(ThisApp->GetCfg().DisableLockWorkstation || ThisApp->GetCfg().AllowOnlyGuest));
	EnableWindow(GetDlgItem(hwndDlg, IDX_BTN_CHANGEPASS), ThisApp->IsAdmin(ThisApp->GetToken()) || !(ThisApp->GetCfg().DisableChangePassword || ThisApp->GetCfg().AllowOnlyGuest));
	EnableWindow(GetDlgItem(hwndDlg, IDX_BTN_TASKMAN), ThisApp->IsAdmin(ThisApp->GetToken()) || !(ThisApp->GetCfg().DisableTaskMgr == 1));
	// If the Taskman button is disabled we'll not show the description either ;)
	ShowWindow(GetDlgItem(hwndDlg,	IDX_STATIC_TASKMANDESC), IsWindowEnabled(GetDlgItem(hwndDlg, IDX_BTN_TASKMAN)) ? SW_SHOW : SW_HIDE);
	
	return ret;
}

int WINAPI MyWlxDialogBoxParam(
	HANDLE                  hWlx,
	HANDLE                  hInst,
	LPWSTR                  lpszTemplate,
	HWND                    hwndOwner,
	DLGPROC                 dlgprc,
	LPARAM                  dwInitParam)
{
	// Necessary if we refer to MFC instances
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	switch(DWORD(lpszTemplate))
	{
	// Hook the security dialog!
	case IDX_WINSECDLG:
		Dbg(_T("[%.5d] MyWlxDialogBoxParam(hWlx == %.8X) -> Catched for: IDX_WINSECDLG"), ::GetCurrentProcessId(), hWlx);
		ThisApp->GINA().pfWlxWinSecDlgProc = dlgprc;
		return ThisApp->GINA().OrigWinlogonFunctions->WlxDialogBoxParam(
																hWlx,
																hInst,
																lpszTemplate,
																hwndOwner,
																WinSec_DialogProc,
																dwInitParam
															);
		break;
	default:
		Dbg(_T("[%.5d] MyWlxDialogBoxParam(hWlx == %.8X) -> Passthru"), ::GetCurrentProcessId(), hWlx);
		return ThisApp->GINA().OrigWinlogonFunctions->WlxDialogBoxParam(
																hWlx,
																hInst,
																lpszTemplate,
																hwndOwner,
																dlgprc,
																dwInitParam
															);
		break;
	}
}

int WINAPI MyWlxDialogBox(
	HANDLE                  hWlx,
	HANDLE                  hInst,
	LPWSTR                  lpszTemplate,
	HWND                    hwndOwner,
	DLGPROC                 dlgprc)
{
// Customize this function
	return MyWlxDialogBoxParam(hWlx, hInst, lpszTemplate, hwndOwner, dlgprc, 0);
}

BOOL
WINAPI
WlxNegotiate(
    DWORD                   dwWinlogonVersion,
    PDWORD                  pdwDllVersion
    )
{
	Dbg(_T("[%.5d] WlxNegotiate(dwWinlogonVersion == %.8X)"), ::GetCurrentProcessId(), dwWinlogonVersion);
// Necessary if we refer to MFC instances
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
// Check required Windows version
	if (!ThisApp->IsRequiredVersion())
	{
		// Display an error string
		CString temp;
		temp.LoadString(IDS_STRING_FAILWINLOGON);
		// Remove the value GinaDLL to allow the next boot to succeed
		CRegKey key;
		key.Open(HKEY_LOCAL_MACHINE, WinlogonKey);
		key.DeleteValue(GinaDLL);
		key.Close();
		::MessageBox(0, temp, NULL, MB_OK);
		return FALSE;
	}
// Check wether we support this version
	if (dwWinlogonVersion > MY_WLX_CURRENT_VERSION)
		return FALSE; // Bail out, fail Winlogon.exe
// If the pointer for the version is invalid, exit
	if (NULL == pdwDllVersion)
		exit(1);
// Set LogonType to classic Windows style
	CRegKeyEx key;
	key.Open(HKEY_LOCAL_MACHINE, WinlogonKey);
	key.SetValue(DWORD(0), sLogonType);
	key.Close();
// Retrieve GINA functions
	ThisApp->RetrieveOriginalGinaFunctions();
// Determine version supported by the original GINA
	BOOL ret = ThisApp->GINA().pf.pfWlxNegotiate(dwWinlogonVersion, pdwDllVersion);
// Last check wether we support at least the same GINA version as the original GINA
	if (*pdwDllVersion > MY_WLX_CURRENT_VERSION)
		return FALSE; // Bail out, fail Winlogon.exe
// Return the supported version
	ThisApp->GINA().dwSupportedVersion = *pdwDllVersion;
	return ret;
}

BOOL
WINAPI
WlxInitialize(
    LPWSTR                  lpWinsta,
    HANDLE                  hWlx,
    PVOID                   pvReserved,
    PVOID                   pWinlogonFunctions,
    PVOID *                 pWlxContext
    )
{
	Dbg(_T("[%.5d] WlxInitialize(lpWinsta == \"%s\", hWlx == %.8X)"), ::GetCurrentProcessId(), lpWinsta, hWlx);
	// Necessary if we refer to MFC instances
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// Refresh configuration values
	Dbg(_T("[%.5d] WlxInitialize(lpWinsta == \"%s\", hWlx == %.8X) -> Reading configuration from registry"), ::GetCurrentProcessId(), lpWinsta, hWlx);
	ThisApp->ReadConfig();
	// Save some variables
	Dbg(_T("[%.5d] WlxInitialize(lpWinsta == \"%s\", hWlx == %.8X) -> Saving original GINA's function pointers"), ::GetCurrentProcessId(), lpWinsta, hWlx);
	ThisApp->SetFunctions(hWlx, lpWinsta, pWinlogonFunctions);
	// Hook the dialog functions
	Dbg(_T("[%.5d] WlxInitialize(lpWinsta == \"%s\", hWlx == %.8X) -> Overriding WlxDialogBoxParam() and WlxDialogBox()"), ::GetCurrentProcessId(), lpWinsta, hWlx);
	ThisApp->GINA().PassWinlogonFunctions.WlxDialogBox = MyWlxDialogBox;
	ThisApp->GINA().PassWinlogonFunctions.WlxDialogBoxParam = MyWlxDialogBoxParam;
	// At this point we hook the functions we want to catch
	Dbg(_T("[%.5d] WlxInitialize(lpWinsta == \"%s\", hWlx == %.8X) -> Starting server thread"), ::GetCurrentProcessId(), lpWinsta, hWlx);
	ThisApp->GINA().pServerThread = AfxBeginThread(ServerThread, ThisApp);
	ThisApp->GINA().pRegistryThread = AfxBeginThread(RegistryThread, ThisApp);
	// Pass on the stuff
	Dbg(_T("[%.5d] WlxInitialize(lpWinsta == \"%s\", hWlx == %.8X) -> Setting context pointer"), ::GetCurrentProcessId(), lpWinsta, hWlx);
	ThisApp->GINA().OrigWinlogonFunctions->WlxSetContextPointer(hWlx, *pWlxContext);
	Dbg(_T("[%.5d] WlxInitialize(lpWinsta == \"%s\", hWlx == %.8X) -> Checking for AllowOnlyGuest mode"), ::GetCurrentProcessId(), lpWinsta, hWlx);
	// Simulate Ctrl+Alt+Del
	if (ThisApp->GetCfg().AllowOnlyGuest)
	{
		Dbg(_T("[%.5d] WlxInitialize(hWlx == %.8X) -> simulating Ctrl+Alt+Del SAS"), ::GetCurrentProcessId(), hWlx);
		ThisApp->GINA().OrigWinlogonFunctions->WlxSasNotify(hWlx, WLX_SAS_TYPE_CTRL_ALT_DEL);
	}
	Dbg(_T("[%.5d] WlxInitialize(lpWinsta == \"%s\", hWlx == %.8X) -> Calling original function"), ::GetCurrentProcessId(), lpWinsta, hWlx);
	return ThisApp->GINA().pf.pfWlxInitialize(lpWinsta, hWlx, pvReserved, &ThisApp->GINA().PassWinlogonFunctions, pWlxContext);
}

VOID
WINAPI
WlxDisplaySASNotice(
    PVOID                   pWlxContext
    )
{
	Dbg(_T("[%.5d] ~WlxDisplaySASNotice(pWlxContext == %p)"), ::GetCurrentProcessId(), pWlxContext);
	// Necessary if we refer to MFC instances
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// Pass this call to original GINA instance
	ThisApp->GINA().pf.pfWlxDisplaySASNotice(pWlxContext);
}

int
WINAPI
WlxLoggedOutSAS(
    PVOID                   pWlxContext,
    DWORD                   dwSasType,
    PLUID                   pAuthenticationId,
    PSID                    pLogonSid,
    PDWORD                  pdwOptions,
    PHANDLE                 phToken,
    PWLX_MPR_NOTIFY_INFO    pMprNotifyInfo,
    PVOID *                 pProfile
    )
{
	Dbg(_T("[%.5d] WlxLoggedOutSAS(pWlxContext == %p, dwSasType == %.8X)"), ::GetCurrentProcessId(), pWlxContext, dwSasType);
	// Necessary if we refer to MFC instances
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// Special race condition
	if (phToken == NULL)
	{
		Dbg(_T("[%.5d] WlxLoggedOutSAS(pWlxContext == %p) -> Bailing out due to invalid token pointer"), ::GetCurrentProcessId(), pWlxContext);
		return WLX_SAS_ACTION_NONE;
	}
	// Refresh configuration values
	ThisApp->ReadConfig();
	// Check for Shift or F1 as override sequence
	BOOL override = (0x8000 & (::GetAsyncKeyState(VK_F1) | ::GetAsyncKeyState(VK_SHIFT))) != 0;

	// If no override was requested and "guest only" mode is on
	// -> Maintenance mode overrides "guest only" mode
	if (!override && !ThisApp->GetCfg().MaintenanceMode && ThisApp->GetCfg().AllowOnlyGuest)
	{
		Dbg(_T("[%.5d] WlxLoggedOutSAS(pWlxContext == %p) -> Now replacing logon credentials for guest"), ::GetCurrentProcessId(), pWlxContext);
		// ... set autologon credentials
		ThisApp->ReplaceAutologonCredentials();
	}

	// Pass this call to original GINA instance
	int ret = ThisApp->GINA().pf.pfWlxLoggedOutSAS(pWlxContext, dwSasType, pAuthenticationId, pLogonSid, pdwOptions, phToken, pMprNotifyInfo, pProfile);
	Dbg(_T("[%.5d] WlxLoggedOutSAS(pWlxContext == %p) == %.8X"), ::GetCurrentProcessId(), pWlxContext, ret);

	// If no override was requested and "guest only" mode is on
	if (!override && !ThisApp->GetCfg().MaintenanceMode && ThisApp->GetCfg().AllowOnlyGuest)
	{
		Dbg(_T("[%.5d] WlxLoggedOutSAS(pWlxContext == %p) -> Now restoring logon credentials for guest"), ::GetCurrentProcessId(), pWlxContext);
		// ... restore autologon credentials
		ThisApp->RestoreAutologonCredentials();
	}

	// In guest only mode when overriding, only admins are allowed to logon
	if (override && ThisApp->GetCfg().AllowOnlyGuest && !ThisApp->IsAdmin(*phToken))
	{
		Dbg(_T("[%.5d] WlxLoggedOutSAS(pWlxContext == %p) -> AllowOnlyGuest & !IsAdmin"), ::GetCurrentProcessId(), pWlxContext);
		// Get MPR info from original GINA. We know the original one fill it in.
		CString temp;
		// Build a string of format domain\username
		temp.Format(_T("%s\\%s"), pMprNotifyInfo->pszDomain, pMprNotifyInfo->pszUserName);
		CString user, domain;
		ThisApp->DecryptAndRetrievePassword(ThisName_User, user);
		ThisApp->DecryptAndRetrievePassword(ThisName_Domain, domain);
		// Same for the stored guest credentials
		user = domain + '\\' + user;
		// Nice try. A user who's neither guest nor admin tried to logon!
		if (user.CompareNoCase(temp) != 0)
		{
			// Note: doing this and guaranteeing that no one holds down the
			// override sequence will seeminglessly logon the guest ;)
			ThisApp->GINA().pf.pfWlxLogoff(pWlxContext);
			Dbg(_T("[%.5d] WlxLoggedOutSAS(pWlxContext == %p) -> AllowOnlyGuest & !IsAdmin -> not guest nor admin"), ::GetCurrentProcessId(), pWlxContext);
			return WLX_SAS_ACTION_NONE;
		}
	}

	if(!ThisApp->GetCfg().AllowOnlyGuest && (ret == WLX_SAS_ACTION_LOGON))
	{
		Dbg(_T("[%.5d] WlxLoggedOutSAS(pWlxContext == %p) -> ret == WLX_SAS_ACTION_LOGON"), ::GetCurrentProcessId(), pWlxContext);
		// Admins will not see the maintenance mode notice!
		if((!ThisApp->IsAdmin(*phToken)) && (ThisApp->GetCfg().MaintenanceMode))
		{
			// Logoff the user who tried to logon, because it's no admin and
			// we are in maintenance mode :-D
			ThisApp->GINA().pf.pfWlxLogoff(pWlxContext);
			CShowMessageDlg dlg;
			dlg.SetUrlOrText(ThisApp->GetCfg().MaintenanceText);
			dlg.DoModal();
			// Return to logon dialog
			Dbg(_T("[%.5d] WlxLoggedOutSAS(pWlxContext == %p) -> MaintenanceMode & !IsAdmin"), ::GetCurrentProcessId(), pWlxContext);
			return WLX_SAS_ACTION_NONE;
		}
		// Only if the admin is allowed to skip, or user is no admin
		if((!ThisApp->IsAdmin(*phToken)) || ((ThisApp->IsAdmin(*phToken)) && (!ThisApp->GetCfg().AdminSkips)))
		{
			Dbg(_T("[%.5d] WlxLoggedOutSAS(pWlxContext == %p) -> !IsAdmin | (IsAdmin & !AdminSkips)"), ::GetCurrentProcessId(), pWlxContext);
			// Check whether we should show the agreement
			if(!((ThisApp->GetCfg().ShowTimer == TRUE) && (ThisApp->GetCfg().TimerDuration == 0)))
			{
				Dbg(_T("[%.5d] WlxLoggedOutSAS(pWlxContext == %p) -> Showing agreement)"), ::GetCurrentProcessId(), pWlxContext);
				// Show agreement
				CAgreementDlg dlg;
				dlg.SetUrlOrText(ThisApp->GetCfg().HTML_file);
				// Check whether user chose YES or NO
				if (IDNO == dlg.DoModal())
				{
					Dbg(_T("[%.5d] WlxLoggedOutSAS(pWlxContext == %p) -> Answer was NO -> logoff enforced)"), ::GetCurrentProcessId(), pWlxContext);
					// Logoff the user if he did not agree
					ThisApp->GINA().pf.pfWlxLogoff(pWlxContext);
					return WLX_SAS_ACTION_NONE;
				}
			}
			// If news mode is active, let's show the message
			if (ThisApp->GetCfg().NewsActive)
			{
				Dbg(_T("[%.5d] WlxLoggedOutSAS(pWlxContext == %p) -> Showing news)"), ::GetCurrentProcessId(), pWlxContext);
				// Show news if applicable
				CShowMessageDlg dlg;
				dlg.SetUrlOrText(ThisApp->GetCfg().NewsText);
				dlg.DoModal();
			}
		}
	}

	if(ret == WLX_SAS_ACTION_LOGON)
	{
		Dbg(_T("[%.5d] WlxLoggedOutSAS(pWlxContext == %p) -> Setting user information)"), ::GetCurrentProcessId(), pWlxContext);
		// Set information for the thread which returns user informations
		ThisApp->SetUserData(*phToken, pMprNotifyInfo->pszDomain, pMprNotifyInfo->pszUserName, !override && ThisApp->GetCfg().AllowOnlyGuest);
	}

	return ret;
}

BOOL
WINAPI
WlxActivateUserShell(
    PVOID                   pWlxContext,
    PWSTR                   pszDesktopName,
    PWSTR                   pszMprLogonScript,
    PVOID                   pEnvironment
    )
{
	Dbg(_T("[%.5d] ~WlxActivateUserShell(pWlxContext == %p, pszDesktopName == \"%s\")"), ::GetCurrentProcessId(), pWlxContext, pszDesktopName);
	// Necessary if we refer to MFC instances
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// Pass this call to original GINA instance
	return ThisApp->GINA().pf.pfWlxActivateUserShell(pWlxContext, pszDesktopName, pszMprLogonScript, pEnvironment);
}

int
WINAPI
WlxLoggedOnSAS(
    PVOID                   pWlxContext,
    DWORD                   dwSasType,
    PVOID                   pReserved
    )
{
	Dbg(_T("[%.5d] ~WlxLoggedOnSAS(pWlxContext == %p, dwSasType == %.8X)"), ::GetCurrentProcessId(), pWlxContext, dwSasType);
	// Necessary if we refer to MFC instances
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// Pass this call to original GINA instance
	return ThisApp->GINA().pf.pfWlxLoggedOnSAS(pWlxContext, dwSasType, pReserved);
}

VOID
WINAPI
WlxDisplayLockedNotice(
    PVOID                   pWlxContext
    )
{
	Dbg(_T("[%.5d] ~WlxDisplayLockedNotice(pWlxContext == %p)"), ::GetCurrentProcessId(), pWlxContext);
	// Necessary if we refer to MFC instances
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// Pass this call to original GINA instance
	ThisApp->GINA().pf.pfWlxDisplayLockedNotice(pWlxContext);
}

int
WINAPI
WlxWkstaLockedSAS(
    PVOID                   pWlxContext,
    DWORD                   dwSasType
    )
{
	Dbg(_T("[%.5d] ~WlxWkstaLockedSAS(pWlxContext == %p, dwSasType == %.8X)"), ::GetCurrentProcessId(), pWlxContext, dwSasType);
	// Necessary if we refer to MFC instances
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// Pass this call to original GINA instance
	return ThisApp->GINA().pf.pfWlxWkstaLockedSAS(pWlxContext, dwSasType);
}

BOOL
WINAPI
WlxIsLockOk(
    PVOID                   pWlxContext
    )
{
	Dbg(_T("[%.5d] ~WlxIsLockOk(pWlxContext == %p)"), ::GetCurrentProcessId(), pWlxContext);
	// Necessary if we refer to MFC instances
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// Pass this call to original GINA instance
	return ThisApp->GINA().pf.pfWlxIsLockOk(pWlxContext);
}

BOOL
WINAPI
WlxIsLogoffOk(
    PVOID                   pWlxContext
    )
{
	Dbg(_T("[%.5d] ~WlxIsLogoffOk(pWlxContext == %p)"), ::GetCurrentProcessId(), pWlxContext);
	// Necessary if we refer to MFC instances
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// Pass this call to original GINA instance
	return ThisApp->GINA().pf.pfWlxIsLogoffOk(pWlxContext);
}

VOID
WINAPI
WlxLogoff(
    PVOID                   pWlxContext
    )
{
	Dbg(_T("[%.5d] WlxShutdown(pWlxContext == %p)"), ::GetCurrentProcessId(), pWlxContext);
	// Necessary if we refer to MFC instances
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// Pass this call to original GINA instance
	Dbg(_T("[%.5d] WlxShutdown(pWlxContext == %p) -> Cleanup of user information"), ::GetCurrentProcessId(), pWlxContext);
	ThisApp->SetUserData(NULL, NULL, NULL);
	ThisApp->GINA().pf.pfWlxLogoff(pWlxContext);
	// Simulate Ctrl+Alt+Del
	if (ThisApp->GetCfg().AllowOnlyGuest)
	{
		Dbg(_T("[%.5d] WlxShutdown(pWlxContext == %p) -> simulating Ctrl+Alt+Del SAS"), ::GetCurrentProcessId(), pWlxContext);
		ThisApp->GINA().OrigWinlogonFunctions->WlxSasNotify(ThisApp->GINA().hWinlogon, WLX_SAS_TYPE_CTRL_ALT_DEL);
	}
}

VOID
WINAPI
WlxShutdown(
    PVOID                   pWlxContext,
    DWORD                   ShutdownType
    )
{
	Dbg(_T("[%.5d] ~WlxShutdown(pWlxContext == %p, ShutdownType == %.8X)"), ::GetCurrentProcessId(), pWlxContext, ShutdownType);
	// Necessary if we refer to MFC instances
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// Pass this call to original GINA instance
	ThisApp->GINA().pf.pfWlxShutdown(pWlxContext, ShutdownType);
}

BOOL
WINAPI
WlxScreenSaverNotify(
    PVOID                   pWlxContext,
    BOOL *                  pSecure
	)
{
	Dbg(_T("[%.5d] ~WlxScreenSaverNotify(pWlxContext == %p)"), ::GetCurrentProcessId(), pWlxContext);
	// Necessary if we refer to MFC instances
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// Pass this call to original GINA instance
	return ThisApp->GINA().pf.pfWlxScreenSaverNotify(pWlxContext, pSecure);
}

BOOL
WINAPI
WlxStartApplication(
    PVOID                   pWlxContext,
    PWSTR                   pszDesktopName,
    PVOID                   pEnvironment,
    PWSTR                   pszCmdLine
    )
{
	Dbg(_T("[%.5d] ~WlxStartApplication(pWlxContext == %p, pszDesktopName == \"%s\", pszCmdLine == \"%s\")"), ::GetCurrentProcessId(), pWlxContext, pszDesktopName, pszCmdLine);
	// Necessary if we refer to MFC instances
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// Pass this call to original GINA instance
	return ThisApp->GINA().pf.pfWlxStartApplication(pWlxContext, pszDesktopName, pEnvironment, pszCmdLine);
}

BOOL
WINAPI
WlxNetworkProviderLoad(
    PVOID                   pWlxContext,
    PWLX_MPR_NOTIFY_INFO    pNprNotifyInfo
    )
{
	Dbg(_T("[%.5d] ~WlxNetworkProviderLoad(pWlxContext == %p)"), ::GetCurrentProcessId(), pWlxContext);
	// Necessary if we refer to MFC instances
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// Pass this call to original GINA instance
	return ThisApp->GINA().pf.pfWlxNetworkProviderLoad(pWlxContext, pNprNotifyInfo);
}

BOOL
WINAPI
WlxDisplayStatusMessage(
    PVOID                   pWlxContext,
    HDESK                   hDesktop,
    DWORD                   dwOptions,
    PWSTR                   pTitle,
    PWSTR                   pMessage
    )
{
	Dbg(_T("[%.5d] ~WlxDisplayStatusMessage(pWlxContext == %p)"), ::GetCurrentProcessId(), pWlxContext);
	// Necessary if we refer to MFC instances
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// Pass this call to original GINA instance
	return ThisApp->GINA().pf.pfWlxDisplayStatusMessage(pWlxContext, hDesktop, dwOptions, pTitle, pMessage);
}

BOOL
WINAPI
WlxGetStatusMessage(
    PVOID                   pWlxContext,
    DWORD *                 pdwOptions,
    PWSTR                   pMessage,
    DWORD                   dwBufferSize
    )
{
	Dbg(_T("[%.5d] ~WlxGetStatusMessage(pWlxContext == %p)"), ::GetCurrentProcessId(), pWlxContext);
	// Necessary if we refer to MFC instances
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// Pass this call to original GINA instance
	return ThisApp->GINA().pf.pfWlxGetStatusMessage(pWlxContext, pdwOptions, pMessage, dwBufferSize);
}

BOOL
WINAPI
WlxRemoveStatusMessage(
    PVOID                   pWlxContext
    )
{
	Dbg(_T("[%.5d] ~WlxRemoveStatusMessage(pWlxContext == %p)"), ::GetCurrentProcessId(), pWlxContext);
	// Necessary if we refer to MFC instances
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// Pass this call to original GINA instance
	return ThisApp->GINA().pf.pfWlxRemoveStatusMessage(pWlxContext);
}

BOOL
WINAPI
WlxGetConsoleSwitchCredentials(
    PVOID                   pWlxContext,
    PVOID                   pCredInfo
    )
{
	Dbg(_T("[%.5d] ~WlxGetConsoleSwitchCredentials(pWlxContext == %p)"), ::GetCurrentProcessId(), pWlxContext);
	// Necessary if we refer to MFC instances
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// Pass this call to original GINA instance
	return ThisApp->GINA().pf.pfWlxGetConsoleSwitchCredentials (pWlxContext, pCredInfo);
}

VOID
WINAPI
WlxReconnectNotify(
    PVOID                   pWlxContext
    )
{
	Dbg(_T("[%.5d] ~WlxReconnectNotify(pWlxContext == %p)"), ::GetCurrentProcessId(), pWlxContext);
	// Necessary if we refer to MFC instances
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// Pass this call to original GINA instance
	ThisApp->GINA().pf.pfWlxReconnectNotify(pWlxContext);
}

VOID
WINAPI
WlxDisconnectNotify(
    PVOID                   pWlxContext
    )
{
	Dbg(_T("[%.5d] ~WlxDisconnectNotify(pWlxContext == %p)"), ::GetCurrentProcessId(), pWlxContext);
	// Necessary if we refer to MFC instances
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// Pass this call to original GINA instance
	ThisApp->GINA().pf.pfWlxDisconnectNotify(pWlxContext);
}
