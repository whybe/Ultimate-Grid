// ChecklistView.cpp : implementation of the CChecklistView class
//

#include "stdafx.h"
#include "Checklist.h"

#include "ChecklistDoc.h"
#include "ChecklistView.h"

#include "ChecklistGrid.h"	// definition of CChecklistGrid

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define IDC_CHECKLIST1	(10001)


/////////////////////////////////////////////////////////////////////////////
// CChecklistView

IMPLEMENT_DYNCREATE(CChecklistView, CView)

BEGIN_MESSAGE_MAP(CChecklistView, CView)
	//{{AFX_MSG_MAP(CChecklistView)
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
// CChecklistView construction/destruction

CChecklistView::CChecklistView()
{
	// TODO: add construction code here
	m_pChecklistGrid = NULL;
}

CChecklistView::~CChecklistView()
{
	if (m_pChecklistGrid != NULL)
	{
		delete m_pChecklistGrid;
		m_pChecklistGrid = NULL;
	}
}

BOOL CChecklistView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CChecklistView drawing

void CChecklistView::OnDraw(CDC* pDC)
{
	CChecklistDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CChecklistView printing

BOOL CChecklistView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CChecklistView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CChecklistView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CChecklistView diagnostics

#ifdef _DEBUG
void CChecklistView::AssertValid() const
{
	CView::AssertValid();
}

void CChecklistView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChecklistDoc* CChecklistView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChecklistDoc)));
	return (CChecklistDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChecklistView message handlers

int CChecklistView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if ((m_pChecklistGrid = new CChecklistGrid) == NULL)
	{
		TRACE(_T("Unable to allocate memory for grid control.\n"));
		return -1;
	}

	
	if (!m_pChecklistGrid->CreateGrid(WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_CHECKLIST1))
	{
		TRACE(_T("Unable to create the grid control.\n"));
		return -1;
	}

	return 0;
}

void CChecklistView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if (m_pChecklistGrid != NULL)
	{
		ASSERT_VALID(m_pChecklistGrid);

		RECT rc;
		GetClientRect(&rc);
		m_pChecklistGrid->MoveWindow(&rc);
	}
}

void CChecklistView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	ASSERT_VALID(m_pChecklistGrid);

	if (m_pChecklistGrid != NULL)
	{
		
		if (!m_font.CreatePointFont(85, _T("Tahoma")))
		{
			TRACE(_T("Unable to create the font.\n"));
			m_font.DeleteObject();
		}
		
		m_pChecklistGrid->SetWidth(600);	// temporary - before first resize...
		
		TCHAR szBuffer[64];
		// insert some dummy items
		for (int i = 0; i < 50; i++)
		{
			wsprintf(szBuffer, _T("Item #%d"), i);
			m_pChecklistGrid->AddItem(i, szBuffer, TRUE, &m_font);

			if (i % 2 == 0)
			{
				long lStyle = UGCT_CHECKBOXROUND | UGCT_CHECKBOX3DRAISED;
				m_pChecklistGrid->SetItemStyle(i, lStyle);

				ASSERT(lStyle == m_pChecklistGrid->GetItemStyle(i));
			}

			ASSERT(m_pChecklistGrid->IsItemChecked(i) == TRUE);
		}

	}
}

void CChecklistView::OnViewUsexpthemes() 
{
	UGXPThemes::UseThemes(!UGXPThemes::UseThemes());
	 m_pChecklistGrid->Invalidate();
}

void CChecklistView::OnUpdateViewUsexpthemes(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes());
}
