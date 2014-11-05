// Ex26View.cpp : implementation of the CEx26View class
//

#include "stdafx.h"
#include "Ex26.h"

// include the header file for the Ultimate Grid derived class
#include "MyCug.h"

#include "Ex26Doc.h"
#include "Ex26View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx26View

IMPLEMENT_DYNCREATE(CEx26View, CView)

BEGIN_MESSAGE_MAP(CEx26View, CView)
	//{{AFX_MSG_MAP(CEx26View)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_VIEW_USEXPTHEMES, OnViewUsexpthemes)
	ON_UPDATE_COMMAND_UI(ID_VIEW_USEXPTHEMES, OnUpdateViewUsexpthemes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx26View construction/destruction

CEx26View::CEx26View()
{
	// TODO: add construction code here

}

CEx26View::~CEx26View()
{
}

BOOL CEx26View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx26View drawing

void CEx26View::OnDraw(CDC* pDC)
{
	CEx26Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->SetTitle(_T("Ultimate Grid"));

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEx26View diagnostics

#ifdef _DEBUG
void CEx26View::AssertValid() const
{
	CView::AssertValid();
}

void CEx26View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx26Doc* CEx26View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx26Doc)));
	return (CEx26Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx26View message handlers

int CEx26View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Create the Grid control in the client rectangle
	m_ctrl.CreateGrid(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,1234);

	CenterWindow();
	return 0;
}

void CEx26View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// Adjust the size of the Grid control
	m_ctrl.MoveWindow( 0, 0, cx, cy );
}

BOOL CEx26View::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
	// return CView::OnEraseBkgnd(pDC);
}

void CEx26View::OnViewUsexpthemes() 
{
	UGXPThemes::UseThemes(!UGXPThemes::UseThemes());
	m_ctrl.Invalidate();
}

void CEx26View::OnUpdateViewUsexpthemes(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes());	
}
