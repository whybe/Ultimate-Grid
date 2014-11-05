// Multiselect ExampleView.cpp : implementation of the CMultiselectExampleView class
//

#include "stdafx.h"
#include "Multiselect Example.h"

#include "Multiselect ExampleDoc.h"
#include "Multiselect ExampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultiselectExampleView

IMPLEMENT_DYNCREATE(CMultiselectExampleView, CView)

BEGIN_MESSAGE_MAP(CMultiselectExampleView, CView)
	//{{AFX_MSG_MAP(CMultiselectExampleView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_RND_SELECTION, OnRndSelection)
	ON_COMMAND(ID_CLEAR, OnClear)
	ON_COMMAND(ID_ROW_CELL, OnRowCell)
	ON_UPDATE_COMMAND_UI(ID_ROW_CELL, OnUpdateRowCell)
	ON_COMMAND(ID_CELL, OnCell)
	ON_UPDATE_COMMAND_UI(ID_CELL, OnUpdateCell)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_EX_FOCUS, OnExFocus)
	ON_UPDATE_COMMAND_UI(ID_EX_FOCUS, OnUpdateExFocus)
	ON_COMMAND(ID_ST_FOCUS, OnStFocus)
	ON_UPDATE_COMMAND_UI(ID_ST_FOCUS, OnUpdateStFocus)
	ON_COMMAND(ID_RND_CELL, OnRndCell)
	ON_COMMAND(ID_FILL, OnFill)
//	ON_COMMAND(ID_LIST_BLOCKS, OnListBlocks)
//	ON_COMMAND(ID_LIST_CELLS, OnListCells)
	ON_COMMAND(ID_THEMES_NONE, OnThemesNone)
	ON_UPDATE_COMMAND_UI(ID_THEMES_NONE, OnUpdateThemesNone)
	ON_COMMAND(ID_THEMES_STYLE1, OnThemesStyle1)
	ON_UPDATE_COMMAND_UI(ID_THEMES_STYLE1, OnUpdateThemesStyle1)
	ON_COMMAND(ID_THEMES_STYLE2, OnThemesStyle2)
	ON_UPDATE_COMMAND_UI(ID_THEMES_STYLE2, OnUpdateThemesStyle2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiselectExampleView construction/destruction

CMultiselectExampleView::CMultiselectExampleView()
{
	// TODO: add construction code here
	m_rowSelection = TRUE;
}

CMultiselectExampleView::~CMultiselectExampleView()
{
}

BOOL CMultiselectExampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMultiselectExampleView drawing

void CMultiselectExampleView::OnDraw(CDC* pDC)
{
	CMultiselectExampleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMultiselectExampleView diagnostics

#ifdef _DEBUG
void CMultiselectExampleView::AssertValid() const
{
	CView::AssertValid();
}

void CMultiselectExampleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMultiselectExampleDoc* CMultiselectExampleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMultiselectExampleDoc)));
	return (CMultiselectExampleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMultiselectExampleView message handlers

int CMultiselectExampleView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect (0,0,0,0);
	m_grid.CreateGrid(WS_CHILD|WS_VISIBLE,rect,this,1234);

	m_grid.SelectRange ( 0, 0, 0, 0 );
	return 0;
}

void CMultiselectExampleView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	CRect rect (0,0,0,0);
	GetClientRect(&rect) ;
	m_grid.MoveWindow(&rect);	
	
}

////////////////////////////////////////////////////////////
//	Returns pointer to current grid object
MyCug* CMultiselectExampleView::GetGrid()
{
	return &m_grid;
}

////////////////////////////////////////////////////////////
//	Make a random selection of cells in the grid
void CMultiselectExampleView::OnRndSelection() 
{
	int stCol, edCol;
	long stRow, edRow;

	stCol = rand()%m_grid.GetNumberCols ();
	stRow = rand()%m_grid.GetNumberRows ();

	edCol = rand()%m_grid.GetNumberCols ();
	edRow = rand()%m_grid.GetNumberRows ();

	m_grid.SelectRange ( stCol, stRow, edCol, edRow );
}

////////////////////////////////////////////////////////////
//	Select random cell in the grid, clear all selections
void CMultiselectExampleView::OnRndCell() 
{
	int col = rand()%m_grid.GetNumberCols (),
		row = rand()%m_grid.GetNumberRows ();
	
	m_grid.GotoCell( col, row );
}

