; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=COpenDatabaseDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "dao sorting.h"
LastPage=0

ClassCount=8
Class1=CChildFrame
Class2=CDAOsortingApp
Class3=CAboutDlg
Class4=CDAOsortingDoc
Class5=CDAOsortingView
Class6=CMainFrame
Class7=MyCug
Class8=COpenDatabaseDlg

ResourceCount=8
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDR_DAOSORTYPE
Resource4=IDD_OPEN_DB
Resource5=IDR_MAINFRAME (English (U.S.))
Resource6=IDR_DAOSORTYPE (English (U.S.))
Resource7=IDD_ABOUTBOX (English (U.S.))
Resource8=IDD_OPEN_DB (English (U.S.))

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp

[CLS:CDAOsortingApp]
Type=0
BaseClass=CWinApp
HeaderFile=DAO sorting.h
ImplementationFile=DAO sorting.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=DAO sorting.cpp
ImplementationFile=DAO sorting.cpp
LastObject=CAboutDlg

[CLS:CDAOsortingDoc]
Type=0
BaseClass=CDocument
HeaderFile=DAO sortingDoc.h
ImplementationFile=DAO sortingDoc.cpp

[CLS:CDAOsortingView]
Type=0
BaseClass=CView
HeaderFile=DAO sortingView.h
ImplementationFile=DAO sortingView.cpp
Filter=C
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:MyCug]
Type=0
BaseClass=CUGCtrl
HeaderFile=Mycug97.h
ImplementationFile=Mycug97.cpp

[CLS:COpenDatabaseDlg]
Type=0
BaseClass=CDialog
HeaderFile=OpenDatabaseDlg.h
ImplementationFile=OpenDatabaseDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=COpenDatabaseDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_OPEN_DB]
Type=1
Class=COpenDatabaseDlg
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BROWSE,button,1342242816
Control4=IDC_STATIC,static,1342308864
Control5=IDC_FILE_NAME,edit,1350631552
Control6=IDC_SQL,edit,1352732804
Control7=IDC_ACCESS,button,1342308361
Control8=IDC_ACCESS2,button,1342177289
Control9=IDC_TABLE_NAME,edit,1484849280
Control10=IDC_OPEN_SQL,button,1342308361
Control11=IDC_OPEN_TABLE,button,1342177289

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_DAOSORTYPE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_APP_ABOUT
CommandCount=21

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

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_DAOSORTYPE (English (U.S.))]
Type=1
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_APP_ABOUT
CommandCount=21

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
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

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_OPEN_DB (English (U.S.))]
Type=1
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BROWSE,button,1342242816
Control4=IDC_STATIC,static,1342308864
Control5=IDC_FILE_NAME,edit,1350631552
Control6=IDC_SQL,edit,1352732804
Control7=IDC_ACCESS,button,1342308361
Control8=IDC_ACCESS2,button,1342177289
Control9=IDC_TABLE_NAME,edit,1484849280
Control10=IDC_OPEN_SQL,button,1342308361
Control11=IDC_OPEN_TABLE,button,1342177289

