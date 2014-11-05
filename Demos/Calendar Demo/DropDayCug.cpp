/////////////////////////////////////////////////////////////////////////////
//	Skeleton Class for a Derived CUGCtrl class

#include "stdafx.h"
#include "resource.h"
#include "DropDayCug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CDropDayCug,CUGCtrl)
	//{{AFX_MSG_MAP(CDropDayCug)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Standard CDropDayCug construction/destruction
CDropDayCug::CDropDayCug()
{
	m_bIsUpdated = FALSE;
	// add the datasource
	AddDataSource( &m_adoDatasource );
}

CDropDayCug::~CDropDayCug()
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnSetup
//		This function is called just after the grid window 
//		is created or attached to a dialog item.
//		It can be used to initially setup the grid
void CDropDayCug::OnSetup()
{
	SetUserSizingMode( 0 );
	SetDefRowHeight( 50 );
	EnableMenu( TRUE );
	SetDefFont( AddFont( "Arial", -13, 400 ));
	m_crossedFont.CreateFont( -13, 0, 0, 0, 400, 0, 0, 1, 0, 0, 0, 0, 0, "Arial" );

	CUGCell cell;
	GetHeadingDefault( &cell );
	cell.SetFont( GetFont( AddFont( "Arial", -13, 700 )));
	SetHeadingDefault( &cell );
}

/////////////////////////////////////////////////////////////////////////////
//	SetDate
void CDropDayCug::SetDate( int nYear, int nMonth, int nDay )
{
	m_bIsUpdated = FALSE;
	SetNumberRows( 0 );
	m_appDate.SetDate( nYear, nMonth, nDay );

	if ( m_appDate.GetStatus() > 0 )
		// date is invalid or null
		return;

	// generate the SQL query
	CString sqlStr = "SELECT Completed, Appointment, Date FROM Appointments "
					 "WHERE Date = #" + m_appDate.Format() + "#;";
	m_adoDatasource.OpenSQL( sqlStr, "Driver={Microsoft Access Driver (*.mdb)};Dbq=Appointments.mdb;Uid=;Pwd=;" );

	// set added datasource to be default
	SetDefDataSource( m_adoDatasource.GetID());
	// complete the datasource binding operation, let grid adjust
	// itself to reflect information found in the datasource
	SetGridUsingDataSource( m_adoDatasource.GetID());

	SetSH_Width( 20 );
	SetColWidth( 0, 30 );
	SetColWidth( 1, 220 );
	SetColWidth( 2, 0 );

	AdjustComponentSizes();
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
void CDropDayCug::OnHitBottom(long numrows,long rowspast,long rowsfound)
{
	UNREFERENCED_PARAMETER(rowspast);
	
	// used by the datasources
	if ( rowsfound > 0 )
	{
		SetNumberRows( numrows + rowsfound );
	}
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
void CDropDayCug::OnGetCell(int col,long row,CUGCell *cell)
{
	if ( col == 0 && row == -1 )
		cell->SetText( "" );
	else if ( col == 0 && row >= 0 )
	{
		cell->SetCellType( UGCT_CHECKBOX );
		cell->SetCellTypeEx( UGCT_CHECKBOXCHECKMARK|UGCT_CHECKBOXUSEALIGN );
		cell->SetAlignment( UG_ALIGNCENTER|UG_ALIGNVCENTER );

		if ( row == GetNumberRows() -1 )
			cell->SetReadOnly( TRUE );
	}
	else if ( col == 1 && row >= 0 )
	{
		CUGCell checkCell;
		GetCell( 0, row, &checkCell );

		if ( checkCell.GetNumber() > 0 )
			cell->SetFont( &m_crossedFont );
	}
}

/////////////////////////////////////////////////////////////////////////////
//	OnSetCell
//		This notification is sent everytime a cell is set,
//		here you have a chance to make final modification
//		to the cell's content before it is saved to the data source.
//	Params:
//		col, row	- coordinates of cell currently saving
//		cell		- pointer to the cell object that is being saved
//	Return:
//		<none>
void CDropDayCug::OnSetCell(int col,long row,CUGCell *cell)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(*cell);

	m_bIsUpdated = TRUE;
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
int CDropDayCug::OnEditStart(int col, long row,CWnd **edit)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(**edit);

	if ( col != 1 )
		return FALSE;

	return TRUE;
}

/***************************************************
OnEditFinish
	This notification is sent when the edit is being finised
Params:
	col, row	- coordinates of the edit cell
	edit		- pointer to the edit control
	string		- actual string that user typed in
	cancelFlag	- indicates if the edit is being cancelled
Return:
	TRUE - to allow the edit it proceede
	FALSE - to force the user back to editing of that same cell
****************************************************/
int CDropDayCug::OnEditFinish(int col, long row,CWnd* edit,LPCTSTR string,BOOL cancelFlag)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(*edit);
	UNREFERENCED_PARAMETER(string);

	if ( cancelFlag == FALSE )
	{	// Every time appointment info is updated,
		// also update the date field
		QuickSetText( 2, row, m_appDate.Format());
	}

	return TRUE;
}

