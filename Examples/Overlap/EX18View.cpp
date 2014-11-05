// EX18View.cpp : implementation of the CEX18View class
//

#include "stdafx.h"
#include "EX18.h"

// include the header file for the Ultimate Grid derived class
#include "MyCug.h"

#include "EX18Doc.h"
#include "EX18View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEX18View

IMPLEMENT_DYNCREATE(CEX18View, CView)

BEGIN_MESSAGE_MAP(CEX18View, CView)
	//{{AFX_MSG_MAP(CEX18View)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_VIEW_USEXPTHEMES, OnViewUsexpthemes)
	ON_UPDATE_COMMAND_UI(ID_VIEW_USEXPTHEMES, OnUpdateViewUsexpthemes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEX18View construction/destruction

CEX18View::CEX18View()
{
	// TODO: add construction code here

}

CEX18View::~CEX18View()
{
}

BOOL CEX18View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEX18View drawing

void CEX18View::OnDraw(CDC* pDC)
{
	CEX18Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->SetTitle(_T("Ultimate Grid"));
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEX18View diagnostics

#ifdef _DEBUG
void CEX18View::AssertValid() const
{
	CView::AssertValid();
}

void CEX18View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEX18Doc* CEX18View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEX18Doc)));
	return (CEX18Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEX18View message handlers

int CEX18View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Create the Grid control in the client rectangle
	m_ctrl.CreateGrid(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,1234);
	
	return 0;
}

void CEX18View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// Adjust the size of the Grid control
	m_ctrl.MoveWindow( 0, 0, cx, cy );
}


void CEX18View::OnViewUsexpthemes() 
{
	UGXPThemes::UseThemes(!UGXPThemes::UseThemes());
	m_ctrl.Invalidate();
}

void CEX18View::OnUpdateViewUsexpthemes(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes());	
}
