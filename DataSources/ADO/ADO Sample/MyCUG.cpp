/////////////////////////////////////////////////////////////////////////////
//	Skeleton Class for a Derived CUGCtrl class

#include "stdafx.h"
#include "resource.h"
#include "MyCUG.h"
#include "ADOImpDatasource.h"

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


/////////////////////////////////////////////////////////////////////////////
// Standard MyCug construction/destruction
MyCug::MyCug()
{
	m_curSortCol = -1;
	m_sortDir = UGCT_SORTARROWDOWN;
	m_defFont.CreatePointFont( 90, _T("Arial"));
}

MyCug::~MyCug()
{
}
/////////////////////////////////////////////////////////////////////////////
//	OnSetup
//		This function is called just after the grid window 
//		is created or attached to a dialog item.
//		It can be used to initially setup the grid
void MyCug::OnSetup()
{
	AddTab( _T("Sheet 1"), 1 );
	SetTabWidth( 200 );
}


/////////////////////////////////////////////////////////////////////////////
//	OnSheetSetup	
//		This notification is called for each additional sheet that the grid
//		might contain, here you can customize each sheet in the grid.
//	Params:
//		sheetNumber - idndex of current sheet
//	Return:
//		<none>
void MyCug::OnSheetSetup( int )
{
	// add the sort arrow celltype
	AddCellType( &m_sortArrow );
	// create and set default font
	SetDefFont( &m_defFont );
	// enable popup menus
	EnableMenu( TRUE );
	SetMultiSelectMode( TRUE );
}

/////////////////////////////////////////////////////////////////////////////
//	OnHitBottom
//		This notification allows for dynamic row loading, it will be called
//		when the grid's drawing function has hit the last row.  It allows the grid
//		to ask the datasource/developer if there are additional rows to be displayed.
//	Params:
//		numrows		- known number of rows in the grid
//		rowspast	- number of extra rows that the grid is looking for in the datasource
//		rowsfound	- number of rows actually found, usually equal to rowspast or zero.
//	Return:
//		<none>
void MyCug::OnHitBottom(long numrows,long rowspast,long rowsfound)
{
	UNREFERENCED_PARAMETER(numrows);
	UNREFERENCED_PARAMETER(rowspast);
	UNREFERENCED_PARAMETER(rowsfound);
	// used by the datasources
	if ( rowsfound > 0 )
	{
		SetNumberRows( numrows + rowsfound, FALSE );
	}
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
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(*rect);
	UNREFERENCED_PARAMETER(*point);
	UNREFERENCED_PARAMETER(processed);

	if ( !updn )
		return;

	BeginWaitCursor();
	
	if ( col == m_curSortCol )
	{
		if ( m_sortDir == UGCT_SORTARROWDOWN )
		{
			m_sortDir = UGCT_SORTARROWUP;
			SortBy( col, UG_SORT_DESCENDING );
		}
		else
		{
			m_sortDir = UGCT_SORTARROWDOWN;
			SortBy( col, UG_SORT_ASCENDING );
		}
	}
	else
	{
		m_curSortCol = col;
		m_sortDir = UGCT_SORTARROWDOWN;
		SortBy( col, UG_SORT_ASCENDING );
	}

	AdjustComponentSizes();
	EndWaitCursor();
}

/////////////////////////////////////////////////////////////////////////////
//	OnCharDown
//		Sent when grid received a WM_CHAR message, usually as a result
//		of a user pressing any key that represents a printable characrer.
//	Params:
//		vcKey		- virtual key code of the key user has pressed
//		processed	- indicates if current event was processed by other control in the grid.
//	Return:
//		<none>
void MyCug::OnCharDown(UINT *vcKey,BOOL processed)
{
	UNREFERENCED_PARAMETER(processed);

	StartEdit( *vcKey );
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
	if ( col >= 0 && col == m_curSortCol && row == -1 )
	{	// set default values to the top heading
		cell->SetCellType( m_sortArrow.GetID());
		cell->SetCellTypeEx( m_sortDir );
	}
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
//						UG_HSCROLL  UG_VSCROLL  UG_CORNERBUT`TON
//		item - ID of the menu item selected
//	Return:
//		<none>
void MyCug::OnMenuCommand(int col,long row,int section,int item)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(section);

	switch( item )
	{
	case 1001:
		InsertRow( row );
		break;
	case 1002:
		AppendRow();
		break;
	case 1003:
		DeleteRow( row );
		break;
	case 1006:
		((CADOImpDatasource*)GetDataSource( GetDefDataSource()))->RefreshData();
		RedrawAll();
		break;
	case 1007:
		if (((CADOImpDatasource*)GetDataSource( GetDefDataSource()))->UpdateNow() != UG_SUCCESS )
			((CADOImpDatasource*)GetDataSource( GetDefDataSource()))->CancelUpdates();

		RedrawAll();
		break;
	case 1008:
		((CADOImpDatasource*)GetDataSource( GetDefDataSource()))->CancelUpdates();
		RedrawAll();
		break;
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

	if ( section == UG_GRID )
	{
		AddMenuItem( 1006, _T("Refresh Data"));
		AddMenuItem( 1007, _T("Commit changes"));
		AddMenuItem( 1008, _T("Cancel changes"));
	}
	else if ( section == UG_SIDEHEADING )
	{
		AddMenuItem( 1001, _T("Insert Row"));
		AddMenuItem( 1002, _T("Append Row"));
		AddMenuItem( 1003, _T("Delete Row"));
	}

	return TRUE;
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
	SetSheetNumber( ID - 1 );
}