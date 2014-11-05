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

	int		x;
	char	buf[30];
	int		ROWS = 14;
	int		COLS = 4;
	CUGCell cell;
	int spinIndex = AddCellType(&m_spin);
	
	SetSH_Width(150);
	SetDefColWidth(150);
	SetNumberCols(COLS);
	SetNumberRows(ROWS);
	SetUniformRowHeight(TRUE);
	SetDefRowHeight(29);
	SetDoubleBufferMode( TRUE );

	RedrawAll();

	//load the bitmaps
	m_bitmap1.LoadBitmap(IDB_DUNDAS);
	m_bitmap2.LoadBitmap(IDB_FOLDER1);
	m_bitmap3.LoadBitmap(IDB_HELLO);
	m_bitmap4.LoadBitmap(IDB_MARKEDPAGE);
	m_bitmap5.LoadBitmap(IDB_NUMBER);
	m_bitmap6.LoadBitmap(IDB_FOLDER2);
	m_bitmap7.LoadBitmap(IDB_PAGE);
	m_bitmap8.LoadBitmap(IDB_ARROW);


	// define side headings
	QuickSetText(-1,0,"Bitmaps");
	QuickSetBitmap(-1,0,&m_bitmap8);
	QuickSetText(-1,3,"Auto Sizing");
	QuickSetBitmap(-1,3,&m_bitmap8);
	QuickSetText(-1,6,"Text Alignment");
	QuickSetBitmap(-1,6,&m_bitmap8);
	QuickSetText(-1,10,"Other Styles");
	QuickSetBitmap(-1,10,&m_bitmap8);
	QuickSetText(-1,12,"Changing");
	QuickSetBitmap(-1,12,&m_bitmap8);
		
	// define top headings
	for(x=0;x<COLS;x++){
		wsprintf(buf,"%d",x);
		QuickSetText(x,-1,buf);
		QuickSetBitmap(x,-1,&m_bitmap5);
	}
	
	// set up the plain bitmap cells
	QuickSetBitmap(0,0,&m_bitmap1);
	QuickSetBitmap(1,0,&m_bitmap2);
	QuickSetBitmap(2,0,&m_bitmap3);
	QuickSetBitmap(3,0,&m_bitmap4);
	QuickSetBitmap(0,1,&m_bitmap5);
	QuickSetBitmap(1,1,&m_bitmap6);
	QuickSetBitmap(2,1,&m_bitmap7);
	QuickSetBitmap(3,1,&m_bitmap8);

	//auto stretch
	QuickSetBitmap(0,3,&m_bitmap1);
	JoinCells(0,3,1,4);
	QuickSetBitmap(2,3,&m_bitmap1);

	// set cells to contain text and bitmaps
	QuickSetText(0,6,"Left alignment");
	QuickSetAlignment(0,6,UG_ALIGNLEFT|UG_ALIGNTOP);
	QuickSetBitmap(0,6,&m_bitmap2);

	QuickSetText(1,6,"Center");
	QuickSetAlignment(1,6,UG_ALIGNCENTER|UG_ALIGNTOP);
	QuickSetBitmap(1,6,&m_bitmap2);
	
	QuickSetText(2,6,"Right ");
	QuickSetAlignment(2,6,UG_ALIGNRIGHT|UG_ALIGNTOP);
	QuickSetBitmap(2,6,&m_bitmap2);

	QuickSetText(0,7,"Verticaly Centered");
	QuickSetAlignment(0,7,UG_ALIGNLEFT|UG_ALIGNVCENTER);
	QuickSetBitmap(0,7,&m_bitmap2);

	QuickSetText(1,7,"V&H Centered");
	QuickSetAlignment(1,7,UG_ALIGNCENTER|UG_ALIGNVCENTER);
	QuickSetBitmap(1,7,&m_bitmap2);

	QuickSetText(2,7,"Right &V Centered");
	QuickSetAlignment(2,7,UG_ALIGNRIGHT|UG_ALIGNVCENTER);
	QuickSetBitmap(2,7,&m_bitmap2);

	QuickSetText(0,8,"Left &Bottom aligned");
	QuickSetAlignment(0,8,UG_ALIGNLEFT|UG_ALIGNBOTTOM);
	QuickSetBitmap(0,8,&m_bitmap2);

	QuickSetText(1,8,"H Center & Bottom ");
	QuickSetAlignment(1,8,UG_ALIGNCENTER|UG_ALIGNBOTTOM);
	QuickSetBitmap(1,8,&m_bitmap2);

	QuickSetText(2,8,"Right & Bottom");
	QuickSetAlignment(2,8,UG_ALIGNRIGHT|UG_ALIGNBOTTOM);
	QuickSetBitmap(2,8,&m_bitmap2);

	// cell with bitmaps and other cell types
	QuickSetCellType(0,10,UGCT_CHECKBOX);
	QuickSetAlignment(0,10,UG_ALIGNVCENTER|UG_ALIGNCENTER);
	QuickSetBitmap(0,10,&m_bitmap3);

	QuickSetCellType(1,10,spinIndex );
	QuickSetAlignment(1,10,UG_ALIGNVCENTER|UG_ALIGNCENTER);
	QuickSetText(1,10,"2");
	QuickSetCellTypeEx(1,10,UGCT_NORMALLABELTEXT);
	QuickSetBitmap(1,10,&m_bitmap2);
	
	QuickSetText(2,10,"Page");
	QuickSetLabelText(2,10,"Page\nFolder\nNumber\n");
	QuickSetCellType(2,10,UGCT_DROPLIST);
	QuickSetAlignment(2,10,UG_ALIGNVCENTER|UG_ALIGNCENTER);
	QuickSetBitmap(2,10,&m_bitmap7);

	QuickSetText(3,10,"Bitmap with Multi-Line Text");
	QuickSetCellTypeEx(3,10,UGCT_NORMALMULTILINE);
	QuickSetAlignment(3,10,UG_ALIGNVCENTER|UG_ALIGNCENTER);
	QuickSetBitmap(3,10,&m_bitmap5);

	// setup cells that will be changed on the fly
	QuickSetText(0,12,"Click Here");
	QuickSetBitmap(0,12,&m_bitmap2);
	QuickSetText(1,12,"Click Here");
	QuickSetBitmap(1,12,&m_bitmap2);
	QuickSetText(2,12,"Click Here");
	QuickSetBitmap(2,12,&m_bitmap7);
	QuickSetText(3,12,"Click Here");
	QuickSetBitmap(3,12,&m_bitmap7);
}


