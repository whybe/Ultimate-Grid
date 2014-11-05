// PPage2.cpp : implementation file
//

#include "stdafx.h"
#include "Ex22.h"
#include "PPage2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPage2 property page

IMPLEMENT_DYNCREATE(CPPage2, CPropertyPage)

CPPage2::CPPage2() : CPropertyPage(CPPage2::IDD)
{
	//{{AFX_DATA_INIT(CPPage2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPPage2::~CPPage2()
{
}

void CPPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPage2)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPPage2, CPropertyPage)
	//{{AFX_MSG_MAP(CPPage2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPage2 message handlers

BOOL CPPage2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_ctrl.AttachGrid(this,IDC_GRID);
	m_font.CreateFont(12,0,0,0,600,0,0,0,0,0,0,0,0,"Courier");
	m_ctrl.SetDefFont(&m_font);

	m_ctrl.AdjustComponentSizes();
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
