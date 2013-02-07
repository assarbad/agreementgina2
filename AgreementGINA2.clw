; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAgreementDlg
LastTemplate=CAsyncSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "agreementgina2.h"
LastPage=0

ClassCount=4
Class1=CAgreementDlg
Class2=CAgreementGINA2App

ResourceCount=5
Resource1=IDD_SHOWMESSAGEDLG (Neutral)
Class3=CShowMessageDlg
Resource2=IDR_MENU_LB (Neutral)
Class4=CConfigureGINA
Resource3=IDD_CONFIGUREDLG (Neutral)
Resource4=IDD_DIALOG_TASKMAN (Neutral)
Resource5=IDD_AGREEMENTDLG_DIALOG (Neutral)

[CLS:CAgreementDlg]
Type=0
BaseClass=CDialog
HeaderFile=AgreementDlg.h
ImplementationFile=AgreementDlg.cpp
LastObject=IDC_EXPLORER1
Filter=W
VirtualFilter=dWC

[CLS:CAgreementGINA2App]
Type=0
BaseClass=CWinApp
HeaderFile=AgreementGINA2.h
ImplementationFile=AgreementGINA2.cpp
LastObject=IDC_EXPLORER1

[DLG:IDD_AGREEMENTDLG_DIALOG]
Type=1
Class=CAgreementDlg

[DLG:IDD_AGREEMENTDLG_DIALOG (Neutral)]
Type=1
Class=CAgreementDlg
ControlCount=6
Control1=IDC_BUTTON_NO,button,1342242816
Control2=IDC_CHECK_AGREE,button,1342245891
Control3=IDC_BUTTON_YES,button,1342242816
Control4=IDC_PROGRESS,msctls_progress32,1342177281
Control5=IDC_STATIC_TIMER,static,1342308353
Control6=IDC_EXPLORER1,{8856F961-340A-11D0-A96B-00C04FD705A2},1342242816

[DLG:IDD_SHOWMESSAGEDLG (Neutral)]
Type=1
Class=CShowMessageDlg
ControlCount=2
Control1=IDC_BUTTON_OK,button,1342242817
Control2=IDC_EXPLORER1,{8856F961-340A-11D0-A96B-00C04FD705A2},1342177280

[CLS:CShowMessageDlg]
Type=0
HeaderFile=showmessagedlg.h
ImplementationFile=showmessagedlg.cpp
BaseClass=CDialog
LastObject=CShowMessageDlg
Filter=D
VirtualFilter=dWC

[DLG:IDD_CONFIGUREDLG (Neutral)]
Type=1
Class=CConfigureGINA
ControlCount=46
Control1=IDC_STATIC_SETTINGSAGREEMENT,button,1342177287
Control2=IDC_BUTTON_AGREEMENT,button,1342242816
Control3=IDC_EDIT_AGREEMENT,edit,1344344196
Control4=IDC_CHECK_SHOWTIMER,button,1342275587
Control5=IDC_EDIT_TIMERDURATION,edit,1342253185
Control6=IDC_SPIN_TIMERDURATION,msctls_updown32,1342177334
Control7=IDC_STATIC_TIMERDURATION,static,1342308352
Control8=IDC_STATIC_SETTINGSNEWS,button,1342177287
Control9=IDC_BUTTON_NEWS,button,1342242816
Control10=IDC_EDIT_NEWS,edit,1344344196
Control11=IDC_BUTTON_MAINTENANCE,button,1342242816
Control12=IDC_EDIT_MAINTENANCE,edit,1344344196
Control13=IDC_CHECK_MAINTENANCE,button,1342275587
Control14=IDC_CHECK_NEWS,button,1342275587
Control15=IDC_STATIC_SETTINGSRESTRICTIONS,button,1342177287
Control16=IDC_CHECK_LOCKWKSTA,button,1342275587
Control17=IDC_CHECK_CHANGEPASS,button,1342275587
Control18=IDC_CHECK_TASKMAN,button,1342275587
Control19=IDC_CHECK_TASKMAN2,button,1342275587
Control20=IDC_EDIT_REPLTASKMAN,edit,1342242944
Control21=IDC_BUTTON_REPLTASKMAN,button,1342242816
Control22=IDC_STATIC_SETTINGSCAPTIONS,button,1342177287
Control23=IDC_STATIC_YES,static,1342308352
Control24=IDC_EDIT_YES,edit,1342242944
Control25=IDC_STATIC_NO,static,1342308352
Control26=IDC_EDIT_NO,edit,1342242944
Control27=IDC_STATIC_CHECKBOX,static,1342308352
Control28=IDC_EDIT_CHECKBOX,edit,1342242944
Control29=IDC_STATIC_GENERAL,button,1342177287
Control30=IDC_STATIC_GUESTUSER,static,1342308354
Control31=IDC_EDIT_GUESTUSER,edit,1342242944
Control32=IDC_STATIC_DOMAIN,static,1342308354
Control33=IDC_EDIT_GUESTDOMAIN,edit,1342242944
Control34=IDC_STATIC_PASSWORD,static,1342308354
Control35=IDC_EDIT_GUESTPASSWORD,edit,1342242976
Control36=IDC_STATIC_PASSWORD2,static,1342308354
Control37=IDC_EDIT_GUESTPASSWORD2,edit,1342242976
Control38=IDC_CHECK_ONLYGUEST,button,1342275587
Control39=IDC_CHECK_ADMINSKIPS,button,1342275587
Control40=IDC_STATIC_PORTNUM,static,1342308354
Control41=IDC_EDIT_PORTNUM,edit,1342253185
Control42=IDC_SPIN_PORTNUM,msctls_updown32,1342177334
Control43=IDC_BUTTON_SAVE,button,1342242816
Control44=IDCANCEL,button,1342242816
Control45=IDOK,button,1342242817
Control46=IDC_BUTTON_ABOUT,button,1342177280

[CLS:CConfigureGINA]
Type=0
HeaderFile=ConfigureGINA.h
ImplementationFile=ConfigureGINA.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CConfigureGINA

[DLG:IDD_DIALOG_TASKMAN (Neutral)]
Type=1
Class=?
ControlCount=5
Control1=IDC_LIST1,listbox,1344341251
Control2=IDC_STATIC_DESC,static,1342308353
Control3=IDC_STATIC_USERNAME,static,1342308993
Control4=IDC_BUTTON_REFRESH,button,1342242816
Control5=IDCANCEL,button,1342242817

[MNU:IDR_MENU_LB (Neutral)]
Type=1
Class=?
Command1=ID_KILLPROCESS
Command2=ID_REFRESHLIST
CommandCount=2

