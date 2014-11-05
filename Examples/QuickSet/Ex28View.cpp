// Ex28View.cpp : implementation of the CEx28View class
//

#include "stdafx.h"
#include "Ex28.h"

// include the header file for the Ultimate Grid derived class
#include "MyCug.h"

#include "Ex28Doc.h"
#include "Ex28View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx28View

IMPLEMENT_DYNCREATE(CEx28View, CView)

BEGIN_MESSAGE_MAP(CEx28View, CView)
	//{{AFX_MSG_MAP(CEx28View)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_VIEW_USEXPTHEMES, OnViewUsexpthemes)
	ON_UPDATE_COMMAND_UI(ID_VIEW_USEXPTHEMES, OnUpdateViewUsexpthemes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx28View construction/destruction

CEx28View::CEx28View()
{
	// TODO: add construction code here

}

CEx28View::~CEx28View()
{
}

BOOL CEx28View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx28View drawing

void CEx28View::OnDraw(CDC* pDC)
{
	CEx28Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->SetTitle (_T("Ultimate Grid"));
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEx28View diagnostics

#ifdef _DEBUG
void CEx28View::AssertValid() const
{
	CView::AssertValid();
}

void CEx28View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx28Doc* CEx28View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx28Doc)));
	return (CEx28Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx28View message handlers

int CEx28View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Create the Grid control in the client rectangle
	m_ctrl.CreateGrid(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,1234);
	
	return 0;
}

void CEx28View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// Adjust the size of the Grid control
	m_ctrl.MoveWindow( 0, 0, cx, cy );
}

void CEx28View::OnViewUsexpthemes() 
{
	UGXPThemes::UseThemes(!UGXPThemes::UseThemes());
	m_ctrl.Invalidate();
}

void CEx28View::OnUpdateViewUsexpthemes(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes());
}
