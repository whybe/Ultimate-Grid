// TestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RTLandLTR.h"
#include "TestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog


CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDlg)
	ON_COMMAND_RANGE(IDC_RADIO1, IDC_RADIO2, OnLayoutChanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg message handlers

BOOL CTestDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_grid.AttachGrid( this, IDC_GRID );

	LONG lExStyles = GetWindowLong( m_grid.GetSafeHwnd(), GWL_EXSTYLE );

	if ( lExStyles&WS_EX_LAYOUTRTL )
		((CButton*)GetDlgItem( IDC_RADIO2 ))->SetCheck( TRUE );
	else
		((CButton*)GetDlgItem( IDC_RADIO1 ))->SetCheck( TRUE );


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// Callback function for EnumChildWindows() API
static BOOL CALLBACK EnumDlgChildWindows(HWND hwnd, LPARAM lParam)
{
	CTestDlg::ToggleLayout( hwnd );

	return TRUE;
}

void CTestDlg::ToggleLayout(HWND hwnd)
{
	LONG lExStyles = GetWindowLong(hwnd, GWL_EXSTYLE) ;

	// The following lines update the application layout to 
	// be right-to-left or left-to-right, as appropriate.
	lExStyles ^= WS_EX_LAYOUTRTL ; // Toggle layout.

	SetWindowLong(hwnd, GWL_EXSTYLE, lExStyles);
}

void CTestDlg::OnLayoutChanged( UINT nID )
{
	// first determine if layout switching is necessary
	LONG lExStyles = GetWindowLong( m_grid.GetSafeHwnd(), GWL_EXSTYLE );

	if (!( lExStyles&WS_EX_LAYOUTRTL ) && nID == IDC_RADIO1 )
		return;
	else if ( lExStyles&WS_EX_LAYOUTRTL && nID == IDC_RADIO2 )
		return;

	// Use ANSI versions of GetWindowLong() and SetWindowLong() because 
	// Unicode is not needed for these calls.
	ToggleLayout( m_hWnd );
	EnumChildWindows(m_hWnd, EnumDlgChildWindows, 0);

	// Force the tab control to re-position its scroll buttons.
	// This step is essential in order to have the grid display properly.
	m_grid.m_CUGTab->SendMessage( WM_SIZE );

	// Force the dialog and all of its components to redraw.
	Invalidate();
	UpdateWindow();
}
