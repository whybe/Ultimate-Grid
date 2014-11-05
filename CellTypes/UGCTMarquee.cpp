/*************************************************************************
				Class Implementation : CUGMarqueeType
**************************************************************************
	Source file : UGCTMarquee.cpp
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
*************************************************************************/

#include "stdafx.h"
#include "UGCtrl.h"
#include "UGCTMarquee.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/***************************************************
CUGMarqueeType - Constructor
	Initialize all member data
****************************************************/
CUGMarqueeType::CUGMarqueeType(){
	m_canOverLap = FALSE;
	m_timerID = 0;
	m_interval = 50;
}

/***************************************************
~CUGMarqueeType - Destructor
	Clean up all allocated resources
****************************************************/
CUGMarqueeType::~CUGMarqueeType(){

	KillTimer(NULL,m_timerID);
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
LPCTSTR CUGMarqueeType::GetName()
{
	return _T("Marquee Text");
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
LPCUGID CUGMarqueeType::GetUGID()
{
	static const UGID ugid = 
	{ 0xb05fa28b, 0xdcaa, 0x11d5, { 0x9b, 0x39, 0x0, 0x50, 0xba, 0xd4, 0x4b, 0xcd } };

	return &ugid;
}

/***************************************************
OnDraw - overloaded CUGCellType::OnDraw
	
    **See CUGCellType::OnDraw for more details
	about this function
****************************************************/
void CUGMarqueeType::OnDraw(CDC *dc,RECT *rect,int col,long row,
							 CUGCell *cell,int selected,int current)
{
	if (!m_drawThemesSet)
			m_useThemes = cell->UseThemes();


	//if the time has not been started yet, then start it
	if(m_timerID == 0)
		StartUp();

	//draw the standard cell border
	DrawBorder(dc,rect,rect,cell);

	int length;
	int position;
	int cellWidth = rect->right - rect->left;

	//get the length of the text
	if(cell->IsPropertySet(UGCELL_FONT_SET) )
		dc->SelectObject(cell->GetFont());
	CSize size = dc->GetOutputTextExtent(cell->GetText());
	length = size.cx + cellWidth;

	//check it drawing position
	position = cell->GetParam();

	//check to see if the position needs to be reset
	if(position >= length){
		position = 0;
		cell->SetParam(0);
		m_ctrl->SetCell(col,row,cell);
	}

	//check the selected and current states
	if(selected || (current && m_ctrl->m_GI->m_currentCellMode&2)){
		dc->SetTextColor(cell->GetHTextColor());
		DrawBackground( dc, rect, cell->GetHBackColor(), row, col, cell, current > 0, selected > 0);
	}
	else{
		dc->SetTextColor(cell->GetTextColor());
		DrawBackground( dc, rect, cell->GetBackColor(), row, col, cell, current > 0, selected > 0);
	}

	// vertical text alignment
	short alignment;
	int top;
	if(cell->IsPropertySet(UGCELL_ALIGNMENT_SET))
		alignment = cell->GetAlignment();
	else
		alignment = 0;

	if(alignment & UG_ALIGNVCENTER)
	{
		top = rect->top + (rect->bottom - rect->top - size.cy) /2;
	}
	else if(alignment & UG_ALIGNBOTTOM)
	{
		top = rect->bottom - size.cy - 1;
	}
	else
	{
		top = rect->top + 1;
	}

	dc->SetBkMode(TRANSPARENT);
	//draw the text in using the default drawing routine
	dc->ExtTextOut(rect->left + (cellWidth - position),top,ETO_CLIPPED,rect,cell->GetText(),NULL);
	dc->SetBkMode(OPAQUE);
}

/***************************************************
SetScrollInterval
	Sets the time interval when the cell will be
	redrawn 1 pixel over
Params
	nMilliSec - interval in milliseconds
Return
	UG_SUCCESS - success
	UG_ERROR - error
****************************************************/
int CUGMarqueeType::SetScrollInterval(long nMilliSec){
	
	if(nMilliSec < 1)
		return UG_ERROR;

	m_interval = nMilliSec;

	if(m_timerID != 0)
		StartUp();

	return UG_SUCCESS;
}

/***************************************************
StartUp
	Starts the timer that is used to redraw all
	visible CUGMarqueeType cells
Params
	none
Return
	none
****************************************************/
void CUGMarqueeType::StartUp(){

	if(m_timerID != 0)
		KillTimer(m_ctrl->m_hWnd,m_timerID);
	m_timerID = SetTimer(m_ctrl->m_hWnd,m_ID,m_interval,TimerProc);

}

/***************************************************
TimerProc
	Timer callback function.
	This function checks for all visible CUGMarqueeType
	cells and updates their drawing positions and marks
	them to be redrawn.
****************************************************/
// v7.2 - update 02 - 64-bit - TimerProc is declared with UINT_PTR as param 3
#if defined(_WIN64)
VOID CALLBACK EXPORT CUGMarqueeType::TimerProc(
			HWND hwnd,         // handle to window
			UINT uMsg,         // WM_TIMER message
			UINT_PTR idEvent,  // timer identifier
			DWORD dwTime       // current system time
			)
#else
VOID CALLBACK EXPORT CUGMarqueeType::TimerProc(
			HWND hwnd,         // handle to window
			UINT uMsg,         // WM_TIMER message
			unsigned int idEvent,  // timer identifier
			DWORD dwTime       // current system time
			)
#endif
{
	UNREFERENCED_PARAMETER(dwTime);
	UNREFERENCED_PARAMETER(uMsg);
	
	CUGCtrl* ctrl = (CUGCtrl*)CWnd::FromHandle(hwnd);
	//check for errors
	if(ctrl == NULL)	
		return;

	//check to see if any CUGMarqueeType cells are visible
	//if so then mark them for redraw
	int leftCol = ctrl->GetLeftCol();
	int rightCol = ctrl->GetRightCol();
	long topRow = ctrl->GetTopRow();
	long bottomRow = ctrl->GetBottomRow();

	CUGCell cell;
	for(long rows = topRow; rows <= bottomRow; rows++){
		for(int cols = leftCol; cols <= rightCol; cols++){
			ctrl->GetCell(cols,rows,&cell);
			if(cell.GetCellType() == (int)idEvent){

				//run other windows messages first

				//update the position for the next time the cell is drawn
				cell.SetParam(cell.GetParam() +1);
				ctrl->SetCell(cols,rows,&cell);
				
				RECT rect;
				ctrl->GetCellRect(cols,rows,&rect);
				ctrl->m_CUGGrid->m_drawHint.AddHint(cols,rows,cols,rows);
				if(ctrl->GetCurrentRow() != rows || ctrl->GetCurrentCol() != cols)
					ctrl->TempDisableFocusRect();
				ctrl->m_CUGGrid->PaintDrawHintsNow(&rect);
			}
		}
	}

}