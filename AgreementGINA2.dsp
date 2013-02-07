# Microsoft Developer Studio Project File - Name="AgreementGINA2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=AgreementGINA2 - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AgreementGINA2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AgreementGINA2.mak" CFG="AgreementGINA2 - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AgreementGINA2 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../Release"
# PROP Intermediate_Dir "../Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "UNICODE" /D "_UNICODE" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 Ws2_32.lib /nologo /subsystem:windows /dll /machine:I386 /out:"../Release/AgreementGINA.dll"
# Begin Custom Build
InputPath=\Projekte\AgreementGINA2\Release\AgreementGINA.dll
SOURCE="$(InputPath)"

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	buildinc.cmd

# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=hhc.exe ".\HtmlHelp\AgreementGINA2.hhp" & set ERRORLEVEL=0
# End Special Build Tool
# Begin Target

# Name "AgreementGINA2 - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AgreementDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AgreementGINA2.cpp
# End Source File
# Begin Source File

SOURCE=.\AgreementGINA2.def
# End Source File
# Begin Source File

SOURCE=.\ConfigureGINA.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomClientSite.cpp
# End Source File
# Begin Source File

SOURCE=.\GINA_exports.cpp
# End Source File
# Begin Source File

SOURCE=.\Installation.cpp
# End Source File
# Begin Source File

SOURCE=.\RegKeyEx.cpp
# End Source File
# Begin Source File

SOURCE=.\ShowMessageDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\webbrowser2.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AgreementDlg.h
# End Source File
# Begin Source File

SOURCE=.\AgreementGINA2.h
# End Source File
# Begin Source File

SOURCE=.\ConfigureGINA.h
# End Source File
# Begin Source File

SOURCE=.\CustomClientSite.h
# End Source File
# Begin Source File

SOURCE=.\GINA_exports.h
# End Source File
# Begin Source File

SOURCE=.\RegKeyEx.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ShowMessageDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\webbrowser2.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Group "HTML Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\res\about.htm
# End Source File
# Begin Source File

SOURCE=.\res\error.html
# End Source File
# Begin Source File

SOURCE=.\res\error_generic.htm
# End Source File
# Begin Source File

SOURCE=.\res\html_help.htm
# End Source File
# End Group
# Begin Source File

SOURCE=.\AgreementGINA2.rc
# End Source File
# Begin Source File

SOURCE=.\res\AgreementGINA2.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\assarbad.png
# End Source File
# End Target
# End Project
# Section AgreementGINA2 : {D30C1661-CDAF-11D0-8A3E-00C04FC9E26E}
# 	2:5:Class:CWebBrowser2
# 	2:10:HeaderFile:webbrowser2.h
# 	2:8:ImplFile:webbrowser2.cpp
# End Section
# Section AgreementGINA2 : {8856F961-340A-11D0-A96B-00C04FD705A2}
# 	2:21:DefaultSinkHeaderFile:webbrowser2.h
# 	2:16:DefaultSinkClass:CWebBrowser2
# End Section
# Section AgreementGINA2 : {20008E12-0000-0000-0500-05001C010000}
# 	1:18:IDR_AGREEMENTGINA2:1016
# End Section
# Section AgreementGINA2 : {20006E12-0000-0000-0A00-0A0011650000}
# 	1:18:IDR_AGREEMENTGINA2:1008
# End Section
# Section AgreementGINA2 : {6C2F2065-3020-3478-3037-202F666F2272}
# 	1:18:IDR_AGREEMENTGINA2:1015
# End Section
