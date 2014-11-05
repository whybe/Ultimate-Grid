/*************************************************************************
				Class Implementation : CUGProgressType
**************************************************************************
	Source file : UGCTprog.cpp
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
*************************************************************************/

#include "stdafx.h"
#include "UGCtrl.h"
#include "UGCTprog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/***************************************************
CUGProgressType - Constructor
	Intialize all member variables here
****************************************************/
CUGProgressType::CUGProgressType()
{
}
/***************************************************
~CUGProgressType - Destructor
	Free all allocated resources here
****************************************************/
CUGProgressType::~CUGProgressType(){
}

/***************************************************
GetName  - overloaded CUGCellType::GetName
	Returns a readable name for the cell type.
	Returned value is used to help end-users
	to see what cell type are available.

    **See CUGCellType::GetName for more details
	about this function

Params:
	<none>
Return:
	cell type name
****************************************************/
LPCTSTR CUGProgressType::GetName()
{
	return _T("Progress Bar");
}

/***************************************************
GetUGID  - overloaded CUGCellType::GetUGID
	Returns a GUID for the cell type, this number
	is unique for each cell type and never changes.
	This number can be used to find the cell types
	added to this instance of the Ultimate Grid.

    **See CUGCellType::GetUGID for more details
	about this function

Params:
	<none>
Returns:
	UGID (which is actually a GUID)
****************************************************/
LPCUGID CUGProgressType::GetUGID()
{
	static const UGID ugid = 
	{ 0x4585888d, 0xd9eb, 0x11d5, { 0x9b, 0x37, 0x0, 0x50, 0xba, 0xd4, 0x4b, 0xcd } };

	return &ugid;
}

/***************************************************
OnDraw - overloaded CUGCellType::OnDraw
	Draws the progress bar, using the cells text field
	as a percentage, and the cells label field as a
	label

    **See CUGCellType::OnDraw for more details
	about this function
****************************************************/
void CUGProgressType::OnDraw(CDC *dc,RECT *rect,int col,long row,
							CUGCell *cell,int selected,int current)
{

	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(selected);
	UNREFERENCED_PARAMETER(current);

	if (!m_drawThemesSet)
		m_useThemes = cell->UseThemes();

	DrawBorder(dc,rect,rect,cell);

	int  fillpos;
	RECT fillrect;
	int left,top;
	SIZE size;

	CString label;
	int		labelSet = FALSE;
		
	int alignment;
	long percent = 0;

	long		properties = cell->GetPropertyFlags();

	if(properties&UGCELL_STRING_SET)
		percent = (long)cell->GetNumber();


	//get the percent
	if(percent >100)
		percent = 100;
	else if(percent <0)
		percent = 0;

	if(properties&UGCELL_CELLTYPEEX_SET){
		if(cell->GetCellTypeEx() == UGCT_PROGRESSUSELABEL){
			label = cell->GetLabelText();
			labelSet = TRUE;
		}
	}
	if(!labelSet){
		label.Format(_T("%% %ld"),percent);
	}

	//select the font
	if(properties&UGCELL_FONT_SET )
		dc->SelectObject(cell->GetFont());

	//text alignment
	if(properties&UGCELL_ALIGNMENT_SET)
		alignment = cell->GetAlignment();
	else
		alignment = 0;

	if(alignment & UG_ALIGNCENTER){
		GetTextExtentPoint(dc->m_hDC,label,label.GetLength(),&size);
		left = rect->left + (rect->right - rect->left - size.cx) /2;
	}
	else if(alignment & UG_ALIGNRIGHT){
		GetTextExtentPoint(dc->m_hDC,label,label.GetLength(),&size);
		left = rect->right - size.cx - 3;
	}
	else{
		left = rect->left+3;
	}	
	if(alignment & UG_ALIGNVCENTER){
		GetTextExtentPoint(dc->m_hDC,label,label.GetLength(),&size);
		top = rect->top + (rect->bottom - rect->top - size.cy) /2;
	}
	else if(alignment & UG_ALIGNBOTTOM){
		GetTextExtentPoint(dc->m_hDC,label,label.GetLength(),&size);
		top = rect->bottom - size.cy -1;
	}
	else{
		top = rect->top+1;
	}

	CopyRect(&fillrect,rect);

	DrawBackground( dc, &fillrect, cell->GetBackColor(), row, col, cell, current > 0, selected > 0);

	fillrect.top++;
	fillrect.bottom --;

	RECT drawRect = fillrect;
	drawRect.left = left;
	drawRect.top = top;

	UGXPThemes::GetTextExtent(NULL, *dc, XPCellTypeProgressUnselected, UGXPThemes::GetState(selected > 0, current > 0), label, label.GetLength(),
		DT_LEFT, &drawRect, &drawRect);

	//get the first rect
	fillpos = fillrect.left + (int)(((long)(fillrect.right - fillrect.left)*percent)/(long)100);
	fillrect.right = fillpos;
	dc->SetBkColor(cell->GetHBackColor());

	if (!m_useThemes || !UGXPThemes::DrawBackground(NULL, *dc, XPCellTypeProgressSelected, UGXPThemes::GetState(selected > 0, current > 0), &fillrect, NULL))
	{
		DrawBackground( dc, &fillrect, cell->GetHBackColor(), row, col, cell, current > 0, selected > 0);
	}

	if (!m_useThemes || !UGXPThemes::WriteText(NULL, *dc, XPCellTypeProgressSelected, UGXPThemes::GetState(selected > 0, current > 0), label, label.GetLength(), DT_LEFT, &drawRect))
	{
		dc->SetTextColor(cell->GetHTextColor());
		dc->ExtTextOut(left,top,ETO_CLIPPED,&fillrect,label,label.GetLength(),NULL);
	}

	//draw the second half
	if(percent <100)
	{
		fillrect.right = rect->right;
		fillrect.left = fillpos;


		if (!m_useThemes || !UGXPThemes::DrawBackground(NULL, *dc, XPCellTypeProgressUnselected, UGXPThemes::GetState(selected > 0, current > 0), &fillrect, NULL))
		{
			DrawBackground( dc, &fillrect, cell->GetBackColor(), row, col, cell, current>0, selected>0);
		}

		if (!m_useThemes || !UGXPThemes::WriteText(NULL, *dc, XPCellTypeProgressUnselected, UGXPThemes::GetState(selected > 0, current > 0), label, label.GetLength(), DT_RIGHT, &drawRect))
		{
			dc->SetTextColor(cell->GetTextColor());
			dc->ExtTextOut(left,top,ETO_CLIPPED,&fillrect,label,label.GetLength(),NULL);
		}
	}

	return;
}

/****************************************************
GetBestSize
	Returns the best (nominal) size for a cell using
	this cell type, with the given cell properties.
Params:
	dc		- device context to use to calc the size on	
	size	- return the best size in this param
	cell	- pointer to a cell object to use for the calc.
Return:
	<none>
*****************************************************/
void CUGProgressType::GetBestSize(CDC *dc,CSize *size,CUGCell *cell)
{
	long percent;
	CString string;

	// create a string as user sees it in the cell
	if( cell->GetPropertyFlags()&UGCELL_STRING_SET )
		percent = (long)cell->GetNumber();

	//get the percent
	if( percent > 100 )
		percent = 100;
	else if( percent < 0 )
		percent = 0;

	if(cell->GetCellTypeEx() == UGCT_PROGRESSUSELABEL)
		string = cell->GetLabelText();
	else
		string.Format(_T("%% %ld"),percent);

	cell->SetText( string );
	// call the parent class implementation
	CUGCellType::GetBestSize( dc, size, cell );
}