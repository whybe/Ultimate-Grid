; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "appointmentbook.h"
LastPage=0

ClassCount=7
Class1=CAppInfo
Class2=CAppointmentBookApp
Class3=CAboutDlg
Class4=CAppointmentBookDoc
Class5=CAppointmentBookView
Class6=CMainFrame
Class7=MyCug

ResourceCount=3
Resource1=IDR_MAINFRAME (English (U.S.))
Resource2=IDD_ABOUTBOX (English (U.S.))
Resource3=IDD_APP_DLG (English (U.S.))

[CLS:CAppInfo]
Type=0
BaseClass=CDialog
HeaderFile=AppInfo.h
ImplementationFile=AppInfo.cpp

[CLS:CAppointmentBookApp]
Type=0
BaseClass=CWinApp
HeaderFile=AppointmentBook.h
ImplementationFile=AppointmentBook.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=AppointmentBook.cpp
ImplementationFile=AppointmentBook.cpp
LastObject=IDM_XP_THEME

[CLS:CAppointmentBookDoc]
Type=0
BaseClass=CDocument
HeaderFile=AppointmentBookDoc.h
ImplementationFile=AppointmentBookDoc.cpp

[CLS:CAppointmentBookView]
Type=0
BaseClass=CView
HeaderFile=AppointmentBookView.h
ImplementationFile=AppointmentBookView.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC

[CLS:MyCug]
Type=0
BaseClass=CUGCtrl
HeaderFile=Mycug.h
ImplementationFile=Mycug.cpp

[DLG:IDD_APP_DLG]
Type=1
Class=CAppInfo

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[DLG:IDD_APP_DLG (English (U.S.))]
Type=1
Class=?
ControlCount=11
Control1=IDC_START_TIME,combobox,1344339971
Control2=IDC_APP_INFO,edit,1352728580
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,static,1342308866
Control6=IDC_STATIC,static,1342308866
Control7=IDC_HOURS,edit,1350639746
Control8=IDC_HOURS_SPIN,msctls_updown32,1342177590
Control9=IDC_STATIC,static,1342308864
Control10=IDC_MINUTES,combobox,1344340227
Control11=IDC_STATIC,static,1342308864

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=IDM_XP_THEME
Command17=ID_APP_ABOUT
CommandCount=17

[TB:IDR_MAINFRAME (English (U.S.))]
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

