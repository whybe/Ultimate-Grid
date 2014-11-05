/***************************************************
****************************************************
Skeleton Class for a Derived MyCug
****************************************************
****************************************************/

#include "stdafx.h"
#include "resource.h"
#include "MyCug.h"
#include "Ex14Doc.h"
#include "Ex14View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(MyCug,CUGCtrl)
	//{{AFX_MSG_MAP(MyCug)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/***************************************************
****************************************************/
MyCug::MyCug(CEx14View* pView) : m_view(pView)
{
}
/***************************************************
****************************************************/
MyCug::~MyCug()
{
	UGXPThemes::CleanUp();
}

/***************************************************
OnSetup
	This function is called just after the grid window 
	is created or attached to a dialog item.
	It can be used to initially setup the grid
****************************************************/
void MyCug::OnSetup(){

	// initialize local variables
	int rows = 20;
	int cols = 20;
	int i,j;
	CString temp;

	m_defFont.CreatePointFont( 90, "Arial" );
	SetDefFont( &m_defFont );

	// setup rows and columns
	SetNumberRows(rows);
	SetNumberCols(cols);
	m_defEditCtrl.SetAutoSize(FALSE);	
	AdjustComponentSizes();

	// fill-in cells with data
	for (i = 0; i < cols; i++)
		for (j = 1; j < rows; j++) {
			temp.Format("%d",(i+1)*(j+1));
			QuickSetText(i,j,temp);
		}

	// add col headings
	for (i = 0; i < cols; i++) {
		temp.Format("%d",(i+1));
		QuickSetText(i,-1,temp);
	}

	// add row headings
	for (j = 0; j < rows; j++) {
		temp.Format("%d",(j+1));
		QuickSetText(-1,j,temp);
	}

	QuickSetText(0,0,"Interact with the grid to see the basic notifications sent to the grid");
	SetMultiSelectMode(UG_MULTISELECT_CELL);

	// enable and create pop-up menu
	EnableMenu(TRUE);
	AddMenuItem(1001,"Testing Notifcaitons");

	// send notification message
	m_view->AddNotificationMessage("OnSetup");
}


