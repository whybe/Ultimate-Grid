// Ex22PSht.cpp : implementation file
//

#include "stdafx.h"
#include "Ex22.h"
#include "Ex22PSht.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx22PSht

IMPLEMENT_DYNAMIC(CEx22PSht, CPropertySheet)

CEx22PSht::CEx22PSht(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CEx22PSht::CEx22PSht(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CEx22PSht::~CEx22PSht()
{
}


BEGIN_MESSAGE_MAP(CEx22PSht, CPropertySheet)
	//{{AFX_MSG_MAP(CEx22PSht)
	ON_WM_CREATE()
	ON_WM_SYSCOMMAND()
	ON_WM_QUERYDRAGICON()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx22PSht message handlers

int CEx22PSht::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CPropertySheet::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	AddPage(&m_page1);
	AddPage(&m_page2);
	AddPage(&m_page3);
	
	return 0;
}

void CEx22PSht::OnSysCommand(UINT nID, LPARAM lParam) 
{
	// TODO: Add your message handler code here and/or call default
	
	CPropertySheet::OnSysCommand(nID, lParam);
}

HCURSOR CEx22PSht::OnQueryDragIcon() 
{
	// TODO: Add your message handler code here and/or call default
	
	return CPropertySheet::OnQueryDragIcon();
}

void CEx22PSht::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CPropertySheet::OnPaint() for painting messages
}
