/*************************************************************************
				Class Implementation : CUGButtonType
**************************************************************************
	Source file : UGCTButn.cpp
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
*************************************************************************/

#include "stdafx.h"
#include "UGCtrl.h"
#include "UGCTbutn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//toggle button not currently implemented
#define  UGCT_BUTTONTOGGLE	32

/***************************************************
CUGButtonType - Contstructor
	Initialize member variables
****************************************************/
CUGButtonType::CUGButtonType(){
	
	m_btnDown		= FALSE;
	m_mode			= -1;
	m_btnDownCol	= -1;
	m_btnDownRow	= -1;

	m_canOverLap = FALSE;
}

/***************************************************
~CUGButtonType - Destructor
	Clean up all allocated resources
****************************************************/
CUGButtonType::~CUGButtonType(){

}

/***************************************************
OnDClicked - overloaded CUGCellType::OnDClicked
	Calls the OnLClicked function, allowing this
	celltype to respond to double clicks the same
	way it responds to single left clicks

    **See CUGCellType::OnDClicked for more details
	about this function
****************************************************/
BOOL CUGButtonType::OnDClicked(int col,long row,RECT *rect,POINT *point){
	return OnLClicked(col,row,1,rect,point);
}

/***************************************************
OnLClicked - overloaded CUGCellType::OnLClicked

  	When the mouse button is depressed, the	button 
	down variables are set.
	When the mouse button is released and the mouse was
	over the button then send a button click notification.
	Redraw the cell based on the state of the mouse
	button.

    **See CUGCellType::OnLClicked for more details
	about this function

Return 
	TRUE - since the mouse click was handled here
****************************************************/
BOOL CUGButtonType::OnLClicked(int col,long row,int updn,RECT *rect,POINT *point){

	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(point);

	if(updn){
		if(OnCellTypeNotify(m_ID,col,row,UGCT_BUTTONDOWN,0) != TRUE){
			m_btnDown = FALSE;
		}
		m_btnDown		= TRUE;
		m_btnDownCol	= col;
		m_btnDownRow	= row;
		CopyRect(&m_btnDownRect,rect);
	}
	else{
		
		OnCellTypeNotify(m_ID,col,row,UGCT_BUTTONUP,0);
		if(m_mode != UGCT_BUTTONTOGGLE){
			if(m_btnDownCol	== col && m_btnDownRow == row && m_btnDown == TRUE){
				OnCellTypeNotify(m_ID,col,row,UGCT_BUTTONCLICK,0);
			}
		}
		m_btnDown = FALSE;
	}
	
	m_ctrl->RedrawCell(col,row);

	return TRUE;
}

/***************************************************
OnMouseMove - overloaded CUGCellType::OnMouseMove
	If the mouse button is not depressed, then this 
	function just returns without further action.
	If the mouse button is depressed, then this function
	will check to see if it is over button or not. If it 
	is then, draw the button in a recessed state. If not
	then, draw the button in its default raised state.

    **See CUGCellType::OnMouseMove for more details
	about this function

Return
	TRUE - if the notification was processed
	FALSE - if the notification was not processed
****************************************************/
BOOL CUGButtonType::OnMouseMove(int col,long row,POINT *point,UINT flags){

	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(point);

	//return if the button is up
	if((flags&MK_LBUTTON) == FALSE)
		return FALSE;

	if(point->x >= m_btnDownRect.left && point->x <= m_btnDownRect.right){
		if(point->y >= m_btnDownRect.top && point->y <= m_btnDownRect.bottom){
			if(m_btnDown == FALSE){
				m_btnDown = TRUE;
				m_ctrl->RedrawCell(m_btnDownCol,m_btnDownRow);
			}
			return TRUE;
		}
	}

	if(m_btnDown){
		m_btnDown = FALSE;
		m_ctrl->RedrawCell(m_btnDownCol,m_btnDownRow);		
	}
	return FALSE;
}

/***************************************************
OnKeyDown - overloaded CUGCellType::OnKeyDown
	If the enter (return) key was pressed then this
	function will send a button click notification. 
	Otherwise it will just return.

    **See CUGCellType::OnKeyDown for more details
	about this function

Return
	TRUE - if the notification was processed
	FALSE - if the notification was not processed
****************************************************/
BOOL CUGButtonType::OnKeyDown(int col,long row,UINT *vcKey){

	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);

	if(*vcKey == VK_RETURN){
		OnCellTypeNotify(m_ID,m_ctrl->m_GI->m_currentCol,
			m_ctrl->m_GI->m_currentRow,UGCT_BUTTONCLICK,0);
		return TRUE;
	}

	return FALSE;
}

/***************************************************
OnKillFocus - overloaded CUGCellType::OnKillFocus
	Upon the lose of focus the button state is reset
	to its default unpressed state.

    **See CUGCellType::OnKillFocus for more details
	about this function

Return
	none
****************************************************/
void CUGButtonType::OnKillFocus(int col,long row,CUGCell *cell){
	
	CUGCellType::OnKillFocus(col,row,cell);

	m_btnDown		= FALSE;
}

/***************************************************
OnDraw - overloaded CUGCellType::OnDraw
	Draws the push button in its current state,
	pressed or unpressed.
	The drawing of text is performed using the 
	CUGCellType's DrawText function, therefore it
	has all of the same text capabilities as the
	default celltype.

    **See CUGCellType::OnDraw for more details
	about this function
Params
	dc		- device context to draw the cell with
	rect	- rectangle to draw the cell in
	col		- column that is being drawn
	row		- row that is being drawn
	cell	- cell that is being drawn
	selected- TRUE if the cell is selected, otherwise FALSE
	current - TRUE if the cell is the current cell, otherwise FALSE
Return
	none
****************************************************/
void CUGButtonType::OnDraw(CDC *dc,RECT *rect,int col,long row,
						   CUGCell *cell,int selected,int current)
{
	if (!m_drawThemesSet)
		m_useThemes = cell->UseThemes();
	
	UGXPThemeState state = UGXPThemes::GetState(selected>0, current>0);

	if (m_btnDown && current)
	{
		state = ThemeStatePressed;
	}

	RECT rectout;

	if (m_useThemes && UGXPThemes::DrawBackground(NULL, *dc, XPCellTypeButton, state, rect, NULL))
	{
		UGXPThemes::DrawEdge(NULL, *dc, XPCellTypeButton, state, rect, 0, 0, &rectout);
		cell->SetXPStyle(XPCellTypeButton);
		DrawText(dc,rect,rect->right - rectout.right ,col,row,cell,selected,current);
	}
	else
	{
		//draw the button
		if(m_btnDown && current)
                {
			cell->SetBorder(UG_BDR_RECESSED);
			DrawBorder(dc,rect,&rectout,cell);
		}
		else
                {
			cell->SetBorder(UG_BDR_RAISED);
			DrawBorder(dc,rect,&rectout,cell);
		}
	
	//draw the text in using the default drawing routine
		DrawText(dc,&rectout,0,col,row,cell,selected,current);
	}

	if(cell->IsPropertySet(UGCELL_CELLTYPEEX_SET) && current)
	{
		if(cell->GetCellTypeEx()&UGCT_BUTTONNOFOCUS)
		{
			m_ctrl->TempDisableFocusRect();
		}
	}
}
