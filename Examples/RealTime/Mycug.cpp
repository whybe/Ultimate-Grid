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

	// set up rows and cols...
	int rows = 20000;
	int cols = 2000;

	SetNumberRows(rows);
	SetNumberCols(cols);

	// setup scroll rate and ballistics mode
	SetVScrollMode(UG_SCROLLTRACKING);

	SetBallisticMode(3);
	SetBallisticDelay(100);
}

/******************************************************
// while each cell is created 
*******************************************************/
void MyCug::OnGetCell(int col,long row,CUGCell *cell){
	// temporary string used to set cell text
	CString temp;

	// set cell text property
	if (col < 0)
		if (row < 0)
			temp = "0";
		else
			temp.Format ("%d",row);
	else if (row < 0)
		temp.Format ("%d",col);
	else {
		if (col == 0) {
			if (row == 0)
				temp = "This Data";
			else if (row == 1)
				temp = "Loaded on";
			else if (row == 2)
				temp = "The fly";
			else
				temp.Format ("%ld",(long)(col*row));
		}
		else
			temp.Format ("%ld",(long)(col*row));
	}
	cell->SetText(temp);
}