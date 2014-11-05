// DlgGrid.cpp : implementation file
//

#include "stdafx.h"
#include "contextsensitivegrid.h"
#include "DlgGrid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGrid dialog


CDlgGrid::CDlgGrid(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGrid::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgGrid)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgGrid::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGrid)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGrid, CDialog)
	//{{AFX_MSG_MAP(CDlgGrid)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGrid message handlers

BOOL CDlgGrid::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_grid.AttachGrid( this, IDC_GRID );
	m_grid.AdjustComponentSizes();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
