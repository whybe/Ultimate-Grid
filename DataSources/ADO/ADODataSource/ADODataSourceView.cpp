// ADODataSourceView.cpp : implementation of the CADODataSourceView class
//

#include "stdafx.h"
#include "ADODataSource.h"

#include "ADODataSourceDoc.h"
#include "ADODataSourceView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CADODataSourceView

IMPLEMENT_DYNCREATE(CADODataSourceView, CView)

BEGIN_MESSAGE_MAP(CADODataSourceView, CView)
	//{{AFX_MSG_MAP(CADODataSourceView)
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
// CADODataSourceView construction/destruction

CADODataSourceView::CADODataSourceView()
{
	// TODO: add construction code here

}

CADODataSourceView::~CADODataSourceView()
{
}

BOOL CADODataSourceView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CADODataSourceView drawing

void CADODataSourceView::OnDraw(CDC* /*pDC*/)
{
	/*CADODataSourceDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);*/
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CADODataSourceView printing

BOOL CADODataSourceView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CADODataSourceView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CADODataSourceView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CADODataSourceView diagnostics

#ifdef _DEBUG
void CADODataSourceView::AssertValid() const
{
	CView::AssertValid();
}

void CADODataSourceView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CADODataSourceDoc* CADODataSourceView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CADODataSourceDoc)));
	return (CADODataSourceDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CADODataSourceView message handlers

int CADODataSourceView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_grid.CreateGrid( WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 2333 );
	
	return 0;
}

void CADODataSourceView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_grid.MoveWindow( 0, 0, cx, cy );
}

BOOL CADODataSourceView::OnEraseBkgnd(CDC* /*pDC*/) 
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
	// return CView::OnEraseBkgnd(pDC);
}
