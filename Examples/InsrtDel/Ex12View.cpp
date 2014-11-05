// Ex12View.cpp : implementation of the CEx12View class
//

#include "stdafx.h"

// include the header file for the Ultimate Grid derived class
#include "MyCug.h"

#include "Ex12.h"

#include "Ex12Doc.h"
#include "Ex12View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx12View

IMPLEMENT_DYNCREATE(CEx12View, CView)

BEGIN_MESSAGE_MAP(CEx12View, CView)
	//{{AFX_MSG_MAP(CEx12View)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_VIEW_USEXPTHEMES, OnViewUsexpthemes)
	ON_UPDATE_COMMAND_UI(ID_VIEW_USEXPTHEMES, OnUpdateViewUsexpthemes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx12View construction/destruction

CEx12View::CEx12View()
{
	// TODO: add construction code here

}

CEx12View::~CEx12View()
{
}

BOOL CEx12View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx12View drawing

void CEx12View::OnDraw(CDC* pDC)
{
	CEx12Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->SetTitle(_T("Ultimate Grid"));
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEx12View diagnostics

#ifdef _DEBUG
void CEx12View::AssertValid() const
{
	CView::AssertValid();
}

void CEx12View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx12Doc* CEx12View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx12Doc)));
	return (CEx12Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx12View message handlers

int CEx12View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	

	// Create the Grid control in the client rectangle
	m_ctrl.CreateGrid(WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,1234);
	
	CenterWindow();
	return 0;
}

void CEx12View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// Adjust the size of the Grid control
	m_ctrl.MoveWindow( 0, 0, cx, cy );
}


void CEx12View::OnViewUsexpthemes() 
{
	UGXPThemes::UseThemes(!UGXPThemes::UseThemes());
	m_ctrl.Invalidate();
}

void CEx12View::OnUpdateViewUsexpthemes(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes());	
}