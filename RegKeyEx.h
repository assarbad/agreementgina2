// RegKeyEx.h: interface for the CRegKeyEx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGKEYEX_H__F9A08E2F_6368_42B5_9EF7_CC25B43723A1__INCLUDED_)
#define AFX_REGKEYEX_H__F9A08E2F_6368_42B5_9EF7_CC25B43723A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <atlbase.h>

class CRegKeyEx : public CRegKey  
{
public:
	CRegKeyEx();
	virtual ~CRegKeyEx();
	CString ReadString(LPCTSTR lpszValueName);
	bool ReadBool(LPCTSTR lpszValueName);
	DWORD ReadDWORD(LPCTSTR lpszValueName);
	bool ValueExists(LPCTSTR lpszValueName);
};

#endif // !defined(AFX_REGKEYEX_H__F9A08E2F_6368_42B5_9EF7_CC25B43723A1__INCLUDED_)