/***************************************************
OnCellTypeNotify
	This notification is sent by the celltype and it is different from cell-type
	to celltype and even from notification to notification.  It is usually used to
	provide the developer with some feed back on the cell events and sometimes to
	ask the developer if given event is to be accepted or not
Params:
	ID			- celltype ID
	col, row	- co-ordinates cell that is processing the message
	msg			- message ID to identify current process
	param		- additional iformation or object that might be needed
Return:
	TRUE - to allow celltype event
	FALSE - to disallow the celltype event
****************************************************/
int CDropDayCug::OnCellTypeNotify(long ID,int col,long row,long msg,long param)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(param);

	if ( ID == UGCT_CHECKBOX && msg == UGCT_CHECKBOXSET )
	{
		// update the date field
		QuickSetText( 2, row, m_appDate.Format());
		// and redraw the appointment cell
		RedrawCell( 1, row );
	}

	return TRUE;
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
void CDropDayCug::OnLClicked(int col,long row,int updn,RECT *rect,POINT *point,int processed)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(updn);
	UNREFERENCED_PARAMETER(*rect);
	UNREFERENCED_PARAMETER(*point);
	UNREFERENCED_PARAMETER(processed);
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
void CDropDayCug::OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(*rect);
	UNREFERENCED_PARAMETER(*point);
	UNREFERENCED_PARAMETER(processed);

	StartEdit();
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
void CDropDayCug::OnCharDown(UINT *vcKey,BOOL processed)
{
	UNREFERENCED_PARAMETER(*vcKey);
	UNREFERENCED_PARAMETER(processed);

	StartEdit( *vcKey );
}

/////////////////////////////////////////////////////////////////////////////
//	OnKeyDown
//		Sent when grid received a WM_KEYDOWN message, usually as a result
//		of a user pressing any key on the keyboard.
//	Params:
//		vcKey		- virtual key code of the key user has pressed
//		processed	- indicates if current event was processed by other control in the grid.
//	Return:
//		<none>
void CDropDayCug::OnKeyDown(UINT *vcKey,BOOL processed)
{
	UNREFERENCED_PARAMETER(*vcKey);
	UNREFERENCED_PARAMETER(processed);

	if ( m_editInProgress == TRUE )
		return;

	CDropDownCug::OnKeyDown( vcKey, processed );
}

/////////////////////////////////////////////////////////////////////////////
//	OnKillFocus
//		Sent when the grid is loosing focus.
//	Params:
//		section - Id of the grid section loosing focus, usually UG_GRID
//				  possible sections:
//						UG_TOPHEADING, UG_SIDEHEADING, UG_GRID
//		pNewWnd - pointer to the window gaining focus
//	Return:
//		<none>
void CDropDayCug::OnKillFocus(int section, CWnd *pNewWnd)
{
	UNREFERENCED_PARAMETER(section);

	if ( m_editInProgress == TRUE )
	{
		CString tempStr = "";

		if ( pNewWnd == NULL )
		{
			m_editCtrl->GetWindowText( tempStr );
		}
		else
		{
			if (( pNewWnd->GetParent() != m_CUGGrid ) && 
				( pNewWnd->GetParent() != this ))
			{
				m_editCtrl->GetWindowText( tempStr );
			}
		}

		if ( tempStr != "" )
			EditCtrlFinished( tempStr, FALSE, FALSE, 0, 0 );
	}

	if ( m_editInProgress == FALSE && m_cellType != NULL )
	{
		m_adoDatasource.OnRowChange( GetCurrentRow(), GetCurrentRow());
		((CUGCTDropGrid*)m_cellType)->OnClosePopup();
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
//						UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
//		item - ID of the menu item selected
//	Return:
//		<none>
void CDropDayCug::OnMenuCommand(int col,long row,int section,int item)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(section);

	if ( item == 1000 )
	{
		DeleteRow( row );
		RedrawAll();
		m_bIsUpdated = TRUE;
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
int CDropDayCug::OnMenuStart(int col,long row,int section)
{
	UNREFERENCED_PARAMETER(col);

	EmptyMenu();

	if ( section == UG_SIDEHEADING && row < GetNumberRows() - 1 )
	{
		AddMenuItem( 1000, "Delete Appointment" );
	}

	return TRUE;
}