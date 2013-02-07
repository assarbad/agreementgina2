/******************************************************************************
 ******************************************************************************
 ***                                                                        ***
 ***   Exported functions to allow easy installation of the GINA through    ***
 ***   its own functions.                                                   ***
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
#include <stdio.h>

/*
void FillDefaults(GinaCfg& defaults)
{
	defaults.AdminSkips = TRUE;

	defaults.BtnNoText = _T("&No");
	defaults.BtnYesText = _T("&Yes");
	defaults.CheckBoxText = _T("I hereby &accept the agreement and confirm to be authorized!");

	defaults.HTML_file = _T("about:blank");

	defaults.ListenPort = 11;

	defaults.MaintenanceMode = FALSE;
	defaults.MaintenanceText = _T("about:blank");

	defaults.NewsActive = FALSE;
	defaults.NewsText = _T("about:blank");

	defaults.ShowTimer = FALSE;
	defaults.TimerDuration = 10;

	defaults.AllowOnlyGuest = FALSE;

	defaults.DisableLockWorkstation = FALSE;
	defaults.DisableChangePassword = FALSE;
	defaults.DisableTaskMgr = FALSE;
}

void ReadOldValues(CRegKeyEx& key, GinaCfg& defaults)
{
	defaults.AdminSkips = TRUE;
	defaults.AdminNames = _T("Administrator");

	defaults.BtnNoText = _T("&No");
	defaults.BtnYesText = _T("&Yes");
	defaults.CheckBoxText = _T("I hereby &accept the agreement and confirm to be authorized!");

	defaults.HTML_file = _T("about:blank");

	defaults.ListenPort = 11;

	defaults.MaintenanceMode = FALSE;
	defaults.MaintenanceText = _T("about:blank");

	defaults.NewsActive = FALSE;
	defaults.NewsText = _T("about:blank");

	defaults.OnlyAdminLocks = FALSE;

	defaults.ShowTimer = FALSE;
	defaults.TimerDuration = 10;

	defaults.AllowOnlyGuest = FALSE;
	defaults.GuestName = _T("");
	defaults.GuestPassword = _T("");
}

#define SETVALUE(x, y) key.SetValue(y, x)

void WriteDefaults(CRegKeyEx& key, GinaCfg& defaults)
{
	SETVALUE(sAdminSkips, DWORD(defaults.AdminSkips));

	SETVALUE(sBtnNoText, defaults.BtnNoText);
	SETVALUE(sBtnYesText, defaults.BtnYesText);
	SETVALUE(sCheckBoxText, defaults.CheckBoxText);

	SETVALUE(sHTML_file, defaults.HTML_file);

	SETVALUE(sListenPort, defaults.ListenPort);

	SETVALUE(sMaintenanceMode, defaults.MaintenanceMode);
	SETVALUE(sMaintenanceText, defaults.MaintenanceText);

	SETVALUE(sNewsActive, defaults.NewsActive);
	SETVALUE(sNewsText, defaults.NewsText);

	SETVALUE(sShowTimer, defaults.ShowTimer);
	SETVALUE(sTimerDuration, defaults.TimerDuration);

	SETVALUE(sAllowOnlyGuest, defaults.AllowOnlyGuest);

// Delete old-style values (old names "Caption" is now "Title" and "Notice" now "Text")
	key.DeleteValue(_T("AdminNames"));
	key.DeleteValue(_T("OnlyAdminLocks"));
	key.DeleteValue(_T("MaintenanceNotice"));
// Title is taken from the HTML documents now
	key.DeleteValue(_T("DialogCaption"));
	key.DeleteValue(_T("NewsCaption"));
	key.DeleteValue(_T("MaintenanceCaption"));
}

BOOL __declspec(dllexport) WINAPI Install()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	GinaCfg defaults;
	FillDefaults(defaults);
// Create instance
	CRegKeyEx key;
// Open the Winlogon key
	key.Create(HKEY_LOCAL_MACHINE, WinlogonKey);
// Find out wether a replacement exists already
	CString temp = key.ReadString(GinaDLL);
	key.Create(key.m_hKey, ThisName);
	if (temp.CompareNoCase(ThisDLL) != 0)
		// Some other replacement exists, save the old value
		SETVALUE(sOldGINA, temp);
//	else
		// Use the values found
//		ReadOldValues(key, defaults);

	WriteDefaults(key, defaults);
	key.Open(HKEY_LOCAL_MACHINE, WinlogonKey);
// Write the name of this GINA replacement DLL
	SETVALUE(GinaDLL, ThisDLL);
	key.Close();
	return TRUE;
}

BOOL __declspec(dllexport) WINAPI Uninstall()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
// Create instance
	CRegKeyEx key;
// Open the Winlogon key
	key.Open(HKEY_LOCAL_MACHINE, WinlogonKey);
	key.Open(key.m_hKey, ThisName);
	CString temp = key.ReadString(sOldGINA);
	key.Open(HKEY_LOCAL_MACHINE, WinlogonKey);
	key.RecurseDeleteKey(ThisName);
	if (temp.GetLength() != 0)
		SETVALUE(GinaDLL, temp);
	else
		key.DeleteValue(GinaDLL);
	key.Close();
	return TRUE;
}
*/

VOID __declspec(dllexport) WINAPI CfgDialog()
{
	Dbg(_T("CfgDialog() is being called! %s"), _T("xyz"));

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CConfigureGINA zdlg;
	zdlg.DoModal();
}
