/***************************************************
****************************************************
Skeleton Class for a Derived MyCug 
****************************************************
****************************************************/

#include "stdafx.h"
#include "resource.h"
#include "MyCug.h"
#include "cellview.h"

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
	UGXPThemes::CleanUp();
}

/***************************************************
OnSetup
	This function is called just after the grid window 
	is created or attached to a dialog item.
	It can be used to initially setup the grid
****************************************************/
void MyCug::OnSetup(){
	// set up local variables
	int rows = 20,
		cols = 4,
		i,j;
	CString temp;
	CUGCell	cell;

	SetHS_Height( 0 );
	// set up rows and cols...
	SetNumberRows(rows);
	SetNumberCols(cols);

	// fill in cells with some data
	for (i=0;i < cols;i++) 
		for (j=1;j < rows;j++) {
			temp.Format("%d",(i+1)*(j+1));
			QuickSetText(i,j,temp);
		}

	// set column headings
	for (i = 0; i < cols; i++) {
		temp.Format("%d",(i+1));
		QuickSetText(i,-1,temp);
	}
	// set row headings
	for (j = 0; j < rows; j++) {
		temp.Format("%d",(j+1));
		QuickSetText(-1,j,temp);
	}

	// Create fonts to be used through out the example
	m_font1.CreateFont(20,0,0,0,500,0,0,0,0,0,0,0,0,"Arial");
	m_font2.CreateFont(16,0,0,0,500,0,0,0,0,0,0,0,0,"MS Sans Serif");
	m_font3.CreateFont(12,0,0,0,600,0,0,0,0,0,0,0,0,"Courier");

	// We will set the bitmap property of some cells 
	// so we need to load bitmaps for use
	m_bitmap1.LoadBitmap(IDB_CHECK);
	m_bitmap2.LoadBitmap(IDB_HELLO);

	// Clear all cell propeerty for the cell object to
	// be used as a default for column 1
	GetCell (1,1,&cell);
	cell.ClearAll();
	cell.SetTextColor(RGB(255,0,100));
	cell.SetHTextColor(RGB(127,127,0));
	cell.SetBackColor(RGB(255,255,100));
	cell.SetHBackColor(RGB(155,155,0));
	cell.SetFont(&m_font3);
	cell.SetBitmap(&m_bitmap2);
	SetColDefault(1,&cell);
	// after populating the text color, Back color, highlight color, font and alignment
	// of the default cell apply it to be the default for column 1

	// Clear all cell propeerty for the cell object to
	// be used as a default for column 2
	GetCell (2,1,&cell);
	cell.ClearAll();
	cell.SetTextColor(RGB(255,77,99));
	cell.SetHTextColor(RGB(255,255,255));
	cell.SetBackColor(RGB(0,255,255));
	cell.SetHBackColor(RGB(255,0,255));
	cell.SetFont(&m_font1);
	cell.SetAlignment(UG_ALIGNCENTER&UG_ALIGNBOTTOM);
	SetColDefault(2,&cell);
	//  after populating the text color, Back color, highlight color, font and alignment
	// of the default cell apply it to be the default for column 2

	// Now lets change the properties for single cells
	// lets start with cell 1,1
	GetCell(1,1,&cell);
	cell.SetTextColor(RGB(25,237,99));
	cell.SetHTextColor(RGB(25,218,44));
	cell.SetBackColor(RGB(0,255,255));
	cell.SetHBackColor(RGB(0,255,0));
	cell.SetFont(&m_font2);
	cell.SetAlignment(UG_ALIGNCENTER|UG_ALIGNBOTTOM);
	SetCell(1,1,&cell);

	// Now cell 2,1
	GetCell(2,1,&cell);
	cell.SetTextColor(RGB(0,0,255));
	cell.SetHTextColor(RGB(0,0,255));
	cell.SetBackColor(RGB(0,255,0));
	cell.SetHBackColor(RGB(0,255,0));
	SetCell(2,1,&cell);
	
	// Next cell 1,4
	GetCell(1,4,&cell);
	cell.SetFont(&m_font2);
	cell.SetAlignment(UG_ALIGNCENTER);
	SetCell(1,4,&cell);

	// The first cell in the grid
	GetCell(0,0,&cell);
	cell.SetTextColor(RGB(122,122,122));
	cell.SetHTextColor(RGB(11,11,11));
	cell.SetBackColor(RGB(0,255,0));
	cell.SetHBackColor(RGB(0,0,0));
	cell.SetBitmap(&m_bitmap1);
	SetCell(0,0,&cell);

	// give some instruction
	QuickSetText(0,0,"Right click to see the properties of the cell");

	// add a popup menu
	EnableMenu(TRUE);
	AddMenuItem(1000, "View Cell Properties");
	AddMenuItem(1001, "View Cell Indirect Properties");

	// allow multi select to see the highlight cols
	SetMultiSelectMode(TRUE);
	StoreOriginalCols();
}

