/*************************************************************************
				Class Implementation : CUGSliderType
**************************************************************************
	Source file : UGCTsldr.cpp
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
*************************************************************************/

#include "stdafx.h"
#include "UGCtrl.h"
#include "UGCTsldr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/***************************************************
CUGSliderType - Constructor
	Intialize member variables and class wide resource
****************************************************/
CUGSliderType::CUGSliderType(){
	SetTextEditMode(FALSE);

	m_grayPen.CreatePen(PS_SOLID,1,RGB(200,200,200));
	m_darkGrayPen.CreatePen(PS_SOLID,1,RGB(100,100,100));

	m_updateSlider = FALSE;
}

/***************************************************
~CUGSliderType = Destructor
	Clean up all allocated resources
****************************************************/
CUGSliderType::~CUGSliderType(){
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
LPCTSTR CUGSliderType::GetName()
{
	return _T("Slider Control");
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
LPCUGID CUGSliderType::GetUGID()
{
	static const UGID ugid = 
	{ 0x45858892, 0xd9eb, 0x11d5, { 0x9b, 0x37, 0x0, 0x50, 0xba, 0xd4, 0x4b, 0xcd } };

	return &ugid;
}

/***************************************************
OnLClicked - overloaded CUGCellType::OnLClicked
	Checks to see if the slider has been clicked on.
	If the mouse button is pressed over the slider,
	then the slider is put into a interactive update
	state.
	Once the mouse button is release the interactive
	update state is turned off

    **See CUGCellType::OnLClicked for more details
	about this function
****************************************************/
BOOL CUGSliderType::OnLClicked(int col,long row,int updn,RECT *rect,POINT *point){

	if(updn)
	{
		m_updateSlider = FALSE;
	}

	CUGCell cell;
	m_ctrl->GetCell(col,row,&cell);

	//get the slider percentage
	int percent = 0;
	if(cell.IsPropertySet(UGCELL_STRING_SET))
		percent = _ttol(cell.GetText());
	//get the percent
	if(percent >100)
		percent = 100;
	else if(percent <0)
		percent = 0;

	//find the slider x position
	long width = rect->right - rect->left - 6;
	int xPos = rect->left + 3 + ((width * percent) / 100);

	int mouseX = point->x;

	if(mouseX > xPos- 6 && mouseX < xPos+6)
	{
		m_updateSlider = TRUE;
		return TRUE;
	}	

	return FALSE;
}

/***************************************************
OnMouseMove - overloaded CUGCellType::OnMouseMove
	If the slider update state has been activated
	with during OnLClicked. Then this function tracks
	the position of the mouse and updates the cells
	value according to the mouses position along the
	slider (0-100 percent). As the value changes the
	slider is redrawn.

    **See CUGCellType::OnMouseMove for more details
	about this function
****************************************************/
BOOL CUGSliderType::OnMouseMove(int col,long row,POINT *point,UINT flags){

	if((flags& MK_LBUTTON)== FALSE){
		return FALSE;
	}

	if(m_updateSlider){

		RECT rect;
		m_ctrl->GetCellRect(col,row,&rect);

		long mouseX = point->x - rect.left - 3;

		if(mouseX < 0)
			mouseX = 0;

		long width = rect.right - rect.left - 6;

		long percent = (mouseX*100)/width;

		if(percent < 0)
			percent = 0;
		if(percent > 100)
			percent = 100;

		CUGCell cell;
		m_ctrl->GetCellIndirect(col,row,&cell);

		if ( cell.GetReadOnly() == TRUE )
			return FALSE;

		if(percent != (long)cell.GetNumber())
		{
			cell.SetNumber(percent);
			m_ctrl->SetCell(col,row,&cell);
			m_ctrl->RedrawCell(col,row);

			OnCellTypeNotify(m_ID, col, row, UGCT_SLIDER_MOVED, percent);
		}
		return TRUE;
	}
	return FALSE;
}

/***************************************************
OnDraw - overloaded CUGCellType::OnDraw
	Draw the slider control, with the position of the
	control set by the cell's value/text field. The
	value must be in a range of 0-100.
	
    **See CUGCellType::OnDraw for more details
	about this function
****************************************************/
void CUGSliderType::OnDraw(CDC *dc,RECT *rect,int col,long row,
						   CUGCell *cell,int selected,int current)
{
	if (!m_drawThemesSet)
			m_useThemes = cell->UseThemes();

	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(selected);
	UNREFERENCED_PARAMETER(current);

	DrawBorder(dc,rect,rect,cell);

	long properties = cell->GetPropertyFlags();

	//get the slider percentage
	int percent = 0;
	if(properties&UGCELL_STRING_SET)
		percent = _ttol(cell->GetText());
	//get the percent
	if(percent >100)
		percent = 100;
	else if(percent <0)
		percent = 0;

	//fill in the background
	DrawBackground( dc, rect, cell->GetBackColor());//, cell, false, false);

	//make sure the window is wide enough
	int width = rect->right - rect->left - 6;
	if(width <= 6)
	{
		return;
	}

	//find the slider x position
	int xPos = rect->left + ((width * percent) / 100) +3;

	int yPosMid = rect->top + (rect->bottom - rect->top)/2;
	
	int state = 1;

	if ( selected) state = 4;
	if (current) state = 2;

	// Draw background
	if (!m_useThemes || !UGXPThemes::DrawBackground(NULL, *dc, L"TRACKBAR", 3, state, rect, NULL))
	{
		//draw the slider track
		CPen* pOldPen = dc->SelectObject((CPen*)CPen::FromHandle((HPEN)GetStockObject(BLACK_PEN)));
		dc->MoveTo(rect->left+1,yPosMid-1);
		dc->LineTo(rect->right,yPosMid-1);
		dc->MoveTo(rect->left+1,yPosMid+1);
		dc->LineTo(rect->right,yPosMid+1);
		dc->SelectObject((CPen *)&m_darkGrayPen);
		dc->MoveTo(rect->left+1,yPosMid);
		dc->LineTo(rect->right,yPosMid);
		dc->SelectObject(pOldPen);
	}

	RECT rcSlider;
	rcSlider.left = xPos - 4;
	rcSlider.top = rect->top;
	rcSlider.bottom = rect->bottom;
	rcSlider.right = xPos + 4;

	// TODO: 4 is a down arrow, 5 is an up arrow, add the ability to set this.

	if (!m_useThemes || !UGXPThemes::DrawBackground(NULL, *dc, L"TRACKBAR", 4, state, &rcSlider, NULL))
	{
		//draw the slider
		CPen* pOldPen = dc->SelectObject((CPen*)CPen::FromHandle((HPEN)GetStockObject(BLACK_PEN)));
		dc->MoveTo(xPos+3,rect->top+2);
		dc->LineTo(xPos-2,rect->top+2);
		dc->LineTo(xPos-2,rect->bottom -2);
		dc->LineTo(xPos+3,rect->bottom -2);
		dc->LineTo(xPos+3,rect->top+2);
		dc->SelectObject((CPen*)CPen::FromHandle((HPEN)GetStockObject(WHITE_PEN)));
		dc->MoveTo(xPos+2,rect->top+3);
		dc->LineTo(xPos-1,rect->top+3);
		dc->LineTo(xPos-1,rect->bottom -3);
		dc->SelectObject((CPen *)&m_darkGrayPen);
		dc->LineTo(xPos+2,rect->bottom -3);
		dc->LineTo(xPos+2,rect->top+3);	
		dc->SelectObject((CPen *)&m_grayPen);
		dc->MoveTo(xPos+1,rect->top+4);
		dc->LineTo(xPos,rect->top+4);
		dc->LineTo(xPos,rect->bottom-4);
		dc->LineTo(xPos+1,rect->bottom-4);
		dc->LineTo(xPos+1,rect->top+4);
		dc->SelectObject(pOldPen);
	}
}
