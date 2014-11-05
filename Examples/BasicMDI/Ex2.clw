; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CEx2View
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ex2.h"
LastPage=0

ClassCount=7
Class1=CChildFrame
Class2=CAboutDlg
Class3=CEx2App
Class4=CEx2Doc
Class5=CEx2View
Class6=CMainFrame
Class7=MyCug

ResourceCount=3
Resource1=IDR_MAINFRAME (English (U.S.))
Resource2=IDR_EX2TYPE (English (U.S.))
Resource3=IDD_ABOUTBOX (English (U.S.))

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
VirtualFilter=mfWC
LastObject=CChildFrame

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=Ex2.cpp
ImplementationFile=Ex2.cpp

[CLS:CEx2App]
Type=0
BaseClass=CWinApp
HeaderFile=Ex2.h
ImplementationFile=Ex2.cpp

[CLS:CEx2Doc]
Type=0
BaseClass=CDocument
HeaderFile=Ex2Doc.h
ImplementationFile=Ex2Doc.cpp
Filter=N
VirtualFilter=DC
LastObject=CEx2Doc

[CLS:CEx2View]
Type=0
BaseClass=CView
HeaderFile=Ex2View.h
ImplementationFile=Ex2View.cpp
Filter=C
VirtualFilter=VWC
LastObject=ID_VIEW_USEXPTHEMES

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=CMainFrame

[CLS:MyCug]
Type=0
BaseClass=CUGCtrl
HeaderFile=Mycug.h
ImplementationFile=Mycug.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[MNU:IDR_EX2TYPE (English (U.S.))]
Type=1
Class=CEx2View
Command1=ID_FILE_NEW
Command2=ID_FILE_CLOSE
Command3=ID_APP_EXIT
Command4=ID_VIEW_USEXPTHEMES
Command5=ID_WINDOW_NEW
Command6=ID_WINDOW_CASCADE
Command7=ID_WINDOW_TILE_HORZ
Command8=ID_WINDOW_ARRANGE
Command9=ID_APP_ABOUT
CommandCount=9

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_APP_EXIT
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
ControlCount=5
Control1=IDC_STATIC,static,1342308481
Control2=IDC_STATIC,static,1342308353
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342177281
Control5=IDC_STATIC,static,1342181390

