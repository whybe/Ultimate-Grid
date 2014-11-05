///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Skeleton Class for a Derived CFindGrid v97
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "FindGrid.h"

#include <afxdisp.h>
#include <time.h>
#include <locale.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CFindGrid,CUGCtrl)
	//{{AFX_MSG_MAP(CFindGrid)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
CFindGrid::CFindGrid( )
{
	UGXPThemes::UseThemes(true);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
CFindGrid::~CFindGrid( )
{
	UGXPThemes::CleanUp();
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void CFindGrid::OnSetup( ) 
{
	CDC * pDC;
	CUGCell cell;
	int iHeight;
	int i, j;
	
	pDC = GetDC( );
	
	iHeight = -MulDiv( 8, GetDeviceCaps( pDC->m_hDC, LOGPIXELSY), 72 );
	m_font.CreateFont( iHeight, 0, 0, 0, 400, 0, 0, 0, 0, 0, 0, 0, 0, _T( "MS Sans Serif" ) );
	
	ReleaseDC( pDC );

	SetDefFont( &m_font );
		
	GetGridDefault( &cell );
	cell.SetAlignment( UG_ALIGNCENTER | UG_ALIGNVCENTER );
	SetGridDefault( &cell );

	SetNumberCols( 10 );
	SetNumberRows( 50 );

	m_iArrowIndex = AddCellType( &m_sortArrow );

	SetCurrentCellMode( 2 );

	UseHints( TRUE );

	SetSH_Width( 0 );
	SetUniformRowHeight( TRUE );
	SetRowHeight( 0, 30 );
	
	srand( ( unsigned )time( NULL ) );
	
	InitMenu();
	
	LPTSTR strTopHeadings[ 10 ] = { _T( "Numbers" ), _T( "Numbers" ), _T( "Numbers" ), _T( "Last Names" ), _T( "First Names" ),
		_T( "Reds" ), _T( "Greens" ), _T( "Blues" ), _T( "Length" ), _T( "Dates" ) };
	
	GetCell( 0, -1, &cell );
	for( i = 0 ; i < GetNumberCols() ; i++ )
	{
		cell.SetText( strTopHeadings[ i ] );
		SetCell( i, -1, &cell );
	}

	GetCell( 0, 0, &cell );
	for( i = 0 ; i < 3 ; i++ )
	{
		for( j = 0 ; j < GetNumberRows() ; j++ )
		{
			cell.SetNumberDecimals( 0 );
			cell.SetNumber( rand() % 20 + 1 );
			SetCell( i, j, &cell );
		}
	}

	LPTSTR strLastNames[ 10 ] = { _T( "Atwal" ), _T( "Cunningham" ), _T( "Marchand" ), _T( "Zajac" ), _T( "Wadi" ),
		_T( "Scott" ), _T( "Ind" ), _T( "Hong" ), _T( "Zenkovitch" ), _T( "Deveaux" ) };
	
	GetCell( 3, 0, &cell );
	for( j = 0 ; j < GetNumberRows() ; j++ )
	{
		cell.SetText( strLastNames[ rand() % 10 ] );
		SetCell( 3, j, &cell );
	}

	LPTSTR strFirstNames[ 20 ] = { _T( "Randy" ), _T( "David" ), _T( "Troy" ), _T( "Peter" ), _T( "Ghazi" ),
		_T( "Jeff" ), _T( "Wayne" ), _T( "Julie" ), _T( "Donna" ), _T( "Katherine" ), _T( "Hsu" ), _T( "Lily" ),
		_T( "Sumita" ), _T( "Francois" ), _T( "Karl" ), _T( "Yuri" ), _T( "Eli" ), _T( "Guiseppe" ), 
		_T( "Vijay" ), _T( "Ingrid" ) };

	GetCell( 4, 0, &cell );
	for( j = 0 ; j < GetNumberRows() ; j++ )
	{
		cell.SetText( strFirstNames[ rand() % 20 ] );
		SetCell( 4, j, &cell );
	}

	GetCell( 5, 0, &cell );
	for( j = 0 ; j < GetNumberRows() ; j++ )
	{
		cell.UseThemes(false);
		cell.SetBackColor( RGB( rand() % 255 + 1, 0, 0 ) );
		SetCell( 5, j, &cell );
	}

	GetCell( 6, 0, &cell );
	for( j = 0 ; j < GetNumberRows() ; j++ )
	{
		cell.UseThemes(false);
		cell.SetBackColor( RGB( 0, rand() % 255 + 1, 0 ) );
		SetCell( 6, j, &cell );
	}

	GetCell( 7, 0, &cell );
	for( j = 0 ; j < GetNumberRows() ; j++ )
	{
		cell.UseThemes(false);
		cell.SetBackColor( RGB( 0, 0, rand() % 255 + 1 ) );
		SetCell( 7, j, &cell );
	}

	GetCell( 8, 0, &cell );
	for( j = 0 ; j < GetNumberRows() ; j++ )
	{
		CString strTemp( 'a', rand()% 10 + 1 );
		cell.SetText( strTemp );
		cell.SetAlignment( UG_ALIGNLEFT );
		SetCell( 8, j, &cell );
	}

	GetCell( 9, 0, &cell );

	for( j = 0 ; j < GetNumberRows() ; j++ )
	{
		CString strTemp;
		int iDay = 1;
		int iMonth = rand() % 12 + 1;
		int iYear = 1900 + rand() % 99 + 1;
				
		switch( iMonth )
		{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
			{
				iDay = rand() % 31 + 1;
				break;
			}
			case 4:
			case 6:
			case 9:
			case 11:
			{
				iDay = rand() % 30 + 1;
				break;
			}
			case 2:
			{
				if( iYear % 4 )
					iDay = rand() % 29 + 1;
				else
					iDay = rand() % 28 + 1;
			}
		}

		strTemp.Format( "%d/%d/%d", iMonth, iDay, iYear );
		cell.SetText( strTemp );
		cell.SetAlignment( UG_ALIGNRIGHT );
		SetCell( 9, j, &cell );
	}

	QuickSetCellType( 0, -1, m_iArrowIndex );
	SortBy( 0, UG_SORT_ASCENDING );

	m_iSortCol = 0;
	m_bSortedAscending = TRUE;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void CFindGrid::OnTH_LClicked( int iCol, long lRow, int iUpdn, RECT* pRect, POINT* pPoint, BOOL bProcessed )
{
	UNREFERENCED_PARAMETER(lRow);
	UNREFERENCED_PARAMETER(pRect);
	UNREFERENCED_PARAMETER(pPoint);
	UNREFERENCED_PARAMETER(bProcessed);

	if( iUpdn == 0)
		return;

	QuickSetCellType( m_iSortCol, -1, 0 );

	if( iCol == m_iSortCol )
	{
		if( m_bSortedAscending )
			m_bSortedAscending = FALSE;
		else
			m_bSortedAscending = TRUE;
	}
	else
	{
		m_iSortCol = iCol;
		m_bSortedAscending = TRUE;
	}

	if( m_bSortedAscending )
	{
		SortBy( iCol, UG_SORT_ASCENDING );
		QuickSetCellType( m_iSortCol, -1, m_iArrowIndex );
		QuickSetCellTypeEx( m_iSortCol, -1, UGCT_SORTARROWDOWN );

//		((CFindAndSortDemo*)GetParent())->Trace( _T( "Sorted column %d ascending" ), iCol );
	}
	else
	{
		SortBy( iCol, UG_SORT_DESCENDING );
		QuickSetCellType( m_iSortCol, -1, m_iArrowIndex );
		QuickSetCellTypeEx( m_iSortCol, -1, UGCT_SORTARROWUP );
//		Trace( _T( "Sorted column %d descending" ), iCol );
	}
	
	RedrawAll();
}
	
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void CFindGrid::OnGetCell( int iCol, long lRow, CUGCell* pCell )
{
	if( lRow >= 0 && iCol >= 0 )
	{
		if( !pCell->IsPropertySet( UGCELL_BACKCOLOR_SET ) && lRow % 2 )
			pCell->SetBackColor( RGB( 255, 255, 192 ) );
	}
}	

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void CFindGrid::OnMenuCommand( int iCol, long lRow, int iSection, int iItem )
{
	UNREFERENCED_PARAMETER(iCol);
	UNREFERENCED_PARAMETER(lRow);
	UNREFERENCED_PARAMETER(iSection);
	// init. local variables
	CMenu* pMenu;
	pMenu = GetPopupMenu();
	
	switch( iItem )
	{
		case 1000:
		{
			int iCols[ 3 ];

			iCols[ 0 ] = 0;
			iCols[ 1 ] = 1;
			iCols[ 2 ] = 2;
			
			SortBy( iCols, 3, UG_SORT_ASCENDING );
			RedrawAll();
//			Trace( _T( "Sorted all three of the number columns." ) );
			
			break;
		}
		case 1001:
		{
			int iCols[ 2 ];

			iCols[ 0 ] = 4;
			iCols[ 1 ] = 3;
						
			SortBy( iCols, 2, UG_SORT_ASCENDING );
			RedrawAll();
//			Trace( _T( "Sorted the person's names, last name then first name." ) );

			break;
		}
		case 2000:
		{
			FindDialog();
//			Trace( _T( "Displayed the grid's Find Dialog." ) );
			break;
		}
		case 2001:
		{
			ReplaceDialog();
//			Trace( _T( "Displayed the grid's Replace Dialog." ) );
			break;
		}
		case 2002:
		{
			if( pMenu->CheckMenuItem( 2002, MF_CHECKED ) )
			{
				FindInAllCols( FALSE );
				SetBallisticDelay( 0 );
//				Trace( _T( "Turned off the Find/Replace Dialog's ability to search in all columns of the grid." ) );
				pMenu->CheckMenuItem( 2002, MF_UNCHECKED );
			}
			else
			{
				FindInAllCols( TRUE );
//				Trace( _T( "Turned on the Find/Replace Dialog's ability to search in all columns of the grid." ) );
			}
			break;
		}
		case 3000:
		{
			int iFindCol = GetCurrentCol();
			long lFindRow = GetCurrentRow();
			CString strFind;
			strFind.Format( _T( "7" ) );
			FindNext( &strFind, &iFindCol, &lFindRow, UG_FIND_PARTIAL | UG_FIND_ALLCOLUMNS );
			GotoCell( iFindCol, lFindRow );	
//			Trace( _T( "Found the first instance of '7', down from this position." ) );
					
			break;
		}
		case 3001:
		{
			int iFindCol = GetCurrentCol();
			long lFindRow = GetCurrentRow();
			CString strFind;
			strFind.Format( _T( "7" ) );
			FindNext( &strFind, &iFindCol, &lFindRow, UG_FIND_PARTIAL | UG_FIND_ALLCOLUMNS | UG_FIND_UP );
			GotoCell( iFindCol, lFindRow );	
//			Trace( _T( "Found the first instance of '7', up from this position." ) );
			break;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int CFindGrid::OnMenuStart( int iCol, long lRow, int iSection )
{
	UNREFERENCED_PARAMETER(iCol);
	UNREFERENCED_PARAMETER(lRow);

	if( iSection == UG_GRID )
	{
//		Trace( _T( "Displayed the grid's internal pop-up menu." ) );	
		return TRUE;
	}
	else
		return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int CFindGrid::OnHint( int iCol, long lRow, int iSection, CString* pString )
{
	UNREFERENCED_PARAMETER(iCol);
	UNREFERENCED_PARAMETER(lRow);
	UNREFERENCED_PARAMETER(iSection);

	pString->Format( _T( "Right-click on grid for more options..." ) );
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int CFindGrid::OnSortEvaluate( CUGCell* pCell1, CUGCell* pCell2, int iFlags )
{
	if( iFlags & UG_SORT_DESCENDING )
	{
		CUGCell *ptr = pCell1;
		pCell1 = pCell2;
		pCell2 = ptr;
	}

	COLORREF cr1 = pCell1->GetBackColor();
	COLORREF cr2 = pCell2->GetBackColor();
	COleDateTime date1, date2;
	CString str1, str2;
	int iLen1, iLen2;
	int retVal = 0;

	BYTE color1, color2;

	switch ( m_iSortCol )
	{
	case 5:
		color1 = GetRValue( cr1 );
		color2 = GetRValue( cr2 );

		if( color1 > color2 )
			retVal = -1;
		if( color1 < color2 )
			retVal = 1;

		break;
	case 6:
		color1 = GetGValue( cr1 );
		color2 = GetGValue( cr2 );

		if( color1 > color2 )
			retVal = -1;
		if( color1 < color2 )
			retVal = 1;
	
		break;

	case 7:
		color1 = GetBValue( cr1 );
		color2 = GetBValue( cr2 );

		if( color1 > color2 )
			retVal = -1;
		if( color1 < color2 )
			retVal = 1;
	
		break;

	case 8:
		str1 = pCell1->GetText();
		str2 = pCell2->GetText();
		iLen1 = str1.GetLength();
		iLen2 = str2.GetLength();

		if( iLen1 < iLen2 )
			retVal = -1;
		if( iLen1 > iLen2 )
			retVal = 1;

		break;

	case 9:
		date1.ParseDateTime( pCell1->GetText(), VAR_DATEVALUEONLY );
		date2.ParseDateTime( pCell2->GetText(), VAR_DATEVALUEONLY );

		// If a date is invalid, move it to the bottom, by always making it >
		// ( the valid code is 0 )
		if (date1.GetStatus())
			return 1;
		if (date2.GetStatus())
			return -1;
		
		if( date1 < date2 )
			retVal = -1;
		if( date1 > date2 )
			retVal = 1;

		break;

	default:
		if( CString(pCell1->GetText()) == "" )
			return 1;
		else if( CString(pCell2->GetText()) == "" )
			return -1;

		switch( pCell1->GetDataType() )
		{
			case UGCELLDATA_NUMBER:
			case UGCELLDATA_BOOL:
			case UGCELLDATA_CURRENCY:
				if( pCell1->GetNumber() < pCell2->GetNumber())
					retVal = -1;
				if( pCell1->GetNumber() > pCell2->GetNumber())
					retVal = 1;

				break;

			default:
				retVal = _tcscmp( pCell1->GetText( ), pCell2->GetText());
		}
	}

	return retVal;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void CFindGrid::OnCellChange(int oldcol,int newcol,long oldrow,long newrow)
{
	UNREFERENCED_PARAMETER(oldcol);
	UNREFERENCED_PARAMETER(oldrow);

	if( m_findDialogRunning )
	{
		CRect cellRect, dlgRect, tempRect;
		
		m_findReplaceDialog->GetWindowRect( dlgRect );
		GetCellRect( newcol, newrow, cellRect );
		ClientToScreen( cellRect );

		CPoint point1, point2;
		
		point1.x = cellRect.left;
		point1.y = cellRect.top;

		point2.x = cellRect.right;
		point2.y = cellRect.bottom;

		if( dlgRect.PtInRect( point1 ) || dlgRect.PtInRect( point2 ) )
		{
			tempRect.left = dlgRect.left;
			tempRect.right = dlgRect.right;
			tempRect.bottom = cellRect.top - 5;
			tempRect.top = cellRect.top - 5 - dlgRect.Height();
			
			m_findReplaceDialog->MoveWindow( tempRect );
			RedrawAll();
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void CFindGrid::InitMenu()
{
	CMenu submenu;
	CMenu * menu = GetPopupMenu();
	
	EnableMenu(TRUE);
	
	AddMenuItem( 1000, _T( "Sort on all Number Columns" ) );
	AddMenuItem( 1001, _T( "Sort Names, First then Last" ) );
	
	menu->AppendMenu( MF_SEPARATOR, 0, _T( "" ) );
	
	AddMenuItem( 2000, _T( "Find Dialog" ) );
	AddMenuItem( 2001, _T( "ReplaceDialog" ) );
	AddMenuItem( 2002, _T( "Find in All Columns" ) );

	menu->AppendMenu( MF_SEPARATOR, 0, _T( "" ) );

	AddMenuItem( 3000, _T( "Find '7' Down" ) );
	AddMenuItem( 3001, _T( "Find '7' Up" ) );
}
