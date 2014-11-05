// EX25View.cpp : implementation of the CEX25View class
//

#include "stdafx.h"
#include "EX25.h"

// include the header file for the Ultimate Grid derived class
#include "MyCug.h"

#include "EX25Doc.h"
#include "EX25View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEX25View

IMPLEMENT_DYNCREATE(CEX25View, CView)

BEGIN_MESSAGE_MAP(CEX25View, CView)
	//{{AFX_MSG_MAP(CEX25View)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_VIEW_USEXPTHEES, OnViewUsexpthees)
	ON_UPDATE_COMMAND_UI(ID_VIEW_USEXPTHEES, OnUpdateViewUsexpthees)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEX25View construction/destruction

CEX25View::CEX25View()
{
	// TODO: add construction code here

}

CEX25View::~CEX25View()
{
}

BOOL CEX25View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEX25View drawing

void CEX25View::OnDraw(CDC* pDC)
{
	CEX25Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->SetTitle (_T("Ultimate Grid"));
}

/////////////////////////////////////////////////////////////////////////////
// CEX25View diagnostics

#ifdef _DEBUG
void CEX25View::AssertValid() const
{
	CView::AssertValid();
}

void CEX25View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEX25Doc* CEX25View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEX25Doc)));
	return (CEX25Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEX25View message handlers

int CEX25View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Create the Grid control in the client rectangle
	m_ctrl.CreateGrid(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,1234);

	CenterWindow();
	return 0;
}

void CEX25View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// Adjust the size of the Grid control
	m_ctrl.MoveWindow( 0, 0, cx, cy );
	
}

void CEX25View::OnViewUsexpthees() 
{
	UGXPThemes::UseThemes(!UGXPThemes::UseThemes());
	m_ctrl.Invalidate();
}

void CEX25View::OnUpdateViewUsexpthees(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes());
}
