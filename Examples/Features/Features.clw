; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFeaturesView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Features.h"
LastPage=0

ClassCount=6
Class1=CFeaturesApp
Class2=CFeaturesDoc
Class3=CFeaturesView
Class4=CMainFrame

ResourceCount=6
Resource1=IDR_FEATURTYPE
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Class6=CChildFrame
Resource3=IDD_ABOUTBOX
Resource4=IDR_MAINFRAME (English (U.S.))
Resource5=IDR_FEATURTYPE (English (U.S.))
Resource6=IDD_ABOUTBOX (English (U.S.))

[CLS:CFeaturesApp]
Type=0
HeaderFile=Features.h
ImplementationFile=Features.cpp
Filter=N
LastObject=ID_APP_ABOUT

[CLS:CFeaturesDoc]
Type=0
HeaderFile=FeaturesDoc.h
ImplementationFile=FeaturesDoc.cpp
Filter=N
LastObject=CFeaturesDoc

[CLS:CFeaturesView]
Type=0
HeaderFile=FeaturesView.h
ImplementationFile=FeaturesView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=ID_VIEW_USEXPTHEMES

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
LastObject=CChildFrame
BaseClass=CMDIChildWnd
VirtualFilter=mfWC

[CLS:CAboutDlg]
Type=0
HeaderFile=Features.cpp
ImplementationFile=Features.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342181902
Control2=IDC_STATIC,static,1342308353
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342308353
Control5=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_APP_EXIT
Command3=ID_APP_ABOUT
CommandCount=3

[MNU:IDR_FEATURTYPE]
Type=1
Class=CFeaturesView
Command1=ID_FILE_NEW
Command2=ID_APP_EXIT
Command3=ID_APP_ABOUT
CommandCount=3

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
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

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_APP_EXIT
Command3=ID_APP_ABOUT
CommandCount=3

[MNU:IDR_FEATURTYPE (English (U.S.))]
Type=1
Class=CFeaturesView
Command1=ID_FILE_NEW
Command2=ID_APP_EXIT
Command3=ID_VIEW_USEXPTHEMES
Command4=ID_APP_ABOUT
CommandCount=4

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
ControlCount=5
Control1=IDC_STATIC,static,1342181902
Control2=IDC_STATIC,static,1342308353
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342308353
Control5=IDC_STATIC,static,1342308352

