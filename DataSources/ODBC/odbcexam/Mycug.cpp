/***************************************************
****************************************************
Skeleton Class for a Derived MyCug
****************************************************
****************************************************/

/***************************************************
This is the MyCug CUGCtrl derived class with the 
addition of TRACE statements to allow the various
notification sequences to be seen in the output 
window.  The OnMouseMove and OnGetCell notification
TRACE statements are commented out so as to reduce 
the clutter!  
****************************************************/

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


/***************************************************
****************************************************/
MyCug::MyCug()
{
	//TRACE("MyCug: Constructor called.\n");
}
/***************************************************
****************************************************/
MyCug::~MyCug()
{
	//TRACE("MyCug: Destructor called.\n");
}

/***************************************************
OnSetup
	This function is called just after the grid window 
	is created or attached to a dialog item.
	It can be used to initially setup the grid
****************************************************/
void MyCug::OnSetup(){
	//TRACE("MyCug: OnSetup called.\n");


	EnableColSwapping(TRUE);
	CUGEdit *edit = (CUGEdit*)GetEditClass();
	edit->SetAutoSize(FALSE);
}

/***************************************************
OnSheetSetup	
****************************************************/
void MyCug::OnSheetSetup(int sheetNumber){
	//TRACE("MyCug: OnSheetSetup called for sheet %d.\n", sheetNumber);
}

