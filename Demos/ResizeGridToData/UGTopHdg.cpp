// ==========================================================================
// 					Class Implementation : CUGTopHdg
// ==========================================================================
// Source file : UGTopHdg.cpp
// Copyright © The Ultimate Toolbox 2007, All Rights Reserved
// ==========================================================================

#include "stdafx.h"
#include "UGCtrl.h"
// define WM_HELPHITTEST messages
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/************************************************
Contructor
*************************************************/
CUGTopHdg::CUGTopHdg()
{
	//init the varialbes
	m_isSizing	= FALSE;
	m_canSize	= FALSE;
	
	//set the last focus rect position
	m_focusRect.left	= -1;
	m_focusRect.right	= -1;
	m_focusRect.top		= -1;
	m_focusRect.bottom	= -1;

	m_swapStartCol = -1;	//columns to swap
	m_swapEndCol = -1;	
}

/************************************************
Destructor
*************************************************/
CUGTopHdg::~CUGTopHdg()
{
	//perform clean up
}


/************************************************
*************************************************/
BEGIN_MESSAGE_MAP(CUGTopHdg, CWnd)
	//{{AFX_MSG_MAP(CUGTopHdg)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_SETCURSOR()
	ON_MESSAGE(WM_HELPHITTEST, OnHelpHitTest)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CUGTopHdg message handlers

/************************************************
OnPaint
*************************************************/
void CUGTopHdg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	m_drawHint.AddHint(0,m_GI->m_numberTopHdgRows * -1,m_GI->m_numberCols,0);

	DrawCellsIntern(&dc);
	
	m_drawHint.ClearHints();
}
/************************************************
DrawCellsIntern
*************************************************/
void CUGTopHdg::DrawCellsIntern(CDC *dc){

	RECT rect,cellRect;
  	CUGCell cell;
	CUGCellType * cellType;
	int dcID;
	int x,col;
	long y,row;
	
	m_ctrl->OnScreenDCSetup(dc,NULL,UG_TOPHEADING);

	
	//set the default font
	if(m_GI->m_defFont != NULL)
		dc->SelectObject((CFont *) m_GI->m_defFont);

	int blankRight = 0;

	for(y = (m_GI->m_numberTopHdgRows * -1); y < 0 ; y++){

		row = y;
	
		for(x = 0;x < m_GI->m_numberCols;x++){

			if(x == m_GI->m_numLockCols)
				x = m_GI->m_leftCol;
			col = x;
			row = y;
	
			
			//draw if invalid
			if(m_drawHint.IsInvalid(col,row) != FALSE){

				GetCellRect(col,row,&rect);
				CopyRect(&cellRect,&rect);

				m_ctrl->GetCellIndirect(col,row,&cell);

				if(cell.IsPropertySet(UGCELL_JOIN_SET)){
					GetCellRect(col,row,&cellRect);
					m_ctrl->GetJoinStartCell(&col,&row,&cell);
					if(m_drawHint.IsValid(col,row))
						continue;
					m_drawHint.SetAsValid(col,row);
				}
					
				if(cellRect.left < cellRect.right){
					cellType = m_ctrl->GetCellType(cell.GetCellType());

					dcID = dc->SaveDC();
					
					if(m_swapEndCol >=0 && col == m_swapStartCol)
						cellType->OnDraw(dc,&cellRect,col,row,&cell,1,0);
					else
						cellType->OnDraw(dc,&cellRect,col,row,&cell,0,0);

					dc->RestoreDC(dcID);
				}	
			}
			
			if(rect.right > m_GI->m_gridWidth)
				break;
		}
		if(blankRight < rect.right)
			blankRight = rect.right;
	}
	if(blankRight < m_GI->m_gridWidth){
		rect.top = 0;
		rect.bottom = m_GI->m_topHdgHeight;
		rect.left = blankRight;
		rect.right = m_GI->m_gridWidth;
		dc->SetBkColor( m_ctrl->OnGetDefBackColor( UG_TOPHEADING ));
		dc->ExtTextOut(0,0,ETO_OPAQUE,&rect,_T(""),0,NULL);
	}
}

