/*************************************************************************
				Class Implementation : CUGAdvProgressType
**************************************************************************
	Source file : UGCTpro1.cpp
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
*************************************************************************/

#include "stdafx.h"
#include "UGCtrl.h"
#include "UGCTpro1.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/***************************************************
CUGAdvProgressType - Constructor
****************************************************/
CUGAdvProgressType::CUGAdvProgressType(){

	SetTextEditMode(FALSE);
	m_lbuttondown  =	FALSE;
	m_numberSections =	0;
	m_gradlinePercent = 5;
	m_sectionPercent =	NULL;
	m_sectionColor =	NULL;
	m_canAdjust =		TRUE;
	m_direction =		UGCT_PROGRESS_LEFT;
	m_margin =			4;

	SetNumberSections(3);
	SetSectionPercent(0,50);
	SetSectionColor(0,RGB(0,128,0));
	SetSectionPercent(1,90);
	SetSectionColor(1,RGB(200,200,0));
	SetSectionPercent(2,100);
	SetSectionColor(2,RGB(255,0,0));
}

/***************************************************
CUGAdvProgressType - Constructor
****************************************************/
CUGAdvProgressType::CUGAdvProgressType(int adjust, int gridlines, int type){

	// call default constructor
	SetTextEditMode(FALSE);
	m_lbuttondown  =	FALSE;
	m_numberSections =	0;
	m_gradlinePercent = 5;
	m_sectionPercent =	NULL;
	m_sectionColor =	NULL;
	m_canAdjust =		FALSE;
	m_direction =		UGCT_PROGRESS_LEFT;
	m_margin =			4;

	int i;
	
	if (adjust)
		m_canAdjust = TRUE;

	SetGraduationLinePercent(gridlines);

	if (type == UGCT_PROGRESS_ALERT){
			SetNumberSections(3);
			SetSectionPercent(0,50);
			SetSectionColor(0,RGB(0,128,0));
			SetSectionPercent(1,90);
			SetSectionColor(1,RGB(200,200,0));
			SetSectionPercent(2,100);
			SetSectionColor(2,RGB(255,0,0));
	}

	if (type == UGCT_PROGRESS_NORMAL){
		SetNumberSections(1);
		SetSectionPercent(0,100);
		SetSectionColor(0,RGB(0,128,0));
	}

	if (type == UGCT_PROGRESS_RAINBOW){
		SetNumberSections(100);
		for (i=0;i<100;i++){
			SetSectionPercent(i,i+1);
			SetSectionColor(99-i,RGB(255-i, 200-i*2, 20+i));
		}
	}

}

