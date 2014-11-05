/////////////////////////////////////////////////////////////////////////////
//	Skeleton Class for a Derived MyCug 97

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

// define help topics
#include ".\\hlp\\TopicsDefines.h"

/////////////////////////////////////////////////////////////////////////////
// Standard MyCug construction/destruction
MyCug::MyCug()
{
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
	m_hdgFont.CreateFont( -13, 0, 0, 0, 600, 0, 0, 0, 0, 0, 0, 0, 0, "Arial" );
	m_bodyFont.CreateFont( -13, 0, 0, 0, 400, 0, 0, 0, 0, 0, 0, 0, 0, "Arial" );

	CUGCell cell;
	int cols = 8,
		rows = 40;

	SetDefFont( &m_bodyFont );

	GetHeadingDefault( &cell );
	cell.SetFont( &m_hdgFont );
	SetHeadingDefault( &cell );

	SetTabWidth( 200 );
	AddTab( "Tab 1", 1001 );
	AddTab( "Tab 2", 1001 );
	AddTab( "Tab 3", 1001 );
	AddTab( "Tab 4", 1001 );

	SetDefColWidth( 60 );

	SetNumberRows( rows );
	SetNumberCols( cols );
}

/////////////////////////////////////////////////////////////////////////////
//	OnGetCell
void MyCug::OnGetCell( int col, long row, CUGCell *cell )
{
	if ( col == -1 && row >= 0 )
	{
		cell->SetNumberDecimals( 0 );
		cell->SetNumber( row );
	}
	else if ( row == -1 && col >= 0 )
	{
		cell->SetNumberDecimals( 0 );
		cell->SetNumber( col );
	}
	else if ( col >= 0 && row >= 0 )
	{
		cell->SetNumberDecimals( 0 );
		cell->SetNumber( rand()%100 );
		cell->SetAlignment( UG_ALIGNRIGHT );
	}
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
	return RGB(100,150,150);
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
	// This example displays help topicks based on the grid's section, but
	// this notification provides much greater functionality.  You can 
	// display any help topic (provided you know its ID) based on any
	// cryteria you want, ie. cell's back color, cell's datatype, etc.
	switch ( section )
	{
	case UG_GRID:
		return HID_GRID;
	case UG_TOPHEADING:
		return HID_TOPHEADING;
	case UG_SIDEHEADING:
		return HID_SIDEHEADING;
	case UG_CORNERBUTTON:
		return HID_CORNERBTN;
	case UG_HSCROLL:
		return HID_HSCROLL;
	case UG_VSCROLL:
		return HID_VSCROLL;
	case UG_TAB:
		return HID_TAB;
	}

	return 0;
}