/***************************************************
OnCanMove
	Sent when the current cell in the grid is about
	to move
	A return of TRUE allows the move, a return of
	FALSE stops the move
****************************************************/
int MyCug::OnCanMove(int oldcol,long oldrow,int newcol,long newrow){
	m_temp.Format("Can Move: OldCell %d,%d, NewCell %d,%d", oldcol, oldrow, newcol, newrow);
	m_view->AddNotificationMessage(m_temp);
	return TRUE;
}
/***************************************************
OnCanMove
	Sent when the top row or left column in the grid is about
	to move
	A return of TRUE allows the move, a return of
	FALSE stops the move
****************************************************/
int MyCug::OnCanViewMove(int oldcol,long oldrow,int newcol,long newrow){
	m_temp.Format("Can View Move: OldCell %d,%d, NewCell %d,%d", oldcol, oldrow, newcol, newrow);
	m_view->AddNotificationMessage(m_temp);
	return TRUE;
}
/***************************************************
****************************************************/
void MyCug::OnHitBottom(long numrows,long rowspast,long rowsfound){
	m_temp.Format("Hit Bottom: Number Rows %d, Rowes Past %d", numrows, rowspast);
	m_view->AddNotificationMessage(m_temp);
}
/***************************************************
****************************************************/
void MyCug::OnHitTop(long numrows,long rowspast){
	m_temp.Format("Hit Top: Number Rows %d, Rowes Past %d", numrows, rowspast);
	m_view->AddNotificationMessage(m_temp);
}
/***************************************************
OnCanSizeCol
	Sent when the user is over a separation line on
	the top heading
	A return value of TRUE allows the possibiliy of
	a resize
****************************************************/
int MyCug::OnCanSizeCol(int col){
	m_temp.Format("Can Size Col: column number %d", col);
	m_view->AddNotificationMessage(m_temp);
	return TRUE;
}
/***************************************************
OnColSizing
	Sent when the user is sizing a column
	The column that is being sized is given as 
	well as the width. Plus the width can be modified 
	at this point. This makes it easy to set min and
	max widths
****************************************************/
void MyCug::OnColSizing(int col,int *width){
	m_temp.Format("Column Sizing: column number %d, width %d", col, *width);
	m_view->AddNotificationMessage(m_temp);
}
/***************************************************
OnColSized
	This is sent when the user finished sizing the 
	given column (see above for more details)
****************************************************/
void MyCug::OnColSized(int col,int *width){
	m_temp.Format("Column Sized: column number %d, width %d", col, *width);
	m_view->AddNotificationMessage(m_temp);
}
/***************************************************
OnCanSizeRow
	Sent when the user is over a separation line on
	the side heading
	A return value of TRUE allows the possibiliy of
	a resize
****************************************************/
int  MyCug::OnCanSizeRow(long row){
	m_temp.Format("Can Size Row: row number %d", row);
	m_view->AddNotificationMessage(m_temp);
	return TRUE;
}
/***************************************************
OnRowSizing
    Sent when the user is sizing a row
	The row that is being sized is given as 
	well as the height. Plus the height can be modified 
	at this point. This makes it easy to set min and
	max heights
****************************************************/
void MyCug::OnRowSizing(long row,int *height){
	m_temp.Format("Row Sizing: row number %d, width %d", row, *height);
	m_view->AddNotificationMessage(m_temp);
}
/***************************************************
OnRowSized
	This is sent when the user is finished sizing hte
	given row ( see above for more details)
****************************************************/
void MyCug::OnRowSized(long row,int *height){
	m_temp.Format("Row Sized: row number %d, width %d", row, *height);
	m_view->AddNotificationMessage(m_temp);
}
/***************************************************
OnCanSizeSideHdg
	This is sent when the user moves into position 
	for sizing the width of the side heading
	return TRUE to allow the sizing
	or FALSE to not allow it
****************************************************/
int MyCug::OnCanSizeSideHdg(){
	m_temp.Format("Can Size Heading");
	m_view->AddNotificationMessage(m_temp);
	return TRUE;
}
/***************************************************
OnCanSizeTopHdg
	This is sent when the user moves into position 
	for sizing the height of the top heading
	return TRUE to allow the sizing
	or FALSE to not allow it
****************************************************/
int MyCug::OnCanSizeTopHdg(){
	m_temp.Format("Can Top Size Heading");
	m_view->AddNotificationMessage(m_temp);
	return TRUE;
}
/***************************************************
OnSideHdgSizing
****************************************************/
int MyCug::OnSideHdgSizing(int *width){
	m_temp.Format("Side Heading Size changing: width %d", *width);
	m_view->AddNotificationMessage(m_temp);
	return TRUE;

}
/***************************************************
OnTopHdgSizing
****************************************************/
int MyCug::OnTopHdgSizing(int *height){
	m_temp.Format("Top Heading Size changing: height %d", *height);
	m_view->AddNotificationMessage(m_temp);
	return TRUE;
}

/***************************************************
OnSideHdgSized
	Purpose
	Params
	Return
****************************************************/
int MyCug::OnSideHdgSized(int *width){
	m_temp.Format("Side Heading Sized: width %d", *width);
	m_view->AddNotificationMessage(m_temp);
	return TRUE;
}

/***************************************************
OnTopHdgSized
	Purpose
	Params
	Return
****************************************************/
int MyCug::OnTopHdgSized(int *height){
	m_temp.Format("Top Heading Sized: height %d", *height);
	m_view->AddNotificationMessage(m_temp);
	return TRUE;

}

