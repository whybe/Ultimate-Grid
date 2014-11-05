; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTextDlg
LastTemplate=generic CWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Text.h"

ClassCount=4
Class1=CTextApp
Class2=CTextDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_TEXT_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDD_TEXT_DIALOG (English (U.S.))
Class4=CMyGrid
Resource5=IDD_ABOUTBOX (English (U.S.))

[CLS:CTextApp]
Type=0
HeaderFile=Text.h
ImplementationFile=Text.cpp
Filter=N

[CLS:CTextDlg]
Type=0
HeaderFile=TextDlg.h
ImplementationFile=TextDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_CHECKXP

[CLS:CAboutDlg]
Type=0
HeaderFile=TextDlg.h
ImplementationFile=TextDlg.cpp
Filter=D

[DLG:IDD_TEXT_DIALOG]
Type=1
Class=CTextDlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_GRID,static,1342308352

[CLS:CMyGrid]
Type=0
HeaderFile=MyGrid.h
ImplementationFile=MyGrid.cpp
BaseClass=generic CWnd
Filter=W

[DLG:IDD_ABOUTBOX]
Type=1
Class=?
ControlCount=3
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDOK,button,1342373889

[DLG:IDD_TEXT_DIALOG (English (U.S.))]
Type=1
Class=CTextDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_GRID,static,1342308352
Control3=IDC_CHECKXP,button,1342242819

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=3
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDOK,button,1342373889

