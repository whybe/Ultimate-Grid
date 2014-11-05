// Use UG LibView.cpp : implementation of the CUseUGLibView class
//

#include "stdafx.h"
#include "Use UG Lib.h"

#include "Use UG LibDoc.h"
#include "Use UG LibView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUseUGLibView

IMPLEMENT_DYNCREATE(CUseUGLibView, CView)

BEGIN_MESSAGE_MAP(CUseUGLibView, CView)
	//{{AFX_MSG_MAP(CUseUGLibView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUseUGLibView construction/destruction

CUseUGLibView::CUseUGLibView()
{
	// TODO: add construction code here

}

CUseUGLibView::~CUseUGLibView()
{
}

BOOL CUseUGLibView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CUseUGLibView drawing

void CUseUGLibView::OnDraw(CDC* pDC)
{
	CUseUGLibDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CUseUGLibView printing

BOOL CUseUGLibView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CUseUGLibView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CUseUGLibView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CUseUGLibView diagnostics

#ifdef _DEBUG
void CUseUGLibView::AssertValid() const
{
	CView::AssertValid();
}

void CUseUGLibView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CUseUGLibDoc* CUseUGLibView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUseUGLibDoc)));
	return (CUseUGLibDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CUseUGLibView message handlers

int CUseUGLibView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_grid.CreateGrid( WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 234323 );
	
	return 0;
}

void CUseUGLibView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_grid.MoveWindow( 0, 0, cx, cy );
}

void CUseUGLibView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	m_grid.SetFocus();
}

BOOL CUseUGLibView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
	// return CView::OnEraseBkgnd(pDC);
}