/***************************************************
~CUGAdvProgressType - Destructor
****************************************************/
CUGAdvProgressType::~CUGAdvProgressType(){
	if (m_sectionPercent != NULL){
		delete[] m_sectionPercent;
		delete[] m_sectionColor;
	}
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
LPCTSTR CUGAdvProgressType::GetName()
{
	return _T("Advanced Progress Bar");
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
LPCUGID CUGAdvProgressType::GetUGID()
{
	static const UGID ugid =
	{ 0x4585887f, 0xd9eb, 0x11d5, { 0x9b, 0x37, 0x0, 0x50, 0xba, 0xd4, 0x4b, 0xcd } };

	return &ugid;
}


/***************************************************
OnDraw - overloaded CUGCellType::OnDraw
	Draws the advanced progress bar according to
	it settings.

    **See CUGCellType::OnDraw for more details
	about this function
****************************************************/
void CUGAdvProgressType::OnDraw(CDC *dc,RECT *rect,int col,long row,
								CUGCell *cell, int selected, int current)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(selected);
	UNREFERENCED_PARAMETER(current);

	if (!m_drawThemesSet)
		m_useThemes = cell->UseThemes();

	long percent = 0; 
	int i;
	int lineHeight;
	int  fillpos = 0;
	int  anchor = 0;
	int  moving = 0;
	RECT fillrect, marginrect;
	int left,top;
 	CString string;
	SIZE size;
	short alignment = 0;
	long cellTypeEx = 0;

	long properties = cell->GetPropertyFlags();

	if(properties&UGCELL_TEXT_SET)
		percent = (long)cell->GetNumber();
	if(properties&UGCELL_ALIGNMENT_SET)
		alignment = cell->GetAlignment();
	if(properties&UGCELL_CELLTYPEEX_SET)
		cellTypeEx = cell->GetCellTypeEx();
	
	DrawBorder(dc,rect,rect,cell);

	//get the percent
	if(percent >100)
		percent = 100;
	else if(percent <0)
		percent = 0;

	if(cellTypeEx&UGCT_PROGRESS_ALERT)
 		string = cell->GetLabelText();
	else
		string.Format(_T("%% %ld"),percent);

	//text alignment
	if(alignment & UG_ALIGNCENTER){
		GetTextExtentPoint(dc->m_hDC,string,string.GetLength(),&size);
		left = rect->left + (rect->right - rect->left - size.cx) /2;
	}
	else if(alignment & UG_ALIGNRIGHT){
		GetTextExtentPoint(dc->m_hDC,string,string.GetLength(),&size);
		left = rect->right - size.cx - 3;
	}
	else{
		left = rect->left+3;
	}	
	if(alignment & UG_ALIGNVCENTER){
		GetTextExtentPoint(dc->m_hDC,string,string.GetLength(),&size);
		top = rect->top + (rect->bottom - rect->top - size.cy) /2;
	}
	else if(alignment & UG_ALIGNBOTTOM){
		GetTextExtentPoint(dc->m_hDC,string,string.GetLength(),&size);
		top = rect->bottom - size.cy -1;
	}
	else{
		top = rect->top+1;
	}

	//get the first rect
	CopyRect(&fillrect,rect);
	
	// get anchor positions for future calculations

	switch(m_direction){
		case UGCT_PROGRESS_LEFT:
			anchor = fillrect.left;
			moving = fillrect.right;
			fillrect.top += m_margin;
			fillrect.bottom -= m_margin;
			break;
		case UGCT_PROGRESS_TOP:
			anchor = fillrect.top;
			moving = fillrect.bottom;
			fillrect.left += m_margin;
			fillrect.right -= m_margin;
			break;
		case UGCT_PROGRESS_RIGHT:
			anchor = fillrect.right;
			moving = fillrect.left;
			fillrect.top += m_margin;
			fillrect.bottom -= m_margin;
			break;
		case UGCT_PROGRESS_BOTTOM:
			anchor = fillrect.bottom;
			moving = fillrect.top;
			fillrect.left += m_margin;
			fillrect.right -= m_margin;
			break;
	}

	for (i=0;i<m_numberSections;i++){

		fillpos = anchor + ((long)(moving - anchor) * min(m_sectionPercent[i],percent))/100;

		switch(m_direction){
			case UGCT_PROGRESS_LEFT:
				fillrect.right = fillpos;
				break;
			case UGCT_PROGRESS_TOP:
				fillrect.bottom = fillpos;
				break;
			case UGCT_PROGRESS_RIGHT:
				fillrect.left = fillpos;
				break;
			case UGCT_PROGRESS_BOTTOM:
				fillrect.top = fillpos;
				break;
		}

		dc->SetTextColor(cell->GetHTextColor());
		DrawBackground( dc, &fillrect, m_sectionColor[i]);

		dc->ExtTextOut(left,top,ETO_CLIPPED,&fillrect,string,NULL);

		switch(m_direction){
			case UGCT_PROGRESS_LEFT:
				fillrect.left = fillrect.right;
				break;
			case UGCT_PROGRESS_TOP:
				fillrect.top = fillrect.bottom;
				break;
			case UGCT_PROGRESS_RIGHT:
				fillrect.right = fillrect.left;
				break;
			case UGCT_PROGRESS_BOTTOM:
				fillrect.bottom = fillrect.top;
				break;
		}
	}
			
	//draw the second half
	if(percent <100){

		switch(m_direction){
			case UGCT_PROGRESS_LEFT:
				fillrect.right = rect->right;
				fillrect.left = fillpos;
				break;
			case UGCT_PROGRESS_TOP:
				fillrect.bottom = rect->bottom;
				fillrect.top = fillpos;
				break;
			case UGCT_PROGRESS_RIGHT:
				fillrect.left = rect->left;
				fillrect.right = fillpos;
				break;
			case UGCT_PROGRESS_BOTTOM:
				fillrect.top = rect->top;
				fillrect.bottom = fillpos;
				break;
		}

		dc->SetTextColor(cell->GetTextColor());
		DrawBackground( dc, &fillrect, cell->GetBackColor(), row, col, cell);
		dc->ExtTextOut(left,top,ETO_CLIPPED,&fillrect,string,NULL);
	}
	if(m_margin > 0){
		dc->SetTextColor(cell->GetTextColor());

		switch(m_direction){
			case UGCT_PROGRESS_LEFT:
			case UGCT_PROGRESS_RIGHT:
				CopyRect(&marginrect,rect);
				marginrect.bottom = marginrect.top+m_margin;
				DrawBackground( dc, &marginrect, cell->GetBackColor());

				CopyRect(&marginrect,rect);
				marginrect.top = marginrect.bottom-m_margin;
				DrawBackground( dc, &marginrect, cell->GetBackColor());
				break;
			case UGCT_PROGRESS_TOP:
			case UGCT_PROGRESS_BOTTOM:
				CopyRect(&marginrect,rect);
				marginrect.right = marginrect.left+m_margin;
				DrawBackground( dc, &marginrect, cell->GetBackColor());

				CopyRect(&marginrect,rect);
				marginrect.left = marginrect.right-m_margin;
				DrawBackground( dc, &marginrect, cell->GetBackColor());
				break;
		}
	}

	if (m_gradlinePercent>0 && (m_direction == UGCT_PROGRESS_LEFT || m_direction == UGCT_PROGRESS_RIGHT)){
		for (i=0; i<100; i+=m_gradlinePercent){
			if (m_gradlinePercent == 5){
				fillpos = anchor + ((long)(moving - anchor)*i/100);
				dc->MoveTo(fillpos, fillrect.bottom);
				
				if ((i % 25) ==0){
					lineHeight = (fillrect.bottom-fillrect.top)/3;
					dc->MoveTo(fillpos, fillrect.bottom);
					dc->LineTo(fillpos, fillrect.bottom -lineHeight);
					dc->MoveTo(fillpos+1, fillrect.bottom);
					dc->LineTo(fillpos+1, fillrect.bottom -lineHeight);
		
				}
				else if ((i % 50) ==0){
					lineHeight = (fillrect.bottom-fillrect.top)/2;
					dc->MoveTo(fillpos-1, fillrect.bottom);
					dc->LineTo(fillpos-1, fillrect.bottom -lineHeight);
					dc->MoveTo(fillpos, fillrect.bottom);
					dc->LineTo(fillpos, fillrect.bottom -lineHeight);
					dc->MoveTo(fillpos+1, fillrect.bottom);
					dc->LineTo(fillpos+1, fillrect.bottom -lineHeight);
				}
				else{
					lineHeight = (fillrect.bottom-fillrect.top)/4;
					dc->MoveTo(fillpos, fillrect.bottom);
					dc->LineTo(fillpos, fillrect.bottom -lineHeight);
				}
			} 
			else {
				lineHeight = (fillrect.bottom-fillrect.top)/4;
				dc->MoveTo(fillpos, fillrect.bottom);
				dc->LineTo(fillpos, fillrect.bottom -lineHeight);
			}
		}
	}
}

/***************************************************
OnMouseMove - overloaded CUGCellType::OnMouseMove
	Allows the progress bars value to be set interactivly
	if SetCanAdjust() is set to TRUE.

    **See CUGCellType::OnMouseMove for more details
	about this function
****************************************************/
BOOL CUGAdvProgressType::OnMouseMove(int col,long row,POINT *point,UINT flags){

	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);

	if((flags&MK_LBUTTON) == FALSE)
		return FALSE;

	if (!m_canAdjust)
		return FALSE;

	int ref = 0, span = 0;
	float ftemp;
	CUGCell mycell;

	if (point->x>m_rect.right) 
		point->x = m_rect.right;
	if (point->x<m_rect.left)  
		point->x = m_rect.left;
	if (point->y>m_rect.bottom) 
		point->y = m_rect.bottom;
	if (point->y<m_rect.top) 
		point->y = m_rect.top;

	m_ctrl->GetCell(m_col, m_row, &mycell);


	switch(m_direction){

		case UGCT_PROGRESS_LEFT:
			ref = point->x - m_rect.left;
			span = m_rect.right - m_rect.left; 
			break;
		case UGCT_PROGRESS_TOP:
			ref = point->y - m_rect.top;
			span = m_rect.bottom - m_rect.top; 
			break;
		case UGCT_PROGRESS_RIGHT:
			ref = point->x - m_rect.right;
			span = m_rect.left - m_rect.right; 
			break;
		case UGCT_PROGRESS_BOTTOM:
			ref = point->y - m_rect.bottom;
			span = m_rect.top - m_rect.bottom; 
			break;
	}
	
	ftemp = ((float)ref / (float)span) * 100;
	

	if((flags&MK_LBUTTON)){
		// we are resizing the progress bar
		// find the new mouse position, and change the percent value in the
		// cell to reflect the mouse position
	
		mycell.SetNumber(ftemp);
		m_ctrl->SetCell(m_col, m_row, &mycell);
		m_ctrl->RedrawCell(m_col, m_row);

	} else {
		// we just moving over the resize area, not changing the progress bar
		// if the mouse pointer moves within 5 pixels of the current progress bar setting
		// then we should change the mouse pointer to double resize arrows.

		if (abs((int)ftemp - (int)mycell.GetNumber()) < 5){
			if (m_direction == UGCT_PROGRESS_TOP || m_direction == UGCT_PROGRESS_BOTTOM){
				// change the mouse pointer to double arrows left and right
			} else {
				// change the mouse pointer to double up and down arrows
			}
		}else{
		}
			// change mouse pointer to normal


	}
	return TRUE;
}

