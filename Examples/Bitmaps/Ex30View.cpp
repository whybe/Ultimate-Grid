// Ex30View.cpp : implementation of the CEx30View class
//

#include "stdafx.h"
#include "Ex30.h"

// include the header file for the Ultimate Grid derived class
#include "MyCug.h"

#include "Ex30Doc.h"
#include "Ex30View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx30View

IMPLEMENT_DYNCREATE(CEx30View, CView)

BEGIN_MESSAGE_MAP(CEx30View, CView)
	//{{AFX_MSG_MAP(CEx30View)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_VIEW_USEXPTHEMES, OnViewUsexpthemes)
	ON_UPDATE_COMMAND_UI(ID_VIEW_USEXPTHEMES, OnUpdateViewUsexpthemes)
	//}}AFX_MSG_MAP
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx30View construction/destruction

CEx30View::CEx30View()
{
	// TODO: add construction code here

}

CEx30View::~CEx30View()
{
}

BOOL CEx30View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx30View drawing

void CEx30View::OnDraw(CDC* pDC)
{
	CEx30Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->SetTitle(_T("Ultimate Grid"));
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEx30View diagnostics

#ifdef _DEBUG
void CEx30View::AssertValid() const
{
	CView::AssertValid();
}

void CEx30View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx30Doc* CEx30View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx30Doc)));
	return (CEx30Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx30View message handlers

int CEx30View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Create the Grid control in the client rectangle
	m_ctrl.CreateGrid(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,1234);

	return 0;
}

void CEx30View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// Adjust the size of the Grid control
	m_ctrl.MoveWindow( 0, 0, cx, cy );
	
}

BOOL CEx30View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
	// return CView::OnEraseBkgnd(pDC);
}

void CEx30View::OnViewUsexpthemes() 
{
	UGXPThemes::UseThemes(!UGXPThemes::UseThemes());
	m_ctrl.Invalidate();
}

void CEx30View::OnUpdateViewUsexpthemes(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes());
}
