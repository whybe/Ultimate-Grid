// SelectionList.cpp : implementation file
//

#include "stdafx.h"
#include "Multiselect Example.h"
#include "SelectionList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectionList

IMPLEMENT_DYNCREATE(CSelectionList, CListView)

CSelectionList::CSelectionList()
{
}

CSelectionList::~CSelectionList()
{
}


BEGIN_MESSAGE_MAP(CSelectionList, CListView)
	//{{AFX_MSG_MAP(CSelectionList)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectionList drawing

void CSelectionList::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CSelectionList diagnostics

#ifdef _DEBUG
void CSelectionList::AssertValid() const
{
	CListView::AssertValid();
}

void CSelectionList::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSelectionList message handlers

int CSelectionList::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	lpCreateStruct->style = LVS_REPORT;

	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
/*	CListCtrl &tempList = GetListCtrl ();

	tempList.InsertColumn ( 0, "Some text" );
	tempList.SetColumnWidth ( 0, 350 );
*/
	return 0;
}
