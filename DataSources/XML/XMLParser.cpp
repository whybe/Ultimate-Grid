// XMLParser.cpp: implementation of the CXMLParser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XMLParser.h"

#include "tchar.h"
#include "UGStrOp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// Construction/Destruction
/////////////////////////////////////////////////////////////////////////////

CXMLParser::CXMLParser()
{
	m_defFontName = _T("Arial");
	m_defFontSize = 10;
	m_pAddedStyles = NULL;
	m_pGrid = NULL;
}

CXMLParser::~CXMLParser()
{
	// clean up possible styles allocated by the AddStyle function
	_tagAddedStyles *pStyle, *pTempStyle;
	pStyle = m_pAddedStyles;
	while ( pStyle != NULL )
	{
		pTempStyle = pStyle->next;
		delete pStyle;
		pStyle = pTempStyle;
	}	
}

/////////////////////////////////////////////////////////////////////////////
//	Load
//		This function is used to load a XML file and use its content
//		to setup the grid.  The grid will first be cleared of all
//		current settings and data, then it will be reallocated
//		using the information found in the XML file.
//	Parameters:
//		filePath	- full file name of the XML file to load
//		m_pGrid		- a pointer to the grid object to populate
//	Returns:
//		TRUE on success otherwise FALSE
int CXMLParser::Load( CString filePath )
{
	ASSERT( m_pGrid );
	ASSERT( filePath != _T(""));

	m_pGrid->ClearAllFonts();

	// let the COXParser load and parse the XML file,
	// this object will be used to extract all of the information
	// stored in the XML document.
	COXParser parser;
	parser.ParseFile( filePath );

	COXParserElement *root = parser.Root();
	COXParserElement *workbook = root->FindElement(_T("Workbook"));

	if ( workbook == NULL )
		// The WorkBook element was not found.
		return FALSE;

	int nWorkSheetCount = 0;
	// enumerate and setup all of the worksheets
	for ( int nIndex = 0; nIndex < workbook->NumObjects(); nIndex ++ )
	{
		COXParserObject *workSheet = workbook->Object( nIndex );

		if ( workSheet->GetType() != COXParserObject::ELEMENT )
			continue;

		if ( _tcscmp(((COXParserElement*) workSheet )->GetName(), _T("Worksheet")) == 0 )
		{
			CUGCell cell;
			COXAttribute *attr = NULL;
			// setup sheet information
			if ( nWorkSheetCount == 0 )
				m_pGrid->SetTabWidth( 200 );
			else
				m_pGrid->SetNumberSheets( nWorkSheetCount + 1 );

			nWorkSheetCount ++;

			// setup corresponding tab information
			attr = ((COXParserElement*) workSheet )->FindAttribute(_T("ss:Name"));
			m_pGrid->AddTab( attr->GetStringValue(), m_pGrid->GetNumberSheets());
			m_pGrid->SetSheetNumber( m_pGrid->GetNumberSheets() - 1 );

			// working with the Table subobject of the Worksheet
			COXParserElement *pTableElement = ((COXParserElement*) workSheet )->FindElement(_T("Table"));
			// before continuing make sure that the table information exists
			if ( pTableElement == NULL )
				continue;
			// if a table element exists, setup grid's defaults
			m_pGrid->SetSH_Width( 26 );
			m_pGrid->SetTH_Height( 17 );
			m_pGrid->SetDefColWidth( 64 );
			m_pGrid->SetDefRowHeight( 17 );
			// parse out and set defaults affecting entire grid
			m_pGrid->GetGridDefault( &cell );
			cell.SetFont( CreateFont( m_defFontName, m_defFontSize ));
			cell.SetAlignment( UG_ALIGNLEFT|UG_ALIGNBOTTOM );
			m_pGrid->SetGridDefault( &cell );
			// load the information contained within the table object
			LoadTableInfo( pTableElement );
		}
	}

	// enable painting for each sheet that was loaded
	for ( int nSheetNum = 0; nSheetNum < m_pGrid->GetNumberSheets(); nSheetNum ++ )
	{
		m_pGrid->SetSheetNumber( nSheetNum );
		m_pGrid->SetPaintMode( TRUE );
	}

	m_pGrid->SetSheetNumber( 0 );

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	LoadTableInfo
//		The LoadTableInfo function will retrieve information related
//		to a table, and make sure that column and row info is also loaded.
//	Parameters:
//		pTableElement
//		m_pGrid
//	Returns:
//		TRUE on success otherwise FALSE
int CXMLParser::LoadTableInfo( COXParserElement *pTableElement )
{
	// Excel stores number of columns and rows used as:
	// ss:ExpandedColumnCount	- number of columns
	// ss:ExpandedRowCount		- number or rows
	COXAttribute *attr = NULL;
	attr = pTableElement->FindAttribute(_T("ss:ExpandedColumnCount"));
	if ( attr != NULL )
		m_pGrid->SetNumberCols( _ttol( attr->GetStringValue()));

	attr = pTableElement->FindAttribute(_T("ss:ExpandedRowCount"));
	if ( attr != NULL )
		m_pGrid->SetNumberRows( _ttol( attr->GetStringValue()));

	// loop through all of the subobjects of the Table element
	// and populate the grid with appropriate data
	// - setup columns, attibutes supported:
	//		ss:Index	- index is one based
	//		ss:Span		- indicates howmany items in a row will be affected
	//		ss:Width	- is stored as a float, divide it by .75 to get pixels
	//		ss:StyleID	- stores which style should be applied
	//		- translation
	// - setup rows, attibutes supported:
	//		ss:Index	- index is one based
	//		ss:Height	- is stored as a float, divide it by .75 to get pixels
	//		- defaults will be left out because the UG does not
	//		  support row defaults.
	//		* for each row call LoadRowData to setup cells
	int nColIndex = 0;
	int nRowIndex = 0;
	for ( int nSubObjIndex = 0; nSubObjIndex < pTableElement->NumObjects(); nSubObjIndex ++ )
	{
		COXParserObject *tableSubObj = pTableElement->Object( nSubObjIndex );

		if ( tableSubObj->GetType() != COXParserObject::ELEMENT )
			// we are only interested in sub elements of the table
			continue;

		if ( _tcscmp( tableSubObj->GetText(), _T("Column")) == 0 )
		{
			LoadColInfo((COXParserElement*)tableSubObj, nColIndex );
		}
		else if ( _tcscmp( tableSubObj->GetText(), _T("Row")) == 0 )
		{
			LoadRowInfo((COXParserElement*)tableSubObj, nRowIndex );
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	LoadColInfo
//		The LoadColInfo function retrieves all of the information required
//		to setup grid's columns, this includes column defaults and sizes.
//
//		TODO: add support to load column translation information.
//		TODO: add support to properly load hidden columns
//
//	Parameters:
//		pColElement	- pointer to a COXParserEmelent object that
//					  needs to be parsed out.
//		m_pGrid		- pointer the grid control control
//		colNum		- column number currently worked on
//	Returns:
//		TRUE if successful otherwise FALSE.
int CXMLParser::LoadColInfo( COXParserElement *pColElement, int &nColIndex )
{
	// ss:Index	- index is one based
	COXAttribute *pColIndex = pColElement->FindAttribute(_T("ss:Index"));

	if ( pColIndex != NULL )
		nColIndex = _ttol( pColIndex->GetStringValue());
	else
		nColIndex ++;

	// ss:Span	- indicates howmany items in a row will be affected
	COXAttribute *pColSpan = pColElement->FindAttribute(_T("ss:Span"));
	int colSpan = 0;
	if ( pColSpan != NULL )
		colSpan = _ttol( pColSpan->GetStringValue());

	// ss:Width - is stored as a float, divide it by .75 to get pixels
	COXAttribute *pColWidth = pColElement->FindAttribute(_T("ss:Width"));

	// ss:StyleID - stores which style should be applied
	COXAttribute *pColStyle = pColElement->FindAttribute(_T("ss:StyleID"));
	// get a pointer to the styles collection
	COXParserElement *pStyles = FindStylesElement( pColElement );

	CUGCell cell;
	for ( int nSetIndex = 0; nSetIndex <= colSpan; nSetIndex ++ )
	{
		// set column's width
		if ( pColWidth != NULL )
			m_pGrid->SetColWidth( nColIndex + nSetIndex - 1, (int)( _tcstod( pColWidth->GetStringValue(), NULL ) / 0.75));

		// set colum default to match the style
		if ( pColStyle != NULL )
		{
			cell.ClearAll();
			m_pGrid->GetColDefault( nColIndex + nSetIndex - 1, &cell );
			PopulateCellFromStyle( pColStyle->GetStringValue(), pStyles, &cell );
			m_pGrid->SetColDefault( nColIndex + nSetIndex - 1, &cell );
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	LoadRowInfo
//		The LoadRowInfo funciton will retieve row index and height information,
//		and it will make sure that row's data is properly loaded.
//	Parameters:
//		pRowElement	- pointer to a COXParserEmelent object that
//					  needs to be parsed out.
//		m_pGrid		- pointer the grid control control
//		colNum		- column number currently worked on
//	Returns:
//		TRUE if successful otherwise FALSE.
int CXMLParser::LoadRowInfo( COXParserElement *pRowElement, int &nRowIndex )
{
	// ss:Index	- index is one based
	COXAttribute *pRowIndex = pRowElement->FindAttribute(_T("ss:Index"));
	
	if ( pRowIndex != NULL )
		nRowIndex = _ttol( pRowIndex->GetStringValue());
	else
		nRowIndex ++;

	// ss:Height - is stored as a float, divide it by .75 to get pixels
	COXAttribute *pRowHeight = pRowElement->FindAttribute(_T("ss:Height"));

	// set row's height
	if ( pRowHeight != NULL )
		m_pGrid->SetRowHeight( nRowIndex - 1, (int)( _tcstod( pRowHeight->GetStringValue(), NULL) / 0.75 ));

	COXParserElement *pStyles = FindStylesElement( pRowElement );
	// ss:StyleID - stores style that should be applied to blank cells
	COXAttribute *pRowStyle = pRowElement->FindAttribute(_T("ss:StyleID"));

	if ( pRowStyle != NULL )
	{	// loop through all of the cells within a row
		// if a default row style was specified.
		CUGCell defCell;
		for ( int nColIndex = 0; nColIndex < m_pGrid->GetNumberCols(); nColIndex ++ )
		{
			m_pGrid->GetCellIndirect( nColIndex, nRowIndex - 1, &defCell );
			PopulateCellFromStyle( pRowStyle->GetStringValue(), pStyles, &defCell );
			m_pGrid->SetCell( nColIndex, nRowIndex - 1, &defCell );
		}
	}

	// load row's data
	return LoadRowData( pRowElement, nRowIndex - 1 );
}

/////////////////////////////////////////////////////////////////////////////
//	LoadRowData
//		This function is called to populate cells in a given row.
//		
//	Parameters:
//		pRowElement	- pointer to a COXParserEmelent object that
//					  needs to be parsed out.
//		m_pGrid		- pointer the grid control control
//		rowNum		- row number currently worked on
//	Returns:
//		TRUE if successful otherwise FALSE.
int CXMLParser::LoadRowData( COXParserElement *pRowElement, long rowNum )
{
	CUGCell cell;
	int nCellIndex = 0;
	COXParserElement *pStyles = FindStylesElement( pRowElement );

	for ( int nSubObjIndex = 0; nSubObjIndex < pRowElement->NumObjects(); nSubObjIndex ++ )
	{
		COXParserObject *rowSubObj = pRowElement->Object( nSubObjIndex );

		if ( rowSubObj->GetType() != COXParserObject::ELEMENT )
			// we are only interested in sub elements of the row
			continue;

		// Cell object's attributes supported:
		// ss:Index			- column number a cell resides in
		// ss:MergeAcross	- join cells horizontally
		// ss:MergeDown		- join cells vertically
		// ss:StyleID		- cell's style

		// Data sub-object attributes suppoted:
		// ss:Type			- cells data type, can be:
		//					  "String"
		//					  "Number"
		//					  "DateTime" -> stored as 2002-12-12T00:00:00.000

		// ss:Index
		COXAttribute *pColIndex = ((COXParserElement*) rowSubObj )->FindAttribute(_T("ss:Index"));
		if ( pColIndex != NULL )
			nCellIndex = _ttol( pColIndex->GetStringValue());
		else
			nCellIndex ++;

		// Cell joining
		CSize joinRange(0,0);
		// ss:MergeAcross
		COXAttribute *pMergeAcross = ((COXParserElement*) rowSubObj )->FindAttribute(_T("ss:MergeAcross"));
		if ( pMergeAcross != NULL )
			joinRange.cx = _ttol( pMergeAcross->GetStringValue());
		// ss:MergeDown
		COXAttribute *pMergeDown = ((COXParserElement*) rowSubObj )->FindAttribute(_T("ss:MergeDown"));
		if ( pMergeDown != NULL )
			joinRange.cy = _ttol( pMergeDown->GetStringValue());

		// if necessary setup cell join information
		if ( joinRange != CSize(0,0))
		{
			// adjust which column cell resides in,
			// this is required because the ss:Index is one base
			int nCellCol = nCellIndex - 1;
			m_pGrid->JoinCells( nCellCol, rowNum, nCellCol + joinRange.cx, rowNum  + joinRange.cy );
		}

		// Setup cell object
		cell.ClearAll();
		m_pGrid->GetCellIndirect( nCellIndex - 1, rowNum, &cell );
		// load cell's data
		COXParserElement* pCellData = ((COXParserElement*) rowSubObj )->FindElement(_T("Data"));

		if ( pCellData != NULL )
		{
			CString dataType;
			COXAttribute *pDataType = pCellData->FindAttribute(_T("ss:Type"));

			if ( pDataType != NULL )
				dataType = pDataType->GetStringValue();
			else
				// by default treat all data as strings
				dataType = _T("String");

			for ( int nDataIndex = 0; nDataIndex < pCellData->NumObjects(); nDataIndex ++ )
			{
				COXParserObject *pObject = pCellData->Object( nDataIndex );

				if ( pObject->GetType() != COXParserObject::PLAINTEXT )
					continue;

				// TD v 7.2 ref kvt cell.SetText( pObject->GetText());
				// new fixup for importing multiline rows
				{
					CString theLine = pObject->GetText();
					if(theLine.Find(_T("\n")) != -1)
						cell.SetPropertyFlags(cell.GetPropertyFlags() | UGCELL_MULTIROWCELL);
					cell.SetText(theLine);
				}

				if ( dataType == _T("Number"))
				{
					cell.SetDataType( UGCELLDATA_NUMBER );
					cell.SetAlignment( UG_ALIGNRIGHT|UG_ALIGNBOTTOM );
				}
				else if ( dataType == _T("DateTime"))
				{	// change the date/time string to a format that COleDateTime understands
					CString date = cell.GetText();
					date.Replace( _T("-"), _T("/"));
					date.Replace( _T("T"), _T(" "));
					int sep = date.Find( _T(" "));
					// split the string to the date and 
					cell.SetText( date.Left( sep + 6 ));
					cell.SetDataType( UGCELLDATA_TIME );
				}
			}
		}

		// If necessary setup cell's properties from the Style set
		// ss:StyleID
		COXAttribute *pStyleID = ((COXParserElement*) rowSubObj )->FindAttribute(_T("ss:StyleID"));
		if ( pStyleID != NULL )
		{
			PopulateCellFromStyle( pStyleID->GetStringValue(), pStyles, &cell );
		}

		// save the cell object in the grid
		m_pGrid->SetCell( nCellIndex - 1, rowNum, &cell );
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
//	PopulateCellFromStyle
//		The PopulateCellFromStyle function is responsible for properly
//		setting cell's properties from appropriate Style element.
//
//		Objects supported: Alignment, Font, Interior, NumberFormat
//
//		*Note: The format information will be saved as label text
//			of a cell, this way it can be retieved and used
//			by custom celltypes to properly display the information.
//			
//	Parameters:
//		styleID	- ID of the style to parse out
//		pStyles	- pointer to Styles element (child of the Workbook)
//		pCell	- pointer to the cell object to populate with style information
//	Returns:
//		Pointer to the styles element found
int CXMLParser::PopulateCellFromStyle( CString styleID, COXParserElement *pStyles, CUGCell *pCell )
{
	if ( styleID == "Default" )
		return TRUE;

	if ( pStyles == NULL )
		return FALSE;

	// Attributes:
	//	ss:ID
	//	ss:Name
	//	ss:Parent
	COXParserElement *pStyleElement = NULL;

	for ( int nStyleIndex = 0; nStyleIndex < pStyles->NumObjects(); nStyleIndex ++ )
	{	// find Style object that is requested
		COXParserObject *pStyleSubObj = pStyles->Object( nStyleIndex );

		if ( pStyleSubObj->GetType() != COXParserObject::ELEMENT )
			// we are only interested in sub elements of the row
			continue;

		COXAttribute *pStyleId = ((COXParserElement*)pStyleSubObj)->FindAttribute(_T("ss:ID"));

		if ( pStyleId == NULL )
			continue;

		if ( _tcscmp( pStyleId->GetStringValue(), styleID ) == 0 )
		{	// requested style was found
			pStyleElement = (COXParserElement*)pStyleSubObj;
			break;
		}
	}

	if ( pStyleElement == NULL )
		// style was not found, exit with an error
		return FALSE;

	// Allow the parent style to populate the cell object first
	COXAttribute *pParentElement = pStyles->FindAttribute(_T("ss:Parent"));

	if ( pParentElement != NULL )
		PopulateCellFromStyle( pParentElement->GetStringValue(), pStyles, pCell );

	// Sub Objects supported:
	//	Alignment
	GetAlignmentStyle( pStyleElement, pCell );
	//	Font
	GetFontStyle( pStyleElement, pCell );
	//	Interior
	GetInteriorStyle( pStyleElement, pCell );
	//	NumberFormat
	GetNumberFormat( pStyleElement, pCell );

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	GetAlignmentStyle
//		The GetAlignmentStyle function loads cell alignment information
//		ss:Horizontal	"Left", "Center", "Right"
//		ss:Vertical		"Bottom", "Center", "Top"
void CXMLParser::GetAlignmentStyle( COXParserElement *pStyleElement, CUGCell *pCell )
{
	COXParserElement *pAlignmentElement = pStyleElement->FindElement(_T("Alignment"));

	if ( pAlignmentElement != NULL )
	{
		short sAlignment = pCell->GetAlignment();
		// check horizontal alignment settings
		COXAttribute *pHoriz = pAlignmentElement->FindAttribute(_T("ss:Horizontal"));

		if ( pHoriz != NULL )
		{	// remove all existing horizontal styles set
			// before setting new alignment
			sAlignment = sAlignment | UG_ALIGNLEFT | UG_ALIGNRIGHT | UG_ALIGNCENTER;
			sAlignment = sAlignment - UG_ALIGNLEFT - UG_ALIGNRIGHT - UG_ALIGNCENTER;

			if ( _tcscmp( pHoriz->GetStringValue(), _T("Right")) == 0 )
				sAlignment |= UG_ALIGNRIGHT;
			else if ( _tcscmp( pHoriz->GetStringValue(), _T("Center")) == 0 )
				sAlignment |= UG_ALIGNCENTER;
			else // left
				sAlignment |= UG_ALIGNLEFT;
		}

		// check vertical alignment settings
		COXAttribute *pVert = pAlignmentElement->FindAttribute(_T("ss:Vertical"));

		if ( pVert != NULL )
		{	// remove all existing vertical styles set
			// before setting new alignment
			sAlignment = sAlignment | UG_ALIGNTOP | UG_ALIGNVCENTER | UG_ALIGNBOTTOM;
			sAlignment = sAlignment - UG_ALIGNTOP - UG_ALIGNVCENTER - UG_ALIGNBOTTOM;

			if ( _tcscmp( pVert->GetStringValue(), _T("Top")) == 0 )
				sAlignment |= UG_ALIGNTOP;
			else if ( _tcscmp( pVert->GetStringValue(), _T("Center")) == 0 )
				sAlignment |= UG_ALIGNVCENTER;
			else // Bottom
				sAlignment |= UG_ALIGNBOTTOM;
		}

		pCell->SetAlignment( sAlignment );
	}
}

/////////////////////////////////////////////////////////////////////////////
//	GetFontStyle
void CXMLParser::GetFontStyle( COXParserElement *pStyleElement, CUGCell *pCell )
{
	// Cell fonts, attributes supported:
	//	ss:FontName
	//	ss:Size
	//	ss:Bold
	//	ss:Italic
	//	ss:Underline
	//	ss:Color
	COXParserElement *pFontElement = pStyleElement->FindElement(_T("Font"));

	if ( pFontElement != NULL )
	{
		CString faceName= _T("");
		CString fontFamily = _T("");
		int nCharSet	= 0;
		int nSize		= 0,
			nBold		= -1,
			nItalic		= -1,
			nUnderline	= -1;
		CFont *pFont = NULL;

		if ( pCell->GetPropertyFlags()&UGCELL_FONT_SET )
			pFont = pCell->GetFont();

		COXAttribute *pFaceName = pFontElement->FindAttribute(_T("ss:FontName"));
		if ( pFaceName != NULL )
			faceName = pFaceName->GetStringValue();

		COXAttribute *pFontFamily = pFontElement->FindAttribute(_T("x:Family"));
		if ( pFontFamily != NULL )
			fontFamily = pFontFamily->GetStringValue();

		COXAttribute *pCharSet = pFontElement->FindAttribute(_T("x:CharSet"));
		if ( pCharSet != NULL )
			nCharSet = _ttol( pCharSet->GetStringValue());

		COXAttribute *pFontSize = pFontElement->FindAttribute(_T("ss:Size"));
		if ( pFontSize != NULL )
		{
			CDC dc;
			double newSize = _tcstod( pFontSize->GetStringValue(), NULL);
			// get display information
			dc.CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
			float yPerInch = (float)dc.GetDeviceCaps(LOGPIXELSY);
			nSize = -(int)((newSize * yPerInch ) / 72 );
		}

		COXAttribute *pBoldAttr = pFontElement->FindAttribute(_T("ss:Bold"));
		if ( pBoldAttr != NULL )
		{
			if ( _tcscmp( pBoldAttr->GetStringValue(), _T("1")) == 0 )
				nBold = 1;
			else
				nBold = 0;
		}

		COXAttribute *pItalicAttr = pFontElement->FindAttribute(_T("ss:Italic"));
		if ( pItalicAttr != NULL )
		{
			if ( _tcscmp( pItalicAttr->GetStringValue(), _T("1")) == 0 )
				nItalic = 1;
			else
				nItalic = 0;
		}

		COXAttribute *pUnderlineAttr = pFontElement->FindAttribute(_T("ss:Underline"));
		if ( pUnderlineAttr != NULL )
		{
			if ( _tcscmp( pUnderlineAttr->GetStringValue(), _T("Single")) == 0 )
				nUnderline = 1;
			else
				nUnderline = 0;
		}

		pCell->SetFont( ModifyFont( pFont, faceName, fontFamily, nSize, nBold , nItalic , nUnderline, nCharSet ));

		COXAttribute *pTextColor = pFontElement->FindAttribute(_T("ss:Color"));
		if ( pTextColor != NULL )
		{
			pCell->SetTextColor( HexToColorref( pTextColor->GetStringValue()));
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
//	GetInteriorStyle
void CXMLParser::GetInteriorStyle( COXParserElement *pStyleElement, CUGCell *pCell )
{
	// Background color, attributes supported:
	//	ss:Color
	//	ss:Pattern
	//	ss:PatternColor
	COXParserElement *pBackElement = pStyleElement->FindElement(_T("Interior"));

	if ( pBackElement != NULL )
	{
		COXAttribute *pBackColor = pBackElement->FindAttribute(_T("ss:Color"));
		if ( pBackColor != NULL )
		{
			pCell->SetBackColor( HexToColorref( pBackColor->GetStringValue()));
		}

		/*TODO: the grid does not have a function yet to set a CBrush as cell's background
				this however is something that will be added to the grid shortly.
		COXAttribute *pPattern = pFontElement->FindAttribute(_T("ss:Pattern"));
		if ( pPattern != NULL )
		{
		}*/
	}
}

/////////////////////////////////////////////////////////////////////////////
//	GetNumberFormat
//		Data format information in the XML document is stored in the
//		"NumberFormat" subobject of the "Styles".  The format information
//		will be retieved and stored as cell's "label text", this information
//		can then be used by a CUGCellFormat derived class to provide proper
//		on screen formatting.
//		ss:Format
void CXMLParser::GetNumberFormat( COXParserElement *pStyleElement, CUGCell *pCell )
{
	COXParserElement *pFormat = pStyleElement->FindElement(_T("NumberFormat"));

	if ( pFormat != NULL )
	{
		COXAttribute *pFormatAttr = pFormat->FindAttribute(_T("ss:Format"));

		if ( pFormatAttr != NULL )
		{
			CString formatStr = pFormatAttr->GetStringValue();
			pCell->SetLabelText( formatStr );

			switch( pCell->GetDataType())
			{
			case UGCELLDATA_NUMBER:
				if ( formatStr == _T("Fixed"))
				{
					pCell->SetNumberDecimals( 2 );
				}
				else if ( formatStr.GetLength() > 1 )
				{
					int strPos = formatStr.Find(_T('.')) + 1;
					pCell->SetNumberDecimals( formatStr.GetLength() - strPos );
				}
				else
				{
					pCell->SetNumberDecimals( 0 );
				}
				break;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
//	ModifyFont
//		The ModifyFont function is used to create a new CFont object based
//		on an existing font and set of parameters that can be changed.
//		This function is required because the XML file does not provide
//		information on full set of font properties, but only what has changed.
//	Parameters:
//		pBaseFont	- pointer to an existing font object that will be used as
//					  base for the new object.  If this paramter is NULL than
//					  grid's default font will be used.
//		sFaceName	- parameter indicates new face name, only used when not empty
//		nSize		- parameter indicates new font size, or 0 when not used
//		nBold		- parameter indicates states of the bold flag in the new font,
//					  or -1 when not used
//		nItalic		- parameter indicates states of the italic flag in the new font,
//					  or -1 when not used
//		nUnderline	- parameter indicates states of the underline flag in the new font,
//					  or -1 when not used
CFont* CXMLParser::ModifyFont( CFont *pBaseFont, CString sFaceName, CString sFontFamily /*= ""*/, int nSize /*= 0*/ , int nBold /*= -1*/, int nItalic /*= -1*/, int nUnderline /*= -1*/, int nCharSet /*= 0*/ )
{
	if ( pBaseFont == NULL )
	{	// find the default font
		pBaseFont = m_pGrid->m_GI->m_defFont;
		
		if ( pBaseFont == NULL )
			// the default font is not set
			return NULL;
	}

	LOGFONT newFontLg;
	pBaseFont->GetLogFont( &newFontLg );

	if ( sFaceName != _T("") )
		UGStr::tcscpy( newFontLg.lfFaceName, ::_tcslen(sFaceName.GetBuffer(0)) ,sFaceName.GetBuffer(0));

	// Set font's family
	//if ( sFontFamily == _T("Swiss"))
	//	newFontLg.lfPitchAndFamily = TMPF_TRUETYPE|FF_SWISS;
	//else if ( sFontFamily == _T("Roman"))
	//	newFontLg.lfPitchAndFamily = TMPF_TRUETYPE|FF_ROMAN;
	//else if ( sFontFamily == _T("Script"))
	//	newFontLg.lfPitchAndFamily = TMPF_TRUETYPE|FF_SCRIPT;
	//else if ( sFontFamily == _T("Modern"))
	//	newFontLg.lfPitchAndFamily = TMPF_TRUETYPE|FF_MODERN;

	if ( nSize != 0 )
		newFontLg.lfHeight = nSize;
	
	if ( nBold == 0 )
		newFontLg.lfWeight = FW_NORMAL;
	else if ( nBold > 0 )
		newFontLg.lfWeight = FW_BOLD;

	if ( nItalic != -1 )
		newFontLg.lfItalic = (BYTE)nItalic;

	if ( nUnderline != -1 )
		newFontLg.lfUnderline = (BYTE)nUnderline;

	if ( nCharSet > 0 )
		newFontLg.lfCharSet = (BYTE)nCharSet;
	else
		newFontLg.lfCharSet = DEFAULT_CHARSET;

	return CreateFontIndirect( newFontLg );
}

/////////////////////////////////////////////////////////////////////////////
//	CreateFont
//		The CreateFont function will create a font object using only
//		basic (common) information of the object.
//	Parameters:
//		faceName	- a string containing face name of the font
//		nSize		- desired point size of the font 
//		bBold		- On/off flag indicating if the style is set
//		bItalic		- On/off flag 
//		bUnderline	- On/off flag 
//	Returns:
//		A pointer to appropriate font object.
CFont* CXMLParser::CreateFont( CString faceName, int nSize, BYTE bFontFamily /*= 0*/, BOOL bBold /*= FALSE*/, BOOL bItalic /*= FALSE*/, BOOL bUnderline /*= FALSE*/ )
{
	CDC dc;
	// get display information
	dc.CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
	float yPerInch = (float)dc.GetDeviceCaps(LOGPIXELSY);
	int nHeight = -(int)((float)nSize * yPerInch ) / 72;
	int nWeight = FW_NORMAL;

	if ( bBold == TRUE )
		nWeight = FW_BOLD;

	return CreateFont( nHeight, 0, 0, 0, nWeight, (BYTE)bItalic, (BYTE)bUnderline, 0, 0, 0, 0, 0, bFontFamily, faceName );
}

/////////////////////////////////////////////////////////////////////////////
//	CreateFont
//		Function is used to create new font object and add it to the link
//		list of fonts in use.
//	Paramters:
//		The parametrs list is identical to the CFont::CreateFont function
//	Returns:
//		A pointer to an appropriate font object.
CFont* CXMLParser::CreateFont( int nHeight, int nWidth, int nEscapement, int nOrientation, int nWeight, BYTE bItalic, BYTE bUnderline, BYTE cStrikeOut, BYTE nCharSet, BYTE nOutPrecision, BYTE nClipPrecision, BYTE nQuality, BYTE nPitchAndFamily, LPCTSTR lpszFacename )
{
	int nFontIndex = m_pGrid->AddFont( nHeight, nWidth, nEscapement, nOrientation, nWeight, 
						bItalic, bUnderline, cStrikeOut, nCharSet, nOutPrecision, 
						nClipPrecision, nQuality, nPitchAndFamily, lpszFacename );

	return m_pGrid->GetFont( nFontIndex );
}

/////////////////////////////////////////////////////////////////////////////
//	CreateFontIndirect
//		Function is used to add new fonts to the font's link list, but
//		it will also check if an object, that matches the new font,
//		is already found in the list if it is than new font will not
//		be created but a pointer to existing object will be returned.
//	Parameters:
//		newLogFont	- log font object representing new font to be created.
//	Returns:
//		A pointer to an appropriate font object.
CFont* CXMLParser::CreateFontIndirect( LOGFONT newLogFont )
{
	int nFontIndex = m_pGrid->AddFontIndirect( newLogFont );
	return m_pGrid->GetFont( nFontIndex );
}

/////////////////////////////////////////////////////////////////////////////
//	HexToColorref
//		The HexToColorref function converts color information from
//		the Hex notation (ex. #008080) to a COLORREF (a long integer).
COLORREF CXMLParser::HexToColorref( CString hexColor )
{
	long lVal;

	hexColor.Remove(_T('#'));
	hexColor.Format( _T("%s%s%s"), hexColor.Right( 2 ), hexColor.Mid( 2, 2 ), hexColor.Left( 2 ));
	hexColor = "0x" + hexColor;
#if _MSC_VER >= 1400
	_stscanf_s( hexColor, _T("%x"), &lVal );
#else
	_stscanf( hexColor, _T("%x"), &lVal );
#endif
	return lVal;
}

/////////////////////////////////////////////////////////////////////////////
//	ColorrefToHex
//		The ColorrefToHex function converts a color information from
//		the COLORREF notation to the Hex.
CString CXMLParser::ColorrefToHex( COLORREF color )
{
	CString hexColor;
	hexColor.Format( _T("%06x"), color );
	// reverse the string
	hexColor.Format( _T("#%s%s%s"), hexColor.Right( 2 ), hexColor.Mid( 2, 2 ), hexColor.Left( 2 ));

	return hexColor;
}

/////////////////////////////////////////////////////////////////////////////
//	FindStylesElement
//		The FindStylesElement function will attempt to find a pointer to
//		Styles element.
//	Parameters:
//		pCurElement	- pointer to current element
//	Returns:
//		pointer to Styles element, or NULL if failed
COXParserElement* CXMLParser::FindStylesElement( COXParserElement *pCurElement )
{
	COXParserElement *pBaseElement = pCurElement->GetParent();

	if ( pBaseElement != NULL )
		return FindStylesElement( pBaseElement );

	// if pBaseElement is NULL than we know that the pCurElement points to the ROOT
	// locate the Workbook element
	pBaseElement = pCurElement->FindElement(_T("Workbook"));

	if ( pBaseElement == NULL )
		return NULL;

	// locate the Styles element
	pBaseElement = pBaseElement->FindElement(_T("Styles"));

	return pBaseElement;
}

/////////////////////////////////////////////////////////////////////////////
//	Save
//		The Save function gets current grid information and saves it
//		in a XML file.  The element and attribute names and file layout
//		used are identical to Excel XP, making it possible for the information
//		to be exchanged between Excel XP and Ultimate Grid.
//	Parameters:
//		filePath	- path and file name of the XML file to write.
//		m_pGrid		- pointer to a grid object to work with
//	Returns:
int CXMLParser::Save( CString filePath )
{
	ASSERT( m_pGrid );
	ASSERT( filePath != _T(""));

	COXParser parser;
	int nCurrentSheet = m_pGrid->GetSheetNumber();
	// disable grid's painting
	m_pGrid->SetPaintMode( FALSE );
	// make sure that the grid is set to show first sheet
	m_pGrid->SetSheetNumber( 0 );
	
	COXParserObject *parserObj = new COXParserObject();
	parserObj->SetText(_T("xml version=\"1.0\""));
	parserObj->SetType( COXParserObject::PROCINSTR );
	parser.Root()->AddObject( parserObj );
	COXParserElement *pWorkBook = parser.Root()->AddElement(_T("Workbook"));
	// add "ss" namespace, so our XML page could be read by Excel
	pWorkBook->AddAttribute(_T("xmlns"), _T("urn:schemas-microsoft-com:office:spreadsheet"));
	pWorkBook->AddAttribute(_T("xmlns:o"), _T("urn:schemas-microsoft-com:office:office"));
	pWorkBook->AddAttribute(_T("xmlns:x"), _T("urn:schemas-microsoft-com:office:excel"));
	pWorkBook->AddAttribute(_T("xmlns:ss"), _T("urn:schemas-microsoft-com:office:spreadsheet"));
	pWorkBook->AddAttribute(_T("xmlns:html"), _T("http://www.w3.org/TR/REC-html40"));

	// The styles collection will be populated using the AddStyle
	// method, it will be called for each column or cell that have
	// additional styles set (font, etc).
	pWorkBook->AddElement( _T("Styles") );

	// loop through all of the sheets in the grid and add them one at a time
	for( int nSheetIndex = 0; nSheetIndex < m_pGrid->GetNumberSheets(); nSheetIndex ++ )
	{
		COXParserElement *pWorksheetElement = pWorkBook->AddElement(_T("Worksheet"));
		// change grid's current sheet to allow retrieval of data
		m_pGrid->SetSheetNumber( nSheetIndex );
		// gather information on the current grid's sheet
		GatherWorksheetInfo( pWorksheetElement );
	}

	parser.WriteFile( filePath );

	// clean up possible styles allocated by the AddStyle function
	if ( m_pAddedStyles != NULL )
	{
		_tagAddedStyles *pStyle, *pTempStyle;
		pStyle = m_pAddedStyles;
		m_pAddedStyles = NULL;

		while ( pStyle != NULL )
		{
			pTempStyle = pStyle->next;
			delete pStyle;
			pStyle = pTempStyle;
		}	
	}

	// restore sheet information as it was before starting the save
	m_pGrid->SetSheetNumber( nCurrentSheet );
	// and enable painting
	m_pGrid->SetPaintMode( TRUE );

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	GatherWorksheetInfo
//		The GatherWorksheetInfo function will gather name information for the
//		sheet element and create table sub-object.
//	Paramters:
//		pWorksheetElement	- pointer to worksheet element
//		m_pGrid	- pointer to the grid control that we are gathering information from
//	Return:
//		TRUE if successful, FALSE if failed.
int CXMLParser::GatherWorksheetInfo( COXParserElement *pWorksheetElement )
{
	int nSheetIndex = m_pGrid->GetSheetNumber();
	// save sheet name information
	pWorksheetElement->AddAttribute( _T("ss:Name"), m_pGrid->m_CUGTab->GetTabLabel( nSheetIndex ));
	
	if ( m_pGrid->GetNumberCols() > 0 && m_pGrid->GetNumberRows() > 0 )
	{	// create table sub-object
		COXParserElement *pTableElement = pWorksheetElement->AddElement(_T("Table"));
		// gather table information
		return GatherTableInfo( pTableElement );
	}

	// the given sheet does not have any information to save
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	GatherTableInfo
//		The GatherTableInfo function will gather table specific information
//		(number columns and rows).
//		sub-objects.
//	Parameters:
//		pTableElement	- pointer to the table element
//		m_pGrid	- pointer to the grid control that we are gathering information from
//	Return:
//		TRUE if successful, FALSE if failed.
int CXMLParser::GatherTableInfo( COXParserElement *pTableElement )
{
	CString tempStr;
	tempStr.Format( _T("%d"), m_pGrid->GetNumberCols());
	pTableElement->AddAttribute( _T("ss:ExpandedColumnCount"), tempStr );
	tempStr.Format( _T("%d"), m_pGrid->GetNumberRows());
	pTableElement->AddAttribute( _T("ss:ExpandedRowCount"), tempStr );
	// gather information on the columns
	GatherColumnInfo( pTableElement );
	// gather information on the rows and cells
	GatherRowInfo( pTableElement );

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	GatherColumnInfo
//		The GatherColumnInfo will go through all columns in the grid, and 
//		for each column that is different than the default it will create
//		a Column element (a child to the table).
//	Parameters:
//		pTableElement
//		m_pGrid
//	Return:
//		TRUE if successful, FALSE if failed.
int CXMLParser::GatherColumnInfo( COXParserElement *pTableElement )
{
	CUGCell colDef, gridDef;
	CString ssIndex, ssWidth, ssStyleID;
	COXParserElement *pStylesElement = NULL;

	// find a pointer to styles element
	pStylesElement = FindStylesElement( pTableElement );

	// setup default information
	m_pGrid->GetGridDefault( &gridDef );
	int nLastIndex = -1;

	for ( int nColIndex = 0; nColIndex < m_pGrid->GetNumberCols(); nColIndex ++ )
	{
		ssIndex = "";
		ssWidth = "";
		ssStyleID = "";

		// compare cell's style
		colDef.ClearAll();
		m_pGrid->GetColDefault( nColIndex, &colDef );
		short changeMask = CompareCellStyles( &gridDef, &colDef );
		if ( changeMask != 0 )
			ssStyleID = AddStyle( pStylesElement, &colDef, changeMask );

		// compare column's width to the default col width
		if ( m_pGrid->GetColWidth( nColIndex ) != m_pGrid->m_GI->m_defColWidth )
			ssWidth.Format( _T("%.2f"), m_pGrid->GetColWidth( nColIndex ) * 0.75 );

		if ( ssStyleID != "" || ssWidth != "" )
		{
			// make sure that the ss:Index properly set
			if (( nColIndex - 1 ) != nLastIndex )
				ssIndex.Format(_T("%d"), nColIndex + 1 );

			nLastIndex = nColIndex;

			COXParserElement *pColElement = pTableElement->AddElement(_T("Column"));
			// add the changed attributes to the colunm element
			if ( ssIndex != "" )
				pColElement->AddAttribute(_T("ss:Index"), ssIndex );

			if ( ssStyleID != "" )
				pColElement->AddAttribute(_T("ss:StyleID"), ssStyleID );

			if ( ssWidth != "" )
			{
				pColElement->AddAttribute(_T("ss:AutoFitWidth"), _T("0"));
				pColElement->AddAttribute(_T("ss:Width"), ssWidth );
			}
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	GatherRowInfo
int CXMLParser::GatherRowInfo( COXParserElement *pTableElement )
{
	CString ssIndex, ssHeight;
	int nLastIndex = -1;

	for ( long nRowIndex = 0; nRowIndex < m_pGrid->GetNumberRows(); nRowIndex ++ )
	{
		COXParserElement *pRowElement = NULL;
		// gather information on row's cells
		pRowElement = GatherRowData( pTableElement, nRowIndex );
		// gather information on row's attributes
		ssIndex = "";
		ssHeight = "";

		// compare row's height to the default row height
		if ( m_pGrid->GetRowHeight( nRowIndex ) != m_pGrid->m_GI->m_defRowHeight )
			// TD v 7.2 ref kvt 
			// this is a fixup because MS Excel does not like a single cell to be more than 2047 high
			// ssHeight.Format( _T("%.2f"), m_pGrid->GetRowHeight( nRowIndex ) * 0.75 );
			ssHeight.Format( _T("%.2f"), min(2047.0, m_pGrid->GetRowHeight( nRowIndex ) * 0.75 ));

		if ( ssHeight != "" || pRowElement != NULL )
		{	
			if ( pRowElement == NULL )
				pRowElement = pTableElement->AddElement(_T("Row"));

			// make sure that the ss:Index properly set
			if (( nRowIndex - 1 ) != nLastIndex )
				ssIndex.Format(_T("%d"), nRowIndex + 1 );

			nLastIndex = nRowIndex;

			// add the changed attributes to the row element
			if ( ssIndex != "" )
				pRowElement->AddAttribute(_T("ss:Index"), ssIndex );

			if ( ssHeight != "" )
			{
				pRowElement->AddAttribute(_T("ss:AutoFitHeight"), _T("0"));
				pRowElement->AddAttribute(_T("ss:Height"), ssHeight );
			}
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	GatherRowData
//		The GatherRowData function loops through all of the cells in a row
//		and check each if it needs to be persisted based on its style settings
//		and data.
//	Parameters:
//		pTableElement
//		m_pGrid
//		nRowNum
//	Returns:
//		A pointer to row element that was used to save cell information.
//		If none of the cells was saved than returns NULL.
COXParserElement* CXMLParser::GatherRowData( COXParserElement *pTableElement, long nRowNum )
{
	BOOL bOrigin;
	int nJoinCol;
	long nJoinRow;
	int nLastIndex = -1;
	CString ssStyleID;
	CUGCell colInfo, cellInfo;
	COXParserElement* pRowElement = NULL;
	// find a pointer to styles element
	COXParserElement* pStylesElement = FindStylesElement( pTableElement );

	for ( int nCellIndex = 0; nCellIndex < m_pGrid->GetNumberCols(); nCellIndex ++ )
	{
		// clear member variables that will be reused
		colInfo.ClearAll();
		cellInfo.ClearAll();
		bOrigin = FALSE;
		nJoinCol = 0;
		nJoinRow = 0;
		ssStyleID = _T("");

		// get cell information
		//m_pGrid->GetColDefault( nCellIndex, &colInfo );
		m_pGrid->GetGridDefault( &colInfo );
		m_pGrid->GetCellIndirect( nCellIndex, nRowNum, &cellInfo );
		// make sure that this cell is not part of a join
		if ( cellInfo.GetPropertyFlags()&UGCELL_JOIN_SET )
		{
			cellInfo.GetJoinInfo( &bOrigin, &nJoinCol, &nJoinRow );
			if ( bOrigin != TRUE )
				continue;
		}
		// compare cell's style information
		short changeMask = CompareCellStyles( &colInfo, &cellInfo );
		// if necessary add the new style to the Styles collection.
		if ( changeMask != 0 )
			ssStyleID = AddStyle( pStylesElement, &cellInfo, changeMask );

		if ( ssStyleID == _T("") &&
			!( cellInfo.GetPropertyFlags()&UGCELL_STRING_SET ) &&
			!( cellInfo.GetPropertyFlags()&UGCELL_JOIN_SET ))
			// the cell does not contain any information that needs to be saved
			continue;

		// Save cell information if it has data or style information set
		if ( pRowElement == NULL )
			pRowElement = pTableElement->AddElement(_T("Row"));

		COXParserElement* pCellElement = pRowElement->AddElement(_T("Cell"));

		CString ssIndex;
		// make sure that the ss:Index is properly set
		if (( nCellIndex - 1 ) != nLastIndex )
			ssIndex.Format(_T("%d"), nCellIndex + 1 );

		nLastIndex = nCellIndex;

		// write the index information to the cell
		if ( ssIndex != _T(""))
			pCellElement->AddAttribute(_T("ss:Index"), ssIndex );

		// generate and write join information (if necessary)
		if ( cellInfo.GetPropertyFlags()&UGCELL_JOIN_SET )
		{
			CString tempJoinStr;

			if ( nJoinCol > 0 )
			{
				tempJoinStr.Format(_T("%d"), nJoinCol );
				pCellElement->AddAttribute(_T("ss:MergeAcross"), tempJoinStr );
			}
			if ( nJoinRow > 0 )
			{
				tempJoinStr.Format(_T("%d"), nJoinRow );
				pCellElement->AddAttribute(_T("ss:MergeDown"), tempJoinStr );
			}
		}

		// write the style information to the cell
		if ( ssStyleID != _T(""))
			pCellElement->AddAttribute(_T("ss:StyleID"), ssStyleID );

		// write cell data information
		if ( cellInfo.GetPropertyFlags()&UGCELL_STRING_SET )
		{
			//COXParserElement* pDataElement = pCellElement->AddElement(_T("Data"));
			CString cellDataType, cellData;
			COleDateTime dateTime;

			switch( cellInfo.GetDataType())
			{
			case UGCELLDATA_BOOL:
				cellDataType = _T("Boolean");
				cellData.Format(_T("%d"), cellInfo.GetNumber());
				break;
			case UGCELLDATA_NUMBER:
			case UGCELLDATA_CURRENCY:
				cellDataType = _T("Number");
				cellData.Format(_T("%f"), cellInfo.GetNumber());
				cellData.TrimRight(_T('0'));
				cellData.TrimLeft(_T('0'));
				break;
			case UGCELLDATA_TIME:
				cellDataType = _T("DateTime");
				// [YYYY-MM-DD]T[HH:MM:SS.###]
				dateTime = cellInfo.GetNumber();
				cellData.Format(_T("%02d-%02d-%02dT%02d:%02d:%02d.000"),
					dateTime.GetYear(), dateTime.GetMonth(), dateTime.GetDay(),
					dateTime.GetHour(), dateTime.GetMinute(), dateTime.GetSecond());
				break;
			case UGCELLDATA_STRING:
				cellDataType = _T("String");
				cellData = cellInfo.GetText();

				// TD added v 7.2 ref kvt
				cellData.Replace(_T(" "), _T("&#160")); // same as &nbsp; this is what excel exports (?)
				
				// optional (?) kvt reports IE probs if used with #160
				//cellData.Replace(_T("<"), _T("&lt"));
				//cellData.Replace(_T(">"), _T("&gt"));
				if(cellInfo.GetPropertyFlags()&UGCELL_MULTIROWCELL)
					cellData.Replace(_T("\n"), _T("&#10;"));

				break;
			default:
				break;
			}
			COXParserObject* pObject = new COXParserObject;
			// Persist cell's data, the data tag is expected to be as:
			// <Data ss:Type="Number">113</Data>
			pObject->SetText( "<Data ss:Type='" + cellDataType + "'>" + cellData + "</Data>" );
			pObject->SetType( COXParserObject::RAWTEXT );
			pCellElement->AddObject( pObject );
		}
	}

	return pRowElement;
}

/////////////////////////////////////////////////////////////////////////////
//	AddStyle
//		The AddStyle function will first try to determine if an identical style
//		was aready added to the Styles collection.  If matching style is found,
//		then its ID information will be used, otherwise a new elemenet will be
//		created.
//	Parameters:
//		pStylesElement	- pointer to existing Styles element
//		pCell			- pointer to a cell to persist
//		changeMask		- determines which properties of the cell are to be persisted.
//						  This mask is determined by the CompareCellStyles function.
//	Returns:
//		a string representing Style element that contains cell's format information
CString CXMLParser::AddStyle( COXParserElement *pStylesElement, CUGCell *pCell, short changeMask )
{
	// create new style structure
	_tagAddedStyles	*pNewStyle = new _tagAddedStyles;
	PopulateStyleStruct( pNewStyle, pCell, changeMask );

	// check if an identical style exists
	_tagAddedStyles	*pLoopStyle = m_pAddedStyles;
	while ( pLoopStyle != NULL )
	{
		if ( CompareStyles( pLoopStyle, pNewStyle ) == 0 )
		{	// matching style was found, return style ID
			delete pNewStyle;
			return pLoopStyle->styleID;
		}
		// move on to the next item
		pLoopStyle = pLoopStyle->next;
	}

	// Add the new item to the list
	int nStylesCount = 0;
	if ( m_pAddedStyles == NULL )
	{
		m_pAddedStyles = pNewStyle;
	}
	else
	{	// search for last good item
		pLoopStyle = m_pAddedStyles;
		nStylesCount ++;
		while ( pLoopStyle->next != NULL )
		{
			// move on to the next item
			pLoopStyle = pLoopStyle->next;
			nStylesCount ++;
		}

		pLoopStyle->next = pNewStyle;
	}

	// The styles generated contain sequencial IDs starting at 50
	pNewStyle->styleID.Format( _T("s%d"), nStylesCount + 50 );

	// Add it to the Styles collection
	COXParserElement *pNewSubElement = NULL;
	COXParserElement *pNewElement = pStylesElement->AddElement(_T("Style"));

	// Style ID
	pNewElement->AddAttribute(_T("ss:ID"), pNewStyle->styleID );

	// Alignment - TD v 7.2 change ref kvt multiline cells
//	if ( changeMask&STYLE_HALIGN || changeMask&STYLE_VALIGN )
	if ( changeMask&STYLE_HALIGN || changeMask&STYLE_VALIGN || changeMask&STYLE_MULTIROWCELL)
	{
		pNewSubElement = pNewElement->AddElement(_T("Alignment"));
		// Horizontal alignement
		if ( changeMask&STYLE_HALIGN )
			pNewSubElement->AddAttribute(_T("ss:Horizontal"), pNewStyle->style_hAlign );
		// Vertical alignment
		if ( changeMask&STYLE_VALIGN )
			pNewSubElement->AddAttribute(_T("ss:Vertical"), pNewStyle->style_vAlign );
		// TD v 7.2 change ref kvt multirow cell alignment 
		if ( changeMask&STYLE_MULTIROWCELL )
			pNewSubElement->AddAttribute(_T("ss:WrapText"), pNewStyle->style_multiRowCell );
	}

	//Font
	if ( changeMask&STYLE_FONTNAME || changeMask&STYLE_FONTSIZE ||
		 changeMask&STYLE_FONTBOLD || changeMask&STYLE_FONTITALIC ||
		 changeMask&STYLE_FONTUNDERLINE || changeMask&STYLE_FONTCOLOR )
	{
		pNewSubElement = pNewElement->AddElement(_T("Font"));
		if ( changeMask&STYLE_FONTNAME )
			pNewSubElement->AddAttribute(_T("ss:FontName"), pNewStyle->style_fontName );
		if ( pNewStyle->style_fontFamily != _T(""))
			pNewSubElement->AddAttribute(_T("x:Family"), pNewStyle->style_fontFamily );
		if ( pNewStyle->style_charSet != _T(""))
			pNewSubElement->AddAttribute(_T("x:CharSet"), pNewStyle->style_charSet );
		if ( changeMask&STYLE_FONTSIZE )
			pNewSubElement->AddAttribute(_T("ss:Size"), pNewStyle->style_fontSize );
		if ( changeMask&STYLE_FONTBOLD )
			pNewSubElement->AddAttribute(_T("ss:Bold"), pNewStyle->style_fontBold );
		if ( changeMask&STYLE_FONTITALIC )
			pNewSubElement->AddAttribute(_T("ss:Italic"), pNewStyle->style_fontIatalic );
		if ( changeMask&STYLE_FONTUNDERLINE )
			pNewSubElement->AddAttribute(_T("ss:Underline"), pNewStyle->style_fontUnderline );
		// Text color
		if ( changeMask&STYLE_FONTCOLOR )
			pNewSubElement->AddAttribute(_T("ss:Color"), pNewStyle->style_fontColor );
	}
	//Interior
	if ( changeMask&STYLE_BACKCOLOR || changeMask&STYLE_BACKPATTERN )
	{
		pNewSubElement = pNewElement->AddElement(_T("Interior"));
		// back color
		if ( changeMask&STYLE_BACKCOLOR )
			pNewSubElement->AddAttribute(_T("ss:Color"), pNewStyle->style_backColor );

		// back pattern
		if ( changeMask&STYLE_BACKPATTERN )
			pNewSubElement->AddAttribute(_T("ss:Pattern"), pNewStyle->style_backPattern );
		else if ( changeMask&STYLE_BACKCOLOR )
			pNewSubElement->AddAttribute(_T("ss:Pattern"), _T("Solid"));
	}
	// NumberFormat
	if ( changeMask&STYLE_NUMBERFORMAT )
	{
		pNewSubElement = pNewElement->AddElement(_T("NumberFormat"));
		pNewSubElement->AddAttribute(_T("ss:Format"), pNewStyle->style_numberFormat );
	}

	return pNewStyle->styleID;
}

/////////////////////////////////////////////////////////////////////////////
//	PopulateStyleStruct
int CXMLParser::PopulateStyleStruct( _tagAddedStyles *pStyle, CUGCell *pCell, short changeMask )
{
	pStyle->next = NULL;

	// Horizontal alignement
	if ( changeMask&STYLE_HALIGN )
	{
		short alignment = pCell->GetAlignment();

		if ( alignment&UG_ALIGNRIGHT )
			pStyle->style_hAlign = _T("Right");
		else if ( alignment&UG_ALIGNCENTER )
			pStyle->style_hAlign = _T("Center");
		else
			pStyle->style_hAlign = _T("Left");
	}
	// Vertical alignment
	if ( changeMask&STYLE_VALIGN )
	{
		short alignment = pCell->GetAlignment();

		if ( alignment&UG_ALIGNTOP )
			pStyle->style_vAlign = _T("Top");
		else if ( alignment&UG_ALIGNVCENTER )
			pStyle->style_vAlign = _T("Center");
		else
			pStyle->style_vAlign = _T("Bottom");
	}
	// TD v 7.2 added ref kvt multiRowCell alignment 
	if ( changeMask&STYLE_MULTIROWCELL )
	{
		pStyle->style_multiRowCell = _T("1");
	}

	// Font information 
	CFont *pFont = pCell->GetFont();
	if ( pFont != NULL )
	{
		LOGFONT lgFont;
		pFont->GetLogFont( &lgFont );
		// Font face name
		if ( changeMask&STYLE_FONTNAME )
			pStyle->style_fontName = lgFont.lfFaceName;

		if ( changeMask&STYLE_FONTSIZE )
		{
			CDC dc;
			float nSize = (float)lgFont.lfHeight;
			// get display information
			dc.CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
			float yPerInch = (float)dc.GetDeviceCaps(LOGPIXELSY);
			pStyle->style_fontSize.Format( _T("%.0f"), -( nSize * 72 / yPerInch ));
		}

		if ( changeMask&STYLE_FONTBOLD )
		{
			if ( lgFont.lfWeight > FW_NORMAL )
				pStyle->style_fontBold = _T("1");
			else
				pStyle->style_fontBold = _T("0");
		}

		if ( changeMask&STYLE_FONTITALIC )
		{
			if ( lgFont.lfItalic > 0 )
				pStyle->style_fontIatalic = _T("1");
			else
				pStyle->style_fontIatalic = _T("0");
		}

		if ( changeMask&STYLE_FONTUNDERLINE )
		{
			if ( lgFont.lfUnderline > 0 )
				pStyle->style_fontUnderline = _T("Single");
			else
				pStyle->style_fontUnderline = _T("");
		}

		if ( changeMask&STYLE_FONTNAME )
		{	// When the font name is changed,
			// - if required store the font family
			if ( lgFont.lfPitchAndFamily&FF_SWISS )
				pStyle->style_fontFamily = _T("Swiss");
			else if ( lgFont.lfPitchAndFamily&FF_ROMAN )
				pStyle->style_fontFamily = _T("Roman");
			else if ( lgFont.lfPitchAndFamily&FF_SCRIPT )
				pStyle->style_fontFamily = _T("Script");
			else if ( lgFont.lfPitchAndFamily&FF_MODERN )
				pStyle->style_fontFamily = _T("Modern");
			else
				pStyle->style_fontFamily = _T("");

			// - and character set
			if ( lgFont.lfCharSet > 1 )
				pStyle->style_charSet.Format(_T("%d"), lgFont.lfCharSet );
		}
	}
	// Text color
	if ( changeMask&STYLE_FONTCOLOR )
		pStyle->style_fontColor = ColorrefToHex( pCell->GetTextColor());
	// back color
	if ( changeMask&STYLE_BACKCOLOR )
		pStyle->style_backColor = ColorrefToHex( pCell->GetBackColor());
	// back pattern
	if ( changeMask&STYLE_BACKPATTERN )
	{
		// TODO
	}
	// numeric format
	if ( changeMask&STYLE_NUMBERFORMAT )
	{
		int nNumDec = pCell->GetNumberDecimals();

		if ( nNumDec == 0 )
			pStyle->style_numberFormat = _T("0");
		else if ( nNumDec == 2 )
			pStyle->style_numberFormat = _T("Fixed");
		else
		{
			CString formatStr;
			formatStr.Format( _T("0.%%0%dd"), nNumDec );
			pStyle->style_numberFormat.Format( formatStr, 0 );
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	CompareStyles
int CXMLParser::CompareStyles( _tagAddedStyles* pLoopStyle, _tagAddedStyles* pNewStyle )
{
	int returnVal = 0;
	// Alignment
	if ( pLoopStyle->style_hAlign != pNewStyle->style_hAlign )
		returnVal ++;
	if ( pLoopStyle->style_vAlign != pNewStyle->style_vAlign )
		returnVal ++;
	// TD v 7.2 ref kvt multiline cells 
	if ( pLoopStyle->style_multiRowCell != pNewStyle->style_multiRowCell )
		returnVal ++;

	// Font information
	if ( pLoopStyle->style_fontName != pNewStyle->style_fontName )
		returnVal ++;

	if ( pLoopStyle->style_fontFamily != pNewStyle->style_fontFamily )
		returnVal ++;

	if ( pLoopStyle->style_charSet != pNewStyle->style_charSet )
		returnVal ++;

	if ( pLoopStyle->style_fontSize != pNewStyle->style_fontSize )
		returnVal ++;

	if ( pLoopStyle->style_fontBold != pNewStyle->style_fontBold )
		returnVal ++;

	if ( pLoopStyle->style_fontIatalic != pNewStyle->style_fontIatalic )
		returnVal ++;

	if ( pLoopStyle->style_fontUnderline != pNewStyle->style_fontUnderline )
		returnVal ++;

	// Text color
	if ( pLoopStyle->style_fontColor != pNewStyle->style_fontColor )
		returnVal ++;

	// Back color
	if ( pLoopStyle->style_backColor != pNewStyle->style_backColor )
		returnVal ++;

	// Back pattern
	if ( pLoopStyle->style_backPattern != pNewStyle->style_backPattern )
		returnVal ++;

	// Numeric format
	if ( pLoopStyle->style_numberFormat != pNewStyle->style_numberFormat )
		returnVal ++;

	return returnVal;
}

/////////////////////////////////////////////////////////////////////////////
//	CompareCellStyles
//		The CompareCellStyles function will take the two cell objects
//		passed in and it will compare them.  It will only compare the
//		attributes that are saved in a Style element.
//	Parameters:
//		pCell1, pCell2	- pointers to CUGCell objects to be compared.
//	Returns:
//		zero when both cells are equal
short CXMLParser::CompareCellStyles( CUGCell *pCell1, CUGCell *pCell2 )
{
	short returnVal = 0;

	// compare alignment
	if ( pCell2->GetPropertyFlags()&UGCELL_ALIGNMENT_SET )
	{
		short align1, align2;
		// check if the horizontal alignment was changed
		align1 = pCell1->GetAlignment();
		align2 = pCell2->GetAlignment();
		// remove vertical alignment styles
		// the 0x38 represents all of the vertical styles set,
		// in the next couple of lines I will set all of these
		// and then remove them, this way we will be left with
		// only the horizontal styles set.
		align1 = ( align1|0x38 ) - 0x38;
		align2 = ( align2|0x38 ) - 0x38;

		if ( align1 != align2 )
			returnVal |= STYLE_HALIGN;

		// check if the vertical aligment styles are different
		align1 = pCell1->GetAlignment();
		align2 = pCell2->GetAlignment();
		// remove horizontal alignment styles
		// the 0x07 represents all of the vertical styles set
		align1 = ( align1|0x07 ) - 0x07;
		align2 = ( align2|0x07 ) - 0x07;

		if ( align1 != align2 )
			returnVal |= STYLE_VALIGN;
	}

	// TD v 7.2 added ref kvt - compare multirow cell alignment 
	{
		long cell1, cell2;
		cell1 = pCell1->GetPropertyFlags()&UGCELL_MULTIROWCELL;
		cell2 = pCell2->GetPropertyFlags()&UGCELL_MULTIROWCELL;
		if(cell1 != cell2)
			returnVal |= STYLE_MULTIROWCELL;
	}

	// compare cell fonts
	if ( pCell2->GetPropertyFlags()&UGCELL_FONT_SET )
	{
		CFont *pFont1 = pCell1->GetFont();
		CFont *pFont2 = pCell2->GetFont();
		
		if ( pFont1 == NULL )
			// all of font properties differ
			returnVal |= STYLE_FONTNAME|STYLE_FONTSIZE|STYLE_FONTBOLD|STYLE_FONTITALIC|STYLE_FONTUNDERLINE;
		else if ( pFont2 != NULL )
		{
			LOGFONT lgFont1, lgFont2;
			pFont1->GetLogFont( &lgFont1 );
			pFont2->GetLogFont( &lgFont2 );

			// compare font face name
			if ( _tcscmp( lgFont1.lfFaceName, lgFont2.lfFaceName ) != 0 )
				returnVal |= STYLE_FONTNAME;
			// font height
			if ( lgFont1.lfHeight != lgFont2.lfHeight )
				returnVal |= STYLE_FONTSIZE;
			// font weight (BOLD)
			if ( lgFont1.lfWeight != lgFont2.lfWeight )
				returnVal |= STYLE_FONTBOLD;
			// italic flag
			if ( lgFont1.lfItalic != lgFont2.lfItalic )
				returnVal |= STYLE_FONTITALIC;
			// underline flag
			if ( lgFont1.lfUnderline != lgFont2.lfUnderline )
				returnVal |= STYLE_FONTUNDERLINE;
		}
	}

	// compare cell's text color
	if ( pCell2->GetPropertyFlags()&UGCELL_TEXTCOLOR_SET )
	{
		if ( pCell1->GetTextColor() != pCell2->GetTextColor() )
			returnVal |= STYLE_FONTCOLOR;
	}

	// compare cell's back color
	if ( pCell2->GetPropertyFlags()&UGCELL_BACKCOLOR_SET )
	{
		if ( pCell2->GetBackColor() != pCell1->GetBackColor())
			returnVal |= STYLE_BACKCOLOR;
	}

/*	TODO: the back pattern functionality is not yet finished.
	if ( pCell2->GetPropertyFlags()&UGCELL_BACKPATTERN_SET )
	{
		if ( pCell2->GetBackColor() != pCell1->GetBackColor())
			returnVal |= STYLE_BACKPATTERN;
	}*/

	if ( pCell2->GetPropertyFlags()&UGCELL_NUMBERDEC_SET )
	{
		if (!( pCell1->GetPropertyFlags()&UGCELL_NUMBERDEC_SET ))
			returnVal |= STYLE_NUMBERFORMAT;
		else if ( pCell2->GetNumberDecimals() != pCell1->GetNumberDecimals())
			returnVal |= STYLE_NUMBERFORMAT;
	}

	return returnVal;
}