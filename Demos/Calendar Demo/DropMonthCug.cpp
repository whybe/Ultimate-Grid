/////////////////////////////////////////////////////////////////////////////
//	Skeleton Class for a Derived CUGCtrl class

#include "stdafx.h"
#include "resource.h"
#include "DropMonthCug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CDropMonthCug,CUGCtrl)
	//{{AFX_MSG_MAP(CDropMonthCug)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Standard CDropMonthCug construction/destruction
CDropMonthCug::CDropMonthCug()
{
	m_nYear = COleDateTime::GetCurrentTime().GetYear();
}

CDropMonthCug::~CDropMonthCug()
{
}

/////////////////////////////////////////////////////////////////////////////
//	OnSetup
//		This function is called just after the grid window 
//		is created or attached to a dialog item.
//		It can be used to initially setup the grid
void CDropMonthCug::OnSetup()
{
	int cols = 2,
		rows = 12;
	CString tempStr;
	CUGCell cell;
	TCHAR *monthInfo[12] = {"January","February","March","April","May","June","July","August","September","October","November","December"};

	GetHeadingDefault( &cell );
	int hedingFontIndex = AddFont( "Arial", -13, 700 );
	cell.SetFont( GetFont( hedingFontIndex ));
	cell.SetTextColor( RGB(0,0,200));
	SetHeadingDefault( &cell );

	GetGridDefault( &cell );
	int gridFontIndex = AddFont( "Arial", -13, 400 );
	cell.SetFont( GetFont( gridFontIndex ));
	SetGridDefault( &cell );

	SetUserSizingMode( 0 );
	SetNumberRows( rows );
	SetNumberCols( cols );

	// The two scroll buttons in the top heading
	QuickSetCellType( -1, -1, UGCT_ARROW );
	QuickSetCellTypeEx( -1, -1, UGCT_ARROWLEFT );
	QuickSetCellType( 1, -1, UGCT_ARROW );
	QuickSetCellTypeEx( 1, -1, UGCT_ARROWRIGHT );

	// Month information
	for ( int nIndex = 0; nIndex < rows; nIndex ++ )
	{
		JoinCells( 0, nIndex, 1, nIndex );
		tempStr.Format( "%d", nIndex + 1 );
		QuickSetText( -1, nIndex, tempStr );
		QuickSetText( 0, nIndex, monthInfo[nIndex] );
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
void CDropMonthCug::OnGetCell(int col,long row,CUGCell *cell)
{
	if ( col == 0 && row == -1 )
	{
		cell->SetPropertyFlags( cell->GetPropertyFlags()|UGCELL_DONOT_LOCALIZE );
		cell->SetNumber( m_nYear );
	}
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
void CDropMonthCug::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(*rect);
	UNREFERENCED_PARAMETER(*point);
	UNREFERENCED_PARAMETER(processed);

	if ( updn && col == 1 )
	{
		m_nYear ++;
		RedrawCell( 0, -1 );
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
void CDropMonthCug::OnTH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{
	OnTH_LClicked( col, row, 1, rect, point, processed );
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
void CDropMonthCug::OnCB_LClicked(int updn,RECT *rect,POINT *point,BOOL processed)
{
	UNREFERENCED_PARAMETER(*rect);
	UNREFERENCED_PARAMETER(*point);
	UNREFERENCED_PARAMETER(processed);

	if ( updn )
	{
		m_nYear --;
		RedrawCell( 0, -1 );
	}
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
void CDropMonthCug::OnCB_DClicked(RECT *rect,POINT *point,BOOL processed)
{
	OnCB_LClicked( 1, NULL, NULL, processed );
}
