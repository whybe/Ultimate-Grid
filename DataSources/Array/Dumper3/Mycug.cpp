/***************************************************
****************************************************
Skeleton Class for a Derived MyCug
****************************************************
****************************************************/

/***************************************************
This is the MyCug CUGCtrl derived class with the 
addition of TRACE statements to allow the various
notification sequences to be seen in the output 
window.  The OnMouseMove and OnGetCell notification
TRACE statements are commented out so as to reduce 
the clutter!  
****************************************************/

#include "stdafx.h"
#include "UGCBADSC.h"
#include "resource.h"
#include "MyCug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(MyCug,CUGCtrl)
	//{{AFX_MSG_MAP(MyCug)
	ON_COMMAND(ID_EDIT_FIND, OnEditFind)
	ON_UPDATE_COMMAND_UI(ID_EDIT_FIND, OnUpdateEditFind)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/***************************************************
****************************************************/
MyCug::MyCug()
{
	// TRACE("MyCug: Constructor called.\n");
}
/***************************************************
****************************************************/
MyCug::~MyCug()
{
	// TRACE("MyCug: Destructor called.\n");
}

/***************************************************
OnSetup
	This function is called just after the grid window 
	is created or attached to a dialog item.
	It can be used to initially setup the grid
****************************************************/
void MyCug::OnSetup()
{
	m_font.CreateFont(14,8,0,0,500,0,0,0,255,0,0,0,0,_T("Courier New"));
	m_printFont.CreateFont(0,0,0,0,200,0,0,0,255,0,0,0,0,_T("Courier New"));
	
	SetDefFont(&m_font);

	CUGCell cell, defcell, headingCell;

	GetCell(0,0,&defcell);
	defcell.SetFont(&m_font);
	defcell.SetHBackColor(RGB(255,250,220));
	defcell.SetHTextColor(RGB(0,0,0));
    defcell.SetCellTypeEx(UGCT_NORMALMULTILINE);
    defcell.SetBorderColor(&m_borderPen);
	SetColDefault(0,&cell);
	SetColDefault(1,&cell);

	int index = AddDataSource(&m_data);
	SetDefDataSource(index);
	SetGridUsingDataSource(index);

	PrintSetOption(UG_PRINT_TOPHEADING, TRUE);
	PrintSetOption(UG_PRINT_SIDEHEADING, TRUE);

	SetMultiSelectMode(TRUE);
	EnableCellOverLap(FALSE);
	((CUGEdit*)GetEditClass())->SetAutoSize(FALSE);
}

void MyCug::OnEditFind() 
{
	FindInAllCols(TRUE);
	FindDialog();
}

void MyCug::OnUpdateEditFind(CCmdUI* pCmdUI) 
{
	if(0 != GetNumberRows()) 
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}
