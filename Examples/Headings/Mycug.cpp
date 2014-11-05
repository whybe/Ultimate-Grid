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
OnSetup
	This function is called just after the grid window 
	is created or attached to a dialog item.
	It can be used to initially setup the grid
****************************************************/
void MyCug::OnSetup(){

	// initailize local vatiables
	int rows = 24;
	int cols = 14;
	int i,j;
	CString tmpNum;
	CUGCell cell;

	// setup rows and columns
	SetNumberRows(rows);
	SetNumberCols(cols);

	// fill-in cells with numbers
	// limit number of decimal places to 0
	GetCell (0,0,&cell);
	cell.SetNumberDecimals(0);
	cell.SetAlignment (UG_ALIGNRIGHT);
	for (i = 0; i < cols; i++)
		for (j = 0; j < rows; j++) {
			cell.SetNumber(rand()%1000);
			SetCell (i,j,&cell);
		}

	GetColDefault (10,&cell);
	m_pen.CreatePen (PS_SOLID,1,RGB(255,0,0));
	cell.SetBorderColor (&m_pen);
	cell.SetBorder (UG_BDR_LTHIN);
	SetColDefault (10,&cell);
	// create 3 column side heading
	SetSH_NumberCols(2);
	// ensure that side heading is large enough to fit 3 cols
	SetSH_Width(80);			
	SetSH_ColWidth(-1,30);		// resize columns in the side heading
	SetSH_ColWidth(-2,50);

	// create 3 row top heading
	SetTH_NumberRows(3);
	// ensure that top heading is large enough to fit 3 rows
	SetTH_Height(60);			
	SetTH_RowHeight(-1,20);		// resize rows in the top heading
	SetTH_RowHeight(-2,20);
	SetTH_RowHeight(-3,20);

	// join cells and assign text values in the top headings
	JoinCells (0,-3,9,-3);
	JoinCells (10,-3,13,-3);
	QuickSetText (0,-3,"Week-days");
	QuickSetTextColor (10,-3,RGB(255,0,10));
	QuickSetText (10,-3,"Week-end");
	for (i=0;i<cols;i+=2){
		JoinCells (i,-2,i+1,-2);
		if (i >= 10){
			QuickSetTextColor (i,-1,RGB(255,0,10));
			QuickSetTextColor (i+1,-1,RGB(255,0,10));
			QuickSetTextColor (i,-2,RGB(255,0,10));
		}
		QuickSetText (i,-1,"Sched.");
		QuickSetText (i+1,-1,"To Do");
	}
	QuickSetText (0,-2,"Monday");
	QuickSetText (2,-2,"Tuesday");
	QuickSetText (4,-2,"Wednesday");
	QuickSetText (6,-2,"Thursday");
	QuickSetText (8,-2,"Friday");
	QuickSetText (10,-2,"Satruday");
	QuickSetText (12,-2,"Sunday");

	// join cells and assign text in the side headings
	j = 8;
	for (i=0;i<rows;i+=2) {
		JoinCells (-2,i,-2,i+1);
		tmpNum.Format ("%d",j++);
		if (j < 13)
			tmpNum += " AM";
		else 
			tmpNum += " PM";
		QuickSetText (-2,i,tmpNum);
		QuickSetText (-1,i,":00");
		QuickSetText (-1,i+1,":30");
	}
}