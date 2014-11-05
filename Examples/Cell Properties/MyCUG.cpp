/////////////////////////////////////////////////////////////////////////////
//	Skeleton Class for a Derived CUGCtrl class

#include "stdafx.h"
#include "resource.h"
#include "MyCUG.h"
#include "PropertyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(MyCug,CUGCtrl)
	//{{AFX_MSG_MAP(MyCug)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Standard MyCug construction/destruction
MyCug::MyCug()
{
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
	int cols = 6,
		rows = 15;

	SetDefColWidth( 60 );
	EnableMenu( TRUE );
	SetMultiSelectMode( TRUE );
	SetDoubleBufferMode( TRUE );

	CUGCell cell;
	// setup the default grid look
	GetGridDefault( &cell );
	cell.SetFont( GetFont( AddFont( "Arial", -12, 400 )));
	SetGridDefault( &cell );

	SetNumberRows( rows );
	SetNumberCols( cols );

	AddBitmap( IDB_CHECKMARK );
	AddBitmap( IDB_DUNDASLOGO );

	// setup column defaults
	GetColDefault( 1, &cell );
	cell.SetFont( GetFont( AddFont( "Times New Roman", -12, 400 )));
	cell.SetBackColor( RGB(200,190,200));
	cell.SetHBackColor( RGB(100,200,100));
	cell.SetAlignment( UG_ALIGNCENTER|UG_ALIGNVCENTER );
	cell.SetText( "Col 1" );
	SetColDefault( 1, &cell );

	GetColDefault( 3, &cell );
	cell.SetFont( GetFont( AddFont( "Times New Roman", -12, 400 )));
	cell.SetBackColor( RGB(100,190,100));
	cell.SetHBackColor( RGB(200,210,200));
	cell.SetAlignment( UG_ALIGNRIGHT|UG_ALIGNVCENTER );
	cell.SetNumber( 3 );
	cell.SetNumberDecimals( 2 );
	SetColDefault( 3, &cell );

	GetColDefault( 5, &cell );
	cell.SetCellType( UGCT_CHECKBOX );
	SetColDefault( 5, &cell );

	// Clear a range of cells
	GetCellIndirect( 0, 3, &cell );
	cell.SetText( "" );
	cell.SetDataType( UGCELLDATA_STRING );
	cell.SetPropertyFlags( cell.GetPropertyFlags());
	QuickSetRange( 0, 3, cols - 1, 5, &cell );
	// setup individual cells.
	GetCellIndirect( 1, 4, &cell );
	cell.SetText( "Long text with bitmap" );
	cell.SetBitmap( GetBitmap( 0 ));
	SetCell( 1, 4, &cell );
}
	
/////////////////////////////////////////////////////////////////////////////
//	OnGetCell
//		This message is sent everytime the grid needs to
//		draw a cell in the grid. At this point the cell
//		object has been populated with all of the information
//		that will be used to draw the cell. This information
//		can now be changed before it is used for drawing.
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
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(*cell);

	if ( col >= 0 && row == -1 )
	{	// set default values to the top heading
		cell->SetNumberDecimals( 0 );
		cell->SetNumber( col );
	}
	else if ( row >= 0 && col == -1 )
	{	// set default values to the side heading (row numbers)
		cell->SetNumberDecimals( 0 );
		cell->SetNumber( row );
	}
	else if ( col >= 0 && row >= 0 )
	{
	}
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
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);

	if ( ID == UGCT_DROPLIST && msg == UGCT_DROPLISTSTART )
	{
		CStringList *pItemList = (CStringList*)param;
		pItemList->AddTail( "Option One" );
		pItemList->AddTail( "Option Two" );
		pItemList->AddTail( "Option Three" );
	}

	return TRUE;
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
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(*rect);
	UNREFERENCED_PARAMETER(*point);
	UNREFERENCED_PARAMETER(processed);
	StartEdit();
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
	UNREFERENCED_PARAMETER(section);

	CPropertyDlg dlg;
	CUGCell cell;

	switch( item )
	{
	case 1000:
		GetCell( col, row, &cell );
		break;
	case 1001:
		GetCellIndirect( col, row, &cell );
		break;
	case 1002:
		GetColDefault( col, &cell );
		break;
	case 1003:
		GetGridDefault( &cell );
		break;
	default:
		return;
	}

	dlg.UseCell( &cell );
	dlg.UseCtrl( this );

	// show the properties dialog
	if ( dlg.DoModal() == IDOK )
	{	// the user wants to commit changes to a cell
		if ( item == 1000 || item == 1001 )
		{
			SetCell( col, row, &cell );
			RedrawCell( col, row );
		}
		else if ( item == 1002 )
		{
			SetColDefault( col, &cell );
			RedrawCol( col );
		}
		else if ( item == 1003 )
		{
			SetGridDefault( &cell );
			// loop through all columns in the grid and update their defaults
			for ( int nIndex = 0; nIndex < GetNumberCols(); nIndex ++ )
				SetColDefault( nIndex, &cell );

			RedrawAll();
		}
	}
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
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	
	EmptyMenu();

	if ( section == UG_GRID && col >= 0 && row >= 0 )
	{
		AddMenuItem( 1000, "Cell properties only" );
		AddMenuItem( 1001, "Cell and Col properties" );
	}
	else if ( section == UG_TOPHEADING && col >= 0 )
	{
		AddMenuItem( 1002, "Column defaults" );
	}
	else if ( section == UG_CORNERBUTTON )
	{
		AddMenuItem( 1003, "Grid defaults" );
	}

	return TRUE;
}

