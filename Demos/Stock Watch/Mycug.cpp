/////////////////////////////////////////////////////////////////////////////
//	Skeleton Class for a Derived MyCug

#include "stdafx.h"
#include "resource.h"
#include "MyCug.h"
#include "UGStrOp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(MyCug,CUGCtrl)
	//{{AFX_MSG_MAP(MyCug)
	ON_WM_SIZE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Standard MyCug construction/destruction
MyCug::MyCug()
{
	UGXPThemes::UseThemes(true);
}

MyCug::~MyCug()
{
	UGXPThemes::CleanUp();
}

/////////////////////////////////////////////////////////////////////////////
//	OnSetup
//		This function is called just after the grid window 
//		is created or attached to a dialog item.
//		It can be used to initially setup the grid
void MyCug::OnSetup()
{
	// Set up the Tab controls
	int	nIndex = 0;
	CUGCell cell;

	GetGridDefault(&cell);
	cell.SetBackColor(MY_COLOR_BACK);
	cell.SetTextColor(MY_COLOR_TEXT);
	cell.UseThemes(false);
	SetGridDefault(&cell);
	EnableExcelBorders(FALSE);
	SetHighlightRow(TRUE, FALSE);
	SetDoubleBufferMode(TRUE);
	SetUserSizingMode( FALSE );

	AddTab("Technology", nIndex++);
	AddTab("Favorite", nIndex++);

	// Create and set default font
	AddFont("Arial", -12, FW_NORMAL);
	AddFont("Arial", -12, FW_BOLD);
	SetDefFont(0);

	// Add bitmaps
	AddBitmap(IDB_BITMAP_ARROW_UP);
	AddBitmap(IDB_BITMAP_ARROW_DOWN);

	// Add cell type
	m_nArrowCellIndx = AddCellType(&m_celllArrow);
	
	// Set number of Sheets 
	SetNumberSheets(2);

	// Start timers
	srand( (unsigned)time( NULL ) );
	SetTimer(0, 75, NULL);
	SetTimer(1, 1000, NULL);
}

