// Ex16View.cpp : implementation of the CEx16View class
//

#include "stdafx.h"
#include "MyCug.h"

#include "Ex16.h"

#include "Ex16Doc.h"
#include "Ex16View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx16View

IMPLEMENT_DYNCREATE(CEx16View, CView)

BEGIN_MESSAGE_MAP(CEx16View, CView)
	//{{AFX_MSG_MAP(CEx16View)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_VIEW_USEXPTHEMES, OnViewUsexpthemes)
	ON_UPDATE_COMMAND_UI(ID_VIEW_USEXPTHEMES, OnUpdateViewUsexpthemes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx16View construction/destruction

CEx16View::CEx16View()
{
	// TODO: add construction code here

}

CEx16View::~CEx16View()
{
}

BOOL CEx16View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	// do this to the view that will contain Ultimate Grid
	cs.style |= WS_CLIPCHILDREN;

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx16View drawing

void CEx16View::OnDraw(CDC* pDC)
{
	CEx16Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->SetTitle (_T("Ultimate Grid"));
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEx16View diagnostics

#ifdef _DEBUG
void CEx16View::AssertValid() const
{
	CView::AssertValid();
}

void CEx16View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx16Doc* CEx16View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx16Doc)));
	return (CEx16Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx16View message handlers

int CEx16View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	RECT	rect;
	GetClientRect(&rect);
	m_ctrl.CreateGrid(WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN,
						rect,this,1234);
	CenterWindow();
	return 0;
}

void CEx16View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	

	// TODO: Add your message handler code here
	RECT rect;
	GetClientRect(&rect);
	m_ctrl.MoveWindow(&rect);
	
}


void CEx16View::OnViewUsexpthemes() 
{
	UGXPThemes::UseThemes(!UGXPThemes::UseThemes());
	m_ctrl.Invalidate();
}

void CEx16View::OnUpdateViewUsexpthemes(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes());
}