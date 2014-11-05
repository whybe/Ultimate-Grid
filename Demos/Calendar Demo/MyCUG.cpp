/////////////////////////////////////////////////////////////////////////////
//	Skeleton Class for a Derived CUGCtrl class

#include "stdafx.h"
#include "resource.h"
#include "MyCUG.h"

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
	m_nMonthDispFont = 0;
	m_nCurrMonth = -1;
	m_nCurrYear = -1;
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
	m_nBellBmpIndex = AddBitmap( IDB_BELL );
	AddCellType( &m_dropGridCT );
	m_nMonthDispFont = AddFont( "Arial", -16, 700 );
	m_borderPen.CreatePen( PS_SOLID, 1, RGB(190,190,190));
	m_dropMonthGrid.CreateGrid( WS_CHILD|WS_BORDER, CRect(0,0,0,0), this, 3526212 );
	m_dropDayGrid.CreateGrid( WS_CHILD|WS_BORDER, CRect(0,0,0,0), this, 3525232 );
	// ADO recordset
	m_adoRecordSet.SetOption( UG_ADO_DS_USE_GHOSTROW, FALSE, 0 );
	m_adoRecordSet.SetOption( UG_ADO_DS_SET_EDITMODE, FALSE, 0 );
	AddDataSource( &m_adoRecordSet );

	int cols = 7,
		rows = 12;
	CUGCell cell;

	SetDefColWidth( 80 );
	SetDefRowHeight( 50 );
	SetSH_Width( 0 );

	SetTH_NumberRows( 2 );
	SetTH_Height( 50 );
	SetTH_RowHeight( -1, 20 );
	SetTH_RowHeight( -2, 30 );
	SetUserSizingMode( 0 );
	EnableExcelBorders( FALSE );

	GetHeadingDefault( &cell );
	int hedingFontIndex = AddFont( "Arial", -13, 700 );
	cell.SetFont( GetFont( hedingFontIndex ));
	SetHeadingDefault( &cell );

	GetGridDefault( &cell );
	int gridFontIndex = AddFont( "Arial", -13, 400 );
	cell.SetFont( GetFont( gridFontIndex ));
	SetGridDefault( &cell );

	SetNumberRows( rows );
	SetNumberCols( cols );

	// Month cell with drop down grid
	JoinCells( 1, -2, 5, -2 );
	QuickSetCellType( 1, -2, m_dropGridCT.GetID());

	// Arrows
	QuickSetCellType( 0, -2, UGCT_ARROW );
	QuickSetCellTypeEx( 0, -2, UGCT_ARROWLEFT );
	QuickSetCellType( 6, -2, UGCT_ARROW );
	QuickSetCellTypeEx( 6, -2, UGCT_ARROWRIGHT );

	PopulateMonthInfo();
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
	UNREFERENCED_PARAMETER(*rect);
	UNREFERENCED_PARAMETER(*point);
	UNREFERENCED_PARAMETER(processed);

	if ( col == 0 && row == -2 && updn )
	{
		if ( m_nCurrMonth > 1 )
			m_nCurrMonth --;
		else
		{
			m_nCurrMonth = 12;
			m_nCurrYear --;
		}

		PopulateMonthInfo();
		RedrawAll();
	}
	else if ( col == 6 && row == -2 && updn )
	{
		if ( m_nCurrMonth < 12 )
			m_nCurrMonth ++;
		else
		{
			m_nCurrMonth = 1;
			m_nCurrYear ++;
		}

		PopulateMonthInfo();
		RedrawAll();
	}
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
	OnTH_LClicked( col, row, 1, rect, point, processed );
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
	if ( col >= 0 && row == -1 )
	{	// set default values to the top heading
		switch( col )
		{
		case 0:
			cell->SetText( "Sunday" );
			cell->SetTextColor( RGB(255,0,0));
			break;
		case 1:
			cell->SetText( "Monday" );
			break;
		case 2:
			cell->SetText( "Tuesday" );
			break;
		case 3:
			cell->SetText( "Wednesday" );
			break;
		case 4:
			cell->SetText( "Thursday" );
			break;
		case 5:
			cell->SetText( "Friday" );
			break;
		case 6:
			cell->SetText( "Saturday" );
			cell->SetTextColor( RGB(255,0,0));
			break;
		}
	}
	else if ( col == 1 && row == -2 )
	{
		cell->SetText( m_tempDateTime.Format( "%B, %Y" ));
		cell->SetFont( GetFont( m_nMonthDispFont ));
		cell->SetTextColor( RGB(0,0,200));
	}
	else if (( col == 0 || col == 6 ) && cell->GetText() != NULL )
	{
		cell->SetTextColor( RGB(255,0,0));
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
	CUGCell cell;

	if ( ID == m_dropGridCT.GetID() && msg == UGCT_SHOWDROPGRID )
	{
		CreateDropDownGrid *pCreateStruct = (CreateDropDownGrid*)param;

		if ( col >= 0 && row >= 0 )
		{
			pCreateStruct->popUpWndRect.right += 200;
			pCreateStruct->popUpWndRect.bottom += 100;
			// configure the drop-drid object
			m_dropDayGrid.SetParent( pCreateStruct->pGridCtrl->GetParent());
			pCreateStruct->pGridCtrl = &m_dropDayGrid;
			// setup the day details grid
			GetCell( col, row - 1, &cell );
			m_dropDayGrid.SetDate( m_nCurrYear, m_nCurrMonth, (int)cell.GetNumber());
		}
		else if ( col == 1 && row == -2 )
		{
			// showing the month sub grid
			CRect cellRect;
			GetCellRect( col, row, cellRect );
			pCreateStruct->popUpWndRect.left = cellRect.right - 150;
			pCreateStruct->popUpWndRect.right = cellRect.right;
			pCreateStruct->popUpWndRect.bottom += 100;
			// setup the month select grid
			m_dropMonthGrid.SetParent( pCreateStruct->pGridCtrl->GetParent());
			m_dropMonthGrid.SetCurrentYear( m_nCurrYear );
			pCreateStruct->pGridCtrl = &m_dropMonthGrid;
			pCreateStruct->pGridCtrl->SetSH_Width( 30 );
			pCreateStruct->pGridCtrl->SetColWidth( 0, 70 );
			pCreateStruct->pGridCtrl->SetColWidth( 1, 30 );
		}
	}
	else if ( ID == m_dropGridCT.GetID() && msg == UGCT_SELECTEDITEM )
	{
		SelectedGridItem *pSelectStruct = (SelectedGridItem*)param;

		if ( col >= 0 && row >= 0 )
		{
		}
		else if ( col == 1 && row == -2 )
		{
			m_nCurrMonth = pSelectStruct->pGridCtrl->GetCurrentRow() + 1;
			m_nCurrYear = m_dropMonthGrid.GetCurrentYear();
			PopulateMonthInfo();
		}
	}
	else if ( ID == m_dropGridCT.GetID() && msg == UGCT_CLOSEDROPGRID )
	{
		if ( col >= 0 && row >= 0 )
		{
			if ( m_dropDayGrid.IsUpdated())
				PopulateMonthInfo();

			m_dropDayGrid.SetParent( this );
			m_dropDayGrid.ShowWindow( SW_HIDE );
		}
		else
		{
			m_dropMonthGrid.SetParent( this );
			m_dropMonthGrid.ShowWindow( SW_HIDE );
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	PopulateMonthInfo
void MyCug::PopulateMonthInfo()
{
	int nMinDay, nDaysInMonth;
	CUGCell cell;
	CString string;
	int nLoopDay = 0;

	GetMonthInfo( nMinDay, nDaysInMonth );

	for ( int yIndex = 0; yIndex < GetNumberRows(); yIndex += 2 )
	{
		SetRowHeight( yIndex, 20 );
		SetRowHeight( yIndex + 1, 50 );

		for ( int xIndex = 0; xIndex < GetNumberCols(); xIndex ++ )
		{
			if (( yIndex == 0 && xIndex < nMinDay ) ||
				( nLoopDay >= nDaysInMonth ))
			{	// ** work on the empty cells
				GetCellIndirect( xIndex, yIndex, &cell );
				cell.SetText( "" );
				cell.SetCellType( UGCT_NORMAL );
				cell.SetBackColor( RGB(255,255,255));

				if ( yIndex == 0 && xIndex + 1 == nMinDay )
					cell.SetBorder( UG_BDR_RTHIN );
				else
					cell.SetBorder( 0 );

				//cell.SetBorderColor( &m_borderPen );
				SetCell( xIndex, yIndex, &cell );

				GetCellIndirect( xIndex, yIndex + 1, &cell );
				cell.SetText( "" );
				cell.SetBitmap( NULL );
				cell.SetCellType( UGCT_NORMAL );
				cell.SetBackColor( RGB(255,255,255));

				if ( yIndex == 0 && xIndex + 1 == nMinDay )
					cell.SetBorder( UG_BDR_RTHIN|UG_BDR_BTHIN );
				else if ( yIndex == 0 && xIndex < nMinDay )
					cell.SetBorder( UG_BDR_BTHIN );
				else
					cell.SetBorder( 0 );

				//cell.SetBorderColor( &m_borderPen );
				SetCell( xIndex, yIndex + 1, &cell );
			}
			else
			{	// ** work on the day's number cell
				GetCellIndirect( xIndex, yIndex, &cell );
				// set cell's value and alignemnt
				cell.SetNumber( nLoopDay + 1 );
				cell.SetAlignment( UG_ALIGNCENTER|UG_ALIGNVCENTER );
				// set back color and border properties
				cell.SetBackColor( RGB(210,210,210));
				cell.SetBorder( UG_BDR_RTHIN );
				cell.SetBorderColor( &m_borderPen );
				// commit changes
				SetCell( xIndex, yIndex, &cell );
				// ** work on the day's info cell
				GetCellIndirect( xIndex, yIndex + 1, &cell );
				// to indicate that this day has appointments set ...
				if ( GetAppCount( nLoopDay ) > 0 )
				{
					cell.SetText( "  ..." );
					cell.SetBitmap( GetBitmap( m_nBellBmpIndex ));
				}
				else
				{
					cell.SetText( "" );
					cell.SetBitmap( NULL );
				}

				// set dropdown grid celltype
				cell.SetCellType( m_dropGridCT.GetID());
				cell.SetCellTypeEx( UGCT_DROPLISTHIDEBUTTON|UGCT_NORMALELLIPSIS );
				// set back color and border properties
				cell.SetBackColor( RGB(255,255,255));
				cell.SetBorder( UG_BDR_RTHIN|UG_BDR_BTHIN );
				cell.SetBorderColor( &m_borderPen );
				// commit changes
				SetCell( xIndex, yIndex + 1, &cell );

				nLoopDay ++;
			}
		}
	}

	m_tempDateTime.SetDate( m_nCurrYear, m_nCurrMonth, 1 );
}

/////////////////////////////////////////////////////////////////////////////
//	GetAppCount
void MyCug::GetMonthInfo( int &nMinDay, int &nDaysInMonth )
{
	if ( m_nCurrMonth == -1 || m_nCurrYear == -1 )
	{
		COleDateTime curDate = COleDateTime::GetCurrentTime();

		if ( m_nCurrMonth == -1 )
			m_nCurrMonth = curDate.GetMonth();

		if ( m_nCurrYear == -1 )
			m_nCurrYear = curDate.GetYear();
	}

	COleDateTime workMonth( m_nCurrYear, m_nCurrMonth, 1, 0, 0, 0 );
	COleDateTime nextMonth( m_nCurrYear, m_nCurrMonth + 1, 1, 0, 0, 0 );

	nMinDay = workMonth.GetDayOfWeek() - 1;
	
	if ( m_nCurrMonth < 12 )
		nDaysInMonth = nextMonth.GetDayOfYear() - workMonth.GetDayOfYear();
	else
		nDaysInMonth = 31;

	COleDateTime endOfMonth( m_nCurrYear, m_nCurrMonth, nDaysInMonth, 0, 0, 0 );

	// refresh the 'hidden' recordset that contains information on
	// howmany appointments are for each day in the month
	CString sqlStr = "SELECT DISTINCT Date, COUNT(Date) FROM Appointments "
					 "WHERE Date BETWEEN #" + workMonth.Format() + "# AND "
					 "#" + endOfMonth.Format() + "# "
					 "GROUP BY [Date];";
	m_adoRecordSet.OpenSQL( sqlStr, "Driver={Microsoft Access Driver (*.mdb)};Dbq=Appointments.mdb;Uid=;Pwd=;" );
}

/////////////////////////////////////////////////////////////////////////////
//	GetAppCount
int MyCug::GetAppCount( int nDayOfMonth )
{
	// loop through the record set to check if given day has
	// appointments associated with it
	for ( int nIndex = 0; nIndex < m_adoRecordSet.GetNumRowsComplete(); nIndex ++ )
	{
		CUGCell cell;
		m_adoRecordSet.GetCell( 0, nIndex, &cell );
		COleDateTime dateTime = cell.GetNumber();

		if ( dateTime.GetDay() - 1 == nDayOfMonth )
		{
			m_adoRecordSet.GetCell( 1, nIndex, &cell );
			return (int)cell.GetNumber();
		}
	}

	return 0;
}