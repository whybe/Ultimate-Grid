/*************************************************************************
				Class Implementation : CUGCTDropGrid, CDropDownCug
**************************************************************************
	Source file : UGCTDropGrid.cpp
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
*************************************************************************/

#include "stdafx.h"
#include "UGCtrl.h"
#include "UGCTDropGrid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/***************************************************
CUGCTDropGrid - Contstructor
	Initialize member variables
****************************************************/
CUGCTDropGrid::CUGCTDropGrid()
{
	m_pDropGridStruct = new CreateDropDownGrid;
	m_pGridCtrl = NULL;
	//set up the variables
	m_pen.CreatePen(PS_SOLID,1,GetSysColor(COLOR_BTNFACE));
	m_brush.CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
	m_btnWidth = GetSystemMetrics(SM_CXVSCROLL);
	// create the popup window, 
	CString className = AfxRegisterWndClass ( NULL );
	m_popupWnd.CreateEx( WS_EX_TOOLWINDOW|WS_EX_TOPMOST, className, _T(""), WS_POPUP, CRect(0,0,0,0), NULL, NULL );
	// make sure that this cell types do not overlap
	m_canOverLap = FALSE;
	// set the initial state of the button
	m_btnDown = FALSE;
	m_btnCol = -1;
	m_btnRow = -1;
}

