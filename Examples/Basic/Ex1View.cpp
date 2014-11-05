// Ex1View.cpp : implementation of the CEx1View class
//

#include "stdafx.h"
#include "MyCug.h"

#include "Ex1.h"

#include "Ex1Doc.h"
#include "Ex1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx1View

IMPLEMENT_DYNCREATE(CEx1View, CView)

BEGIN_MESSAGE_MAP(CEx1View, CView)
	//{{AFX_MSG_MAP(CEx1View)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_VIEW_USEXPTHEMES, OnViewUsexpthemes)
	ON_UPDATE_COMMAND_UI(ID_VIEW_USEXPTHEMES, OnUpdateViewUsexpthemes)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx1View construction/destruction

CEx1View::CEx1View()
{
	// TODO: add construction code here

}

CEx1View::~CEx1View()
{
}

BOOL CEx1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	// do this to the view that will contain Ultimate Grid
	cs.style |= WS_CLIPCHILDREN;

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx1View drawing

void CEx1View::OnDraw(CDC* pDC)
{
	CEx1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->SetTitle (_T("Ulitimate Grid"));
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEx1View diagnostics

#ifdef _DEBUG
void CEx1View::AssertValid() const
{
	CView::AssertValid();
}

void CEx1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx1Doc* CEx1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx1Doc)));
	return (CEx1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx1View message handlers

int CEx1View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	RECT	rect;
	GetClientRect(&rect);
	m_ctrl.CreateGrid(WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
						rect,this,1234);

	CenterWindow();


	
	return 0;
}

void CEx1View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	RECT rect;
	GetClientRect(&rect);
	m_ctrl.MoveWindow(&rect);
	
}

void CEx1View::OnViewUsexpthemes() 
{
	UGXPThemes::UseThemes(!UGXPThemes::UseThemes());
	m_ctrl.Invalidate();
}

void CEx1View::OnUpdateViewUsexpthemes(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes());
}

BOOL CEx1View::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
	return CWnd::OnEraseBkgnd(pDC);
}