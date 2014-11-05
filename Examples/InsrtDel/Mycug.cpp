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

	UseDefaultStateStorage(FALSE);
	
	// initialize local variables
	int rows = 30,
		cols = 15,
		i,j;
	CUGCell	cell;

	// setup rows and columns
	SetNumberRows(rows);
	SetNumberCols(cols);

	// limit number of decimal points in the cell (0,0) to 0 (none)
	GetCell(0,1,&cell);
	cell.SetNumberDecimals(0);

	// fill-in cells with data
	for (i = 0; i < cols; i++)
		for (j = 0; j < rows; j++) {
			cell.SetNumber(rand()%1000);
			SetCell(i,j,&cell);
		}
	// setup titles for top and side headings
	for (i=0;i < cols;i++){
		cell.SetNumber (i+1);
		SetCell (i,-1,&cell);
	}
	for (j=0;j < rows;j++){
		cell.SetNumber (j+1);
		SetCell (-1,j,&cell);
	}
	// put text in first row ..
//	GetCell(0,0,&cell);
//	cell.SetText("Right click on the grid to invoke menu...");
//	SetCell(0,0,&cell);

	// create pop-up menu
	EnableMenu(TRUE);
	AddMenuItem(1001,"Insert Row");		// 'Insert Row' menu item
	AddMenuItem(1002,"Delete Row");		// 'Delete Row' menu item
	AddMenuItem(1003,"Insert Column");	// 'Insert Column' menu item
	AddMenuItem(1004,"Delete Column");	// 'Delete Column' menu item
}

/***************************************************
sections - UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
			UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
****************************************************/
void MyCug::OnMenuCommand(int col,long row,int section,int item){
	// if right mouse click outside grid area, exit
	if (section != UG_GRID)
		return;
	
	switch (item) {
	case 1001:		// "Insert Row"
		InsertRow(row);	
		break;
	case 1002:		// "Delete Row"
		DeleteRow(row);
		break;
	case 1003:		// "Insert Column"
		InsertCol(col);
		break;
	case 1004:		// "Delete Column"
		DeleteCol(col);
		break;
	}
	RedrawAll();
}
/***************************************************
return UG_SUCCESS to allow the menu to appear
return 1 to not allow the menu to appear
****************************************************/
int MyCug::OnMenuStart(int col,long row,int section){
	if (section != UG_GRID)
		return FALSE;
	return TRUE;
}