/***************************************************
~CUGCTDropGrid - Destructor
	Clean up all allocated resources
****************************************************/
CUGCTDropGrid::~CUGCTDropGrid()
{
	if ( m_pGridCtrl->GetSafeHwnd() != NULL )
		m_pGridCtrl->DestroyWindow();

	delete m_pGridCtrl;
	delete m_pDropGridStruct;
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
LPCTSTR CUGCTDropGrid::GetName()
{
	return _T("Drop down grid");
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
LPCUGID CUGCTDropGrid::GetUGID()
{
	static const UGID ugid = { 0xfd332181, 0xd183,
								0x428a, 0xb5, 0xc5,
								0x90, 0x3c, 0x92,
								0x1, 0xc6, 0xf1 };

	return &ugid;
}

/***************************************************
GetEditArea  - overloaded CUGCellType::GetEditArea
	Returns the editable area of a cell type.
	Some celltypes (i.e. drop list) require to
	have certain portion of the cell not covered
	by the edit control.  In case of the drop down
	the drop button should not be covered.

Params:
	rect - pointer to the cell rectangle, it can
		   be used to modify the edit area
Return:
	UG_SUCCESS or UG_ERROR, currently the Utltimate
	Grid does not check the return value.
****************************************************/
int CUGCTDropGrid::GetEditArea(RECT *rect)
{	
	rect->right -=(m_btnWidth+1);

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
void CUGCTDropGrid::GetBestSize(CDC *dc,CSize *size,CUGCell *cell)
{
	CUGCellType::GetBestSize( dc, size, cell );
	// in the case of the drop down celltypes we will take the normal
	// width of the text selected, and if the drop button is visible,
	// we will increase the total width by the width of the button.
	if (!( cell->GetCellTypeEx()&UGCT_DROPLISTHIDEBUTTON ))
	{
		size->cx += m_btnWidth;
	}
}

/***************************************************
OnLClicked - overloaded CUGCellType::OnLClicked
	This function is called when the left mouse 
	button is clicked over a cell.
	The drop down grid cell type uses this event to
	show the drop down control when the user
	clicks on the drop button.
	The popup window will also be hiden when
	user clicks on the same cell while it is
	showing.
 
Params:
	col - column that was clicked in
	row - row that was clicked in
	updn - TRUE if the mouse button just went down
		 - FALSE if the mouse button just went up
	rect - rectangle of the cell that was clicked in
	point - point where the mouse was clicked
Return:
	TRUE - if the event was processed
	FALSE - if the event was not
****************************************************/
BOOL CUGCTDropGrid::OnLClicked( int col, long row, int updn, RECT *rect, POINT *point )
{	
	if( updn )
	{
		if( point->x > ( rect->right - m_btnWidth ))
		{			
			if( col == m_btnCol && row == m_btnRow )
			{
				m_btnCol = -1;
				m_btnRow = -1;		
				if ( m_pDropGridStruct->pGridCtrl->GetSafeHwnd() != NULL )
					m_pDropGridStruct->pGridCtrl->DestroyWindow();
			}
			else
			{
				//copy the dropdown button co-ords
				CopyRect( &m_btnRect, rect );
				m_btnRect.left = rect->right - m_btnWidth;
			
				//redraw the button
				m_btnDown = TRUE;
				m_btnCol = col;
				m_btnRow = row;
				m_ctrl->RedrawCell( m_btnCol, m_btnRow );

				//start the drop down process
				ShowPopupGridWnd();
				return TRUE;
			}
		}
		else if(m_btnCol ==-2)
		{
			m_btnCol = -1;
			m_btnRow = -1;			
			return FALSE;
		}
	}
	else if(m_btnDown)
	{
		m_ctrl->RedrawCell( col, row );
		return TRUE;
	}

	return FALSE;
}

/***************************************************
OnMouseMove - overloaded CUGCellType::OnMouseMove
	This function is called when the mouse  is over
	a cell of this celltype.
	The Drop down cell type uses this notification
	to visually represent to the user that the left
	mouse button was pressed over the button area,
	but it now has been moved on and the popup will
	not be shown if the button is released.

Params:
	col - column that the mouse is over
	row - row that the mouse is over
	point - point where the mouse is
	flags - mouse move flags (see WM_MOUSEMOVE)
Return:
	TRUE - if the event was processed
	FALSE - if the event was not
***************************************************/
BOOL CUGCTDropGrid::OnMouseMove(int col,long row,POINT *point,UINT flags)
{	
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);

	if((flags&MK_LBUTTON) == FALSE)
		return TRUE;

	if(point->x >= m_btnRect.left && point->x <= m_btnRect.right)
	{
		if(point->y >= m_btnRect.top && point->y <= m_btnRect.bottom)
		{
			if(!m_btnDown)
			{
				m_btnDown = TRUE;
				m_ctrl->RedrawCell(m_btnCol,m_btnRow);
			}
		}
		else if(m_btnDown)
		{
			m_btnDown = FALSE;
			m_ctrl->RedrawCell(m_btnCol,m_btnRow);
		}
	}
	else if(m_btnDown)
	{
		m_btnDown = FALSE;
		m_ctrl->RedrawCell(m_btnCol,m_btnRow);
	}

	return FALSE;
}

/***************************************************
OnKillFocus - overloaded CUGCellType::OnKillFocus
	This function is called when a the cell type
	looses focus.  The dropdown celltype uses this
	notification to make sure that the popup window
	is no longer visible.

Params:
	col - column that just lost focus
	row - row that just lost focus
	cell - pointer to the cell object located at col/row
Return:
	<none>
****************************************************/
void CUGCTDropGrid::OnKillFocus(int col,long row,CUGCell *cell)
{	
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(cell);

	if ( m_btnDown == TRUE )
		OnClosePopup();
}

/***************************************************
OnKeyDown - overloaded CUGCellType::OnKeyDown
	This function is called when a cell of this type
	has focus and a key is pressed.(See WM_KEYDOWN)
	The drop down cell type allows the user to show
	the popup window.

Params:
	col - column that has focus
	row - row that has focus
	vcKey - pointer to the virtual key code, of the key that was pressed
Return:
	TRUE - if the event was processed
	FALSE - if the event was not
****************************************************/
BOOL CUGCTDropGrid::OnKeyDown(int col,long row,UINT *vcKey)
{	
	if((*vcKey==VK_RETURN) || ((*vcKey==VK_DOWN)&&(GetKeyState(VK_CONTROL) < 0)))
	{
		m_btnCol = col;
		m_btnRow = row;
		ShowPopupGridWnd();
		*vcKey =0;
		return TRUE;
	}

	return FALSE;
}

/***************************************************
OnCharDown  - overloaded CUGCellType::OnCharDown
	The drop down celltype only handles this notification to inform the 
	grid that the enter and down arrow keys were already handled.

Params:
	col - column that has focus
	row - row that has focus
	vcKey - pointer to the virtual key code, of the key that was pressed
Return:
	TRUE - if the event was processed
	FALSE - if the event was not
****************************************************/
BOOL CUGCTDropGrid::OnCharDown(int col,long row,UINT *vcKey)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);

	if(*vcKey==VK_RETURN)
		return TRUE;
	if(*vcKey==VK_DOWN)
		return TRUE;
	return FALSE;
}