/***************************************************
OnCanMove
	Sent when the current cell in the grid is about
	to move
	A return of TRUE allows the move, a return of
	FALSE stops the move
****************************************************/
int MyCug::OnCanMove(int oldcol,long oldrow,int newcol,long newrow){
	//TRACE("MyCug: OnCanMove called with oldcol = %d, oldrow = %ld, newcol = %d, newrow = %ld.\n", oldcol, oldrow, newcol, newrow);
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
	//TRACE("MyCug: OnCanViewMove called with oldcol = %d, oldrow = %ld, newcol = %d, newrow = %ld.\n", oldcol, oldrow, newcol, newrow);
	return TRUE;
}
/***************************************************
****************************************************/
void MyCug::OnHitBottom(long numrows,long rowspast,long rowsfound){
	//TRACE("MyCug: OnHitBottom called with numrows = %d, rowspast = %ld, rowsfound = %ld.\n",numrows, rowspast, rowsfound);

	if(rowsfound >0){
		SetNumberRows(numrows+rowsfound,FALSE);
	}

}
/***************************************************
****************************************************/
void MyCug::OnHitTop(long numrows,long rowspast){
	//TRACE("MyCug: OnHitTop called with numrows = %d, rowspast = %ld\n",numrows, rowspast);
}
/***************************************************
OnCanSizeCol
	Sent when the user is over a separation line on
	the top heading
	A return value of TRUE allows the possibiliy of
	a resize
****************************************************/
int MyCug::OnCanSizeCol(int col){
	//TRACE("MyCug: OnCanSizeCol called for col = %d.\n", col);
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
	//TRACE("MyCug: OnColSizing called for col = %d.\n", col);
}
/***************************************************
OnColSized
	This is sent when the user finished sizing the 
	given column (see above for more details)
****************************************************/
void MyCug::OnColSized(int col,int *width){
	//TRACE("MyCug: OnColSized called for col = %d.\n", col);
}
/***************************************************
OnCanSizeRow
	Sent when the user is over a separation line on
	the side heading
	A return value of TRUE allows the possibiliy of
	a resize
****************************************************/
int  MyCug::OnCanSizeRow(long row){
	//TRACE("MyCug: OnCanSizeRow called for row = %ld.\n", row);
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
	//TRACE("MyCug: OnRowSizing called for row = %ld.\n", row);
}
/***************************************************
OnRowSized
	This is sent when the user is finished sizing hte
	given row ( see above for more details)
****************************************************/
void MyCug::OnRowSized(long row,int *height){
	//TRACE("MyCug: OnRowSized called for row = %ld.\n", row);
}
/***************************************************
OnCanSizeSideHdg
	This is sent when the user moves into position 
	for sizing the width of the side heading
	return TRUE to allow the sizing
	or FALSE to not allow it
****************************************************/
int MyCug::OnCanSizeSideHdg(){
	//TRACE("MyCug: OnCanSizeSideHdg called.\n");
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
	//TRACE("MyCug: OnCanSizeTopHdg called.\n");
	return TRUE;
}
/***************************************************
OnSideHdgSizing
****************************************************/
int MyCug::OnSideHdgSizing(int *width){
	//TRACE("MyCug: OnSideHdgSizing called.\n");
	return TRUE;

}
/***************************************************
OnSideHdgSized
****************************************************/
int MyCug::OnSideHdgSized(int *width){
	//TRACE("MyCug: OnSizeHdgSized called.\n");
	return TRUE;
}
/***************************************************
OnTopHdgSized
****************************************************/
int MyCug::OnTopHdgSized(int *height){
	//TRACE("MyCug: OnTopHdgSized called.\n");
	return TRUE;
}
/***************************************************
OnTopHdgSizing
****************************************************/
int MyCug::OnTopHdgSizing(int *height){
	//TRACE("MyCug: OnTopHdgSizing called.\n");
	return TRUE;
}
/***************************************************
OnColChange
	Sent whenever the current column changes
	The old and the new columns are given
****************************************************/
void MyCug::OnColChange(int oldcol,int newcol){
	//TRACE("MyCug: OnColChange called with oldcol = %d, newcol = %d\n", oldcol, newcol);
}
/***************************************************
OnRowChange
	Sent whenever the current row changes
	The old and the new rows are given
****************************************************/
void MyCug::OnRowChange(long oldrow,long newrow){
	//TRACE("MyCug: OnRowChange called with oldrow = %ld, newrow = %ld\n", oldrow, newrow);
}
/***************************************************
OnCellChange
	Sent whenever the current cell changes rows or
	columns
****************************************************/
void MyCug::OnCellChange(int oldcol,int newcol,long oldrow,long newrow){
	//TRACE("MyCug: OnCellChange called with oldcol = %d, oldrow = %ld, newcol = %d, newrow = %ld.\n", oldcol, oldrow, newcol, newrow);
}
/***************************************************
OnLeftColChange
	Sent whenever the left visible column in the grid 
	changes
****************************************************/
void MyCug::OnLeftColChange(int oldcol,int newcol){
	//TRACE("MyCug: OnLeftColChange called with oldcol = %d, newcol = %d.\n", oldcol, newcol);
}
/***************************************************
OnTopRowChange
	Sent whenever the top visible row in the grid changes
****************************************************/
void MyCug::OnTopRowChange(long oldrow,long newrow){
	//TRACE("MyCug: OnTopRowChange called with oldrow = %ld, newrow = %ld.\n", oldrow, newrow);
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
void MyCug::OnLClicked(int col,long row,int updn,RECT *rect,POINT *point,int processed){
	//TRACE("MyCug: OnLClicked called with col = %d, row = %ld, updn = %d, processed = %d\n",col, row, updn, processed);
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
void MyCug::OnRClicked(int col,long row,int updn,RECT *rect,POINT *point,int processed){
	//TRACE("MyCug: OnRClicked called with col = %d, row = %ld, updn = %d, processed = %d\n",col, row, updn, processed);
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
void MyCug::OnDClicked(int col,long row,RECT *rect,POINT *point,int processed){
	//TRACE("MyCug: OnDClicked called with col = %d, row = %ld, processed = %d\n",col, row, processed);

	StartEdit();
}				 
/***************************************************
OnMouseMove
****************************************************/
void MyCug::OnMouseMove(int col,long row,POINT *point,UINT nFlags,BOOL processed){
//	TRACE("MyCug: OnMouseMove called with col = %d, row = %ld, processed = %d\n",
//		col, row, processed);
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
	//TRACE("MyCug: OnTH_LClicked called with col = %d, row = %ld, updn = %d, processed = %d\n",col, row, updn, processed);
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
	//TRACE("MyCug: OnTH_RClicked called with col = %d, row = %ld, updn = %d, processed = %d\n",col, row, updn, processed);
}
/***************************************************
OnTH_DClicked
	Sent whenever the user double clicks the left mouse
	button within the top heading

	'col' is negative if the area clicked in is not valid
****************************************************/
void MyCug::OnTH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed){
	//TRACE("MyCug: OnTH_DClicked called with col = %d, row = %ld, processed = %d\n",col, row, processed);

	m_sortCol = col;

	col = GetColTranslation(col);

	// lets sort the column in descending order...
	CODBCFieldInfo   FieldInfo;
	CString FieldName;
	m_odbc.GetRecordset()->GetODBCFieldInfo(col, FieldInfo);
	
	if(SQL_LONGVARCHAR == FieldInfo.m_nSQLType 
		|| SQL_BINARY == FieldInfo.m_nSQLType
		|| SQL_VARBINARY == FieldInfo.m_nSQLType
		|| SQL_LONGVARBINARY == FieldInfo.m_nSQLType)
		return;		// can't sort memos or pictures etc...

	FieldName = FieldInfo.m_strName;

	m_odbc.GetRecordset()->m_strSort = "[" + FieldName + "] DESC";

	SetNumberRows(0);
	SetNumberCols(0);

	m_odbc.GetRecordset()->Requery();
	SetGridUsingDataSource(GetDefDataSource());

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
	//TRACE("MyCug: OnSH_LClicked called with col = %d, row = %ld, updn = %d, processed = %d\n",col, row, updn, processed);
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
	//TRACE("MyCug: OnSH_RClicked called with col = %d, row = %ld, updn = %d, processed = %d\n",col, row, updn, processed);

}
/***************************************************
OnSH_DClicked
	Sent whenever the user double clicks the left mouse
	button within the side heading

	'row' is negative if the area clicked in is not valid
****************************************************/
void MyCug::OnSH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed){
	//TRACE("MyCug: OnSH_DClicked called with col = %d, row = %ld, processed = %d\n",col, row, processed);
	DeleteRow(row);
	RedrawAll();
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
	//TRACE("MyCug: OnCB_LClicked called with processed = %d\n",processed);
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
	//TRACE("MyCug: OnCB_RClicked called with processed = %d\n",processed);
}
/***************************************************
OnCB_DClicked
	Sent whenever the user double clicks the left mouse
	button within the top corner button
****************************************************/
void MyCug::OnCB_DClicked(RECT *rect,POINT *point,BOOL processed){
	//TRACE("MyCug: OnCB_DClicked called with processed = %d\n",processed);

	// append an array of cells...
	int cols = m_odbc.GetNumCols();

	CUGCell **cellArray;

	// make array of cell pointers
	cellArray = new CUGCell*[cols];
		
	// fill with pointers to new cells
	int i = 0;
	for (i = 0; i < cols; i++)		// will throw, but rarely...
		cellArray[i] = new CUGCell;


	// set some text...
	for (i = 0; i < cols; i++) {
		cellArray[i]->SetText(_T("Test677s73"));
	}

	// call append row...
	if(m_odbc.AppendRow(cellArray, cols)==UG_SUCCESS) {
		SetNumberRows(m_GI->m_numberRows + 1);
		GotoRow(m_GI->m_numberRows -1);
	}


	// delete cells...
	for (i = 0; i < cols; i++) {
		delete cellArray[i];
		cellArray[i] = NULL;
	}

	// delete array of pointers
	delete [] cellArray;
   	cellArray = NULL;

	RedrawAll();



}
/***************************************************
OnKeyDown
	Sent whenever the user types when the grid has
	focus. The keystroke can be modified here as well.
	(See WM_KEYDOWN for more information)
****************************************************/
void MyCug::OnKeyDown(UINT *vcKey,BOOL processed){
	//TRACE("MyCug: OnKeyDown called with *vcKey = %d, processed = %d\n", *vcKey, processed);
}
/***************************************************
OnCharDown
	Sent whenever the user types when the grid has
	focus. The keystroke can be modified here as well.
	(See WM_CHAR for more information)
****************************************************/
void MyCug::OnCharDown(UINT *vcKey,BOOL processed){
	//TRACE("MyCug: OnCharDown called with *vcKey = %d, processed = %d\n", *vcKey, processed);
}
	
/***************************************************
OnGetCell
	This message is sent everytime the grid needs to
	draw a cell in the grid. At this point the cell
	class has been filled with the information to be
	used to draw the cell. The information can now be
	changed before it is used for drawing
****************************************************/
void MyCug::OnGetCell(int col,long row,CUGCell *cell){
//	TRACE("MyCug: OnGetCell called with col = %d, row = %ld\n", col, row);	
//	if (row == -1 ) {
//		if (col == m_sortCol) {
//			cell->SetText("Hello");
//		}
//		else {
//			cell->SetText(" ");
//		}
//	}


}
/***************************************************
OnSetCell
	This message is sent everytime the a cell is about 
	to change.
****************************************************/
void MyCug::OnSetCell(int col,long row,CUGCell *cell){
	//TRACE("MyCug: OnSetCell called with col = %d, row = %ld\n", col, row);	
}
/***************************************************
OnDataSourceNotify
	This message is sent from a data source , message
	depends on the data source - check the information
	on the data source(s) being used
	- The ID of the Data source is also returned
****************************************************/
void MyCug::OnDataSourceNotify(int ID,long msg,long param){
	//TRACE("MyCug: OnDataSourceNotify called with ID = %d, msg = %ld, param = %ld\n",ID, msg, param);	
}
/***************************************************
OnCellTypeNotify
	This message is sent from a cell type , message
	depends on the cell type - check the information
	on the cell type classes
	- The ID of the cell type is given
****************************************************/
int MyCug::OnCellTypeNotify(long ID,int col,long row,long msg,long param){
	//TRACE("MyCug: OnCellTypeNotify called with ID = %d, col = %d, row = %ld, msg = %ld, param = %ld\n",ID, col, row, msg, param);	
	return 0;
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
	//TRACE("MyCug: OnEditStart called with col = %d, row = %ld\n", col, row);
	return TRUE;
}
/***************************************************
OnEditVerify
	This is send when the editing is about to end
****************************************************/
int MyCug::OnEditVerify(int col, long row,CWnd *edit,UINT *vcKey){
	//TRACE("MyCug: OnEditVerify called with col = %d, row = %ld, vcKey = %d\n", col, row, *vcKey);

	return TRUE;
}
/***************************************************
OnEditFinish this is send when editing is finished
****************************************************/
int MyCug::OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag){
	//TRACE("MyCug: OnEditFinish called with col = %d, row = %ld, string = %s, cancelFlag = %d\n",col, row, string, cancelFlag);
	return TRUE;
}
/***************************************************
OnEditFinish this is send when editing is finished
****************************************************/
int MyCug::OnEditContinue(int oldcol,long oldrow,int* newcol,long* newrow){
	//TRACE("MyCug: OnEditContinue called with oldcol = %d, oldrow = %ld, newcol = %d, newrow = %ld\n",oldcol, oldrow, *newcol, *newrow );
	return TRUE;
}
/***************************************************
sections - UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
			UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
****************************************************/
void MyCug::OnMenuCommand(int col,long row,int section,int item){
	//TRACE("MyCug: OnMenuCommand called with col = %d, row = %ld, section = %d, item = %d\n",col, row, section, item);
}
/***************************************************
return UG_SUCCESS to allow the menu to appear
return 1 to not allow the menu to appear
****************************************************/
int MyCug::OnMenuStart(int col,long row,int section){
	//TRACE("MyCug: OnMenuStart called with col = %d, row = %ld, section = %d\n",col, row, section);
	return TRUE;
}
/***************************************************
OnHint
****************************************************/
int MyCug::OnHint(int col,long row,int section,CString *string){
	//TRACE("MyCug: OnHint called with col = %d, row = %ld, section = %d, *string = %s\n",col, row, section, (LPCTSTR)*string); 
	string->Format(_T("Col:%d Row:%ld"),col,row);
	return TRUE;
}
/***************************************************
OnVScrollHint
****************************************************/
int MyCug::OnVScrollHint(long row,CString *string){
	//TRACE("MyCug: OnVScrollHint called with row = %ld, *string = %s\n",row, (LPCTSTR)*string);
	return TRUE;
}
/***************************************************
OnHScrollHint
****************************************************/
int MyCug::OnHScrollHint(int col,CString *string){
	//TRACE("MyCug: OnHScrollHint called with col = %ld, *string = %s\n",col, (LPCTSTR)*string);
	return TRUE;
}

