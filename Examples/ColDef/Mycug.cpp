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

// defines for the popup menu ids
#define	 MI_CHANGE_FONT 1000  
#define	 MI_HALIGN_LEFT	1010
#define	 MI_HALIGN_CENTRE 1011
#define	 MI_HALIGN_RIGHT 1012
#define	 MI_VALIGN_TOP 1020
#define	 MI_VALIGN_CENTRE 1021
#define	 MI_VALIGN_BOTTOM 1022
#define	 MI_BACKCOLOR_RED 1030
#define	 MI_BACKCOLOR_GREEN 1031
#define	 MI_BACKCOLOR_BLUE	1032
#define	 MI_BACKCOLOR_WHITE 1033
#define	 MI_BACKCOLOR_OTHER 1034


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
	int rows = 20;
	int cols = 10;
	int i,j;
	CString temp;
	CUGCell	cell;

	// setup rows and columns	
	SetNumberRows(rows);
	SetNumberCols(cols);

	// fill cells with data
	GetCell(0,1,&cell);
	for (i = 0; i < cols; i++) {
		for (j = 0; j < rows; j++) {
			temp.Format("%d",(i+1)*(j+1));
			cell.SetText(temp);
			SetCell(i,j,&cell);
		}
	}

	// setup column headings
	for (i = 0; i < cols; i++) {
		temp.Format("%d",(i+1));
		cell.SetText(temp);
		SetCell(i,-1,&cell);
	}

	// setup row headings
	for (j = 0; j < rows; j++) {
		temp.Format("%d",(j+1));
		cell.SetText(temp);
		SetCell(-1,j,&cell);
		SetRowHeight(j, 45);
	}

	// setup font for entire grid
	LOGFONT lf={12,0,0,0,500,0,0,0,0,0,0,0,0,"MS Sans Serif"};
	for (i=0;i<10;i++)
		m_colFont[i].CreateFontIndirect(&lf);

	// set backcolor property for some columns
	cell.SetAlignment(UG_ALIGNCENTER);
	cell.SetBackColor(RGB(255,0,0));
	SetColDefault(0, &cell);

	cell.SetAlignment(UG_ALIGNRIGHT);
	cell.SetBackColor(RGB(0,255,0));
	SetColDefault(2, &cell);

	cell.SetAlignment(UG_ALIGNRIGHT|UG_ALIGNVCENTER);
	cell.SetBackColor(RGB(0,0,255));
	SetColDefault(4, &cell);

	cell.SetAlignment(UG_ALIGNBOTTOM);
	cell.SetBackColor(RGB(255,0,0));
	SetColDefault(6, &cell);

	cell.SetAlignment(UG_ALIGNTOP|UG_ALIGNVCENTER);
	cell.SetBackColor(RGB(0,0,255));
	SetColDefault(8, &cell);

	// create popup menu
	EnableMenu(TRUE);
	CMenu * pMenu = GetPopupMenu();
	CMenu tmpMenu;
	// add menu items for changing col properties
	// font menu item
	pMenu->AppendMenu(MF_STRING, MI_CHANGE_FONT, "Change Font");

	// Horizontal Alignment submenu
	tmpMenu.CreatePopupMenu();
	tmpMenu.AppendMenu(MF_STRING, MI_HALIGN_LEFT, "Left");
	tmpMenu.AppendMenu(MF_STRING, MI_HALIGN_CENTRE, "Centre");
	tmpMenu.AppendMenu(MF_STRING, MI_HALIGN_RIGHT, "Right");
	pMenu->AppendMenu(MF_POPUP, (UINT)tmpMenu.Detach(), "Horizontal Alignment");

	// Vertical Alignment submenu 
	tmpMenu.CreatePopupMenu();
	tmpMenu.AppendMenu(MF_STRING, MI_VALIGN_TOP, "Top");
	tmpMenu.AppendMenu(MF_STRING, MI_VALIGN_CENTRE, "Centre");
	tmpMenu.AppendMenu(MF_STRING, MI_VALIGN_BOTTOM, "Bottom");
	pMenu->AppendMenu(MF_POPUP, (UINT)tmpMenu.Detach(), "Vertical Alignment");

	// Back Color sunmenu
	tmpMenu.CreatePopupMenu();
	tmpMenu.AppendMenu(MF_STRING, MI_BACKCOLOR_RED, "Red");
	tmpMenu.AppendMenu(MF_STRING, MI_BACKCOLOR_GREEN, "Green");
	tmpMenu.AppendMenu(MF_STRING, MI_BACKCOLOR_BLUE, "Blue");
	tmpMenu.AppendMenu(MF_STRING, MI_BACKCOLOR_WHITE, "White");
	tmpMenu.AppendMenu(MF_STRING, MI_BACKCOLOR_OTHER, "Other...");
	pMenu->AppendMenu(MF_POPUP, (UINT)tmpMenu.Detach(), "BackColor");
}


