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
}

/***************************************************
OnSetup
	This function is called just after the grid window 
	is created or attached to a dialog item.
	It can be used to initially setup the grid
****************************************************/
void MyCug::OnSetup(){
	SetDefColWidth(180);
	SetVScrollMode(UG_SCROLLTRACKING);

	if(m_data.Open(_T("mytext.txt"),NULL) == UG_SUCCESS){
		int index = AddDataSource(&m_data);
		SetDefDataSource(index);
		SetGridUsingDataSource(index);
	}

	EnableMenu(TRUE);
	AddMenuItem(1000, _T("Load New File"));
	AddMenuItem(1001, _T("Save File"));
	AddMenuItem(1002, _T("Save As..."));


}

/***************************************************
sections - UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
			UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
****************************************************/
void MyCug::OnMenuCommand(int col,long row,int section,int item){
	switch(item){
	case 1000:{ // "Load New File"
		CFileDialog dlg(TRUE);
		if(dlg.DoModal()==IDOK)
			m_data.Open(dlg.GetFileName(),NULL);
		}
		break;
	case 1001: // "Save File"
		m_data.Save();
		break;
	case 1002: { // "Save As..."
		CFileDialog dlg(FALSE);
		if(dlg.DoModal()==IDOK)
			m_data.SaveAs(dlg.GetFileName(),NULL);
		}
		break;
	}
}

void MyCug::OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed){
	StartEdit();
}

