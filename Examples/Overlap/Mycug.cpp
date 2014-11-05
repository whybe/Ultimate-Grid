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
	// initalize local variables
	int rows = 30,
		cols = 10,
		i,j;
	CString temp;

	// setup rows and columns
	SetNumberRows(rows);
	SetNumberCols(cols);

	// fill-in cells with data
	for (i = 0; i < cols; i+=2)
		for (j = 0; j < rows; j++) {
			temp.Format("%15f",(i+1.0)*(j+1));
			QuickSetText (i,j,temp);
		}
	// add col headings
	for (i = 0; i < cols; i++) {
		temp.Format("%d",(i+1));
		QuickSetText(i,-1,temp);
	}
	// add row headings
	for (j = 0; j < rows; j++) {
		temp.Format("%d",(j+1));
		QuickSetText(-1,j,temp);
	}

//	QuickSetText(0,0,"This Example shows the use of overlapped text:  Text that covers more than one cell.");
}

