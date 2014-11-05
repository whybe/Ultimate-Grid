// ExampleView.cpp : implementation of the CExampleView class
//

#include "stdafx.h"
#include "Example.h"

#include "ExampleDoc.h"
#include "ExampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExampleView

IMPLEMENT_DYNCREATE(CExampleView, CView)

BEGIN_MESSAGE_MAP(CExampleView, CView)
	//{{AFX_MSG_MAP(CExampleView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExampleView construction/destruction

CExampleView::CExampleView()
{
	// TODO: add construction code here

}

CExampleView::~CExampleView()
{
}

BOOL CExampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CExampleView drawing

void CExampleView::OnDraw(CDC* pDC)
{
	CExampleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CExampleView diagnostics

#ifdef _DEBUG
void CExampleView::AssertValid() const
{
	CView::AssertValid();
}

void CExampleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExampleDoc* CExampleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExampleDoc)));
	return (CExampleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExampleView message handlers

int CExampleView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Create the Grid control in the client rectangle
	RECT	rect;
	GetClientRect(&rect);
	m_ctrl.CreateGrid(WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
						rect,this,1234);
	
	return 0;
}

void CExampleView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// Adjust the size of the Grid control
	RECT rect;
	GetClientRect(&rect);
	m_ctrl.MoveWindow(&rect);
	
}
