// DelimView.cpp : implementation of the CDelimView class
//

#include "stdafx.h"
#include "Delim.h"

#include "MyCug.h"

#include "DelimDoc.h"
#include "DelimView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDelimView

IMPLEMENT_DYNCREATE(CDelimView, CView)

BEGIN_MESSAGE_MAP(CDelimView, CView)
	//{{AFX_MSG_MAP(CDelimView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDelimView construction/destruction

CDelimView::CDelimView()
{
}

CDelimView::~CDelimView()
{
}

BOOL CDelimView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDelimView drawing

void CDelimView::OnDraw(CDC* pDC)
{
	CDelimDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CDelimView printing

BOOL CDelimView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDelimView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CDelimView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// CDelimView diagnostics

#ifdef _DEBUG
void CDelimView::AssertValid() const
{
	CView::AssertValid();
}

void CDelimView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDelimDoc* CDelimView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDelimDoc)));
	return (CDelimDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDelimView message handlers

int CDelimView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	RECT rect = {0,0,0,0};
	
	m_grid.CreateGrid(WS_CHILD|WS_VISIBLE,rect,this,123);

	return 0;
}

void CDelimView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	RECT rect;
	GetClientRect(&rect);

	m_grid.MoveWindow(&rect);
	

}
