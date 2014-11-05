// SetupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "speedtest.h"
#include "SetupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg dialog


CSetupDlg::CSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetupDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_interval = 1;
	m_redrawDelay = 100;
	m_cols = 10;
	m_rows = 200;
}


void CSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetupDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetupDlg, CDialog)
	//{{AFX_MSG_MAP(CSetupDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg message handlers

int CSetupDlg::GetInterval()
{
	return m_interval;
}

int CSetupDlg::GetRedrawDelay()
{
	return m_redrawDelay;
}

int CSetupDlg::GetNumberRows()
{
	return m_rows;
}

int CSetupDlg::GetNumberCols()
{
	return m_cols;
}

BOOL CSetupDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem( IDC_COLS )->SetWindowText( "10" );
	GetDlgItem( IDC_ROWS )->SetWindowText( "200" );
	GetDlgItem( IDC_INTERVAL )->SetWindowText( "1" );
	GetDlgItem( IDC_REDRAW_DELAY )->SetWindowText( "100" );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetupDlg::OnOK() 
{
	// TODO: Add extra validation here
	m_interval = GetDlgItemInt( IDC_INTERVAL );
	m_redrawDelay = GetDlgItemInt( IDC_REDRAW_DELAY );
	m_rows = GetDlgItemInt( IDC_ROWS );
	m_cols = GetDlgItemInt( IDC_COLS );

	CDialog::OnOK();
}