/*********************************************
OLE
**********************************************/
#ifdef __AFXOLE_H__

/***************************************************
****************************************************/
DROPEFFECT  MyCug::OnDragEnter(COleDataObject* pDataObject){
	//TRACE("MyCug: OnDragEnter called.\n");
	return DROPEFFECT_NONE;
}
/***************************************************
****************************************************/
DROPEFFECT  MyCug::OnDragOver(COleDataObject* pDataObject,int col,long row){
	//TRACE("MyCug: OnDragOver called with col = %d, row = %ld.\n",col, row);
	return DROPEFFECT_NONE;
}
/***************************************************
****************************************************/
DROPEFFECT  MyCug::OnDragDrop(COleDataObject* pDataObject,int col,long row){
	//TRACE("MyCug: OnDragDrop called with col = %d, row = %ld.\n",col, row);
	return DROPEFFECT_NONE;
}
#endif
/***************************************************
****************************************************/
void MyCug::OnScreenDCSetup(CDC *dc,int section){
	//TRACE("MyCug: OnScreenDCSetup called with section = %d\n", section);
}
/***************************************************
OnSortEvaluate
return		-1  <
			0	==
			1	>
****************************************************/
int MyCug::OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags){
	//TRACE("MyCug: OnSortEvaluate called.\n");
	return _tcscmp(cell1->GetText(),cell2->GetText());
}

