; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CEx13View
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ex13.h"
LastPage=0

ClassCount=7
Class1=CAdjuster
Class2=CAboutDlg
Class3=CEx13App
Class4=CEx13Doc
Class5=CEx13View
Class6=CMainFrame
Class7=MyCug

ResourceCount=3
Resource1=IDR_MAINFRAME (English (U.S.))
Resource2=IDD_ABOUTBOX (English (U.S.))
Resource3=IDD_COL_ROW_ADJ (English (U.S.))

[CLS:CAdjuster]
Type=0
BaseClass=CDialog
HeaderFile=Adjust.h
ImplementationFile=Adjust.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=Ex13.cpp
ImplementationFile=Ex13.cpp
LastObject=ID_VIEW_USEXPTHEMES

[CLS:CEx13App]
Type=0
BaseClass=CWinApp
HeaderFile=Ex13.h
ImplementationFile=Ex13.cpp

[CLS:CEx13Doc]
Type=0
BaseClass=CDocument
HeaderFile=Ex13Doc.h
ImplementationFile=Ex13Doc.cpp

[CLS:CEx13View]
Type=0
BaseClass=CView
HeaderFile=Ex13View.h
ImplementationFile=Ex13View.cpp
Filter=C
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:MyCug]
Type=0
BaseClass=CUGCtrl
HeaderFile=Mycug.h
ImplementationFile=Mycug.cpp

[DLG:IDD_COL_ROW_ADJ]
Type=1
Class=CAdjuster

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_APP_EXIT
Command2=ID_VIEW_USEXPTHEMES
Command3=ID_APP_ABOUT
CommandCount=3

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342183438
Control2=IDC_STATIC,static,1342308353
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342308353

[DLG:IDD_COL_ROW_ADJ (English (U.S.))]
Type=1
Class=?
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308354
Control4=IDC_STATIC,static,1342308354
Control5=IDC_STATIC,static,1342308354
Control6=IDC_STATIC,static,1342308354
Control7=IDC_ROW_HEIGHT,edit,1350639744
Control8=IDC_COL_WIDTH,edit,1350639744
Control9=IDC_TOP_H_HEIGHT,edit,1350639744
Control10=IDC_SIDE_H_WIDTH,edit,1350639744