/////////////////////////////////////////////////////////////////////////////
//	OnSheetSetup	
//		This notification is called for each additional sheet that the grid
//		might contain, here you can customize each sheet in the grid.
//	Params:
//		sheetNumber - idndex of current sheet
//	Return:
//		<none>
void MyCug::OnSheetSetup(int sheetNumber)
{
	int	nRow = 0, nCol = 0;
	// ****************************************************************
	// ** Set up columns
	// ****************************************************************
	CUGCell cell;

	GetGridDefault(&cell);
	cell.SetBackColor(MY_COLOR_BACK);
	cell.SetTextColor(MY_COLOR_TEXT);
	SetGridDefault(&cell);
	EnableExcelBorders(FALSE);
	SetHighlightRow(TRUE, FALSE);
	SetDoubleBufferMode(TRUE);
	SetDefFont(0);
	SetSH_Width(0);
	
	// Number
	SetNumberCols(7);

	// Names 
	QuickSetText(nCol++, -1, "Name");
	QuickSetText(nCol++, -1, "Symbol");
	QuickSetText(nCol++, -1, "Bid");
	QuickSetText(nCol++, -1, "Ask");
	QuickSetText(nCol++, -1, "Last");
	QuickSetText(nCol++, -1, "Net");
	QuickSetText(nCol++, -1, "Volume");

	// Header font
	for(int i = 0; i < GetNumberCols(); i++)
	{
		QuickSetFont(i, -1, 1);
	}

	// Alignment
	GetColDefault(6, &cell);
	cell.SetAlignment(UG_ALIGNRIGHT);
	SetColDefault(6, &cell);
	cell.SetAlignment(UG_ALIGNCENTER);
	SetColDefault(1, &cell);
	SetColDefault(2, &cell);
	SetColDefault(3, &cell);
	SetColDefault(5, &cell);	

	cell.SetCellType(m_nArrowCellIndx);
	SetColDefault(4, &cell);
	

	// ****************************************************************
	// ** Set up the Sheet data
	// ****************************************************************
	SetSheetNumber(sheetNumber);

	if(sheetNumber == 0)
	{
		nRow = 0;
		SetNumberRows(10);

		nCol = 0;
		QuickSetText(nCol++, nRow, "ABS Direct Inc");
		QuickSetText(nCol++, nRow, "ABS");
		QuickSetText(nCol++, nRow, "78.10");
		QuickSetText(nCol++, nRow, "80.50");
		GetCell(nCol, nRow, &cell);
		cell.SetText("80.40");
		cell.SetParam(0);
		SetCell(nCol++, nRow, &cell);
		QuickSetText(nCol++, nRow, "+2.10");
		QuickSetText(nCol++, nRow++, "150000");

		nCol = 0;
		QuickSetText(nCol++, nRow, "Adv. Computer Systems Ltd");
		QuickSetText(nCol++, nRow, "ACS");
		QuickSetText(nCol++, nRow, "36.87");
		QuickSetText(nCol++, nRow, "35.20");
		GetCell(nCol, nRow, &cell);
		cell.SetText("35.20");
		cell.SetParam(1);
		SetCell(nCol++, nRow, &cell);
		QuickSetText(nCol++, nRow, "+.20");
		QuickSetText(nCol++, nRow++, "100200");

		nCol = 0;
		QuickSetText(nCol++, nRow, "AGY Inc");
		QuickSetText(nCol++, nRow, "AGY");
		QuickSetText(nCol++, nRow, "37.85");
		QuickSetText(nCol++, nRow, "38.00");
		GetCell(nCol, nRow, &cell);
		cell.SetText("37.85");
		cell.SetParam(0);
		SetCell(nCol++, nRow, &cell);
		QuickSetText(nCol++, nRow, "-1.30");
		QuickSetText(nCol++, nRow++, "20000");

		nCol = 0;
		QuickSetText(nCol++, nRow, "Emerald Software Inc");
		QuickSetText(nCol++, nRow, "EMS");
		QuickSetText(nCol++, nRow, "12.40");
		QuickSetText(nCol++, nRow, "12.60");
		GetCell(nCol, nRow, &cell);
		cell.SetText("12.50");
		cell.SetParam(0);
		SetCell(nCol++, nRow, &cell);
		QuickSetText(nCol++, nRow, "+.10");
		QuickSetText(nCol++, nRow++, "1000");

		nCol = 0;
		QuickSetText(nCol++, nRow, "IT Consulting Inc");
		QuickSetText(nCol++, nRow, "ITC");
		QuickSetText(nCol++, nRow, "18.75");
		QuickSetText(nCol++, nRow, "19.00");
		GetCell(nCol, nRow, &cell);
		cell.SetText("19.00");
		cell.SetParam(1);
		SetCell(nCol++, nRow, &cell);
		QuickSetText(nCol++, nRow, "-.25");
		QuickSetText(nCol++, nRow++, "50000");

		nCol = 0;
		QuickSetText(nCol++, nRow, "NCA Inc");
		QuickSetText(nCol++, nRow, "NCA");
		QuickSetText(nCol++, nRow, "24.50");
		QuickSetText(nCol++, nRow, "25.00");
		GetCell(nCol, nRow, &cell);
		cell.SetText("24.75");
		cell.SetParam(1);
		SetCell(nCol++, nRow, &cell);
		QuickSetText(nCol++, nRow, "+1.25");
		QuickSetText(nCol++, nRow++, "650000");

		nCol = 0;
		QuickSetText(nCol++, nRow, "MCH Ltd");
		QuickSetText(nCol++, nRow, "MCH");
		QuickSetText(nCol++, nRow, "69.70");
		QuickSetText(nCol++, nRow, "70.20");
		GetCell(nCol, nRow, &cell);
		cell.SetText("70.20");
		cell.SetParam(1);
		SetCell(nCol++, nRow, &cell);
		QuickSetText(nCol++, nRow, "-.20");
		QuickSetText(nCol++, nRow++, "20200");

		nCol = 0;
		QuickSetText(nCol++, nRow, "Smart Communications Inc");
		QuickSetText(nCol++, nRow, "SMC");
		QuickSetText(nCol++, nRow, "98.10");
		QuickSetText(nCol++, nRow, "99.25");
		GetCell(nCol, nRow, &cell);
		cell.SetText("99.00");
		cell.SetParam(0);
		SetCell(nCol++, nRow, &cell);
		QuickSetText(nCol++, nRow, "-.30");
		QuickSetText(nCol++, nRow++, "900000");

		nCol = 0;
		QuickSetText(nCol++, nRow, "Wireless Systems Cp");
		QuickSetText(nCol++, nRow, "WSY");
		QuickSetText(nCol++, nRow, "78.20");
		QuickSetText(nCol++, nRow, "81.00");
		GetCell(nCol, nRow, &cell);
		cell.SetText("79.80");
		cell.SetParam(0);
		SetCell(nCol++, nRow, &cell);
		QuickSetText(nCol++, nRow, "-1.20");
		QuickSetText(nCol++, nRow++, "250000");

		nCol = 0;
		QuickSetText(nCol++, nRow, "WYC Inc");
		QuickSetText(nCol++, nRow, "WYC");
		QuickSetText(nCol++, nRow, "19.10");
		QuickSetText(nCol++, nRow, "20.00");
		GetCell(nCol, nRow, &cell);
		cell.SetText("19.90");
		cell.SetParam(0);
		SetCell(nCol++, nRow, &cell);
		QuickSetText(nCol++, nRow, "-.10");
		QuickSetText(nCol++, nRow++, "30000");
	}

	if(sheetNumber == 1)
	{
		nRow = 0;
		SetNumberRows(12);

		nCol = 0;
		QuickSetText(nCol++, nRow, "Astor Systems Inc");
		QuickSetText(nCol++, nRow, "ASY");
		QuickSetText(nCol++, nRow, "22.20");
		QuickSetText(nCol++, nRow, "23.50");
		GetCell(nCol, nRow, &cell);
		cell.SetText("23.40");
		cell.SetParam(0);
		SetCell(nCol++, nRow, &cell);
		QuickSetText(nCol++, nRow, "+1.00");
		QuickSetText(nCol++, nRow++, "220000");

		nCol = 0;
		QuickSetText(nCol++, nRow, "Asteck Consulting Ltd");
		QuickSetText(nCol++, nRow, "ACS");
		QuickSetText(nCol++, nRow, "16.27");
		QuickSetText(nCol++, nRow, "17.50");
		GetCell(nCol, nRow, &cell);
		cell.SetText("17.50");
		cell.SetParam(1);
		SetCell(nCol++, nRow, &cell);
		QuickSetText(nCol++, nRow, "-.10");
		QuickSetText(nCol++, nRow++, "10200");

		nCol = 0;
		QuickSetText(nCol++, nRow, "Basset Inc");
		QuickSetText(nCol++, nRow, "BAS");
		QuickSetText(nCol++, nRow, "55.45");
		QuickSetText(nCol++, nRow, "58.00");
		GetCell(nCol, nRow, &cell);
		cell.SetText("57.60");
		cell.SetParam(0);
		SetCell(nCol++, nRow, &cell);
		QuickSetText(nCol++, nRow, "+3.30");
		QuickSetText(nCol++, nRow++, "3000000");

		nCol = 0;
		QuickSetText(nCol++, nRow, "TTY Construction Inc");
		QuickSetText(nCol++, nRow, "TTY");
		QuickSetText(nCol++, nRow, "11.90");
		QuickSetText(nCol++, nRow, "12.30");
		GetCell(nCol, nRow, &cell);
		cell.SetText("12.10");
		cell.SetParam(0);
		SetCell(nCol++, nRow, &cell);
		QuickSetText(nCol++, nRow, "+.30");
		QuickSetText(nCol++, nRow++, "20000");

		nCol = 0;
		QuickSetText(nCol++, nRow, "IT Consulting Inc");
		QuickSetText(nCol++, nRow, "ITC");
		QuickSetText(nCol++, nRow, "18.75");
		QuickSetText(nCol++, nRow, "19.00");
		GetCell(nCol, nRow, &cell);
		cell.SetText("19.00");
		cell.SetParam(1);
		SetCell(nCol++, nRow, &cell);
		QuickSetText(nCol++, nRow, "-.25");
		QuickSetText(nCol++, nRow++, "50000");

		nCol = 0;
		QuickSetText(nCol++, nRow, "KFG Systems Inc");
		QuickSetText(nCol++, nRow, "KFG");
		QuickSetText(nCol++, nRow, "34.70");
		QuickSetText(nCol++, nRow, "38.00");
		GetCell(nCol, nRow, &cell);
		cell.SetText("38.75");
		cell.SetParam(1);
		SetCell(nCol++, nRow, &cell);
		QuickSetText(nCol++, nRow, "-1.75");
		QuickSetText(nCol++, nRow++, "950000");

		nCol = 0;
		QuickSetText(nCol++, nRow, "DFP Ltd");
		QuickSetText(nCol++, nRow, "DFP");
		QuickSetText(nCol++, nRow, "66.30");
		QuickSetText(nCol++, nRow, "67.30");
		GetCell(nCol, nRow, &cell);
		cell.SetText("67.00");
		cell.SetParam(1);
		SetCell(nCol++, nRow, &cell);
		QuickSetText(nCol++, nRow, "+4.20");
		QuickSetText(nCol++, nRow++, "120000");

		nCol = 0;
		QuickSetText(nCol++, nRow, "ERT Communications Inc");
		QuickSetText(nCol++, nRow, "ERT");
		QuickSetText(nCol++, nRow, "48.54");
		QuickSetText(nCol++, nRow, "49.60");
		GetCell(nCol, nRow, &cell);
		cell.SetText("49.60");
		cell.SetParam(0);
		SetCell(nCol++, nRow, &cell);
		QuickSetText(nCol++, nRow, "+.10");
		QuickSetText(nCol++, nRow++, "850000");

		nCol = 0;
		QuickSetText(nCol++, nRow, "Fast ConstructionCp");
		QuickSetText(nCol++, nRow, "FCN");
		QuickSetText(nCol++, nRow, "77.30");
		QuickSetText(nCol++, nRow, "77.40");
		GetCell(nCol, nRow, &cell);
		cell.SetText("77.40");
		cell.SetParam(0);
		SetCell(nCol++, nRow, &cell);
		QuickSetText(nCol++, nRow, "-.10");
		QuickSetText(nCol++, nRow++, "4500000");

		nCol = 0;
		QuickSetText(nCol++, nRow, "Niss Inc");
		QuickSetText(nCol++, nRow, "NSS");
		QuickSetText(nCol++, nRow, "17.10");
		QuickSetText(nCol++, nRow, "18.00");
		GetCell(nCol, nRow, &cell);
		cell.SetText("18.90");
		cell.SetParam(0);
		SetCell(nCol++, nRow, &cell);
		QuickSetText(nCol++, nRow, "-2.90");
		QuickSetText(nCol++, nRow++, "300000");

		nCol = 0;
		QuickSetText(nCol++, nRow, "FGH Wireless Systems Cp");
		QuickSetText(nCol++, nRow, "FGH");
		QuickSetText(nCol++, nRow, "78.20");
		QuickSetText(nCol++, nRow, "81.00");
		GetCell(nCol, nRow, &cell);
		cell.SetText("79.80");
		cell.SetParam(0);
		SetCell(nCol++, nRow, &cell);
		QuickSetText(nCol++, nRow, "-1.20");
		QuickSetText(nCol++, nRow++, "250000");

		nCol = 0;
		QuickSetText(nCol++, nRow, "WYC Inc");
		QuickSetText(nCol++, nRow, "WYC");
		QuickSetText(nCol++, nRow, "19.10");
		QuickSetText(nCol++, nRow, "20.00");
		GetCell(nCol, nRow, &cell);
		cell.SetText("19.90");
		cell.SetParam(0);
		SetCell(nCol++, nRow, &cell);
		QuickSetText(nCol++, nRow, "-.10");
		QuickSetText(nCol++, nRow++, "30000");
	}

	for(nRow=0; nRow<GetNumberRows(); nRow++)
	{
		QuickSetBackColor(0, nRow, MY_COLOR_BACK);
	}

}

