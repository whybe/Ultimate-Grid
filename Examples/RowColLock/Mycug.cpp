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
	// initialize local variables
	int rows = 50,
		cols = 20,
		i,j;
	CUGCell	cell;

	// set-up rows and columns in the grid
	SetNumberRows(rows);
	SetNumberCols(cols);

	// fill-in grid cells with random data
	GetCell(0,0,&cell);
	cell.SetNumberDecimals(0);
	for (i = 0; i < cols; i++)
		for (j = 0; j < rows; j++) {
			cell.SetNumber(rand()%1000);
			SetCell(i,j,&cell);
		}
	// number columns
	for (i=0;i < cols;i++){
		cell.SetNumber(i);
		SetCell (i,-1,&cell);
	}
	// number rows
	for (j=0;j < rows;j++){
		cell.SetNumber(j);
		SetCell (-1,j,&cell);
	}

	// enable and create pop-up menu
	EnableMenu (TRUE);
	AddMenuItem (1001,"Lock Rows");
	AddMenuItem (1002,"Un-Lock Rows");
	AddMenuItem (1101,"");
	AddMenuItem (1003,"Lock Columns");
	AddMenuItem (1004,"Un-Lock Columns");

	// lock default rows and columns
	LockRows (5);
	LockColumns (3);
}

/***************************************************
sections - UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
			UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
****************************************************/
void MyCug::OnMenuCommand(int col,long row,int section,int item){
	switch(item){
	case 1001:
		LockRows(row);
		break;
	case 1002:
		LockRows(0);
		break;
	case 1003:
		LockColumns(col);
		break;
	case 1004:
		LockColumns(0);
		break;
	}
	RedrawAll();
}
/***************************************************
return UG_SUCCESS to allow the menu to appear
return 1 to not allow the menu to appear
****************************************************/
int MyCug::OnMenuStart(int col,long row,int section){
	return TRUE;
}
