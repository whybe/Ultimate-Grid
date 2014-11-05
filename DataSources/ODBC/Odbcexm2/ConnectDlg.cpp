// ConnectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "selectsqldlg.h"
#include "db7.h"
#include "ConnectDlg.h"

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
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	// one time init
	m_nOpenType = CRecordset::dynaset;
}


void CConnectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConnectDlg)
	DDX_Control(pDX, IDC_SQLDOTBUTTON, m_sqlButton);
	DDX_Control(pDX, IDC_SQLEDIT, m_sqlEdit);
	DDX_Control(pDX, IDC_DSNCOMBO, m_dsnCombo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConnectDlg, CDialog)
	//{{AFX_MSG_MAP(CConnectDlg)
	ON_BN_CLICKED(IDC_BROWSEBUTTON, OnBrowsebutton)
	ON_BN_CLICKED(IDC_RADIODYNASET, OnRadiodynaset)
	ON_BN_CLICKED(IDC_RADIOSNAPSHOT, OnRadiosnapshot)
	ON_BN_CLICKED(IDC_SQLDOTBUTTON, OnSqldotbutton)
	ON_CBN_SELCHANGE(IDC_DSNCOMBO, OnSelchangeDsncombo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConnectDlg message handlers

void CConnectDlg::OnBrowsebutton() 
{
	// empty the array of SQL statements
	m_selectSQLDlg.m_strSQLArray.RemoveAll();

	if(UG_SUCCESS == m_pOdbc->Browse(this->m_hWnd)) {
		//  get the table names from the datasource...
		int i = 0;
		SQLDatasourceInfo*	dbI;
		CString sqlString;
		
		while(dbI = m_pOdbc->GetTableInfo(i++)){
			// ... and put them in the list in the select sql dialog
            // Put [] around name only if has spaces
            if(0 != _tcschr((LPTSTR)dbI->tableName, 32))
			    sqlString.Format(_T("Select * FROM [%s]"),dbI->tableName);
            else
			    sqlString.Format(_T("Select * FROM %s"),dbI->tableName);
			m_selectSQLDlg.m_strSQLArray.Add(sqlString);
		}
		// now allow the list to be invoked
		m_sqlButton.EnableWindow(TRUE);
	}
	m_strDSN = *m_pOdbc->GetConnectString();
	m_selectSQLDlg.m_strDSN = m_strDSN;
	if(!m_strDSN.IsEmpty()) {
		CStringArray *strArray = &((CDb7App*)AfxGetApp())->m_arrStrDsn;
		strArray->Add(m_strDSN);
		m_dsnCombo.SetCurSel(m_dsnCombo.AddString(m_strDSN));
	}
}

BOOL CConnectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CStringArray *strArray = &((CDb7App*)AfxGetApp())->m_arrStrDsn;
	int hiIndex = strArray->GetUpperBound();
	for(int i = 0; i <= hiIndex; i++) {
		m_dsnCombo.AddString(strArray->GetAt(i));
	}


	CButton *cbSnapshot = (CButton *) GetDlgItem(IDC_RADIOSNAPSHOT);
	CButton *cbDynaset = (CButton *) GetDlgItem(IDC_RADIODYNASET);

	if(m_nOpenType == CRecordset::snapshot) {
		cbDynaset->SetCheck(0);
		cbSnapshot->SetCheck(1);
	}
	else {
		cbDynaset->SetCheck(1);
		cbSnapshot->SetCheck(0);
	}		

	m_dsnCombo.SetWindowText(m_strDSN);
	m_sqlEdit.SetWindowText(m_strSQL);

	if(m_strDSN = m_selectSQLDlg.m_strDSN)
		m_sqlButton.EnableWindow(TRUE);
	else
		m_sqlButton.EnableWindow(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConnectDlg::OnRadiodynaset() 
{
	// TODO: Add your control notification handler code here
	m_nOpenType = CRecordset::dynaset;
}

void CConnectDlg::OnRadiosnapshot() 
{
	// TODO: Add your control notification handler code here
	m_nOpenType = CRecordset::snapshot;
}


void CConnectDlg::OnOK() 
{
	// TODO: Add extra validation here
	m_dsnCombo.GetWindowText(m_strDSN);
	m_sqlEdit.GetWindowText(m_strSQL);
	
	CDialog::OnOK();
}

void CConnectDlg::OnSqldotbutton() 
{
	// TODO: Add your control notification handler code here
	if(IDOK == m_selectSQLDlg.DoModal())
		m_sqlEdit.SetWindowText(m_selectSQLDlg.m_strSQL);
}

void CConnectDlg::OnSelchangeDsncombo() 
{
	// TODO: Add your control notification handler code here

	int pos = m_dsnCombo.GetCurSel();
	if(-1 != pos)
		m_dsnCombo.GetLBText(pos,m_strDSN);

	if(m_strDSN == m_selectSQLDlg.m_strDSN) {
		m_sqlButton.EnableWindow(TRUE);
	}
	else {
		m_sqlButton.EnableWindow(FALSE);
		m_sqlEdit.SetWindowText(_T(""));
	}
}
