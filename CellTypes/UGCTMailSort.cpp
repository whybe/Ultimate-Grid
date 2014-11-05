/*************************************************************************
				Class Implementation : CUGCTMailSort
**************************************************************************
	Source file : UGCTMail.cpp
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
*************************************************************************/

#include "stdafx.h"
#include "UGCtrl.h"
#include "UGCTMailSort.h"

#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
	const int sortByRightMargin = 40;
}
/***************************************************
CUGCTMail - Constructor
	Initialize member variables
****************************************************/
CUGCTMailSort::CUGCTMailSort() : m_whitePen(PS_SOLID, 1, RGB(255, 255, 255)), 
								 m_arrowPen(PS_SOLID, 1, RGB(172, 168, 153))
{
	m_normalFont.CreateFont(14, 0, 0, 0, 500, 0, 0, 0, 0, 0, 0, 0, 0, _T("Arial"));
	m_sortAscending = false;
	m_sortOrder = sortByDate;
}

/***************************************************
~CUGCTMailSort - Destructor
	Clean up all allocated resources
****************************************************/
CUGCTMailSort::~CUGCTMailSort()
{
}

/***************************************************
OnDraw
	The Ultimate Grid calls this visual function
	every time it is drawing a cell.  It is up to
	the individual cell type to properly draw itself.
Params:
	dc		- device context to draw the cell with
	rect	- rectangle to draw the cell in
	col		- column that is being drawn
	row		- row that is being drawn
	cell	- cell that is being drawn
	selected- TRUE if the cell is selected, otherwise FALSE
	current - TRUE if the cell is the current cell, otherwise FALSE
Return
	<none>
****************************************************/
void CUGCTMailSort::OnDraw(CDC *dc,RECT *rect,int col,long row,CUGCell *cell,int selected,int current)
{
	if (!m_drawThemesSet)
		m_useThemes = cell->UseThemes();

	// Draw background
	dc->FillSolidRect(rect, RGB(236, 233, 216));
	int oldBkMode = dc->SetBkMode(TRANSPARENT);

	RECT rcLine = *rect;
	rcLine.top = rcLine.bottom - 3;

	dc->FillSolidRect(&rcLine, RGB(220, 216, 200));

	rcLine.top += 1;
	dc->FillSolidRect(&rcLine, RGB(210, 207, 190));

	rcLine.top += 1;
	rcLine.bottom += 1;
	dc->FillSolidRect(&rcLine, RGB(197, 194, 178));

	CFont * pOldFont = dc->SelectObject(&m_normalFont);

	CString output;

	switch(m_sortOrder)
	{
	case sortByAttachments:
		output = "Arranged By: Attachments";
		break;
	case sortByCategories:
		output = "Arranged By: Categories";
		break;
	case sortByConversation:
		output = "Arranged By: Conversation";
		break;
	case sortByDate:
		output = "Arranged By: Date";
		break;
	case sortByFlag:
		output = "Arranged By: Flag";
		break;
	case sortByFrom:
		output = "Arranged By: From";
		break;
	case sortByImportance:
		output = "Arranged By: Importance";
		break;
	case sortBySize:
		output = "Arranged By: Size";
		break;
	case sortBySubject:
		output = "Arranged By: Subject";
		break;
	case sortByTo:
		output = "Arranged By: To";
		break;
	case sortByType:
		output = "Arranged By: Type";
		break;
	}

	CSize szArrBy = dc->GetTextExtent(output);

	CString sortOrder;

	switch (m_sortOrder)
	{
	case sortByFlag:
		sortOrder =  ((m_sortAscending) ? "Unflagged on top" : "Red on top");
		break;
	case sortByDate:
		sortOrder =  ((m_sortAscending) ? "Oldest on top" : "Newest on top");
		break;
	case sortBySize:
		sortOrder =  ((m_sortAscending) ? "Smallest on top" : "Largest on top");
		break;
	case sortByAttachments:
		sortOrder =  ((m_sortAscending) ? "None on top" : "With on top");
		break;
	default:
		sortOrder =  ((m_sortAscending) ? "Z on top" : "A on top");
		break;
	}

	CSize szSortText = dc->GetTextExtent(sortOrder);

	int divider = rect->right - (szSortText.cx + sortByRightMargin);

	if (divider < szArrBy.cx + 10) divider = szArrBy.cx + 10;
	if (divider > rect->right - rect->left - 15) divider = rect->right - rect->left - 15;	
		

	// Now we have all the info we need to draw this string
	RECT rcLeftText = *rect;
	rcLeftText.right = rect->left + divider;
	rcLeftText.top += 2;
	rcLeftText.left += 2;
	dc->DrawText(output, &rcLeftText, DT_END_ELLIPSIS);

	rcLine.left = divider;
	rcLine.top = rect->top + 2;
	rcLine.right = divider + 1;
	rcLine.bottom = rect->bottom - 4;
	dc->FillSolidRect(&rcLine, RGB(172, 168, 153));

	rcLine.left += 1;
	rcLine.right += 1;
	dc->FillSolidRect(&rcLine, RGB(255, 255, 255));

	rcLine.left += 3;
	rcLine.right =  rect->right - 14; //szSortText.cx;

	rcLine.top = rect->top + 2;

	dc->DrawText(sortOrder, &rcLine, DT_END_ELLIPSIS);

	// Draw arrow

	CPen * pOldPen = dc->SelectObject(&m_whitePen);

	if (m_sortAscending)
	{
		dc->MoveTo(rect->right - 11, rect->top + 12);
		dc->LineTo(rect->right - 4, rect->top + 12);
		dc->LineTo(rect->right - 4, rect->top + 11);
		dc->LineTo(rect->right - 5, rect->top + 11);
		dc->LineTo(rect->right - 5, rect->top + 9);
		dc->LineTo(rect->right - 6, rect->top + 9);
		dc->LineTo(rect->right - 6, rect->top + 7);
		dc->LineTo(rect->right - 7, rect->top + 7);
		dc->LineTo(rect->right - 7, rect->top + 5);
		dc->SelectObject(&m_arrowPen);
		dc->MoveTo(rect->right - 8, rect->top + 6);
		dc->LineTo(rect->right - 8, rect->top + 7);
		dc->LineTo(rect->right - 9, rect->top + 7);
		dc->LineTo(rect->right - 9, rect->top + 9);
		dc->LineTo(rect->right - 10, rect->top + 9);
		dc->LineTo(rect->right - 10, rect->top + 11);
		dc->LineTo(rect->right - 11, rect->top + 11);
		dc->LineTo(rect->right - 11, rect->top + 13);
	}
	else
	{
		dc->MoveTo(rect->right - 5, rect->top + 7);
		dc->LineTo(rect->right - 6, rect->top + 7);
		dc->LineTo(rect->right - 6, rect->top + 9);
		dc->LineTo(rect->right - 7, rect->top + 9);
		dc->LineTo(rect->right - 7, rect->top + 11);
		dc->LineTo(rect->right - 8, rect->top + 11);
		dc->LineTo(rect->right - 8, rect->top + 12);
		dc->LineTo(rect->right - 8, rect->top + 13);
		dc->SelectObject(&m_arrowPen);
		dc->MoveTo(rect->right - 9, rect->top + 12);
		dc->LineTo(rect->right - 9, rect->top + 11);
		dc->LineTo(rect->right - 10, rect->top + 11);
		dc->LineTo(rect->right - 10, rect->top + 9);
		dc->LineTo(rect->right - 11, rect->top + 9);
		dc->LineTo(rect->right - 11, rect->top + 7);
		dc->LineTo(rect->right - 12, rect->top + 7);
		dc->LineTo(rect->right - 12, rect->top + 6);
		dc->LineTo(rect->right - 4, rect->top + 6);
	}


	dc->SelectObject(pOldPen);
	dc->SelectObject(pOldFont);
	dc->SetBkMode(oldBkMode);
}

