/*************************************************************************
				Class Implementation : CUGExcel
**************************************************************************
	Source file : UGExcel.cpp
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
*************************************************************************/
#include "stdafx.h"
#include "resource.h"
#include "UGExcel.h"

#include "UGStrOp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CUGExcel,CUGCtrl)
	//{{AFX_MSG_MAP(CUGExcel)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Standard CUGExcel construction/destruction
CUGExcel::CUGExcel()
{
 	UGXPThemes::UseThemes(true);

	m_fontsList = NULL;
	m_excelTopHdg = NULL;
	m_excelSideHdg = NULL;
	m_hiddenColsList = NULL;
	m_pCurEnumItem = NULL;
	m_bForceEnumRestart = TRUE;
}

CUGExcel::~CUGExcel()
{
	UGXPThemes::CleanUp();
	// clean up possible fonts allocated by the user
	_tagFonts *pFont, *pTemp;
	pFont = m_fontsList;
	while ( pFont != NULL )
	{
		pTemp = pFont->next;
		delete pFont;
		pFont = pTemp;
	}
	// clean up information on possibly hidden columns
	_tagHiddenCols *pColItem, *pTempColItem;
	pColItem = m_hiddenColsList;
	while ( pColItem != NULL )
	{
		pTempColItem = pColItem->next;
		delete pColItem;
		pColItem = pTempColItem;
	}
	// we do not have to delete the m_excelTopHdg or the m_excelSideHdg,
	// these objects will be deleted by the framework.
}

