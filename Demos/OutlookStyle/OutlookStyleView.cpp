// OutlookStyleView.cpp : implementation of the COutlookStyleView class
//

#include "stdafx.h"
#include "OutlookStyle.h"

#include "OutlookStyleDoc.h"
#include "OutlookStyleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "UGCTOutlookHeader.h"

/////////////////////////////////////////////////////////////////////////////
// COutlookStyleView

IMPLEMENT_DYNCREATE(COutlookStyleView, CView)

BEGIN_MESSAGE_MAP(COutlookStyleView, CView)
	//{{AFX_MSG_MAP(COutlookStyleView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(IDD_REDFLAG, OnRedFlag)
	ON_COMMAND(IDD_BLUEFLAG, OnBlueFlag)
	ON_COMMAND(IDD_YELLOWFLAG, OnYellowFlag)
	ON_COMMAND(IDD_GREENFLAG, OnGreenFlag)
	ON_COMMAND(IDD_ORANGEFLAG, OnOrangeFlag)
	ON_COMMAND(IDD_PURPLEFLAG, OnPurpleFlag)
	ON_COMMAND(IDD_CLEARFLAG, OnClearFlag)
	ON_COMMAND(IDD_FLAGCOMPLETE, OnFlagComplete)
	ON_COMMAND(IDD_DEFAULTRED, OnDefRedFlag)
	ON_COMMAND(IDD_DEFAULTBLUE, OnDefBlueFlag)
	ON_COMMAND(IDD_DEFAULTYELLOW, OnDefYellowFlag)
	ON_COMMAND(IDD_DEFAULTGREEN, OnDefGreenFlag)
	ON_COMMAND(IDD_DEFAULTORANGE, OnDefOrangeFlag)
	ON_COMMAND(IDD_DEFAULTPURPLE, OnDefPurpleFlag)
	ON_COMMAND(ID_CHANGEREAD, OnChangeRead)
	ON_COMMAND(IDD_SHOWGROUPS, OnChangeShowGroups)
	ON_UPDATE_COMMAND_UI(IDD_SHOWGROUPS, OnUpdateShowgroups)
	ON_COMMAND(IDD_SORTDATE, OnSortByDate)
	ON_UPDATE_COMMAND_UI(IDD_SORTDATE, OnUpdateSortByDate)
	ON_COMMAND(IDD_SORTFROM, OnSortByFrom)
	ON_UPDATE_COMMAND_UI(IDD_SORTFROM, OnUpdateSortByFrom)
	ON_COMMAND(IDD_SORTSIZE, OnSortBySize)
	ON_UPDATE_COMMAND_UI(IDD_SORTSIZE, OnUpdateSortBySize)
	ON_COMMAND(IDD_SORTSUBJECT, OnSortBySubject)
	ON_UPDATE_COMMAND_UI(IDD_SORTSUBJECT, OnUpdateSortBySubject)
	ON_COMMAND(IDD_SORTFLAG, OnSortByFlag)
	ON_UPDATE_COMMAND_UI(IDD_SORTFLAG, OnUpdateSortByFlag)
	ON_COMMAND(IDD_SORTATTACHMENTS, OnSortByAttachments)
	ON_UPDATE_COMMAND_UI(IDD_SORTATTACHMENTS, OnUpdateSortByAttachments)
	ON_COMMAND(IDD_CONTEXTEXPANDALL, OnExpandAll)
	ON_COMMAND(IDD_CONTEXTCOLLAPSEALL, OnCollapseAll)
	ON_COMMAND(IDD_CONTEXTMARKREAD, OnMarkReadAll)
	ON_COMMAND(IDD_CONTEXTMARKUNREAD, OnMarkUnreadAll)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDD_DEFAULTSELRED, OnDefRedFlag)
	ON_COMMAND(IDD_DEFAULTSELBLUE, OnDefBlueFlag)
	ON_COMMAND(IDD_DEFAULTSELYELLOW, OnDefYellowFlag)
	ON_COMMAND(IDD_DEFAULTSELGREEN, OnDefGreenFlag)
	ON_COMMAND(IDD_DEFAULTSELORANGE, OnDefOrangeFlag)
	ON_COMMAND(IDD_DEFAULTSELPURPLE, OnDefPurpleFlag)
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutlookStyleView construction/destruction

COutlookStyleView::COutlookStyleView()
{
	m_gridWidth = 248;
	m_isMoving = false;
	m_moveCursor = ::LoadCursor(NULL, IDC_SIZEWE);
	m_defaultCursor = ::LoadCursor(NULL, IDC_ARROW);
}