////////////////////////////////////////////////////////////
//	Clear all selections in the grid
void CMultiselectExampleView::OnClear() 
{
	m_grid.ClearSelections ();
	m_grid.RedrawAll ();

	// Select currect cell
	m_grid.Select ( m_grid.GetCurrentCol(), m_grid.GetCurrentRow() );
}

////////////////////////////////////////////////////////////
//	Change current cell mode to row heightlight mode
void CMultiselectExampleView::OnRowCell() 
{
	if ( !m_rowSelection )
		m_rowSelection = TRUE;
	else 
		m_rowSelection = FALSE;

	m_grid.SetHighlightRow ( !m_rowSelection );
	// clear all current selections
	OnClear ();
}

////////////////////////////////////////////////////////////
//	Change current cell mode to cell heightlight mode
void CMultiselectExampleView::OnCell() 
{
	if ( !m_rowSelection )
		m_rowSelection = TRUE;
	else 
		m_rowSelection = FALSE;

	m_grid.SetHighlightRow ( !m_rowSelection );
	// clear all current selections
	OnClear ();
}

////////////////////////////////////////////////////////////
//	
void CMultiselectExampleView::OnUpdateRowCell(CCmdUI* pCmdUI) 
{
	int state = TRUE;

	if ( !m_rowSelection )
	{
		state = FALSE;
	}

	pCmdUI->Enable ( state );

	if ( state != m_rowSelection )
		OnClear();
}

////////////////////////////////////////////////////////////
//	
void CMultiselectExampleView::OnUpdateCell(CCmdUI* pCmdUI) 
{
	int state = TRUE;

	if ( !m_rowSelection )
	{
		state = FALSE;
	}

	pCmdUI->Enable ( !state );

	if ( state != m_rowSelection )
		OnClear();
}

////////////////////////////////////////////////////////////
//	
BOOL CMultiselectExampleView::OnEraseBkgnd(CDC* pDC) 
{
	// to limitate the flicker of the grid
	return FALSE;
}

void CMultiselectExampleView::OnExFocus() 
{
	m_grid.m_bDrawExcelFocus = TRUE;
	m_grid.RedrawAll();
}

void CMultiselectExampleView::OnUpdateExFocus(CCmdUI* pCmdUI) 
{
	int state = TRUE;

	if ( m_grid.m_bDrawExcelFocus )
	{
		state = FALSE;
	}

	pCmdUI->Enable( state );
}

void CMultiselectExampleView::OnStFocus() 
{
	m_grid.m_bDrawExcelFocus = FALSE;	
	m_grid.RedrawAll();
}

void CMultiselectExampleView::OnUpdateStFocus(CCmdUI* pCmdUI) 
{
	int state = TRUE;

	if ( m_grid.m_bDrawExcelFocus )
	{
		state = FALSE;
	}

	pCmdUI->Enable( !state );
}

void CMultiselectExampleView::OnFill() 
{
	int col,
		row;
	CString tempStr;

	m_grid.EnableUpdate( FALSE );
	for( col = 0; col < m_grid.GetNumberCols(); col ++ )
	{
		for( row = 0; row < m_grid.GetNumberRows(); row ++ )
		{
			tempStr.Format( "%d", rand()%99 );
			m_grid.QuickSetText( col, row, tempStr );
		}
	}
	m_grid.EnableUpdate( TRUE );
	m_grid.RedrawAll();
}


void CMultiselectExampleView::OnThemesNone()
{
	UGXPThemes::UseThemes(false);
	Invalidate(FALSE);
}

void CMultiselectExampleView::OnUpdateThemesNone(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(!UGXPThemes::UseThemes());	
}

void CMultiselectExampleView::OnThemesStyle1()
{
	UGXPThemes::UseThemes(true);
	UGXPThemes::SetGridStyle(Style1);
	Invalidate(FALSE);
}

void CMultiselectExampleView::OnUpdateThemesStyle1(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes() && UGXPThemes::GetGridStyle() == Style1);	
}

void CMultiselectExampleView::OnThemesStyle2()
{
	UGXPThemes::UseThemes(true);
	UGXPThemes::SetGridStyle(Style2);
	Invalidate(FALSE);
}

void CMultiselectExampleView::OnUpdateThemesStyle2(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes() && UGXPThemes::GetGridStyle() == Style2);	
}
