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
}

/***************************************************
OnSetup
	This function is called just after the grid window 
	is created or attached to a dialog item.
	It can be used to initially setup the grid
****************************************************/
void MyCug::OnSetup()
{

	if(Open())
	{
		int index = AddDataSource(&m_data);
		SetDefDataSource(index);
		SetGridUsingDataSource(index);
		int cols = GetNumberCols();
		int rows = GetNumberRows();
		BestFit(0,cols-1,rows,0);
	}

	EnableMenu(TRUE);
	AddMenuItem(1000, _T("Load New File"));

}


/***************************************************
sections - UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
			UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
****************************************************/
void MyCug::OnMenuCommand(int col,long row,int section,int item){
	switch(item)
	{
	case 1000: // "Load New File"
		if (Open()) {
			TRACE(_T("Open suceeded\n"));
			int cols = GetNumberCols();
			int rows = GetNumberRows();
			SetNumberRows(rows);
			SetNumberCols(cols);
			BestFit(0,cols-1,rows,0);
			RedrawAll();
		}			
			
		break;
	}

}
/***************************************************
return UG_SUCCESS to allow the menu to appear
return 1 to not allow the menu to appear
****************************************************/
int MyCug::OnMenuStart(int col,long row,int section){
	return TRUE;
}

BOOL MyCug::Open()
{
	
	if(m_dlg.DoModal()==IDOK)
	{
		CString type;
		CString file;
		file=m_dlg.m_fileName;
		type.Format(_T("%d"), m_dlg.m_TableNumber);
		if(m_dlg.m_File==FALSE)
		{
			if (file.Find(_T("http:////"))==-1)
				file = _T("http://") + file;
			
		}
		if(m_data.Open(file, type) == UG_SUCCESS)
			return TRUE;
	}

	return FALSE;

}
