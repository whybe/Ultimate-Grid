; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCelltypesView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "cell types.h"
LastPage=0

ClassCount=20
Class1=CCelltypesApp
Class2=CAboutDlg
Class3=CCelltypesDoc
Class4=CCelltypesView
Class5=CCellTypeDemoGrid
Class6=CChildFrame
Class7=CMainFrame
Class8=CUGCnrBtn
Class9=CUGCtrl
Class10=CUGEdit
Class11=CUGEditBase
Class12=CUGGrid
Class13=CUGHint
Class14=CUGHScroll
Class15=CUGLstBox
Class16=CUGMaskedEdit
Class17=CUGSideHdg
Class18=CUGTab
Class19=CUGTopHdg
Class20=CUGVScroll

ResourceCount=3
Resource1=IDR_CELLTYTYPE (English (U.S.))
Resource2=IDR_MAINFRAME (English (U.S.))
Resource3=IDD_ABOUTBOX (English (U.S.))

[CLS:CCelltypesApp]
Type=0
BaseClass=CWinApp
HeaderFile=Cell types.h
ImplementationFile=Cell types.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=Cell types.cpp
ImplementationFile=Cell types.cpp
LastObject=CAboutDlg

[CLS:CCelltypesDoc]
Type=0
BaseClass=CDocument
HeaderFile=Cell typesDoc.h
ImplementationFile=Cell typesDoc.cpp

[CLS:CCelltypesView]
Type=0
BaseClass=CView
HeaderFile=Cell typesView.h
ImplementationFile=Cell typesView.cpp
Filter=C
VirtualFilter=VWC

[CLS:CCellTypeDemoGrid]
Type=0
BaseClass=CUGCtrl
HeaderFile=CellTypeDemoGrid.h
ImplementationFile=CellTypeDemoGrid.cpp

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CUGCnrBtn]
Type=0
BaseClass=CWnd
HeaderFile=\Contract Work\Code Project\Ultimate Grid\Working\Include\UGCnrBtn.h
ImplementationFile=\Contract Work\Code Project\Ultimate Grid\Working\Source\UGCnrBtn.cpp

[CLS:CUGCtrl]
Type=0
BaseClass=CWnd
HeaderFile=\Contract Work\Code Project\Ultimate Grid\Working\Include\UGCtrl.h
ImplementationFile=\Contract Work\Code Project\Ultimate Grid\Working\Source\UGCtrl.cpp

[CLS:CUGEdit]
Type=0
BaseClass=CEdit
HeaderFile=\Contract Work\Code Project\Ultimate Grid\Working\Include\UGEdit.h
ImplementationFile=\Contract Work\Code Project\Ultimate Grid\Working\Source\UGEdit.cpp

[CLS:CUGEditBase]
Type=0
BaseClass=CEdit
HeaderFile=\Contract Work\Code Project\Ultimate Grid\Working\Include\UGEditBase.h
ImplementationFile=\Contract Work\Code Project\Ultimate Grid\Working\Source\UGEditBase.cpp

[CLS:CUGGrid]
Type=0
BaseClass=CWnd
HeaderFile=\Contract Work\Code Project\Ultimate Grid\Working\Include\UGGrid.h
ImplementationFile=\Contract Work\Code Project\Ultimate Grid\Working\Source\UGGrid.cpp

[CLS:CUGHint]
Type=0
BaseClass=CWnd
HeaderFile=\Contract Work\Code Project\Ultimate Grid\Working\Include\UGHint.h
ImplementationFile=\Contract Work\Code Project\Ultimate Grid\Working\Source\UGHint.cpp

[CLS:CUGHScroll]
Type=0
BaseClass=CScrollBar
HeaderFile=\Contract Work\Code Project\Ultimate Grid\Working\Include\ughscrol.h
ImplementationFile=\Contract Work\Code Project\Ultimate Grid\Working\Source\ughscrol.cpp

[CLS:CUGLstBox]
Type=0
BaseClass=CListBox
HeaderFile=\Contract Work\Code Project\Ultimate Grid\Working\Include\uglstbox.h
ImplementationFile=\Contract Work\Code Project\Ultimate Grid\Working\Source\ugLstBox.cpp

[CLS:CUGMaskedEdit]
Type=0
BaseClass=CEdit
HeaderFile=\Contract Work\Code Project\Ultimate Grid\Working\Include\UGMEdit.h
ImplementationFile=\Contract Work\Code Project\Ultimate Grid\Working\Source\UGMEdit.cpp

[CLS:CUGSideHdg]
Type=0
BaseClass=CWnd
HeaderFile=\Contract Work\Code Project\Ultimate Grid\Working\Include\ugsidehd.h
ImplementationFile=\Contract Work\Code Project\Ultimate Grid\Working\Source\ugsidehd.cpp

[CLS:CUGTab]
Type=0
BaseClass=CWnd
HeaderFile=\Contract Work\Code Project\Ultimate Grid\Working\Include\ugtab.h
ImplementationFile=\Contract Work\Code Project\Ultimate Grid\Working\Source\ugtab.cpp

[CLS:CUGTopHdg]
Type=0
BaseClass=CWnd
HeaderFile=\Contract Work\Code Project\Ultimate Grid\Working\Include\UGTopHdg.h
ImplementationFile=\Contract Work\Code Project\Ultimate Grid\Working\Source\UGTopHdg.cpp

[CLS:CUGVScroll]
Type=0
BaseClass=CScrollBar
HeaderFile=\Contract Work\Code Project\Ultimate Grid\Working\Include\ugvscrol.h
ImplementationFile=\Contract Work\Code Project\Ultimate Grid\Working\Source\ugvscrol.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

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

[MNU:IDR_MAINFRAME (English (U.S.))]
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

[MNU:IDR_CELLTYTYPE (English (U.S.))]
Type=1
Class=CCelltypesView
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
Command17=ID_USEXPTHEMES_STYLE1
Command18=ID_USEXPTHEMES_STYLE2
Command19=ID_USEXPTHEMES_NONE
Command20=ID_WINDOW_NEW
Command21=ID_WINDOW_CASCADE
Command22=ID_WINDOW_TILE_HORZ
Command23=ID_WINDOW_ARRANGE
Command24=ID_APP_ABOUT
CommandCount=24

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

