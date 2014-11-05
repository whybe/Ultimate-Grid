// Code3View.cpp : implementation of the CCode3View class
//

#include "stdafx.h"
#include "mycug.h"
#include "Code3.h"

#include "Code3Doc.h"
#include "Code3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCode3View

IMPLEMENT_DYNCREATE(CCode3View, CView)

BEGIN_MESSAGE_MAP(CCode3View, CView)
	//{{AFX_MSG_MAP(CCode3View)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_VIEW_USEXPTHEMES, OnViewUsexpthemes)
	ON_UPDATE_COMMAND_UI(ID_VIEW_USEXPTHEMES, OnUpdateViewUsexpthemes)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCode3View construction/destruction

CCode3View::CCode3View()
{
	// TODO: add construction code here

}

CCode3View::~CCode3View()
{
}

BOOL CCode3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = cs.style | WS_MAXIMIZE;
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCode3View drawing

void CCode3View::OnDraw(CDC* pDC)
{
	CCode3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CCode3View printing

BOOL CCode3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCode3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCode3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCode3View diagnostics

#ifdef _DEBUG
void CCode3View::AssertValid() const
{
	CView::AssertValid();
}

void CCode3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCode3Doc* CCode3View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCode3Doc)));
	return (CCode3Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCode3View message handlers

int CCode3View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	SendMessage(WM_MDIMAXIMIZE);
	RECT  rect={0,0,0,0};
	m_ctrl.CreateGrid(WS_CHILD|WS_VISIBLE,rect,this,7777);

	
	return 0;
}

void CCode3View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
		RECT rect;
		GetClientRect(&rect);
		m_ctrl.MoveWindow(&rect);
}

void CCode3View::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	m_ctrl.m_CUGGrid->SetFocus();
}

void CCode3View::OnViewUsexpthemes() 
{
	UGXPThemes::UseThemes(!UGXPThemes::UseThemes());
	m_ctrl.Invalidate();
	
}

void CCode3View::OnUpdateViewUsexpthemes(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes());	
}
