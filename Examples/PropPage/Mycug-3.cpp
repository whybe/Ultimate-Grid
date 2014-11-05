/***************************************************
****************************************************
Skeleton Class for a Derived MyCug3
****************************************************
****************************************************/

#include "stdafx.h"
#include "resource.h"
#include "MyCug-3.h"
#include <stdlib.h>
#include <time.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(MyCug3,CUGCtrl)
	//{{AFX_MSG_MAP(MyCug3)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/***************************************************
****************************************************/
MyCug3::MyCug3()
{
}
/***************************************************
****************************************************/
MyCug3::~MyCug3()
{
}

/***************************************************
OnSetup
	This function is called just after the grid window 
	is created or attached to a dialog item.
	It can be used to initially setup the grid
****************************************************/
void MyCug3::OnSetup(){

	CUGCell cell;
	
	SetNumberCols(5);
	SetNumberRows(8);

	SetHighlightRow(TRUE);

	QuickSetText(0,-1,"Name");
	QuickSetText(0,0,"Randy");
	QuickSetText(0,1,"Ghazi");
	QuickSetText(0,2,"Peter");
	QuickSetText(0,3,"Donna");
	QuickSetText(0,4,"Troy");
	QuickSetText(0,5,"Julie");
	QuickSetText(0,6,"David");
	QuickSetText(0,7,"Andrei");

	QuickSetText(1,-1,"Happy");
	QuickSetText(2,-1,"Angry");
	QuickSetText(3,-1,"Sad");
	QuickSetText(4,-1,"Tired");
	
	GetColDefault(1,&cell);
	cell.SetBackColor(RGB(255,200,200));
	cell.SetCellType(UGCT_CHECKBOX);
	cell.SetCellTypeEx(UGCT_CHECKBOXCHECKMARK|UGCT_CHECKBOX3DRECESS);
	SetColDefault(1,&cell);
	cell.SetBackColor(RGB(200,10,0));
	SetColDefault(2,&cell);
	cell.SetBackColor(RGB(128,128,255));
	SetColDefault(3,&cell);
	cell.SetBackColor(RGB(192,192,0));
	SetColDefault(4,&cell);
	
	srand((unsigned)time(NULL));
	GetCell(0,0,&cell);
	for (int x = 1; x < 5 ;x++)
		for (int y = 1; y < 8 ;y++){
			cell.SetBool(rand()%2);
			SetCell(x,y,&cell);
	}

	FitToWindow(0,4);
}

/***************************************************
OnCanSizeCol
	Sent when the user is over a separation line on
	the top heading
	A return value of TRUE allows the possibiliy of
	a resize
****************************************************/
int MyCug3::OnCanSizeCol(int col){
	return FALSE;
}
/***************************************************
OnCanSizeRow
	Sent when the user is over a separation line on
	the side heading
	A return value of TRUE allows the possibiliy of
	a resize
****************************************************/
int  MyCug3::OnCanSizeRow(long row){
	return FALSE;
}
/***************************************************
OnCanSizeSideHdg
	This is sent when the user moves into position 
	for sizing the width of the side heading
	return TRUE to allow the sizing
	or FALSE to not allow it
****************************************************/
int MyCug3::OnCanSizeSideHdg(){
	return FALSE;
}
/***************************************************
OnCanSizeTopHdg
	This is sent when the user moves into position 
	for sizing the height of the top heading
	return TRUE to allow the sizing
	or FALSE to not allow it
****************************************************/
int MyCug3::OnCanSizeTopHdg(){
	return FALSE;
}
/***************************************************
OnGetCell
	This message is sent everytime the grid needs to
	draw a cell in the grid. At this point the cell
	class has been filled with the information to be
	used to draw the cell. The information can now be
	changed before it is used for drawing
****************************************************/
void MyCug3::OnGetCell(int col,long row,CUGCell *cell){
	
	if (col == -1){
		if (row == GetCurrentRow())
			cell->SetCellType(UGCT_ARROW);
		else
			cell->SetCellType(0);
	}
}
