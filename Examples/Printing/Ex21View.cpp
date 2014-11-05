// Ex21View.cpp : implementation of the CEx21View class
//

#include "stdafx.h"
#include "Ex21.h"

#include "Mycug.h"

#include "Ex21Doc.h"
#include "Ex21View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx21View

IMPLEMENT_DYNCREATE(CEx21View, CView)

BEGIN_MESSAGE_MAP(CEx21View, CView)
	//{{AFX_MSG_MAP(CEx21View)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_VIEW_USEXPTHEMES, OnViewUsexpthemes)
	ON_UPDATE_COMMAND_UI(ID_VIEW_USEXPTHEMES, OnUpdateViewUsexpthemes)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx21View construction/destruction

CEx21View::CEx21View()
{
	// TODO: add construction code here
}

CEx21View::~CEx21View()
{
}

BOOL CEx21View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx21View drawing

void CEx21View::OnDraw(CDC* pDC)
{
	CEx21Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here

	pDoc->SetTitle(_T("Ultimate Grid"));

	//If we are printing then "print" the appropriate page
	//otherwise fill the DC with white space
	
	CRect rect;
	if (m_isPrinting){
		rect = m_drawRect;
		m_ctrl.PrintPage(pDC, m_printPage);
	}
	else{
		GetClientRect(&rect);
		CBrush brush(RGB(255,255,255));
		pDC->FillRect(&rect,&brush);
	}

}

/////////////////////////////////////////////////////////////////////////////
// CEx21View printing

BOOL CEx21View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx21View::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add extra initialization before printing

	pInfo->SetMaxPage(m_ctrl.PrintInit(pDC,pInfo->m_pPD,0,0,m_ctrl.GetNumberCols()-1,
		m_ctrl.GetNumberRows()-1));
	m_isPrinting = TRUE;
}

void CEx21View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
	m_isPrinting = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CEx21View diagnostics

#ifdef _DEBUG
void CEx21View::AssertValid() const
{
	CView::AssertValid();
}

void CEx21View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx21Doc* CEx21View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx21Doc)));
	return (CEx21Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx21View message handlers

int CEx21View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	RECT rect;
	m_ctrl.CreateGrid(WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
		rect,this,1234);

	return 0;
}

void CEx21View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	RECT rect;
	GetClientRect(&rect);
	m_ctrl.MoveWindow(&rect);
}

void CEx21View::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class

	m_drawRect = pInfo->m_rectDraw;
	m_printPage = pInfo->m_nCurPage;

	CView::OnPrint(pDC, pInfo);
}

void CEx21View::OnViewUsexpthemes() 
{
	UGXPThemes::UseThemes(!UGXPThemes::UseThemes());
	m_ctrl.Invalidate();
}

void CEx21View::OnUpdateViewUsexpthemes(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes());
}
