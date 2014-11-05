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
	int rows = 30,
		cols = 12,
		i,j;
	CString temp;

	// setup rows and columns
	SetNumberRows(rows);
	SetNumberCols(cols);

	// fill-in grid cells with random data
	for (i = 0; i < cols; i++) {
		for (j = 0; j < rows; j++) {
			temp.Format("%d",rand()%1000);
			QuickSetText(i,j,temp);
		}
	}
	// top headings
	for (i = 0; i < cols; i++) {
		temp.Format("%d",(i+1));
		QuickSetText(i,-1,temp);
	}
	// side headings
	for (j = 0; j < rows; j++) {
		temp.Format("%d",(j+1));
		QuickSetText(-1,j,temp);
	}

	m_font.CreateFont(15,0,0,0,600,0,0,0,0,0,0,0,0,"Times New Roman");

	// enable and create menu
	EnableMenu(TRUE);
	AddMenuItem (1011, "QuickSet Align Left");
	AddMenuItem (1001, "QuickSet Align Center");
	AddMenuItem (1012, "QuickSet Align Right");
	AddMenuItem (1101, "");
	AddMenuItem (1008, "QuickSet Text");
	AddMenuItem (1010, "QuickSet Number");
	AddMenuItem (1002, "QuickSet Text Color");
	AddMenuItem (1004, "QuickSet Back Color");
	AddMenuItem (1102, "");
	AddMenuItem (1003, "QuickSet Highlight Text Color");
	AddMenuItem (1005, "QuickSet Highlight Back Color");
	AddMenuItem (1103, "");
	AddMenuItem (1006, "QuickSet Font");
	AddMenuItem (1007, "QuickSet Bitmaps");
	AddMenuItem (1009, "QuickSet Borders");

	m_bitmap.LoadBitmap(IDB_BITMAP1);
	SetMultiSelectMode(UG_MULTISELECT_CELL);
}

/***************************************************
sections - UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
			UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
****************************************************/
void MyCug::OnMenuCommand(int col,long row,int section,int item){
	switch (item){
	case 1011:		// allign left
		QuickSetAlignment(col,row,UG_ALIGNLEFT);
		break;
	case 1001:		// allign center
		QuickSetAlignment(col,row,UG_ALIGNCENTER);
		break;
	case 1012:		// allign right
		QuickSetAlignment(col,row,UG_ALIGNRIGHT);
		break;
	case 1002:		// set text color
		QuickSetTextColor(col,row,RGB(0,0,255));
		break;
	case 1003:		// set text hightcolor
		QuickSetHTextColor(col,row,RGB(0,255,0));
		break;
	case 1004:		// set backgrouns color
		QuickSetBackColor(col,row,RGB(255,0,255));
		break;
	case 1005:		// set background hightlight color
		QuickSetHBackColor(col,row,RGB(255,0,0));
		break;
	case 1006:		// set font
		QuickSetFont(col,row,&m_font);
		break;
	case 1007:		// add bitmap
		QuickSetBitmap(col,row,&m_bitmap);
		break;
	case 1008:		// set text
		QuickSetText(col,row,"Text");
		break;
	case 1009:		// add borders
		QuickSetBorder(col,row,UG_BDR_LMEDIUM|UG_BDR_TMEDIUM);
		break;
	case 1010:		// add number
		QuickSetNumber(col,row,rand()%1000);
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

