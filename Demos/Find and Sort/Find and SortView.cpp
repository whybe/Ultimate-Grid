// Find and SortView.cpp : implementation of the CFindandSortView class
//

#include "stdafx.h"
#include "Find and Sort.h"

#include "Find and SortDoc.h"
#include "Find and SortView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindandSortView

IMPLEMENT_DYNCREATE(CFindandSortView, CView)

BEGIN_MESSAGE_MAP(CFindandSortView, CView)
	//{{AFX_MSG_MAP(CFindandSortView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_THEMES_NONE, OnThemesNone)
	ON_UPDATE_COMMAND_UI(ID_THEMES_NONE, OnUpdateThemesNone)
	ON_COMMAND(ID_THEMES_STYLE1, OnThemesStyle1)
	ON_UPDATE_COMMAND_UI(ID_THEMES_STYLE1, OnUpdateThemesStyle1)
	ON_COMMAND(ID_THEMES_STYLE2, OnThemesStyle2)
	ON_UPDATE_COMMAND_UI(ID_THEMES_STYLE2, OnUpdateThemesStyle2)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindandSortView construction/destruction

CFindandSortView::CFindandSortView()
{
	// TODO: add construction code here

}

CFindandSortView::~CFindandSortView()
{
}

BOOL CFindandSortView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFindandSortView drawing

void CFindandSortView::OnDraw(CDC* pDC)
{
	CFindandSortDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CFindandSortView printing

BOOL CFindandSortView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFindandSortView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFindandSortView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFindandSortView diagnostics

#ifdef _DEBUG
void CFindandSortView::AssertValid() const
{
	CView::AssertValid();
}

void CFindandSortView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFindandSortDoc* CFindandSortView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFindandSortDoc)));
	return (CFindandSortDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFindandSortView message handlers

int CFindandSortView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_grid.CreateGrid( WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 23432 );
	
	return 0;
}

void CFindandSortView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_grid.MoveWindow( 0, 0, cx, cy );
}

BOOL CFindandSortView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
	// return CView::OnEraseBkgnd(pDC);
}

void CFindandSortView::OnThemesNone()
{
	UGXPThemes::UseThemes(false);
	Invalidate(FALSE);
}

void CFindandSortView::OnUpdateThemesNone(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(!UGXPThemes::UseThemes());	
}

void CFindandSortView::OnThemesStyle1()
{
	UGXPThemes::UseThemes(true);
	UGXPThemes::SetGridStyle(Style1);
	Invalidate(FALSE);
}

void CFindandSortView::OnUpdateThemesStyle1(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes() && UGXPThemes::GetGridStyle() == Style1);	
}

void CFindandSortView::OnThemesStyle2()
{
	UGXPThemes::UseThemes(true);
	UGXPThemes::SetGridStyle(Style2);
	Invalidate(FALSE);
}

void CFindandSortView::OnUpdateThemesStyle2(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes() && UGXPThemes::GetGridStyle() == Style2);	
}
