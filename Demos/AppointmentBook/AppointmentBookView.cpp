// AppointmentBookView.cpp : implementation of the CAppointmentBookView class
//

#include "stdafx.h"
#include "AppointmentBook.h"

#include "AppointmentBookDoc.h"
#include "AppointmentBookView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAppointmentBookView

IMPLEMENT_DYNCREATE(CAppointmentBookView, CView)

BEGIN_MESSAGE_MAP(CAppointmentBookView, CView)
	//{{AFX_MSG_MAP(CAppointmentBookView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_USEXPTHEMES_STYLE1, OnViewUsexpthemes1)
	ON_COMMAND(ID_USEXPTHEMES_STYLE2, OnViewUsexpthemes2)
	ON_COMMAND(ID_USEXPTHEMES_NONE, OnViewUsexpthemesNone)
	ON_UPDATE_COMMAND_UI(ID_USEXPTHEMES_STYLE1, OnUpdateViewUsexpthemes1)
	ON_UPDATE_COMMAND_UI(ID_USEXPTHEMES_STYLE2, OnUpdateViewUsexpthemes2)
	ON_UPDATE_COMMAND_UI(ID_USEXPTHEMES_NONE, OnUpdateViewUsexpthemesNone)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppointmentBookView construction/destruction

CAppointmentBookView::CAppointmentBookView()
{
	// TODO: add construction code here

}

CAppointmentBookView::~CAppointmentBookView()
{
}

BOOL CAppointmentBookView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAppointmentBookView drawing

void CAppointmentBookView::OnDraw(CDC* pDC)
{
	CAppointmentBookDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CAppointmentBookView printing

BOOL CAppointmentBookView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAppointmentBookView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAppointmentBookView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CAppointmentBookView diagnostics

#ifdef _DEBUG
void CAppointmentBookView::AssertValid() const
{
	CView::AssertValid();
}

void CAppointmentBookView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAppointmentBookDoc* CAppointmentBookView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAppointmentBookDoc)));
	return (CAppointmentBookDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAppointmentBookView message handlers

int CAppointmentBookView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_grid.CreateGrid( WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 234333 );
	
	return 0;
}

void CAppointmentBookView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_grid.MoveWindow( 0, 0, cx, cy );
}

BOOL CAppointmentBookView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
	// return CView::OnEraseBkgnd(pDC);
}



void CAppointmentBookView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	m_grid.SetFocus();
}


void CAppointmentBookView::OnViewUsexpthemes1() 
{
	UGXPThemes::UseThemes(true);
	UGXPThemes::SetGridStyle(Style1);

	this->Invalidate();
}

void CAppointmentBookView::OnViewUsexpthemes2() 
{
	UGXPThemes::UseThemes(true);
	UGXPThemes::SetGridStyle(Style2);

	this->Invalidate();
}

void CAppointmentBookView::OnViewUsexpthemesNone() 
{
	UGXPThemes::UseThemes(false);

	this->Invalidate();
}

void CAppointmentBookView::OnUpdateViewUsexpthemes1(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes() && (UGXPThemes::GetGridStyle() == Style1));	
}

void CAppointmentBookView::OnUpdateViewUsexpthemes2(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes() && (UGXPThemes::GetGridStyle() == Style2));	
}
void CAppointmentBookView::OnUpdateViewUsexpthemesNone(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(!UGXPThemes::UseThemes());	
}