/***************************************************
OnLClicked - overloaded CUGCellType::OnLClicked
	Allows the progress bars value to be set interactivly
	if SetCanAdjust() is set to TRUE.

    **See CUGCellType::OnLClicked for more details
	about this function
****************************************************/
BOOL CUGAdvProgressType::OnLClicked(int col, long row, int updn, RECT *rect, POINT *point){
	if (!m_canAdjust)
		return UG_SUCCESS;

	int ref = 0, span = 0;
	CUGCell mycell;
	float ftemp;
	if (updn==1){
		m_ctrl->GetCell(col, row, &mycell);

		switch(m_direction){
		case UGCT_PROGRESS_LEFT:
			ref = point->x - rect->left;
			span = rect->right - rect->left; 
			break;
		case UGCT_PROGRESS_TOP:
			ref = point->y - rect->top;
			span = rect->bottom - rect->top; 
			break;
		case UGCT_PROGRESS_RIGHT:
			ref = point->x - rect->right;
			span = rect->left - rect->right; 
			break;
		case UGCT_PROGRESS_BOTTOM:
			ref = point->y - rect->bottom;
			span = rect->top - rect->bottom; 
			break;
		}
		ftemp = ((float)ref / (float)span) * 100;
		if (ftemp>98)
				ftemp=(float)100;
		if (ftemp<2)
				ftemp=(float)0;

		mycell.SetNumber(ftemp);
		m_ctrl->SetCell(col, row, &mycell);

		m_lbuttondown = TRUE;
		m_row = row;
		m_col = col;
		CopyRect(&m_rect,rect);
		m_ctrl->RedrawCell(col, row);

		return TRUE;
	} else {
		// the mouse button was released
		m_lbuttondown = FALSE;

	}

	return FALSE;
}

