/*************************************************************************
				Class Declaration : CXMLParser
**************************************************************************
	Source file : XMLParser.cpp
	Header file : XMLParser.h

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

	Purpose:
		The CXMLParser class provides the Ultimate Grid with ability
		to load and save XML formatted documents.  The expected format
		for the XML documents is common to MS Excel XP and the Spreadsheet
		Component and is described in "XML Spreadsheet Reference"
		and "XML in Excel and the Spreadsheet Component" articles
		in the MSDN.

	Ultimate ToolBox dependencies:
		The CXMLParser uses the COXParser class (from the Ultimate ToolBox)
		to parse out the XML document, then the parsed data is queried
		and converted so the Ultimate Grid can understand it.

		The COXParser class requires following files to be added to
		a project:
			OXParser.cpp
			OXHashTable.cpp
			OXQuickString.cpp

		These files are included with the XML parser, and can be found in:
			"<UG install>\DataSources\XML\COXParser"

	Details:
		The basic functionality of this class can be accessed via
		the Load and Save functions.

		The Load function will load and parse the XML document specified
		and it will translate relative information into a form that the
		Ultimate Grid can understand.

		The Save function gets current grid information and saves it
		in a XML file.  Element and attribute names and file layout
		used are identical to Excel XP, making it possible for the information
		to be exchanged between Excel XP and Ultimate Grid.

		The XML file format that is expected is:
		* This is the same file format as used by MS Excel XP.

		+->	Workbook
			+->	Styles
			|	+->	Style[...]
			|		ss:ID
			|		ss:Parent
			|		+->	Alignment
			|		|	ss:Horizontal
			|		|	ss:Horizontal
			|		+->	Font
			|		|	ss:FontName	
			|		|	x:Family
			|		|	x:CharSet
			|		|	ss:Size
			|		|	ss:Bold
			|		|	ss:Italic
			|		|	ss:Underline
			|		|	ss:Color
			|		+->	Interior
			|		|	ss:Color
			|		|	<... ss:Pattern ...>
			|		|	<... ss:PatternColor ...>
			|		+->	NumberFormat
			|			ss:Format
			+->	Worksheet[...]
				ss:Name
				+->	Table
					ss:ExpandedColumnCount
					ss:ExpandedRowCount
					+->	Column[...]
					|	ss:Index
					|	ss:Span
					|	ss:Width
					|	ss:StyleID
					+->	Row[...]
						ss:Index
						ss:Height
						ss:StyleID
						+->	Cell[...]
							ss:Index
							ss:MergeAcross
							ss:MergeDown
							ss:StyleID
							+->	Data
								ss:Type

	*Note: Excel does not save overlay objects in the XML file,
	it saves formulas along with the calculated value.  The Ultimate
	Grid does not have support for formulas, therefore we only
	retrieve the calculated value.

*************************************************************************/
#if !defined(AFX_XMLPARSER_H__9018A8B5_8AAB_4D9B_9172_8F1A836A44A1__INCLUDED_)
#define AFX_XMLPARSER_H__9018A8B5_8AAB_4D9B_9172_8F1A836A44A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OXParser.h"
#include "UGCtrl.h"

// These defines are used by the CompareCellStyles
// function as a return value to indicate which
// cell properties it found different.
// And by the AddStyle function to know which
// styles it should use to create a Style element.
#define STYLE_HALIGN		BIT0
#define STYLE_VALIGN		BIT1
#define STYLE_FONTNAME		BIT2
#define STYLE_FONTSIZE		BIT3
#define STYLE_FONTBOLD		BIT4
#define STYLE_FONTITALIC	BIT5
#define STYLE_FONTUNDERLINE	BIT6
#define STYLE_FONTCOLOR		BIT7
#define STYLE_BACKCOLOR		BIT8
#define STYLE_BACKPATTERN	BIT9
#define STYLE_NUMBERFORMAT	BIT10
#define STYLE_MULTIROWCELL	BIT11	// TD v 7.2 - ref kvt

class CXMLParser  
{
public:
	CXMLParser();
	virtual ~CXMLParser();

