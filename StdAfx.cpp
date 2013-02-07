// stdafx.cpp : source file that includes just the standard includes
//	AgreementGINA2.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

void MyOutputDebugString(LPCTSTR str, ...)
{
	CString txt;
	va_list marker;
	va_start(marker, str);
	txt.FormatV(str, marker);
	txt += _T("\n");
	va_end(marker);
	OutputDebugString(txt);

	try
	{
		CTime time = CTime::GetCurrentTime();
		CString temp = time.Format(_T("%Y-%m-%d@%H:%M:%S -> "));
		temp += txt;

		CStdioFile file(_T("C:\\GINAlog.txt"), CFile::modeReadWrite | CFile::modeNoTruncate | CFile::modeCreate | CFile::shareDenyWrite);
		file.SeekToEnd();
		file.WriteString(temp);
		file.Flush();
		file.Close();
	}
	catch(CFileException)
	{
	}
}
