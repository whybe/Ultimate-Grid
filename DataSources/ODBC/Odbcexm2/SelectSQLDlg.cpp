// SelectSQLDlg.cpp : implementation file
//

#include "stdafx.h"
#include "db7.h"
#include "SelectSQLDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectSQLDlg dialog


CSelectSQLDlg::CSelectSQLDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectSQLDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectSQLDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSelectSQLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectSQLDlg)
	DDX_Control(pDX, IDC_SQLLIST, m_sqlList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectSQLDlg, CDialog)
	//{{AFX_MSG_MAP(CSelectSQLDlg)
	ON_LBN_SELCHANGE(IDC_SQLLIST, OnSelchangeSqllist)
	ON_LBN_DBLCLK(IDC_SQLLIST, OnDblclkSqllist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectSQLDlg message handlers

BOOL CSelectSQLDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// set up the list box from the array...
	for (int i = 0; i < m_strSQLArray.GetSize(); i++) 
		m_sqlList.AddString(m_strSQLArray[i]);
		


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectSQLDlg::OnSelchangeSqllist() 
{
	// TODO: Add your control notification handler code here
	m_sqlList.GetText(m_sqlList.GetCurSel(), m_strSQL);
	
}

void CSelectSQLDlg::OnDblclkSqllist() 
{
	// TODO: Add your control notification handler code here
	m_sqlList.GetText(m_sqlList.GetCurSel(), m_strSQL);
	EndDialog(IDOK);
}