/************************************************
Update 
	Purpose
		Checks to see what needs to be redrawn
		Then calls the redraw routines
	Params
		none
	Return
		none
*************************************************/
void CUGTopHdg::Update(){

	//calc the last row height
	//find the row
	int height = 0;
	for(int y= -1;y > (m_GI->m_numberTopHdgRows * -1) ;y--){
		height += GetTHRowHeight(y);
	}
	height = m_GI->m_topHdgHeight - height;
	if(height <0)
		height = 0;
	m_ctrl->SetTH_RowHeight(y,height);

	//redraw the window
	InvalidateRect(NULL);
	UpdateWindow();
}
/************************************************
Moved
	Purpose
	Params
		none
	Return
		none
*************************************************/
void CUGTopHdg::Moved(){

	if(m_GI->m_leftCol == m_GI->m_lastLeftCol)
		return;

	//redraw the window
	InvalidateRect(NULL);
	UpdateWindow();
}

/************************************************
*************************************************/
void CUGTopHdg::CheckForUserResize(CPoint *point){


	if(m_GI->m_userSizingMode == FALSE)
		return;

	//top heading column sizing
	int width = 0;
	for(int col = 0;col < m_GI->m_numberCols;col++){
		
		if(col == m_GI->m_numLockCols && col < m_GI->m_leftCol)
			col = m_GI->m_leftCol;
		
		width += m_ctrl->GetColWidth(col);
		if(width > m_GI->m_gridWidth)
			break;

		if(point->x < width+3 && point->x > width-3){
			
			if(m_ctrl->GetColWidth(col+1) == 0 && (col+1) < m_GI->m_numberCols)
				col++;

			if(m_ctrl->OnCanSizeCol(col) == FALSE)
				return;

			m_canSize = TRUE;
			m_colOrRowSizing	= 0;				// 0-col 1-row
			m_sizingColRow		= col;				//column/row being sized
			m_sizingStartSize	= m_ctrl->GetColWidth(col);//original size
			m_sizingStartPos	= point->x;			//original start pos

			SetCursor(m_GI->m_WEResizseCursor);
			return;
		}
	}

	//top heading row sizing
	int height = m_GI->m_topHdgHeight;
	for(int row = 0; row < m_GI->m_numberTopHdgRows; row++){
			
		if(point->y < height+3  && point->y > height-3){
				
			if(m_ctrl->OnCanSizeTopHdg() == FALSE)
				return;
			
			m_canSize = TRUE;
			m_colOrRowSizing	= 1;				// 0-col 1-row
			m_sizingColRow		= row;				//column/row being sized
			m_sizingStartSize	= m_GI->m_topHdgHeights[row];//original size
			m_sizingStartPos	= point->y;			//original start pos
			m_sizingStartHeight = m_GI->m_topHdgHeight;

			SetCursor(m_GI->m_NSResizseCursor);
			return;
		}
		height -= m_GI->m_topHdgHeights[row];
	}

	if(m_canSize){
		m_canSize = FALSE;
		SetCursor(m_GI->m_arrowCursor);
	}
}
/************************************************
OnMouseMove
	Purpose
		Checks to see if the mouse is over a cell separation
		If it is then it checks to see if sizing is allowed
		if so then the cusor is changed.
		If sizing is in progress then it resizes the width
		or height of the cells. It may redraw the new demensions
		immediatly or just draw a focus rect.
	Params
		  nFlags - mouse button states
		  point - point where the mouse is
	Return
		none
*************************************************/
void CUGTopHdg::OnMouseMove(UINT nFlags, CPoint point) 
{
	//check to see if the mouse is over a cell separation 
	//if the mouse is not currently sizing
	if(m_isSizing == FALSE && (nFlags&MK_LBUTTON) == 0 && m_GI->m_userSizingMode >0){
		//check for user resize position
		CheckForUserResize(&point);		
	}


	else if(m_isSizing){
	
		if(m_colOrRowSizing == 0){	//col sizing
			
			if(point.x < m_sizingStartPos - m_sizingStartSize)
				point.x = m_sizingStartPos - m_sizingStartSize;

			int width = m_sizingStartSize + (point.x - m_sizingStartPos);

			// send notifications to cell types.  In order to provide acceptable performance
			// this notification will only be sent to the visible rows.
			for(int nIndex=m_ctrl->GetTopRow(); nIndex<m_ctrl->GetBottomRow(); nIndex++)
			{
				CUGCellType* pCellType=m_ctrl->GetCellType(m_sizingColRow,nIndex);
				if(pCellType!=NULL)
				{
					pCellType->OnChangingCellWidth(m_sizingColRow,nIndex,&width);
				}
			}
			//send notification to control
			m_ctrl->OnColSizing(m_sizingColRow,&width);

			//just draw a focus rect
			if(m_GI->m_userSizingMode == 1){
				m_ctrl->SetColWidth(m_sizingColRow,width);
				Update();
				
				CDC* dc = m_ctrl->m_CUGGrid->GetDC();
				dc->DrawFocusRect(&m_focusRect);
				m_focusRect.top = 0;
				m_focusRect.bottom = m_GI->m_gridHeight;
				m_focusRect.left = point.x-1;
				m_focusRect.right = point.x+1;
				dc->DrawFocusRect(&m_focusRect);
				m_ctrl->m_CUGGrid->ReleaseDC(dc);

			}
			//update on the fly
			else{
				m_ctrl->SetColWidth(m_sizingColRow,width);
				m_ctrl->RedrawAll();				
			}
		}
		else{	//row sizing
			int height = m_sizingStartSize + (point.y - m_sizingStartPos);
			if(height <0)
				height = 0;
			m_GI->m_topHdgHeights[m_sizingColRow] = height;

			height = m_sizingStartHeight + (point.y - m_sizingStartPos);
			if(height <0)
				height = 0;

			if(m_ctrl->OnTopHdgSizing(&height) == TRUE)
			{
				m_GI->m_topHdgHeight = height;
				m_ctrl->AdjustComponentSizes();
			}
		}
	}
	//check for column swapping
	else if(m_GI->m_enableColSwapping && m_swapStartCol >= 0){
		
		MSG msg;
		
		//while column swapping enable mouse scrolling of the grid
		if(point.x < 0 || point.x > m_GI->m_gridWidth){
			
			//remove the focus rectangle
			CDC* dc = m_ctrl->m_CUGGrid->GetDC();
			dc->DrawFocusRect(&m_focusRect);
			m_focusRect.left	= -1;
			m_focusRect.right	= -1;
			m_ctrl->m_CUGGrid->ReleaseDC(dc);		

			while(1){
				if(point.x < 0){
					m_ctrl->MoveLeftCol(UG_LINEUP);
				}
				else if(point.x > m_GI->m_gridWidth){
					m_ctrl->MoveLeftCol(UG_LINEDOWN);
				}
				//check for messages, if ther are none then scroll some more
				while(PeekMessage(&msg,NULL,0,0,PM_NOREMOVE)){
					if(msg.message == WM_MOUSEMOVE || msg.message == WM_LBUTTONUP){
						return;
					}			
					GetMessage(&msg,NULL,0,0);
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}
	
		else{

			int col,row;
			RECT rect;
			point.y = 1;

			//find the column that the mouse is over
			if(GetCellFromPoint(&point,&col,&row,&rect) != UG_SUCCESS)
				return;

			//only start swapping if the mouse has moved over
			//a different column since the mouse button was pressed
			if(col != m_swapStartCol || m_swapEndCol >=0){
				
				if(( point.x - rect.left) > ((rect.right - rect.left)/2)){
					col ++;
					rect.left = rect.right;
				}

				if(col > m_GI->m_numberCols)
					col = m_GI->m_numberCols;

				//the firt time this is called redraw the top heading
				//so that the startswap cell is updated
				if(m_swapEndCol < 0){
					m_swapEndCol = col;
					Update();
				}

				//store the current col number
				m_swapEndCol = col;

				//draw a focus rect showing where the swap will
				//take place
				CDC* dc = m_ctrl->m_CUGGrid->GetDC();
				dc->DrawFocusRect(&m_focusRect);
				m_focusRect.top = 0;
				m_focusRect.bottom = m_GI->m_gridHeight;
				m_focusRect.left = rect.left;
				m_focusRect.right = rect.left+2;
				dc->DrawFocusRect(&m_focusRect);
				m_ctrl->m_CUGGrid->ReleaseDC(dc);		
			}
		}
	}
}

/************************************************
OnLButtonDown
	Purpose
		Checks to see if the sizing is allowed and
		if it is then sizing is started
		Also sends a mouse click notification to the
		main grid class
	Params
		  nFlags - mouse button states
		  point - point where the mouse is
	Return
		none
*************************************************/
void CUGTopHdg::OnLButtonDown(UINT nFlags, CPoint point)
{
	int col;
	int row;
	RECT rect;

	UNREFERENCED_PARAMETER(nFlags);

	if(GetFocus() != m_ctrl->m_CUGGrid)
		m_ctrl->m_CUGGrid->SetFocus();

	if(m_canSize){
		m_isSizing = TRUE;
		SetCapture();
	}
	else if(GetCellFromPoint(&point,&col,&row,&rect) == UG_SUCCESS){

		//store the column where the button was pressed
		//just in case a swap is to take place
		if(m_ctrl->OnColSwapStart(col) != FALSE)
			m_swapStartCol = col;

		//send a notification to the cell type	
		BOOL processed = m_ctrl->GetCellType(col,row)->OnLClicked(col,row,1,&rect,&point);
		//send a notification to the main grid class
		m_ctrl->OnTH_LClicked(col,row,1,&rect,&point,processed);

	}
	
	SetCapture();
}

/************************************************
OnLButtonUp
	Purpose
		Checks to see if the sizing is in progress, if
		it is then it is finished and the grid is redrawn.
		Plus a notification is sent to say sizing is 
		finished.
		Also sends a mouse click notification to the
		main grid class
	Params
		  nFlags - mouse button states
		  point - point where the mouse is
	Return
		none
*************************************************/
void CUGTopHdg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	int col;
	int row;
	RECT rect;

	UNREFERENCED_PARAMETER(nFlags);

	if(m_isSizing){

		if(m_colOrRowSizing == 0){	//col sizing
			//send notifications
			int width = m_ctrl->GetColWidth(m_sizingColRow);
			// send notifications to cell types.  In order to provide acceptable performance
			// this notification will only be sent to the visible rows.
			for(int nIndex=m_ctrl->GetTopRow(); nIndex<m_ctrl->GetBottomRow(); nIndex++)
			{
				CUGCellType* pCellType=m_ctrl->GetCellType(m_sizingColRow,nIndex);
				if(pCellType!=NULL)
				{
					pCellType->OnChangedCellWidth(m_sizingColRow,nIndex,&width);
				}
			}
			m_ctrl->OnColSized(m_sizingColRow,&width);
			if(width != m_ctrl->GetColWidth(m_sizingColRow))
				m_ctrl->SetColWidth(m_sizingColRow,width);
		}
		else{
			m_ctrl->OnTopHdgSized(&m_GI->m_topHdgHeight);
		}
		m_isSizing			= FALSE;

		//send notification
		m_ctrl->m_CUGGrid->InvalidateRect(NULL);
		m_ctrl->AdjustComponentSizes();
	}	

	else if(GetCellFromPoint(&point,&col,&row,&rect) == UG_SUCCESS){

		//send a notification to the cell type	
		BOOL processed = m_ctrl->GetCellType(col,row)->OnLClicked(col,row,0,&rect,&point);
		//send a notification to the main grid class
		m_ctrl->OnTH_LClicked(col,row,0,&rect,&point,processed);

	}

	//column swapping
	if(m_GI->m_enableColSwapping && m_swapStartCol >= 0){
		
		int end = m_swapEndCol;
		if(m_swapStartCol < end) // this needs to be done since the internal
			end --;				 // calc. does not take into account that the 
								 // start col will be removed and all the cols
								 // are going to slide over one position
		if(m_ctrl->OnCanColSwap(m_swapStartCol,end) != FALSE){
			m_ctrl->MoveColPosition(m_swapStartCol,m_swapEndCol,TRUE);

			// send OnColSwapped notification to inform user that the swap is completed
			m_ctrl->OnColSwapped(m_swapStartCol,end);

			//only redraw if swapping or a potential swap took place
			if(m_swapEndCol >=0){
				m_swapEndCol = -1;	
				m_ctrl->RedrawAll();
			}
			else{
				Invalidate();
			}
		}
		else{
			m_swapEndCol = -1;
			m_ctrl->RedrawAll();
		}
	}

	//reset variables
	m_swapStartCol		= -1;
	m_swapEndCol		= -1;	
	m_focusRect.left	= -1;
	m_focusRect.right	= -1;

	ReleaseCapture();
}

/************************************************
OnLButtonDblClk
	Purpose
		Sends a mouse click notification to the
		main grid class
	Params
		  nFlags - mouse button states
		  point - point where the mouse is
	Return
		none
*************************************************/
void CUGTopHdg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	int		col;
	int		row;
	RECT	rect;
	BOOL	processed = FALSE;

	UNREFERENCED_PARAMETER(nFlags);

	if(m_canSize){
		
		//check to see if the column should be BestFit
		if(m_GI->m_userBestSizeFlag){
			m_ctrl->BestFit(m_sizingColRow,m_sizingColRow,20,UG_BESTFIT_TOPHEADINGS);
			CheckForUserResize(&point);
		}
	}

	else if(GetCellFromPoint(&point,&col,&row,&rect) == UG_SUCCESS){

		//send a notification to the cell type	
		BOOL processed = m_ctrl->GetCellType(col,row)->OnDClicked(col,row,&rect,&point);
		//send a notification to the main grid class
		m_ctrl->OnTH_DClicked(col,row,&rect,&point,processed);
	}
}

