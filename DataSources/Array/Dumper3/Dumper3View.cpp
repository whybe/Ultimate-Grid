// Dumper3View.cpp : implementation of the CDumper3View class
//

#include "stdafx.h"
#include "MyCug.h"

#include "Dumper3.h"

#include "Dumper3Doc.h"
#include "Dumper3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDumper3View

IMPLEMENT_DYNCREATE(CDumper3View, CView)

BEGIN_MESSAGE_MAP(CDumper3View, CView)
	//{{AFX_MSG_MAP(CDumper3View)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_EDIT_FIND, OnEditFind)
	ON_UPDATE_COMMAND_UI(ID_EDIT_FIND, OnUpdateEditFind)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDumper3View construction/destruction

CDumper3View::CDumper3View()
{
	// TODO: add construction code here
	m_ctrl = NULL;

}

CDumper3View::~CDumper3View()
{
	if(m_ctrl)
		delete m_ctrl;
}

BOOL CDumper3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDumper3View drawing

void CDumper3View::OnDraw(CDC* pDC)
{
	CDumper3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
		CRect rect;	if (m_isPrinting){	
			rect=m_drawRect;
			m_ctrl->PrintPage(pDC,m_printPage);	
		}
		else{
			GetClientRect(&rect);
			CBrush brush(RGB(255,255,255));
			pDC->FillRect(&rect,&brush);
		}
}

/////////////////////////////////////////////////////////////////////////////
// CDumper3View printing

BOOL CDumper3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDumper3View::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add extra initialization before printing
	m_ctrl->SetDefFont(&m_ctrl->m_printFont);
	m_ctrl->BestFit(0,1,1,0);
	pInfo->SetMaxPage(m_ctrl->PrintInit(pDC,pInfo->m_pPD,0,0,m_ctrl->GetNumberCols()-1,m_ctrl->GetNumberRows()-1));
	m_isPrinting = TRUE;
}

void CDumper3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
	m_ctrl->SetDefFont(&m_ctrl->m_font);
	m_ctrl->BestFit(0,1,1,0);
	m_isPrinting = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CDumper3View diagnostics

#ifdef _DEBUG
void CDumper3View::AssertValid() const
{
	CView::AssertValid();
}

void CDumper3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDumper3Doc* CDumper3View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDumper3Doc)));
	return (CDumper3Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDumper3View message handlers

void CDumper3View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(m_ctrl != NULL) {
		RECT rect;
		GetClientRect(&rect);
		m_ctrl->MoveWindow(&rect);
		m_ctrl->BestFit(0,1,1,0);
	}
}

void CDumper3View::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	m_ctrl = new MyCug;
	RECT rect;
	GetClientRect(&rect);
	m_ctrl->m_data.m_byteArray = &(GetDocument()->m_byteArray);
	m_ctrl->CreateGrid(WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN, rect, this, 1777);
	m_ctrl->BestFit(0,1,1,0);
    m_ctrl->AdjustComponentSizes();

	
}

BOOL CDumper3View::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
//	return CView::OnEraseBkgnd(pDC);
}

void CDumper3View::OnEditFind() 
{
	// TODO: Add your command handler code here
	m_ctrl->OnEditFind();
}

void CDumper3View::OnUpdateEditFind(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	m_ctrl->OnUpdateEditFind(pCmdUI);
}

void CDumper3View::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_drawRect=pInfo->m_rectDraw;
	m_printPage=pInfo->m_nCurPage;
	
	CView::OnPrint(pDC, pInfo);
}
