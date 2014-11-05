/***********************************************
	Ultimate Grid version 7.2

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

	Class 
		CUGAccessCtrl
	Purpose
		This class is derived from the grid's main
		base class CUGCtrl. 
**********************************************/

#include "stdafx.h"
#include "resource.h"
#include "UGAccess.h"
#include "ugdao.h"

BEGIN_MESSAGE_MAP(CUGAccessCtrl,CUGCtrl)
	//{{AFX_MSG_MAP(CUGAccessCtrl)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/***************************************************
****************************************************/
CUGAccessCtrl::CUGAccessCtrl()
{
	m_arrowCursor = FALSE;
	m_bUpdateFailed = FALSE;
	m_nExtraRow = -1;
	// important to init this so that OnHitBottom will detect
	// that it should force EOF


}
/***************************************************
****************************************************/
CUGAccessCtrl::~CUGAccessCtrl()
{
	DestroyCursor( m_excelArrow);
	DestroyCursor( m_excelWEResize);
	DestroyCursor( m_excelNSResize);

	
}

/***************************************************
OnSetup
	This function is called just after the grid window 
	is created or attached to a dialog item.
	It can be used to initially setup the grid
****************************************************/
void CUGAccessCtrl::OnSetup(){

	// regular font for cells
	m_font.CreateFont(16,0,0,0,500,0,0,0,0,0,0,0,0,_T("Arial"));
	// bold font for top heading - see OnGetCell()
	m_thFont.CreateFont(16,0,0,0,700,0,0,0,0,0,0,0,0,_T("Arial"));
	
	SetDefFont(&m_font);

	//m_excelArrow = LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_CURSOR2));
	m_excelArrow	 = LoadCursor(NULL,IDC_IBEAM);
	m_excelWEResize  = LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_CURSOR3));
	m_excelNSResize  = LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_CURSOR1));

	SetArrowCursor(m_excelArrow);
	SetWESizingCursor(m_excelWEResize);
	SetNSSizingCursor(m_excelNSResize);

	EnableMenu(1);	



 	EnableColSwapping(true);
	
//	SetMultiSelectMode(1);

	EnableCellOverLap(FALSE);

	UseVScrollHints(TRUE);

	// set the desired font for the hint class.  This affects only
	// the v and h scroll hints - the grid hints are tooltips.
	m_hintFont.CreateFont(14,0,0,0,400,0,0,0,0,0,0,0,0,_T("MS Sans Serif"));
	m_CUGHint->SetFont(&m_hintFont);

//	m_pTopHdg = new CAccessTopHdng; 
//	m_pSideHdg = new CAccessSideHdng;

//	RECT rect ={0,0,0,0};
//	m_pTopHdg->Create(NULL,_T(""),WS_CHILD|WS_VISIBLE,rect,this,2222,NULL);
//	m_pSideHdg->Create(NULL,_T(""),WS_CHILD|WS_VISIBLE,rect,this,3333,NULL);
//
//	SetNewTopHeadingClass(m_pTopHdg);
//	SetNewSideHeadingClass(m_pSideHdg);

	SetUniformRowHeight(TRUE);

}

/***************************************************
****************************************************/
void CUGAccessCtrl::OnMouseMove(int col,long row,POINT *point,UINT nFlags,BOOL processed){

	RECT rect;
	

	GetCellFromPoint(point->x, point->y, &col, &row, &rect);
	if(point->x > rect.right || point->y > rect.bottom)	{		// we're in the client area...
		SetCursor(LoadCursor(NULL,IDC_ARROW));
		m_arrowCursor = TRUE;
		return;
	}

	if(col == GetCurrentCol() && row == GetCurrentRow()){
		GetCellRect(col,row,&rect);
		if(point->x < rect.left +4 || point->x > rect.right -4){
			m_arrowCursor = TRUE;
			SetArrowCursor(LoadCursor(NULL,IDC_ARROW));
			SetCursor(LoadCursor(NULL,IDC_ARROW));
			return;
		}
		else if(point->y < rect.top +4 || point->y > rect.bottom -4){
			m_arrowCursor = TRUE;
			SetArrowCursor(LoadCursor(NULL,IDC_ARROW));
			SetCursor(LoadCursor(NULL,IDC_ARROW));
			return;
		}
	}
	if(m_arrowCursor){
		SetArrowCursor(m_excelArrow);
		SetCursor(m_excelArrow);
		m_arrowCursor = FALSE;
		return;
	}
	
}