/************************************************
OnRButtonDown
	Purpose
		Sends a mouse click notification to the
		main grid class.
		Checks to see if menus are enabled. If so 
		then a OnMenuStart notification is sent if
		it returns TRUE then the menu appears.
	Params
		  nFlags - mouse button states
		  point - point where the mouse is
	Return
		none
*************************************************/
void CUGTopHdg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	int col;
	int row;
	RECT rect;

	UNREFERENCED_PARAMETER(nFlags);

	if(GetFocus() != m_ctrl->m_CUGGrid)
		m_ctrl->m_CUGGrid->SetFocus();

	if(GetCellFromPoint(&point,&col,&row,&rect) == UG_SUCCESS){

		//send a notification to the cell type	
		BOOL processed = m_ctrl->GetCellType(col,row)->OnRClicked(col,row,0,&rect,&point);
		//send a notification to the main grid class
		m_ctrl->OnTH_RClicked(col,row,1,&rect,&point,processed);
	}

	if(m_GI->m_enablePopupMenu){
		ClientToScreen(&point);
		m_ctrl->StartMenu(col,row,&point,UG_TOPHEADING);
	}
}

/************************************************
OnRButtonUp
	Purpose
		Sends a mouse click notification to the
		main grid class.
	Params
		  nFlags - mouse button states
		  point - point where the mouse is
	Return
		none
*************************************************/
void CUGTopHdg::OnRButtonUp(UINT nFlags, CPoint point) 
{
	int col;
	int row;
	RECT rect;

	UNREFERENCED_PARAMETER(nFlags);

	if(GetCellFromPoint(&point,&col,&row,&rect) == UG_SUCCESS){

		//send a notification to the cell type	
		BOOL processed = m_ctrl->GetCellType(col,row)->OnRClicked(col,row,0,&rect,&point);
		//send a notification to the main grid class
		m_ctrl->OnTH_RClicked(col,row,0,&rect,&point,processed);
	}
}

