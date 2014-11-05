// db7View.cpp : implementation of the CDb7View class
//

#include "stdafx.h"

#include "db7.h"
#include "ConnectDlg.h"

#include "db7Doc.h"
#include "db7View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDb7View

IMPLEMENT_DYNCREATE(CDb7View, CView)

BEGIN_MESSAGE_MAP(CDb7View, CView)
	//{{AFX_MSG_MAP(CDb7View)
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
// CDb7View construction/destruction

CDb7View::CDb7View()
{
	// TODO: add construction code here
}

CDb7View::~CDb7View()
{
}

BOOL CDb7View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDb7View drawing

void CDb7View::OnDraw(CDC* pDC)
{
	CDb7Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDb7View printing

BOOL CDb7View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDb7View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDb7View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDb7View diagnostics

#ifdef _DEBUG
void CDb7View::AssertValid() const
{
	CView::AssertValid();
}

void CDb7View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDb7Doc* CDb7View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDb7Doc)));
	return (CDb7Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDb7View message handlers

int CDb7View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	
	CConnectDlg *cnnDlg = &((CDb7App*)AfxGetApp())->m_connDlg;

	// TODO: Add your specialized creation code here
	cnnDlg->m_pOdbc = &m_odbc;
	if(IDCANCEL == cnnDlg->DoModal())
		return -1;

	CWaitCursor myWaitCursor;

	if(UG_SUCCESS != m_odbc.Open(cnnDlg->m_strDSN, cnnDlg->m_strSQL, 0, cnnDlg->m_nOpenType, 0, NULL, NULL))
		return -1;
	
	m_ctrl.CreateGrid(WS_VISIBLE|WS_CHILD,CRect(0,0,0,0),this,123);

	return 0;
}

void CDb7View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_ctrl.MoveWindow( 0, 0, cx, cy );
}


BOOL CDb7View::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
	return CView::OnEraseBkgnd(pDC);
}

void CDb7View::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	CConnectDlg *cnnDlg = &((CDb7App*)AfxGetApp())->m_connDlg;

	GetDocument()->SetTitle(cnnDlg->m_strSQL);

	int index = m_ctrl.AddDataSource(&m_odbc);
	m_ctrl.SetDefDataSource(index);
	m_ctrl.SetGridUsingDataSource(index);

	m_ctrl.BestFit(0,m_ctrl.GetNumberCols()-1,0,UG_BESTFIT_TOPHEADINGS);
}
