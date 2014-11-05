// Adjust.cpp : implementation file
//

#include "stdafx.h"
#include "Ex13.h"
#include "Adjust.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdjuster dialog


CAdjuster::CAdjuster(int colwidth, int rowheight, int sidewidth, int topheight, CWnd* pParent /*=NULL*/)
	: CDialog(CAdjuster::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAdjuster)
	m_rowheight = rowheight;
	m_colwidth = colwidth;
	m_sidewidth = sidewidth;
	m_topheight = topheight;
	//}}AFX_DATA_INIT
}


void CAdjuster::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdjuster)
	DDX_Text(pDX, IDC_ROW_HEIGHT, m_rowheight);
	DDX_Text(pDX, IDC_COL_WIDTH, m_colwidth);
	DDX_Text(pDX, IDC_SIDE_H_WIDTH, m_sidewidth);
	DDX_Text(pDX, IDC_TOP_H_HEIGHT, m_topheight);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAdjuster, CDialog)
	//{{AFX_MSG_MAP(CAdjuster)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdjuster message handlers