/***************************************************
OnDClicked - overloaded CUGCellType::OnDClicked
	Allows the progress bars value to be set interactivly
	if SetCanAdjust() is set to TRUE.
	Calls from this function are just passed over to
	the OnLClicked function, therefore double clicks
	are processed the same as a single left click.

    **See CUGCellType::OnDClicked for more details
	about this function
****************************************************/
BOOL CUGAdvProgressType::OnDClicked(int col,long row,RECT *rect,POINT *point){
	return OnLClicked(col, row, TRUE, rect, point);
}

/***************************************************
CalcPointFromValue - reserved for future use
Params
Return
	UG_SUCCESS - success
	UG_ERROR - failure
****************************************************/
int CUGAdvProgressType::CalcPointFromValue (int percent, POINT *point){

	UNREFERENCED_PARAMETER(percent);
	UNREFERENCED_PARAMETER(point);

	return UG_SUCCESS;
}		

/*****************************************************
SetNumberSections
	This functions sets the number of divisions within the 
	progress bar area.  Progress bars can be all one color,
	or may be divided into different colored regions to 
	handle different situations.  

	You may wish to use a progress bar with 3 areas, green
	for the safe zone, yellow for the warning zone, and red
	for the danger zone.

	When you call SetNumberSections, it will automatically
	assign default colors and percentage markers to the
	progress bar.  If you wish to change the defaults 
	(which you probably will), then you will need to call
	SetSectionPercent(), and SetSectionColor();
Params
	sections - number of sections that the bar is made of
		the default value is 3
Return
	UG_SUCCESS - success
	UG_ERROR - failure
*******************************************************/
int CUGAdvProgressType::SetNumberSections(int sections){

	if (sections<0 || sections>100)
		return UG_ERROR;

	int i;

	m_numberSections = sections;

	// if the lists already exists, delete
	if (m_sectionPercent != NULL){
		delete[] m_sectionPercent;
		delete[] m_sectionColor;
	}

	// create new lists for section data
	m_sectionPercent = new int[sections];
	m_sectionColor   = new COLORREF[sections];

	// assign default values
	for (i=0;i<=sections;i++){

		SetSectionColor(i,RGB(255 - (200/sections) * i,0,0));
		SetSectionPercent(i, (100/sections * i));
	}
	return UG_SUCCESS;
}
		 
