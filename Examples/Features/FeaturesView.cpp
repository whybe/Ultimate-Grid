// FeaturesView.cpp : implementation of the CFeaturesView class
//

#include "stdafx.h"
#include "Features.h"

#include "MyCug.h"

#include "FeaturesDoc.h"
#include "FeaturesView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFeaturesView

IMPLEMENT_DYNCREATE(CFeaturesView, CView)

BEGIN_MESSAGE_MAP(CFeaturesView, CView)
	//{{AFX_MSG_MAP(CFeaturesView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_VIEW_USEXPTHEMES, OnViewUsexpthemes)
	ON_UPDATE_COMMAND_UI(ID_VIEW_USEXPTHEMES, OnUpdateViewUsexpthemes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFeaturesView construction/destruction

CFeaturesView::CFeaturesView()
{
	// TODO: add construction code here

}

CFeaturesView::~CFeaturesView()
{
}

BOOL CFeaturesView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFeaturesView drawing

void CFeaturesView::OnDraw(CDC* pDC)
{
	CFeaturesDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->SetTitle(_T("Ultimate Grid"));
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CFeaturesView diagnostics

#ifdef _DEBUG
void CFeaturesView::AssertValid() const
{
	CView::AssertValid();
}

void CFeaturesView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFeaturesDoc* CFeaturesView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFeaturesDoc)));
	return (CFeaturesDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFeaturesView message handlers

int CFeaturesView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	RECT rect = {0,0,50,50};
	m_grid.CreateGrid (WS_CHILD|WS_VISIBLE,rect,this,1234);

	return 0;
}

void CFeaturesView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	RECT rect;
	
	GetClientRect(&rect);
	m_grid.MoveWindow(&rect);
}

void CFeaturesView::OnViewUsexpthemes() 
{
	UGXPThemes::UseThemes(!UGXPThemes::UseThemes());
	m_grid.Invalidate();
}

void CFeaturesView::OnUpdateViewUsexpthemes(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes());
}
