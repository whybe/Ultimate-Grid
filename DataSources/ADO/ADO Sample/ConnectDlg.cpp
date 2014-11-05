// ConnectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ADO Sample.h"
#include "ConnectDlg.h"
#include "SQLUCODE.H"
#include <afxdb.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConnectDlg dialog
CConnectDlg::CConnectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConnectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConnectDlg)
	m_browseOpt = 0;
	//}}AFX_DATA_INIT
	m_szConnection = "";
	m_szSQL = "";
}

void CConnectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConnectDlg)
	DDX_Radio(pDX, IDC_RADIO1, m_browseOpt);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CConnectDlg, CDialog)
	//{{AFX_MSG_MAP(CConnectDlg)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_COMMAND_RANGE( IDC_RADIO1, IDC_RADIO2, OnRadioChage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConnectDlg message handlers
void CConnectDlg::OnOK() 
{
	// IDC_SQL_EDIT IDC_DNS_EDIT
	GetDlgItemText( IDC_DNS_EDIT, m_szConnection );
	GetDlgItemText( IDC_SQL_EDIT, m_szSQL );
	
	if ( m_szConnection != _T("") && m_szSQL != _T(""))
		CDialog::OnOK();
	else
	{
		MessageBox( _T("Please make sure that both the connection and SQL strings are filled in."), _T("Error ..."));
	}
}

BOOL CConnectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetDlgItemText( IDC_DNS_EDIT, _T("DSN=North;"));
	SetDlgItemText( IDC_SQL_EDIT, _T("SELECT * FROM Customers;"));
	
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConnectDlg::OnRadioChage( UINT nID )
{
	SetDlgItemText( IDC_DNS_EDIT, _T(""));
}

void CConnectDlg::OnBrowse() 
{
	UpdateData( TRUE );

	if ( m_browseOpt == 0 )
		DnsBrowse();
	else
		FileBrowse();
}

/////////////////////////////////////////////////////////////////
//	DnsBrowse
//		
//		
//		
int CConnectDlg::DnsBrowse()
{
	HENV henv;
	HDBC hdbc;
	RETCODE retcode;
	SQLTCHAR  szOutCon[2048];
	SWORD num;

	retcode = SQLAllocEnv(&henv);
	if (retcode == SQL_ERROR)
	{
		return retcode;
	}

	retcode = SQLAllocConnect(henv,&hdbc);
	if (retcode == SQL_ERROR)
	{
		SQLFreeEnv(henv);
		return retcode;
	}

	if ( retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO )
	{
		// Set login timeout to 5 seconds. 
		SQLSetConnectOption( hdbc, SQL_LOGIN_TIMEOUT, 5 );
		// Connect to data source 
        // this should cause the ODBC Driver to come up with the
		// necessary prompts to form a connect string...
		
		// NOTE: VC6 Unicode builds have a problem here unless SQLUCODE.H is explicitly loaded 
		
		SQLTCHAR szInCon[6] = _T("APP=;");
		retcode = SQLDriverConnect( hdbc, GetSafeHwnd(), szInCon, 6, szOutCon, 2048, &num, SQL_DRIVER_PROMPT );
		
		if ( retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO )
		{
			//			CString connStr;
			//			WCHAR pBuffer[2048];
			//
			//			MultiByteToWideChar( CP_ACP, 0, (LPCSTR)szOutCon, 2048, pBuffer, 2048 );
			//			connStr.Format( _T("%s"), pBuffer );
			//			SetDlgItemText( IDC_DNS_EDIT, connStr );
			SetDlgItemText( IDC_DNS_EDIT, (LPTSTR)szOutCon );
			SQLDisconnect( hdbc );
		}

		// cleanup
		SQLFreeConnect( hdbc );
		SQLFreeEnv( henv );
	 }
	
	return retcode;
}

int CConnectDlg::FileBrowse()
{
	CFileDialog fileDlg( TRUE, NULL, NULL, OFN_FILEMUSTEXIST, _T("MS Access files (*.mdb)|*.mdb|All Files(*.*)|*.*|"), this );

	if ( fileDlg.DoModal() == IDOK )
	{
		CString connStr;
		connStr.Format( _T("Driver={Microsoft Access Driver (*.mdb)};Dbq=%s;Uid=;Pwd=;"), fileDlg.GetPathName());
		SetDlgItemText( IDC_DNS_EDIT, connStr );
	}

	return 0;
}