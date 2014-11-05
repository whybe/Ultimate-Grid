// Ex2View.cpp : implementation of the CEx2View class
//

#include "stdafx.h"

//include the header file for the Ultimate Grid derived class
#include "MyCug.h"

#include "Ex2.h"

#include "Ex2Doc.h"
#include "Ex2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx2View

IMPLEMENT_DYNCREATE(CEx2View, CView)

BEGIN_MESSAGE_MAP(CEx2View, CView)
	//{{AFX_MSG_MAP(CEx2View)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_VIEW_USEXPTHEMES, OnViewUsexpthemes)
	ON_UPDATE_COMMAND_UI(ID_VIEW_USEXPTHEMES, OnUpdateViewUsexpthemes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx2View construction/destruction

CEx2View::CEx2View()
{
	// TODO: add construction code here

}

CEx2View::~CEx2View()
{
}

BOOL CEx2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	// do this to the view that will contain Ultimate Grid
	cs.style |= WS_CLIPCHILDREN|WS_CLIPSIBLINGS;

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx2View drawing

void CEx2View::OnDraw(CDC* pDC)
{
	CEx2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEx2View diagnostics

#ifdef _DEBUG
void CEx2View::AssertValid() const
{
	CView::AssertValid();
}

void CEx2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx2Doc* CEx2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx2Doc)));
	return (CEx2Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx2View message handlers

int CEx2View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//: Create the Grid control in the client rectangle
	m_ctrl.CreateGrid(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,1234);
	
	return 0;
}

void CEx2View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	//: Adjust the size of the Grid control
	m_ctrl.MoveWindow( 0, 0, cx, cy );
	
}

void CEx2View::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	Invalidate();		// invalidate window
	UpdateWindow();	// force repaint
}

void CEx2View::OnViewUsexpthemes() 
{
	UGXPThemes::UseThemes(!UGXPThemes::UseThemes());
	m_ctrl.Invalidate();
}

void CEx2View::OnUpdateViewUsexpthemes(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes());
}

