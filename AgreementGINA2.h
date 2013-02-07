// AgreementGINA2.h : main header file for the AGREEMENTGINA2 DLL
//

#if !defined(AFX_AGREEMENTGINA2_H__B9F32E66_AC6A_41FA_A78E_6591D6825850__INCLUDED_)
#define AFX_AGREEMENTGINA2_H__B9F32E66_AC6A_41FA_A78E_6591D6825850__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include <WinWlx.h>			// GINA specific stuff
#include <Winsock2.h>
#include <Ntsecapi.h>
#include "RegKeyEx.h"
#include "GINA_exports.h"

const LPCTSTR WinlogonKey		= _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon");
const LPCTSTR GinaDLL			= _T("GinaDLL");
const LPCTSTR ThisName			= _T("AgreementGINA");
const LPCTSTR ThisName_User		= _T("{AgreementGINA}.user");
const LPCTSTR ThisName_Passwd	= _T("{AgreementGINA}.password");
const LPCTSTR ThisName_Domain	= _T("{AgreementGINA}.domain");
const LPCTSTR sLogonType		= _T("LogonType");

const LPCTSTR sOldGINA			= _T("Old GinaDLL value");
const LPCTSTR sAdminSkips		= _T("AdminSkips");
const LPCTSTR sBtnNoText		= _T("BtnNoText");
const LPCTSTR sBtnYesText		= _T("BtnYesText");
const LPCTSTR sCheckBoxText		= _T("CheckBoxText");
const LPCTSTR sHTML_file		= _T("HTML_file"); // this is the agreement
const LPCTSTR sListenPort		= _T("ListenPort");
const LPCTSTR sMaintenanceMode	= _T("MaintenanceMode");
const LPCTSTR sMaintenanceText	= _T("MaintenanceText"); // was MaintenanceNotice
const LPCTSTR sNewsActive		= _T("NewsActive");
const LPCTSTR sNewsText			= _T("NewsText");
const LPCTSTR sShowTimer		= _T("ShowTimer");
const LPCTSTR sTimerDuration	= _T("TimerDuration");
const LPCTSTR sAllowOnlyGuest	= _T("AllowOnlyGuest");
const LPCTSTR sGuestName		= _T("GuestName");
const LPCTSTR sGuestPassword	= _T("GuestPassword");
const LPCTSTR sGuestDomain		= _T("GuestDomain");
const LPCTSTR sDisableLockWorkstation	= _T("DisableLockWorkstation");
const LPCTSTR sDisableChangePassword	= _T("DisableChangePassword");
const LPCTSTR sDisableTaskMgr			= _T("DisableTaskMgr");
// Autologon strings
const LPCTSTR sDefaultDomainName		= _T("DefaultDomainName");
const LPCTSTR sDefaultPassword			= _T("DefaultPassword");
const LPCTSTR sDefaultUserName			= _T("DefaultUserName");
const LPCTSTR sAutoAdminLogon			= _T("AutoAdminLogon");
const LPCTSTR sForceAutoLogon			= _T("ForceAutoLogon");
// Taskman replacement
const LPCTSTR sImageFileExecution		= _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options");
const LPCTSTR sReplacementTaskMgr		= _T("ReplacementTaskMgr");
const LPCTSTR sDebugger					= _T("Debugger");
const LPCTSTR sTaskMgr					= _T("taskmgr.exe");
const LPCTSTR sReplacedTaskman			= _T("ReplacedTaskman");

typedef struct tagGinaCfg
{
	BOOL	AdminSkips;

	CString	BtnNoText;
	CString	BtnYesText;
	CString	CheckBoxText;

	CString	HTML_file;

	DWORD	ListenPort;

	BOOL	MaintenanceMode;
	CString	MaintenanceText;

	BOOL	NewsActive;
	CString	NewsText;

	BOOL	ShowTimer;
	DWORD	TimerDuration;

// Override to admin logon holding down the shift key
	BOOL	AllowOnlyGuest;

// Restrictions only apply to non-admin users
	BOOL	DisableLockWorkstation;
	BOOL	DisableChangePassword;
	DWORD	DisableTaskMgr;
	CString	ReplacementTaskMgr;
} GinaCfg;