/*****************************************************
SetSectionPercent
	This function is called after SetNumberSections()

	This function allows you to set the percentage at which
	the progress bar color will change.  The region that
	will be colored will defined by the number you pass this
	function, up to the value assigned to the next highest
	section.

	For example if you set section 1 to 50, and section 2
	to 80, you would have a progress bar with 3 regions,
	0 to 50, 50 to 80, and 80 to 100.  You cannot set
	the percent for section 0, as it is always 0 which is
	the beginning position of the progress bar.
Params
	section (0 based index of the section to set)
	percent percentage of the bar that the section occupies
Return
	UG_SUCCESS - success
	UG_ERROR - failure
*******************************************************/

int CUGAdvProgressType::SetSectionPercent(int section, int percent){
	if (percent<0 || percent >100)
		return UG_ERROR;

	if (section < 0 || section >= m_numberSections)
		return UG_ERROR;
	if (section>0)
		if (m_sectionPercent[section-1]+1 > percent)
			return UG_ERROR;

	m_sectionPercent[section] = percent;
	// assign the percent here
	return UG_SUCCESS;
}

/*****************************************************
SetSectionColor
	This function is called after SetNumberSections()
	This function allows you to set the color of a given 
	Section. 
	You may wish to color the first section green, the
	second section yellow, and the final section red,
	for example to illustrate safety, warning and danger
	levels.
Params
	section (0 based index of the section to set)
	color - RGB value to use for the given section
Return
	UG_SUCCESS - success
	UG_ERROR - failure
*******************************************************/

