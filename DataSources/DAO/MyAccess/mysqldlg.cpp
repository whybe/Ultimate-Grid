// MYSQLDLG.cpp : implementation file
//

#include "stdafx.h"
#include "MySQLDlg.h"
#include "MyAccess.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMySQLDlg dialog


CMySQLDlg::CMySQLDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMySQLDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMySQLDlg)
	m_bNumSH = FALSE;
	m_bBase1 = FALSE;
	//}}AFX_DATA_INIT
}


void CMySQLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMySQLDlg)
	DDX_Control(pDX, IDC_COMBO4, m_cbTableName);
	DDX_Control(pDX, IDC_ALLOWEDIT, m_AllowEditCheck);
	DDX_Control(pDX, IDC_GHOST, m_GhostCheck);
	DDX_Control(pDX, IDC_COMBO2, m_cbRecordType);
	DDX_Control(pDX, IDC_COMBO1, m_cbSQL);
	DDX_Check(pDX, IDC_NUMSH, m_bNumSH);
	DDX_Check(pDX, IDC_BASE1, m_bBase1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMySQLDlg, CDialog)
	//{{AFX_MSG_MAP(CMySQLDlg)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_GHOST, OnGhost)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnSelchangeCombo2)
	ON_BN_CLICKED(IDC_ALLOWEDIT, OnAllowedit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMySQLDlg message handlers

int CMySQLDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	
	return 0;
}

BOOL CMySQLDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	TCHAR	buf[255];


	CWnd * pPathWnd = GetDlgItem(IDC_PATH);

	pPathWnd->SetWindowText((LPCTSTR) m_csPath);	// get path into edit

	// 1. init open type
	m_cbRecordType.SetCurSel(0);		// dynaset type in list box
	m_nOpenType = dbOpenDynaset;

	// 2. get the table lists into SQL and TableName
	int count  = m_pData->GetTableDefCount();
	
	m_cbSQL.ResetContent( );
	CDaoTableDefInfo ti;
	for(int loop =0;loop <count;loop++){
		try{
			m_pData->GetTableDefInfo(loop,ti,AFX_DAO_PRIMARY_INFO);
			if(!(ti.m_lAttributes&dbSystemObject)){
				wsprintf(buf,_T("SELECT * FROM [%s]"),ti.m_strName);
				m_cbSQL.AddString(buf);
				wsprintf(buf,_T("[%s]"),ti.m_strName);
				m_cbTableName.AddString(buf);
			}
		}
		catch(CDaoException* e){
			e->ReportError();
			e->Delete();
		}
	}

	m_cbSQL.SetCurSel(0);
	m_cbTableName.SetCurSel(0);


	// 3. set defaults for edit and ghost
	m_bAllowEdit = FALSE;
	m_bUseGhost = FALSE;

	m_AllowEditCheck.SetCheck(0);			// off
	m_GhostCheck.EnableWindow(FALSE);		// grayed?

	// 4. enable SQL and disable TableNames
	m_cbSQL.EnableWindow(TRUE);
	m_cbTableName.EnableWindow(FALSE);

	// ...ok...
	SetCursor(LoadCursor(NULL,IDC_ARROW));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMySQLDlg::SetDatabase(CDaoDatabase* m_pDb) {
	m_pData = m_pDb;
}

LPTSTR	CMySQLDlg::GetSQLString(){
	return (LPTSTR) m_csSQLString.GetBuffer(1);
}

LPTSTR	CMySQLDlg::GetTableName(){
	return (LPTSTR) m_csTableName.GetBuffer(1);
}

INT  CMySQLDlg::GetOpenType() {
	return m_nOpenType;
}

void CMySQLDlg::OnOK() 
{
	// TODO: Add extra validation here
	m_cbSQL.GetWindowText(m_csSQLString);
	m_cbTableName.GetWindowText(m_csTableName);
	
	CDialog::OnOK();
}

void CMySQLDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	
}

void CMySQLDlg::OnGhost() 
{
	if(m_GhostCheck.GetCheck())
		m_bUseGhost = TRUE;
	else 
		m_bUseGhost = FALSE;

}

void CMySQLDlg::OnSelchangeCombo2() 
{
	// selection changed...
	// box is sorted, so 0 = dynaset, 1 = snapshot, 2 = table
	switch(m_cbRecordType.GetCurSel()) {
	case 0:		// dynaset
		m_nOpenType = dbOpenDynaset;
		m_AllowEditCheck.EnableWindow(TRUE);
		m_cbSQL.EnableWindow(TRUE);
		m_cbTableName.EnableWindow(FALSE);
		break;
	case 1:		// snapshot
		m_nOpenType = dbOpenSnapshot;
		m_bAllowEdit = FALSE;
		m_bUseGhost  = FALSE;
		m_GhostCheck.SetCheck(0);
		m_GhostCheck.EnableWindow(FALSE);
		m_AllowEditCheck.SetCheck(0);
		m_AllowEditCheck.EnableWindow(FALSE);
		m_cbSQL.EnableWindow(TRUE);
		m_cbTableName.EnableWindow(FALSE);
		break;
	case 2:
		m_nOpenType = dbOpenTable;
		m_AllowEditCheck.EnableWindow(TRUE);
		m_cbSQL.EnableWindow(FALSE);
		m_cbTableName.EnableWindow(TRUE);
		break;
	default:
		m_nOpenType = dbOpenDynaset;
		m_AllowEditCheck.EnableWindow(TRUE);
		m_cbSQL.EnableWindow(TRUE);
		m_cbTableName.EnableWindow(FALSE);
		break;
	}		
	
}

void CMySQLDlg::OnAllowedit() 
{
	// ok - if checked, set bool and enable ghost...
	if(m_AllowEditCheck.GetCheck()) {
		m_bAllowEdit = TRUE;
		m_GhostCheck.EnableWindow(TRUE);
	}
	else {
		m_bAllowEdit = FALSE;
		m_GhostCheck.EnableWindow(FALSE);
	}


}
