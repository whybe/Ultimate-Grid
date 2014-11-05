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
	int rows = 1000,
		cols = 200;
	CString tmpStr;
	CMenu *tmpMenu = GetPopupMenu();

	// setup rows and columns
	SetNumberRows(rows);
	SetNumberCols(cols);
	// set scroll mode
	SetVScrollMode(UG_SCROLLTRACKING);

	// create and enable pop-menu
	AddMenuItem(1000,"No Balistics");
	AddMenuItem(0,"");
	AddMenuItem(1001,"Balistics Level 1");
	AddMenuItem(1002,"Balistics Level 2");
	AddMenuItem(1003,"Balistics Level 3");
	AddMenuItem(0,"");
	AddMenuItem(1004,"0ms Balistic Delay");
	AddMenuItem(1005,"100ms Balistic Delay");
	AddMenuItem(1006,"200ms Balistic Delay");
	EnableMenu(1);	
	// check appropriate menu items
	tmpMenu->CheckMenuRadioItem (1000,1003,1000,MF_BYCOMMAND);
	tmpMenu->CheckMenuRadioItem (1004,1006,1005,MF_BYCOMMAND);
	// set default ballistics mode
	SetBallisticMode(0);
	SetBallisticDelay(100);

}

/******************************************************
*******************************************************/
void MyCug::OnMenuCommand(int col,long row,int section,int item){
	CMenu *tmpMenu = GetPopupMenu();

	switch(item){
		case 1000:		//no balistics
			tmpMenu->CheckMenuRadioItem (1000,1003,1000,MF_BYCOMMAND);
			tmpMenu->CheckMenuItem (1000,MF_CHECKED);
			SetBallisticMode(0);
			break;
		case 1001:		//balistic level 1
			tmpMenu->CheckMenuRadioItem (1000,1003,1001,MF_BYCOMMAND);
			SetBallisticMode(1);
			break;
		case 1002:		//balistic level 2
			tmpMenu->CheckMenuRadioItem (1000,1003,1002,MF_BYCOMMAND);
			SetBallisticMode(2);
			break;
		case 1003:		//balistic level 3
			tmpMenu->CheckMenuRadioItem (1000,1003,1003,MF_BYCOMMAND);
			SetBallisticMode(3);
			break;
		case 1004:		//0ms delay
			tmpMenu->CheckMenuRadioItem (1004,1006,1004,MF_BYCOMMAND);
			SetBallisticDelay(0);
			break;
		case 1005:		//100ms delay
			tmpMenu->CheckMenuRadioItem (1004,1006,1005,MF_BYCOMMAND);
			SetBallisticDelay(100);
			break;
		case 1006:		//200ms delay
			tmpMenu->CheckMenuRadioItem (1004,1006,1006,MF_BYCOMMAND);
			SetBallisticDelay(200);
			break;
	}
}
/***************************************************
OnGetCell
	This message is sent everytime the grid needs to
	draw a cell in the grid. At this point the cell
	class has been filled with the information to be
	used to draw the cell. The information can now be
	changed before it is used for drawing
****************************************************/
void MyCug::OnGetCell(int col,long row,CUGCell *cell){

	static char buf[64];

	if(col < 0){
		
		if(row < 0)
			return;

		wsprintf(buf,"%ld",row);
		cell->SetText(buf);
	}
	else if(row <0){
		wsprintf(buf,"%ld",col);
		cell->SetText(buf);
	}
	else{
		if (col == 0 && row == 0)
		strcpy(buf,"Right Click "); // Message to inform of how to invoke menu
		else
		wsprintf(buf,"%ld",row*col);
	cell->SetText(buf);
	}
}
