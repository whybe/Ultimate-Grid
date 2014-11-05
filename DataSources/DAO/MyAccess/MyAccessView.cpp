// MyAccessView.cpp : implementation of the CMyAccessView class
//

#include "stdafx.h"
#include "ugaccess.h"
#include "ugdao.h"
#include "MyAccess.h"
#include "MyAccessDoc.h"
#include "MyAccessView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyAccessView

IMPLEMENT_DYNCREATE(CMyAccessView, CView)

BEGIN_MESSAGE_MAP(CMyAccessView, CView)
	//{{AFX_MSG_MAP(CMyAccessView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyAccessView construction/destruction

CMyAccessView::CMyAccessView()
{
	// TODO: add construction code here

}

CMyAccessView::~CMyAccessView()
{
}

BOOL CMyAccessView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyAccessView drawing

void CMyAccessView::OnDraw(CDC* pDC)
{
	CMyAccessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	CRect rect;	
	if (m_isPrinting){	
		rect=m_drawRect;
		m_ctrl.PrintPage(pDC,m_printPage);	
	}
	else{	
		GetClientRect(&rect);
		CBrush brush(RGB(255,255,255));		
		pDC->FillRect(&rect,&brush);	
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMyAccessView printing

BOOL CMyAccessView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyAccessView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add extra initialization before printing
	pInfo->SetMaxPage(m_ctrl.PrintInit(pDC,pInfo->m_pPD,0,0,m_ctrl.GetNumberCols()-1,m_ctrl.GetNumberRows()-1));
	m_isPrinting = TRUE;
}

void CMyAccessView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
	m_isPrinting = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CMyAccessView diagnostics

#ifdef _DEBUG
void CMyAccessView::AssertValid() const
{
	CView::AssertValid();
}

void CMyAccessView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyAccessDoc* CMyAccessView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyAccessDoc)));
	return (CMyAccessDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyAccessView message handlers

int CMyAccessView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;


//	CUGCell *cells = new CUGCell[20];
	
	// TODO: Add your specialized creation code here
	RECT rect = {0,0,0,0};
	m_ctrl.CreateGrid(WS_VISIBLE|WS_CHILD,rect,this,123);
	
	return 0;
	
}

void CMyAccessView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	RECT rect;
	GetClientRect(&rect);
	m_ctrl.MoveWindow(&rect);

	
}

void CMyAccessView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

	// assume, if we get here, that the Document has opened
	// a valid datasource...
	int index = m_ctrl.AddDataSource(&GetDocument()->m_data);
	m_ctrl.SetDefDataSource(index);
	m_ctrl.SetGridUsingDataSource(index);
	m_ctrl.BestFit(0,m_ctrl.GetNumberCols()-1, 0, UG_BESTFIT_TOPHEADINGS);

	m_ctrl.SetNumberRows(GetDocument()->m_data.GetNumRowsComplete());
		
}

void CMyAccessView::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CView::OnShowWindow(bShow, nStatus);
	
	
}

void CMyAccessView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	m_drawRect=pInfo->m_rectDraw;	
	m_printPage=pInfo->m_nCurPage;	

	CView::OnPrint(pDC, pInfo);
}

void CMyAccessView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetCursor(LoadCursor(NULL,IDC_ARROW));
	//CView::OnMouseMove(nFlags, point);
}

BOOL CMyAccessView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
	return CView::OnEraseBkgnd(pDC);
}