/************************************************
OnSetCusor
	Purpose
		Sends a OnSetCusor notification to allow the
		cursor being shown to be changed.
*************************************************/
BOOL CUGTopHdg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	UNREFERENCED_PARAMETER(*pWnd);
	UNREFERENCED_PARAMETER(nHitTest);
	UNREFERENCED_PARAMETER(message);

	if(!m_canSize)
	{
		SetCursor(m_GI->m_arrowCursor);
		return 1;
	}
	else if(m_colOrRowSizing == 0)
		SetCursor(m_GI->m_WEResizseCursor);
	else
		SetCursor(m_GI->m_NSResizseCursor);

	return 1;
	
}
/************************************************
PreCreateWindow
	Purpose
		Adds clipchildren and clipsiblings
*************************************************/
BOOL CUGTopHdg::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style = cs.style | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	return CWnd::PreCreateWindow(cs);
}
/************************************************
GetCellRect
	Purpose
		Returns the rectangle for the given cell co-ordinates.
		If the cell is joined then the given co-ordinates 
		are modified to point to the start cell for the join.
	Params
		col - column to find the rect of
		row - row to find the rect of
		rect - rectangle to calculate
	Return
		UG_SUCCESS - success
		1 - cell not visible
*************************************************/
int CUGTopHdg::GetCellRect(int col,int row,RECT *rect){
	return GetCellRect(&col,&row,rect);
}

