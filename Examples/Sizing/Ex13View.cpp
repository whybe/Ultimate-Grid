// Ex13View.cpp : implementation of the CEx13View class
//

#include "stdafx.h"
#include "Ex13.h"

// include the header file for the Ultimate Grid derived class
#include "MyCug.h"

#include "Ex13Doc.h"
#include "Ex13View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx13View

IMPLEMENT_DYNCREATE(CEx13View, CView)

BEGIN_MESSAGE_MAP(CEx13View, CView)
	//{{AFX_MSG_MAP(CEx13View)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_VIEW_USEXPTHEMES, OnViewUsexpthemes)
	ON_UPDATE_COMMAND_UI(ID_VIEW_USEXPTHEMES, OnUpdateViewUsexpthemes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx13View construction/destruction

CEx13View::CEx13View()
{
	// TODO: add construction code here

}

CEx13View::~CEx13View()
{
}

BOOL CEx13View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx13View drawing

void CEx13View::OnDraw(CDC* pDC)
{
	CEx13Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->SetTitle (_T("Ultimate Grid"));
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEx13View diagnostics

#ifdef _DEBUG
void CEx13View::AssertValid() const
{
	CView::AssertValid();
}

void CEx13View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx13Doc* CEx13View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx13Doc)));
	return (CEx13Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx13View message handlers

int CEx13View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Create the Grid control in the client rectangle
	m_ctrl.CreateGrid(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,1234);
	CenterWindow();
	return 0;
}

void CEx13View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// Adjust the size of the Grid control
	m_ctrl.MoveWindow( 0, 0, cx, cy );
	
}

void CEx13View::OnViewUsexpthemes() 
{
	UGXPThemes::UseThemes(!UGXPThemes::UseThemes());
	m_ctrl.Invalidate();
}

void CEx13View::OnUpdateViewUsexpthemes(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes());
}
