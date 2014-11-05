// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Multiselect Example.h"

#include "MainFrm.h"

// include headers for the splitter view classed
#include "Multiselect ExampleDoc.h"
#include "Multiselect ExampleView.h"
#include "SelectionList.h"

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
	ON_COMMAND(ID_LIST_BLOCKS, OnListBlocks)
	ON_COMMAND(ID_LIST_CELLS, OnListCells)
	ON_COMMAND(ID_VIEW_USEXPTHEMES, OnViewUsexpthemes)
	ON_UPDATE_COMMAND_UI(ID_VIEW_USEXPTHEMES, OnUpdateViewUsexpthemes)
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

CMainFrame::CMainFrame()
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
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

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

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.cx = 600;
	cs.cy = 500;

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


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL retcd = m_splitterWnd.CreateStatic ( this, 2, 1 );

	retcd |= m_splitterWnd.CreateView ( 0, 0, RUNTIME_CLASS( CMultiselectExampleView ), CSize(100,200), pContext );
	retcd |= m_splitterWnd.CreateView ( 1, 0, RUNTIME_CLASS( CSelectionList ), CSize(100,300), pContext );

	return retcd;
	return CFrameWnd::OnCreateClient(lpcs, pContext);
}

void CMainFrame::OnListAll() 
{
	TRACE ( "CMainFrame::OnListAll\n" );
}

void CMainFrame::OnListBlocks() 
{
	TRACE ( "CMainFrame::OnListBlocks\n" );
	int stCol, edCol, blockCount = 0;
	long stRow, edRow;
	CString tempStr;

	SetCursor(LoadCursor(NULL, IDC_WAIT));
	// Get handle to the list control
	CWnd *temp = m_splitterWnd.GetPane ( 1, 0 );
	CListCtrl &tempList = ((CSelectionList*)temp)->GetListCtrl ();
	// Set up the list conrtol for our use
	// delete all columns, and data
	while( tempList.DeleteColumn( 0 ) );
	tempList.DeleteAllItems ();
	// Add columns required for this view
	tempList.InsertColumn ( 0, "Block #" );
	tempList.SetColumnWidth ( 0, 50 );
	tempList.InsertColumn ( 1, "Selected Range" );
	tempList.SetColumnWidth ( 1, 150 );
	
	// get handle to the grid
	MyCug *grid;
	temp = m_splitterWnd.GetPane ( 0, 0 );
	grid = ((CMultiselectExampleView*)temp)->GetGrid ();

	grid->m_GI->m_multiSelect->EnumFirstBlock ( &stCol, &stRow, &edCol, &edRow );
	do
	{
		tempStr.Format ( "%d", blockCount );
		tempList.InsertItem ( blockCount, tempStr );
		tempStr.Format ( "%d, %d - %d, %d", stCol, stRow, edCol, edRow );
		tempList.SetItemText ( blockCount, 1, tempStr );
		blockCount ++;
	} while ( !grid->m_GI->m_multiSelect->EnumNextBlock( &stCol, &stRow, &edCol, &edRow ));
	SetCursor(LoadCursor(NULL, IDC_ARROW));
}

void CMainFrame::OnListCells() 
{
	TRACE ( "CMainFrame::OnListCells\n" );
	int stCol, itemCount = 0;
	long stRow;
	CString tempStr;

	SetCursor(LoadCursor(NULL, IDC_WAIT));
	// Get handle to the list control
	CWnd *temp = m_splitterWnd.GetPane ( 1, 0 );
	CListCtrl &tempList = ((CSelectionList*)temp)->GetListCtrl ();
	// Set up the list conrtol for our use
	// delete all columns, and data
	while( tempList.DeleteColumn( 0 ) );
	tempList.DeleteAllItems ();
	// Add columns required for this view
	tempList.InsertColumn ( 0, "Item #" );
	tempList.SetColumnWidth ( 0, 50 );
	tempList.InsertColumn ( 1, "Selected Cell" );
	tempList.SetColumnWidth ( 1, 150 );
	
	// get handle to the grid
	MyCug *grid;
	temp = m_splitterWnd.GetPane ( 0, 0 );
	grid = ((CMultiselectExampleView*)temp)->GetGrid ();

	grid->m_GI->m_multiSelect->EnumFirstSelected ( &stCol, &stRow );
	do
	{
		tempStr.Format ( "%d", itemCount );
		tempList.InsertItem ( itemCount, tempStr );
		tempStr.Format ( "%d, %d", stCol, stRow );
		tempList.SetItemText ( itemCount, 1, tempStr );
		itemCount ++;
	} while ( !	grid->m_GI->m_multiSelect->EnumNextSelected ( &stCol, &stRow ));
	SetCursor(LoadCursor(NULL, IDC_ARROW));
}

void CMainFrame::OnViewUsexpthemes() 
{
	UGXPThemes::UseThemes(!UGXPThemes::UseThemes());
	Invalidate();
}

void CMainFrame::OnUpdateViewUsexpthemes(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes());
}