/////////////////////////////////////////////////////////////////////////////
int CUGExcel::GotoCell(int col,long row)
{
	return CUGCtrl::GotoCell( LocateCol( col ), row );
}
/////////////////////////////////////////////////////////////////////////////
int CUGExcel::BestFit(int startCol,int endCol,int CalcRange,int flag)
{
	UNREFERENCED_PARAMETER(flag);
	return CUGCtrl::BestFit( LocateCol( startCol ), LocateCol( endCol ), CalcRange, 0 );;
}
/////////////////////////////////////////////////////////////////////////////
int CUGExcel::RedrawCell(int col,long row)
{
	return CUGCtrl::RedrawCell( LocateCol( col ), row );;
}
/////////////////////////////////////////////////////////////////////////////
int CUGExcel::GetCell(int col,long row,CUGCell *cell)
{
	return CUGCtrl::GetCell( LocateCol( col ), row, cell );
}
/////////////////////////////////////////////////////////////////////////////
int CUGExcel::SetCell(int col,long row,CUGCell *cell)
{
	return CUGCtrl::SetCell( LocateCol( col ), row, cell );;
}
/////////////////////////////////////////////////////////////////////////////
int CUGExcel::SetColWidth(int col,int width)
{
	if ( col < 0 )
	{
		col = (col * -1) -1;
		SetSH_ColWidth( col, width );
	}
	else
	{
		CUGCtrl::SetColWidth( LocateCol( col ), width );
		m_CUGHScroll->Update();
	}

	return UG_SUCCESS;
}
/////////////////////////////////////////////////////////////////////////////
int CUGExcel::GetColDefault(int col,CUGCell *cell)
{
	return CUGCtrl::GetColDefault( LocateCol( col ), cell );;
}
/////////////////////////////////////////////////////////////////////////////
int CUGExcel::SetColDefault(int col,CUGCell *cell)
{
	return CUGCtrl::SetColDefault( LocateCol( col ), cell );;
}
/////////////////////////////////////////////////////////////////////////////
int CUGExcel::Select(int col,long row)
{
	return CUGCtrl::Select( LocateCol( col ), row );
}
/////////////////////////////////////////////////////////////////////////////
int CUGExcel::SelectRange(int startCol,long startRow,int endCol,long endRow)
{
	return CUGCtrl::SelectRange( LocateCol( startCol ), startRow, LocateCol( endCol ), endRow );
}
/////////////////////////////////////////////////////////////////////////////
BOOL CUGExcel::IsSelected(int col,long row,int *blockNum )
{
	UNREFERENCED_PARAMETER(blockNum);
	return CUGCtrl::IsSelected( LocateCol( col ), row );
}
/////////////////////////////////////////////////////////////////////////////
int CUGExcel::EnumFirstSelected(int *col,long *row)
{
	int retVal = CUGCtrl::EnumFirstSelected( col, row );
	*col = LocateCol( *col );

	return retVal;
}
/////////////////////////////////////////////////////////////////////////////
int CUGExcel::EnumNextSelected(int *col,long *row)
{
	int retVal = CUGCtrl::EnumNextSelected( col, row );
	*col = LocateCol( *col );

	return retVal;
}
/////////////////////////////////////////////////////////////////////////////
int CUGExcel::EnumFirstBlock(int *startCol,long *startRow,int *endCol,long *endRow)
{
	int retVal = CUGCtrl::EnumFirstBlock( startCol, startRow, endCol, endRow );
	*startCol = LocateCol( *startCol );
	*endCol = LocateCol( *endCol );

	return retVal;
}
/////////////////////////////////////////////////////////////////////////////
int CUGExcel::EnumNextBlock(int *startCol,long *startRow,int *endCol,long *endRow)
{
	int retVal = CUGCtrl::EnumNextBlock( startCol, startRow, endCol, endRow );
	*startCol = LocateCol( *startCol );
	*endCol = LocateCol( *endCol );

	return retVal;
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::JoinCells(int startcol,long startrow,int endcol,long endrow)
{
	return CUGCtrl::JoinCells( LocateCol( startcol ), startrow, LocateCol( endcol ), endrow );
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::UnJoinCells(int col,long row)
{
	return CUGCtrl::UnJoinCells( LocateCol( col ), row );
}
/////////////////////////////////////////////////////////////////////////////
int CUGExcel::RedrawCol(int col)
{
	return CUGCtrl::RedrawCol( LocateCol( col ));
}
/////////////////////////////////////////////////////////////////////////////
int CUGExcel::RedrawRange(int startCol,long startRow,int endCol,long endRow)
{
	return CUGCtrl::RedrawRange( LocateCol( startCol ), startRow, LocateCol( endCol ), endRow );
}
/////////////////////////////////////////////////////////////////////////////
int CUGExcel::FitToWindow(int startCol,int endCol)
{
	return CUGCtrl::FitToWindow( LocateCol( startCol ), LocateCol( endCol ));
}
/////////////////////////////////////////////////////////////////////////////
int CUGExcel::SortBy(int col,int flag )
{
	return CUGCtrl::SortBy( LocateCol( col ), flag );
}
/////////////////////////////////////////////////////////////////////////////
int CUGExcel::SortBy( int *cols, int num, int flag )
{
	return CUGCtrl::SortBy( cols, num, flag );
}
/////////////////////////////////////////////////////////////////////////////
int CUGExcel::GotoCol(int col)
{
	return CUGCtrl::GotoCol( LocateCol( col ));
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::GetCurrentCol()
{
	return LocateCol( CUGCtrl::GetCurrentCol());
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::GetLeftCol()
{
	return LocateCol( CUGCtrl::GetLeftCol());
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::GetRightCol()
{
	return LocateCol( CUGCtrl::GetRightCol());
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::SetLeftCol(int col)
{
	return CUGCtrl::SetLeftCol( LocateCol( col ));
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::StartEdit()
{
	return CUGCtrl::StartEdit();
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::StartEdit(int key)
{
	return CUGCtrl::StartEdit( key );
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::StartEdit(int col,long row,int key)
{
	return CUGCtrl::StartEdit( LocateCol( col ), row, key );
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::InsertCol(int col)
{
	return CUGCtrl::InsertCol( LocateCol( col ));
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::DeleteCol(int col)
{
	return CUGCtrl::DeleteCol( LocateCol( col ));
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::GetColWidth(int col,int *width)
{
	if ( col < 0 )
	{
		col = (col * -1) -1;

		if( col >= 0 && col < m_GI->m_numberSideHdgCols )
		{
			*width = m_GI->m_sideHdgWidths[col];
		}
		else
		{
			*width = GetSH_Width();
		}
	}
	else
	{
		*width = CUGCtrl::GetColWidth( LocateCol( col ));
	}

	return UG_SUCCESS;
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::GetColWidth( int col )
{
	int nWidth;
	GetColWidth( col, &nWidth );

	return nWidth;
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::DeleteCell(int col,long row)
{
	return CUGCtrl::DeleteCell( LocateCol( col ), row );
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::QuickSetText(int col,long row,LPCTSTR string)
{
	return CUGCtrl::QuickSetText( LocateCol( col ), row, string );
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::QuickSetNumber(int col,long row,double number)
{
	return CUGCtrl::QuickSetNumber( LocateCol( col ), row, number );
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::QuickSetMask(int col,long row,LPCTSTR string)
{
	return CUGCtrl::QuickSetMask( LocateCol( col ), row, string );
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::QuickSetLabelText(int col,long row,LPCTSTR string)
{
	return CUGCtrl::QuickSetLabelText( LocateCol( col ), row, string );
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::QuickSetTextColor(int col,long row,COLORREF color)
{
	return CUGCtrl::QuickSetTextColor( LocateCol( col ), row, color );
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::QuickSetBackColor(int col,long row,COLORREF color)
{
	return CUGCtrl::QuickSetBackColor( LocateCol( col ), row, color );
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::QuickSetAlignment(int col,long row,int align)
{
	return CUGCtrl::QuickSetAlignment( LocateCol( col ), row, (short)align );
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::QuickSetBorder(int col,long row,int border)
{
	return CUGCtrl::QuickSetBorder( LocateCol( col ), row, (short) border );
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::QuickSetBorderColor(int col,long row,CPen *pen)
{
	return CUGCtrl::QuickSetBorderColor( LocateCol( col ), row, pen );
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::QuickSetFont(int col,long row,CFont * font)
{
	return CUGCtrl::QuickSetFont( LocateCol( col ), row, font );
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::QuickSetFont(int col,long row,int index)
{
	return CUGCtrl::QuickSetFont( LocateCol( col ), row, index );
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::QuickSetBitmap(int col,long row,CBitmap * bitmap)
{
	return CUGCtrl::QuickSetBitmap( LocateCol( col ), row, bitmap );
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::QuickSetBitmap(int col,long row,int index)
{
	return CUGCtrl::QuickSetBitmap( LocateCol( col ), row, index );
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::QuickSetCellType(int col,long row,long type)
{
	return CUGCtrl::QuickSetCellType( LocateCol( col ), row, type );
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::QuickSetCellTypeEx(int col,long row,long typeEx)
{
	return CUGCtrl::QuickSetCellTypeEx( LocateCol( col ), row, typeEx );
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::QuickSetHTextColor(int col,long row,COLORREF color)
{
	return CUGCtrl::QuickSetHTextColor( LocateCol( col ), row, color );
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::QuickSetHBackColor(int col,long row,COLORREF color)
{
	return CUGCtrl::QuickSetHBackColor( LocateCol( col ), row, color );
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::QuickSetRange(int startCol,long startRow,int endCol,long endRow, CUGCell* cell)
{
	return CUGCtrl::QuickSetRange( LocateCol( startCol ), startRow, LocateCol( endCol ), endRow, cell );
}
/////////////////////////////////////////////////////////////////////////////
int	CUGExcel::QuickGetText(int col,long row,CString *string)
{
	return CUGCtrl::QuickGetText( LocateCol( col ), row, string );
}
/////////////////////////////////////////////////////////////////////////////
LPCTSTR	CUGExcel::QuickGetText(int col,long row)
{
	return CUGCtrl::QuickGetText( LocateCol( col ), row );
}
/////////////////////////////////////////////////////////////////////////////
int CUGExcel::FindFirst(CString *string,int *col,long *row,long flags)
{
	int retVal = CUGCtrl::FindFirst( string, col, row, flags );
	*col = LocateCol( *col );

	return retVal;
}
/////////////////////////////////////////////////////////////////////////////
int CUGExcel::FindNext(CString *string,int *col,long *row,int flags)
{
	int retVal = CUGCtrl::FindNext( string, col, row, flags );
	*col = LocateCol( *col );

	return retVal;
}
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//	OnSetup
//		This function is called just after the grid window 
//		is created or attached to a dialog item.
//		It can be used to initially setup the grid
void CUGExcel::OnSetup()
{
	// create and set new top-heading class
	m_excelTopHdg = new CExcelTopHdg;
	m_excelTopHdg->Create( NULL, "", WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 234752 );
	SetNewTopHeadingClass( m_excelTopHdg );
	// create and set new side-heading class
	m_excelSideHdg = new CExcelSideHdg;
	m_excelSideHdg->Create( NULL, "", WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 234753 );
	SetNewSideHeadingClass( m_excelSideHdg );
	// create the default pen representing cell's border
	m_cellBorderPen.CreatePen( PS_SOLID, 1, RGB(157,157,161));
	// add and set heading's default celltype
	CUGCell cell;
	GetHeadingDefault( &cell );
	cell.SetBorder( UG_BDR_RTHIN|UG_BDR_BTHIN );
	cell.SetBackColor( RGB(239,237,222));	
	cell.SetHBackColor( RGB(162,192,248));	
	cell.SetBorderColor( &m_cellBorderPen );
	SetHeadingDefault( &cell );

	// create a font and set it as Grid Default
	GetGridDefault( &cell );
	cell.SetFont( CreateFont( -11, 0, 0, 0, 200, 0, 0, 0, 0, 0, 0, 0, 0, "Arial" ));
	cell.SetBorderColor( &m_cellBorderPen );
	cell.SetBorder( UG_BDR_RTHIN|UG_BDR_BTHIN );
	SetGridDefault( &cell );
	// create a font and set it as Heading Default
	GetHeadingDefault( &cell );
	cell.SetFont( CreateFont( -13, 0, 0, 0, 200, 0, 0, 0, 0, 0, 0, 0, 0, "Arial" ));
	SetHeadingDefault( &cell );

	// set default properties
	EnableMenu( TRUE );
	EnableExcelBorders( FALSE );
	SetMultiSelectMode( TRUE );
	SetDoubleBufferMode( TRUE );
	SetVScrollMode( UG_SCROLLTRACKING );
	SetHScrollMode( UG_SCROLLTRACKING );
	SetUserSizingMode( 2 );
}

/////////////////////////////////////////////////////////////////////////////
//	OnSheetSetup	
//		This notification is called for each additional sheet that the grid
//		might contain, here you can customize each sheet in the grid.
//	Params:
//		sheetNumber - idndex of current sheet
//	Return:
//		<none>
void CUGExcel::OnSheetSetup(int sheetNumber)
{
	UNREFERENCED_PARAMETER(sheetNumber);
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
int CUGExcel::OnCanMove(int oldcol,long oldrow,int newcol,long newrow)
{
	UNREFERENCED_PARAMETER(newrow);
	UNREFERENCED_PARAMETER(oldrow);

	oldcol = GetColTranslation( oldcol );
	newcol = GetColTranslation( newcol );

	// ...

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
int CUGExcel::OnCanViewMove(int oldcol,long oldrow,int newcol,long newrow)
{
	UNREFERENCED_PARAMETER(newrow);
	UNREFERENCED_PARAMETER(oldrow);

	oldcol = GetColTranslation( oldcol );
	newcol = GetColTranslation( newcol );

	// ...

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
void CUGExcel::OnHitBottom(long numrows,long rowspast,long rowsfound)
{
	UNREFERENCED_PARAMETER(numrows);
	UNREFERENCED_PARAMETER(rowspast);
	UNREFERENCED_PARAMETER(rowsfound);
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
void CUGExcel::OnHitTop(long numrows,long rowspast)
{
	UNREFERENCED_PARAMETER(numrows);
	UNREFERENCED_PARAMETER(rowspast);
}

/////////////////////////////////////////////////////////////////////////////
//	OnCanSizeCol
//		Sent when the user is about to size a given column
//	Params:
//		col - identifies column number that will be sized
//	Return:
//		TRUE - to allow sizing
//		FALSE - to prevent sizing
int CUGExcel::OnCanSizeCol(int col)
{
	BOOL allow = TRUE;

	// Do not allow hidden cols to be sized
	if ( GetColWidth( col ) == 0 )
	{	// the column is invisible, but is it located before first visible col?
		allow = FALSE;

		for( int xIndex = 0; xIndex < col && allow == FALSE; xIndex ++ )
		{
			if ( GetColWidth( xIndex ) > 0 )
			{
				allow = TRUE;
			}
		}
	}

	return allow;
}

/////////////////////////////////////////////////////////////////////////////
//	OnColSizing
//		Sent when the user is sizing a column
//	Params:
//		col - column currently sizing
//		width - current new column width
//	Return:
//		<none>
void CUGExcel::OnColSizing(int col,int *width)
{
	UNREFERENCED_PARAMETER(width);
	col = GetColTranslation( col );
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
void CUGExcel::OnColSized(int col,int *width)
{
	UNREFERENCED_PARAMETER(width);
	col = GetColTranslation( col );
}

/////////////////////////////////////////////////////////////////////////////
//	OnCanSizeRow
//		Sent when the user is about to start sizing of a row
//	Params:
//		row - identifies row number that will be sized
//	Return:
//		TRUE - to allow sizing
//		FALSE - to prevent sizing
int CUGExcel::OnCanSizeRow(long row)
{
	UNREFERENCED_PARAMETER(row);
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
void CUGExcel::OnRowSizing(long row,int *height)
{
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(height);
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
void CUGExcel::OnRowSized(long row,int *height)
{
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(height);
}

/////////////////////////////////////////////////////////////////////////////
//	OnCanSizeSideHdg
//		Sent when the user is about to start sizing of the side heading
//	Params:
//		<none>
//	Return:
//		TRUE - to allow sizing
//		FALSE - to prevent sizing
int CUGExcel::OnCanSizeSideHdg()
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
int CUGExcel::OnSideHdgSizing(int *width)
{
	UNREFERENCED_PARAMETER(width);
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
int CUGExcel::OnSideHdgSized(int *width)
{
	UNREFERENCED_PARAMETER(width);
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
int CUGExcel::OnCanSizeTopHdg()
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
int CUGExcel::OnTopHdgSizing(int *height)
{
	UNREFERENCED_PARAMETER(height);
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
int CUGExcel::OnTopHdgSized(int *height)
{
	UNREFERENCED_PARAMETER(height);
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
void CUGExcel::OnColChange(int oldcol,int newcol)
{
	oldcol = GetColTranslation( oldcol );
	newcol = GetColTranslation( newcol );

	m_CUGTopHdg->Invalidate();
	m_CUGSideHdg->Invalidate();	
}

/////////////////////////////////////////////////////////////////////////////
//	OnRowChange
//		Sent whenever the current row changes
//	Params:
//		oldrow - row that is loosing the locus
//		newrow - row that user moved into
//	Return:
//		<none>
void CUGExcel::OnRowChange(long oldrow,long newrow)
{
	UNREFERENCED_PARAMETER(oldrow);
	UNREFERENCED_PARAMETER(newrow);
	m_CUGTopHdg->Invalidate();
	m_CUGSideHdg->Invalidate();	
}

/////////////////////////////////////////////////////////////////////////////
//	OnCellChange
//		Sent whenever the current cell changes
//	Params:
//		oldcol, oldrow - coordinates of cell that is loosing the focus
//		newcol, newrow - coordinates of cell that is gaining the focus
//	Return:
//		<none>
void CUGExcel::OnCellChange(int oldcol,int newcol,long oldrow,long newrow)
{
	UNREFERENCED_PARAMETER(oldrow);
	UNREFERENCED_PARAMETER(newrow);
	oldcol = GetColTranslation( oldcol );
	newcol = GetColTranslation( newcol );
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
void CUGExcel::OnLeftColChange(int oldcol,int newcol)
{
	oldcol = GetColTranslation( oldcol );
	newcol = GetColTranslation( newcol );
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
void CUGExcel::OnTopRowChange(long oldrow,long newrow)
{
	UNREFERENCED_PARAMETER(oldrow);
	UNREFERENCED_PARAMETER(newrow);
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
void CUGExcel::OnLClicked(int col,long row,int updn,RECT *rect,POINT *point,int processed)
{
	UNREFERENCED_PARAMETER(processed);
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(updn);
	UNREFERENCED_PARAMETER(row);
	col = GetColTranslation( col );
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
void CUGExcel::OnRClicked(int col,long row,int updn,RECT *rect,POINT *point,int processed)
{
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(updn);
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(processed);
	col = GetColTranslation( col );
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
void CUGExcel::OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(processed);
	col = GetColTranslation( col );
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
void CUGExcel::OnMouseMove(int col,long row,POINT *point,UINT nFlags,BOOL processed)
{
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(nFlags);
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(processed);

	col = GetColTranslation( col );

	if( nFlags & MK_LBUTTON )
	{
		m_CUGTopHdg->Invalidate();
		m_CUGSideHdg->Invalidate();
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
void CUGExcel::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(updn);
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(processed);
	col = GetColTranslation( col );
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
void CUGExcel::OnTH_RClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(updn);
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(processed);
	col = GetColTranslation( col );
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
void CUGExcel::OnTH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(processed);
	col = GetColTranslation( col );
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
void CUGExcel::OnSH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(updn);
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(processed);
	col = GetColTranslation( col );
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
void CUGExcel::OnSH_RClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(updn);
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(processed);
	col = GetColTranslation( col );
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
void CUGExcel::OnSH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(processed);
	col = GetColTranslation( col );
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
void CUGExcel::OnCB_LClicked(int updn,RECT *rect,POINT *point,BOOL processed)
{
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(point);

	if ( !updn && !processed )
	{
		SelectRange( 0, 0, GetNumberCols()-1, GetNumberRows()-1 );
		m_CUGTopHdg->Invalidate();
		m_CUGSideHdg->Invalidate();	
	}
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
void CUGExcel::OnCB_RClicked(int updn,RECT *rect,POINT *point,BOOL processed)
{
	UNREFERENCED_PARAMETER(updn);
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(processed);
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
void CUGExcel::OnCB_DClicked(RECT *rect,POINT *point,BOOL processed)
{
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(processed);
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
void CUGExcel::OnKeyDown(UINT *vcKey,BOOL processed)
{
	UNREFERENCED_PARAMETER(processed);

	int col = GetCurrentCol();
	long row = GetCurrentRow();

	switch ( *vcKey )
	{
	case VK_TAB:	// handle cell movement using the TAB key
		if ( GetKeyState( VK_SHIFT ) < 0 )
		{
			col --;
			if ( col < 0 )
			{
				col = GetNumberCols() - 1;
			}
		}
		else
		{
			col ++;
			if ( col >= GetNumberCols())
			{
				col = 0;
			}
		}
		break;
	case VK_LEFT:
		if ( GetKeyState( VK_CONTROL ) < 0 )
			col = 0;

		break;
	case VK_RIGHT:
		if ( GetKeyState( VK_CONTROL ) < 0 )
			col = GetNumberCols()-1;

		break;
	case VK_UP:
		if ( GetKeyState( VK_CONTROL ) < 0 )
			row = 0;

		break;
	case VK_DOWN:
		if ( GetKeyState( VK_CONTROL ) < 0 )
			row = GetNumberRows()-1;

		break;
	case VK_HOME:
		if ( col == 0 )
			row = 0;

		break;
	case VK_END:
		if ( col == GetNumberCols() - 1 )
			row = GetNumberRows() - 1;

		break;
	case VK_DELETE:
		DeleteCell( col, row );
		RedrawCell( col, row );
	}

	if ( col != GetCurrentCol() || row != GetCurrentRow())
	{
		// make sure that current selection is cleared
		m_GI->m_multiSelect->ClearAll();
		m_GI->m_multiSelect->StartBlock( col, row );
		// move current cell to the new location
		GotoCell( col, row );
	}
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
void CUGExcel::OnCharDown(UINT *vcKey,BOOL processed)
{
	UNREFERENCED_PARAMETER(vcKey);
	UNREFERENCED_PARAMETER(processed);
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
void CUGExcel::OnGetCell(int col,long row,CUGCell *cell)
{
	int selCol;
	long selRow;

	// enumerate current selections and update proper cells
	EnumFirstSelected( &selCol, &selRow );
	do
	{
		if (( col >= 0 && row >= 0 ) && ( selRow == row || selCol == col ))
		{	// update the highlight colors for selected cells
			cell->SetHBackColor( BlendColors( cell->GetBackColor(), cell->GetHBackColor(), .6 ));
			cell->SetHTextColor( BlendColors( cell->GetTextColor(), cell->GetHTextColor(), .2 ));
			break;
		}
		else if (( col == -1 || row == -1 ) && ( selRow == row || selCol == col ))
		{	// change the back color of proper heading cells
			cell->SetBackColor( BlendColors( cell->GetBackColor(), cell->GetHBackColor(), .6 ));
			break;
		}

	} while ( EnumNextSelected( &selCol, &selRow ) != UG_ERROR );
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
void CUGExcel::OnSetCell(int col,long row,CUGCell *cell)
{
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(cell);
	col = GetColTranslation( col );
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
void CUGExcel::OnDataSourceNotify(int ID,long msg,long param)
{
	UNREFERENCED_PARAMETER(ID);
	UNREFERENCED_PARAMETER(msg);
	UNREFERENCED_PARAMETER(param);
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
int CUGExcel::OnCellTypeNotify(long ID,int col,long row,long msg,long param)
{
	UNREFERENCED_PARAMETER(ID);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(msg);
	UNREFERENCED_PARAMETER(param);

	col = GetColTranslation( col );

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
int CUGExcel::OnEditStart(int col, long row,CWnd **edit)
{
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(edit);

	col = GetColTranslation( col );

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
int CUGExcel::OnEditVerify(int col, long row,CWnd *edit,UINT *vcKey)
{
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(edit);
	UNREFERENCED_PARAMETER(vcKey);

	col = GetColTranslation( col );

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
int CUGExcel::OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag)
{
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(edit);
	UNREFERENCED_PARAMETER(string);
	UNREFERENCED_PARAMETER(cancelFlag);
	col = GetColTranslation( col );

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
int CUGExcel::OnEditContinue(int oldcol,long oldrow,int* newcol,long* newrow)
{
	UNREFERENCED_PARAMETER(newrow);
	UNREFERENCED_PARAMETER(oldrow);
	UNREFERENCED_PARAMETER(oldcol);
	int newColTemp = GetColTranslation( *newcol );
	*newcol = LocateCol( newColTemp );

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
void CUGExcel::OnMenuCommand(int col,long row,int section,int item)
{
	UNREFERENCED_PARAMETER(section);

	col = GetColTranslation( col );

	int selCol;
	long selRow;
	CUGCell cell;
	CFont *selectedFont = NULL;
	LOGFONT selectedLogFont;
	COLORREF textColor(RGB(0,0,0));
	COLORREF backColor;
	CColorDialog *colorDlg = NULL;

	if ( item > MSG_UNHIDE_COL )
	{	// handle possible
		UnHideCol( item - MSG_UNHIDE_COL );
		return;
	}

	switch( item )
	{
	case MSG_RESET_SELECTED:
		ResetSelected();
		break;
	case MSG_HIDE_COL:
		HideCol( col );
		break;
	case MSG_CHANGE_FONT:
		GetCellIndirect( col, row, &cell );
		break;
	case MSG_CHANGE_BACKCOLOR:
		GetCellIndirect( col, row, &cell );
		colorDlg = new CColorDialog( cell.GetBackColor());

		if ( colorDlg->DoModal())
		{
			backColor = colorDlg->GetColor();
			EnumFirstSelected( &selCol, &selRow );
			do
			{
				GetCell( selCol, selRow, &cell );
				cell.SetBackColor( backColor );
				SetCell( selCol, selRow, &cell );
			} while ( EnumNextSelected( &selCol, &selRow ) == UG_SUCCESS );
		}
		RedrawAll();
		break;
	case MSG_CHANGE_COL_FONT:
		GetColDefault( col, &cell );
		break;
	case MSG_CHANGE_COL_BACKCOLOR:
		GetColDefault( col, &cell );
		colorDlg = new CColorDialog( cell.GetBackColor());

		if ( colorDlg->DoModal())
		{
			cell.SetBackColor( colorDlg->GetColor());
			SetColDefault( col, &cell );
		}
		RedrawCol( col );
		break;
	}

	if ( item != MSG_CHANGE_FONT && item != MSG_CHANGE_COL_FONT )
	{	// only allow processing of this notification if the user
		// decided to change cell's font.
		return;
	}

	textColor = cell.GetTextColor();

	if ( ShowFontDlg( cell, selectedLogFont, textColor ))
	{
		selectedFont = CreateFontIndirect( selectedLogFont );

		switch( item )
		{
		case MSG_CHANGE_FONT:
			// change font of current cell/selection 
			// since we are working with a selection we must loop through all
			// selected cells to set new font and color settings
			EnumFirstSelected( &selCol, &selRow );
			do
			{
				GetCell( selCol, selRow, &cell );
				cell.SetFont( selectedFont );
				cell.SetTextColor( textColor );
				SetCell( selCol, selRow, &cell );
			} while ( EnumNextSelected( &selCol, &selRow ) == UG_SUCCESS );
			break;
		case MSG_CHANGE_COL_FONT:
			// change font of given col default
			GetColDefault( col, &cell );
			cell.SetFont( selectedFont );
			cell.SetTextColor( textColor );
			SetColDefault( col, &cell );
			break;
		}	
		RedrawAll();
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
int CUGExcel::OnMenuStart(int col,long row,int section)
{
	UNREFERENCED_PARAMETER(row);

	col = GetColTranslation( col );

	EmptyMenu();
	if ( section == UG_TOPHEADING )
	{
		CString tempStr;
		int hiddenCol = EnumHiddenCols();

		AddMenuItem(MSG_RESET_SELECTED, "Reset cells");

		AddMenuItem( MSG_HIDE_COL, "Hide Col" );
		while ( hiddenCol >= 0 )
		{
			tempStr.Format( "Un-Hide col %d", hiddenCol );
			AddMenuItem( MSG_UNHIDE_COL + hiddenCol, tempStr );
			hiddenCol = EnumHiddenCols();
		}
		AddMenuItem( 10000, "" );
		AddMenuItem( MSG_CHANGE_COL_FONT, "Change Column Font" );
		AddMenuItem( MSG_CHANGE_COL_BACKCOLOR, "Change Column Back Color" );
	}
	else if ( section == UG_GRID )
	{
		AddMenuItem( MSG_CHANGE_FONT, "Change Font" );
		AddMenuItem( MSG_CHANGE_BACKCOLOR, "Change Back Color" );
		AddMenuItem( MSG_RESET_SELECTED, "Reset cells" );
	}

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
DWORD CUGExcel::OnGetContextHelpID( int col, long row, int section )
{
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(section);

	col = GetColTranslation( col );

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
int CUGExcel::OnHint(int col,long row,int section,CString *string)
{
	UNREFERENCED_PARAMETER(section);

	col = GetColTranslation( col );
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
int CUGExcel::OnVScrollHint(long row,CString *string)
{
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(string);
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
int CUGExcel::OnHScrollHint(int col,CString *string)
{
	UNREFERENCED_PARAMETER(string);
	col = GetColTranslation( col );

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
DROPEFFECT CUGExcel::OnDragEnter(COleDataObject* pDataObject)
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
DROPEFFECT CUGExcel::OnDragOver(COleDataObject* pDataObject,int col,long row)
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
DROPEFFECT CUGExcel::OnDragDrop(COleDataObject* pDataObject,int col,long row)
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
void CUGExcel::OnScreenDCSetup(CDC *dc,int section)
{
	UNREFERENCED_PARAMETER(dc);
	UNREFERENCED_PARAMETER(section);
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
int CUGExcel::OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags)
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
void CUGExcel::OnTabSelected(int ID)
{
	UNREFERENCED_PARAMETER(ID);
}

/////////////////////////////////////////////////////////////////////////////
//	OnAdjustComponentSizes
//		Called when the grid components are baing arranged.
//	Params:
//		grid, topHdg, sideHdg, cnrBtn, vScroll, hScroll, 
//		tabs	- sizes and location of each of the grid components
//	Return:
//		<none>
void CUGExcel::OnAdjustComponentSizes(RECT *grid,RECT *topHdg,RECT *sideHdg,
		RECT *cnrBtn,RECT *vScroll,RECT *hScroll,RECT *tabs)
{
	UNREFERENCED_PARAMETER(grid);
	UNREFERENCED_PARAMETER(topHdg);
	UNREFERENCED_PARAMETER(sideHdg);
	UNREFERENCED_PARAMETER(cnrBtn);
	UNREFERENCED_PARAMETER(vScroll);
	UNREFERENCED_PARAMETER(hScroll);
	UNREFERENCED_PARAMETER(tabs);
} 

/////////////////////////////////////////////////////////////////////////////
//	OnDrawFocusRect
//		Called when the focus rect needs to be painted.
//	Params:
//		dc		- pointer to the current CDC object
//		rect	- rect of the cell that requires the focus rect
//	Return:
//		<none>
void CUGExcel::OnDrawFocusRect(CDC *dc,RECT *rect)
{
	BOOL innerRectOnly = FALSE;
	BOOL hideTop = FALSE;
	BOOL hideLeft = FALSE;
	CPen pen, wPen;
	int dcID = dc->SaveDC();

	//find the rect to draw - may be a range of cells
	//if multi-select is on
	if ( m_GI->m_multiSelectFlag&3 )
	{
		if(m_GI->m_multiSelect->GetNumberBlocks() <= 2)
		{
			int startCol,endCol;
			long startRow,endRow;
			m_GI->m_multiSelect->GetCurrentBlock(&startCol,&startRow,&endCol,&endRow);

			if( startRow < m_GI->m_topRow && endRow < m_GI->m_topRow )
			{
				if ( m_GI->m_numLockRows > 0 && startRow < m_GI->m_numLockRows  )
				{
					if ( endRow < m_GI->m_topRow && endRow != startRow )
						return;
				}
				else
					return;
			}

			if( startRow > m_GI->m_bottomRow && endRow > m_GI->m_bottomRow )
				return;

			if( startCol < m_GI->m_leftCol && endCol < m_GI->m_leftCol )
			{
				if ( m_GI->m_numLockCols > 0 && startCol < m_GI->m_numLockCols )
				{
					if ( endCol < m_GI->m_leftCol && startCol != endCol )
						return;
				}
				else
					return;
			}

			if( startCol > m_GI->m_rightCol && endCol > m_GI->m_rightCol )
				return;
			
			if(startCol != endCol || startRow != endRow)
				GetRangeRect(startCol,startRow,endCol,endRow,rect);

			if(startCol >= m_GI->m_numLockCols && startCol < m_GI->m_leftCol)
				//hide the left
				hideLeft = TRUE;

			if(startRow >= m_GI->m_numLockRows && startRow < m_GI->m_topRow)
				//hide the top
				hideTop = TRUE;

			if(rect->bottom <= rect->top)
				GetRangeRect(startCol,startRow,endCol,endRow,rect);

			if(rect->right <= rect->left)
				GetRangeRect(startCol,startRow,endCol,endRow,rect);
			
			//add draw hints for the grid so it will clear up the
			//focus rect next time
			m_CUGGrid->m_drawHint.AddHint(startCol-1,startRow-1,endCol+1,endRow+1);
		}
		else if(m_GI->m_multiSelect->GetNumberBlocks() > 2)
		{
			innerRectOnly = TRUE;
		}
		else
		{	//add draw hints for the grid so it will clear up the
			//focus rect next time
			m_CUGGrid->m_drawHint.AddHint(m_GI->m_currentCol-1,m_GI->m_currentRow-1,
				m_GI->m_currentCol+1,m_GI->m_currentRow+1);
		}
	}
	else
	{	//add draw hints for the grid so it will clear up the
		//focus rect next time
		m_CUGGrid->m_drawHint.AddHint(m_GI->m_currentCol-1,m_GI->m_currentRow-1,
			m_GI->m_currentCol+1,m_GI->m_currentRow+1);
	}

	int top = rect->top;
	int left = rect->left;

	//inner black rect
	dc->SelectObject(GetStockObject(BLACK_PEN));

	if(rect->top == 0)
		rect->top ++;

	if(rect->left == 0)
		rect->left ++;

	if(!hideTop)
	{
		dc->MoveTo(rect->left,rect->top);
		dc->LineTo(rect->right-1,rect->top);
	}
	else
	{
		dc->MoveTo(rect->right-1,rect->top);
	}

	dc->LineTo(rect->right-1,rect->bottom-1);
	dc->LineTo(rect->left,rect->bottom-1);

	if(!hideLeft)
		dc->LineTo(rect->left,rect->top-1);

	rect->top = top;
	rect->left = left;

	//inner white rect
	dc->SelectObject(GetStockObject(WHITE_PEN));

	if(rect->top == 0)
		rect->top ++;

	if(rect->left == 0)
		rect->left ++;

	if(!hideTop)
	{
		dc->MoveTo(rect->left+1,rect->top+1);
		dc->LineTo(rect->right-2,rect->top+1);
	}
	else
	{
		dc->MoveTo(rect->right-2,rect->top+1);
	}

	dc->LineTo(rect->right-2,rect->bottom-2);
	dc->LineTo(rect->left+1,rect->bottom-2);

	if(!hideLeft)
		dc->LineTo(rect->left+1,rect->top);

	rect->top = top;
	rect->left = left;

	//draw the rest if innerRectOnly is false
	if(!innerRectOnly)
	{
		dc->SelectObject(GetStockObject(BLACK_PEN));

		//outer rect
		if(rect->top == 0)
			rect->top +=2;

		if(rect->left == 0)
			rect->left +=2;

		if(hideLeft)
			rect->left++;

		if(!hideTop)
		{
			dc->MoveTo(rect->left-2,rect->top-2);
			dc->LineTo(rect->right+1,rect->top-2);			
		}
		else
		{
			rect->top++;
			dc->MoveTo(rect->right+1,rect->top-2);
		}
		
		dc->LineTo(rect->right+1,rect->bottom+1);
		dc->LineTo(rect->left-2,rect->bottom+1);
		
		if(!hideLeft)
			dc->LineTo(rect->left-2,rect->top -3);

		rect->top = top;
		rect->left = left;

		//bottom right square
		dc->MoveTo(rect->right-2,rect->bottom-2);
		dc->LineTo(rect->right,rect->bottom-2);
		dc->MoveTo(rect->right+2,rect->bottom-2);
		dc->LineTo(rect->right+2,rect->bottom+1);
		dc->MoveTo(rect->right+2,rect->bottom+1);
		dc->LineTo(rect->right+2,rect->bottom+2);
		dc->LineTo(rect->right,rect->bottom+2);
		dc->MoveTo(rect->right-2,rect->bottom+2);
		dc->LineTo(rect->right,rect->bottom+2);

		wPen.CreatePen(PS_SOLID,1,RGB(255,255,255));
		dc->SelectObject(wPen);
		dc->MoveTo(rect->right+3,rect->bottom-3);
		dc->LineTo(rect->right-3,rect->bottom-3);
		dc->LineTo(rect->right-3,rect->bottom+3);

		pen.CreatePen(PS_SOLID,1,RGB(120,120,120));
		dc->SelectObject(pen);

		//dark gray middle rect
		if(rect->top >0 && !hideTop)
		{
			dc->MoveTo(rect->left-2,rect->top-1);
			dc->LineTo(rect->right+2,rect->top-1);
		}
		else
			rect->top +=2;

		dc->MoveTo(rect->right,rect->top-1);
		dc->LineTo(rect->right,rect->bottom+3);

		if(rect->left >0 && !hideLeft)
		{
			dc->MoveTo(rect->left-1,rect->bottom+1);
			dc->LineTo(rect->left-1,rect->top-2);
		}
		else
			rect->left +=3;

		dc->MoveTo(rect->right+2,rect->bottom);
		dc->LineTo(rect->left-3,rect->bottom);

	}

	rect->top = top;
	rect->left = left;

	dc->RestoreDC(dcID);
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
COLORREF CUGExcel::OnGetDefBackColor(int section)
{
	UNREFERENCED_PARAMETER(section);
	//return RGB(255,255,255);
	return GetSysColor( COLOR_APPWORKSPACE );
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
void CUGExcel::OnSetFocus(int section)
{
	UNREFERENCED_PARAMETER(section);
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
void CUGExcel::OnKillFocus(int section)
{
	UNREFERENCED_PARAMETER(section);
}

/////////////////////////////////////////////////////////////////////////////
//	OnColSwapStart
//		Called to inform the grid that the col swap was started on given col.
//	Params:
//		col - identifies the column
//	Return:
//		TRUE - to allow for the swap to take place
//		FALSE - to disallow the swap
BOOL CUGExcel::OnColSwapStart(int col)
{
	col = GetColTranslation( col );

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
BOOL CUGExcel::OnCanColSwap(int fromCol,int toCol)
{
	fromCol = GetColTranslation( fromCol );
	toCol = GetColTranslation( toCol );

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnTrackingWindowMoved
//		Called to notify the grid that the tracking window was moved
//	Params:
//		origRect	- from
//		newRect		- to location and size of the track window
//	Return:
//		<none>
void CUGExcel::OnTrackingWindowMoved(RECT *origRect,RECT *newRect)
{
	UNREFERENCED_PARAMETER(origRect);
	UNREFERENCED_PARAMETER(newRect);
}

/////////////////////////////////////////////////////////////////////////////
//	CreateFont
//		Function is used to create new font object and add it to the link
//		list of fonts in use
CFont* CUGExcel::CreateFont( int nHeight, int nWidth, int nEscapement, int nOrientation, int nWeight, BYTE bItalic, BYTE bUnderline, BYTE cStrikeOut, BYTE nCharSet, BYTE nOutPrecision, BYTE nClipPrecision, BYTE nQuality, BYTE nPitchAndFamily, LPCTSTR lpszFacename )
{
	_tagFonts *pFont;
	pFont = m_fontsList;

	if ( pFont == NULL )
	{	// the list is empty, create new font object based on the information provided
		pFont = new _tagFonts;
		m_fontsList = pFont;
		pFont->font.CreateFont( nHeight, nWidth, nEscapement, nOrientation, nWeight, 
								bItalic, bUnderline, cStrikeOut, nCharSet, nOutPrecision, 
								nClipPrecision, nQuality, nPitchAndFamily, lpszFacename );

		return &pFont->font;
	}

	// create a log font object from the information provided and pass it to
	// the CreateFontIndirect function, which will perform all of the necessary
	// comparisons.
	CFont tempNewFont;
	LOGFONT newLogFont;

	tempNewFont.CreateFont( nHeight, nWidth, nEscapement, nOrientation, nWeight, 
							bItalic, bUnderline, cStrikeOut, nCharSet, nOutPrecision, 
							nClipPrecision, nQuality, nPitchAndFamily, lpszFacename );
	tempNewFont.GetLogFont( &newLogFont );

	return CreateFontIndirect( newLogFont );
}

/////////////////////////////////////////////////////////////////////////////
//	CreateFontIndirect
//		Function is used to add new fonts to the font's link list, but
//		it will also check if an object is already found in the list
//		that matches the new font.
CFont* CUGExcel::CreateFontIndirect( LOGFONT newLogFont )
{
	_tagFonts *pFont;
	pFont = m_fontsList;

	if ( pFont == NULL )
	{
		pFont = new _tagFonts;
		m_fontsList = pFont;
		pFont->font.CreateFontIndirect( &newLogFont );
	}

	LOGFONT tempLogFont;

	while ( pFont != NULL )
	{
		pFont->font.GetLogFont( &tempLogFont );
		// compare two logical font objects
		if ( newLogFont.lfWidth == tempLogFont.lfWidth &&
			 newLogFont.lfWeight == tempLogFont.lfWeight &&
			 newLogFont.lfHeight == tempLogFont.lfHeight &&
			 newLogFont.lfItalic == tempLogFont.lfItalic &&
			 newLogFont.lfCharSet == tempLogFont.lfCharSet &&
			 newLogFont.lfQuality == tempLogFont.lfQuality &&
			 newLogFont.lfUnderline == tempLogFont.lfUnderline &&
			 newLogFont.lfStrikeOut == tempLogFont.lfStrikeOut &&
			 newLogFont.lfEscapement == tempLogFont.lfEscapement &&
			 newLogFont.lfOrientation == tempLogFont.lfOrientation &&
			 newLogFont.lfOutPrecision == tempLogFont.lfOutPrecision &&
			 newLogFont.lfClipPrecision == tempLogFont.lfClipPrecision &&
			 newLogFont.lfPitchAndFamily == tempLogFont.lfPitchAndFamily &&
 			 strcmp( newLogFont.lfFaceName, tempLogFont.lfFaceName ) == 0 )
		{
			break;
		}
		else if ( pFont->next == NULL )
		{
			// add new font 
			pFont->next = new _tagFonts;
			pFont = pFont->next;
			pFont->font.CreateFontIndirect( &newLogFont );
			break;
		}
		pFont = pFont->next;
	}

	// return pointer to the foint font object
	return &pFont->font;
}

/////////////////////////////////////////////////////////////////////////////
//	ShowFontDlg
//		Function is used to properly preset and display the FontDialog
//		which user can use to change font.
//	Params
//		cell - object for which to preset the font dialog
//		selectedLogFont
//		textColor
//	Returns
//		TRUE/FALSE identifying 
BOOL CUGExcel::ShowFontDlg( CUGCell &cell, LOGFONT &selectedLogFont, COLORREF &textColor )
{
	BOOL retVal = FALSE;
	LOGFONT tempLogFont;
	CFont *font = cell.GetFont();
	CFontDialog *fontDlg;

	if ( font != NULL )
	{
		font->GetLogFont( &tempLogFont );
	}

	fontDlg = new CFontDialog( &tempLogFont );
	fontDlg->m_cf.rgbColors = textColor;

	if ( fontDlg->DoModal() == IDOK )
	{
		fontDlg->GetCurrentFont( &selectedLogFont );
		textColor = fontDlg->GetColor();

		retVal = TRUE;
	}

	delete fontDlg;
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////
//	BlendColors
//		Function is used to provide Excel 2000 look of multiselected cells
//		it blends the two colors passed in according to the blend rate specified.
//	Params:
//		color1, color2 - the two colors to combine
//		rate	- the percentage rate of the blend
//	Returns:
//		COLORREF - a new color that is a result of the blending process
COLORREF CUGExcel::BlendColors( COLORREF color1, COLORREF color2, double rate )
{
	COLORREF smColor, grColor;
	int rVal, gVal, bVal;

	smColor = color1<color2?color1:color2;
	grColor = color1>color2?color1:color2;

	rVal = (int)((GetRValue( grColor ) - GetRValue( smColor )) * rate ) + GetRValue( smColor );
	gVal = (int)((GetGValue( grColor ) - GetGValue( smColor )) * rate ) + GetGValue( smColor );
	bVal = (int)((GetBValue( grColor ) - GetBValue( smColor )) * rate ) + GetBValue( smColor );

	return RGB( rVal , gVal, bVal );
}

/////////////////////////////////////////////////////////////////////////////
//	LocateCol
//		This function completes functionality of the GetColTranslation, it 
//		will return current location of a column.  This is accomplished by
//		looping through Column translation information looking for the column
//		in question to be returned.
//
//	Params:
//		col	- original column location to look for
//	Return:
//		int	- current on screen column location
//			- if function fails it will return zero
int CUGExcel::LocateCol( int col )
{
	// check if the column is within the range
	if ( col < 0 || col >= GetNumberCols())
		return 0;

	// check if the col was moved in the first place.
	if ( GetColTranslation( col ) == col )
		return col;

	for ( int xIndex = 0; xIndex < GetNumberCols(); xIndex ++ )
	{
		if ( GetColTranslation( xIndex ) == col )
		{
			return xIndex;
		}
	}

	// the column in question was not found, probably deleted.
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// HideCol
//		This function will hide specified column, this process is done by removing
//		that column from the display and un linking its datasourse column from any
//		display col.
void CUGExcel::HideCol(int col)
{
	EnableUpdate( FALSE );

	int maxCol = GetNumberCols() - 1;

	// add the column number user want's hidden into the link list
	// Original column location will be storred.
	_tagHiddenCols *pColItem;
	pColItem = m_hiddenColsList;

	if ( pColItem == NULL )
	{
		pColItem = new _tagHiddenCols;
		pColItem->colNumber = col;
		m_hiddenColsList = pColItem;
	}
	else
	{
		while ( pColItem->next != NULL )
			pColItem = pColItem->next;

		pColItem->next = new _tagHiddenCols;
		pColItem = pColItem->next;
		pColItem->colNumber = col;
	}

	for ( int nIndex = LocateCol( col ); nIndex < maxCol; nIndex ++ )
	{
		//SetColTranslation( nIndex, GetColTranslation( nIndex + 1 ));
		MoveColPosition( nIndex + 1, nIndex, TRUE );
	}

	SetNumberCols( maxCol );

	// redraw the grid view
	EnableUpdate( TRUE );
	AdjustComponentSizes();
}

/////////////////////////////////////////////////////////////////////////////
// UnHideCol
//		This function is used to reverse effects of the HideCol function
//		it will loop through all 'hidden' cols to look for one that matches
//		origColPos specified, it will the place this col where it belongs.
void CUGExcel::UnHideCol(int origColPos, int newWidth)
{
	BOOL colFound = FALSE;

	EnableUpdate( FALSE );

	if ( m_hiddenColsList == NULL )
		// the list empty
		return;

	// check if the specified column has been hidden and
	// if item found, remove it from the link list
	_tagHiddenCols *pColItem, *pFoundItem = NULL;
	pColItem = m_hiddenColsList;

	while ( pColItem != NULL && colFound == FALSE )
	{
		if ( pColItem->colNumber == origColPos )
		{
			colFound = TRUE;

			if ( pFoundItem == NULL )
				// item was found in the head of the list
				m_hiddenColsList = m_hiddenColsList->next;
			else
				// represents the previous item in the list
				pFoundItem->next = pColItem->next;

			// when item is found than the pColItem is a pointer to 
			// item in the list to delete
			delete pColItem;
			pColItem = NULL;
		}
		else
		{
			pFoundItem = pColItem;
			pColItem = pColItem->next;
		}
	}
	// force restart of hidden col enumerator
	m_bForceEnumRestart = TRUE;

	if ( colFound == FALSE )
	{	// specified column was not hidden, there is no need to continue
		return;
	}

	// increment number of columns in the grid
	SetNumberCols( GetNumberCols() + 1 );

	// move all columns located after the column we are about to show
	for ( int nIndex = GetNumberCols() - 1; nIndex >= origColPos; nIndex -- )
	{
		MoveColPosition( nIndex, nIndex + 1, FALSE );
		//SetColTranslation( origColPos, origColPos );
	}

	SetColTranslation( origColPos, origColPos );

	if ( newWidth < 0 )
		newWidth = m_GI->m_defColWidth;

	SetColWidth( origColPos, newWidth );

	// redraw the grid view
	EnableUpdate( TRUE );
	AdjustComponentSizes();
}

/////////////////////////////////////////////////////////////////////////////
// EnumNextHidden
int CUGExcel::EnumHiddenCols()
{
	if ( m_bForceEnumRestart == TRUE )
		m_pCurEnumItem = m_hiddenColsList;

	if ( m_pCurEnumItem == NULL )
	{	// reached end of the list, or the list is empty
		m_bForceEnumRestart = TRUE;
		return -1;
	}

	int enumCol = m_pCurEnumItem->colNumber;
	m_pCurEnumItem = m_pCurEnumItem->next;
	m_bForceEnumRestart = FALSE;

	return enumCol;
}

void CUGExcel::ResetSelected()
{
	int startCol,endCol;
	long startRow,endRow;
	m_GI->m_multiSelect->GetCurrentBlock(&startCol,&startRow,&endCol,&endRow);
	ResetCells(startRow, endRow, startCol, endCol);
}