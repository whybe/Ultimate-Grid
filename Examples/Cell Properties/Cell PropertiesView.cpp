// Cell PropertiesView.cpp : implementation of the CCellPropertiesView class
//

#include "stdafx.h"
#include "Cell Properties.h"

#include "Cell PropertiesDoc.h"
#include "Cell PropertiesView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCellPropertiesView

IMPLEMENT_DYNCREATE(CCellPropertiesView, CView)

BEGIN_MESSAGE_MAP(CCellPropertiesView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_VIEW_USEXPTHEMES, OnViewUsexpthemes)
	ON_UPDATE_COMMAND_UI(ID_VIEW_USEXPTHEMES, OnUpdateViewUsexpthemes)
END_MESSAGE_MAP()

// CCellPropertiesView construction/destruction

CCellPropertiesView::CCellPropertiesView()
{
	// TODO: add construction code here

}

CCellPropertiesView::~CCellPropertiesView()
{
}

BOOL CCellPropertiesView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CCellPropertiesView drawing

void CCellPropertiesView::OnDraw(CDC* /*pDC*/)
{
	CCellPropertiesDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


// CCellPropertiesView printing

BOOL CCellPropertiesView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCellPropertiesView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCellPropertiesView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CCellPropertiesView diagnostics

#ifdef _DEBUG
void CCellPropertiesView::AssertValid() const
{
	CView::AssertValid();
}

void CCellPropertiesView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCellPropertiesDoc* CCellPropertiesView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCellPropertiesDoc)));
	return (CCellPropertiesDoc*)m_pDocument;
}
#endif //_DEBUG


// CCellPropertiesView message handlers

int CCellPropertiesView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	m_grid.CreateGrid( WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 23422 );

	return 0;
}

void CCellPropertiesView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	m_grid.MoveWindow( 0, 0, cx, cy );
}

void CCellPropertiesView::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);

	// TODO: Add your message handler code here
	m_grid.SetFocus();
}

BOOL CCellPropertiesView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
	//return CView::OnEraseBkgnd(pDC);
}

void CCellPropertiesView::OnViewUsexpthemes() 
{
	UGXPThemes::UseThemes(!UGXPThemes::UseThemes());
	m_grid.Invalidate();
}

void CCellPropertiesView::OnUpdateViewUsexpthemes(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes());
}