int CUGTopHdg::GetCellRect(int *col,int *row,RECT *rect){

	int x,y;
	int width	= 0;
	int height	= 0;

	int leftCol = 0;
	long topRow = 0;

	int startCol	= *col;
	int startRow	= *row;
	int endCol		= *col;
	int endRow		= *row;

	rect->left		= 0;
	rect->top		= 0;
	rect->right		= 0;
	rect->bottom	= m_GI->m_topHdgHeight;
	
	//if the specified cell is within a join then find the joined range
	if(m_GI->m_enableJoins)
		if(GetJoinRange(&startCol,&startRow,&endCol,&endRow) == UG_SUCCESS){
			*col = startCol;
			*row = startRow;
		}


	//find the col
	if(startCol >= m_GI->m_numLockCols){//if the col is not within the lock region
		rect->left = m_GI->m_lockColWidth;
		rect->right = m_GI->m_lockColWidth;
	}
	for(x=0;x<m_GI->m_numberCols;x++){
	
		if(x == m_GI->m_numLockCols)
			x = m_GI->m_leftCol;		
		
		if(x == startCol)
			rect->left = width;
		
		width += m_ctrl->GetColWidth(x);

		if(x == endCol){
			rect->right = width;
			break;
		}
	}

	//find the row
	for(y= (m_GI->m_numberTopHdgRows * -1);y < 0;y++){
			
		if(y == startRow)
			rect->top = height;

		height += GetTHRowHeight(y);

		if(y == endRow){
			rect->bottom = height;	
			break;
		}
	}

	return UG_SUCCESS;
}

