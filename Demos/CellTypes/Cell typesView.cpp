// Cell typesView.cpp : implementation of the CCelltypesView class
//

#include "stdafx.h"
#include "Cell types.h"

#include "Cell typesDoc.h"
#include "Cell typesView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCelltypesView

IMPLEMENT_DYNCREATE(CCelltypesView, CView)

BEGIN_MESSAGE_MAP(CCelltypesView, CView)
	//{{AFX_MSG_MAP(CCelltypesView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_USEXPTHEMES_STYLE1, OnViewUsexpthemes1)
	ON_COMMAND(ID_USEXPTHEMES_STYLE2, OnViewUsexpthemes2)
	ON_COMMAND(ID_USEXPTHEMES_NONE, OnViewUsexpthemesNone)
	ON_UPDATE_COMMAND_UI(ID_USEXPTHEMES_STYLE1, OnUpdateViewUsexpthemes1)
	ON_UPDATE_COMMAND_UI(ID_USEXPTHEMES_STYLE2, OnUpdateViewUsexpthemes2)
	ON_UPDATE_COMMAND_UI(ID_USEXPTHEMES_NONE, OnUpdateViewUsexpthemesNone)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND(ID_VIEW_RESET, OnViewReset)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCelltypesView construction/destruction

CCelltypesView::CCelltypesView()
{
	// TODO: add construction code here

}

CCelltypesView::~CCelltypesView()
{
}

BOOL CCelltypesView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCelltypesView drawing

void CCelltypesView::OnDraw(CDC* pDC)
{
	CCelltypesDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CCelltypesView printing

BOOL CCelltypesView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCelltypesView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCelltypesView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCelltypesView diagnostics

#ifdef _DEBUG
void CCelltypesView::AssertValid() const
{
	CView::AssertValid();
}

void CCelltypesView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCelltypesDoc* CCelltypesView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCelltypesDoc)));
	return (CCelltypesDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCelltypesView message handlers

int CCelltypesView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_grid.CreateGrid( WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 234322 );
	
	return 0;
}

void CCelltypesView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_grid.MoveWindow( 0, 0, cx, cy );
}

BOOL CCelltypesView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
	// return CView::OnEraseBkgnd(pDC);
}

void CCelltypesView::OnViewUsexpthemes1() 
{
	UGXPThemes::UseThemes(true);
	UGXPThemes::SetGridStyle(Style1);

	this->Invalidate();
}

void CCelltypesView::OnViewUsexpthemes2() 
{
	UGXPThemes::UseThemes(true);
	UGXPThemes::SetGridStyle(Style2);

	this->Invalidate();
}

void CCelltypesView::OnViewUsexpthemesNone() 
{
	UGXPThemes::UseThemes(false);

	this->Invalidate();
}

void CCelltypesView::OnUpdateViewUsexpthemes1(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes() && (UGXPThemes::GetGridStyle() == Style1));	
}

void CCelltypesView::OnUpdateViewUsexpthemes2(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes() && (UGXPThemes::GetGridStyle() == Style2));	
}
void CCelltypesView::OnUpdateViewUsexpthemesNone(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(!UGXPThemes::UseThemes());	
}

void CCelltypesView::OnViewReset()
{
	m_grid.Reset();
}
