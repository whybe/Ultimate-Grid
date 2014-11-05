; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGridDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Use UG Lib.h"
LastPage=0

ClassCount=7
Class1=CUseUGLibApp
Class2=CUseUGLibDoc
Class3=CUseUGLibView
Class4=CMainFrame

ResourceCount=4
Resource1=IDR_USEUGLTYPE
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class5=CChildFrame
Class6=CAboutDlg
Class7=CGridDlg
Resource4=IDD_GRID_DLG

[CLS:CUseUGLibApp]
Type=0
HeaderFile=Use UG Lib.h
ImplementationFile=Use UG Lib.cpp
Filter=N

[CLS:CUseUGLibDoc]
Type=0
HeaderFile=Use UG LibDoc.h
ImplementationFile=Use UG LibDoc.cpp
Filter=N

[CLS:CUseUGLibView]
Type=0
HeaderFile=Use UG LibView.h
ImplementationFile=Use UG LibView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CMDIFrameWnd
VirtualFilter=fWC


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
BaseClass=CMDIChildWnd
VirtualFilter=mfWC


[CLS:CAboutDlg]
Type=0
HeaderFile=Use UG Lib.cpp
ImplementationFile=Use UG Lib.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_GRID_DLG
CommandCount=2

[MNU:IDR_USEUGLTYPE]
Type=1
Class=CUseUGLibView
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
Class=CMainFrame
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

[DLG:IDD_GRID_DLG]
Type=1
Class=CGridDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_GRID,static,1342312961

[CLS:CGridDlg]
Type=0
HeaderFile=GridDlg.h
ImplementationFile=GridDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CGridDlg
VirtualFilter=dWC

