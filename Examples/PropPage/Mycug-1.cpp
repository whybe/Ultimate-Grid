/***************************************************
****************************************************
Skeleton Class for a Derived MyCug1
****************************************************
****************************************************/

#include "stdafx.h"
#include "resource.h"
#include "MyCug-1.h"
#include <stdlib.h>
#include <time.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(MyCug1,CUGCtrl)
	//{{AFX_MSG_MAP(MyCug1)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/***************************************************
****************************************************/
MyCug1::MyCug1()
{
}
/***************************************************
****************************************************/
MyCug1::~MyCug1()
{
}

/***************************************************
OnSetup
	This function is called just after the grid window 
	is created or attached to a dialog item.
	It can be used to initially setup the grid
****************************************************/
void MyCug1::OnSetup(){

	int numCols = 3;
	long j, numRows = 30;
	CUGCell cell;
	CString string;
	
	SetSH_Width(0);
	
	SetNumberCols(numCols);
	SetNumberRows(numRows);

	FitToWindow(0,2);

	QuickSetText(0,-1,"ID");
	QuickSetText(1,-1,"Last Name");
	QuickSetText(2,-1,"First Name");
	
	srand((unsigned)time(NULL));
	for (j = 0; j < numRows ;j++){
		string.Format("%d",((rand()%30)*(rand()%50)));
		QuickSetText(0,j,string);
		string.Format("%c%c%c%c%c%c",rand()%26+65,rand()%26+97,rand()%26+97,rand()%26+97,rand()%26+97,rand()%26+97);
		QuickSetText(1,j,string);
		string.Format("%c%c%c%c%c%c",rand()%26+65,rand()%26+97,rand()%26+97,rand()%26+97,rand()%26+97,rand()%26+97);
		QuickSetText(2,j,string);
	}
}
/***************************************************
OnCanSizeCol
	Sent when the user is over a separation line on
	the top heading
	A return value of TRUE allows the possibiliy of
	a resize
****************************************************/
int MyCug1::OnCanSizeCol(int col){
	return FALSE;
}

int  MyCug1::OnCanSizeTopHdg(){
	return FALSE;
}


