// SplitterView.cpp : implementation of the CSplitterView class
//

#include "stdafx.h"
#include "Splitter.h"

#include "SplitterDoc.h"
#include "SplitterView.h"

#include "MyCUG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplitterView

IMPLEMENT_DYNCREATE(CSplitterView, CView)

BEGIN_MESSAGE_MAP(CSplitterView, CView)
	//{{AFX_MSG_MAP(CSplitterView)
	ON_WM_SIZE()
	ON_COMMAND(ID_VIEW_USEXPTHEES, OnViewUsexpthees)
	ON_UPDATE_COMMAND_UI(ID_VIEW_USEXPTHEES, OnUpdateViewUsexpthees)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplitterView construction/destruction

CSplitterView::CSplitterView()
{
	m_pGrid = NULL;
}

CSplitterView::~CSplitterView()
{
	if (m_pGrid != NULL)
		delete m_pGrid;
}

BOOL CSplitterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSplitterView drawing

void CSplitterView::OnDraw(CDC* pDC)
{
	CSplitterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSplitterView printing

BOOL CSplitterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSplitterView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSplitterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSplitterView diagnostics

#ifdef _DEBUG
void CSplitterView::AssertValid() const
{
	CView::AssertValid();
}

void CSplitterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSplitterDoc* CSplitterView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSplitterDoc)));
	return (CSplitterDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSplitterView message handlers

void CSplitterView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	if (m_pGrid == NULL)
	{
		// Create the grid object
		if ((m_pGrid = new CMyCUG()) != NULL)
		{
			RECT rect;
			GetClientRect(&rect);
			m_pGrid->CreateGrid(WS_CHILD | WS_VISIBLE, rect, this, 10001);
		}
	}	
}

void CSplitterView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// Move the grid window to fill the entire client area
	if (m_pGrid != NULL)
	{
		RECT rect;
		GetClientRect(&rect);
		
		m_pGrid->MoveWindow(&rect);
	}
}

void CSplitterView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// This function is called whenever the user has finished editing a cell.
	// We post a message here to tell the grid to clean the "dirty" area of
	// the window: the newly edited cell.
	if (m_pGrid != NULL)
		m_pGrid->PostMessage(WM_PAINT);
}

void CSplitterView::OnViewUsexpthees() 
{
	UGXPThemes::UseThemes(!UGXPThemes::UseThemes());
	m_pGrid->Invalidate();
}

void CSplitterView::OnUpdateViewUsexpthees(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes());
}