/***************************************************
OnRClicked - is called whenever a cell of this type
is right clicked.  In this case, we use the built in
notification to send a message to our grid-derived 
class, letting it know if we clicked over the right
most icon, or on the rest of the cell, this then
controls which context menu is shown.
****************************************************/

BOOL CUGCTMailSort::OnRClicked(int col,long row,int updn,RECT *rect,POINT *point)
{
	m_ctrl->OnCellTypeNotify(m_ID, col, row, 0, (LONG_PTR)point);

	return TRUE;
}

/***************************************************
OnLClicked - is called whenever a cell of this type
is left clicked.  We respond to this event by working
out if the cell has been clicked over the right most 
icon, and if so, we change the flag state.
****************************************************/
BOOL CUGCTMailSort::OnLClicked(int col,long row,int updn,RECT *rect,POINT *point)
{
	BOOL retval = FALSE;

	if(updn)
	{
		CDC dc;
		dc.CreateCompatibleDC(NULL);
		CFont * pOldFont = dc.SelectObject(&m_normalFont);

		CString sortOrder((m_sortAscending) ? "Oldest on top" : "Newest on top");
		CSize sz = dc.GetTextExtent(sortOrder);
		dc.SelectObject(pOldFont);

		if (point->x >= rect->right - (sz.cx + sortByRightMargin))
		{
			// We clicked on the sort icon
			m_sortAscending = !m_sortAscending;
			m_ctrl->OnCellTypeNotify(m_ID, col, row, 1, (LONG_PTR)point);
			m_ctrl->Invalidate();
			retval = TRUE;
		}
		else
		{
			m_ctrl->OnCellTypeNotify(m_ID, col, row, 0, (LONG_PTR)point);
		}
	}
	
	return retval;
}