/***************************************************
sections - UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
			UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
****************************************************/
void MyCug::OnMenuCommand(int col,long row,int section,int item){
}
/***************************************************
return UG_SUCCESS to allow the menu to appear
return 1 to not allow the menu to appear
****************************************************/
int MyCug::OnMenuStart(int col,long row,int section){
	return TRUE;
}
/******************************************************
*******************************************************/
int MyCug::OnCellTypeNotify(long ID,int col,long row,long msg,long param){
	if(col ==1 && row ==10){
		CUGCell cell;
		GetCell(col,row,&cell);
		double  d = cell.GetNumber();
		if(msg == UGCT_SPINBUTTONUP)
			d ++;
		if(msg == UGCT_SPINBUTTONDOWN)
			d --;
		if(d >7)
			d = 2;
		if(d<2)
			d = 7;
		cell.SetNumber(d);
		if(d==2)
			//cell.SetBitmap(m_bitmap2);
			cell.SetBitmap(&m_bitmap2);
		if(d==3)
			cell.SetBitmap(&m_bitmap3);
		if(d==4)
			cell.SetBitmap(&m_bitmap4);
		if(d==5)
			cell.SetBitmap(&m_bitmap5);
		if(d==6)
			cell.SetBitmap(&m_bitmap6);
		if(d==7)
			cell.SetBitmap(&m_bitmap7);
		SetCell(col,row,&cell);
	}

	else if(ID == UGCT_DROPLIST && col ==2 && row ==10){
		if(msg == UGCT_DROPLISTSELECT){
			CString *s = (CString*)param;
			if(*s == "Page")
				QuickSetBitmap(col,row,&m_bitmap7);
			if(*s == "Folder")
				QuickSetBitmap(col,row,&m_bitmap2);
			if(*s == "Number")
				QuickSetBitmap(col,row,&m_bitmap5);
		}
	}
	return TRUE;
}

/******************************************************
*******************************************************/
void MyCug::OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed){
	OnLClicked(col,row,1,rect,point,processed);
}

/******************************************************
	
	  Change the bitmap displayed upon double clicking on it

*******************************************************/
void MyCug::OnLClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL  processed){
	// if mouse button pressed, and row == 12, then change bitmap
	if(updn){
		if(row == 12){
			if(col ==0 || col ==1){
				// Change between a closed folder and an open  
				// folder

				CUGCell cell;
				GetCell(col,row,&cell);
				if(cell.GetBitmap() == &m_bitmap2)
					cell.SetBitmap(&m_bitmap6);
				else
					cell.SetBitmap(&m_bitmap2);
				SetCell(col,row,&cell);
				RedrawCell(col,row);
			}
			if(col ==2 || col ==3){	
				// Chnage between a blank page and 
				// a blank page with a check mark
				CUGCell cell;
				GetCell(col,row,&cell);
				if(cell.GetBitmap() == &m_bitmap7)
					cell.SetBitmap(&m_bitmap4);
				else
					cell.SetBitmap(&m_bitmap7);
				SetCell(col,row,&cell);
				RedrawCell(col,row);
			}
		}
	}
}
/***************************************************
	we override this function to fill the empty 
	are of the grid with the button face  color
	otherwise it will return the default for the rest of the 
	grid control memebres

****************************************************/
COLORREF MyCug::OnGetDefBackColor(int section){
	return GetSysColor(COLOR_BTNFACE);	
}