	int Load( CString filePath );
	int Save( CString filePath );
	inline void SetGridObject( CUGCtrl *pGrid ) { m_pGrid = pGrid; }
	void GridCleanUp();

protected:
	CString m_defFontName;
	int m_defFontSize;
	CUGCtrl* m_pGrid;

public:
	// Accessor functions to the link list of fonts, this list is
	// populated when XML file is loaded and contains pointers
	// to all of the font objects used within the grid.
	CFont* ModifyFont( CFont *pBaseFont, CString sFaceName, CString sFontFamily = _T(""), int nSize = 0, int bBold = -1, int bItalic = -1, int bUnderline = -1, int nCharSet = 0 );
	CFont* CreateFont( CString faceName, int nSize, BYTE bFontFamily = 0, BOOL bBold = FALSE, BOOL bItalic = FALSE, BOOL bUnderline = FALSE );
	CFont* CreateFont( int nHeight, int nWidth, int nEscapement, int nOrientation, int nWeight, BYTE bItalic, BYTE bUnderline, BYTE cStrikeOut, BYTE nCharSet, BYTE nOutPrecision, BYTE nClipPrecision, BYTE nQuality, BYTE nPitchAndFamily, LPCTSTR lpszFacename );
	CFont* CreateFontIndirect( LOGFONT newLogFont );

protected:
	// Generic helper functions
	short CompareCellStyles( CUGCell *pCell1, CUGCell *pCell2 );
	COXParserElement* FindStylesElement( COXParserElement *pCurElement );
	CString AddStyle( COXParserElement *pStylesElement, CUGCell *pCell, short changeMask );

	int PopulateCellFromStyle( CString styleID, COXParserElement *pStyles, CUGCell *pCell );
	void GetAlignmentStyle( COXParserElement *pStyle, CUGCell *pCell );
	void GetFontStyle( COXParserElement *pStyle, CUGCell *pCell );
	void GetInteriorStyle( COXParserElement *pStyle, CUGCell *pCell );
	void GetNumberFormat( COXParserElement *pStyle, CUGCell *pCell );

	// Color notation conversion functions
	COLORREF HexToColorref( CString hexColor );
	CString ColorrefToHex( COLORREF color );

	// Link list that stores information on all styles added through
	// the AddStyle function.  The list is used to make sure that two
	// identical style elements are not added to the XML file.
	struct _tagAddedStyles
	{
		CString styleID;
		CString style_hAlign;
		CString style_vAlign;
		CString style_fontName;
		CString style_fontFamily;
		CString style_charSet;
		CString style_fontSize;
		CString style_fontBold;
		CString style_fontIatalic;
		CString style_fontUnderline;
		CString style_fontColor;
		CString style_backColor;
		CString style_backPattern;
		CString style_numberFormat;
		CString style_multiRowCell;	// TD v 7.2 - ref kvt
		_tagAddedStyles *next;
	} *m_pAddedStyles;

	int PopulateStyleStruct( _tagAddedStyles *pStyle, CUGCell *pCell, short changeMask );
	int CompareStyles( _tagAddedStyles* pLoopStyle, _tagAddedStyles* pNewStyle );

protected:
	// Member functions related to loading the XML file
	int LoadTableInfo( COXParserElement *pTableElement );
	int LoadColInfo( COXParserElement *pColElement, int &nColIndex );
	int LoadRowInfo( COXParserElement *pRowElement, int &nRowIndex );
	int LoadRowData( COXParserElement *pRowElement, long rowNum );
	// Member functions related to saving the XML file
	int GatherWorksheetInfo( COXParserElement *pWorksheetElement );
	int GatherTableInfo( COXParserElement *pTableElement );
	int GatherColumnInfo( COXParserElement *pTableElement );
	int GatherRowInfo( COXParserElement *pTableElement );
	COXParserElement* GatherRowData( COXParserElement *pTableElement, long nRowNum );
};

#endif // !defined(AFX_XMLPARSER_H__9018A8B5_8AAB_4D9B_9172_8F1A836A44A1__INCLUDED_)