/***************************************************
OnDraw - overloaded CUGCellType::OnDraw
	The drop down cell type draws its text using the
	base classes DrawText routine, plus draws the
	drop down button

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
void CUGCTDropGrid::OnDraw(CDC *dc,RECT *rect,int col,long row,CUGCell *cell,int selected,int current)
{
	if (!m_drawThemesSet)
		m_useThemes = cell->UseThemes();

	//draw the text in using the default drawing routine
	CUGCellType::DrawText(dc,rect,0,col,row,cell,selected,current);

	int left = rect->left;
	RECT rectout;
	CPen * oldpen;

	int style = 0;
	if(cell->IsPropertySet(UGCELL_CELLTYPEEX_SET))
		style = cell->GetCellTypeEx();

	//if the cell is not current and hide button is on
	//then dont draw the button
	if(style&UGCT_DROPLISTHIDEBUTTON && !current)
	{
		CUGCellType::OnDraw(dc,rect,col,row,cell,selected,current);
		return;
	}

	DrawBorder(dc,rect,rect,cell);

	// The printer and the monitor have different resolutions.
	// So we should adjust the size of the button.

	float fScale = 1.0;
	
#ifdef UG_ENABLE_PRINTING
	fScale = m_ctrl->GetUGPrint()->GetPrintVScale(dc);
#endif

	rect->left = rect->right - (int) (fScale * m_btnWidth);

#ifdef UG_ENABLE_PRINTING
	if (dc->IsPrinting())
	{
		rect->left += (int) fScale;
		rect->right -= (int) fScale;
		rect->top += (int) fScale;
		rect->bottom -= (int) fScale;
	}
#endif
	// draw the 3D border
	if( m_btnDown == TRUE && m_btnCol == col && m_btnRow == row )
	{
		cell->SetBorder(UG_BDR_RECESSED);
		DrawBorder(dc,rect,&rectout,cell);
	}
	else{
		cell->SetBorder(UG_BDR_RAISED);
		DrawBorder(dc,rect,&rectout,cell);
	}

	if (!m_useThemes || !UGXPThemes::DrawBackground(NULL, *dc, L"COMBOBOX", 1, 0, &rectout, NULL))
	{
		//fill the border in
		dc->FillRect(&rectout,&m_brush);
		
		//make a line to separate the border from the rest ofthe cell
		oldpen = (CPen *)dc->SelectObject((CPen *)&m_pen);
		dc->MoveTo(rect->left-1,rect->top);
		dc->LineTo(rect->left-1,rect->bottom);
		dc->SelectObject(oldpen);

		//draw the down arrow
		if (dc->IsPrinting())
		{
	#ifdef UG_ENABLE_PRINTING
			CRgn rgn;

			int	nWidth = rect->right - rect->left;
			int	nHeight = rect->bottom - rect->top;

			POINT point[] = {
				{rect->left + nWidth * 3 / 10, rect->top + nHeight * 5 / 12} ,
				{rect->left + nWidth * 7 / 10, rect->top + nHeight * 5 / 12},
				{rect->left + nWidth / 2, rect->top + nHeight * 7 / 12}
			};

			rgn.CreatePolygonRgn(point, 3, ALTERNATE);

			CBrush Brush;
			Brush.CreateSolidBrush(RGB(0,0,0));
			dc->FillRgn(&rgn, &Brush);

			dc->SelectObject((CPen*)CPen::FromHandle((HPEN)GetStockObject(BLACK_PEN)));
			dc->MoveTo(rect->left,rect->top);
			dc->LineTo(rect->right,rect->top);
	#endif
		}
		else
		{
			int x= (int) ((fScale * m_btnWidth-5)/2) + rect->left;
			int y = ((rect->bottom - rect->top -3)/2) + rect->top;

			// create a pen object that will be used to draw the arrow on the button
			CPen *arrowPen = NULL;
			if ( cell->GetReadOnly() == TRUE )
			{
				arrowPen = new CPen;
				arrowPen->CreatePen( PS_SOLID, 1, RGB(128,128,128));
			}
			else
				arrowPen = (CPen*)CPen::FromHandle((HPEN)GetStockObject(BLACK_PEN));

			oldpen = dc->SelectObject( arrowPen );

			// draw the arrow
			dc->MoveTo(x,y);
			dc->LineTo(x+5,y);
			dc->MoveTo(x+1,y+1);
			dc->LineTo(x+4,y+1);
			dc->MoveTo(x+2,y+2);
			dc->LineTo(x+2,y+1);

			if ( cell->GetReadOnly() == TRUE )
			{
				// clean up after temporary pen object
				dc->SelectObject(oldpen);
				arrowPen->DeleteObject();
				delete arrowPen;
				// when the arrow is disabled, add a while outline line
				dc->SelectObject((CPen*)CPen::FromHandle((HPEN)GetStockObject(WHITE_PEN)));
				dc->MoveTo(x+3,y+2);
				dc->LineTo(x+5,y);
				dc->MoveTo(x+3,y+3);
				dc->LineTo(x+6,y);
			}
		}
	}
}

/***************************************************
ShowPopupGridWnd
	The ShowPopupGridWnd function takes care of showing the popup window,
	and allows the developer to initialize the CreateDropDownGrid structure.
	By default the CreateDropDownGrid will be populated with the calculated
	position and size for the popup, default instance of the CDropDownCug,
	and pointer to the popup window.  All of this information can be
	modified/customized through the OnCellTypeNotify notification.
Params:
	<none>
Return:
	UG_ERROR	- when user decides not to show the popup window
	UG_SUCCESS	- 
***************************************************/
int CUGCTDropGrid::ShowPopupGridWnd()
{
	CRect clientRect(0,0,0,0), cellRect(0,0,0,0);
	CUGCell cell;
	m_ctrl->GetCellIndirect( m_btnCol, m_btnRow, &cell );
	
	// calculate the initial rectangle for dropdown window, this information
	// will often be changed by the user throught the CUGCtrl::OnCellTypeNotify
	m_ctrl->GetCellRect( m_btnCol, m_btnRow, cellRect );

	if ( m_btnRow >= 0 )
	{
		cellRect.top += m_ctrl->GetTH_Height();
		cellRect.bottom += m_ctrl->GetTH_Height();
	}

	m_pDropGridStruct->popUpWndRect = CRect( cellRect.left, cellRect.bottom,
											 cellRect.left + 100, cellRect.bottom + 100 );

	if (!( cell.GetCellTypeEx()&UGCT_SHOWASPOPUPWND ))
	{
		// adjust the popup's window position and size so that it does not
		// extend beyond the grid window.
		m_ctrl->GetClientRect( clientRect );
		if ( m_pDropGridStruct->popUpWndRect.bottom > clientRect.bottom )
		{
			int dif = m_pDropGridStruct->popUpWndRect.bottom - clientRect.bottom;
			m_pDropGridStruct->popUpWndRect.bottom -= dif;
			m_pDropGridStruct->popUpWndRect.top -= dif;
			if ( m_pDropGridStruct->popUpWndRect.top < 0 )
				m_pDropGridStruct->popUpWndRect.top = 0;
		}
		if ( m_pDropGridStruct->popUpWndRect.right > clientRect.right )
		{
			int dif = m_pDropGridStruct->popUpWndRect.right - clientRect.right;
			m_pDropGridStruct->popUpWndRect.right -= dif;
			m_pDropGridStruct->popUpWndRect.left -= dif;
			if ( m_pDropGridStruct->popUpWndRect.left < 0 )
				m_pDropGridStruct->popUpWndRect.left = 0;
		}
	}

	// If necessary delete the default grid control, allow for recreation
	if ( m_pGridCtrl != NULL )
	{
		if ( m_pGridCtrl->GetSafeHwnd() != NULL )
			m_pGridCtrl->DestroyWindow();

		delete m_pGridCtrl;
	}
	// create the default grid control
	m_pGridCtrl = new CDropDownCug;
	m_pGridCtrl->CreateGrid( WS_CHILD|WS_BORDER, CRect(0,0,0,0), &m_popupWnd, 3551512 );

	m_pDropGridStruct->pPopupWnd = &m_popupWnd;
	m_pDropGridStruct->pGridCtrl = m_pGridCtrl;

	// notify the user of the celltype that the popup window is about to be displayed
	if ( OnCellTypeNotify(m_ID,m_btnCol,m_btnRow,UGCT_SHOWDROPGRID,(LONG_PTR)m_pDropGridStruct) == FALSE )
		// if FALSE was returned from OnCellTypeNotify call, than the developer does not
		// wish to show the popup window at the moment.
		return UG_ERROR;

	// provide the 'poped up' grid control with information on the parent
	// including pointer to the parent CUGCtrl derived class, celltype
	// and location of the cell that initiated the popup.
	m_pDropGridStruct->pGridCtrl->m_parentCtrl = m_ctrl;
	m_pDropGridStruct->pGridCtrl->m_cellType = this;
	// show and position the popup window (parent to the grid)
	CRect popRect ( m_pDropGridStruct->popUpWndRect );
	m_ctrl->ClientToScreen( popRect );
	m_popupWnd.MoveWindow( popRect );
	m_popupWnd.ShowWindow( SW_SHOW );
	// show and size the poped up grid control
	m_pDropGridStruct->pGridCtrl->ShowWindow( SW_SHOW );
	m_pDropGridStruct->pGridCtrl->MoveWindow( 0, 0, m_pDropGridStruct->popUpWndRect.Width(), m_pDropGridStruct->popUpWndRect.Height() );
	m_pDropGridStruct->pGridCtrl->SetFocus();
	// redraw current cell with the drop button down.
	m_btnDown = TRUE;
	m_ctrl->RedrawCell(m_btnCol,m_btnRow);

	return UG_SUCCESS;
}