/***************************************************
OnColChange
	Sent whenever the current column changes
	The old and the new columns are given
****************************************************/
void MyCug::OnColChange(int oldcol,int newcol){
	m_temp.Format("Column Changed: old col %d, new col %d", oldcol, newcol);
	m_view->AddNotificationMessage(m_temp);

}
/***************************************************
OnRowChange
	Sent whenever the current row changes
	The old and the new rows are given
****************************************************/
void MyCug::OnRowChange(long oldrow,long newrow){
	m_temp.Format("Row Changed: old row %d, new row %d", oldrow, newrow);
	m_view->AddNotificationMessage(m_temp);
}
/***************************************************
OnCellChange
	Sent whenever the current cell changes rows or
	columns
****************************************************/
void MyCug::OnCellChange(int oldcol,int newcol,long oldrow,long newrow){
	m_temp.Format("Cell Changed: old cell %d,%d, new cell %d,%d", oldcol,oldrow,newcol,newrow);
	m_view->AddNotificationMessage(m_temp);
}
/***************************************************
OnLeftColChange
	Sent whenever the left visible column in the grid 
	changes
****************************************************/
void MyCug::OnLeftColChange(int oldcol,int newcol){
	m_temp.Format("Left Column Changed: old col %d, new col %d", oldcol, newcol);
	m_view->AddNotificationMessage(m_temp);
}
/***************************************************
OnTopRowChange
	Sent whenever the top visible row in the grid changes
****************************************************/
void MyCug::OnTopRowChange(long oldrow,long newrow){
	m_temp.Format("Top Row Changed: old row %d, new row %d", oldrow, newrow);
	m_view->AddNotificationMessage(m_temp);
}
/***************************************************
OnLClicked
	Sent whenever the user clicks the left mouse
	button within the grid
	this message is sent when the button goes down
	then again when the button goes up

	'col' and 'row' are negative if the area clicked
	in is not a valid cell
	'rect' the rectangle of the cell that was clicked in
	'point' the point where the mouse was clicked
	'updn'  TRUE if the button is down FALSE if the
	        button just when up
****************************************************/
void MyCug::OnLClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed){
	m_temp.Format("Left Clicked: UpDown %d, Point %d,%d, Rect %d,%d,%d,%d "
		,updn,point->x,point->y,rect->left,rect->top,rect->right,rect->bottom);
	m_view->AddNotificationMessage(m_temp);
}
/***************************************************
OnRClicked
	Sent whenever the user clicks the right mouse
	button within the grid
	this message is sent when the button goes down
	then again when the button goes up

	'col' and 'row' are negative if the area clicked
	in is not a valid cell
	'rect' the rectangle of the cell that was clicked in
	'point' the point where the mouse was clicked
	'updn'  TRUE if the button is down FALSE if the
	        button just when up
****************************************************/
void MyCug::OnRClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed){
	m_temp.Format("Right Clicked: UpDown %d, Point %d,%d, Rect %d,%d,%d,%d "
		,updn,point->x,point->y,rect->left,rect->top,rect->right,rect->bottom);
	m_view->AddNotificationMessage(m_temp);
}
/***************************************************
OnDClicked
	Sent whenever the user double clicks the left mouse
	button within the grid

	'col' and 'row' are negative if the area clicked
	in is not a valid cell
	'rect' the rectangle of the cell that was clicked in
	'point' the point where the mouse was clicked
****************************************************/
void MyCug::OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed){
	m_temp.Format("Double Clicked: Point %d,%d, Rect %d,%d,%d,%d "
		,point->x,point->y,rect->left,rect->top,rect->right,rect->bottom);
	m_view->AddNotificationMessage(m_temp);
	StartEdit();
}				 

/***************************************************
OnMouseMove
****************************************************/
void MyCug::OnMouseMove(int col,long row,POINT *point,UINT nFlags,BOOL processed){
	m_temp.Format("Mouse Moved: Point %d,%d, Col %d, Row %d, Flag %d, Processed %d "
		,point->x,point->y,col,row,nFlags,processed);
	m_view->AddNotificationMessage(m_temp);
}

