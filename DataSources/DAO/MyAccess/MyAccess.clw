; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMySQLDlg
LastTemplate=generic CWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "myaccess.h"
LastPage=0

ClassCount=10
Class1=CChildFrame
Class2=CMainFrame
Class3=CMyAccessApp
Class4=CAboutDlg
Class5=CMyAccessDoc
Class6=CMyAccessView
Class7=CMySQLDlg
Class8=CUGAccessCtrl

ResourceCount=4
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Resource3=IDR_MYACCETYPE
Class9=CAccessTopHdng
Class10=CAccessSideHdng
Resource4=IDD_SQLDIALOG

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
LastObject=CChildFrame

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
LastObject=ID_FILE_OPEN
Filter=T
VirtualFilter=fWC

[CLS:CMyAccessApp]
Type=0
BaseClass=CWinApp
HeaderFile=MyAccess.h
ImplementationFile=MyAccess.cpp
LastObject=CMyAccessApp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=MyAccess.cpp
ImplementationFile=MyAccess.cpp
LastObject=CAboutDlg

[CLS:CMyAccessDoc]
Type=0
BaseClass=CDocument
HeaderFile=MyAccessDoc.h
ImplementationFile=MyAccessDoc.cpp
LastObject=CMyAccessDoc
Filter=N
VirtualFilter=DC

[CLS:CMyAccessView]
Type=0
BaseClass=CView
HeaderFile=MyAccessView.h
ImplementationFile=MyAccessView.cpp
Filter=C
VirtualFilter=VWC
LastObject=CMyAccessView

[CLS:CMySQLDlg]
Type=0
BaseClass=CDialog
HeaderFile=mysqldlg.h
ImplementationFile=mysqldlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=CMySQLDlg

[CLS:CUGAccessCtrl]
Type=0
BaseClass=CUGCtrl
HeaderFile=Ugaccess.h
ImplementationFile=ugaccess.cpp
LastObject=CUGAccessCtrl

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342308480
Control2=IDC_STATIC,static,1342308352
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_SQLDIALOG]
Type=1
Class=CMySQLDlg
ControlCount=15
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_COMBO1,combobox,1344340290
Control5=IDC_COMBO2,combobox,1344340227
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_GHOST,button,1342242819
Control9=IDC_ALLOWEDIT,button,1342242819
Control10=IDC_PATH,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_COMBO4,combobox,1344340227
Control13=IDC_STATIC,button,1342177287
Control14=IDC_NUMSH,button,1342242819
Control15=IDC_BASE1,button,1342242819

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_SAVE
Command3=ID_EDIT_CUT
Command4=ID_EDIT_COPY
Command5=ID_EDIT_PASTE
Command6=ID_FILE_PRINT
Command7=ID_APP_ABOUT
CommandCount=7

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_PRINT_SETUP
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_APP_ABOUT
CommandCount=7

[MNU:IDR_MYACCETYPE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_PRINT
Command5=ID_FILE_PRINT_PREVIEW
Command6=ID_FILE_PRINT_SETUP
Command7=ID_FILE_MRU_FILE1
Command8=ID_APP_EXIT
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_VIEW_TOOLBAR
Command14=ID_VIEW_STATUS_BAR
Command15=ID_WINDOW_CASCADE
Command16=ID_WINDOW_TILE_HORZ
Command17=ID_WINDOW_ARRANGE
Command18=ID_APP_ABOUT
CommandCount=18

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[CLS:CAccessTopHdng]
Type=0
HeaderFile=AccessTopHdng.h
ImplementationFile=AccessTopHdng.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CAccessTopHdng

[CLS:CAccessSideHdng]
Type=0
HeaderFile=AccessSideHdng.h
ImplementationFile=AccessSideHdng.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CAccessSideHdng

