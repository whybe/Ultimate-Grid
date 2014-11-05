// Ex7View.cpp : implementation of the CEx7View class
//

#include "stdafx.h"

// include the header file for the Ultimate Grid derived class
#include "MyCug.h"

#include "Ex7.h"

#include "Ex7Doc.h"
#include "Ex7View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx7View

IMPLEMENT_DYNCREATE(CEx7View, CView)

BEGIN_MESSAGE_MAP(CEx7View, CView)
	//{{AFX_MSG_MAP(CEx7View)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_VIEW_USEXPTHEMES, OnViewUsexpthemes)
	ON_UPDATE_COMMAND_UI(ID_VIEW_USEXPTHEMES, OnUpdateViewUsexpthemes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx7View construction/destruction

CEx7View::CEx7View()
{
	// TODO: add construction code here

}

CEx7View::~CEx7View()
{
}

BOOL CEx7View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	// do this to the view that will contain Ultimate Grid
	cs.style |= WS_CLIPCHILDREN;

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx7View drawing

void CEx7View::OnDraw(CDC* pDC)
{
	CEx7Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->SetTitle(_T("Ultimate Grid"));
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEx7View diagnostics

#ifdef _DEBUG
void CEx7View::AssertValid() const
{
	CView::AssertValid();
}

void CEx7View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx7Doc* CEx7View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx7Doc)));
	return (CEx7Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx7View message handlers

int CEx7View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Create the Grid control in the client rectangle
	m_ctrl.CreateGrid(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,1234);
	return 0;
}

void CEx7View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// Adjust the size of the Grid control
	m_ctrl.MoveWindow( 0, 0, cx, cy );

	if ( m_ctrl.GetSafeHwnd())
		m_ctrl.FitToWindow ( 0, m_ctrl.GetNumberCols () -1 );
}


void CEx7View::OnViewUsexpthemes() 
{
	UGXPThemes::UseThemes(!UGXPThemes::UseThemes());
	m_ctrl.Invalidate();
}

void CEx7View::OnUpdateViewUsexpthemes(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes());	
}
