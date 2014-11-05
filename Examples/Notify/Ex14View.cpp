// Ex14View.cpp : implementation of the CEx14View class
//

#include "stdafx.h"
#include "Ex14.h"

// include the header file for the Ultimate Grid derived class
#include "MyCug.h"

#include "Ex14Doc.h"
#include "Ex14View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx14View

IMPLEMENT_DYNCREATE(CEx14View, CFormView)

BEGIN_MESSAGE_MAP(CEx14View, CFormView)
	//{{AFX_MSG_MAP(CEx14View)
	ON_WM_SIZE()
	ON_COMMAND(ID_VIEW_USEXPTHEMES, OnViewUsexpthemes)
	ON_UPDATE_COMMAND_UI(ID_VIEW_USEXPTHEMES, OnUpdateViewUsexpthemes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx14View construction/destruction

CEx14View::CEx14View() 
	:CFormView(CEx14View::IDD),
	m_ctrl(this)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

CEx14View::~CEx14View()
{
}

BOOL CEx14View::PreCreateWindow(CREATESTRUCT& cs)
{
	
	return CFormView::PreCreateWindow(cs);
}


void CEx14View::DoDataExchange(CDataExchange* pDX) 
{
	CFormView::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CEx14View)
	DDX_Control(pDX, IDC_NOTIFICATION_OUT, m_output);
	//}}AFX_DATA_MAP

}


/////////////////////////////////////////////////////////////////////////////
// CEx14View drawing

void CEx14View::OnDraw(CDC* pDC)
{
	CEx14Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->SetTitle(_T("Ultimate Grid"));
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEx14View diagnostics

#ifdef _DEBUG
void CEx14View::AssertValid() const
{
	CFormView::AssertValid();
}

void CEx14View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CEx14Doc* CEx14View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx14Doc)));
	return (CEx14Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx14View message handlers

void CEx14View::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	m_output.AddString("Notifiactions Recieved:");
	
	// attach the grid to the static control
	m_ctrl.AttachGrid(this, IDC_GRID);
}


void CEx14View::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);

	// resize components to take up all real estate
	CWnd* pWnd = GetDlgItem(IDC_GRID);
	if(pWnd)
		pWnd->SetWindowPos(NULL, 0, 0, cx, cy/2, SWP_NOZORDER);

	pWnd = GetDlgItem(IDC_NOTIFICATION_OUT);
	if(pWnd)
		pWnd->SetWindowPos(NULL, 0, cy/2+3, cx,cy/2-4, SWP_NOZORDER);
}

void CEx14View::AddNotificationMessage(LPCSTR message)
{
	m_output.SetCurSel(m_output.AddString(message));
}


void CEx14View::OnViewUsexpthemes() 
{
	UGXPThemes::UseThemes(!UGXPThemes::UseThemes());
	m_ctrl.Invalidate();	
}

void CEx14View::OnUpdateViewUsexpthemes(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(UGXPThemes::UseThemes());	
}
