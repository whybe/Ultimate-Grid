// Ex5View.cpp : implementation of the CEx5View class
//

#include "stdafx.h"

// include the header file for the Ultimate Grid derived class
#include "MyCug.h"

#include "Ex5.h"

#include "Ex5Doc.h"
#include "Ex5View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx5View

IMPLEMENT_DYNCREATE(CEx5View, CView)

BEGIN_MESSAGE_MAP(CEx5View, CView)
	//{{AFX_MSG_MAP(CEx5View)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_VIEW_USEXPTHEMES, OnViewUsexpthemes)
	ON_UPDATE_COMMAND_UI(ID_VIEW_USEXPTHEMES, OnUpdateViewUsexpthemes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx5View construction/destruction

CEx5View::CEx5View()
{
	// TODO: add construction code here

}

CEx5View::~CEx5View()
{
}

BOOL CEx5View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	// do this to the view that will contain Ultimate Grid
	cs.style |= WS_CLIPCHILDREN;


	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx5View drawing

void CEx5View::OnDraw(CDC* pDC)
{
	CEx5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->SetTitle(_T("Ultimate Grid Example 5"));

}

/////////////////////////////////////////////////////////////////////////////
// CEx5View diagnostics

#ifdef _DEBUG
void CEx5View::AssertValid() const
{
	CView::AssertValid();
}

void CEx5View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx5Doc* CEx5View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx5Doc)));
	return (CEx5Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx5View message handlers

int CEx5View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_ctrl.CreateGrid(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,1234);
	
	return 0;
}

void CEx5View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// Adjust the size of the Grid control
	m_ctrl.MoveWindow( 0, 0, cx, cy );

	
}

void CEx5View::OnViewUsexpthemes() 
{
	UGXPThemes::UseThemes(!UGXPThemes::UseThemes());
	m_ctrl.Invalidate();
}

void CEx5View::OnUpdateViewUsexpthemes(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes());
}