/************************************************
GetCellFromPoint
	Purpose
		Returns the cell that lies over the given 
		point. Plus the rectangle for the cell is
		also returned
	Params
		point - point to check
		col	  - column that lies over the point
		row   - row that lies over the point
		rect  - rectangle of the cell found
	Return
*************************************************/
int CUGTopHdg::GetCellFromPoint(CPoint *point,int *col,int *row,RECT *rect){

	int ptsFound = 0;

	int x,y;

	rect->left		=0;
	rect->top		=0;
	rect->right		=0;
	rect->bottom	=0;

	//find the col
	for(x=0;x<m_GI->m_numberCols;x++){
		
		if(x == m_GI->m_numLockCols)
			x = m_GI->m_leftCol;
		
		rect->right += m_ctrl->GetColWidth(x);

		if(rect->right > point->x){
			rect->left = rect->right - m_ctrl->GetColWidth(x);
			ptsFound ++;
			*col = x;
			break;
		}
	}

	//find the row
	for(y = -m_GI->m_numberTopHdgRows; y< 0;y++){
	
		rect->bottom += GetTHRowHeight(y);

		if(rect->bottom > point->y){
			rect->top = rect->bottom - GetTHRowHeight(y);
			ptsFound ++;
			*row = y;
			break;
		}
	}

	if(ptsFound == 2)
		return UG_SUCCESS;

	*col = -1;
	*row = -1;
	return 1;
}
/************************************************
GetJoinRange
	Purpose
	Params
	Return
*************************************************/
int CUGTopHdg::GetJoinRange(int *col,int *row,int *endCol,int *endRow){
	
	if(m_GI->m_enableJoins == FALSE){
		return 1;
	}
	CUGCell cell;
	m_ctrl->GetCellIndirect(*col,*row,&cell);
	if(cell.IsPropertySet(UGCELL_JOIN_SET) == FALSE)
		return 2;

	int startCol;
	long startRow;
	BOOL origin;

	cell.GetJoinInfo(&origin,&startCol,&startRow);
	if(!origin){
		*col += startCol;
		*row += (int)startRow;
		m_ctrl->GetCellIndirect(*col,*row,&cell);
	}
	long r;
	cell.GetJoinInfo(&origin,endCol,&r);
	*endCol +=*col;
	*endRow = r + *row;

	return UG_SUCCESS;
}
/************************************************
GetTHRowHeight
	Purpose
	Params
	Return
*************************************************/
int CUGTopHdg::GetTHRowHeight(int row){

	//translate the row number into a 0 based positive index
	row = (row * -1) -1;

	if(row <0 || row > m_GI->m_numberTopHdgRows)
		return 0;

	return m_GI->m_topHdgHeights[row];
}

