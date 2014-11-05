// OpenDatabaseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dao sorting.h"
#include "OpenDatabaseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenDatabaseDlg dialog


COpenDatabaseDlg::COpenDatabaseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COpenDatabaseDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COpenDatabaseDlg)
	m_accessVer = -1;
	m_sql = _T("");
	m_fileName = _T("");
	m_openStyle = -1;
	m_tableName = _T("");
	//}}AFX_DATA_INIT
}


void COpenDatabaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COpenDatabaseDlg)
	DDX_Radio(pDX, IDC_ACCESS, m_accessVer);
	DDX_Text(pDX, IDC_SQL, m_sql);
	DDX_Text(pDX, IDC_FILE_NAME, m_fileName);
	DDX_Radio(pDX, IDC_OPEN_SQL, m_openStyle);
	DDX_Text(pDX, IDC_TABLE_NAME, m_tableName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COpenDatabaseDlg, CDialog)
	//{{AFX_MSG_MAP(COpenDatabaseDlg)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_OPEN_SQL, OnOpenSql)
	ON_BN_CLICKED(IDC_OPEN_TABLE, OnOpenTable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenDatabaseDlg message handlers

void COpenDatabaseDlg::OnOK() 
{
	// first make sure that all required fileds are filled
	CString fileName, sql;
	GetDlgItemText( IDC_FILE_NAME, fileName );
	GetDlgItemText( IDC_SQL, sql );

	UpdateData( TRUE );

	if ( fileName == _T("") || sql == _T("") )
	{
		MessageBox( _T("Not All required fields are populated, please double check"),
					_T("Entry error") );

		return;
	}

	if ( m_accessVer == 1 )
	{	// selected database is created with MS Access 2000
		// following line will allow me to use new DAO 3.6
		AfxGetModuleState()->m_dwVersion = 0x0601; 
	}
	
	CDialog::OnOK();
}

void COpenDatabaseDlg::OnBrowse() 
{
	CFileDialog fileDlg( TRUE, _T("*.mdb"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
				_T("MS Access Files|*.mdb|All Files|*.*|"), this );

	if ( fileDlg.DoModal() == IDOK )
	{
		SetDlgItemText( IDC_FILE_NAME, fileDlg.GetPathName());
	}
}

CString COpenDatabaseDlg::GetFileName()
{
	return m_fileName;
}

CString COpenDatabaseDlg::GetSQL()
{
	return m_sql;
}

BOOL COpenDatabaseDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_openStyle = 0;	// default to open SQL
	m_accessVer = 1;	// make MS Access 2000 default
	m_sql = _T("SELECT * FROM customers");
	m_tableName = _T("<Blank>");
	m_fileName = _T("..\\..\\test.mdb");

	UpdateData( FALSE );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COpenDatabaseDlg::OnOpenSql() 
{
	UpdateData( TRUE );
	if ( m_openStyle == 0 )
	{
		GetDlgItem( IDC_SQL )->EnableWindow( TRUE );
		GetDlgItem( IDC_TABLE_NAME )->EnableWindow( FALSE );
	}
}

void COpenDatabaseDlg::OnOpenTable() 
{
	UpdateData( TRUE );
	if ( m_openStyle == 1 )
	{
		GetDlgItem( IDC_SQL )->EnableWindow( FALSE );
		GetDlgItem( IDC_TABLE_NAME )->EnableWindow( TRUE );
	}
}

void COpenDatabaseDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
