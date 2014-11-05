// OpenHTML.cpp : implementation file
//

#include "stdafx.h"
#include "example.h"
#include "OpenHTML.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// OpenHTML dialog


OpenHTML::OpenHTML(CWnd* pParent /*=NULL*/)
	: CDialog(OpenHTML::IDD, pParent)
{
	//{{AFX_DATA_INIT(OpenHTML)
	m_fileName = _T("");
	m_TableNumber = 1;
	//}}AFX_DATA_INIT
}


void OpenHTML::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(OpenHTML)
	DDX_Control(pDX, IDC_BROWSE, m_browse);
	DDX_Text(pDX, IDC_FILE_URL, m_fileName);
	DDX_Text(pDX, IDC_TABLE_NO, m_TableNumber);
	DDV_MinMaxLong(pDX, m_TableNumber, 0, 32767);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(OpenHTML, CDialog)
	//{{AFX_MSG_MAP(OpenHTML)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_FILE, OnFile)
	ON_BN_CLICKED(IDC_URL, OnUrl)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// OpenHTML message handlers

void OpenHTML::OnBrowse() 
{
	UpdateData(TRUE);
	CFileDialog dlg(TRUE, NULL, NULL, 0, _T("HTML files (*.htm, *.html)|*.htm;*.html||"));
	if(dlg.DoModal()==IDOK)
	{
		m_fileName =dlg.GetFileName();
		UpdateData(FALSE);
	}
}

void OpenHTML::OnFile() 
{
	m_File=TRUE;
	m_browse.EnableWindow(TRUE);	
}

void OpenHTML::OnUrl() 
{
	m_File=FALSE;
	m_browse.EnableWindow(FALSE);	
}

int OpenHTML::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	

	
	return 0;
}

BOOL OpenHTML::OnInitDialog() 
{
	CDialog::OnInitDialog();
//	CButton* pWnd=(CButton*)GetDlgItem(IDC_FILE);
//	pWnd->SetCheck(TRUE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void OpenHTML::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	CButton* pWnd1=(CButton*)GetDlgItem(IDC_FILE);	
	CButton* pWnd2=(CButton*)GetDlgItem(IDC_URL);

	if (m_File)
		pWnd1->SetCheck(TRUE);
	else
		pWnd2->SetCheck(TRUE);

	
}
