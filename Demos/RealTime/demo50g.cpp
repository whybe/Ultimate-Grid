/***********************************************
	Ultimate Grid
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.


	class 
		CUGCRealTimeGrid
	Purpose
		General purpose derived grid class.
		This class can be used as a starting 
		point for any grid project.
************************************************/

#include "stdafx.h"
#include "resource.h"
#include "Demo50G.h"
#include "realtime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CRealTimeGrid,CUGCtrl)
	//{{AFX_MSG_MAP(CRealTimeGrid)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/***************************************************
****************************************************/
CRealTimeGrid::CRealTimeGrid()
{
	UGXPThemes::UseThemes(true);
}
/***************************************************
****************************************************/
CRealTimeGrid::~CRealTimeGrid()
{
	UGXPThemes::CleanUp();
}

/***************************************************
OnSetup
	This function is called just after the grid window 
	is created or attached to a dialog item.
	It can be used to initially setup the grid
****************************************************/
void CRealTimeGrid::OnSetup(){
	
	int y;
	int ROWS = 25;
	int COLS = 6;
	int iHeight;
	CUGCell cell;
	CString strTemp;
	CDC* pDC;

	m_pro1Index = AddCellType( &m_pro1 );
	m_pro1.SetCanAdjust( FALSE );
	m_buttonIndex = AddCellType( &m_button );

	pDC = GetDC();
	iHeight = -MulDiv( 10, GetDeviceCaps( pDC->m_hDC, LOGPIXELSY), 72 );
	m_font1.CreateFont( iHeight,0,0,0,800,0,0,0,0,0,0,0,0, _T( "Arial" ) );
	m_font2.CreateFont( iHeight,0,0,0,500,0,0,0,0,0,0,0,0, _T( "Arial" ) );
	ReleaseDC( pDC );
	
	SetDefFont(&m_font2);

	SetUniformRowHeight(TRUE);
	SetDefRowHeight(25);
	SetNumberCols(COLS);
	SetNumberRows(ROWS);
	SetDoubleBufferMode(1);
	Set3DHeight( 2 );

	SetTH_Height( 0 );
	SetSH_Width( 100 );

	for( y = 0 ; y < ROWS ; y++ )
	{
		QuickSetCellType(0,y,m_pro1Index);
		QuickSetAlignment(0,y,UG_ALIGNCENTER|UG_ALIGNVCENTER);
		QuickSetText( 0, y, _T( "20" ) );
		QuickSetTextColor(0,y,RGB(0,0,0));
		QuickSetHTextColor(0,y,RGB(0,0,0));
		JoinCells(0,y,2,y);

		QuickSetAlignment(3,y,UG_ALIGNCENTER|UG_ALIGNVCENTER);
		QuickSetText(3,y,_T( "Normal" ) );
		//QuickSetFont(3,y,&m_font2);

		strTemp.Format( _T( "Sensor %d" ), y );
		QuickSetText( -1, y, strTemp );
	}

	GetColDefault( 4, &cell );
	cell.SetCellType( m_buttonIndex );
	cell.SetText( _T( "Reset" ) );
	cell.SetAlignment( UG_ALIGNCENTER | UG_ALIGNVCENTER );
	cell.SetBackColor( GetSysColor( COLOR_BTNFACE ) );
	SetColDefault( 4, &cell );

	GetColDefault( 5, &cell );
	cell.SetCellType( UGCT_CHECKBOX );
	cell.SetLabelText( _T( "Enabled" ) );
	cell.SetBool( TRUE );
	cell.SetAlignment( UG_ALIGNVCENTER );
	SetColDefault( 5, &cell );
	SetColWidth( 5, GetColWidth( 5 ) + 20 );

	SetTimer( TIMERID, 100, NULL);
}

void CRealTimeGrid::OnGetCell( int col, long row, CUGCell *cell )
{
	if( col == -1 && row == m_GI->m_currentRow )
		cell->SetFont( &m_font1 );
}

