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
		cols = 25,
		i,j;
	CString temp;
	CUGCell	cell;

	// setup rows and columns
	SetNumberRows(rows);
	SetNumberCols(cols);

	// fill-in cells with randim data
	for (i = 0; i < cols; i++) {
		for (j = 0; j < rows; j++) {
			temp.Format("%d",rand()%1000);
			QuickSetText(i,j,temp);
		}
	}

//	QuickSetText(0,0,"Right-Click");
//	QuickSetText(0,1,"For options");


	// add some col headings
	for (i = 0; i < cols; i++) {
		temp.Format("%d",(i+1));
		QuickSetText(i,-1,temp);
	}

	// add some row headings
	for (j = 0; j < rows; j++) {
		temp.Format("%d",(j+1));
		QuickSetText(-1,j,temp);
	}

	// create and enable menu
	CMenu * pMenu = GetPopupMenu();
	CMenu tmpMenu;
	EnableMenu(TRUE);

	// Vertical Scrollbar submenu
	tmpMenu.CreatePopupMenu();
	tmpMenu.AppendMenu(MF_STRING, 1000, "Normal Scroll Mode");
	tmpMenu.AppendMenu(MF_STRING, 1001, "Tracking Scroll Mode");
	tmpMenu.AppendMenu(MF_STRING, 1002, "Joystick Scroll Mode");
	tmpMenu.AppendMenu(MF_SEPARATOR, 0, "");
	tmpMenu.AppendMenu(MF_STRING, 1003, "Small Scroll Bars");
	tmpMenu.AppendMenu(MF_STRING, 1004, "Normal Scroll Bars");
	tmpMenu.AppendMenu(MF_STRING, 1005, "Large Scroll Bars");
	tmpMenu.AppendMenu(MF_STRING, 1006, "Hide");
	// Attach to main menu Vertical ScrollBar option
	pMenu->AppendMenu(MF_POPUP, (UINT)tmpMenu.Detach(), "Vertical ScrollBar");
	// Check the default options
	pMenu->CheckMenuRadioItem(1000,1002,1000,MF_BYCOMMAND); 
	pMenu->CheckMenuRadioItem(1003,1005,1004,MF_BYCOMMAND); 

	pMenu->AppendMenu(MF_SEPARATOR, 0, "");

	// Horisontal Scrollbar submenu
	tmpMenu.CreatePopupMenu();
	tmpMenu.AppendMenu(MF_STRING, 1010, "Normal Scroll Mode");
	tmpMenu.AppendMenu(MF_STRING, 1011, "Tracking Scroll Mode");
	tmpMenu.AppendMenu(MF_SEPARATOR, 0, "");
	tmpMenu.AppendMenu(MF_STRING, 1013, "Small Scroll Bars");
	tmpMenu.AppendMenu(MF_STRING, 1014, "Normal Scroll Bars");
	tmpMenu.AppendMenu(MF_STRING, 1015, "Large Scroll Bars");
	tmpMenu.AppendMenu(MF_STRING, 1016, "Hide");
	// Attach to main menu Horisontal ScrollBar option
	pMenu->AppendMenu(MF_POPUP, (UINT) tmpMenu.Detach(), "Horizontal ScrollBar");
	// Check the default options
	pMenu->CheckMenuRadioItem(1010,1011,1010,MF_BYCOMMAND); 
	pMenu->CheckMenuRadioItem(1013,1015,1014,MF_BYCOMMAND); 
}
/***************************************************
sections - UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
			UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
****************************************************/
void MyCug::OnMenuCommand(int col,long row,int section,int item){
	CMenu * pMenu = GetPopupMenu();

	switch(item){
	// vertical scrollbar
	case 1000:				// "Normal Scroll Mode"
		pMenu->CheckMenuRadioItem(1000,1002,1000,MF_BYCOMMAND); 
		SetVScrollMode(UG_SCROLLNORMAL);
		break;
	case 1001:				// "Tracking Scroll Mode"
		pMenu->CheckMenuRadioItem(1000,1002,1001,MF_BYCOMMAND); 
		SetVScrollMode(UG_SCROLLTRACKING);
		break;
	case 1002:				// "Joystick Scroll Mode"
		pMenu->CheckMenuRadioItem(1000,1002,1002,MF_BYCOMMAND); 
		SetVScrollMode(UG_SCROLLJOYSTICK);
		break;
	case 1003:				// "Small Scroll Bars"
		pMenu->CheckMenuRadioItem(1003,1006,1003,MF_BYCOMMAND); 
		SetVS_Width(GetSystemMetrics(SM_CXHSCROLL)/3);
		break;
	case 1004:				// "Normal Scroll Bars"
		pMenu->CheckMenuRadioItem(1003,1006,1004,MF_BYCOMMAND); 
		SetVS_Width(GetSystemMetrics(SM_CXHSCROLL));
		break;
	case 1005:				// "Large Scroll Bars"
		pMenu->CheckMenuRadioItem(1003,1006,1005,MF_BYCOMMAND); 
		SetVS_Width(GetSystemMetrics(SM_CXHSCROLL)*3);
		break;
	case 1006:				// "Hide"
		pMenu->CheckMenuRadioItem(1003,1006,1006,MF_BYCOMMAND); 
		SetVS_Width(0);
		break;
	// horizontal scrollbar
	case 1010:				// "Normal Scroll Mode"
		pMenu->CheckMenuRadioItem(1010,1011,1010,MF_BYCOMMAND); 
		SetHScrollMode(UG_SCROLLNORMAL);
		break;
	case 1011:				// "Tracking Scroll Mode"
		pMenu->CheckMenuRadioItem(1010,1011,1011,MF_BYCOMMAND); 
		SetHScrollMode(UG_SCROLLTRACKING);
		break;
	case 1013:				// "Small Scroll Bars"
		pMenu->CheckMenuRadioItem(1013,1016,1013,MF_BYCOMMAND); 
		SetHS_Height(GetSystemMetrics(SM_CYVSCROLL)/3);
		break;
	case 1014:				// "Normal Scroll Bars"
		pMenu->CheckMenuRadioItem(1013,1016,1014,MF_BYCOMMAND); 
		SetHS_Height(GetSystemMetrics(SM_CYVSCROLL));
		break;
	case 1015:				// "Large Scroll Bars"
		pMenu->CheckMenuRadioItem(1013,1016,1015,MF_BYCOMMAND); 
		SetHS_Height(GetSystemMetrics(SM_CYVSCROLL)*3);
		break;
	case 1016:				// "Hide"
		pMenu->CheckMenuRadioItem(1013,1016,1016,MF_BYCOMMAND); 
		SetHS_Height(0);
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
