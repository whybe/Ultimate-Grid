// ADO SampleView.cpp : implementation of the CADOSampleView class
//

#include "stdafx.h"
#include "ADO Sample.h"

#include "ADO SampleDoc.h"
#include "ADO SampleView.h"
#include "SqlEditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CADOSampleView

IMPLEMENT_DYNCREATE(CADOSampleView, CView)

BEGIN_MESSAGE_MAP(CADOSampleView, CView)
	//{{AFX_MSG_MAP(CADOSampleView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_REFRESH_DATA, OnRefreshData)
	ON_COMMAND(ID_SHOW_SQL, OnShowSql)
	ON_COMMAND(ID_APPEND_ROW, OnAppendRow)
	ON_COMMAND(ID_DELETE_RECORD, OnDeleteRecord)
	ON_COMMAND(ID_ADD_TABLE, OnAddTable)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CADOSampleView construction/destruction

CADOSampleView::CADOSampleView()
{
	// TODO: add construction code here
	m_pDSList = NULL;
}

CADOSampleView::~CADOSampleView()
{
	// clear the DS link list
	_tagDSList *pTempItem = m_pDSList,
				*pDeleteItem = NULL;

	while ( pTempItem != NULL )
	{
		pDeleteItem = pTempItem;
		pTempItem = pTempItem->next;
		delete pDeleteItem->m_dsADO;
		delete pDeleteItem;
	}
}

BOOL CADOSampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CADOSampleView drawing

void CADOSampleView::OnDraw(CDC* pDC)
{
	CADOSampleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CADOSampleView printing

BOOL CADOSampleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CADOSampleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CADOSampleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CADOSampleView diagnostics

#ifdef _DEBUG
void CADOSampleView::AssertValid() const
{
	CView::AssertValid();
}

void CADOSampleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CADOSampleDoc* CADOSampleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CADOSampleDoc)));
	return (CADOSampleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CADOSampleView message handlers

int CADOSampleView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_grid.CreateGrid( WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 23422 );
	
	return 0;
}

void CADOSampleView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_grid.MoveWindow( 0, 0, cx, cy );
}

void CADOSampleView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	m_grid.SetFocus();
}

BOOL CADOSampleView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
	// return CView::OnEraseBkgnd(pDC);
}

/////////////////////////////////////////////////////////////////////////////
//	OnInitialUpdate
//		The OnInitialUpdate function is used to bind the grid to ADO datasource
//		using the SQL and connect information specified by the user.
void CADOSampleView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	
	// bind the datasource to data, provide it with query and connection information
	m_pDSList = new _tagDSList;
	m_pDSList->m_dsADO = new CADOImpDatasource;
	m_pDSList->m_dsADO->OpenSQL( GetDocument()->GetSQLString(), GetDocument()->GetConnectionString());
	// add the open datasource
	m_grid.AddDataSource( m_pDSList->m_dsADO );
	// set added datasource to be default
	m_grid.SetDefDataSource( m_pDSList->m_dsADO->GetID());
	// complete the datasource binding operation, let grid adjust
	// itself to reflect information found in the datasource
	m_grid.SetGridUsingDataSource( m_pDSList->m_dsADO->GetID());	
}

/////////////////////////////////////////////////////////////////////////////
//	OnRefreshData
//		The OnRefreshData function will force the data in current sheet to
//		be reloaded from the database.
void CADOSampleView::OnRefreshData() 
{
	int nSheetNumber = m_grid.GetSheetNumber();
	_tagDSList *pTempItem = m_pDSList;
	
	for( int nIndex = 0; nIndex < nSheetNumber && pTempItem != NULL; nIndex ++ )
		pTempItem = pTempItem->next;

	if ( pTempItem == NULL )
		return;

	pTempItem->m_dsADO->RefreshData();
	m_grid.RedrawAll();
}

