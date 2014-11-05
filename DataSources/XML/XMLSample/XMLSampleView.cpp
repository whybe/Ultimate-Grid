// XMLSampleView.cpp : implementation of the CXMLSampleView class
//

#include "stdafx.h"
#include "XMLSample.h"

#include "XMLSampleDoc.h"
#include "XMLSampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXMLSampleView

IMPLEMENT_DYNCREATE(CXMLSampleView, CView)

BEGIN_MESSAGE_MAP(CXMLSampleView, CView)
	//{{AFX_MSG_MAP(CXMLSampleView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXMLSampleView construction/destruction

CXMLSampleView::CXMLSampleView()
{
	// TODO: add construction code here
}

CXMLSampleView::~CXMLSampleView()
{
}

BOOL CXMLSampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CXMLSampleView drawing

void CXMLSampleView::OnDraw(CDC* pDC)
{
	CXMLSampleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CXMLSampleView printing

BOOL CXMLSampleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CXMLSampleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CXMLSampleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CXMLSampleView diagnostics

#ifdef _DEBUG
void CXMLSampleView::AssertValid() const
{
	CView::AssertValid();
}

void CXMLSampleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CXMLSampleDoc* CXMLSampleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CXMLSampleDoc)));
	return (CXMLSampleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXMLSampleView message handlers

int CXMLSampleView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_grid.CreateGrid( WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 234222 );
	
	return 0;
}

void CXMLSampleView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_grid.MoveWindow( 0, 0, cx, cy );
}

void CXMLSampleView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	m_grid.SetFocus();
}

BOOL CXMLSampleView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
	// return CView::OnEraseBkgnd(pDC);
}

void CXMLSampleView::OnFileClose()
{
	GetDocument()->SetTitle( _T("Untitled"));
	// for each sheet in the grid delete all information
	int sheetCount = m_grid.GetNumberSheets();

	int nIndex;
	for ( nIndex = 0; nIndex < sheetCount; nIndex ++ )
	{
		m_grid.SetSheetNumber( nIndex );
		m_grid.SetNumberCols( 0 );
		m_grid.SetNumberRows( 0 );
		m_grid.GetDataSource( 0 )->Empty();
	}
	// reset currently visible sheet
	m_grid.SetSheetNumber( 0 );
	m_grid.SetNumberSheets( 1 );

	// delete information on current tabs
	int tabCount = m_grid.m_CUGTab->GetTabCount();
	for ( nIndex = 0; nIndex < tabCount; nIndex ++ )
		m_grid.m_CUGTab->DeleteTab( m_grid.m_CUGTab->GetTabID( 0 ));
}

void CXMLSampleView::OnFileSave()
{
	if ( GetDocument()->GetOpenFilename() == _T(""))
		OnFileSaveAs();
	else
	{
		CString openFileBackup = GetDocument()->GetOpenFilename();
		m_grid.SaveFile( openFileBackup );
		OnFileClose();
		GetDocument()->SetOpenFilename( openFileBackup );
		m_grid.OpenFile( openFileBackup );
		m_grid.AdjustComponentSizes();
	}
}

void CXMLSampleView::OnFileSaveAs()
{
	CFileDialog fileDlg( FALSE, _T("xml"), NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, _T("XML documents (*.xml)|*.xml|All Files (*.*)|*.*|"), this );

	if ( fileDlg.DoModal() == IDOK )
	{
		CString openFile = fileDlg.GetPathName();
		m_grid.SaveFile( openFile );
		OnFileClose();
		GetDocument()->SetTitle( fileDlg.GetFileName());
		GetDocument()->SetOpenFilename( openFile );
		m_grid.OpenFile( openFile );
		m_grid.AdjustComponentSizes();
	}
}

void CXMLSampleView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	if ( GetDocument()->GetOpenFilename() != _T(""))
	{
		m_grid.OpenFile( GetDocument()->GetOpenFilename());
		m_grid.AdjustComponentSizes();
	}
	else
	{
		m_grid.SetDefFont( m_grid.AddFont( _T("Arial"), -13, 400 ));
		m_grid.SetNumberCols( 10 );
		m_grid.SetNumberRows( 40 );
	}
}
