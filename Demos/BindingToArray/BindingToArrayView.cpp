// BindingToArrayView.cpp : implementation of the CBindingToArrayView class
//

#include "stdafx.h"
#include "BindingToArray.h"

#include "BindingToArrayDoc.h"
#include "BindingToArrayView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBindingToArrayView

IMPLEMENT_DYNCREATE(CBindingToArrayView, CView)

BEGIN_MESSAGE_MAP(CBindingToArrayView, CView)
	//{{AFX_MSG_MAP(CBindingToArrayView)
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
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBindingToArrayView construction/destruction

CBindingToArrayView::CBindingToArrayView()
{
	// TODO: add construction code here

}

CBindingToArrayView::~CBindingToArrayView()
{
}

BOOL CBindingToArrayView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBindingToArrayView drawing

void CBindingToArrayView::OnDraw(CDC* pDC)
{
	CBindingToArrayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CBindingToArrayView printing

BOOL CBindingToArrayView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBindingToArrayView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBindingToArrayView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBindingToArrayView diagnostics

#ifdef _DEBUG
void CBindingToArrayView::AssertValid() const
{
	CView::AssertValid();
}

void CBindingToArrayView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBindingToArrayDoc* CBindingToArrayView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBindingToArrayDoc)));
	return (CBindingToArrayDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBindingToArrayView message handlers

int CBindingToArrayView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_grid.CreateGrid( WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 23422 );
	
	return 0;
}

void CBindingToArrayView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_grid.MoveWindow( 0, 0, cx, cy );
}

BOOL CBindingToArrayView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
	// return CView::OnEraseBkgnd(pDC);
}


void CBindingToArrayView::OnViewUsexpthemes1() 
{
	UGXPThemes::UseThemes(true);
	UGXPThemes::SetGridStyle(Style1);

	this->Invalidate();
}

void CBindingToArrayView::OnViewUsexpthemes2() 
{
	UGXPThemes::UseThemes(true);
	UGXPThemes::SetGridStyle(Style2);

	this->Invalidate();
}

void CBindingToArrayView::OnViewUsexpthemesNone() 
{
	UGXPThemes::UseThemes(false);

	this->Invalidate();
}

void CBindingToArrayView::OnUpdateViewUsexpthemes1(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes() && (UGXPThemes::GetGridStyle() == Style1));	
}

void CBindingToArrayView::OnUpdateViewUsexpthemes2(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes() && (UGXPThemes::GetGridStyle() == Style2));	
}
void CBindingToArrayView::OnUpdateViewUsexpthemesNone(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(!UGXPThemes::UseThemes());	
}