/***************************************************
sections - UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
			UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
****************************************************/
void MyCug::OnMenuCommand(int col,long row,int section,int item){

	if(section != UG_GRID)
		return;
	CUGCell cell;
	short align;
	GetColDefault(col,&cell);

	switch(item){
	case MI_CHANGE_FONT:{	// change font
		LOGFONT lf;
		CFontDialog fontDlg(&lf);
		CFont* curr = cell.GetFont();
		if(!curr)
			curr=&m_colFont[col];
		curr->GetLogFont(&lf);
		if(fontDlg.DoModal()==IDOK){
			fontDlg.GetCurrentFont(&lf);
			curr->DeleteObject();
			curr->CreateFontIndirect(&lf);

			cell.SetFont(curr);						// set font size and style
			cell.SetTextColor (fontDlg.GetColor()); // set font color
			}
		}
		break;
	case MI_HALIGN_LEFT:	// change to Horisontal Alignment Left
		align = cell.GetAlignment();
		align|= UG_ALIGNLEFT;
		align&= ~UG_ALIGNCENTER;
		align&= ~UG_ALIGNRIGHT;
		cell.SetAlignment(align);
		break;
	case MI_HALIGN_CENTRE:  // change to Horisontal Alignment Centre
		align = cell.GetAlignment();
		align&= ~UG_ALIGNLEFT;
		align|= UG_ALIGNCENTER;
		align&= ~UG_ALIGNRIGHT;
		cell.SetAlignment(align);
		break;
	case MI_HALIGN_RIGHT:	// change to Horisontal Alignment Right
		align = cell.GetAlignment();
		align&= ~UG_ALIGNLEFT;
		align&= ~UG_ALIGNCENTER;
		align|= UG_ALIGNRIGHT;
		cell.SetAlignment(align);
		break;
	case MI_VALIGN_TOP:		// change to Vertical Alignment Top
		align = cell.GetAlignment();
		align|= UG_ALIGNTOP;
		align&= ~UG_ALIGNVCENTER;
		align&= ~UG_ALIGNBOTTOM;
		cell.SetAlignment(align);
		break;
	case MI_VALIGN_CENTRE:  // change to Vertical Alignment Centre
		align = cell.GetAlignment();
		align&= ~UG_ALIGNTOP;
		align|= UG_ALIGNVCENTER;
		align&= ~UG_ALIGNBOTTOM;
		cell.SetAlignment(align);
		break;
	case MI_VALIGN_BOTTOM:  // change to Vertical Alignment Bottom
		align = cell.GetAlignment();
		align&= ~UG_ALIGNTOP;
		align&= ~UG_ALIGNVCENTER;
		align|= UG_ALIGNBOTTOM;
		cell.SetAlignment(align);
		break;
	case MI_BACKCOLOR_RED:		// Set BackColor to Red
		cell.SetBackColor(RGB(255,0,0));
		break;
	case MI_BACKCOLOR_GREEN:	// Set BackColor to Green
		cell.SetBackColor(RGB(0,255,0));
		break;
	case MI_BACKCOLOR_BLUE:		// Set BackColor to Blue
		cell.SetBackColor(RGB(0,0,255));
		break;
	case MI_BACKCOLOR_WHITE:	// Set BackColor to White
		cell.SetBackColor(RGB(255,255,255));
		break;
	case MI_BACKCOLOR_OTHER: {  // Set BackColor to Other (user selected)
		CColorDialog clrDlg(cell.GetBackColor());
		if(clrDlg.DoModal()==IDOK)
			cell.SetBackColor(clrDlg.GetColor());
		}
		break;
	}

	SetColDefault(col,&cell);
	RedrawCol(col);
}
/***************************************************
return UG_SUCCESS to allow the menu to appear
return 1 to not allow the menu to appear
****************************************************/
int MyCug::OnMenuStart(int col,long row,int section){
	if(section != UG_GRID)
		return FALSE;
	return TRUE;
}
