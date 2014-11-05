// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "OutlookStyle.h"
#include "OutlookStyleView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame() : COXMenuBarFrame<CFrameWnd,COXSizeDockBar>(CBRS_ALIGN_ANY,
	RUNTIME_CLASS(COXSizableMiniDockFrameWnd))
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), AFX_IDW_TOOLBAR) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))

	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	// Create and initialize the second toolbar
	if (!m_wndToolBar2.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), 3344554) ||
		!m_wndToolBar2.LoadToolBar(IDR_TOOLBARFLAGS))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	m_toolbar2Images.Create(16, 15, ILC_COLOR24 | ILC_MASK, 8, 0);
	CBitmap bmpImage;
	bmpImage.LoadBitmap(IDB_TOOLBARFLAGS);
	m_toolbar2Images.Add(&bmpImage, RGB(255, 0, 255));
	bmpImage.DeleteObject();
	m_wndToolBar2.GetToolBarCtrl().SetImageList(&m_toolbar2Images);

	// Create and initialize the second toolbar
	if (!m_wndToolBar3.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), 3344554) ||
		!m_wndToolBar3.LoadToolBar(IDR_TOOLBARDEFAULTFLAGS))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	m_toolbar3Images.Create(16, 15, ILC_COLOR24 | ILC_MASK, 12, 0);
	bmpImage.LoadBitmap(IDB_TOOLBARDEFAULTFLAGS);
	m_toolbar3Images.Add(&bmpImage, RGB(255, 0, 255));
	bmpImage.DeleteObject();
	m_wndToolBar3.GetToolBarCtrl().SetImageList(&m_toolbar3Images);


	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	m_BMO.AttachFrameWnd(this);
	m_BMO.AutoSetMenuImage();

	// This toolbar only exists to create an image list that I can easily pass in to my context menu.
	m_wndToolBar2.ShowWindow(SW_HIDE);
	m_wndToolBar3.ShowWindow(SW_HIDE);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::OnEraseBkgnd(CDC* pDC) 
{
//	return FALSE;
	
	return CFrameWnd::OnEraseBkgnd(pDC);
}