/***************************************************
OnTabSelected
****************************************************/
void MyCug::OnTabSelected(int ID){
	//TRACE("MyCug: OnTabSelected called with ID = %d\n", ID);
}

/***************************************************
OnAdjustComponentSizes
****************************************************/
void MyCug::OnAdjustComponentSizes(RECT *grid,RECT *topHdg,RECT *sideHdg,
		RECT *cnrBtn,RECT *vScroll,RECT *hScroll,RECT *tabs){
	//TRACE("MyCug: OnAdjustComponentSizes called.\n");
} 

/***************************************************
OnDrawFocusRect
****************************************************/
void MyCug::OnDrawFocusRect(CDC *dc,RECT *rect){
	//TRACE("MyCug: OnDrawFocusRect called.\n");
	//DrawExcelFocusRect(dc,rect);
	
	rect->bottom --;
	rect->right --;
	dc->DrawFocusRect(rect);
}

/***************************************************
OnGetDefBackColor
****************************************************/
COLORREF MyCug::OnGetDefBackColor(int section){
	//TRACE("MyCug: OnGetDefBackColor called with section = %d\n", section);
	return RGB(255,255,255);
}
/***************************************************
OnSetFocus
****************************************************/
void MyCug::OnSetFocus(int section){
	//TRACE("MyCug: OnSetFocus called with section = %d\n", section);
}

/***************************************************
OnKillFocus
****************************************************/
void MyCug::OnKillFocus(int section){
	//TRACE("MyCug: OnKillFocus called with section = %d\n", section);
}
/***************************************************
OnColSwapStart
****************************************************/
BOOL MyCug::OnColSwapStart(int col){
	//TRACE("MyCug: OnColSwapStart called with col = %d\n", col);
	return TRUE;
}

/***************************************************
OnCanColSwap
****************************************************/
BOOL MyCug::OnCanColSwap(int fromCol,int toCol){
	//TRACE("MyCug: OnCanColSwap called with fromCol = %d, toCol = %d\n",fromCol, toCol);
	return TRUE;
}
/***************************************************
OnTrackingWindowMoved
****************************************************/
void MyCug::OnTrackingWindowMoved(RECT *origRect,RECT *newRect){
	//TRACE("MyCug: OnTrackingWindowMoved called.\n");
}