/***************************************************
OnSelectedGridItem
	The OnSelectedGridItem function should be called when a selection
	in the grid is made, if the pSelectedInfo is not provided than
	it will be created using standard information (current cell location,
	pointer to a cell object, and pointer to the grid control).
Params:
	pSelectedInfo	- pointer to the SelectedGridItem structure, which
					  will be passed on to the developer through the
					  OnCellTypeNotify notification.
Return:
	<none>
***************************************************/
int CUGCTDropGrid::OnSelectedGridItem( SelectedGridItem *pSelectedInfo /*= NULL*/ )
{
	CUGCell cell;
	SelectedGridItem selectedInfo;
	m_ctrl->GetCellIndirect( m_btnCol, m_btnRow, &cell );

	if ( cell.GetReadOnly() == TRUE )
		// Do not allow changes to be made for ReadOnly cells.
		return UG_ERROR;

	if ( pSelectedInfo == NULL )
	{	// the user did not pass in a valid pointer to the SelectedGridItem
		// structure.  Create an instance of the structure and poputate it
		// with default information (current col, row, and text value of the cell)
		selectedInfo.pGridCtrl = m_pDropGridStruct->pGridCtrl;
		selectedInfo.selectedCol = m_pDropGridStruct->pGridCtrl->GetCurrentCol();
		selectedInfo.selectedRow = m_pDropGridStruct->pGridCtrl->GetCurrentRow();
		selectedInfo.selectedCell = &cell;
		pSelectedInfo = &selectedInfo;
		// populate the cell with the text of the selected cell
		cell.SetText( m_pDropGridStruct->pGridCtrl->QuickGetText( selectedInfo.selectedCol, selectedInfo.selectedRow ));
	}

	// notify the devloper 
	if ( OnCellTypeNotify(m_ID,m_btnCol,m_btnRow,UGCT_SELECTEDITEM,(LONG_PTR)pSelectedInfo ) == FALSE )
	{	// If the developer returns FALSE than the cell information will not be saved.
		return UG_ERROR;
	}

	// Set the new value to the cell
	m_ctrl->SetCell( m_btnCol, m_btnRow, selectedInfo.selectedCell );

	return UG_SUCCESS;
}