/***************************************************
sections - UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
			UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
****************************************************/
void MyCug::OnMenuCommand(int col,long row,int section,int item){
	if(item==1000){			// get cell properties
		CUGCell cell;
		GetCell(col,row,&cell);
		CUGCellPropViewer dlg(cell);
		dlg.DoModal();
	}
	else if(item==1001){	// get cell idirect properties
		CUGCell cell;
		GetCellIndirect(col,row,&cell);
		CUGCellPropViewer dlg(cell);
		dlg.DoModal();
	}
}
/***************************************************
return UG_SUCCESS to allow the menu to appear
return 1 to not allow the menu to appear
****************************************************/
int MyCug::OnMenuStart(int col,long row,int section){
	return TRUE;
}

/***************************************************
OnGetDefBackColor
****************************************************/
COLORREF MyCug::OnGetDefBackColor(int section){
//	return RGB(255,255,255);
	return GetSysColor (COLOR_BTNFACE);
}

/////////////////////////////////////////////////////////////////////////////
//	OnColSized
//		This is sent when the user finished sizing the 
//		given column (see above for more details)
void MyCug::OnColSized(int col,int *width)
{
	StoreOriginalCols();
	FitToWindow( 0, GetNumberCols() - 1 );
}

/////////////////////////////////////////////////////////////////////////////
//	FitToWindow
//		Overwrites functionality of existing FitToWindow function
int MyCug::FitToWindow(int startCol, int endCol)
{
	RECT rect;
	int screenwidth,
		columnwidths,
		loop,
		newwidth;
	float ratio;

	// check if the range specified is within grid's column range
	if(startCol < 0 || endCol < startCol || endCol >= m_GI->m_numberCols)
		return UG_ERROR;
	
	// get the grid's window width
	m_CUGGrid->GetClientRect(&rect);
	screenwidth = rect.right;

	// find out what is the total (original) width of all columns in range
	columnwidths = 0;
	for( loop = startCol; loop <= endCol; loop++ )
	{
		columnwidths += m_originalCols[loop];
	}
	
	// calculate the ratio
	ratio = ((float)screenwidth) / ((float)columnwidths );

	// set new width for all columns in range
	for( loop = startCol; loop < endCol; loop++ )
	{
		newwidth = (int)( (float)m_originalCols[loop] * ratio );
		SetColWidth( loop,newwidth );
		screenwidth -= newwidth;
	}
	// because of possible fractions in the multiplication, we need to set the
	// last column width based on how many pixels are left, not by what we need
	// there is a possibility of this last column to have a slightly different
	// width than all other columns in the range.
	SetColWidth( endCol, screenwidth );
	
	Update();
	return UG_SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////
//	StoreOriginalCols
//		Here we will store all original column widths,
//		to be used by the FitToWindow function
int MyCug::StoreOriginalCols()
{
	if ( m_originalCols.GetUpperBound() > 0 )
		m_originalCols.RemoveAll();

	m_originalCols.SetSize ( GetNumberCols (), 0 );

	for ( int col = 0; col < GetNumberCols (); col ++ )
	{
		m_originalCols.SetAt ( col, GetColWidth(col) );
	}
	
	return UG_SUCCESS;
}