/***************************************************
OnTH_LClicked
	Sent whenever the user clicks the left mouse
	button within the top heading
	this message is sent when the button goes down
	then again when the button goes up

	'col' is negative if the area clicked in is not valid
	'updn'  TRUE if the button is down FALSE if the
	        button just when up
****************************************************/
void MyCug::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed){
	m_temp.Format("Top Heading Left Clicked: UpDown %d, Point %d,%d, Rect %d,%d,%d,%d "
		,updn,point->x,point->y,rect->left,rect->top,rect->right,rect->bottom);
	m_view->AddNotificationMessage(m_temp);
}
/***************************************************
OnTH_RClicked
	Sent whenever the user clicks the right mouse
	button within the top heading
	this message is sent when the button goes down
	then again when the button goes up

	'col' is negative if the area clicked in is not valid
	'updn'  TRUE if the button is down FALSE if the
	        button just when up
****************************************************/
void MyCug::OnTH_RClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed){
	m_temp.Format("Top Heading Right Clicked: UpDown %d, Point %d,%d, Rect %d,%d,%d,%d "
		,updn,point->x,point->y,rect->left,rect->top,rect->right,rect->bottom);
	m_view->AddNotificationMessage(m_temp);
}
/***************************************************
OnTH_LClicked
	Sent whenever the user double clicks the left mouse
	button within the top heading

	'col' is negative if the area clicked in is not valid
****************************************************/
void MyCug::OnTH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed){
	m_temp.Format("Top Heading Double Clicked: Point %d,%d, Rect %d,%d,%d,%d "
		,point->x,point->y,rect->left,rect->top,rect->right,rect->bottom);
	m_view->AddNotificationMessage(m_temp);
}
/***************************************************
OnSH_LClicked
	Sent whenever the user clicks the left mouse
	button within the side heading
	this message is sent when the button goes down
	then again when the button goes up

	'row' is negative if the area clicked in is not valid
	'updn'  TRUE if the button is down FALSE if the
	        button just when up
****************************************************/
void MyCug::OnSH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed){
	m_temp.Format("Side Heading Left Clicked: UpDown %d, Point %d,%d, Rect %d,%d,%d,%d "
		,updn,point->x,point->y,rect->left,rect->top,rect->right,rect->bottom);
	m_view->AddNotificationMessage(m_temp);
}
/***************************************************
OnSH_RClicked
	Sent whenever the user clicks the right mouse
	button within the side heading
	this message is sent when the button goes down
	then again when the button goes up

	'row' is negative if the area clicked in is not valid
	'updn'  TRUE if the button is down FALSE if the
	        button just when up
****************************************************/
void MyCug::OnSH_RClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed){
	m_temp.Format("Side Heading Right Clicked: UpDown %d, Point %d,%d, Rect %d,%d,%d,%d "
		,updn,point->x,point->y,rect->left,rect->top,rect->right,rect->bottom);
	m_view->AddNotificationMessage(m_temp);
}
/***************************************************
OnSH_DClicked
	Sent whenever the user double clicks the left mouse
	button within the side heading

	'row' is negative if the area clicked in is not valid
****************************************************/
void MyCug::OnSH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed){
	m_temp.Format("Side Heading Double Clicked: Point %d,%d, Rect %d,%d,%d,%d "
		,point->x,point->y,rect->left,rect->top,rect->right,rect->bottom);
	m_view->AddNotificationMessage(m_temp);
}
/***************************************************
OnCB_LClicked
	Sent whenever the user clicks the left mouse
	button within the top corner button
	this message is sent when the button goes down
	then again when the button goes up

	'updn'  TRUE if the button is down FALSE if the
	        button just when up
****************************************************/
void MyCug::OnCB_LClicked(int updn,RECT *rect,POINT *point,BOOL processed){
	m_temp.Format("Corner Button Left Clicked: UpDown %d, Point %d,%d, Rect %d,%d,%d,%d "
		,updn,point->x,point->y,rect->left,rect->top,rect->right,rect->bottom);
	m_view->AddNotificationMessage(m_temp);
}
/***************************************************
OnCB_RClicked
	Sent whenever the user clicks the right mouse
	button within the top corner button
	this message is sent when the button goes down
	then again when the button goes up

	'updn'  TRUE if the button is down FALSE if the
	        button just when up
****************************************************/
void MyCug::OnCB_RClicked(int updn,RECT *rect,POINT *point,BOOL processed){
	m_temp.Format("Corner Button Right Clicked: UpDown %d, Point %d,%d, Rect %d,%d,%d,%d "
		,updn,point->x,point->y,rect->left,rect->top,rect->right,rect->bottom);
	m_view->AddNotificationMessage(m_temp);
}
/***************************************************
OnCB_DClicked
	Sent whenever the user double clicks the left mouse
	button within the top corner button
****************************************************/
void MyCug::OnCB_DClicked(RECT *rect,POINT *point,BOOL processed){
	m_temp.Format("Corner Button Double Clicked: Point %d,%d, Rect %d,%d,%d,%d "
		,point->x,point->y,rect->left,rect->top,rect->right,rect->bottom);
	m_view->AddNotificationMessage(m_temp);
}
/***************************************************
OnKeyDown
	Sent whenever the user types when the grid has
	focus. The keystroke can be modified here as well.
	(See WM_KEYDOWN for more information)
****************************************************/
void MyCug::OnKeyDown(UINT *vcKey,BOOL processed){
	m_temp.Format("Key Down: KeyCode %d", *vcKey);
	m_view->AddNotificationMessage(m_temp);
}
/***************************************************
OnCharDown
	Sent whenever the user types when the grid has
	focus. The keystroke can be modified here as well.
	(See WM_CHAR for more information)
****************************************************/
void MyCug::OnCharDown(UINT *vcKey,BOOL processed){
	m_temp.Format("Char Down: KeyCode %d", *vcKey);
	m_view->AddNotificationMessage(m_temp);
}
	
