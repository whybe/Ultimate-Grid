; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ex7.h"
LastPage=0

ClassCount=7
Class1=CUGCellPropViewer
Class2=CAboutDlg
Class3=CEx7App
Class4=CEx7Doc
Class5=CEx7View
Class6=CMainFrame
Class7=MyCug

ResourceCount=3
Resource1=IDD_ABOUTBOX (English (U.S.))
Resource2=IDR_MAINFRAME (English (U.S.))
Resource3=IDD_PROP_VIEW (English (U.S.))

[CLS:CUGCellPropViewer]
Type=0
BaseClass=CDialog
HeaderFile=CellView.h
ImplementationFile=CellView.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=Ex7.cpp
ImplementationFile=Ex7.cpp

[CLS:CEx7App]
Type=0
BaseClass=CWinApp
HeaderFile=Ex7.h
ImplementationFile=Ex7.cpp

[CLS:CEx7Doc]
Type=0
BaseClass=CDocument
HeaderFile=Ex7Doc.h
ImplementationFile=Ex7Doc.cpp

[CLS:CEx7View]
Type=0
BaseClass=CView
HeaderFile=Ex7View.h
ImplementationFile=Ex7View.cpp
Filter=C
VirtualFilter=VWC
LastObject=CEx7View

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=ID_VIEW_USEXPTHEMES

[CLS:MyCug]
Type=0
BaseClass=CUGCtrl
HeaderFile=Mycug.h
ImplementationFile=Mycug.cpp

[DLG:IDD_PROP_VIEW]
Type=1
Class=CUGCellPropViewer

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

[DLG:IDD_PROP_VIEW (English (U.S.))]
Type=1
Class=?
ControlCount=19
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308354
Control3=IDC_STATIC,static,1342308354
Control4=IDC_STATIC,static,1342308354
Control5=IDC_STATIC,static,1342308354
Control6=IDC_STATIC,static,1342308354
Control7=IDC_STATIC,static,1342308354
Control8=IDC_STATIC,static,1342308354
Control9=IDC_STATIC,static,1342308354
Control10=IDC_STATIC,static,1342308354
Control11=IDC_TEXT,edit,1350633600
Control12=IDC_VERT_ALIGN,edit,1350633600
Control13=IDC_HORIZ_ALIGN,edit,1350633600
Control14=IDC_BACK_COLOR,edit,1350633600
Control15=IDC_TEXT_COLOR,edit,1350633600
Control16=IDC_HIGH_BACK_COL,edit,1350633600
Control17=IDC_HIGH_TEXT_COLOR,edit,1350633600
Control18=IDC_BITMAP,edit,1350633600
Control19=IDC_FONT,edit,1350633600