/////////////////////////////////////////////////////////////////////////////
//	OnCanMove
//		Sent when current cell is changed
//	Params:
//		oldcol, oldrow - 
//		newcol, newrow - cell that is gaining focus
//	Return:
//		TRUE - to allow the move
//		FALSE - to prevent new cell from gaining focus
int MyCug::OnCanMove(int oldcol,long oldrow,int newcol,long newrow)
{
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnCanViewMove
//		Is called when current grid view is about to be scrolled
//	Params:
//		oldcol, oldrow - coordinates of orriginal top-left cell
//		newcol, newrow - coordinates of top-left cell that is gaining the focus
//	Return:
//		TRUE - to allow for the scroll
//		FALSE - to prevent the view from scrolling
int MyCug::OnCanViewMove(int oldcol,long oldrow,int newcol,long newrow)
{
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnHitBottom
//		This notification allows for dynamic row loading, it will be called
//		when the grid drawing function has hit the last row.  It allows the grid
//		to ask the datasource/developer if there are additional rows to be displayed.
//	Params:
//		numrows		- known number of rows in the grid
//		rowspast	- number of extra rows that the grid is looking for in the datasource
//		rowsfound	- number of rows actually found, usually equal to rowspast or zero.
//	Return:
//		<none>
void MyCug::OnHitBottom(long numrows,long rowspast,long rowsfound)
{
	// used by the datasources
	/*if ( rowsfound > 0 )
	{
		SetNumberRows( numrows + rowsfound, FALSE );
	}*/
}

/////////////////////////////////////////////////////////////////////////////
//	OnHitTop
//		Is called when the user has scrolled all the way to the top of the grid.
//	Params:
//		numrows		- known number of rows in the grid
//		rowspast	- number of extra rows that the grid is looking for in the datasource
//	Return:
//		<none>
void MyCug::OnHitTop(long numrows,long rowspast)
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnCanSizeCol
//		Sent when the user is about to size a given column
//	Params:
//		col - identifies column number that will be sized
//	Return:
//		TRUE - to allow sizing
//		FALSE - to prevent sizing
int MyCug::OnCanSizeCol(int col)
{
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnColSizing
//		Sent when the user is sizing a column
//	Params:
//		col - column currently sizing
//		width - current new column width
//	Return:
//		<none>
void MyCug::OnColSizing(int col,int *width)
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnColSized
//		This is sent when the user finished sizing the 
//		given column.
//	Params:
//		col - column sized
//		width - new column width
//	Return:
//		<none>
void MyCug::OnColSized(int col,int *width)
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnCanSizeRow
//		Sent when the user is about to start sizing of a row
//	Params:
//		row - identifies row number that will be sized
//	Return:
//		TRUE - to allow sizing
//		FALSE - to prevent sizing
int MyCug::OnCanSizeRow(long row)
{
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnRowSizing
//		Sent durring user sizing of a row, can provide feed back on current height
//	Params:
//		row - row sizing
//		width - current new row height
//	Return:
//		<none>
void MyCug::OnRowSizing(long row,int *height)
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnRowSized
//		This is sent when the user is finished sizing hte
//		given row.
//	Params:
//		row - row sized
//		width - new row height
//	Return:
//		<none>
void MyCug::OnRowSized(long row,int *height)
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnCanSizeSideHdg
//		Sent when the user is about to start sizing of the side heading
//	Params:
//		<none>
//	Return:
//		TRUE - to allow sizing
//		FALSE - to prevent sizing
int MyCug::OnCanSizeSideHdg()
{
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnSideHdgSizing
//		Sent while the heading is being sized
//	Params:
//		width - current new width of the side heading
//	Return:
//		TRUE - to accept current new size
//		FALSE - to stop sizing, the size is either too large or too small
int MyCug::OnSideHdgSizing(int *width)
{
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnSideHdgSized
//		Sent when the user has completed the sizing of the side heading
//	Params:
//		width - new width
//	Return:
//		TRUE - to accept new size
//		FALSE - to revert to old size
int MyCug::OnSideHdgSized(int *width)
{
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnCanSizeTopHdg
//		Sent when the user is about to start sizing of the top heading
//	Params:
//		<none>
//	Return:
//		TRUE - to allow sizing
//		FALSE - to prevent sizing
int MyCug::OnCanSizeTopHdg()
{
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnTopHdgSizing
//		Sent while the top heading is being sized
//	Params:
//		height - current new height of the top heading
//	Return:
//		TRUE - to accept current new size
//		FALSE - to stop sizing, the size is either too large or too small
int MyCug::OnTopHdgSizing(int *height)
{
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnTopHdgSized
//		Sent when the user has completed the sizing of the top heading
//	Params:
//		height - new height
//	Return:
//		TRUE - to accept new size
//		FALSE - to revert to old size
int MyCug::OnTopHdgSized(int *height)
{
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnColChange
//		Sent whenever the current column changes
//	Params:
//		oldcol - column that is loosing the focus
//		newcol - column that the user move into
//	Return:
//		<none>
void MyCug::OnColChange(int oldcol,int newcol)
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnRowChange
//		Sent whenever the current row changes
//	Params:
//		oldrow - row that is loosing the locus
//		newrow - row that user moved into
//	Return:
//		<none>
void MyCug::OnRowChange(long oldrow,long newrow)
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnCellChange
//		Sent whenever the current cell changes
//	Params:
//		oldcol, oldrow - coordinates of cell that is loosing the focus
//		newcol, newrow - coordinates of cell that is gaining the focus
//	Return:
//		<none>
void MyCug::OnCellChange(int oldcol,int newcol,long oldrow,long newrow)
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnLeftColChange
//		Sent whenever the left visible column in the grid changes, indicating
//		that the view was scrolled horizontaly
//	Params:
//		oldcol - column that used to be on the left
//		newcol - new column that is going to be the first visible column from the left
//	Return:
//		<none>
void MyCug::OnLeftColChange(int oldcol,int newcol)
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnTopRowChange
//		Sent whenever the top visible row in the grid changes, indicating
//		that the view was scrolled vertically
//	Params:
//		oldrow - row that used to be on the top
//		newrow - new row that is going to be the first visible row from the top
//	Return:
//		<none>
void MyCug::OnTopRowChange(long oldrow,long newrow)
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnLClicked
//		Sent whenever the user clicks the left mouse button within the grid
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnLClicked(int col,long row,int updn,RECT *rect,POINT *point,int processed)
{
}
		
/////////////////////////////////////////////////////////////////////////////
//	OnRClicked
//		Sent whenever the user clicks the right mouse button within the grid
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnRClicked(int col,long row,int updn,RECT *rect,POINT *point,int processed)
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnDClicked
//		Sent whenever the user double clicks the left mouse button within the grid
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{
}	
			 
/////////////////////////////////////////////////////////////////////////////
//	OnMouseMove
//		Is sent to each cell that the mouse is over.
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		point		- represents the screen point where the mouse event was detected
//		nFlags		- 
//		processed	- indicates if current event was processed by other control in the grid.
//	Return:
//		<none>
void MyCug::OnMouseMove(int col,long row,POINT *point,UINT nFlags,BOOL processed)
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnTH_LClicked
//		Sent whenever the user clicks the left mouse button within the top heading
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnTH_RClicked
//		Sent whenever the user clicks the right mouse button within the top heading
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnTH_RClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnTH_DClicked
//		Sent whenever the user double clicks the left mouse
//		button within the top heading
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnTH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnSH_LClicked
//		Sent whenever the user clicks the left mouse button within the side heading
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnSH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnSH_RClicked
//		Sent whenever the user clicks the right mouse button within the side heading
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnSH_RClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnSH_DClicked
//		Sent whenever the user double clicks the left mouse button within the side heading
//	Params:
//		col, row	- coordinates of a cell that received mouse click event
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnSH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnCB_LClicked
//		Sent whenever the user clicks the left mouse button within the top corner button
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnCB_LClicked(int updn,RECT *rect,POINT *point,BOOL processed)
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnCB_RClicked
//		Sent whenever the user clicks the right mouse button within the top corner button
//		this message is sent when the button goes down then again when the button goes up
//	Params:
//		updn		- is TRUE if mouse button is 'down' and FALSE if button is 'up'
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnCB_RClicked(int updn,RECT *rect,POINT *point,BOOL processed)
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnCB_DClicked
//		Sent whenever the user double clicks the left mouse
//		button within the top corner button
//	Params:
//		processed	- indicates if current event was processed by other control in the grid.
//		rect		- represents the CDC rectangle of cell in question
//		point		- represents the screen point where the mouse event was detected
//	Return:
//		<none>
void MyCug::OnCB_DClicked(RECT *rect,POINT *point,BOOL processed)
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnKeyDown
//		Sent whenever the user types when the grid has focus. The keystroke can be
//		modified here as well. (See WM_KEYDOWN for more information)
//	Params:
//		vcKey		- virtual key code of the key user has pressed
//		processed	- indicates if current event was processed by other control in the grid.
//	Return:
//		<none>
void MyCug::OnKeyDown(UINT *vcKey,BOOL processed)
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnCharDown
//		Sent whenever the user types when the grid has focus. The keystroke can be 
//		modified here as well. (See WM_CHAR for more information)
//	Params:
//		vcKey		- virtual key code of the key user has pressed
//		processed	- indicates if current event was processed by other control in the grid.
//	Return:
//		<none>
void MyCug::OnCharDown(UINT *vcKey,BOOL processed)
{
}
	
/////////////////////////////////////////////////////////////////////////////
//	OnGetCell
//		This message is sent everytime the grid needs to
//		draw a cell in the grid. At this point the cell
//		class has been filled with the information to be
//		used to draw the cell. The information can now be
//		changed before it is used for drawing
//
//	Warning:
//		This notification is called for each cell that needs to be painted
//		Placing complicated calculations here will slowdown the refresh speed.
//	Params:
//		col, row	- coordinates of cell currently drawing
//		cell		- pointer to the cell object that is being drawn
//	Return:
//		<none>
void MyCug::OnGetCell(int col,long row,CUGCell *cell)
{
	// Display negative Net in a red color
	if(row >= 0)
	{
		float value;
		if(col == 4)
		{
			
			cell->SetTextColor((cell->GetParam() == 1) ? MY_COLOR_LO_TEXT : MY_COLOR_HI_TEXT);
		}

		else if(col == 5)
		{
			cell->GetNumber(&value);
			cell->SetTextColor((value < 0) ? MY_COLOR_LO_TEXT : MY_COLOR_HI_TEXT);
		}

		else if(col == 6)
		{
			char szBuffer[1024];

			cell->GetNumber(&value);
			if(value >= 1000000)
			{
				UGStr::stprintf(szBuffer, 1024, "%d,%03d,%03d", (int)value/1000000, (int)(value - (int)value/1000000*1000000)/1000, (int)(value - (int)value/1000000*1000000)%1000);
			}
			else
			{
				UGStr::stprintf(szBuffer, 1024, "%d,%03d", (int)value/1000, (int)value%1000);
			}
			cell->SetText(szBuffer);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
//	OnSetCell
//		This notification is sent everytime a cell is set, here you have a chance
//		to make final modification to the cell's content before it is set.
//	Params:
//		col, row	- coordinates of cell currently saving
//		cell		- pointer to the cell object that is being saved
//	Return:
//		<none>
void MyCug::OnSetCell(int col,long row,CUGCell *cell)
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnDataSourceNotify
//		This message is sent from a data source and this message
//		depends on the data source - check the information
//		on the data source(s) being used
//		- The ID of the Data source is also returned
//	Params:
//		ID		- datasource ID
//		msg		- message ID to identify current process
//		param	- additional iformation or object that might be needed
//	Return:
//		<none>
void MyCug::OnDataSourceNotify(int ID,long msg,long param)
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnCellTypeNotify
//		This notification is sent by the celltype and it is different from cell-type
//		to celltype and even from notification to notification.  It is usually used to
//		provide the developer with some feed back on the cell events and sometimes to
//		ask the developer if given event is to be accepted or not
//	Params:
//		ID			- celltype ID
//		col, row	- co-ordinates cell that is processing the message
//		msg			- message ID to identify current process
//		param		- additional iformation or object that might be needed
//	Return:
//		TRUE - to allow celltype event
//		FALSE - to disallow the celltype event
int MyCug::OnCellTypeNotify(long ID,int col,long row,long msg,long param)
{
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnEditStart
//		This message is sent whenever the grid is ready to start editing a cell
//	Params:
//		col, row - location of the cell that edit was requested over
//		edit -	pointer to a pointer to the edit control, allows for swap of edit control
//				if edit control is swapped permanently (for the whole grid) is it better
//				to use 'SetNewEditClass' function.
//	Return:
//		TRUE - to allow the edit to start
//		FALSE - to prevent the edit from starting
int MyCug::OnEditStart(int col, long row,CWnd **edit)
{
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnEditVerify
//		This notification is sent every time the user hits a key while in edit mode.
//		It is mostly used to create custom behavior of the edit contol, because it is
//		so eazy to allow or disallow keys hit.
//	Params:
//		col, row	- location of the edit cell
//		edit		-	pointer to the edit control
//		vcKey		- virtual key code of the pressed key
//	Return:
//		TRUE - to accept pressed key
//		FALSE - to do not accept the key
int MyCug::OnEditVerify(int col, long row,CWnd *edit,UINT *vcKey)
{
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnEditFinish
//		This notification is sent when the edit is being finised
//	Params:
//		col, row	- coordinates of the edit cell
//		edit		- pointer to the edit control
//		string		- actual string that user typed in
//		cancelFlag	- indicates if the edit is being cancelled
//	Return:
//		TRUE - to allow the edit it proceede
//		FALSE - to force the user back to editing of that same cell
int MyCug::OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag)
{
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnEditContinue
//		This notification is called when the user pressed 'tab' or 'enter' keys
//		Here you have a chance to modify the destination cell
//	Params:
//		oldcol, oldrow - edit cell that is loosing edit focus
//		newcol, newrow - cell that the edit is going into, by changing their
//							values you are able to change where to edit next
//	Return:
//		TRUE - allow the edit to continue
//		FALSE - to prevent the move, the edit will be stopped
int MyCug::OnEditContinue(int oldcol,long oldrow,int* newcol,long* newrow)
{
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnMenuCommand
//		This notification is called when the user has selected a menu item
//		in the pop-up menu.
//	Params:
//		col, row - the cell coordinates of where the menu originated from
//		setcion - identify for which portion of the gird the menu is for.
//				  possible sections:
//						UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
//						UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
//		item - ID of the menu item selected
//	Return:
//		<none>
void MyCug::OnMenuCommand(int col,long row,int section,int item)
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnMenuStart
//		Is called when the pop up menu is about to be shown
//	Params:
//		col, row	- the cell coordinates of where the menu originated from
//		setcion		- identify for which portion of the gird the menu is for.
//					possible sections:
//						UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
//						UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
//	Return:
//		TRUE - to allow menu to show
//		FALSE - to prevent the menu from poping up
int MyCug::OnMenuStart(int col,long row,int section)
{
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnGetContextHelpID 
//		this notification is called as result of context help bing activated
//		over the UG area
//	Params:
//		col, row	- coordinates of cell which received the message
//		section		- grid section which received this message
//	Return:
//		Context help ID to be shown in the help.
DWORD MyCug::OnGetContextHelpID( int col, long row, int section )
{
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
//	OnHint
//		Is called whent the hint is about to be displayed on the main grid area,
//		here you have a chance to set the text that will be shown
//	Params:
//		col, row	- the cell coordinates of where the menu originated from
//		string		- pointer to the string that will be shown
//	Return:
//		TRUE - to show the hint
//		FALSE - to prevent the hint from showing
int MyCug::OnHint(int col,long row,int section,CString *string)
{
	string->Format( _T("Col:%d Row:%ld") ,col,row);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnVScrollHint
//		Is called whent the hint is about to be displayed on the vertical scroll bar,
//		here you have a chance to set the text that will be shown
//	Params:
//		row		- current top row
//		string	- pointer to the string that will be shown
//	Return:
//		TRUE - to show the hint
//		FALSE - to prevent the hint from showing
int MyCug::OnVScrollHint(long row,CString *string)
{
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnHScrollHint
//		Is called whent the hint is about to be displayed on the horizontal scroll bar,
//		here you have a chance to set the text that will be shown
//	Params:
//		col		- current left col
//		string	- pointer to the string that will be shown
//	Return:
//		TRUE - to show the hint
//		FALSE - to prevent the hint from showing
int MyCug::OnHScrollHint(int col,CString *string)
{
	return TRUE;
}

#ifdef __AFXOLE_H__
/////////////////////////////////////////////////////////////////////////////
//	OLE
//		following 3 functions are to be used with drag and drop functionality
/////////////////////////////////////////////////////////////////////////////
//	OnDragEnter
//	Params:
//		pDataObject - 
//	Return:
//		DROPEFFECT_NONE - no drag and drop
//		DROPEFFECT_COPY - allow drag and drop for copying
DROPEFFECT MyCug::OnDragEnter(COleDataObject* pDataObject)
{
	return DROPEFFECT_NONE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnDragOver
//	Params:
//		col, row	-
//		pDataObject - 
//	Return:
//		DROPEFFECT_NONE - no drag and drop
//		DROPEFFECT_COPY - allow drag and drop for copying
DROPEFFECT MyCug::OnDragOver(COleDataObject* pDataObject,int col,long row)
{
	return DROPEFFECT_NONE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnDragDrop
//	Params:
//		col, row	-
//		pDataObject - 
//	Return:
//		DROPEFFECT_NONE - no drag and drop
//		DROPEFFECT_COPY - allow drag and drop for copying
DROPEFFECT MyCug::OnDragDrop(COleDataObject* pDataObject,int col,long row)
{
	return DROPEFFECT_NONE;
}
#endif

/////////////////////////////////////////////////////////////////////////////
//	OnScreenDCSetup
//		Is called when each of the components are painted.
//	Params:
//		dc		- pointer to the current CDC object
//		section	- section of the grid painted.
//					possible sections:
//						UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
//						UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
//	Return:
//		<none>
void MyCug::OnScreenDCSetup(CDC *dc,int section)
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnSortEvaluate
//		Sent as a result of the 'SortBy' call, this is called for each cell
//		comparison and allows for customization of the sorting routines.
//		We provide following code as example of what could be done here,
//		you migh have to modify it to give your application customized sorting.
//	Params:
//		cell1, cell2	- pointers to cells that are compared
//		flags			- identifies sort direction
//	Return:
//		value less than zero to identify that the cell1 comes before cell2
//		value equal to zero to identify that the cell1 and cell2 are equal
//		value greater than zero to identify that the cell1 comes after cell2
int MyCug::OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags)
{
	// if one of the cells is NULL, do not compare its text
	if ( cell1 == NULL && cell2 == NULL )
		return 0;
	else if ( cell1 == NULL )
		return 1;
	else if ( cell2 == NULL )
		return -1;

	if(flags&UG_SORT_DESCENDING)
	{
		CUGCell *ptr = cell1;
		cell1 = cell2;
		cell2 = ptr;
	}

	// initialize variables for numeric check
	double num1, num2;
	// compare the cells, with respect to the cell's datatype
	switch(cell1->GetDataType())
	{
		case UGCELLDATA_STRING:
			if(NULL == cell1->GetText() && NULL == cell2->GetText())
				return 0;
			if(NULL == cell1->GetText())
				return 1;
			if(NULL == cell2->GetText())
				return -1;
			return _tcscmp(cell1->GetText(),cell2->GetText());	
		case UGCELLDATA_NUMBER:
		case UGCELLDATA_BOOL:
		case UGCELLDATA_CURRENCY:
			num1 = cell1->GetNumber();
			num2 = cell2->GetNumber();
			if(num1 < num2)
				return -1;
			if(num1 > num2)
				return 1;
			return 0;
		default:
			// if datatype is not recognized, compare cell's text
			if(NULL == cell1->GetText())
				return 1;
			if(NULL == cell2->GetText())
				return -1;
			return _tcscmp(cell1->GetText(),cell2->GetText());	
	}
}

/////////////////////////////////////////////////////////////////////////////
//	OnTabSelected
//		Called when the user selects one of the tabs on the bottom of the screen
//	Params:
//		ID	- id of selected tab
//	Return:
//		<none>
void MyCug::OnTabSelected(int ID)
{
	SetSheetNumber(ID);
	PostMessage(WM_SIZE, 0, 0L);
}

/////////////////////////////////////////////////////////////////////////////
//	OnAdjustComponentSizes
//		Called when the grid components are baing arranged.
//	Params:
//		grid, topHdg, sideHdg, cnrBtn, vScroll, hScroll, 
//		tabs	- sizes and location of each of the grid components
//	Return:
//		<none>
void MyCug::OnAdjustComponentSizes(RECT *grid,RECT *topHdg,RECT *sideHdg,
		RECT *cnrBtn,RECT *vScroll,RECT *hScroll,RECT *tabs)
{
} 

/////////////////////////////////////////////////////////////////////////////
//	OnDrawFocusRect
//		Called when the focus rect needs to be painted.
//	Params:
//		dc		- pointer to the current CDC object
//		rect	- rect of the cell that requires the focus rect
//	Return:
//		<none>
void MyCug::OnDrawFocusRect(CDC *dc,RECT *rect)
{
	//DrawExcelFocusRect(dc,rect);
	
/*	rect->bottom --;
	rect->right --;
	dc->DrawFocusRect(rect);
	*/
}

/////////////////////////////////////////////////////////////////////////////
//	OnGetDefBackColor
//		Sent when the area behind the grid needs to be paindted.
//	Params:
//		section - Id of the grid section that requested this color
//				  possible sections:
//						UG_TOPHEADING, UG_SIDEHEADING, UG_GRID
//	Return:
//		RGB value representing the color of choice
COLORREF MyCug::OnGetDefBackColor(int section)
{
	return MY_COLOR_BACK;
}

/////////////////////////////////////////////////////////////////////////////
//	OnSetFocus
//		Sent when the grid is gaining focus.
//	Params:
//		section - Id of the grid section gaining focus, usually UG_GRID
//				  possible sections:
//						UG_TOPHEADING, UG_SIDEHEADING, UG_GRID
//	Return:
//		<none>
//
//	Note:
//		The grid will loose focus when the edit is started, of drop list shown
void MyCug::OnSetFocus(int section)
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnKillFocus
//		Sent when the grid is loosing focus.
//	Params:
//		section - Id of the grid section loosing focus, usually UG_GRID
//				  possible sections:
//						UG_TOPHEADING, UG_SIDEHEADING, UG_GRID
//	Return:
//		<none>
void MyCug::OnKillFocus(int section)
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnColSwapStart
//		Called to inform the grid that the col swap was started on given col.
//	Params:
//		col - identifies the column
//	Return:
//		TRUE - to allow for the swap to take place
//		FALSE - to disallow the swap
BOOL MyCug::OnColSwapStart(int col)
{
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnCanColSwap
//		Called when col swap is about to take place, here you can 'lock' certain
//		cols in place so that are not swapable.
//	Params:
//		fromCol - where the col orriginated from
//		toCol	- where the col will be located if the swap is allowed
//	Return:
//		TRUE - to allow for the swap to take place
//		FALSE - to disallow the swap
BOOL MyCug::OnCanColSwap(int fromCol,int toCol)
{
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnColSwapped
//		Called just after column-swap operation was completed.
//	Params:
//		fromCol - where the col orriginated from
//		toCol	- where the col will be located if the swap is allowed
//	Return:
//		<none>
void MyCug::OnColSwapped(int fromCol,int toCol)
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnTrackingWindowMoved
//		Called to notify the grid that the tracking window was moved
//	Params:
//		origRect	- from
//		newRect		- to location and size of the track window
//	Return:
//		<none>
void MyCug::OnTrackingWindowMoved(RECT *origRect,RECT *newRect)
{
}

void MyCug::OnSize(UINT nType, int cx, int cy)
{
	EnableUpdate(FALSE);

	RECT rect;
	GetClientRect(&rect);

	SetTabWidth(max(rect.right/3, 75));
	SetSH_Width(0);
	SetColWidth(0, 175);
	for(int y = 1;y < 7; y++)
	{
		SetColWidth(y, (rect.right-175)/6);
	}

	EnableUpdate(TRUE);


	CUGCtrl::OnSize(nType,cx,cy);
}

void MyCug::OnTimer(UINT nIDEvent)
{
	CUGCell cell;
	int		nColorStep = 5;

	if(nIDEvent == 0)		// Back color updates
	{
		// loop throug all raws
		for(int nRow=0; nRow<GetNumberRows(); nRow++)
		{
			GetCell(0, nRow, &cell);
			COLORREF color = cell.GetBackColor();
			COLORREF colorText = cell.GetTextColor();
			if(color != MY_COLOR_BACK)
			{
				// adjust back color
				int nRColor = GetRValue(color) - nColorStep;
				int nGColor = GetGValue(color) - nColorStep;
				int nBColor = GetBValue(color) - nColorStep;

				if(nRColor < GetRValue(MY_COLOR_BACK))
				{
					nRColor = GetRValue(MY_COLOR_BACK);
				}
				if(nGColor < GetGValue(MY_COLOR_BACK))
				{
					nGColor = GetGValue(MY_COLOR_BACK);
				}
				if(nBColor < GetBValue(MY_COLOR_BACK))
				{
					nBColor = GetBValue(MY_COLOR_BACK);
				}

				color = RGB((BYTE)nRColor, (BYTE)nGColor, (BYTE)nBColor);

				// adjust text color
				nRColor = GetRValue(colorText) + nColorStep;
				nGColor = GetGValue(colorText) + nColorStep;
				nBColor = GetBValue(colorText) + nColorStep;

				if(nRColor > GetRValue(MY_COLOR_TEXT))
				{
					nRColor = GetRValue(MY_COLOR_TEXT);
				}
				if(nGColor > GetGValue(MY_COLOR_TEXT))
				{
					nGColor = GetGValue(MY_COLOR_TEXT);
				}
				if(nBColor > GetBValue(MY_COLOR_TEXT))
				{
					nBColor = GetBValue(MY_COLOR_TEXT);
				}

				colorText = RGB((BYTE)nRColor, (BYTE)nGColor, (BYTE)nBColor);


				for(int nCol=0; nCol<GetNumberCols(); nCol++)
				{
					QuickSetBackColor(nCol ,nRow, color);
					QuickSetTextColor(nCol ,nRow, colorText);
				}

				RedrawRow(nRow);
			}
		}
	}
	else if(nIDEvent == 1)	// Data changes
	{
		if((rand()%5) >= 3)
		{
			char	szBuffer[255];

			// Pick up a random row
			int nRow = rand() % GetNumberRows();

			// Get current values of the row
			CUGCell cellBid, cellAsk, cellLast, cellNet, cellVolume;
			GetCell(2, nRow, &cellBid);
			GetCell(3, nRow, &cellAsk);
			GetCell(4, nRow, &cellLast);
			GetCell(5, nRow, &cellNet);
			GetCell(6, nRow, &cellVolume);

			float fBid, fAsk, fLast, fNet, fVolume;
			cellBid.GetNumber(&fBid);
			cellAsk.GetNumber(&fAsk);
			cellLast.GetNumber(&fLast);
			cellNet.GetNumber(&fNet);
			cellVolume.GetNumber(&fVolume);

			// Randomly change row data
			fBid += (float)(12. - rand() / (RAND_MAX/20.));
			fAsk = (float)(fBid + rand() / (RAND_MAX/2.));
			fLast = (float)(fBid + rand() / (RAND_MAX/2.));
			fNet = (float)(3.5 - rand() / (RAND_MAX/6.));
			fVolume += (int)((rand() / (RAND_MAX/1000.)))*100;

			cellLast.SetParam((int)rand() % 2);

			// Set new data into the cell
			UGStr::stprintf(szBuffer, 255, "%.02f", fBid);
			cellBid.SetText(szBuffer);
			UGStr::stprintf(szBuffer, 255, "%.02f", fAsk);
			cellAsk.SetText(szBuffer);
			UGStr::stprintf(szBuffer, 255, "%.02f", fLast);
			cellLast.SetText(szBuffer);
			UGStr::stprintf(szBuffer, 255, "%+#.02f", fNet);
			cellNet.SetText(szBuffer);
			UGStr::stprintf(szBuffer, 255, "%d", (int)fVolume);
			cellVolume.SetText(szBuffer);

			// Set cell data
			SetCell(2, nRow, &cellBid);
			SetCell(3, nRow, &cellAsk);
			SetCell(4, nRow, &cellLast);
			SetCell(5, nRow, &cellNet);
			SetCell(6, nRow, &cellVolume);

			// Higlight row
			QuickSetTextColor(0, nRow, MY_COLOR_CHANGED_TEXT);
			QuickSetBackColor(0, nRow, MY_COLOR_CHANGED_BACK);
		}
	}
}