/***************************************************
OnClosePopup
	function should be called whenever the popup window
	should be closed without making selection.
	By default it is called by the CDropDownCug when
	user hits the ESC key or window looses focus.
Params:
	<none>
Return:
	<none>
***************************************************/
void CUGCTDropGrid::OnClosePopup()
{
	if ( m_popupWnd.IsWindowVisible())
		m_popupWnd.ShowWindow( SW_HIDE );

	// notify the developer that the popup window is closed
	OnCellTypeNotify( m_ID, m_btnCol, m_btnRow, UGCT_CLOSEDROPGRID, 0 );

	// Delete the default grid control, allow for recreation
	if ( m_pGridCtrl != NULL )
	{
		if ( m_pGridCtrl->GetSafeHwnd() != NULL )
			m_pGridCtrl->DestroyWindow();

		delete m_pGridCtrl;
		m_pGridCtrl = NULL;
	}

	// reset the button's state
	m_btnDown = FALSE;
	m_btnCol = -1;
	m_btnRow = -1;

	// redraw the grid
	m_ctrl->Invalidate();
	m_ctrl->SetFocus();
}

/*************************************************************************
				Class Implementation : CDropDownCug
**************************************************************************
	Source file : UGCTDropGrid.cpp
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
*************************************************************************/

/////////////////////////////////////////////////////////////////////////////
// Standard CDropDownCug construction/destruction
CDropDownCug::CDropDownCug()
{
	m_parentCtrl = NULL;
	m_cellType = NULL;
}