/////////////////////////////////////////////////////////////////////////////
//	OnShowSql
//		The OnShowSql function provides user with ability to view and modify
//		current SQL query.
void CADOSampleView::OnShowSql() 
{
	CSQLEditDlg sqlDlg;
	int nSheetNumber = m_grid.GetSheetNumber();

	// get a pointer to the current datasource
	_tagDSList *pTempItem = m_pDSList;
	
	for( int nIndex = 0; nIndex < nSheetNumber && pTempItem != NULL; nIndex ++ )
		pTempItem = pTempItem->next;

	if ( pTempItem == NULL )
		return;

	sqlDlg.SetSQLStr( pTempItem->m_dsADO->GetSQL());

	if ( sqlDlg.DoModal() == IDOK )
	{
		GetDocument()->SetSQLString( sqlDlg.GetSQLStr(), nSheetNumber );
		// Reset the grid
		m_grid.SetNumberRows( 0 );
		m_grid.SetNumberCols( 0 );
		// reload the recordset
		pTempItem->m_dsADO->Close();
		pTempItem->m_dsADO->OpenSQL( GetDocument()->GetSQLString( nSheetNumber ), GetDocument()->GetConnectionString());
		m_grid.SetGridUsingDataSource( pTempItem->m_dsADO->GetID());	
		m_grid.AdjustComponentSizes();
	}
}

/////////////////////////////////////////////////////////////////////////////
//	OnAppendRow
void CADOSampleView::OnAppendRow() 
{
	m_grid.AppendRow();
/*	
	int row = m_grid.GetNumberRows() - 1;	
	m_grid.QuickSetText(0, row, _T("LastName"));
	m_grid.QuickSetText(0, row, _T("LastName"));
	m_grid.QuickSetText(1, row, _T("FirstName"));
	m_grid.QuickSetText(2, row, _T("100100"));
	m_grid.RedrawRow(row);
*/
}

/////////////////////////////////////////////////////////////////////////////
//	OnDeleteRecord
void CADOSampleView::OnDeleteRecord() 
{
	m_grid.DeleteRow( m_grid.GetCurrentRow());
}

/////////////////////////////////////////////////////////////////////////////
//	OnAddTable
//		The OnAddTable function demonstrates that the Ultimate Grid can display
//		number of sheets, where each sheet is bound to a different datasource.
//		In this case we provide the user to bind additional sheets to datasources
//		that use same database.  Each sheet is completely independent of each other.
void CADOSampleView::OnAddTable() 
{
	// Prompt the user to specify the SQL query to show in the new sheet
	CSQLEditDlg sqlDlg;
	sqlDlg.SetSQLStr( _T("SELECT * FROM Customers;"));

	if ( sqlDlg.DoModal() == IDOK )
	{
		if ( sqlDlg.GetSQLStr() == _T(""))
			return;

		int nNumberSheets = m_grid.GetNumberSheets();
		// Get the new SQL query and make sure that empty string is not used
		GetDocument()->SetSQLString( sqlDlg.GetSQLStr(), nNumberSheets );
		nNumberSheets ++;
		// Add and initialize new sheet
		m_grid.SetNumberSheets( nNumberSheets );
		// Add and initialize new tab
		CString tempStr;
		tempStr.Format( _T("Sheet %d"), nNumberSheets );
		m_grid.AddTab( tempStr, nNumberSheets );
		// Adjust the view to display the new sheet
		m_grid.SetCurrentTab( nNumberSheets );
		m_grid.SetSheetNumber( nNumberSheets - 1 );
		m_grid.SetPaintMode( TRUE );
		// Bind the new sheet to the datasource
		_tagDSList *pTempItem = m_pDSList;

		if ( pTempItem == NULL )
			return;

		while ( pTempItem->next != NULL )
			pTempItem = pTempItem->next;

		pTempItem->next = new _tagDSList;
		pTempItem = pTempItem->next;
		pTempItem->m_dsADO = new CADOImpDatasource;

		pTempItem->m_dsADO->OpenSQL( sqlDlg.GetSQLStr(), GetDocument()->GetConnectionString());
		// add the open datasource
		m_grid.AddDataSource( pTempItem->m_dsADO );
		// set added datasource to be default
		m_grid.SetDefDataSource( pTempItem->m_dsADO->GetID());
		// complete the datasource binding operation, let grid adjust
		// itself to reflect information found in the datasource
		m_grid.SetGridUsingDataSource( pTempItem->m_dsADO->GetID());
	}
}