int CUGAdvProgressType::SetSectionColor(int section, COLORREF color){

	if (section < 0 || section >= m_numberSections)
		return 1;

	// assign section color to appropriate section
	m_sectionColor[section] = color;
	return UG_SUCCESS;
}

/*****************************************************
SetGraduationLinePercent
	This function allows you to change the interval of the
	graduation lines in the progress bar.  Graduation lines
	are the "ruler" type markings that can optionally appear
	in a progress bar.

	A good standard default is 5%.  If 5% is chosen, markings 
	at 25% and 50% will be emphasized automatically, if you
	choose another percentage, no emphasis will appear.

	You can disable the graduation lines entirely by passing
	a value of 0;
Params
	percent - distance between tickmarks as a percentage
Return
	UG_SUCCESS - success
	UG_ERROR - failure
*******************************************************/

int CUGAdvProgressType::SetGraduationLinePercent(int percent){
	if (percent<0 || percent >100)
		return 1;

	m_gradlinePercent = percent;
	return UG_SUCCESS;
}

/***************************************************
SetCanAdjust
	If set to TRUE, then the progress bars value 
	can be set interactivly, using the mouse.
	This interaction is off by default.
Params
	adjust - TRUE to allow interactive value adjustment,
		otherwise FALSE
Return
	UG_SUCCESS - success
	UG_ERROR - failure
****************************************************/
int CUGAdvProgressType::SetCanAdjust(BOOL adjust){
	
	if (adjust)
		m_canAdjust = TRUE;
	else
		m_canAdjust = FALSE;

	return UG_SUCCESS;
}

/***************************************************
SetDirection
	Sets the orientation of the progressbar.
Params
	direction - direction can be any one of these values:
		UGCT_PROGRESS_TOP - start from the top to the bottom
		UGCT_PROGRESS_LEFT - start from the left to the right
		UGCT_PROGRESS_RIGHT - start from the right to the left
		UGCT_PROGRESS_BOTTOM - start from the bottom to the top
Return
	UG_SUCCESS - success
	UG_ERROR - failure
****************************************************/
int CUGAdvProgressType::SetDirection(int direction){

	// bounds checking
	if (direction != UGCT_PROGRESS_TOP)
		if (direction != UGCT_PROGRESS_LEFT)
			if (direction != UGCT_PROGRESS_RIGHT)
				if (direction != UGCT_PROGRESS_BOTTOM)
					return 1;

	m_direction = direction;
	return UG_SUCCESS;
}

/***************************************************
SetMargin
	The progress bar will take up the entire cell area
	besides the area set aside for the margine. The
	margin is in pixels and their is only one value
	for all sides.
Params
	margin - margin in pixels
Return
	UG_SUCCESS - success
	UG_ERROR - failure
****************************************************/
int CUGAdvProgressType::SetMargin(int margin){
	m_margin = margin;
	return UG_SUCCESS;
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
void CUGAdvProgressType::GetBestSize(CDC *dc,CSize *size,CUGCell *cell)
{
	CString string;
	// create the string that use sees in the cell
	if( cell->GetCellTypeEx()&UGCT_PROGRESS_ALERT )
 		string = cell->GetLabelText();
	else if( cell->GetPropertyFlags() & UGCELL_TEXT_SET )
	{
		long percent = (long)cell->GetNumber();

		if ( percent > 100 )
			percent = 100;
		else if ( percent < 0 )
			percent = 0;

		string.Format(_T("%% %ld"), percent );
	}
	cell->SetText( string );

	// call the parent class implementation
	CUGCellType::GetBestSize( dc, size, cell);
}