int CRealTimeGrid::OnCellTypeNotify(long ID,int col,long row,long msg,long param)
{
	if( ID == m_buttonIndex && msg == UGCT_BUTTONCLICK )
	{
		QuickSetNumber( 0, row, 0 );
		QuickRedrawCell( 0, row );

		CUGCell cell;
		GetCell( 3, row, &cell );
		cell.SetBackColor(RGB(255,255,255));
		cell.SetTextColor(RGB(0,0,0));
		cell.SetText( _T( "Okay" ) );
		SetCell( 3, row, &cell );
		QuickRedrawCell( 3, row );

		TRACE( _T( "Reset the progress bar in row %ld" ), row );
		GotoCell( -1, row );
	}

	if( ID == UGCT_CHECKBOX && msg == UGCT_CHECKBOXSET )
	{
		if( param == TRUE )
			TRACE( _T( "Progress bar in row %ld was enabled." ), row );
		else
			TRACE( _T( "Progress bar in row %ld was disabled." ), row );
	}
		
	return TRUE;
}

void CRealTimeGrid::OnRowSizing(long row,int *height)
{
	if( *height < 18 )
		*height = 18;
	else if ( *height > 50 )
		*height = 50;
}

void CRealTimeGrid::OnTimer(UINT nIDEvent) 
{
	CUGCell cell, enableCell;
	CString string;
	int		row,random;
	double	oldValue;
	double	newValue;
	long	direction;
	
	int numRows = (int)GetNumberRows();

	//update the progress bars
	for ( row=0; row < numRows; row++)
	{
		GetCellIndirect( 5, row, &enableCell );
		if( enableCell.GetBool() == FALSE )
			continue;
		
		//get the old info
		GetCell(0,row,&cell);
				
		oldValue = cell.GetNumber();
		direction = cell.GetCellTypeEx();

		//get the random number
		random = rand() % 7;

		//move the current position in the same direction
		if (random < 6){
			if (direction == CT_NEGATIVE){
				newValue = oldValue  - random;
				if(newValue < 0){
					newValue = 0;
					cell.SetCellTypeEx(CT_POSITIVE);		
				}
			}
			else{
				newValue = oldValue  + random;
				if(newValue >100){
					newValue = 100;
					cell.SetCellTypeEx(CT_NEGATIVE);
				}
			}

			//update the cell	
			cell.SetNumber(newValue);
			SetCell(0,row,&cell);
			QuickRedrawCell(0,row);

			//set the alert status
			GetCell(3,row,&cell);

			// turn off themes for these cells, to show the coloured backgrounds.
			cell.UseThemes(false);
			cell.GetText(&string);
			if( newValue > 90 )// && string != _T( "Alert" ) )
			{
				cell.SetBackColor(RGB(255,0,0));
				cell.SetTextColor(RGB(255,255,255));
				cell.SetText( _T( "Ahhhhhhh!" ) );
				SetCell( 3, row, &cell );
				QuickRedrawCell( 3, row );
			} 
			else if( newValue <= 90 && newValue >= 50 ) //string == "Alert"){
			{
				cell.SetBackColor( RGB( 200, 200, 0 ) );
				cell.SetTextColor( RGB( 0, 0, 0 ) );
				cell.SetText( _T( "Uh-oh!" ) );
				SetCell( 3, row, &cell );
				QuickRedrawCell( 3, row );
			}	
			else
			{
				cell.SetBackColor(RGB(255,255,255));
				cell.SetTextColor(RGB(0,0,0));
				cell.SetText( _T( "Okay" ) );
				SetCell( 3, row, &cell );
				QuickRedrawCell( 3, row );
			}
		}
		//reverse directions
		else{
			if (direction == CT_NEGATIVE)
				direction = CT_POSITIVE;
			else
				direction = CT_NEGATIVE;
			cell.SetCellTypeEx(direction);
			SetCell(0,row,&cell);
		}
	}
	
	CUGCtrl::OnTimer(nIDEvent);
}

/***********************************************
	QuickRedrawCell
		The QuickRedrawCell function is used to quickly
		and effectively redraw a cell.  This function
		will directly add draw hints to the CUGGrid and
		use PaintDrawHintsNow to quickly redraw a cell.
***********************************************/
void CRealTimeGrid::QuickRedrawCell( int col, long row )
{
	CRect rect;
	GetCellRect( col, row, rect );
	m_CUGGrid->m_drawHint.AddHint( col, row, col, row );

	if( GetCurrentRow() != row || GetCurrentCol() != col )
		TempDisableFocusRect();

	m_CUGGrid->PaintDrawHintsNow( rect );
}