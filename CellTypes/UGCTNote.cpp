/*************************************************************************
				Class Implementation : CUGNoteType
**************************************************************************
	Source file : UGCTNote.cpp
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
*************************************************************************/

#include "stdafx.h"
#include "UGCtrl.h"
#include "UGCTNote.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/***************************************************
CUGNoteType - Constructor
	Initialize all member data
****************************************************/
CUGNoteType::CUGNoteType(){

	m_canOverLap = FALSE;
	m_bInit = FALSE;
	m_timerID = 0;

	m_nNoteWidth = 150;
	m_nNoteHeight = 130;
}

/***************************************************
~CUGNoteType - Destructor
	Clean up all allocated resources
****************************************************/
CUGNoteType::~CUGNoteType(){

	if(m_timerID != 0)
		KillTimer(m_ctrl->m_hWnd,m_timerID);
}

/***************************************************
SetNoteSize
	Sets the width and height of the note popup
	window
Params
	width - width in pixels
	height - height in pixels
Return
	UG_SUCCESS - succes
	UG_ERROR - failure
****************************************************/
int CUGNoteType::SetNoteSize(int width, int height){

	if(width < 1 || height < 1)
		return UG_ERROR;

	m_nNoteWidth = width;
	m_nNoteHeight = height;

	return UG_SUCCESS;
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
LPCTSTR CUGNoteType::GetName()
{
	return _T("Note");
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
LPCUGID CUGNoteType::GetUGID()
{
	static const UGID ugid = 
	{ 0x5b379535, 0xdcbf, 0x11d5, { 0x9b, 0x39, 0x0, 0x50, 0xba, 0xd4, 0x4b, 0xcd } };

	return &ugid;
}

/***************************************************
OnSetFocus - overloaded CUGCellType::OnSetFocus
	
    **See CUGCellType::OnSetFocus for more details
	about this function
****************************************************/
void CUGNoteType::OnSetFocus(int col,long row,CUGCell *cell)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(cell);
}

/***************************************************
OnKillFocus - overloaded CUGCellType::OnKillFocus
	
    **See CUGCellType::OnKillFocus for more details
	about this function
****************************************************/
void CUGNoteType::OnKillFocus(int col,long row,CUGCell *cell){

	UNREFERENCED_PARAMETER(cell);

	if(m_timerID != 0){
		KillTimer(m_noteWnd.m_hWnd,m_timerID);
		m_timerID = 0;
		m_noteWnd.ShowWindow(SW_HIDE);
		m_ctrl->RedrawCell(col,row);
	}
}

/***************************************************
OnLClicked - overloaded CUGCellType::OnLClicked
	
	Return TRUE here, so that All mouse move messages
	are sent to this control while the mouse button is down

    **See CUGCellType::OnLClicked for more details
	about this function
****************************************************/
BOOL CUGNoteType::OnLClicked(int col,long row,int updn,RECT *rect,POINT *point){

	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(updn);
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(point);

	return FALSE;
}

/***************************************************
OnMouseMove - overloaded CUGCellType::OnMouseMove
	
    **See CUGCellType::OnMouseMove for more details
	about this function
****************************************************/
BOOL CUGNoteType::OnMouseMove(int col,long row,POINT *point,UINT nFlags){

	UNREFERENCED_PARAMETER(nFlags);
	
	RECT rect;
	m_ctrl->GetCellRect(col,row,&rect);

	if(point->x > rect.left && point->x < rect.right && point->y > rect.top && point->y < rect.bottom){
		if(m_noteWnd.IsWindowVisible() == FALSE ){

			//set the position of the note window
			RECT gridRect;
			m_ctrl->m_CUGGrid->GetClientRect(&gridRect);

			// show the note window to the right to the cell
			rect.left = rect.right + OFSET_HORIZ;
			rect.right = rect.left + m_nNoteWidth;

			if ( rect.top > OFSET_VERT )
				rect.top = rect.top - OFSET_VERT;
			rect.bottom = rect.top + m_nNoteHeight;

			CUGCell cell;
			m_ctrl->GetCell(col,row,&cell);

			m_noteWnd.SetWindowPos(&CWnd::wndTop,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
			m_noteWnd.MoveWindow(&rect);
			m_noteWnd.SetWindowText(cell.GetLabelText());
			m_noteWnd.ShowWindow(SW_SHOW);

			m_ctrl->GetCellRect(col,row,&m_noteCellRect);
			m_ctrl->m_CUGGrid->ClientToScreen(m_noteCellRect);

			if(m_timerID != 0)
				KillTimer(m_ctrl->m_hWnd,m_timerID);
			m_timerID = SetTimer(m_noteWnd.m_hWnd,100,200,TimerProc);
		}
		else if(m_timerID == 0){
			m_noteWnd.ShowWindow(SW_HIDE);
		}
	}
	else{
		m_noteWnd.ShowWindow(SW_HIDE);
		KillTimer(m_ctrl->m_hWnd,m_timerID);
	}
	
	return FALSE;
}

/***************************************************
OnScrolled - overloaded CUGCellType::OnScrolled
	
    **See CUGCellType::OnScrolled for more details
	about this function
****************************************************/
void CUGNoteType::OnScrolled(int col,long row,CUGCell *cell)
{
	if ( m_noteWnd.IsWindowVisible())
	{
		m_noteWnd.ShowWindow( SW_HIDE );
		m_ctrl->m_CUGGrid->Invalidate();
	}
}

/***************************************************
OnDraw - overloaded CUGCellType::OnDraw
	
    **See CUGCellType::OnDraw for more details
	about this function
****************************************************/
void CUGNoteType::OnDraw(CDC *dc,RECT *rect,int col,long row,
							 CUGCell *cell,int selected,int current)
{
	if (!m_drawThemesSet)
			m_useThemes = cell->UseThemes();

	//initialize the note window upon first use
	if(!m_bInit){
		m_bInit = TRUE;
		CRect rect(0,0,0,0);
		m_noteWnd.Create(WS_CHILD|ES_MULTILINE |WS_BORDER | WS_CLIPSIBLINGS,
			rect,m_ctrl->m_CUGGrid,ID_NOTEWND);
	}

	//draw the standard cell border
	DrawBorder(dc,rect,rect,cell);

	//draw the text
	DrawText(dc,rect,0,col,row,cell,selected,current);

	//draw the note indicator
	if(cell->IsPropertySet(UGCELL_LABEL_SET)){
		if(lstrlen(cell->GetLabelText()) > 0 ){
			//draw it
			CBrush brush;
			brush.CreateSolidBrush(RGB(255,0,0));
			CBrush* oldBrush = dc->SelectObject(&brush);
			dc->MoveTo(rect->right,rect->top);
			dc->BeginPath();
			dc->LineTo(rect->right,rect->top + 6);
			dc->LineTo(rect->right-6,rect->top);
			dc->LineTo(rect->right,rect->top);
			dc->EndPath();

			dc->FillPath();
			dc->SelectObject(oldBrush);

		}
	}
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
VOID CALLBACK EXPORT CUGNoteType::TimerProc(
			HWND hwnd,         // handle to window
			UINT uMsg,         // WM_TIMER message
			UINT_PTR idEvent,  // timer identifier
			DWORD dwTime       // current system time
			)
#else
VOID CALLBACK EXPORT CUGNoteType::TimerProc(
			HWND hwnd,         // handle to window
			UINT uMsg,         // WM_TIMER message
			unsigned int idEvent,  // timer identifier
			DWORD dwTime       // current system time
			)
#endif
{
	UNREFERENCED_PARAMETER(uMsg);
	UNREFERENCED_PARAMETER(dwTime);
	
	POINT point;
	GetCursorPos(&point);

	if(point.x < m_noteCellRect.left || point.x > m_noteCellRect.right ||
		point.y < m_noteCellRect.top || point.y > m_noteCellRect.bottom)
	{
		ShowWindow(hwnd,SW_HIDE);
		KillTimer(hwnd,idEvent);
	}
}

