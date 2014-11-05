// Ex27View.cpp : implementation of the CEx27View class
//

#include "stdafx.h"

// include the header file for the Ultimate Grid derived class
#include "MyCug.h"

#include "Ex27.h"

#include "Ex27Doc.h"
#include "Ex27View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx27View

IMPLEMENT_DYNCREATE(CEx27View, CView)

BEGIN_MESSAGE_MAP(CEx27View, CView)
	//{{AFX_MSG_MAP(CEx27View)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_VIEW_USEXPTHEMES, OnViewUsexpthemes)
	ON_UPDATE_COMMAND_UI(ID_VIEW_USEXPTHEMES, OnUpdateViewUsexpthemes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx27View construction/destruction

CEx27View::CEx27View()
{
	// TODO: add construction code here

}

CEx27View::~CEx27View()
{
}

BOOL CEx27View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx27View drawing

void CEx27View::OnDraw(CDC* pDC)
{
	CEx27Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->SetTitle (_T("Ultimate Grid"));
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEx27View diagnostics

#ifdef _DEBUG
void CEx27View::AssertValid() const
{
	CView::AssertValid();
}

void CEx27View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx27Doc* CEx27View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx27Doc)));
	return (CEx27Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx27View message handlers

int CEx27View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Create the Grid control in the client rectangle
	m_ctrl.CreateGrid(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,1234);
	
	return 0;
}

void CEx27View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here

	// Adjust the size of the Grid control
	m_ctrl.MoveWindow( 0, 0, cx, cy );
}

void CEx27View::OnViewUsexpthemes() 
{
	UGXPThemes::UseThemes(!UGXPThemes::UseThemes());
	m_ctrl.Invalidate();
}

void CEx27View::OnUpdateViewUsexpthemes(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes());
}
