// DAO sortingView.cpp : implementation of the CDAOsortingView class
//

#include "stdafx.h"
#include "DAO sorting.h"

#include "DAO sortingDoc.h"
#include "DAO sortingView.h"
#include "OpenDatabaseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDAOsortingView

IMPLEMENT_DYNCREATE(CDAOsortingView, CView)

BEGIN_MESSAGE_MAP(CDAOsortingView, CView)
	//{{AFX_MSG_MAP(CDAOsortingView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDAOsortingView construction/destruction

CDAOsortingView::CDAOsortingView()
{
	// TODO: add construction code here

}

CDAOsortingView::~CDAOsortingView()
{
}

BOOL CDAOsortingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDAOsortingView drawing

void CDAOsortingView::OnDraw(CDC* pDC)
{
	CDAOsortingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	if ( pDC->IsPrinting())
	{
		m_grid.PrintPage(pDC, m_printPage);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDAOsortingView printing

BOOL CDAOsortingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDAOsortingView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// make sure that all of the rows in the grid are showing
	m_grid.SetNumberRows( m_data.GetNumRowsComplete());

	pInfo->SetMaxPage(m_grid.PrintInit(pDC,pInfo->m_pPD,0,0,m_grid.GetNumberCols()-1,m_grid.GetNumberRows()-1));
}

void CDAOsortingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDAOsortingView diagnostics

#ifdef _DEBUG
void CDAOsortingView::AssertValid() const
{
	CView::AssertValid();
}

void CDAOsortingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDAOsortingDoc* CDAOsortingView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDAOsortingDoc)));
	return (CDAOsortingDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDAOsortingView message handlers

int CDAOsortingView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_grid.CreateGrid( WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 23423 );
	
	// configure DAO datasource before oppenig
	m_data.SetOption( UGDAO_OPT_ALLOWEDITS, 1, 0 );
	m_data.SetOption( UGDAO_OPT_GHOSTROWMODE, 1, 0 );

	// get sql and location of the selected database
	COpenDatabaseDlg openDlg;
	if ( openDlg.DoModal() == IDOK )
	{	
		if ( openDlg.m_openStyle == 0 )
		{	// open datasource with SQL, and looking for records that do not exist
			// therefore returning empty recordset
			m_data.OpenSQL( openDlg.GetFileName(), openDlg.GetSQL());
		}
		else
		{	// open datasource with table name
			m_data.Open( openDlg.GetFileName(), openDlg.m_tableName );
		}
		// add default data source to the grid
		m_dataIndex = m_grid.AddDataSource( &m_data );
		m_grid.SetDefDataSource( m_dataIndex );
		// set grid using new datasource
		m_grid.SetGridUsingDataSource( m_dataIndex );
		// m_grid.SetNumberRows( m_data.GetNumRowsComplete());
		// do best fit
		// m_grid.BestFit( 0, m_data.GetNumCols() -1 , m_grid.GetNumberRows() -1, 0 );
	}
	else
		// action canceled by user
		return 0;

	m_grid.SetMultiSelectMode( TRUE );

	return 0;
}

void CDAOsortingView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	m_grid.MoveWindow( 0, 0, cx, cy );
}

BOOL CDAOsortingView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
	//return CView::OnEraseBkgnd(pDC);
}

void CDAOsortingView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	m_printPage = pInfo->m_nCurPage;

	CView::OnPrint(pDC, pInfo);
}
