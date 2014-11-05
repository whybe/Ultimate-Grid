// SQLEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ADO Sample.h"
#include "SQLEditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSQLEditDlg dialog


CSQLEditDlg::CSQLEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSQLEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSQLEditDlg)
	m_szSQLStr = _T("");
	//}}AFX_DATA_INIT
}


void CSQLEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSQLEditDlg)
	DDX_Text(pDX, IDC_SQL_STR, m_szSQLStr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSQLEditDlg, CDialog)
	//{{AFX_MSG_MAP(CSQLEditDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSQLEditDlg message handlers

void CSQLEditDlg::SetSQLStr(CString szSQL)
{
	m_szSQLStr = szSQL;

	if ( GetSafeHwnd() != NULL )
		UpdateData( TRUE );
}

CString CSQLEditDlg::GetSQLStr()
{
	if ( GetSafeHwnd() != NULL )
		UpdateData( FALSE );

	return m_szSQLStr;
}