/************************************************
OnHelpHitTest
	Purpose
		Sent as a result of context sensitive help
		being activated (with mouse) over top heading
	Params
		WPARAM - not used
		LPARAM - x, y coordinates of the mouse event
	Return
		Context help ID to be displayed
*************************************************/
LRESULT CUGTopHdg::OnHelpHitTest(WPARAM, LPARAM lParam)
{
	// this message is fired as result of mouse activated
	// context help being hit over the grid.
	int col;
	long row;
	CRect rect(0,0,0,0);
	int xPos = LOWORD(lParam),
		yPos = HIWORD(lParam);
	m_ctrl->GetCellFromPoint( xPos, yPos, &col, &row, &rect );
	// return context help ID to be looked up
	return m_ctrl->OnGetContextHelpID( col, row, UG_TOPHEADING );
}

/************************************************
OnHelpInfo
	Purpose
		Sent as a result of context sensitive help
		being activated (with mouse) over top heading
		if the grid is on the dialog
	Params
		HELPINFO - structure that contains information on selected help topic
	Return
		TRUE or FALSE to allow further processing of this message
*************************************************/
BOOL CUGTopHdg::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	if (pHelpInfo->iContextType == HELPINFO_WINDOW)
	{
		// this message is fired as result of mouse activated help in a dialog
		int col;
		long row;
		CRect rect(0,0,0,0);
		CPoint point;
		point.x = pHelpInfo->MousePos.x;
		point.y = pHelpInfo->MousePos.y;

		ScreenToClient( &point );
		int xPos = point.x,
			yPos = point.y;
		m_ctrl->GetCellFromPoint( xPos, yPos, &col, &row, &rect );
		// call context help with ID returned by the user notification
		AfxGetApp()->WinHelp( m_ctrl->OnGetContextHelpID( col, row, UG_TOPHEADING ));
		// prevent further handling of this message
		return TRUE;
	}
	return FALSE;
}
