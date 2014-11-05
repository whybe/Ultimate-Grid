/***************************************************
****************************************************
Skeleton Class for a Derived MyCug
****************************************************
****************************************************/

#include "stdafx.h"
//#include "uglibsel.h"		// Include the file which will select which library file to use

#include "resource.h"
#include "MyCug.h"

#include "adjust.h"
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
	//  initialize local variables
	int rows = 30;
	int cols = 15;
	int i,j;
	CString temp;

	// setup rows and columns
	SetNumberRows(rows);
	SetNumberCols(cols);

	// fill-in cells with data
	for (i = 0; i < cols; i++)
		for (j = 0; j < rows; j++) {
			temp.Format("%d",rand()%1000);
			QuickSetText(i,j,temp);
		}

	// add column headings
	for (i = 0; i < cols; i++) {
		temp.Format("%d",(i+1));
		QuickSetText(i,-1,temp);
	}

	// add row headings
	for (j = 0; j < rows; j++) {
		temp.Format("%d",(j+1));
		QuickSetText(-1,j,temp);
	}

//	QuickSetText(0,0,"Use the mouse to adjust the size of the headings or right click on a cell to adjust a row and column"); 	
	
	// create and enable pop-up menu
	AddMenuItem(1000, "Adjust Components");
	EnableMenu(TRUE);
}

/***************************************************
sections - UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
			UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
****************************************************/
void MyCug::OnMenuCommand(int col,long row,int section,int item){
	// init local variables
	int colheight;
	int rowwidth;

	if(item==1000){			// bring up a dialog to allow the adjust components
		GetColWidth(col, &colheight);
		GetRowHeight(row,&rowwidth);
		CAdjuster dlg(colheight,rowwidth,GetSH_Width(), GetTH_Height());

		if(dlg.DoModal()==IDOK){	// change the info to what is in dlg
			SetColWidth(col, dlg.GetColWidth());
			SetRowHeight(row, dlg.GetRowHeight());
			SetSH_Width(dlg.GetSideWidth());
			SetTH_Height(dlg.GetTopHeight());
		}
	}
}

/***************************************************
OnGetDefBackColor
****************************************************/
COLORREF MyCug::OnGetDefBackColor(int section){
	return GetSysColor (COLOR_BTNFACE);
}
