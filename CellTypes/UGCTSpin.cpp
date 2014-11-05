/*************************************************************************
				Class Implementation : CUGSpinButtonType
**************************************************************************
	Source file : UGCTSpin.cpp
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
*************************************************************************/

#include "stdafx.h"
#include "UGCtrl.h"
#include "UGCTspin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/***************************************************
CUGSpinButtonType - Constructor
	Initialize member variables
****************************************************/
CUGSpinButtonType::CUGSpinButtonType(){
		
	//set up the variables
	btnWidth = GetSystemMetrics(SM_CXVSCROLL);

	btnTopDown = FALSE;
	btnBottomDown = FALSE;

	pen.CreatePen(PS_SOLID,1,GetSysColor(COLOR_BTNFACE));
	brush.CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
}

/***************************************************
~CUGSpinButtonType - Destructor
	Free all allocated resoruces
****************************************************/
CUGSpinButtonType::~CUGSpinButtonType(){

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
LPCTSTR CUGSpinButtonType::GetName()
{
	return _T("Spin Button");
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
LPCUGID CUGSpinButtonType::GetUGID()
{
	static const UGID ugid = 
	{ 0x45858899, 0xd9eb, 0x11d5, { 0x9b, 0x37, 0x0, 0x50, 0xba, 0xd4, 0x4b, 0xcd } };

	return &ugid;
}

/***************************************************
GetEditArea - overloaded CUGCellType::GetEditArea
	Returns an adjusted rectangle that can be used
	for the editing area, which is the entire cell
	minus the area used for the spin button on the
	righthand side of the cell.

    **See CUGCellType::GetEditArea for more details
	about this function
****************************************************/
int CUGSpinButtonType::GetEditArea(RECT *rect){
	
	rect->right -=(btnWidth+1);

	return TRUE;
}
/***************************************************
OnDClicked - overloaded CUGCellType::OnDClicked
	Calls the OnLClicked function

    **See CUGCellType::OnDClicked for more details
	about this function
****************************************************/
BOOL CUGSpinButtonType::OnDClicked(int col,long row,RECT *rect,POINT *point){
	return OnLClicked(col,row,1,rect,point);
}
/***************************************************
OnLClicked - overloaded CUGCellType::OnLClicked
	Checks to see if the spin button was clicked on.
	If so, then it checks to see if it was the up or down
	spin arrow.
	If the up arrow was clicked then a cell type event
	is fired: UGCT_SPINBUTTONUP
	If the down arrow was clicked then a cell type event
	is fired: UGCT_SPINBUTTONDOWN
	The value within the cell is not modified, this must
	be done during the cell type even. The reason for this
	is to allow the spin control work with any data type
	rather than just numbers.
	
    **See CUGCellType::OnLClicked for more details
	about this function
****************************************************/
BOOL CUGSpinButtonType::OnLClicked(int col,long row,int updn,RECT *rect,POINT *point){
	
	if(updn){
		if(point->x > (rect->right -btnWidth)){

			//copy the droplist button co-ords
			CopyRect(&btnRect,rect);
			btnRect.left = rect->right - btnWidth;
			
			btnCol = col;
			btnRow = row;

			//check to see which button
			if(point->y < (rect->top +(rect->bottom - rect->top)/2)){
				//Top button
				btnTopDown =	TRUE;
				btnBottomDown = FALSE;
				btnTopBottom = 1;
				btnRect.bottom = (rect->top +(rect->bottom - rect->top)/2);

				//notify the user of the list, so it can be modified if needed
				OnCellTypeNotify(m_ID,btnCol,btnRow,UGCT_SPINBUTTONUP,0);
			}
			else{
				//bottom button
				btnBottomDown = TRUE;
				btnTopDown =	FALSE;
				btnTopBottom = 2;
				btnRect.top = (rect->top +(rect->bottom - rect->top)/2);

				//notify the user of the list, so it can be modified if needed
				OnCellTypeNotify(m_ID,btnCol,btnRow,UGCT_SPINBUTTONDOWN,0);
			}
			m_ctrl->RedrawCell(btnCol,btnRow);
			return TRUE;
		}
	}

	else if(btnTopDown || btnBottomDown){		
		btnTopDown =	FALSE;
		btnBottomDown = FALSE;
		btnTopBottom =	0;
		m_ctrl->RedrawCell(col,row);
		return TRUE;
	}

	return FALSE;
}
/***************************************************
OnMouseMove - overloaded CUGCellType::OnMouseMove
	If the mouse button is down, this routine checks
	to see if the mouse was click on an arrow, but
	then was moved off. If so then the pressed/raised
	state of the arrow is changed, and redrawn.

    **See CUGCellType::OnMouseMove for more details
	about this function
****************************************************/
BOOL CUGSpinButtonType::OnMouseMove(int col,long row,POINT *point,UINT flags){

	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);

	if((flags&MK_LBUTTON) == FALSE){
		btnTopDown =	FALSE;
		btnBottomDown = FALSE;
		return FALSE;
	}
	
	if(point->x >= btnRect.left && point->x <= btnRect.right){
		if(point->y >= btnRect.top && point->y <= btnRect.bottom){
			if(btnTopBottom==1 && !btnTopDown){
				btnTopDown = TRUE;
				m_ctrl->RedrawCell(btnCol,btnRow);
			}
			else if(btnTopBottom==2 && !btnBottomDown){
				btnBottomDown = TRUE;
				m_ctrl->RedrawCell(btnCol,btnRow);
			}
		}
		else if(btnTopDown || btnBottomDown){		
			btnTopDown = FALSE;
			btnBottomDown = FALSE;
			m_ctrl->RedrawCell(btnCol,btnRow);
		}
	}
	else if(btnTopDown || btnBottomDown){		
		btnTopDown = FALSE;
		btnBottomDown = FALSE;
		m_ctrl->RedrawCell(btnCol,btnRow);
	}

	return FALSE;
}

/***************************************************
OnDraw - overloaded CUGCellType::OnDraw
	Draws the cells text on the left hand side using 
	the CUGCellType::DrawText function, so that all
	standard text drawing capabilities are available.
	Draws the sort arrows on the right according to
	their current pressed/raised state.

    **See CUGCellType::OnDraw for more details
	about this function
****************************************************/
void CUGSpinButtonType::OnDraw(CDC *dc,RECT *rect,int col,long row,
							  CUGCell *cell,int selected,int current)
{
	if (!m_drawThemesSet)
			m_useThemes = cell->UseThemes();
	
	int style = 0;
	if( cell->IsPropertySet( UGCELL_CELLTYPEEX_SET ) )
		style = cell->GetCellTypeEx();

	float fScale = 1.0;
#ifdef UG_ENABLE_PRINTING
	fScale = m_ctrl->GetUGPrint()->GetPrintVScale(dc);
#endif

	//if the cell is not current and hide button is on
	//then dont draw the button
	if( style & UGCT_SPINBUTTONHIDEBUTTON && !current)
	{
		CUGCellType::OnDraw(dc,rect,col,row,cell,selected,current);
		return;
	}

	DrawBorder(dc,rect,rect,cell);

	int t,x,y;
	RECT rectout;
	CPen * oldpen;
	int left = rect->left;
	int height = rect->bottom - rect->top;

#ifdef UG_ENABLE_PRINTING
	if (dc->IsPrinting())
	{
		rect->left += (int) fScale;
		rect->right -= (int) fScale;
		rect->top += (int) fScale;
		rect->bottom -= (int) fScale;
	}
#endif

	rect->left = rect->right - (int) (fScale * btnWidth);
	
	// The Spin type does not contain themes we can use for selected or current, we use the same for both.
	UGXPThemeState topstate = UGXPThemes::GetState(selected > 0 || current > 0, false);

	//draw the top button
	t = rect->bottom;
	rect->bottom = rect->top + (rect->bottom - rect->top) / 2;
	if(btnTopDown && current){
		cell->SetBorder(UG_BDR_RECESSED);
		DrawBorder(dc,rect,&rectout,cell);
		topstate = ThemeStatePressed;
	}
	else{
		cell->SetBorder(UG_BDR_RAISED);
		DrawBorder(dc,rect,&rectout,cell);
	}

	if (!m_useThemes || !UGXPThemes::DrawBackground(NULL, *dc, XPCellTypeSpinUp, topstate, &rectout, NULL))
	{
		//fill the border in
		dc->SetBkColor(GetSysColor(COLOR_BTNFACE));
		dc->FillRect(&rectout,&brush);

		//draw the down arrow
		if( height >9 ){
			if( dc->IsPrinting() )
			{
	#ifdef UG_ENABLE_PRINTING
				CRgn rgn;

				int	nWidth = rectout.right - rectout.left;
				int	nHeight = rectout.bottom - rectout.top;

				POINT point[] = {
					{rectout.left + nWidth / 2, rectout.top + nHeight / 2 - (int) fScale} ,
					{rectout.left + nWidth / 2 - (int) (2 * fScale), rectout.top + nHeight / 2 + (int) fScale} ,
					{rectout.left + nWidth / 2 + (int) (2 * fScale), rectout.top + nHeight / 2 + (int) fScale}
				};

				rgn.CreatePolygonRgn(point, 3, ALTERNATE);

				CBrush Brush;
				Brush.CreateSolidBrush(RGB(0, 0 , 0));
				dc->FillRgn(&rgn, &Brush);
	#endif
			}
			else {
				x = ((btnWidth-5)/2) + rect->left;
				y = ((rect->bottom - rect->top -3)/2) + rect->top;
				dc->SelectObject((CPen*)CPen::FromHandle((HPEN)GetStockObject(BLACK_PEN)));
				dc->MoveTo(x,y+2);
				dc->LineTo(x+5,y+2);
				dc->MoveTo(x+1,y+1);
				dc->LineTo(x+4,y+1);
				dc->MoveTo(x+2,y);
				dc->LineTo(x+2,y+1);
			}
		}
	}

	//reset the rect
	rect->bottom = t;

	// The Spin type does not contain themes we can use for selected or current, we use the same for both.
	UGXPThemeState bottomstate = UGXPThemes::GetState(selected > 0 || current > 0, false);

	//draw the bottom button
	t = rect->top;
	rect->top = (rect->top +(rect->bottom - rect->top)/2);
	if(btnBottomDown && current){
		cell->SetBorder(UG_BDR_RECESSED);
		DrawBorder(dc,rect,&rectout,cell);
		bottomstate = ThemeStatePressed;
	}
	else{
		cell->SetBorder(UG_BDR_RAISED);
		DrawBorder(dc,rect,&rectout,cell);
	}
	//fill the border in
	dc->SetBkColor(GetSysColor(COLOR_BTNFACE));
	dc->FillRect(&rectout,&brush);

	if (!m_useThemes || !UGXPThemes::DrawBackground(NULL, *dc, XPCellTypeSpinDown, bottomstate, &rectout, NULL))
	{
		//draw the down arrow
		if(height >9){
			if( dc->IsPrinting() )
			{
	#ifdef UG_ENABLE_PRINTING
				CRgn rgn;

				int	nWidth = rectout.right - rectout.left;
				int	nHeight = rectout.bottom - rectout.top;

				POINT point[] = {
					{rectout.left + nWidth / 2 - (int) (2 * fScale), rectout.top + nHeight / 2 - (int) fScale} ,
					{rectout.left + nWidth / 2 + (int) (2 * fScale), rectout.top + nHeight / 2 - (int) fScale} ,
					{rectout.left + nWidth / 2, rectout.top + nHeight / 2 + (int) fScale}
				};

				rgn.CreatePolygonRgn(point, 3, ALTERNATE);

				CBrush Brush;
				Brush.CreateSolidBrush(RGB(0, 0 , 0));
				dc->FillRgn(&rgn, &Brush);
	#endif
			}
			else
			{
				x= ((btnWidth-5)/2) + rect->left;
				y = ((rect->bottom - rect->top -3)/2) + rect->top +1;
				dc->SelectObject((CPen*)CPen::FromHandle((HPEN)GetStockObject(BLACK_PEN)));
				dc->MoveTo(x,y);
				dc->LineTo(x+5,y);
				dc->MoveTo(x+1,y+1);
				dc->LineTo(x+4,y+1);
				dc->MoveTo(x+2,y+2);
				dc->LineTo(x+2,y+1);
			}
		}
	}

	//reset the rect
	rect->top = t;

	
	//make a line to separate the border from the rest ofthe cell
	oldpen = (CPen *)dc->SelectObject((CPen *)&pen);
	dc->MoveTo(rect->left - (int)fScale,rect->top);
	dc->LineTo(rect->left - (int)fScale,rect->bottom);
	dc->SelectObject(oldpen);
	
	//draw the text in using the default drawing routine
	rect->left = left;
	rect->right -= (int) ((btnWidth+1) * fScale);

	DrawText(dc,rect,0,col,row,cell,selected,current);

	return;
}

/****************************************************
GetBestSize
	Returns the best (nominal) size for spin control
	cell type, with the given cell properties.
Params:
	dc		- device context to use to calc the size on	
	size	- return the best size in this param
	cell	- pointer to a cell object to use for the calc.
Return:
	<none>
*****************************************************/
void CUGSpinButtonType::GetBestSize(CDC *dc,CSize *size,CUGCell *cell)
{
	// get the width of the cell's text
	CUGCellType::GetBestSize( dc, size, cell );
	// then add the width of the spin control
	if (!( cell->GetCellTypeEx() & UGCT_SPINBUTTONHIDEBUTTON ))
		size->cx += btnWidth;
}