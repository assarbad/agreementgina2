; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSimpTaskmanDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SimpTaskman.h"

ClassCount=3
Class1=CSimpTaskmanApp
Class2=CSimpTaskmanDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX (English (U.S.))
Resource2=IDR_MAINFRAME
Resource3=IDD_SIMPTASKMAN_DIALOG (English (U.S.))
Resource4=IDD_DIALOG_TASKMAN (Neutral)

[CLS:CSimpTaskmanApp]
Type=0
HeaderFile=SimpTaskman.h
ImplementationFile=SimpTaskman.cpp
Filter=N

[CLS:CAboutDlg]
Type=0
HeaderFile=SimpTaskmanDlg.h
ImplementationFile=SimpTaskmanDlg.cpp
Filter=D

[DLG:IDD_SIMPTASKMAN_DIALOG (English (U.S.))]
Type=1
Class=CSimpTaskmanDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DIALOG_TASKMAN (Neutral)]
Type=1
Class=?
ControlCount=5
Control1=IDC_LIST1,listbox,1344341251
Control2=IDC_STATIC_DESC,static,1342308353
Control3=IDC_STATIC_USERNAME,static,1342308993
Control4=IDC_BUTTON_REFRESH,button,1342242816
Control5=IDCANCEL,button,1342242817

[CLS:CSimpTaskmanDlg]
Type=0
HeaderFile=simptaskmandlg.h
ImplementationFile=simptaskmandlg.cpp
BaseClass=CDialog
LastObject=CSimpTaskmanDlg