/***************************************************
OnCanMove
	Sent when the current cell in the grid is about
	to move
	A return of TRUE allows the move, a return of
	FALSE stops the move
****************************************************/
int CUGAccessCtrl::OnCanMove(int oldcol,long oldrow,int newcol,long newrow){
	return TRUE;
}
/***************************************************
OnCanMove
	Sent when the top row or left column in the grid is about
	to move
	A return of TRUE allows the move, a return of
	FALSE stops the move
****************************************************/
int CUGAccessCtrl::OnCanViewMove(int oldcol,long oldrow,int newcol,long newrow){
	return TRUE;
}
/***************************************************
****************************************************/
void CUGAccessCtrl::OnHitBottom(long numrows,long rowspast,long rowsfound){
	// Important!
	if(rowsfound >0){
		SetNumberRows(numrows+rowsfound,FALSE);
	}

}
/***************************************************
****************************************************/
void CUGAccessCtrl::OnHitTop(long numrows,long rowspast){
}
/***************************************************
OnCanSizeCol
	Sent when the user is over a separation line on
	the top heading
	A return value of TRUE allows the possibiliy of
	a resize
****************************************************/
int CUGAccessCtrl::OnCanSizeCol(int col){
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
void CUGAccessCtrl::OnColSizing(int col,int *width){
}
/***************************************************
OnColSized
	This is sent when the user finished sizing the 
	given column (see above for more details)
****************************************************/
void CUGAccessCtrl::OnColSized(int col,int *width){
}
/***************************************************
OnCanSizeRow
	Sent when the user is over a separation line on
	the side heading
	A return value of TRUE allows the possibiliy of
	a resize
****************************************************/
int  CUGAccessCtrl::OnCanSizeRow(long row){
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
void CUGAccessCtrl::OnRowSizing(long row,int *height){
}
/***************************************************
OnRowSized
	This is sent when the user is finished sizing hte
	given row ( see above for more details)
****************************************************/
void CUGAccessCtrl::OnRowSized(long row,int *height){
}
/***************************************************
OnCanSizeSideHdg
	This is sent when the user moves into position 
	for sizing the width of the side heading
	return TRUE to allow the sizing
	or FALSE to not allow it
****************************************************/
int CUGAccessCtrl::OnCanSizeSideHdg(){
	return TRUE;
}
/***************************************************
OnCanSizeTopHdg
	This is sent when the user moves into position 
	for sizing the height of the top heading
	return TRUE to allow the sizing
	or FALSE to not allow it
****************************************************/
int CUGAccessCtrl::OnCanSizeTopHdg(){
	return TRUE;
}
/***************************************************
OnSideHdgSizing
****************************************************/
int CUGAccessCtrl::OnSideHdgSizing(int *width){
	return TRUE;

}
/***************************************************
OnTopHdgSizing
****************************************************/
int CUGAccessCtrl::OnTopHdgSizing(int *height){
	return TRUE;
}
/***************************************************
OnColChange
	Sent whenever the current column changes
	The old and the new columns are given
****************************************************/
void CUGAccessCtrl::OnColChange(int oldcol,int newcol){
}
/***************************************************
OnRowChange
	Sent whenever the current row changes
	The old and the new rows are given
****************************************************/
void CUGAccessCtrl::OnRowChange(long oldrow,long newrow){
//	TRACE("CUGAccessCtrl::OnRowChange  - oldrow = %ld,  newrow = %ld\r\n",
//		oldrow, newrow);

}
/***************************************************
OnCellChange
	Sent whenever the current cell changes rows or
	columns
****************************************************/
void CUGAccessCtrl::OnCellChange(int oldcol,int newcol,long oldrow,long newrow){
}
/***************************************************
OnLeftColChange
	Sent whenever the left visible column in the grid 
	changes
****************************************************/
void CUGAccessCtrl::OnLeftColChange(int oldcol,int newcol){
}
/***************************************************
OnTopRowChange
	Sent whenever the top visible row in the grid changes
****************************************************/
void CUGAccessCtrl::OnTopRowChange(long oldrow,long newrow){
}
/***************************************************
OnLClicked
	Sent whenever the user clicks the left mouse
	button within the grid
	this message is sent when the button goes down
	then again when the button goes up

	'col' and 'row' are negitive if the area clicked
	in is not a valid cell
	'rect' the rectangle of the cell that was clicked in
	'point' the point where the mouse was clicked
	'updn'  TRUE if the button is down FALSE if the
	        button just when up
****************************************************/
void CUGAccessCtrl::OnLClicked(int col,long row,int updn,RECT *rect,POINT *point,int processed){

	if (!updn) 
		StartEdit();	
}
/***************************************************
OnRClicked
	Sent whenever the user clicks the right mouse
	button within the grid
	this message is sent when the button goes down
	then again when the button goes up

	'col' and 'row' are negitive if the area clicked
	in is not a valid cell
	'rect' the rectangle of the cell that was clicked in
	'point' the point where the mouse was clicked
	'updn'  TRUE if the button is down FALSE if the
	        button just when up
****************************************************/
void CUGAccessCtrl::OnRClicked(int col,long row,int updn,RECT *rect,POINT *point,int processed){
}
/***************************************************
OnDClicked
	Sent whenever the user double clicks the left mouse
	button within the grid

	'col' and 'row' are negitive if the area clicked
	in is not a valid cell
	'rect' the rectangle of the cell that was clicked in
	'point' the point where the mouse was clicked
****************************************************/
void CUGAccessCtrl::OnDClicked(int col,long row,RECT *rect,POINT *point,int processed){
	StartEdit();	
}				 
/***************************************************
OnTH_LClicked
	Sent whenever the user clicks the left mouse
	button within the top heading
	this message is sent when the button goes down
	then again when the button goes up

	'col' is negitive if the area clicked in is not valid
	'updn'  TRUE if the button is down FALSE if the
	        button just when up
****************************************************/
void CUGAccessCtrl::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed){

}
/***************************************************
OnTH_RClicked
	Sent whenever the user clicks the right mouse
	button within the top heading
	this message is sent when the button goes down
	then again when the button goes up

	'col' is negitive if the area clicked in is not valid
	'updn'  TRUE if the button is down FALSE if the
	        button just when up
****************************************************/
void CUGAccessCtrl::OnTH_RClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed){
}
/***************************************************
OnTH_LClicked
	Sent whenever the user double clicks the left mouse
	button within the top heading

	'col' is negitive if the area clicked in is not valid
****************************************************/
void CUGAccessCtrl::OnTH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed){

}
/***************************************************
OnSH_LClicked
	Sent whenever the user clicks the left mouse
	button within the side heading
	this message is sent when the button goes down
	then again when the button goes up

	'row' is negitive if the area clicked in is not valid
	'updn'  TRUE if the button is down FALSE if the
	        button just when up
****************************************************/
void CUGAccessCtrl::OnSH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed){

}
/***************************************************
OnSH_RClicked
	Sent whenever the user clicks the right mouse
	button within the side heading
	this message is sent when the button goes down
	then again when the button goes up

	'row' is negitive if the area clicked in is not valid
	'updn'  TRUE if the button is down FALSE if the
	        button just when up
****************************************************/
void CUGAccessCtrl::OnSH_RClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed){
}
/***************************************************
OnSH_DClicked
	Sent whenever the user double clicks the left mouse
	button within the side heading

	'row' is negitive if the area clicked in is not valid
****************************************************/
void CUGAccessCtrl::OnSH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed){
	DeleteRow(row);
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
void CUGAccessCtrl::OnCB_LClicked(int updn,RECT *rect,POINT *point,BOOL processed){
	
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
void CUGAccessCtrl::OnCB_RClicked(int updn, RECT *rect,POINT *point,BOOL processed){

}
/***************************************************
OnCB_DClicked
	Sent whenever the user double clicks the left mouse
	button within the top corner button
****************************************************/
void CUGAccessCtrl::OnCB_DClicked(RECT *rect, POINT *point,BOOL processed){
}
/***************************************************
OnKeyDown
	Sent whenever the user types when the grid has
	focus. The keystroke can be modified here as well.
	(See WM_KEYDOWN for more information)
****************************************************/
void CUGAccessCtrl::OnKeyDown(UINT *vcKey,int processed){
	if(*vcKey == VK_ESCAPE){}
//		TRACE("CUGAccessCtrl::OnKeyDown - ESC pressed\n");
	
}
/***************************************************
OnCharDown
	Sent whenever the user types when the grid has
	focus. The keystroke can be modified here as well.
	(See WM_CHAR for more information)
****************************************************/
void CUGAccessCtrl::OnCharDown(UINT *vcKey,int processed){
	if(*vcKey != VK_RETURN && *vcKey != VK_ESCAPE)
		if(!processed)
			StartEdit(*vcKey);
}
	
/***************************************************
OnGetCell
	This message is sent everytime the grid needs to
	draw a cell in the grid. At this point the cell
	class has been filled with the information to be
	used to draw the cell. The information can now be
	changed before it is used for drawing
****************************************************/
void CUGAccessCtrl::OnGetCell(int col,long row,CUGCell *cell){
	if (row < 0 )
		cell->SetFont(&m_thFont);

	if(-1 < row)
 	{
 		int type = 0;
 		// Change bool cell types to check box.
 		if ((CUGDAODataSource*)GetDataSource(GetDefDataSource())->GetColType(col, &type) == UG_SUCCESS)
 		{
			switch (type) {
			case 1:		// boolean
				cell->SetCellType(UGCT_CHECKBOX);
 				cell->SetCellTypeEx(UGCT_CHECKBOX3DRECESS) ;
				break;
			case 8:		// memo - set cell to multi-line
				cell->SetCellType(UGCT_NORMAL);
				cell->SetCellTypeEx(UGCT_NORMALMULTILINE);
				break;
			default:
				break;
			}
 			
 		}
 	}

	static int biggest = 0;

	if (row > biggest)
		biggest = row;
}
/***************************************************
OnSetCell
	This message is sent everytime the a cell is about 
	to change.
****************************************************/
void CUGAccessCtrl::OnSetCell(int col,long row,CUGCell *cell){
}
/***************************************************
OnDataSourceNotify
	This message is sent from a data source , message
	depends on the data source - check the information
	on the data source(s) being used
	- The ID of the Data source is also returned
****************************************************/
void CUGAccessCtrl::OnDataSourceNotify(int ID,long msg,long param){
	if(ID == UGDS_ID_DAO) {
		switch (msg) {
		case UGDSM_DAO_EOF:
			break;
		case UGDSM_DAO_UPDATEFAILED:
			m_bUpdateFailed = TRUE;		
			break;
		case UGDSM_DAO_KILLEXTRAROW:
			m_nExtraRow = -1;
			break;
		case UGDSM_DAO_ADJUSTROWS:
			SetNumberRows(param);
			break;
		default:
			break;
		} 
	} 
}
/***************************************************
OnCellTypeNotify
	This message is sent from a cell type , message
	depends on the cell type - check the information
	on the cell type classes
	- The ID of the cell type is given
****************************************************/
int CUGAccessCtrl::OnCellTypeNotify(long ID,int col,long row,long msg,long param){
	return TRUE;
}
/***************************************************
OnEditStart
	This message is sent whenever the grid is ready 
	to start editing a cell
	A return of TRUE allows the editing a return of
	FALSE stops editing
	Plus the properties of the CEdit class can be modified
****************************************************/
int CUGAccessCtrl::OnEditStart(int col, long row,CWnd **edit){

//	TRACE("CUGAccessCtrl::OnEditStart - col = %d, row = %ld\r\n", col,row);
	CUGEdit *cue = (CUGEdit*) *(edit);
	cue->SetAutoSize(FALSE);
	return TRUE;
}
/***************************************************
OnEditVerify
	This is send when the editing is about to end
****************************************************/
int CUGAccessCtrl::OnEditVerify(int col,long row,UINT *vcKey,LPCTSTR string,int pos){
//	TRACE("CUGAccessCtrl::OnEditVerify\r\n");

	return TRUE;
}

/***************************************************
OnEditFinish this is send when editing is finished
****************************************************/
int CUGAccessCtrl::OnEditFinish(int col, long row,CWnd *edit,LPCSTR string,BOOL cancelFlag){	
//	TRACE("CUGAccessCtrl::OnEditFinish - col = %d, row = %ld\r\n", col,row);
	return TRUE;
}
/***************************************************
OnEditFinish this is send when editing is finished
****************************************************/
int CUGAccessCtrl::OnEditContinue(int oldcol,long oldrow,int* newcol,long* newrow){

//	TRACE("CUGAccessCtrl::OnEditContinue - oldcol = %d, oldrow = %ld\r\n", oldcol,oldrow);
	return TRUE;
}
/***************************************************
sections - UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
			UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
****************************************************/
void CUGAccessCtrl::OnMenuCommand(int col,long row,int section,int item){

	switch(section) {
	case UG_GRID:
		switch(item){
		case 1050:
			FindInAllCols(FALSE);
			FindDialog();
			break;
		case 1051:
			FindInAllCols(TRUE);
			FindDialog();
			break;

		case 1000:		// Start Transaction
			GetDataSource(GetDefDataSource())->StartTransaction();
			break;
		case 1001:		// Commit transaction
			GetDataSource(GetDefDataSource())->FinishTransaction();
			break;
		case 1002:		// Rollback transaction
			GetDataSource(GetDefDataSource())->CancelTransaction();
			AdjustComponentSizes();
			break;
		default:
			break;
	}
	case UG_TOPHEADING:
		switch (item) {
		case 1010:
			ClearSelections();
			m_CUGGrid->SetFocus();
			BeginWaitCursor();
			SortBy(col, UG_SORT_ASCENDING);
			EndWaitCursor();
			AdjustComponentSizes();
			break;
		case 1011:
			ClearSelections();
			m_CUGGrid->SetFocus();
			BeginWaitCursor();
			SortBy(col, UG_SORT_DESCENDING);
			EndWaitCursor();
			EnableUpdate(FALSE);
			AdjustComponentSizes();
			break;
		default:
			break;
	}
	case UG_SIDEHEADING:
		switch (item) {
		case 1020:
			AppendRow();
			break;
		case 1021:
			DeleteRow(row);
			AdjustComponentSizes();
			break;
		default:
			break;
		}
	}
}
/***************************************************
return TRUE to allow the menu to appear
return FALSE to not allow the menu to appear
****************************************************/
int CUGAccessCtrl::OnMenuStart(int col,long row,int section){

	EmptyMenu();
	CUGDAODataSource *ds = (CUGDAODataSource*) GetDataSource(GetDefDataSource());
	short openType = ds->GetRecordSet()->GetType();

	switch (section) {
	case UG_GRID:
		AddMenuItem(1050,_T("Find..."));
		AddMenuItem(1051,_T("Find (all columns)"));
		AddMenuItem(1052,_T(""));
		AddMenuItem(1000,_T("Start Transaction"));
		AddMenuItem(1001,_T("Commit Transaction"));
		AddMenuItem(1002,_T("Rollback Transaction"));
		if(dbOpenSnapshot == openType)
		{
			m_menu->EnableMenuItem(1000,MF_GRAYED);
			m_menu->EnableMenuItem(1001,MF_GRAYED);
			m_menu->EnableMenuItem(1002,MF_GRAYED);
		}
		return TRUE;
		break;
	case UG_TOPHEADING:
		AddMenuItem(1010,_T("Sort Ascending"));
		AddMenuItem(1011,_T("Sort Descending"));
		if(dbOpenTable == openType)
		{
			m_menu->EnableMenuItem(1010,MF_GRAYED);
			m_menu->EnableMenuItem(1011,MF_GRAYED);
		}
		return TRUE;
		break;
	case UG_SIDEHEADING:
		AddMenuItem(1020, _T("Add Record"));
		AddMenuItem(1021, _T("Delete Record"));
		return TRUE;
		break;
	default:
		break;
	}

	return FALSE;

}

/***************************************************
****************************************************/
int CUGAccessCtrl::OnVScrollHint(long row,CString *string) {
	string->Format(_T("Record %ld of %ld"), row, GetNumberRows());
	return UG_SUCCESS;
}
	

/*********************************************
drag and drop
**********************************************/
#ifdef UG_ENABLE_DRAGDROP
/***************************************************
****************************************************/
DROPEFFECT  CUGAccessCtrl::OnDragEnter(COleDataObject* pDataObject){
	return DROPEFFECT_NONE;
}
/***************************************************
****************************************************/
DROPEFFECT  CUGAccessCtrl::OnDragOver(COleDataObject* pDataObject,int col,long row){
	return DROPEFFECT_NONE;
}
/***************************************************
****************************************************/
DROPEFFECT  CUGAccessCtrl::OnDragDrop(COleDataObject* pDataObject,int col,long row){
	return DROPEFFECT_NONE;
}
#endif
/***************************************************
****************************************************/
void CUGAccessCtrl::OnScreenDCSetup(CDC *dc,int section){
}
/***************************************************
****************************************************/
void CUGAccessCtrl::OnTabSelected(int ID){
	
	SetSheetNumber(ID);
}
/***************************************************
****************************************************/
BOOL CUGAccessCtrl::OnColSwapStart(int col){

	return TRUE;
}

/***************************************************
****************************************************/
void CUGAccessCtrl::OnDrawFocusRect(CDC *dc,RECT *rect){

    CUGCtrl::OnDrawFocusRect(dc,rect);
	
}

/***************************************************
****************************************************/
COLORREF CUGAccessCtrl::OnGetDefBackColor(int section){
//	TRACE(_T("OnGetDefBackColor called\n"));
		return GetSysColor(COLOR_BTNFACE);	

}


