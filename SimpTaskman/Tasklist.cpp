/******************************************************************************
 ******************************************************************************
 ***                                                                        ***
 ***   Simple class to hold a list of processes and refresh this list,      ***
 ***   including memory management. Uses NT/2000/XP Native API              ***
 ***                                                                        ***
 ******************************************************************************
 ******************************************************************************

                                 _\\|//_
                                (` * * ')
 ______________________________ooO_(_)_Ooo_____________________________________
 ******************************************************************************
 ******************************************************************************
 ***                                                                        ***
 ***                Copyright (c) 2004 - 2005 by -=Assarbad=-               ***
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

 Copyright (c) 2004-2005, -=Assarbad=- ["copyright holder(s)"]
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
#include "SimpTaskman.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace NT;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTasklist::CTasklist()
	: m_ProcessInfo(NULL)
{
	if (hMod)
		FreeLibrary(hMod);

	hMod = LoadLibrary(_T("ntdll.dll"));
	if (hMod != NULL)
		pfZwQuerySystemInformation =
			NT::PFZWQUERYSYSTEMINFORMATION(GetProcAddress(hMod, "ZwQuerySystemInformation"));
	m_Inited = (pfZwQuerySystemInformation != NULL);
}

CTasklist::~CTasklist()
{
	FreeLibrary(hMod);
}

BOOL CTasklist::RefreshData()
{
// Define shorthands. Not sure whether malloc/free would work.
#define ALLOC(x)	VirtualAlloc(NULL, x, MEM_COMMIT, PAGE_READWRITE)
#define FREE(x)		{VirtualFree(x, 0, MEM_RELEASE); x = NULL;}

	if(!m_Inited)
		return FALSE;
	
	BOOL result = TRUE;
	NTSTATUS Status;

	if(m_ProcessInfo != NULL)
		FREE(m_ProcessInfo);

	m_CurrentSize = 64 * 1024;
	m_ProcessInfo = ALLOC(m_CurrentSize);

	while(result)
	{
		if(m_ProcessInfo != NULL)
		{
			Status = pfZwQuerySystemInformation(
						NT::SystemProcessesAndThreadsInformation,
						m_ProcessInfo,
						m_CurrentSize,
						NULL
						);
			if(Status >= 0)
				break;

			// Unknown buffer
			if(Status != STATUS_INFO_LENGTH_MISMATCH)
			{
				result = FALSE;
				// Free old buffer
				FREE(m_ProcessInfo);
				break;
			}
		}

		// Free old buffer
		if(m_ProcessInfo != NULL)
			FREE(m_ProcessInfo);

		// Double size to allocate
		m_CurrentSize *= 2;

		// Allocate required size
		m_ProcessInfo = ALLOC(m_CurrentSize);

		// Check buffer
		if(m_ProcessInfo == NULL)
		{
			// Not enough memory
			result = FALSE;
			break;
		}
	}
	return result;
}

const PSYSTEM_PROCESSES CTasklist::GetProcessInfo()
{
	return PSYSTEM_PROCESSES(m_ProcessInfo);
}