CDropDownCug::~CDropDownCug()
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnKillFocus
//		Sent when the grid is loosing focus.
//	Params:
//		section - Id of the grid section loosing focus, usually UG_GRID
//				  possible sections:
//						UG_TOPHEADING, UG_SIDEHEADING, UG_GRID
//	Return:
//		<none>
void CDropDownCug::OnKillFocus(int section)
{
	if ( m_cellType != NULL )
		((CUGCTDropGrid*)m_cellType)->OnClosePopup();
}

/////////////////////////////////////////////////////////////////////////////
//	OnKeyDown
//		Sent when grid received a WM_KEYDOWN message, usually as a result
//		of a user pressing any key on the keyboard.
//	Params:
//		vcKey		- virtual key code of the key user has pressed
//		processed	- indicates if current event was processed by other control in the grid.
//	Return:
//		<none>
void CDropDownCug::OnKeyDown(UINT *vcKey,BOOL processed)
{
	UNREFERENCED_PARAMETER(processed);

	if ( m_cellType == NULL )
		return;

	if ( *vcKey == VK_ESCAPE )
		((CUGCTDropGrid*)m_cellType)->OnClosePopup();
	else if ( *vcKey == VK_RETURN )
	{
		// call the default implementation for the selection
		((CUGCTDropGrid*)m_cellType)->OnSelectedGridItem();
		// close the popup window
		((CUGCTDropGrid*)m_cellType)->OnClosePopup();
	}
}

/////////////////////////////////////////////////////////////////////////////
//	OnDClicked
//		Sent whenever the user double clicks the left mouse button within the grid
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void CDropDownCug::OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{
	UNREFERENCED_PARAMETER(*rect);
	UNREFERENCED_PARAMETER(*point);
	UNREFERENCED_PARAMETER(processed);

	if ( m_cellType != NULL )
	{
		// call the default implementation for the selection
		((CUGCTDropGrid*)m_cellType)->OnSelectedGridItem();
		// close the popup window
		((CUGCTDropGrid*)m_cellType)->OnClosePopup();
	}
}	