COutlookStyleView::~COutlookStyleView()
{
	::DestroyCursor(m_moveCursor);
	m_moveCursor = NULL;
	::DestroyCursor(m_defaultCursor);
	m_defaultCursor = NULL;
}

BOOL COutlookStyleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COutlookStyleView drawing

void COutlookStyleView::OnDraw(CDC* pDC)
{
	COutlookStyleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// COutlookStyleView printing

BOOL COutlookStyleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COutlookStyleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COutlookStyleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// COutlookStyleView diagnostics

#ifdef _DEBUG
void COutlookStyleView::AssertValid() const
{
	CView::AssertValid();
}

void COutlookStyleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COutlookStyleDoc* COutlookStyleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COutlookStyleDoc)));
	return (COutlookStyleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COutlookStyleView message handlers

int COutlookStyleView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_grid.CreateGrid( WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 234322 );

	 AfxInitRichEdit();
	RECT rc;
	rc.top = rc.bottom = rc.left = rc.right = 0;
	m_edit.Create(WS_CHILD | WS_VISIBLE | ES_MULTILINE, rc, this, 234323);

	m_grid.SetMailWindow(&m_edit);

	return 0;
}

void COutlookStyleView::SetControlPos()
{
	RECT rc;
	this->GetWindowRect(&rc);
	int cx = rc.right - rc.left;
	int cy = rc.bottom - rc.top;

	if (m_gridWidth > cx && cx > 0) m_gridWidth = cx;

	m_grid.MoveWindow(5, 5, m_gridWidth, cy - 10);
	
	m_edit.MoveWindow(m_gridWidth + 14, 9, cx - (m_gridWidth + 23), cy - 18);

	m_edit.RedrawWindow();

	Invalidate();
}

void COutlookStyleView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

	SetControlPos();
}

void COutlookStyleView::SetFlag(flagColor f)
{
	m_grid.SetFlag(f);
}

void COutlookStyleView::SetDefaultFlag(flagColor f)
{
	m_grid.SetDefaultFlag(f);
}

void COutlookStyleView::ChangeReadFlag()
{
	m_grid.ChangeReadFlag();
}

BOOL COutlookStyleView::OnEraseBkgnd(CDC* pDC) 
{
	// Draw the blue strips around the controls.
	RECT rc;
	this->GetWindowRect(&rc);

	const int width = rc.right - rc.left;
	const int height = rc.bottom - rc.top;

	pDC->FillSolidRect(0, 0, width, 5, RGB(196, 218, 250));
	pDC->FillSolidRect(width - 8, 0, 8, height, RGB(196, 218, 250));
	pDC->FillSolidRect(0, 0, 5, height, RGB(196, 218, 250));
	pDC->FillSolidRect(0, height-8, width, 8, RGB(196, 218, 250));
	pDC->FillSolidRect(m_gridWidth + 5, 0, 5, height, RGB(196, 218, 250));

	pDC->FillSolidRect(m_gridWidth + 10, 5, width - m_gridWidth - 15, 5, RGB(255, 255, 255));
	pDC->FillSolidRect(m_gridWidth + 10, height-10, width - m_gridWidth - 15, 5, RGB(255, 255, 255));
	pDC->FillSolidRect(m_gridWidth + 10, 5, 5, height-10, RGB(255, 255, 255));
	pDC->FillSolidRect(width - 10, 5, 5, height-10, RGB(255, 255, 255));

	CPen blk(PS_SOLID, 1, RGB(0, 0, 0));

	CPen * pOldPen = pDC->SelectObject(&blk);

	pDC->MoveTo(4, 4);
	pDC->LineTo(4, height-5);
	pDC->LineTo(m_gridWidth + 5, height-5);
	pDC->LineTo(m_gridWidth + 5, 4);
	pDC->LineTo(4, 4);

	pDC->MoveTo(m_gridWidth + 8, 4);
	pDC->LineTo(m_gridWidth + 8, height-5);
	pDC->LineTo(width - 4, height-5);
	pDC->LineTo(width - 4, 4);
	pDC->LineTo(m_gridWidth + 8, 4);

	pDC->SelectObject(pOldPen);

	return TRUE;
}

void COutlookStyleView::OnRedFlag()
{
   SetFlag(red);
}

void COutlookStyleView::OnBlueFlag()
{
	SetFlag(blue);
}

void COutlookStyleView::OnYellowFlag()
{
	SetFlag(yellow);
}

void COutlookStyleView::OnGreenFlag()
{
	SetFlag(green);
}

