; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSelectSQLDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "db7.h"
LastPage=0

ClassCount=9
Class1=CChildFrame
Class2=CConnectDlg
Class3=CDb7App
Class4=CAboutDlg
Class5=CDb7Doc
Class6=CDb7View
Class7=CMainFrame
Class8=MyCug

ResourceCount=10
Resource1=IDR_DB7TYPE
Resource2=IDD_CONNECTDLG
Resource3=IDR_MAINFRAME
Resource4=IDD_ABOUTBOX
Resource5=IDD_PICKSQL
Class9=CSelectSQLDlg
Resource6=IDD_CONNECTDLG (English (U.S.))
Resource7=IDR_DB7TYPE (English (U.S.))
Resource8=IDR_MAINFRAME (English (U.S.))
Resource9=IDD_ABOUTBOX (English (U.S.))
Resource10=IDD_PICKSQL (English (U.S.))

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
LastObject=CChildFrame

[CLS:CConnectDlg]
Type=0
BaseClass=CDialog
HeaderFile=ConnectDlg.h
ImplementationFile=ConnectDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=CConnectDlg

[CLS:CDb7App]
Type=0
BaseClass=CWinApp
HeaderFile=db7.h
ImplementationFile=db7.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=db7.cpp
ImplementationFile=db7.cpp

[CLS:CDb7Doc]
Type=0
BaseClass=CDocument
HeaderFile=db7Doc.h
ImplementationFile=db7Doc.cpp
Filter=N
VirtualFilter=DC
LastObject=CDb7Doc

[CLS:CDb7View]
Type=0
BaseClass=CView
HeaderFile=db7View.h
ImplementationFile=db7View.cpp
Filter=C
VirtualFilter=VWC
LastObject=CDb7View

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

[DLG:IDD_CONNECTDLG]
Type=1
Class=CConnectDlg
ControlCount=10
Control1=IDC_DSNCOMBO,combobox,1344340226
Control2=IDC_SQLEDIT,edit,1350635716
Control3=IDOK,button,1342242817
Control4=IDC_BROWSEBUTTON,button,1342242816
Control5=IDC_SQLDOTBUTTON,button,1342242816
Control6=IDC_RADIOSNAPSHOT,button,1342177289
Control7=IDC_RADIODYNASET,button,1342177289
Control8=IDCANCEL,button,1342242816
Control9=IDC_STATIC,static,1342308354
Control10=IDC_STATIC,static,1342308354

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_SAVE
Command3=ID_EDIT_CUT
Command4=ID_EDIT_COPY
Command5=ID_EDIT_PASTE
Command6=ID_APP_ABOUT
CommandCount=6

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_MRU_FILE1
Command3=ID_APP_EXIT
Command4=ID_VIEW_TOOLBAR
Command5=ID_VIEW_STATUS_BAR
Command6=ID_APP_ABOUT
CommandCount=6

[MNU:IDR_DB7TYPE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_CLOSE
Command3=ID_FILE_PRINT
Command4=ID_FILE_PRINT_PREVIEW
Command5=ID_FILE_PRINT_SETUP
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_VIEW_TOOLBAR
Command13=ID_VIEW_STATUS_BAR
Command14=ID_WINDOW_NEW
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

[DLG:IDD_PICKSQL]
Type=1
Class=CSelectSQLDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SQLLIST,listbox,1353777411

[CLS:CSelectSQLDlg]
Type=0
HeaderFile=SelectSQLDlg.h
ImplementationFile=SelectSQLDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_SQLLIST

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_SAVE
Command3=ID_EDIT_CUT
Command4=ID_EDIT_COPY
Command5=ID_EDIT_PASTE
Command6=ID_APP_ABOUT
CommandCount=6

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_MRU_FILE1
Command3=ID_APP_EXIT
Command4=ID_VIEW_TOOLBAR
Command5=ID_VIEW_STATUS_BAR
Command6=ID_APP_ABOUT
CommandCount=6

[MNU:IDR_DB7TYPE (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_CLOSE
Command3=ID_FILE_PRINT
Command4=ID_FILE_PRINT_PREVIEW
Command5=ID_FILE_PRINT_SETUP
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_VIEW_TOOLBAR
Command13=ID_VIEW_STATUS_BAR
Command14=ID_WINDOW_NEW
Command15=ID_WINDOW_CASCADE
Command16=ID_WINDOW_TILE_HORZ
Command17=ID_WINDOW_ARRANGE
Command18=ID_APP_ABOUT
CommandCount=18

[ACL:IDR_MAINFRAME (English (U.S.))]
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

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CONNECTDLG (English (U.S.))]
Type=1
Class=?
ControlCount=10
Control1=IDC_DSNCOMBO,combobox,1344340226
Control2=IDC_SQLEDIT,edit,1350635716
Control3=IDOK,button,1342242817
Control4=IDC_BROWSEBUTTON,button,1342242816
Control5=IDC_SQLDOTBUTTON,button,1342242816
Control6=IDC_RADIOSNAPSHOT,button,1342177289
Control7=IDC_RADIODYNASET,button,1342177289
Control8=IDCANCEL,button,1342242816
Control9=IDC_STATIC,static,1342308354
Control10=IDC_STATIC,static,1342308354

[DLG:IDD_PICKSQL (English (U.S.))]
Type=1
Class=?
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SQLLIST,listbox,1353777411

