/***************************************************
****************************************************
Skeleton Class for a Derived MyCug

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
****************************************************/

#include "stdafx.h"
#include "MyCug.h"
#include "resource.h"


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
void MyCug::OnSetup(){	
	
	int				COLS = 9;

	RECT			rect = {0,0,0,0};
	int				ROWS = 8;
	CUGCell			cell;
	int				x,y;
	CString			string;
	LPSTR			hdgs[] = {"Plain","AutoExpand","MultiLine","Fonts","Validation","Phone#","Dates","Numbers","Letters","Password ","Password Text"};
	LPSTR			cells[] = {"Plain entry","Auto Expanding Editing","MultiLine Text\r\nIn A Cell","Fonts","Abcd","(999)999-9999","01/01/98","12345","ABCDEF","Password","Password"};
	LPSTR			masks[] = {"","","","","????","(999)999-9999","99/99/99","99999","??????????"};

	//setup the fonts
	m_font1.CreateFont(16,0,0,0,400,0,0,0,0,0,0,0,0,"Arial");
	m_font2.CreateFont(20,0,0,0,600,0,0,0,0,0,0,0,0,"Times New Roman");
	m_font3.CreateFont(12,0,0,0,400,0,0,0,0,0,0,0,0,"MS Sans Serif");
	SetDefFont(&m_font1);

	// Set the general appearence in a reasonable width and height
	SetDefRowHeight(34);
	SetDefColWidth(90);
	
	// Construct the rows and columns  
	SetNumberRows(ROWS);
	SetNumberCols(COLS);
	
	//setup the top heading
	for(x=0;x< COLS ;x++){
		QuickSetText(x,-1,hdgs[x]);
	}

	//EnableCellOverLap( FALSE );

	//setup the grid area
	for(y=0;y<ROWS;y++){
		for(x=0;x< COLS;x++){
				QuickSetText(x,y,cells[x]);
			if(strlen(masks[x]) >0)	
				QuickSetMask(x,y,masks[x]);	// Apply the edit mask to the cell
			if(x == 2)
				QuickSetCellTypeEx(x,y,UGCT_NORMALMULTILINE);	// Apply extended style to the cell
			if(x == 3){
				if(y%3 == 0)	
					QuickSetFont(x,y,&m_font2);	// Change the font of the text to our newly created  fonts
				if(y%3 == 1)
					QuickSetFont(x,y,&m_font3);// Change the font of the text to our newly created  fonts
			}
		}
	}
	StartEdit();
}
/***********************************************
On Double Click
*************************************************/
void MyCug:: OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed){
	StartEdit();
	
}
/***************************************************
OnTH_LClicked
	Sent whenever the user double clicks the left mouse
	button within the top heading

	'col' is negative if the area clicked in is not valid
****************************************************/
void MyCug::OnTH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed){
		StartEdit(col,row,0);
}

/***************************************************
OnKeyDown
	Sent whenever the user types when the grid has
	focus. The keystroke can be modified here as well.
	(See WM_KEYDOWN for more information)
****************************************************/
void MyCug::OnKeyDown(UINT *vcKey,BOOL processed){
		if(*vcKey == VK_DELETE)
		if(DeleteCell(GetCurrentCol(),GetCurrentRow()) == UG_SUCCESS)
			RedrawAll();
}
/***************************************************
OnCharDown
	Sent whenever the user types when the grid has
	focus. The keystroke can be modified here as well.
	(See WM_CHAR for more information)
****************************************************/
void MyCug::OnCharDown(UINT *vcKey,BOOL processed){
	if(!processed)	// Start new session of edit if we are not already editing
		StartEdit(*vcKey);
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
	
}

/***************************************************
OnEditStart
	This message is sent whenever the grid is ready 
	to start editing a cell
	A return of TRUE allows the editing a return of
	FALSE stops editing
	Plus the properties of the CEdit class can be modified
****************************************************/
int MyCug::OnEditStart(int col, long row,CWnd **edit)
{
	return TRUE;
}
/***************************************************
OnEditVerify
	This is send when the editing is about to end
****************************************************/
int MyCug::OnEditVerify(int col, long row,CWnd *edit,UINT *vcKey){
		return TRUE;
}
/***************************************************
OnEditFinish this is send when editing is finished
****************************************************/
int MyCug::OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag){
	
	if(col == 4 && !cancelFlag){	

		int len = lstrlen(string);
		if(len != 4){
			AfxMessageBox("Enter 4 Charaters Only");
			return FALSE;
		}

	}
	return TRUE;
}
/***************************************************
OnEditFinish this is send when editing is finished
****************************************************/
int MyCug::OnEditContinue(int oldcol,long oldrow,int* newcol,long* newrow){
	return TRUE;
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
