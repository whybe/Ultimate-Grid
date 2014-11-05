/***************************************************
****************************************************
Skeleton Class for a Derived MyCug2
****************************************************
****************************************************/

#include "stdafx.h"
#include "resource.h"
#include "MyCug-2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(MyCug2,CUGCtrl)
	//{{AFX_MSG_MAP(MyCug2)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/***************************************************
****************************************************/
MyCug2::MyCug2()
{
}
/***************************************************
****************************************************/
MyCug2::~MyCug2()
{
}

/***************************************************
OnSetup
	This function is called just after the grid window 
	is created or attached to a dialog item.
	It can be used to initially setup the grid
****************************************************/
void MyCug2::OnSetup(){

	CUGCell cell;
	GetGridDefault(&cell);
	cell.SetBackColor(RGB(255,255,208));
	SetGridDefault(&cell);

	SetSH_Width(0);
	SetTH_Height(0);
	
	SetHighlightRow(TRUE);
	SetMultiSelectMode(TRUE);
	
	SetNumberCols(4);
	SetNumberRows(50);

	FitToWindow(0,3);
}

/***************************************************
OnGetCell
	This message is sent everytime the grid needs to
	draw a cell in the grid. At this point the cell
	class has been filled with the information to be
	used to draw the cell. The information can now be
	changed before it is used for drawing
****************************************************/
void MyCug2::OnGetCell(int col,long row,CUGCell *cell){
	
	if ((col >= 0) && (row >=0)){
		cell->SetNumberDecimals(3);
		cell->SetNumber((col+1)*(row+1));
	}
}
