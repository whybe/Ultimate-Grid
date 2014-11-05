// MyCUG.cpp : implementation file
//

#include "stdafx.h"
#include "MyCUG.h"

#include "SplitterDoc.h"
#include "SplitterView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyCUG

CMyCUG::CMyCUG()
{
}

CMyCUG::~CMyCUG()
{
	UGXPThemes::CleanUp();
}


BEGIN_MESSAGE_MAP(CMyCUG, CUGCtrl)
	//{{AFX_MSG_MAP(CMyCUG)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyCUG message handlers

void CMyCUG::OnSetup()
{
	const int nCols = 5;
	const long lRows = 5;
	
	CString temp;
	CUGCell	cell;
	
	// create the default font
	m_font.CreatePointFont(85, _T("Arial"));
	SetDefFont(&m_font);

	
	// set up rows and cols
	SetNumberRows(lRows);
	SetNumberCols(nCols);

	SetVScrollMode(1);
	SetHScrollMode(1);

	// fill in cells with data
	CSplitterView* pView = (CSplitterView*) GetParent();
	if (pView != NULL)
	{
		ASSERT_VALID(pView);
		ASSERT_VALID(pView->GetDocument());

		// Add the datasource to the grid.  This data source is shared between
		// all instantiations of this CUGCtrl derived grid object.
		SetDefDataSource(AddDataSource(&pView->GetDocument()->m_memMan));
	}

	// set column headings
	GetCell(0, -1, &cell);
	for (int i = 0; i < nCols; i++)
	{
		temp.Format(_T("%d"), (i + 1));
		cell.SetText(temp);
		SetCell(i, -1, &cell);
	}

	// set row headings
	for (long j = 0; j < lRows; j++)
	{
		temp.Format(_T("%d"), (j + 1));
		cell.SetText(temp);
		SetCell(-1, j, &cell);
	}
}

void CMyCUG::OnDClicked(int col,long row,RECT *rect,POINT *point,int processed)
{
	// On reciept of a double click event begin editing the current
	// cell
	StartEdit();
}

int CMyCUG::OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag)
{
	// If the user didn't cancel the edit call CDocument::UpdateAllViews which inturn
	// calls the OnUpdate function of the CSplitterView class.
	if (!cancelFlag)
	{
		CSplitterView* pParent = (CSplitterView*) GetParent();

		if (pParent != NULL)
			pParent->GetDocument()->UpdateAllViews(NULL, row);
	}
	return TRUE;
}