typedef struct tagBackupCredentials
{
	CString DefaultDomainName;
	CString DefaultUserName;
	CString AutoAdminLogon;
	CString ForceAutoLogon;

	BOOL bDefaultDomainName;
	BOOL bDefaultUserName;
	BOOL bAutoAdminLogon;
	BOOL bForceAutoLogon;

	BOOL bDefaultPasswordReg;
	CString DefaultPasswordReg;
	BOOL bDefaultPasswordStash;
	CString DefaultPasswordStash;

	CRegKeyEx* key;
} BackupCredentials;

#define ThisApp reinterpret_cast<CAgreementGINA2App *>(AfxGetApp())
#define ThisDLL ThisApp->GetDllName()

#define clLtRed		RGB(0xFF, 0xDD, 0xDD)
#define clLtGreen	RGB(0xDD, 0xFF, 0xDD)
#define clLtBlue	RGB(0xDD, 0xDD, 0xFF)
#define clRed		RGB(0xFF, 0x00, 0x00)
#define clGreen		RGB(0x00, 0xFF, 0x00)
#define clBlue		RGB(0x00, 0x00, 0xFF)
#define clWhite		RGB(0xFF, 0xFF, 0xFF)
#define clGray		::GetSysColor(COLOR_3DFACE)
#define clLilac		RGB(0x40, 0x00, 0x60)

#include "AgreementDlg.h"
#include "ConfigureGINA.h"
#include "ShowMessageDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CAgreementGINA2App
// See AgreementGINA2.cpp for the implementation of this class
//
class CAgreementGINA2App : public CWinApp
{
public:
	CAgreementGINA2App();
	~CAgreementGINA2App();
	SOCKET sServer;
	void RunDlg();
	CString GetDllName();
	BOOL EncryptAndStorePassword(LPCTSTR key, LPCTSTR password);
	BOOL DecryptAndRetrievePassword(LPCTSTR key, CString& password);
	void ReadConfig();
	void ReadConfig(GinaCfg& cfg);
	void WriteConfig();
	void WriteConfig(GinaCfg& cfg);
//	GinaCfg& GetConfig();
	void SetUserData(HANDLE hToken, LPCTSTR pszDomain, LPCTSTR pszUserName, BOOL IsGuest = FALSE);
	BOOL IsAdmin(HANDLE hToken);
	BOOL RetrieveOriginalGinaFunctions();
	void SetFunctions(HANDLE hWlx, LPCTSTR lpWinsta, PVOID pWinlogonFunctions);
	MyGINA& GINA();
	GinaCfg& GetCfg();
	HANDLE GetToken();
	HMODULE GetModuleHandle();
	void GetModuleName(CString& str);
	BOOL IsRequiredVersion();
	BOOL IsStringURL(CString& str);
	void ReplaceAutologonCredentials();
	void RestoreAutologonCredentials();
	// Related to the "server part"
	BOOL WinsockInited();
	BOOL ListenPortChanged();
	BOOL ListenPortChangedReset();
	void SetListenPort(DWORD newPort);
	WORD GetListenPort();
	void WaitPortLock();
	void SendUserData(SOCKET& sClient);
	void CheckAllowUrls(VARIANT FAR* URL, BOOL &Cancel);

private:
	BOOL m_SocketsInitialised; // To know wether the windows sockets were inited
	WSADATA wsaData;
	CString m_dllName;
	GinaCfg m_Configuration;
	CString m_threadUsername;
	CString m_threadDomain;
	HANDLE m_threadToken;
	BOOL m_threadIsGuest;
	BOOL m_threadIsAdmin;
	SYSTEMTIME m_threadTime;
	CString sGinaPath;
	MyGINA m_GINA;
	DWORD m_MajorVer, m_MinorVer;
	BackupCredentials m_BC; // Backup credentials
	bool ReplaceTaskman();
	bool RestoreTaskman();
	bool IsReplacedTaskman();
	BOOL m_ListenPortChanged;
	DWORD m_ListenPort;
	CCriticalSection m_PortLock;
	CCriticalSection m_UserinfoLock;
	void URL_Encode(LPSTR &pc, int &len);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAgreementGINA2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CAgreementGINA2App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AGREEMENTGINA2_H__B9F32E66_AC6A_41FA_A78E_6591D6825850__INCLUDED_)