void COutlookStyleView::OnOrangeFlag()
{
    SetFlag(orange);
}

void COutlookStyleView::OnPurpleFlag()
{
    SetFlag(purple);
}

void COutlookStyleView::OnClearFlag()
{
    SetFlag(clear);
}

void COutlookStyleView::OnFlagComplete()
{
    SetFlag(check);
}

void COutlookStyleView::OnDefRedFlag()
{
    SetDefaultFlag(red);
}

void COutlookStyleView::OnDefBlueFlag()
{
    SetDefaultFlag(blue);
}

void COutlookStyleView::OnDefYellowFlag()
{
    SetDefaultFlag(yellow);
}

void COutlookStyleView::OnDefGreenFlag()
{
    SetDefaultFlag(green);
}

void COutlookStyleView::OnDefOrangeFlag()
{
	SetDefaultFlag(orange);
}

void COutlookStyleView::OnDefPurpleFlag()
{
	SetDefaultFlag(purple);
}

void COutlookStyleView::OnChangeRead()
{
	ChangeReadFlag();
}

void COutlookStyleView::OnChangeShowGroups()
{
	m_grid.SetShowGroups(!m_grid.GetShowGroups());
}

void COutlookStyleView::OnUpdateShowgroups(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_grid.GetShowGroups());
	
}

void COutlookStyleView::OnSortByDate()
{
	m_grid.SetSortBy(CUGCTMailSort::sortByDate);
}

void COutlookStyleView::OnUpdateSortByDate(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_grid.GetSortBy() == CUGCTMailSort::sortByDate);
}

void COutlookStyleView::OnSortByFrom()
{
	m_grid.SetSortBy(CUGCTMailSort::sortByFrom);
}

void COutlookStyleView::OnUpdateSortByFrom(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_grid.GetSortBy() == CUGCTMailSort::sortByFrom);
}

void COutlookStyleView::OnSortBySize()
{
	m_grid.SetSortBy(CUGCTMailSort::sortBySize);
}

void COutlookStyleView::OnUpdateSortBySize(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_grid.GetSortBy() == CUGCTMailSort::sortBySize);
}

void COutlookStyleView::OnSortBySubject()
{
	m_grid.SetSortBy(CUGCTMailSort::sortBySubject);
}

void COutlookStyleView::OnUpdateSortBySubject(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_grid.GetSortBy() == CUGCTMailSort::sortBySubject);
}

void COutlookStyleView::OnSortByFlag()
{
	m_grid.SetSortBy(CUGCTMailSort::sortByFlag);
}

void COutlookStyleView::OnUpdateSortByFlag(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_grid.GetSortBy() == CUGCTMailSort::sortByFlag);
}

void COutlookStyleView::OnSortByAttachments()
{
	m_grid.SetSortBy(CUGCTMailSort::sortByAttachments);
}

void COutlookStyleView::OnUpdateSortByAttachments(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_grid.GetSortBy() == CUGCTMailSort::sortByAttachments);
}

void COutlookStyleView::OnCollapseAll()
{
	m_grid.CollapseAll();
}

void COutlookStyleView::OnExpandAll()
{
	m_grid.ExpandAll();
}

void COutlookStyleView::OnMarkReadAll()
{
	m_grid.MarkAllRead();
}

void COutlookStyleView::OnMarkUnreadAll()
{
	m_grid.MarkAllUnread();
}

void COutlookStyleView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (point.x > m_gridWidth && point.x < m_gridWidth + 15)
	{
		m_oldMousePos = point;
		
		SetCapture();

		m_isMoving = true;
	}
	
	CView::OnLButtonDown(nFlags, point);
}

void COutlookStyleView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (point.x > m_gridWidth && point.x < m_gridWidth + 15)
	{
		SetCursor(m_moveCursor);
	}
	else if (!m_isMoving)
	{
		SetCursor(m_defaultCursor);
	}

	if (nFlags & MK_LBUTTON)
	{
		int x = point.x - m_oldMousePos.x;

		if (m_gridWidth + x >= 100) 
		{
			m_gridWidth += x;
			m_oldMousePos = point;
		}
		else
		{
			m_gridWidth = 100;
			POINT pt(m_oldMousePos);
			ClientToScreen(&pt);
			SetCursorPos(pt.x, pt.y);
		}
		
		SetControlPos();
	}
	else
	{
		m_isMoving = false;
		ReleaseCapture();
	}
	
	CView::OnMouseMove(nFlags, point);
}

BOOL COutlookStyleView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	return CView::OnSetCursor(pWnd, nHitTest, message);
}
