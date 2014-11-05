// XP Theme DemoView.cpp : implementation of the CXPThemeDemoView class
//

#include "stdafx.h"
#include "XP Theme Demo.h"

#include "XP Theme DemoDoc.h"
#include "XP Theme DemoView.h"

#include "UGXPthemes.h"

#include "EditStylesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXPThemeDemoView

IMPLEMENT_DYNCREATE(CXPThemeDemoView, CView)

BEGIN_MESSAGE_MAP(CXPThemeDemoView, CView)
	//{{AFX_MSG_MAP(CXPThemeDemoView)
		ON_WM_CREATE()
		ON_WM_SIZE()
		ON_WM_ERASEBKGND()
	ON_COMMAND(ID_THEMES_CUSTOM, OnThemesCustom)
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
// CXPThemeDemoView construction/destruction

CXPThemeDemoView::CXPThemeDemoView()
{
	// TODO: add construction code here

}

CXPThemeDemoView::~CXPThemeDemoView()
{
	UGXPThemes::CleanUp();
}

BOOL CXPThemeDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

int CXPThemeDemoView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_grid.CreateGrid( WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 234322 );
	
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CXPThemeDemoView drawing

void CXPThemeDemoView::OnDraw(CDC* pDC)
{
	CXPThemeDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CXPThemeDemoView printing

BOOL CXPThemeDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CXPThemeDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CXPThemeDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CXPThemeDemoView diagnostics

#ifdef _DEBUG
void CXPThemeDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CXPThemeDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CXPThemeDemoDoc* CXPThemeDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CXPThemeDemoDoc)));
	return (CXPThemeDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXPThemeDemoView message handlers

void CXPThemeDemoView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_grid.MoveWindow( 0, 0, cx, cy );
}

BOOL CXPThemeDemoView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
	// return CView::OnEraseBkgnd(pDC);
}

void CXPThemeDemoView::OnThemesCustom() 
{
	if (!UGXPThemes::UseThemes())
	{
		UGXPThemes::UseThemes(true);
	}

	CEditStylesDlg dlg;
	dlg.DoModal();
	Invalidate();
}

void CXPThemeDemoView::OnThemesNone() 
{
	UGXPThemes::UseThemes(false);
	Invalidate(FALSE);
}

void CXPThemeDemoView::OnUpdateThemesNone(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(!UGXPThemes::UseThemes());	
}

void CXPThemeDemoView::OnThemesStyle1() 
{
	UGXPThemes::UseThemes(true);
	UGXPThemes::SetGridStyle(Style1);
	Invalidate(FALSE);
}

void CXPThemeDemoView::OnUpdateThemesStyle1(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes() && UGXPThemes::GetGridStyle() == Style1);	
}

void CXPThemeDemoView::OnThemesStyle2() 
{
	UGXPThemes::UseThemes(true);
	UGXPThemes::SetGridStyle(Style2);
	Invalidate(FALSE);
}

void CXPThemeDemoView::OnUpdateThemesStyle2(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes() && UGXPThemes::GetGridStyle() == Style2);	
}
