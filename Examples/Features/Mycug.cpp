/***************************************************
****************************************************
Skeleton Class for a Derived MyCug
****************************************************
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
	// setup rows and columns
	int rows = 30;
	int cols = 5;
	SetNumberRows(rows);
	SetNumberCols(cols);

	// initalize masked edit control, font, and border style
	m_pen.CreatePen (PS_SOLID,1,RGB(0,0,0));
	m_font.CreateFont (16,0,0,0,500,0,0,0,0,0,0,0,0,"Arial");
	SetDefFont (&m_font);

	// setup headings layout
	SetSH_Width (0);
	SetTH_NumberRows (2);
	SetTH_Height(40);
	SetTH_RowHeight(-1,20);
	SetTH_RowHeight(-2,20);
	JoinCells (0,-2,0,-1);
	JoinCells (2,-2,3,-2);
	JoinCells (4,-2,4,-1);
	// setup headings text
	QuickSetText (0,-2,"Date");
	QuickSetText (1,-2,"Number");
	QuickSetText (1,-1,"Type");
	QuickSetText (2,-2,"Payee");
	QuickSetText (2,-1,"Account");
	QuickSetText (3,-1,"Memo");
	QuickSetText (4,-2,"Deposit");
	EnableExcelBorders (FALSE);
	EnableCellOverLap (FALSE);

	// populate the first row group with data
	QuickSetText( 0, 0, "10/10/2001" );
	QuickSetText( 1, 0, "12203" );
	QuickSetText( 1, 1, "CHK" );
	QuickSetText( 2, 0, "Bell" );
	QuickSetText( 2, 1, "Phone" );
	QuickSetText( 4, 0, "45.50" );
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
	if (row % 2 && col == 0)
		GotoCell (col, row-1);
	else
		GotoCell (col,row);
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
	// when mouse is double clicked on a individual cell, start editing mode
	StartEdit();
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
	// set border color for each cell
	cell->SetBorderColor (&m_pen);

	if (row < 0)						// top heading
		cell->SetBorder (UG_BDR_RAISED);
	else if (row > 0 && row % 2){		// lower row
		if (col == 1)
			cell->SetMask ("???");
		else if (col == 2){
			// create and fill-in dropbox menu
			cell->SetCellType (UGCT_DROPLIST);
			cell->SetCellTypeEx (UGCT_DROPLISTHIDEBUTTON);
			cell->SetLabelText ("Phone\nCar\nR&D\nOffice Supplies");
		}
		// define back color and border style, for each cell in lower row
		cell->SetBackColor (RGB(255,255,128));
		cell->SetBorder (UG_BDR_RTHIN|UG_BDR_BTHIN);
	}
	else{								// upper row
		if (col == 0)
			cell->SetMask ("99/99/99");
		else if (col == 1)
			cell->SetMask ("999999");
		else if (col == 2){
			// create and fill-in dropbox menu
			JoinCells (col,row,col+1,row);
			cell->SetCellType (UGCT_DROPLIST);
			cell->SetCellTypeEx (UGCT_DROPLISTHIDEBUTTON);
			cell->SetLabelText ("The Code Project\nBell\nZippy Print & Copy\nAce Paper Co.");
		}
		cell->SetBorder (UG_BDR_RTHIN);
	}

	if ( col == 4 && row >= 0 )
	{	// deposit column, set its allignment
		cell->SetAlignment( UG_ALIGNRIGHT );
	}
}
/***************************************************
OnCellTypeNotify
	This message is sent from a cell type , message
	depends on the cell type - check the information
	on the cell type classes
	- The ID of the cell type is given
	Returns TRUE
****************************************************/
int MyCug::OnCellTypeNotify(long ID,int col,long row,long msg,long param){
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
int MyCug::OnEditStart(int col, long row,CWnd **edit)
{
	return TRUE;
}
/***************************************************
OnEditContinue this is send when editing is just passed focus to another cell
****************************************************/
int MyCug::OnEditContinue(int oldcol,long oldrow,int* newcol,long* newrow){
	// used to navigate through the cells, while in editing mode, 
	// this function will set focus to new cell every time cell looses focus
	if (oldcol >= 4 && oldrow % 2){
		*newrow = oldrow +1;
		*newcol = 0;
	}
	else if (oldrow % 2){
		if (oldcol == 2){
			*newcol = oldcol +1;
			*newrow = oldrow;
		}
		else {
			*newrow = oldrow -1;
			*newcol = oldcol +1;
		}
	}
	else if (oldcol == 0){
		*newcol = 1;
		*newrow = oldrow;
	}
	else{
		*newcol = oldcol;
		*newrow = oldrow +1;
	}
	return TRUE;
}

/***************************************************
OnDrawFocusRect
****************************************************/
void MyCug::OnDrawFocusRect(CDC *dc,RECT *rect){

	//DrawExcelFocusRect(dc,rect);
	
	rect->bottom --;
	rect->right --;
	dc->DrawFocusRect(rect);
}
/***************************************************
	Purpose
	Params
	Return
****************************************************/
COLORREF MyCug::OnGetDefBackColor(int section){
//	if(section == UG_GRID)
//		return GetSysColor(COLOR_WINDOW);
//	else
		return GetSysColor(COLOR_3DSHADOW  );	
}