/***************************************************
OnEditStart
	This message is sent whenever the grid is ready 
	to start editing a cell
	A return of TRUE allows the editing a return of
	FALSE stops editing
	Plus the properties of the CEdit class can be modified
****************************************************/
int MyCug::OnEditStart(int col, long row,CWnd **edit){
	m_temp.Format("Edit Start: Cell %d,%d", col,row);
	m_view->AddNotificationMessage(m_temp);
	return TRUE;
}
/***************************************************
OnEditVerify
	This is send when the editing is about to end
****************************************************/
int MyCug::OnEditVerify(int col,long row,CWnd *edit ,UINT *vcKey){//}//,LPCTSTR string,int pos){
	m_temp.Format("Edit Verify: Cell %d,%d, KeyCode %d, ", col,row,*vcKey);
	m_view->AddNotificationMessage(m_temp);
	return TRUE;
}
/***************************************************
OnEditFinish this is send when editing is finished
****************************************************/
int MyCug::OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag){
	m_temp.Format("Edit Finish: Cell %d,%d, String %s", col,row,string);
	m_view->AddNotificationMessage(m_temp);
	return TRUE;
}
/***************************************************
OnEditFinish this is send when editing is finished
****************************************************/
int MyCug::OnEditContinue(int oldcol,long oldrow,int* newcol,long* newrow){
	m_temp.Format("Edit Continue: Old Cell %d,%d, New Cell %d,%d", oldcol,oldrow,*newcol,*newrow);
	m_view->AddNotificationMessage(m_temp);
	return TRUE;
}
/***************************************************
sections - UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
			UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
****************************************************/
void MyCug::OnMenuCommand(int col,long row,int section,int item){
	m_temp.Format("Menu Command: cell %d,%d, section %d, item id %d", col,row,section,item);
	m_view->AddNotificationMessage(m_temp);
}
/***************************************************
return UG_SUCCESS to allow the menu to appear
return 1 to not allow the menu to appear
****************************************************/
int MyCug::OnMenuStart(int col,long row,int section){
	m_temp.Format("Menu Start: cell %d,%d, section %d", col,row,section);
	m_view->AddNotificationMessage(m_temp);
	return TRUE;
}


/***************************************************
	Purpose
	Params
	Return
****************************************************/
void MyCug::OnSetFocus(int section){
	m_temp.Format("Set Focus: section %d",section);
	m_view->AddNotificationMessage(m_temp);

}

/***************************************************
	Purpose
	Params
	Return
****************************************************/
void MyCug::OnKillFocus(int section){
	m_temp.Format("Kill Focus: section %d",section);
	m_view->AddNotificationMessage(m_temp);
}

/***************************************************
	Purpose
	Params
	Return
****************************************************/
void MyCug::OnAdjustComponentSizes(RECT *grid,RECT *topHdg,RECT *sideHdg,
		RECT *cnrBtn,RECT *vScroll,RECT *hScroll,RECT *tabs){
	m_temp.Format("Components adjusting: lotsa rects");
	m_view->AddNotificationMessage(m_temp);

} 

