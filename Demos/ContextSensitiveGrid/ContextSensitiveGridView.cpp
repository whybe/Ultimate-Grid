// ContextSensitiveGridView.cpp : implementation of the CContextSensitiveGridView class
//

#include "stdafx.h"
#include "ContextSensitiveGrid.h"

#include "ContextSensitiveGridDoc.h"
#include "ContextSensitiveGridView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CContextSensitiveGridView

IMPLEMENT_DYNCREATE(CContextSensitiveGridView, CView)

BEGIN_MESSAGE_MAP(CContextSensitiveGridView, CView)
	//{{AFX_MSG_MAP(CContextSensitiveGridView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_HELPINFO()
	ON_COMMAND(ID_THEMES_NONE, OnThemesNone)
	ON_UPDATE_COMMAND_UI(ID_THEMES_NONE, OnUpdateThemesNone)
	ON_COMMAND(ID_THEMES_STYLE1, OnThemesStyle1)
	ON_UPDATE_COMMAND_UI(ID_THEMES_STYLE1, OnUpdateThemesStyle1)
	ON_COMMAND(ID_THEMES_STYLE2, OnThemesStyle2)
	ON_UPDATE_COMMAND_UI(ID_THEMES_STYLE2, OnUpdateThemesStyle2)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CContextSensitiveGridView construction/destruction

CContextSensitiveGridView::CContextSensitiveGridView()
{
	// TODO: add construction code here

}

CContextSensitiveGridView::~CContextSensitiveGridView()
{
}

BOOL CContextSensitiveGridView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CContextSensitiveGridView drawing

void CContextSensitiveGridView::OnDraw(CDC* pDC)
{
	CContextSensitiveGridDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CContextSensitiveGridView printing

BOOL CContextSensitiveGridView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CContextSensitiveGridView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CContextSensitiveGridView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CContextSensitiveGridView diagnostics

#ifdef _DEBUG
void CContextSensitiveGridView::AssertValid() const
{
	CView::AssertValid();
}

void CContextSensitiveGridView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CContextSensitiveGridDoc* CContextSensitiveGridView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CContextSensitiveGridDoc)));
	return (CContextSensitiveGridDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CContextSensitiveGridView message handlers

int CContextSensitiveGridView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_grid.CreateGrid( WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 13522 );
	
	return 0;
}

void CContextSensitiveGridView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	m_grid.MoveWindow( 0, 0, cx, cy );
}

BOOL CContextSensitiveGridView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
	//return CView::OnEraseBkgnd(pDC);
}

BOOL CContextSensitiveGridView::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CView::OnHelpInfo(pHelpInfo);
}

void CContextSensitiveGridView::OnThemesNone()
{
	UGXPThemes::UseThemes(false);
	Invalidate(FALSE);
}

void CContextSensitiveGridView::OnUpdateThemesNone(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(!UGXPThemes::UseThemes());	
	pCmdUI->Enable();
}

void CContextSensitiveGridView::OnThemesStyle1()
{
	UGXPThemes::UseThemes(true);
	UGXPThemes::SetGridStyle(Style1);
	Invalidate(FALSE);
}

void CContextSensitiveGridView::OnUpdateThemesStyle1(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes() && UGXPThemes::GetGridStyle() == Style1);	
}

void CContextSensitiveGridView::OnThemesStyle2()
{
	UGXPThemes::UseThemes(true);
	UGXPThemes::SetGridStyle(Style2);
	Invalidate(FALSE);
}

void CContextSensitiveGridView::OnUpdateThemesStyle2(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes() && UGXPThemes::GetGridStyle() == Style2);	
}
