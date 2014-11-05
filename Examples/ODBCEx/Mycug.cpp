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
	SetNumberRows (10);
	SetNumberCols (10);
	AdjustComponentSizes ();
}

/***************************************************
****************************************************/
void MyCug::OnHitBottom(long numrows,long rowspast,long rowsfound){
	if (rowsfound > 0)
		SetNumberRows (numrows+rowsfound);
}

/*********************************************
OLE
**********************************************/
#ifdef __AFXOLE_H__

/***************************************************
****************************************************/
DROPEFFECT  MyCug::OnDragEnter(COleDataObject* pDataObject){
	return DROPEFFECT_NONE;
}
/***************************************************
****************************************************/
DROPEFFECT  MyCug::OnDragOver(COleDataObject* pDataObject,int col,long row){
	return DROPEFFECT_NONE;
}
/***************************************************
****************************************************/
DROPEFFECT  MyCug::OnDragDrop(COleDataObject* pDataObject,int col,long row){
	return DROPEFFECT_NONE;
}
#endif
/***************************************************
OnDrawFocusRect
****************************************************/
void MyCug::OnDrawFocusRect(CDC *dc,RECT *rect){
	//DrawExcelFocusRect(dc,rect);
	
	rect->bottom --;
	rect->right --;
	dc->DrawFocusRect(rect);
}

/***************************************************
OnGetDefBackColor
****************************************************/
COLORREF MyCug::OnGetDefBackColor(int section){
//	return RGB(255,255,255);
	return GetSysColor (COLOR_BTNFACE);
}
