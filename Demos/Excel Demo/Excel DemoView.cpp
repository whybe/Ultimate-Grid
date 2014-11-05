// Excel DemoView.cpp : implementation of the CExcelDemoView class
//

#include "stdafx.h"
#include "Excel Demo.h"

#include "Excel DemoDoc.h"
#include "Excel DemoView.h"
#include "XMLParser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExcelDemoView

IMPLEMENT_DYNCREATE(CExcelDemoView, CView)

BEGIN_MESSAGE_MAP(CExcelDemoView, CView)
	//{{AFX_MSG_MAP(CExcelDemoView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_THEMES_NONE, OnThemesNone)
	ON_UPDATE_COMMAND_UI(ID_THEMES_NONE, OnUpdateThemesNone)
	ON_COMMAND(ID_THEMES_STYLE1, OnThemesStyle1)
	ON_UPDATE_COMMAND_UI(ID_THEMES_STYLE1, OnUpdateThemesStyle1)
	ON_COMMAND(ID_THEMES_STYLE2, OnThemesStyle2)
	ON_UPDATE_COMMAND_UI(ID_THEMES_STYLE2, OnUpdateThemesStyle2)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND(ID_VIEW_RESET, &CExcelDemoView::OnViewReset)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExcelDemoView construction/destruction

CExcelDemoView::CExcelDemoView()
{
	// TODO: add construction code here

}

CExcelDemoView::~CExcelDemoView()
{
}

BOOL CExcelDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CExcelDemoView drawing

void CExcelDemoView::OnDraw(CDC* pDC)
{
	UNREFERENCED_PARAMETER(pDC);
	CExcelDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CExcelDemoView printing

BOOL CExcelDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CExcelDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CExcelDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CExcelDemoView diagnostics

#ifdef _DEBUG
void CExcelDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CExcelDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExcelDemoDoc* CExcelDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExcelDemoDoc)));
	return (CExcelDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExcelDemoView message handlers

int CExcelDemoView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_grid.CreateGrid( WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 2343 );
	
	return 0;
}

void CExcelDemoView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	m_grid.MoveWindow( 0, 0, cx, cy );
}

BOOL CExcelDemoView::OnEraseBkgnd(CDC* pDC) 
{
	UNREFERENCED_PARAMETER(pDC);
	// TODO: Add your message handler code here and/or call default
	return FALSE;
	// return CView::OnEraseBkgnd(pDC);
}

void CExcelDemoView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	if ( GetDocument()->GetOpenFilename() != _T(""))
	{
		CXMLParser xmlParser;
		xmlParser.SetGridObject( &m_grid );
		xmlParser.Load( GetDocument()->GetOpenFilename());
		m_grid.AdjustComponentSizes();
	}
	else
	{
		int cols = 10,
			rows = 50;

		m_grid.SetDefColWidth( 60 );
		m_grid.SetNumberRows( rows );
		m_grid.SetNumberCols( cols );

		CUGCell cell;

		for ( int xIndex = 0; xIndex < cols; xIndex ++ )
		{
			m_grid.GetCell( xIndex, 0, &cell );

			for ( int yIndex = 0; yIndex < rows; yIndex ++ )
			{
				cell.SetNumberDecimals( 0 );
				cell.SetNumber( xIndex * yIndex );
				cell.SetAlignment( UG_ALIGNRIGHT );

				switch((int)rand()%7 )
				{
				case 1:
					cell.SetBackColor( RGB( 255, 255, 255 ));
					cell.SetTextColor( RGB( 255, 0, 0 ));
					break;
				case 2:
					cell.SetBackColor( RGB( 100, 80, 128 ));
					cell.SetTextColor( RGB( 240, 240, 210 ));
					break;
				case 3:
					cell.SetBackColor( RGB( 255, 255, 128 ));
					cell.SetTextColor( RGB( 100, 100, 100 ));
					break;
				default:
					cell.SetBackColor( RGB( 255, 255, 255 ));
					cell.SetTextColor( RGB( 0, 0, 0 ));
					break;
				}

				m_grid.SetCell( xIndex, yIndex, &cell );
			}
		}
	}

	m_grid.SetInitialCellStates();
}

void CExcelDemoView::OnFileClose()
{
	GetDocument()->SetTitle( _T("Untitled"));
	// for each sheet in the grid delete all information
	int sheetCount = m_grid.GetNumberSheets();
	for ( int nIndex = 0; nIndex < sheetCount; nIndex ++ )
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
	for ( int nIndex2 = 0; nIndex2 < tabCount; ++nIndex2 )
		m_grid.m_CUGTab->DeleteTab( m_grid.m_CUGTab->GetTabID( 0 ));
}

void CExcelDemoView::OnFileSave()
{
	if ( GetDocument()->GetOpenFilename() == _T(""))
		OnFileSaveAs();
	else
	{
		CXMLParser xmlParser;
		xmlParser.SetGridObject( &m_grid );
		
		CString openFileBackup = GetDocument()->GetOpenFilename();
		xmlParser.Save( openFileBackup );
		OnFileClose();
		GetDocument()->SetOpenFilename( openFileBackup );
		xmlParser.Load( GetDocument()->GetOpenFilename());
		m_grid.AdjustComponentSizes();
	}
}

void CExcelDemoView::OnFileSaveAs()
{
	CFileDialog fileDlg( FALSE, _T("xml"), NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, _T("XML documents (*.xml)|*.xml|All Files (*.*)|*.*|"), this );

	if ( fileDlg.DoModal() == IDOK )
	{
		CXMLParser xmlParser;
		xmlParser.SetGridObject( &m_grid );
		CString openFile = fileDlg.GetPathName();

		xmlParser.Save( openFile );
		OnFileClose();
		GetDocument()->SetTitle( fileDlg.GetFileName());
		GetDocument()->SetOpenFilename( openFile );
		xmlParser.Load( openFile );
		m_grid.AdjustComponentSizes();
	}
}


void CExcelDemoView::OnThemesNone()
{
	UGXPThemes::UseThemes(false);
	Invalidate(FALSE);
}

void CExcelDemoView::OnUpdateThemesNone(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(!UGXPThemes::UseThemes());	
}

void CExcelDemoView::OnThemesStyle1()
{
	UGXPThemes::UseThemes(true);
	UGXPThemes::SetGridStyle(Style1);
	Invalidate(FALSE);
}

void CExcelDemoView::OnUpdateThemesStyle1(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes() && UGXPThemes::GetGridStyle() == Style1);	
}

void CExcelDemoView::OnThemesStyle2()
{
	UGXPThemes::UseThemes(true);
	UGXPThemes::SetGridStyle(Style2);
	Invalidate(FALSE);
}

void CExcelDemoView::OnUpdateThemesStyle2(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes() && UGXPThemes::GetGridStyle() == Style2);	
}

void CExcelDemoView::OnViewReset()
{
	m_grid.ResetAll(true);
}
