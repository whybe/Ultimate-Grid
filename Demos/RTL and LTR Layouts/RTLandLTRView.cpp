// RTLandLTRView.cpp : implementation of the CRTLandLTRView class
//

#include "stdafx.h"
#include "RTLandLTR.h"

#include "RTLandLTRDoc.h"
#include "RTLandLTRView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRTLandLTRView

IMPLEMENT_DYNCREATE(CRTLandLTRView, CView)

BEGIN_MESSAGE_MAP(CRTLandLTRView, CView)
	//{{AFX_MSG_MAP(CRTLandLTRView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_SET_LRT, OnSetLrt)
	ON_COMMAND(ID_SET_RTL, OnSetRtl)
	ON_UPDATE_COMMAND_UI(ID_SET_LRT, OnUpdateSetLrt)
	ON_UPDATE_COMMAND_UI(ID_SET_RTL, OnUpdateSetRtl)
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
// CRTLandLTRView construction/destruction

CRTLandLTRView::CRTLandLTRView()
{
	// TODO: add construction code here

}

CRTLandLTRView::~CRTLandLTRView()
{
}

BOOL CRTLandLTRView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CRTLandLTRView drawing

void CRTLandLTRView::OnDraw(CDC* pDC)
{
	CRTLandLTRDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CRTLandLTRView printing

BOOL CRTLandLTRView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRTLandLTRView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRTLandLTRView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CRTLandLTRView diagnostics

#ifdef _DEBUG
void CRTLandLTRView::AssertValid() const
{
	CView::AssertValid();
}

void CRTLandLTRView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRTLandLTRDoc* CRTLandLTRView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRTLandLTRDoc)));
	return (CRTLandLTRDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRTLandLTRView message handlers

int CRTLandLTRView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_grid.CreateGrid( WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 234222 );
	
	return 0;
}

void CRTLandLTRView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_grid.MoveWindow( 0, 0, cx, cy );
}

BOOL CRTLandLTRView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
	//return CView::OnEraseBkgnd(pDC);
}

void CRTLandLTRView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	m_grid.SetFocus();
}

void CRTLandLTRView::OnSetLrt() 
{
	m_grid.SetGridLayout( 0 );
}

void CRTLandLTRView::OnSetRtl() 
{
	m_grid.SetGridLayout( 1 );
}

void CRTLandLTRView::OnUpdateSetLrt(CCmdUI* pCmdUI) 
{
	LONG lExStyles = GetWindowLong( m_grid.GetSafeHwnd(), GWL_EXSTYLE );

	if ( lExStyles&WS_EX_LAYOUTRTL )
		pCmdUI->SetCheck( 0 );
	else
		pCmdUI->SetCheck();
}

void CRTLandLTRView::OnUpdateSetRtl(CCmdUI* pCmdUI) 
{
	LONG lExStyles = GetWindowLong( m_grid.GetSafeHwnd(), GWL_EXSTYLE );

	if ( lExStyles&WS_EX_LAYOUTRTL )
		pCmdUI->SetCheck();
	else
		pCmdUI->SetCheck( 0 );
}


void CRTLandLTRView::OnThemesNone()
{
	UGXPThemes::UseThemes(false);
	Invalidate(FALSE);
}

void CRTLandLTRView::OnUpdateThemesNone(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(!UGXPThemes::UseThemes());	
}

void CRTLandLTRView::OnThemesStyle1()
{
	UGXPThemes::UseThemes(true);
	UGXPThemes::SetGridStyle(Style1);
	Invalidate(FALSE);
}

void CRTLandLTRView::OnUpdateThemesStyle1(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes() && UGXPThemes::GetGridStyle() == Style1);	
}

void CRTLandLTRView::OnThemesStyle2()
{
	UGXPThemes::UseThemes(true);
	UGXPThemes::SetGridStyle(Style2);
	Invalidate(FALSE);
}

void CRTLandLTRView::OnUpdateThemesStyle2(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes() && UGXPThemes::GetGridStyle() == Style2);	
}
