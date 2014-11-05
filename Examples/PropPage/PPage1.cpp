// PPage1.cpp : implementation file
//

#include "stdafx.h"
#include "Ex22.h"
#include "PPage1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPage1 property page

IMPLEMENT_DYNCREATE(CPPage1, CPropertyPage)

CPPage1::CPPage1() : CPropertyPage(CPPage1::IDD)
{
	//{{AFX_DATA_INIT(CPPage1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPPage1::~CPPage1()
{
}

void CPPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPage1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPPage1, CPropertyPage)
	//{{AFX_MSG_MAP(CPPage1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPage1 message handlers

BOOL CPPage1::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ctrl.AttachGrid(this,IDC_GRID);
	m_ctrl.AdjustComponentSizes();

	// Hide the help button of the pro sheet
	CWnd *pWnd = GetParent()->GetDlgItem( IDHELP );
	pWnd->ShowWindow( FALSE );

	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
