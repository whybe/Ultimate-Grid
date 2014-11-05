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
	int i, numCols = 20;
	long j, numRows = 50;
	CString string;
	
	//Set up the default font I want to use for my grid
	//very important, especially when printing...
	m_font.CreateFont(14,0,0,0,500,0,0,0,0,0,0,0,0,"Arial");
	SetDefFont(&m_font);

	//basic grid setup
	SetNumberCols(numCols);
	SetNumberRows(numRows);
	SetSH_Width(80);

	//give me a simple multiplication table		
	for (i = 0; i < numCols ;i++)
		for (j = 0; j < numRows ;j++){
			string.Format("%d", rand()%1000);
			QuickSetText(i,j,string);
		}
	
	//do the top headings
	for (i = 0; i < numCols ;i++){
		string.Format("Col: %d",i);
		QuickSetText(i,-1,string);
	}

	//do the side headings
	for (j = 0; j < numRows ;j++){
		string.Format("Row: %d",j);
		QuickSetText(-1,j,string);
	}

	//show some instructions on the grid 
	QuickSetText(0,0,"Right click");
	QuickSetText(0,1,"on the grid");
	QuickSetText(0,2,"to see the");
	QuickSetText(0,3,"print options.");
	QuickSetBackColor(0,0,RGB(255,255,192));		
	QuickSetBackColor(0,1,RGB(255,255,192));		
	QuickSetBackColor(0,2,RGB(255,255,192));		
	QuickSetBackColor(0,3,RGB(255,255,192));		
	//set up my pop-up menu
	EnableMenu(TRUE);
	CMenu * menu = GetPopupMenu();
	
	AddMenuItem(1001,"Print Top Headings");
	AddMenuItem(1002,"Print Side Headings");
	menu->AppendMenu(MF_SEPARATOR,0,"");
	// Left Margin sub-menu
	CMenu submenu;
	submenu.CreatePopupMenu();
	submenu.AppendMenu(MF_STRING, 2001, "0 millimetres");
	submenu.AppendMenu(MF_STRING, 2002, "10 millimetres");
	submenu.AppendMenu(MF_STRING, 2003, "50 millimetres");
	menu->AppendMenu(MF_POPUP, (UINT)submenu.Detach(), "Left Margin");
	// Right Margin sub-menu
	submenu.CreatePopupMenu();
	submenu.AppendMenu(MF_STRING, 3001, "0 millimetres");
	submenu.AppendMenu(MF_STRING, 3002, "10 millimetres");
	submenu.AppendMenu(MF_STRING, 3003, "50 millimetres");
	menu->AppendMenu(MF_POPUP, (UINT)submenu.Detach(), "Right Margin");
	// Top Margin sub-menu
	submenu.CreatePopupMenu();
	submenu.AppendMenu(MF_STRING, 4001, "0 millimetres");
	submenu.AppendMenu(MF_STRING, 4002, "10 millimetres");
	submenu.AppendMenu(MF_STRING, 4003, "50 millimetres");
	menu->AppendMenu(MF_POPUP, (UINT)submenu.Detach(), "Top Margin");
	// Bottom Margin sub-menu
	submenu.CreatePopupMenu();
	submenu.AppendMenu(MF_STRING, 5001, "0 millimetres");
	submenu.AppendMenu(MF_STRING, 5002, "10 millimetres");
	submenu.AppendMenu(MF_STRING, 5003, "50 millimetres");
	menu->AppendMenu(MF_POPUP, (UINT)submenu.Detach(), "Bottom Margin");


}

/***************************************************
sections - UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
			UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
****************************************************/
void MyCug::OnMenuCommand(int col,long row,int section,int item){
	// init. local variables
	CMenu * menu;
	menu = GetPopupMenu();
	
	switch (item){
	case 1001:			// Print Top Headings
		if (menu->CheckMenuItem(1001,MF_CHECKED)){
			PrintSetOption(UG_PRINT_TOPHEADING, FALSE);
			menu->CheckMenuItem(1001,MF_UNCHECKED);
		}
		else
			PrintSetOption(UG_PRINT_TOPHEADING, TRUE);
		break;
	case 1002:			// Print Side Headings
		if (menu->CheckMenuItem(1002,MF_CHECKED)){
			PrintSetOption(UG_PRINT_SIDEHEADING, FALSE);
			menu->CheckMenuItem(1002,MF_UNCHECKED);
		}
		else
			PrintSetOption(UG_PRINT_SIDEHEADING, TRUE);
		break;
	case 2001:			// Set Left Margin to 0 mm
			PrintSetOption(UG_PRINT_LEFTMARGIN, 0);
			menu->CheckMenuRadioItem (2001,2003,2001,MF_BYCOMMAND);
		break;
	case 2002:			// Set Left Margin to 10 mm
			PrintSetOption(UG_PRINT_LEFTMARGIN, 10);
			menu->CheckMenuRadioItem (2001,2003,2002,MF_BYCOMMAND);
		break;
	case 2003:			// Set Left Margin to 50 mm
			PrintSetOption(UG_PRINT_LEFTMARGIN, 50);
			menu->CheckMenuRadioItem (2001,2003,2003,MF_BYCOMMAND);
		break;
	case 3001:			// Set Right Margin to 0 mm
			PrintSetOption(UG_PRINT_RIGHTMARGIN, 0);
			menu->CheckMenuRadioItem (3001,3003,3001,MF_BYCOMMAND);
		break;
	case 3002:			// Set Right Margin to 10 mm
			PrintSetOption(UG_PRINT_RIGHTMARGIN, 10);
			menu->CheckMenuRadioItem (3001,3003,3002,MF_BYCOMMAND);
		break;
	case 3003:			// Set Right Margin to 50 mm
			PrintSetOption(UG_PRINT_RIGHTMARGIN, 50);
			menu->CheckMenuRadioItem (3001,3003,3003,MF_BYCOMMAND);
		break;
	case 4001:			// Set Top Margin to 0 mm
			PrintSetOption(UG_PRINT_TOPMARGIN, 0);
			menu->CheckMenuRadioItem (4001,4003,4001,MF_BYCOMMAND);
		break;
	case 4002:			// Set Top Margin to 10 mm
			PrintSetOption(UG_PRINT_TOPMARGIN, 10);
			menu->CheckMenuRadioItem (4001,4003,4002,MF_BYCOMMAND);
		break;
	case 4003:			// Set Top Margin to 50 mm
			PrintSetOption(UG_PRINT_TOPMARGIN, 50);
			menu->CheckMenuRadioItem (4001,4003,4003,MF_BYCOMMAND);
		break;
	case 5001:			// Set Bottom Margin to 0 mm
			PrintSetOption(UG_PRINT_BOTTOMMARGIN, 0);
			menu->CheckMenuRadioItem (5001,5003,5001,MF_BYCOMMAND);
		break;
	case 5002:			// Set Bottom Margin to 10 mm
			PrintSetOption(UG_PRINT_BOTTOMMARGIN, 10);
			menu->CheckMenuRadioItem (5001,5003,5002,MF_BYCOMMAND);
		break;
	case 5003:			// Set Bottom Margin to 50 mm
			PrintSetOption(UG_PRINT_BOTTOMMARGIN, 50);
			menu->CheckMenuRadioItem (5001,5003,5003,MF_BYCOMMAND);
		break;
	}

}
/***************************************************
return UG_SUCCESS to allow the menu to appear
return 1 to not allow the menu to appear
****************************************************/
int MyCug::OnMenuStart(int col,long row,int section){
	
	if (section == UG_GRID)
		return TRUE;
	else
		return FALSE;
}
