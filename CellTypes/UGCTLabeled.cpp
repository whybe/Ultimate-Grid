/*************************************************************************
				Class Implementation : CUGLabeledType
**************************************************************************
	Source file : UGCTLabeled.cpp
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
*************************************************************************/

#include "stdafx.h"
#include "UGCtrl.h"
#include "UGCTLabeled.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/***************************************************
CUGLabeledType - Constructor
	Initialize all member data
****************************************************/
CUGLabeledType::CUGLabeledType(){
	
	m_canOverLap = FALSE;

	SetLabelFont(12,300,_T("Arial"),RGB(0,0,0));
}

/***************************************************
~CUGLabeledType - Destructor
	Clean up all allocated resources
****************************************************/
CUGLabeledType::~CUGLabeledType(){
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
LPCTSTR CUGLabeledType::GetName()
{
	return _T("Labeled");
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
LPCUGID CUGLabeledType::GetUGID()
{
	static const UGID ugid = 
	{ 0x10f07b47, 0xdcde, 0x11d5, { 0x9b, 0x3a, 0x0, 0x50, 0xba, 0xd4, 0x4b, 0xcd } };

	return &ugid;
}

/***************************************************
GetEditArea - overloaded CUGCellType::GetEditArea

	**See CUGCellType::GetEditArea for more details
	about this function
****************************************************/
int CUGLabeledType::GetEditArea(RECT *rect){

	rect->top += m_fontHeight;

	if(m_ctrl->m_editInProgress)
		m_ctrl->RedrawCell(m_ctrl->m_editCol,m_ctrl->m_editRow);

	return UG_SUCCESS;
}

/***************************************************
OnDraw - overloaded CUGCellType::OnDraw
	This function will adjust the font size used for
	drawing the text for the given cell based on the
	length of the text, in an attempt to display the
	entire text string

    **See CUGCellType::OnDraw for more details
	about this function
****************************************************/
void CUGLabeledType::OnDraw(CDC *dc,RECT *rect,int col,long row,
							 CUGCell *cell,int selected,int current)
{
	if (!m_drawThemesSet)
		m_useThemes = cell->UseThemes();


	//draw the cells border using the default drawing routine
	DrawBorder(dc,rect,rect,cell);

	CRect tempRect(rect);
	tempRect.bottom = tempRect.top + m_fontHeight;

	//check the selected and current states
	if(selected || (current && m_ctrl->m_GI->m_currentCellMode&2))
		DrawBackground( dc, rect, cell->GetHBackColor(), row, col, cell, current > 0, selected > 0);
	else
		DrawBackground( dc, rect, cell->GetBackColor(), row, col, cell, current > 0, selected > 0);

	if (UGXPThemes::IsThemed())
	{
		dc->SetBkMode(TRANSPARENT);
	}
	// Draw the label text
	dc->SetTextColor(m_labelColor);
	CFont* oldFont = dc->SelectObject(&m_labelFont);
	dc->ExtTextOut(tempRect.left,tempRect.top,ETO_CLIPPED,tempRect,cell->GetLabelText(),NULL);
	dc->SelectObject(oldFont);

	//check the selected and current states
	if(selected || (current && m_ctrl->m_GI->m_currentCellMode&2))
		dc->SetTextColor(cell->GetHTextColor());
	else
		dc->SetTextColor(cell->GetTextColor());

	tempRect.CopyRect(rect);
	tempRect.top += m_fontHeight;
	//draw the text in using the default drawing routine
	DrawText(dc,tempRect,0,col,row,cell,selected,current);

	dc->SetBkMode(OPAQUE);
}

/***************************************************
SetLabelFont
	Sets up the font that will be used to draw the
	cells label
Params
	height - height of the font in pixels
	weight - weight of the font (0-1000)
	name   - typeface name of the font
	color  - color of the font
Return
	UG_SUCCESS - success
	UG_ERROR - error
****************************************************/
int CUGLabeledType::SetLabelFont(int height,int weight,LPCTSTR name,COLORREF color){

	m_fontHeight = height;
	m_labelColor = color;

	if(m_labelFont.GetSafeHandle() != NULL)
		m_labelFont.DeleteObject();

	if(m_labelFont.CreateFont(m_fontHeight,0,0,0,weight,0,0,0,0,0,0,0,0,name) != 0)
		return UG_SUCCESS;
	return UG_ERROR;
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
void CUGLabeledType::GetBestSize(CDC *dc,CSize *size,CUGCell *cell)
{
	// get the size required by the main text
	CUGCellType::GetBestSize( dc, size, cell );
	// calculate the width required by the label text
	CRect rect(0,0,0,0);
	CFont* oldFont = dc->SelectObject(&m_labelFont);
	dc->DrawText( cell->GetLabelText(), rect, DT_CALCRECT|DT_SINGLELINE );
	dc->SelectObject(oldFont);
	
	if ( size->cx < rect.Width())
		size->cx = rect.Width();
}