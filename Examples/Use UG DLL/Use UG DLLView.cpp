// Use UG DLLView.cpp : implementation of the CUseUGDLLView class
//

#include "stdafx.h"
#include "Use UG DLL.h"

#include "Use UG DLLDoc.h"
#include "Use UG DLLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUseUGDLLView

IMPLEMENT_DYNCREATE(CUseUGDLLView, CView)

BEGIN_MESSAGE_MAP(CUseUGDLLView, CView)
	//{{AFX_MSG_MAP(CUseUGDLLView)
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
// CUseUGDLLView construction/destruction

CUseUGDLLView::CUseUGDLLView()
{
	// TODO: add construction code here

}

CUseUGDLLView::~CUseUGDLLView()
{
}

BOOL CUseUGDLLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CUseUGDLLView drawing

void CUseUGDLLView::OnDraw(CDC* pDC)
{
	CUseUGDLLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CUseUGDLLView printing

BOOL CUseUGDLLView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CUseUGDLLView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CUseUGDLLView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CUseUGDLLView diagnostics

#ifdef _DEBUG
void CUseUGDLLView::AssertValid() const
{
	CView::AssertValid();
}

void CUseUGDLLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CUseUGDLLDoc* CUseUGDLLView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUseUGDLLDoc)));
	return (CUseUGDLLDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CUseUGDLLView message handlers

int CUseUGDLLView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_grid.CreateGrid( WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 234222 );
	
	return 0;
}

void CUseUGDLLView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_grid.MoveWindow( 0, 0, cx, cy );
}

void CUseUGDLLView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	m_grid.SetFocus();
}

BOOL CUseUGDLLView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
	// return CView::OnEraseBkgnd(pDC);
}
