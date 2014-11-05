/////////////////////////////////////////////////////////////////////////////
//	Skeleton Class for a Derived MyCug

#include "stdafx.h"
#include "resource.h"
#include "MyCug.h"

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


/////////////////////////////////////////////////////////////////////////////
// Standard MyCug construction/destruction
MyCug::MyCug()
{
}

MyCug::~MyCug()
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnSetup
//		This function is called just after the grid window 
//		is created or attached to a dialog item.
//		It can be used to initially setup the grid
void MyCug::OnSetup()
{
	CUGExcel::OnSetup();
}

/////////////////////////////////////////////////////////////////////////////
//	OnSheetSetup	
//		This notification is called for each additional sheet that the grid
//		might contain, here you can customize each sheet in the grid.
//	Params:
//		sheetNumber - idndex of current sheet
//	Return:
//		<none>
void MyCug::OnSheetSetup(int sheetNumber)
{
	CUGExcel::OnSheetSetup( sheetNumber );
}

/////////////////////////////////////////////////////////////////////////////
//	OnCanMove
//		Sent when current cell is changed
//	Params:
//		oldcol, oldrow - 
//		newcol, newrow - cell that is gaining focus
//	Return:
//		TRUE - to allow the move
//		FALSE - to prevent new cell from gaining focus
int MyCug::OnCanMove(int oldcol,long oldrow,int newcol,long newrow)
{
	int retVal = CUGExcel::OnCanMove( oldcol, oldrow, newcol, newrow );
	// Translate column location
	oldcol = GetColTranslation( oldcol );
	newcol = GetColTranslation( newcol );
	// TODO: add your notification handling here

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////
//	OnCanViewMove
//		Is called when current grid view is about to be scrolled
//	Params:
//		oldcol, oldrow - coordinates of orriginal top-left cell
//		newcol, newrow - coordinates of top-left cell that is gaining the focus
//	Return:
//		TRUE - to allow for the scroll
//		FALSE - to prevent the view from scrolling
int MyCug::OnCanViewMove(int oldcol,long oldrow,int newcol,long newrow)
{
	int retVal = CUGExcel::OnCanViewMove( oldcol, oldrow, newcol, newrow );
	// Translate column location
	oldcol = GetColTranslation( oldcol );
	// TODO: add your notification handling here

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////
//	OnHitBottom
//		This notification allows for dynamic row loading, it will be called
//		when the grid drawing function has hit the last row.  It allows the grid
//		to ask the datasource/developer if there are additional rows to be displayed.
//	Params:
//		numrows		- known number of rows in the grid
//		rowspast	- number of extra rows that the grid is looking for in the datasource
//		rowsfound	- number of rows actually found, usually equal to rowspast or zero.
//	Return:
//		<none>
void MyCug::OnHitBottom(long numrows,long rowspast,long rowsfound)
{
	CUGExcel::OnHitBottom( numrows, rowspast, rowsfound );
	// TODO: add your notification handling here
}

/////////////////////////////////////////////////////////////////////////////
//	OnHitTop
//		Is called when the user has scrolled all the way to the top of the grid.
//	Params:
//		numrows		- known number of rows in the grid
//		rowspast	- number of extra rows that the grid is looking for in the datasource
//	Return:
//		<none>
void MyCug::OnHitTop(long numrows,long rowspast)
{
	CUGExcel::OnHitTop( numrows, rowspast );
	// TODO: add your notification handling here
}

/////////////////////////////////////////////////////////////////////////////
//	OnCanSizeCol
//		Sent when the user is about to size a given column
//	Params:
//		col - identifies column number that will be sized
//	Return:
//		TRUE - to allow sizing
//		FALSE - to prevent sizing
int MyCug::OnCanSizeCol(int col)
{
	int retVal = CUGExcel::OnCanSizeCol( col );
	// Translate column location
	col = GetColTranslation( col );
	// TODO: add your notification handling here

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////
//	OnColSizing
//		Sent when the user is sizing a column
//	Params:
//		col - column currently sizing
//		width - current new column width
//	Return:
//		<none>
void MyCug::OnColSizing(int col,int *width)
{
	CUGExcel::OnColSizing( col, width );
	// Translate column location
	col = GetColTranslation( col );
	// TODO: add your notification handling here
}

/////////////////////////////////////////////////////////////////////////////
//	OnColSized
//		This is sent when the user finished sizing the 
//		given column.
//	Params:
//		col - column sized
//		width - new column width
//	Return:
//		<none>
void MyCug::OnColSized(int col,int *width)
{
	CUGExcel::OnColSized( col, width );
	// Translate column location
	col = GetColTranslation( col );
	// TODO: add your notification handling here
}

/////////////////////////////////////////////////////////////////////////////
//	OnCanSizeRow
//		Sent when the user is about to start sizing of a row
//	Params:
//		row - identifies row number that will be sized
//	Return:
//		TRUE - to allow sizing
//		FALSE - to prevent sizing
int MyCug::OnCanSizeRow(long row)
{
	int retVal = CUGExcel::OnCanSizeRow( row );
	// TODO: add your notification handling here

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////
//	OnRowSizing
//		Sent durring user sizing of a row, can provide feed back on current height
//	Params:
//		row - row sizing
//		width - current new row height
//	Return:
//		<none>
void MyCug::OnRowSizing(long row,int *height)
{
	CUGExcel::OnRowSizing( row, height );
	// TODO: add your notification handling here
}

/////////////////////////////////////////////////////////////////////////////
//	OnRowSized
//		This is sent when the user is finished sizing hte
//		given row.
//	Params:
//		row - row sized
//		width - new row height
//	Return:
//		<none>
void MyCug::OnRowSized(long row,int *height)
{
	CUGExcel::OnRowSized( row, height );
	// TODO: add your notification handling here
}

/////////////////////////////////////////////////////////////////////////////
//	OnCanSizeSideHdg
//		Sent when the user is about to start sizing of the side heading
//	Params:
//		<none>
//	Return:
//		TRUE - to allow sizing
//		FALSE - to prevent sizing
int MyCug::OnCanSizeSideHdg()
{
	int retVal = CUGExcel::OnCanSizeSideHdg();
	// TODO: add your notification handling here

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////
//	OnSideHdgSizing
//		Sent while the heading is being sized
//	Params:
//		width - current new width of the side heading
//	Return:
//		TRUE - to accept current new size
//		FALSE - to stop sizing, the size is either too large or too small
int MyCug::OnSideHdgSizing(int *width)
{
	int retVal = CUGExcel::OnSideHdgSizing( width );
	// TODO: add your notification handling here

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////
//	OnSideHdgSized
//		Sent when the user has completed the sizing of the side heading
//	Params:
//		width - new width
//	Return:
//		TRUE - to accept new size
//		FALSE - to revert to old size
int MyCug::OnSideHdgSized(int *width)
{
	int retVal = CUGExcel::OnSideHdgSized( width );
	// TODO: add your notification handling here

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////
//	OnCanSizeTopHdg
//		Sent when the user is about to start sizing of the top heading
//	Params:
//		<none>
//	Return:
//		TRUE - to allow sizing
//		FALSE - to prevent sizing
int MyCug::OnCanSizeTopHdg()
{
	int retVal = CUGExcel::OnCanSizeTopHdg();
	// TODO: add your notification handling here

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////
//	OnTopHdgSizing
//		Sent while the top heading is being sized
//	Params:
//		height - current new height of the top heading
//	Return:
//		TRUE - to accept current new size
//		FALSE - to stop sizing, the size is either too large or too small
int MyCug::OnTopHdgSizing(int *height)
{
	int retVal = CUGExcel::OnTopHdgSizing( height );
	// TODO: add your notification handling here

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////
//	OnTopHdgSized
//		Sent when the user has completed the sizing of the top heading
//	Params:
//		height - new height
//	Return:
//		TRUE - to accept new size
//		FALSE - to revert to old size
int MyCug::OnTopHdgSized(int *height)
{
	int retVal = CUGExcel::OnTopHdgSized( height );
	// TODO: add your notification handling here

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////
//	OnColChange
//		Sent whenever the current column changes
//	Params:
//		oldcol - column that is loosing the focus
//		newcol - column that the user move into
//	Return:
//		<none>
void MyCug::OnColChange(int oldcol,int newcol)
{
	CUGExcel::OnColChange( oldcol, newcol );
	// Translate column location
	oldcol = GetColTranslation( oldcol );
	newcol = GetColTranslation( newcol );
	// TODO: add your notification handling here
}

/////////////////////////////////////////////////////////////////////////////
//	OnRowChange
//		Sent whenever the current row changes
//	Params:
//		oldrow - row that is loosing the locus
//		newrow - row that user moved into
//	Return:
//		<none>
void MyCug::OnRowChange(long oldrow,long newrow)
{
	CUGExcel::OnRowChange( oldrow, newrow );
	// TODO: add your notification handling here
}

/////////////////////////////////////////////////////////////////////////////
//	OnCellChange
//		Sent whenever the current cell changes
//	Params:
//		oldcol, oldrow - coordinates of cell that is loosing the focus
//		newcol, newrow - coordinates of cell that is gaining the focus
//	Return:
//		<none>
void MyCug::OnCellChange(int oldcol,int newcol,long oldrow,long newrow)
{	
	CUGExcel::OnCellChange( oldcol, newcol, oldrow, newrow );
	// Translate column location
	oldcol = GetColTranslation( oldcol );
	newcol = GetColTranslation( newcol );
	// TODO: add your notification handling here	
}

/////////////////////////////////////////////////////////////////////////////
//	OnLeftColChange
//		Sent whenever the left visible column in the grid changes, indicating
//		that the view was scrolled horizontaly
//	Params:
//		oldcol - column that used to be on the left
//		newcol - new column that is going to be the first visible column from the left
//	Return:
//		<none>
void MyCug::OnLeftColChange(int oldcol,int newcol)
{
	CUGExcel::OnLeftColChange( oldcol, newcol );
	// Translate column location
	oldcol = GetColTranslation( oldcol );
	newcol = GetColTranslation( newcol );
	// TODO: add your notification handling here
}

/////////////////////////////////////////////////////////////////////////////
//	OnTopRowChange
//		Sent whenever the top visible row in the grid changes, indicating
//		that the view was scrolled vertically
//	Params:
//		oldrow - row that used to be on the top
//		newrow - new row that is going to be the first visible row from the top
//	Return:
//		<none>
void MyCug::OnTopRowChange(long oldrow,long newrow)
{
	CUGExcel::OnTopRowChange( oldrow, newrow );
	// TODO: add your notification handling here
}

/////////////////////////////////////////////////////////////////////////////
//	OnLClicked
//		Sent whenever the user clicks the left mouse button within the grid
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnLClicked(int col,long row,int updn,RECT *rect,POINT *point,int processed)
{
	CUGExcel::OnLClicked( col, row, updn, rect, point, processed );
	// Translate column location
	col = GetColTranslation( col );
	// TODO: add your notification handling here
}
		
/////////////////////////////////////////////////////////////////////////////
//	OnRClicked
//		Sent whenever the user clicks the right mouse button within the grid
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnRClicked(int col,long row,int updn,RECT *rect,POINT *point,int processed)
{
	CUGExcel::OnRClicked( col, row, updn, rect, point, processed );
	// Translate column location
	col = GetColTranslation( col );
	// TODO: add your notification handling here
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
void MyCug::OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{
	CUGExcel::OnDClicked( col, row, rect, point, processed );
	// Translate column location
	col = GetColTranslation( col );
	// TODO: add your notification handling here
	StartEdit();
}	
			 
/////////////////////////////////////////////////////////////////////////////
//	OnMouseMove
//		Is sent to each cell that the mouse is over.
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		point		- represents the screen point where the mouse event was detected
//		nFlags		- 
//		processed	- indicates if current event was processed by other control in the grid.
//	Return:
//		<none>
void MyCug::OnMouseMove(int col,long row,POINT *point,UINT nFlags,BOOL processed)
{
	CUGExcel::OnMouseMove( col, row, point, nFlags, processed );
	// Translate column location
	col = GetColTranslation( col );
	// TODO: add your notification handling here
}

/////////////////////////////////////////////////////////////////////////////
//	OnTH_LClicked
//		Sent whenever the user clicks the left mouse button within the top heading
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{
	CUGExcel::OnTH_LClicked( col, row, updn, rect, point, processed );
	// Translate column location
	col = GetColTranslation( col );
	// TODO: add your notification handling here
}

/////////////////////////////////////////////////////////////////////////////
//	OnTH_RClicked
//		Sent whenever the user clicks the right mouse button within the top heading
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnTH_RClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{
	CUGExcel::OnTH_RClicked( col, row, updn, rect, point, processed );
	// Translate column location
	col = GetColTranslation( col );
	// TODO: add your notification handling here
}

/////////////////////////////////////////////////////////////////////////////
//	OnTH_DClicked
//		Sent whenever the user double clicks the left mouse
//		button within the top heading
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnTH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{
	CUGExcel::OnTH_DClicked( col, row, rect, point, processed );
	// Translate column location
	col = GetColTranslation( col );
	// TODO: add your notification handling here
}

/////////////////////////////////////////////////////////////////////////////
//	OnSH_LClicked
//		Sent whenever the user clicks the left mouse button within the side heading
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnSH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{
	CUGExcel::OnSH_LClicked( col, row, updn, rect, point, processed );
	// Translate column location
	col = GetColTranslation( col );
	// TODO: add your notification handling here
}

/////////////////////////////////////////////////////////////////////////////
//	OnSH_RClicked
//		Sent whenever the user clicks the right mouse button within the side heading
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnSH_RClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{
	CUGExcel::OnSH_RClicked( col, row, updn, rect, point, processed );
	// Translate column location
	col = GetColTranslation( col );
	// TODO: add your notification handling here
}

/////////////////////////////////////////////////////////////////////////////
//	OnSH_DClicked
//		Sent whenever the user double clicks the left mouse button within the side heading
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnSH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{
	CUGExcel::OnSH_DClicked( col, row, rect, point, processed );
	// Translate column location
	col = GetColTranslation( col );
	// TODO: add your notification handling here
}

/////////////////////////////////////////////////////////////////////////////
//	OnCB_LClicked
//		Sent whenever the user clicks the left mouse button within the top corner button
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnCB_LClicked(int updn,RECT *rect,POINT *point,BOOL processed)
{
	CUGExcel::OnCB_LClicked( updn, rect, point, processed );
	// TODO: add your notification handling here
}

/////////////////////////////////////////////////////////////////////////////
//	OnCB_RClicked
//		Sent whenever the user clicks the right mouse button within the top corner button
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnCB_RClicked(int updn,RECT *rect,POINT *point,BOOL processed)
{
	CUGExcel::OnCB_RClicked( updn, rect, point, processed );
	// TODO: add your notification handling here
}

/////////////////////////////////////////////////////////////////////////////
//	OnCB_DClicked
//		Sent whenever the user double clicks the left mouse
//		button within the top corner button
//	Params:
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnCB_DClicked(RECT *rect,POINT *point,BOOL processed)
{
	CUGExcel::OnCB_DClicked( rect, point, processed );
	// TODO: add your notification handling here
}

/////////////////////////////////////////////////////////////////////////////
//	OnKeyDown
//		Sent whenever the user types when the grid has focus. The keystroke can be
//		modified here as well. (See WM_KEYDOWN for more information)
//	Params:
//		vcKey		- virtual key code of the key user has pressed
//		processed	- indicates if current event was processed by other control in the grid.
//	Return:
//		<none>
void MyCug::OnKeyDown(UINT *vcKey,BOOL processed)
{
	CUGExcel::OnKeyDown( vcKey, processed );
	// TODO: add your notification handling here
}

/////////////////////////////////////////////////////////////////////////////
//	OnCharDown
//		Sent whenever the user types when the grid has focus. The keystroke can be 
//		modified here as well. (See WM_CHAR for more information)
//	Params:
//		vcKey		- virtual key code of the key user has pressed
//		processed	- indicates if current event was processed by other control in the grid.
//	Return:
//		<none>
void MyCug::OnCharDown(UINT *vcKey,BOOL processed)
{
	CUGExcel::OnCharDown( vcKey, processed );
	// TODO: add your notification handling here

	if ( *vcKey != VK_TAB && *vcKey != VK_ESCAPE )
		StartEdit( *vcKey );
}
	
/////////////////////////////////////////////////////////////////////////////
//	OnGetCell
//		This message is sent everytime the grid needs to
//		draw a cell in the grid. At this point the cell
//		class has been filled with the information to be
//		used to draw the cell. The information can now be
//		changed before it is used for drawing
//
//	Warning:
//		This notification is called for each cell that needs to be painted
//		Placing complicated calculations here will slowdown the refresh speed.
//	Params:
//		col, row	- coordinates of cell currently drawing
//		cell		- pointer to the cell object that is being drawn
//	Return:
//		<none>
void MyCug::OnGetCell(int col,long row,CUGCell *cell)
{
	// TODO: add your notification handling here

	if ( col >= 0 && row == -1 )
	{	// set default values to the top heading
		CString tempStr;
		tempStr.Format( "%c", 65 + col );
		cell->SetText( tempStr );
	}
	else if ( row >= 0 && col == -1 )
	{	// set default values to the side heading (row numbers)
		cell->SetNumberDecimals( 0 );
		cell->SetNumber( row );
	}
	else if ( col >= 0 && row >= 0 )
	{
	}

	CUGExcel::OnGetCell( col, row, cell );
}

/////////////////////////////////////////////////////////////////////////////
//	OnSetCell
//		This notification is sent everytime a cell is set, here you have a chance
//		to make final modification to the cell's content before it is set.
//	Params:
//		col, row	- coordinates of cell currently saving
//		cell		- pointer to the cell object that is being saved
//	Return:
//		<none>
void MyCug::OnSetCell(int col,long row,CUGCell *cell)
{
	CUGExcel::OnSetCell( col, row, cell );
	// Translate column location
	col = GetColTranslation( col );
	// TODO: add your notification handling here
}

/////////////////////////////////////////////////////////////////////////////
//	OnDataSourceNotify
//		This message is sent from a data source and this message
//		depends on the data source - check the information
//		on the data source(s) being used
//		- The ID of the Data source is also returned
//	Params:
//		ID		- datasource ID
//		msg		- message ID to identify current process
//		param	- additional iformation or object that might be needed
//	Return:
//		<none>
void MyCug::OnDataSourceNotify(int ID,long msg,long param)
{
	CUGExcel::OnDataSourceNotify( ID, msg, param );
	// TODO: add your notification handling here
}

/////////////////////////////////////////////////////////////////////////////
//	OnCellTypeNotify
//		This notification is sent by the celltype and it is different from cell-type
//		to celltype and even from notification to notification.  It is usually used to
//		provide the developer with some feed back on the cell events and sometimes to
//		ask the developer if given event is to be accepted or not
//	Params:
//		ID			- celltype ID
//		col, row	- co-ordinates cell that is processing the message
//		msg			- message ID to identify current process
//		param		- additional iformation or object that might be needed
//	Return:
//		TRUE - to allow celltype event
//		FALSE - to disallow the celltype event
int MyCug::OnCellTypeNotify(long ID,int col,long row,long msg,long param)
{
	int retVal = CUGExcel::OnCellTypeNotify( ID, col, row, msg, param );
	// Translate column location
	col = GetColTranslation( col );
	// TODO: add your notification handling here

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////
//	OnEditStart
//		This message is sent whenever the grid is ready to start editing a cell
//	Params:
//		col, row - location of the cell that edit was requested over
//		edit -	pointer to a pointer to the edit control, allows for swap of edit control
//				if edit control is swapped permanently (for the whole grid) is it better
//				to use 'SetNewEditClass' function.
//	Return:
//		TRUE - to allow the edit to start
//		FALSE - to prevent the edit from starting
int MyCug::OnEditStart(int col, long row,CWnd **edit)
{
	int retVal = CUGExcel::OnEditStart( col, row, edit );
	// Translate column location
	col = GetColTranslation( col );
	// TODO: add your notification handling here

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////
//	OnEditVerify
//		This notification is sent every time the user hits a key while in edit mode.
//		It is mostly used to create custom behavior of the edit contol, because it is
//		so eazy to allow or disallow keys hit.
//	Params:
//		col, row	- location of the edit cell
//		edit		-	pointer to the edit control
//		vcKey		- virtual key code of the pressed key
//	Return:
//		TRUE - to accept pressed key
//		FALSE - to do not accept the key
int MyCug::OnEditVerify(int col, long row,CWnd *edit,UINT *vcKey)
{
	int retVal = CUGExcel::OnEditVerify( col, row, edit, vcKey );
	// Translate column location
	col = GetColTranslation( col );
	// TODO: add your notification handling here

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////
//	OnEditFinish
//		This notification is sent when the edit is being finised
//	Params:
//		col, row	- coordinates of the edit cell
//		edit		- pointer to the edit control
//		string		- actual string that user typed in
//		cancelFlag	- indicates if the edit is being cancelled
//	Return:
//		TRUE - to allow the edit it proceede
//		FALSE - to force the user back to editing of that same cell
int MyCug::OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag)
{
	int retVal = CUGExcel::OnEditFinish( col, row, edit, string, cancelFlag );
	// Translate column location
	col = GetColTranslation( col );
	// TODO: add your notification handling here

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////
//	OnEditContinue
//		This notification is called when the user pressed 'tab' or 'enter' keys
//		Here you have a chance to modify the destination cell
//	Params:
//		oldcol, oldrow - edit cell that is loosing edit focus
//		newcol, newrow - cell that the edit is going into, by changing their
//							values you are able to change where to edit next
//	Return:
//		TRUE - allow the edit to continue
//		FALSE - to prevent the move, the edit will be stopped
int MyCug::OnEditContinue(int oldcol,long oldrow,int* newcol,long* newrow)
{
	int retVal = CUGExcel::OnEditContinue( oldcol, oldrow, newcol, newrow );
	// Translate column location
	oldcol = GetColTranslation( oldcol );
	// TODO: add your notification handling here

	// when user moves from cell to cell using keyboard (TAB, arrows, return keys)
	// than move to the new cell without starting edit
	retVal = FALSE;
	m_GI->m_multiSelect->StartBlock( *newcol, *newrow );
	GotoCell( *newcol, *newrow );

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////
//	OnMenuCommand
//		This notification is called when the user has selected a menu item
//		in the pop-up menu.
//	Params:
//		col, row - the cell coordinates of where the menu originated from
//		setcion - identify for which portion of the gird the menu is for.
//				  possible sections:
//						UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
//						UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
//		item - ID of the menu item selected
//	Return:
//		<none>
void MyCug::OnMenuCommand(int col,long row,int section,int item)
{
	CUGExcel::OnMenuCommand( col, row, section, item );
	// Translate column location
	col = GetColTranslation( col );
	// TODO: add your notification handling here
}

/////////////////////////////////////////////////////////////////////////////
//	OnMenuStart
//		Is called when the pop up menu is about to be shown
//	Params:
//		col, row	- the cell coordinates of where the menu originated from
//		setcion		- identify for which portion of the gird the menu is for.
//					possible sections:
//						UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
//						UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
//	Return:
//		TRUE - to allow menu to show
//		FALSE - to prevent the menu from poping up
int MyCug::OnMenuStart(int col,long row,int section)
{
	int retVal = CUGExcel::OnMenuStart( col, row, section );
	// Translate column location
	col = GetColTranslation( col );
	// TODO: add your notification handling here

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////
//	OnGetContextHelpID 
//		this notification is called as result of context help bing activated
//		over the UG area
//	Params:
//		col, row	- coordinates of cell which received the message
//		section		- grid section which received this message
//	Return:
//		Context help ID to be shown in the help.
DWORD MyCug::OnGetContextHelpID( int col, long row, int section )
{
	DWORD retVal = CUGExcel::OnGetContextHelpID( col, row, section );
	// Translate column location
	col = GetColTranslation( col );
	// TODO: add your notification handling here

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////
//	OnHint
//		Is called whent the hint is about to be displayed on the main grid area,
//		here you have a chance to set the text that will be shown
//	Params:
//		col, row	- the cell coordinates of where the menu originated from
//		string		- pointer to the string that will be shown
//	Return:
//		TRUE - to show the hint
//		FALSE - to prevent the hint from showing
int MyCug::OnHint(int col,long row,int section,CString *string)
{
	int retVal = CUGExcel::OnHint( col, row, section, string );
	// Translate column location
	col = GetColTranslation( col );
	// TODO: add your notification handling here

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////
//	OnVScrollHint
//		Is called whent the hint is about to be displayed on the vertical scroll bar,
//		here you have a chance to set the text that will be shown
//	Params:
//		row		- current top row
//		string	- pointer to the string that will be shown
//	Return:
//		TRUE - to show the hint
//		FALSE - to prevent the hint from showing
int MyCug::OnVScrollHint(long row,CString *string)
{
	int retVal = CUGExcel::OnVScrollHint( row, string );
	// TODO: add your notification handling here

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////
//	OnHScrollHint
//		Is called whent the hint is about to be displayed on the horizontal scroll bar,
//		here you have a chance to set the text that will be shown
//	Params:
//		col		- current left col
//		string	- pointer to the string that will be shown
//	Return:
//		TRUE - to show the hint
//		FALSE - to prevent the hint from showing
int MyCug::OnHScrollHint(int col,CString *string)
{
	int retVal = CUGExcel::OnHScrollHint( col, string );
	// Translate column location
	col = GetColTranslation( col );
	// TODO: add your notification handling here

	return retVal;
}

#ifdef __AFXOLE_H__
/////////////////////////////////////////////////////////////////////////////
//	OLE
//		following 3 functions are to be used with drag and drop functionality
/////////////////////////////////////////////////////////////////////////////
//	OnDragEnter
//	Params:
//		pDataObject - 
//	Return:
//		DROPEFFECT_NONE - no drag and drop
//		DROPEFFECT_COPY - allow drag and drop for copying
DROPEFFECT MyCug::OnDragEnter(COleDataObject* pDataObject)
{
	DROPEFFECT retVal = CUGExcel::OnDragEnter( pDataObject );
	// TODO: add your notification handling here

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////
//	OnDragOver
//	Params:
//		col, row	-
//		pDataObject - 
//	Return:
//		DROPEFFECT_NONE - no drag and drop
//		DROPEFFECT_COPY - allow drag and drop for copying
DROPEFFECT MyCug::OnDragOver(COleDataObject* pDataObject,int col,long row)
{
	DROPEFFECT retVal = CUGExcel::OnDragOver( pDataObject, col, row );
	// Translate column location
	col = GetColTranslation( col );
	// TODO: add your notification handling here

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////
//	OnDragDrop
//	Params:
//		col, row	-
//		pDataObject - 
//	Return:
//		DROPEFFECT_NONE - no drag and drop
//		DROPEFFECT_COPY - allow drag and drop for copying
DROPEFFECT MyCug::OnDragDrop(COleDataObject* pDataObject,int col,long row)
{
	DROPEFFECT retVal = CUGExcel::OnDragDrop( pDataObject, col, row );
	// Translate column location
	col = GetColTranslation( col );
	// TODO: add your notification handling here

	return retVal;
}
#endif

/////////////////////////////////////////////////////////////////////////////
//	OnScreenDCSetup
//		Is called when each of the components are painted.
//	Params:
//		dc		- pointer to the current CDC object
//		section	- section of the grid painted.
//					possible sections:
//						UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
//						UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
//	Return:
//		<none>
void MyCug::OnScreenDCSetup(CDC *dc,int section)
{
	CUGExcel::OnScreenDCSetup( dc, section );
	// TODO: add your notification handling here
}

/////////////////////////////////////////////////////////////////////////////
//	OnSortEvaluate
//		Sent as a result of the 'SortBy' call, this is called for each cell
//		comparison and allows for customization of the sorting routines.
//		We provide following code as example of what could be done here,
//		you migh have to modify it to give your application customized sorting.
//	Params:
//		cell1, cell2	- pointers to cells that are compared
//		flags			- identifies sort direction
//	Return:
//		value less than zero to identify that the cell1 comes before cell2
//		value equal to zero to identify that the cell1 and cell2 are equal
//		value greater than zero to identify that the cell1 comes after cell2
int MyCug::OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags)
{
	int retVal = CUGExcel::OnSortEvaluate( cell1, cell2, flags );
	// TODO: add your notification handling here

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////
//	OnTabSelected
//		Called when the user selects one of the tabs on the bottom of the screen
//	Params:
//		ID	- id of selected tab
//	Return:
//		<none>
void MyCug::OnTabSelected(int ID)
{
	CUGExcel::OnTabSelected( ID );
	// TODO: add your notification handling here
	SetSheetNumber( ID - 1 );
}

/////////////////////////////////////////////////////////////////////////////
//	OnAdjustComponentSizes
//		Called when the grid components are baing arranged.
//	Params:
//		grid, topHdg, sideHdg, cnrBtn, vScroll, hScroll, 
//		tabs	- sizes and location of each of the grid components
//	Return:
//		<none>
void MyCug::OnAdjustComponentSizes(RECT *grid,RECT *topHdg,RECT *sideHdg,
		RECT *cnrBtn,RECT *vScroll,RECT *hScroll,RECT *tabs)
{
	CUGExcel::OnAdjustComponentSizes( grid, topHdg, sideHdg, cnrBtn, vScroll, hScroll, tabs );
	// TODO: add your notification handling here
} 

/////////////////////////////////////////////////////////////////////////////
//	OnDrawFocusRect
//		Called when the focus rect needs to be painted.
//	Params:
//		dc		- pointer to the current CDC object
//		rect	- rect of the cell that requires the focus rect
//	Return:
//		<none>
void MyCug::OnDrawFocusRect(CDC *dc,RECT *rect)
{	
	CUGExcel::OnDrawFocusRect( dc, rect );
}

/////////////////////////////////////////////////////////////////////////////
//	OnGetDefBackColor
//		Sent when the area behind the grid needs to be paindted.
//	Params:
//		section - Id of the grid section that requested this color
//				  possible sections:
//						UG_TOPHEADING, UG_SIDEHEADING, UG_GRID
//	Return:
//		RGB value representing the color of choice
COLORREF MyCug::OnGetDefBackColor(int section)
{
	COLORREF retVal = CUGExcel::OnGetDefBackColor( section );
	// TODO: add your notification handling here

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////
//	OnSetFocus
//		Sent when the grid is gaining focus.
//	Params:
//		section - Id of the grid section gaining focus, usually UG_GRID
//				  possible sections:
//						UG_TOPHEADING, UG_SIDEHEADING, UG_GRID
//	Return:
//		<none>
//
//	Note:
//		The grid will loose focus when the edit is started, of drop list shown
void MyCug::OnSetFocus(int section)
{
	CUGExcel::OnSetFocus( section );
	// TODO: add your notification handling here
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
void MyCug::OnKillFocus(int section)
{
	CUGExcel::OnKillFocus( section );
	// TODO: add your notification handling here
}

/////////////////////////////////////////////////////////////////////////////
//	OnColSwapStart
//		Called to inform the grid that the col swap was started on given col.
//	Params:
//		col - identifies the column
//	Return:
//		TRUE - to allow for the swap to take place
//		FALSE - to disallow the swap
BOOL MyCug::OnColSwapStart(int col)
{
	BOOL retVal = CUGExcel::OnColSwapStart( col );
	// TODO: add your notification handling here

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////
//	OnCanColSwap
//		Called when col swap is about to take place, here you can 'lock' certain
//		cols in place so that are not swapable.
//	Params:
//		fromCol - where the col orriginated from
//		toCol	- where the col will be located if the swap is allowed
//	Return:
//		TRUE - to allow for the swap to take place
//		FALSE - to disallow the swap
BOOL MyCug::OnCanColSwap(int fromCol,int toCol)
{
	BOOL retVal = CUGExcel::OnCanColSwap( fromCol, toCol );
	// Translate column location
	fromCol = GetColTranslation( fromCol );
	toCol = GetColTranslation( toCol );
	// TODO: add your notification handling here

	return retVal;
}

/////////////////////////////////////////////////////////////////////////////
//	OnTrackingWindowMoved
//		Called to notify the grid that the tracking window was moved
//	Params:
//		origRect	- from
//		newRect		- to location and size of the track window
//	Return:
//		<none>
void MyCug::OnTrackingWindowMoved(RECT *origRect,RECT *newRect)
{
	CUGExcel::OnTrackingWindowMoved( origRect, newRect );
	// TODO: add your notification handling here
}

