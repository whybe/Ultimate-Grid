// PPage3.cpp : implementation file
//

#include "stdafx.h"
#include "Ex22.h"
#include "PPage3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPage3 property page

IMPLEMENT_DYNCREATE(CPPage3, CPropertyPage)

CPPage3::CPPage3() : CPropertyPage(CPPage3::IDD)
{
	//{{AFX_DATA_INIT(CPPage3)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPPage3::~CPPage3()
{
}

void CPPage3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPage3)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPPage3, CPropertyPage)
	//{{AFX_MSG_MAP(CPPage3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPage3 message handlers

BOOL CPPage3::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_ctrl.AttachGrid(this,IDC_GRID);
	m_ctrl.AdjustComponentSizes();

	CWnd *pWnd = GetParent()->GetDlgItem( IDHELP );
	pWnd->ShowWindow( FALSE );

	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
