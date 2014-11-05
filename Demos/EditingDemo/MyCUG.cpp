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
	m_fontsList = NULL;
}

MyCug::~MyCug()
{
	// clean up possible fonts allocated by the user
	_tagFonts *pFont, *pTemp;
	pFont = m_fontsList;
	while ( pFont != NULL )
	{
		pTemp = pFont->next;
		delete pFont;
		pFont = pTemp;
	}
}

/////////////////////////////////////////////////////////////////////////////
//	CreateFont
//		Function is used to create new font object and add it to the link
//		list of fonts in use
CFont* MyCug::CreateFont( int nHeight, int nWidth, int nEscapement, int nOrientation, int nWeight, BYTE bItalic, BYTE bUnderline, BYTE cStrikeOut, BYTE nCharSet, BYTE nOutPrecision, BYTE nClipPrecision, BYTE nQuality, BYTE nPitchAndFamily, LPCTSTR lpszFacename )
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
CFont* MyCug::CreateFontIndirect( LOGFONT newLogFont )
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
BOOL MyCug::ShowFontDlg( CUGCell &cell, LOGFONT &selectedLogFont, COLORREF &textColor )
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
	AdjustComponentSizes();
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////
//	OnSetup
//		This function is called just after the grid window 
//		is created or attached to a dialog item.
//		It can be used to initially setup the grid
void MyCug::OnSetup()
{
	CUGCell cell;
	int cols = 8,
		rows = 45;
	int usingCol;
	int usingRow;

	// create a font and set it as Grid Default
	GetGridDefault( &cell );
	m_defFont = CreateFont( 14, 0, 0, 0, 200, 0, 0, 0, 0, 0, 0, 0, 0, "Arial" );
	cell.SetFont( m_defFont );
	SetGridDefault( &cell );
	// create a font and set it as Heading Default
	GetHeadingDefault( &cell );
	cell.SetFont( CreateFont( -13, 0, 0, 0, 200, 0, 0, 0, 0, 0, 0, 0, 0, "Arial" ));
	SetHeadingDefault( &cell );
	// add more default fonts
	m_smallFont = CreateFont( -9, 0, 0, 0, 200, 0, 0, 0, 0, 0, 0, 0, 0, "Arial" );
	m_largeFont = CreateFont( -16, 0, 0, 0, 200, 0, 0, 0, 0, 0, 0, 0, 0, "Times New Roman" );

	// add celltypes
	AddCellType( &m_radioType );
	AddCellType( &m_ellipType );
	AddCellType( &m_labeledType );
	m_labeledType.SetLabelFont(12,300,"Arial",RGB(0,0,164));
	AddCellType( &m_marqueeType );

	// SetDoubleBufferMode( TRUE );
	SetUserSizingMode( 2 );
	SetVScrollMode( UG_SCROLLTRACKING );
	SetHScrollMode( UG_SCROLLTRACKING );
	SetDefColWidth( 80 );
	SetSH_Width( MY_SEPARATOR );
	SetTH_Height( MY_SEPARATOR );

	GetHeadingDefault( &cell );
	cell.SetBackColor( RGB(200,150,150));
	cell.SetBorder( 0 );
	SetHeadingDefault( &cell );

	GetGridDefault( &cell );
	cell.SetReadOnly( TRUE );
	SetGridDefault( &cell );

	SetNumberRows( rows );
	SetNumberCols( cols );

	// normal edit controls
	usingCol = 0;
	usingRow = 0;
	JoinCells( usingCol, usingRow, usingCol + GetNumberCols() - 1, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "Default edit control respects cell's celltype, font size and type" );
	cell.SetBackColor( LABEL_BACK );
	SetCell( usingCol, usingRow, &cell );
	// resize 'separator' rows
	SetRowHeight( usingRow + 1, MY_SEPARATOR );

	GetCell( 0, 2, &cell );
	cell.SetReadOnly( FALSE );
	QuickSetRange( 0, 2, cols - 1, 5, &cell );

	// edit with drop list cell type
	usingCol = 0;
	usingRow = 2;
	JoinCells( usingCol, usingRow, usingCol + 1, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "Using Default font" );
	cell.SetCellType( UGCT_DROPLIST );
	cell.SetCellTypeEx( UGCT_DROPLISTHIDEBUTTON );
	cell.SetReadOnly( FALSE );
	cell.SetLabelText( "Using Small Font\nUsing Default font\nUsing Large Font\n" );
	SetCell( usingCol, usingRow, &cell );

	// edit with ellipsis cell type
	usingCol = 2;
	usingRow = 2;
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "Enter text ..." );
	cell.SetCellType( m_ellipType.GetID());
	SetCell( usingCol, usingRow, &cell );

	// edit with long, cell over lapping text
	usingCol = 0;
	usingRow = 3;
	QuickSetText( usingCol, usingRow, "You can even edit a long (cell overlapping) string." );

	// edit cells with multiline text
	usingCol = 4;
	usingRow = 2;
	JoinCells( usingCol, usingRow, usingCol + 1, usingRow + 2 );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "This cell contains multiline text, which provides multiline edit." );
	cell.SetCellTypeEx( UGCT_NORMALMULTILINE );
	SetCell( usingCol, usingRow, &cell );

	// edit cells with multiline text
	usingCol = 6;
	usingRow = 2;
	JoinCells( usingCol, usingRow, usingCol + 1, usingRow + 2 );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "This cell contains multiline text, which provides multiline edit." );
	cell.SetCellType( m_ellipType.GetID());
	cell.SetLabelText( "Small Font\nDefault font\nLarge Font\n" );
	cell.SetCellTypeEx( UGCT_NORMALMULTILINE );
	SetCell( usingCol, usingRow, &cell );

	// edit with label cell type
	usingCol = 0;
	usingRow = 4;
	JoinCells( usingCol, usingRow, usingCol + 1, usingRow + 1 );
	GetCell( usingCol, usingRow, &cell );
	cell.SetLabelText( "User Name:" );
	cell.SetText( "Enter your name here." );
	cell.SetCellType( m_labeledType.GetID());
	SetCell( usingCol, usingRow, &cell );

	// edit with marquee cell type
	usingCol = 2;
	usingRow = 4;
	JoinCells( usingCol, usingRow, usingCol + 1, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "Enter your text here ..." );
	cell.SetCellType( m_marqueeType.GetID());
	SetCell( usingCol, usingRow, &cell );

	// customizing user input by changing styles on edit control
	usingCol = 0;
	usingRow = 7;
	JoinCells( usingCol, usingRow, usingCol + GetNumberCols() - 1, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "Default edit controls also allow us to customize user's editing experience by:" );
	cell.SetBackColor( LABEL_BACK );
	SetCell( usingCol, usingRow, &cell );
	// resize 'separator' rows
	SetRowHeight( usingRow - 1, MY_SEPARATOR );
	SetRowHeight( usingRow + 1, MY_SEPARATOR );

	// make sure that value entered by the user is always in upper case
	usingCol = 0;
	usingRow = 9;
	JoinCells( usingCol, usingRow, usingCol + 1, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "Converting input to upper case:" );
	cell.SetBackColor( SUBLABEL_BACK );
	SetCell( usingCol, usingRow, &cell );

	GetCell( usingCol + 2, usingRow, &cell );
	cell.SetReadOnly( FALSE );
	cell.SetText( "TYPE HERE ..." );
	cell.SetParam( USE_UPPER );
	SetCell( usingCol + 2, usingRow, &cell );

	// make sure that value entered by the user is always in lower case
	usingCol = 4;
	usingRow = 9;
	JoinCells( usingCol, usingRow, usingCol + 1, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "Converting input to lower case:" );
	cell.SetBackColor( SUBLABEL_BACK );
	SetCell( usingCol, usingRow, &cell );

	GetCell( usingCol + 2, usingRow, &cell );
	cell.SetReadOnly( FALSE );
	cell.SetText( "type here ..." );
	cell.SetParam( USE_LOWER );
	SetCell( usingCol + 2, usingRow, &cell );

	// make sure that value is entered as a password
	usingCol = 0;
	usingRow = 10;
	JoinCells( usingCol, usingRow, usingCol + 1, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "Allowing password input:" );
	cell.SetBackColor( SUBLABEL_BACK );
	SetCell( usingCol, usingRow, &cell );

	GetCell( usingCol + 2, usingRow, &cell );
	cell.SetReadOnly( FALSE );
	cell.SetText( "Type here" );
	cell.SetParam( USE_PASSWORD );
	SetCell( usingCol + 2, usingRow, &cell );

	// make sure that value entered is right aligned
	usingCol = 0;
	usingRow = 11;
	JoinCells( usingCol, usingRow, usingCol + 1, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "Allowing aligned input:" );
	cell.SetBackColor( SUBLABEL_BACK );
	SetCell( usingCol, usingRow, &cell );

	GetCell( usingCol + 2, usingRow, &cell );
	cell.SetReadOnly( FALSE );
	cell.SetText( "Left aligned" );
	cell.SetAlignment( UG_ALIGNLEFT );
	SetCell( usingCol + 2, usingRow, &cell );

	cell.SetText( "Centered" );
	cell.SetAlignment( UG_ALIGNCENTER );
	SetCell( usingCol + 4, usingRow, &cell );

	cell.SetText( "Right aligned" );
	cell.SetAlignment( UG_ALIGNRIGHT );
	SetCell( usingCol + 6, usingRow, &cell );

	// processing user's input on normal edit controls
	usingCol = 0;
	usingRow = 13;
	JoinCells( usingCol, usingRow, usingCol + GetNumberCols() - 1, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "Ultimate Grid allow us to process user's input with various notifications." );
	cell.SetBackColor( LABEL_BACK );
	SetCell( usingCol, usingRow, &cell );
	// resize 'separator' rows
	SetRowHeight( usingRow - 1, MY_SEPARATOR );
	SetRowHeight( usingRow + 1, MY_SEPARATOR );

	// make sure that value entered is 4 chars long
	usingCol = 0;
	usingRow = 15;
	JoinCells( usingCol, usingRow, usingCol + 4, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "We can verify data as it is entered, for example to limit number of chars to 4:" );
	cell.SetBackColor( SUBLABEL_BACK );
	SetCell( usingCol, usingRow, &cell );

	GetCell( usingCol + 5, usingRow, &cell );
	cell.SetReadOnly( FALSE );
	cell.SetText( "<Type here>" );
	cell.SetParam( USE_CHARLIMIT );
	SetCell( usingCol + 5, usingRow, &cell );

	// make sure that value entered is 4 chars long
	usingCol = 0;
	usingRow = 16;
	JoinCells( usingCol, usingRow, usingCol + 4, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "or that the numeric value entered is under 500 (number < 500):" );
	cell.SetBackColor( SUBLABEL_BACK );
	SetCell( usingCol, usingRow, &cell );

	GetCell( usingCol + 5, usingRow, &cell );
	cell.SetReadOnly( FALSE );
	cell.SetText( "<Type here>" );
	cell.SetParam( USE_NUMLIMIT );
	SetCell( usingCol + 5, usingRow, &cell );

	// test data after it is entered
	usingCol = 0;
	usingRow = 17;
	JoinCells( usingCol, usingRow, usingCol + 4, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "We can also test user's input after it is completed, or force user's input:" );
	cell.SetBackColor( SUBLABEL_BACK );
	SetCell( usingCol, usingRow, &cell );

	GetCell( usingCol + 5, usingRow, &cell );
	cell.SetReadOnly( FALSE );
	cell.SetText( "<Type here>" );
	cell.SetParam( USE_FINISHTEST );
	SetCell( usingCol + 5, usingRow, &cell );

	// using other edit controls
	usingCol = 0;
	usingRow = 19;
	JoinCells( usingCol, usingRow, usingCol + GetNumberCols() - 1, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "The Ultimate Grid also allows us to use other edit controls when needed:" );
	cell.SetBackColor( LABEL_BACK );
	SetCell( usingCol, usingRow, &cell );
	// resize 'separator' rows
	SetRowHeight( usingRow - 1, MY_SEPARATOR );
	SetRowHeight( usingRow + 1, MY_SEPARATOR );

	// using default mask edit control
	usingCol = 0;
	usingRow = 21;
	JoinCells( usingCol, usingRow, usingCol + 4, usingRow + 1 );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "Just by setting a mask on a cell, the grid will change edit controls to use a mask edit.  "
				  "By default Ultimate Grid creates an instance of CUGMEdit to use as mask edit control." );
	cell.SetBackColor( SUBLABEL_BACK );
	cell.SetCellTypeEx( UGCT_NORMALMULTILINE );
	SetCell( usingCol, usingRow, &cell );

	JoinCells( usingCol + 5, usingRow, usingCol + 6, usingRow );
	GetCell( usingCol + 5, usingRow, &cell );
	cell.SetReadOnly( FALSE );
	cell.SetText( "<Select mask>" );
	cell.SetCellType( UGCT_DROPLIST );
	cell.SetReadOnly( FALSE );
	cell.SetParam( USE_SETMASK );
	SetCell( usingCol + 5, usingRow, &cell );

	JoinCells( usingCol + 5, usingRow + 1, usingCol + 6, usingRow + 1 );
	GetCell( usingCol + 5, usingRow + 1, &cell );
	cell.SetReadOnly( FALSE );
	cell.SetText( "<Type here>" );
	cell.SetMask( "" );
	SetCell( usingCol + 5, usingRow + 1, &cell );

	// using default mask edit control
	usingCol = 0;
	usingRow = 24;
	JoinCells( usingCol, usingRow, usingCol + 4, usingRow + 2 );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "The Ultimate Grid 5 also comes with a set of advanced edit control previosly only found "
				  "in Ultimate ToolBox.  We can now easily incorporate powerful controls like COXMaskEdit, "
				  "COXNumericEdit, and COXCurrencyEdit into our applications." );
	cell.SetBackColor( SUBLABEL_BACK );
	cell.SetCellTypeEx( UGCT_NORMALMULTILINE );
	SetCell( usingCol, usingRow, &cell );
	// resize 'separator' rows
	SetRowHeight( usingRow - 1, MY_SEPARATOR );
	SetRowHeight( usingRow + 3, MY_SEPARATOR );

	// using COXMaskEdit edit control
	usingCol = 0;
	usingRow = 28;
	JoinCells( usingCol, usingRow, usingCol + 4, usingRow + 1 );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "The COXMaskEdit works very similarly to the default mask edit control, to use it just "
				  "set a mask on a cell and inform the grid that you want to use different edit control." );
	cell.SetBackColor( SUBLABEL_BACK );
	cell.SetCellTypeEx( UGCT_NORMALMULTILINE );
	SetCell( usingCol, usingRow, &cell );
	// resize 'separator' rows
	SetRowHeight( usingRow + 2, MY_SEPARATOR );

	JoinCells( usingCol + 5, usingRow, usingCol + 7, usingRow );
	GetCell( usingCol + 5, usingRow, &cell );
	cell.SetReadOnly( FALSE );
	cell.SetText( "<Select mask>" );
	cell.SetCellType( UGCT_DROPLIST );
	cell.SetReadOnly( FALSE );
	cell.SetParam( USE_SETCOXMASK );
	SetCell( usingCol + 5, usingRow, &cell );

	JoinCells( usingCol + 5, usingRow + 1, usingCol + 7, usingRow + 1 );
	GetCell( usingCol + 5, usingRow + 1, &cell );
	cell.SetReadOnly( FALSE );
	cell.SetText( "<Type here>" );
	cell.SetMask( "" );
	cell.SetParam( USE_SETCOXMASK );
	SetCell( usingCol + 5, usingRow + 1, &cell );

	// using COXNumericEdit and COXCurrencyEdit edit controls
	usingCol = 0;
	usingRow = 31;
	JoinCells( usingCol, usingRow, usingCol + 4, usingRow + 1 );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "The COXNumericEdit and COXCurrencyEdit on the other hand allow us to provide additional "
				  "setup information that will drive the way the edit control will behave." );
	cell.SetBackColor( SUBLABEL_BACK );
	cell.SetCellTypeEx( UGCT_NORMALMULTILINE );
	SetCell( usingCol, usingRow, &cell );
	// resize 'separator' rows
	SetRowHeight( usingRow + 2, MY_SEPARATOR );

	// using COXNumericEdit edit control
	usingCol = 0;
	usingRow = 34;
	JoinCells( usingCol, usingRow, usingCol + 1, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "Using COXNumericEdit:" );
	cell.SetBackColor( SUBLABEL_BACK );
	SetCell( usingCol, usingRow, &cell );

	JoinCells( usingCol + 2, usingRow, usingCol + 3, usingRow );
	GetCell( usingCol + 2, usingRow, &cell );
	cell.SetReadOnly( FALSE );
	cell.SetText( "<Type here>" );
	cell.SetParam( USE_SETCOXNUMBER );
	SetCell( usingCol + 2, usingRow, &cell );

	// setup properties availabled for the numeric edic control
	usingCol = 0;
	usingRow = 35;
	JoinCells( usingCol, usingRow, usingCol + 2, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "Following are properties we can set." );
	cell.SetBackColor( LABEL_BACK );
	SetCell( usingCol, usingRow, &cell );

	// Decimal digit count
	usingRow = 36;
	// label
	JoinCells( usingCol, usingRow, usingCol + 1, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "Decimal digit count :" );
	cell.SetAlignment( UG_ALIGNRIGHT );
	cell.SetBackColor( SUBLABEL_BACK );
	SetCell( usingCol, usingRow, &cell );
	// property
	GetCell( usingCol + 2, usingRow, &cell );
	cell.SetCellType( UGCT_DROPLIST );
	cell.SetReadOnly( FALSE );
	cell.SetText( "<Disabled>" );
	cell.SetLabelText( "<Disabled>\n0\n1\n2\n3\n4\n5\n6\n" );
	cell.SetAlignment( UG_ALIGNCENTER );
	cell.SetParam( USE_SETCOXNUMBER );
	SetCell( usingCol + 2, usingRow, &cell );
	// Decimal Separator
	usingRow += 1;
	// label
	JoinCells( usingCol, usingRow, usingCol + 1, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "Decimal Separator :" );
	cell.SetAlignment( UG_ALIGNRIGHT );
	cell.SetBackColor( SUBLABEL_BACK );
	SetCell( usingCol, usingRow, &cell );
	// property
	GetCell( usingCol + 2, usingRow, &cell );
	cell.SetCellType( UGCT_DROPLIST );
	cell.SetReadOnly( FALSE );
	cell.SetText( "." );
	cell.SetLabelText( ".\n,\n|\n/\n" );
	cell.SetAlignment( UG_ALIGNCENTER );
	cell.SetParam( USE_SETCOXNUMBER );
	SetCell( usingCol + 2, usingRow, &cell );
	// Fractional digit count
	usingRow += 1;
	// label
	JoinCells( usingCol, usingRow, usingCol + 1, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "Fractional digit count :" );
	cell.SetAlignment( UG_ALIGNRIGHT );
	cell.SetBackColor( SUBLABEL_BACK );
	SetCell( usingCol, usingRow, &cell );
	// property
	GetCell( usingCol + 2, usingRow, &cell );
	cell.SetCellType( UGCT_DROPLIST );
	cell.SetReadOnly( FALSE );
	cell.SetText( "2" );
	cell.SetLabelText( "0\n1\n2\n3\n4\n5\n6\n" );
	cell.SetAlignment( UG_ALIGNCENTER );
	cell.SetParam( USE_SETCOXNUMBER );
	SetCell( usingCol + 2, usingRow, &cell );
	// Group Separator
	usingRow += 1;
	// label
	JoinCells( usingCol, usingRow, usingCol + 1, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "Group Separator :" );
	cell.SetAlignment( UG_ALIGNRIGHT );
	cell.SetBackColor( SUBLABEL_BACK );
	SetCell( usingCol, usingRow, &cell );
	// property
	GetCell( usingCol + 2, usingRow, &cell );
	cell.SetCellType( UGCT_DROPLIST );
	cell.SetReadOnly( FALSE );
	cell.SetText( "," );
	cell.SetLabelText( ".\n,\n|\n/\n" );
	cell.SetAlignment( UG_ALIGNCENTER );
	cell.SetParam( USE_SETCOXNUMBER );
	SetCell( usingCol + 2, usingRow, &cell );
	// Digits in group
	usingRow += 1;
	// label
	JoinCells( usingCol, usingRow, usingCol + 1, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "Digits in group :" );
	cell.SetAlignment( UG_ALIGNRIGHT );
	cell.SetBackColor( SUBLABEL_BACK );
	SetCell( usingCol, usingRow, &cell );
	// property
	GetCell( usingCol + 2, usingRow, &cell );
	cell.SetCellType( UGCT_DROPLIST );
	cell.SetReadOnly( FALSE );
	cell.SetText( "3" );
	cell.SetLabelText( "<Disabled>\n1\n2\n3\n4\n5\n6\n" );
	cell.SetAlignment( UG_ALIGNCENTER );
	cell.SetParam( USE_SETCOXNUMBER );
	SetCell( usingCol + 2, usingRow, &cell );
	// Negative Format
	usingRow += 1;
	// label
	JoinCells( usingCol, usingRow, usingCol + 1, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "Negative Format :" );
	cell.SetAlignment( UG_ALIGNRIGHT );
	cell.SetBackColor( SUBLABEL_BACK );
	SetCell( usingCol, usingRow, &cell );
	// property
	GetCell( usingCol + 2, usingRow, &cell );
	cell.SetCellType( UGCT_DROPLIST );
	cell.SetReadOnly( FALSE );
	cell.SetText( "-1.1" );
	cell.SetLabelText( "(1.1)\n-1.1\n- 1.1\n1.1-\n" );
	cell.SetAlignment( UG_ALIGNCENTER );
	cell.SetParam( USE_SETCOXNUMBER );
	SetCell( usingCol + 2, usingRow, &cell );
	// Show leading zero
	usingRow += 1;
	// label
	JoinCells( usingCol, usingRow, usingCol + 1, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "Show leading zero :" );
	cell.SetAlignment( UG_ALIGNRIGHT );
	cell.SetBackColor( SUBLABEL_BACK );
	SetCell( usingCol, usingRow, &cell );
	// property
	GetCell( usingCol + 2, usingRow, &cell );
	cell.SetCellType( UGCT_CHECKBOX );
	cell.SetCellTypeEx( UGCT_CHECKBOXUSEALIGN );
	cell.SetAlignment( UG_ALIGNCENTER|UG_ALIGNVCENTER );
	cell.SetBool( TRUE );
	cell.SetReadOnly( FALSE );
	cell.SetParam( USE_SETCOXNUMBER );
	SetCell( usingCol + 2, usingRow, &cell );

	// using COXCurrencyEdit edit control
	usingCol = 4;
	usingRow = 34;
	JoinCells( usingCol, usingRow, usingCol + 1, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "Using COXCurrencyEdit:" );
	cell.SetBackColor( SUBLABEL_BACK );
	SetCell( usingCol, usingRow, &cell );

	JoinCells( usingCol + 2, usingRow, usingCol + 3, usingRow );
	GetCell( usingCol + 2, usingRow, &cell );
	cell.SetReadOnly( FALSE );
	cell.SetText( "<Type here>" );
	cell.SetParam( USE_SETCOXCURRENCY );
	SetCell( usingCol + 2, usingRow, &cell );

	// setup properties availabled for the currency edic control
	usingCol = 4;
	usingRow += 1;
	JoinCells( usingCol, usingRow, usingCol + 2, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "Following are properties we can set." );
	cell.SetBackColor( LABEL_BACK );
	SetCell( usingCol, usingRow, &cell );

	// Decimal digit count
	usingRow += 1;
	// label
	JoinCells( usingCol, usingRow, usingCol + 1, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "Decimal digit count :" );
	cell.SetAlignment( UG_ALIGNRIGHT );
	cell.SetBackColor( SUBLABEL_BACK );
	SetCell( usingCol, usingRow, &cell );
	// property
	GetCell( usingCol + 2, usingRow, &cell );
	cell.SetCellType( UGCT_DROPLIST );
	cell.SetReadOnly( FALSE );
	cell.SetText( "<Disabled>" );
	cell.SetLabelText( "<Disabled>\n0\n1\n2\n3\n4\n5\n6\n" );
	cell.SetAlignment( UG_ALIGNCENTER );
	cell.SetParam( USE_SETCOXCURRENCY );
	SetCell( usingCol + 2, usingRow, &cell );
	// Decimal Separator
	usingRow += 1;
	// label
	JoinCells( usingCol, usingRow, usingCol + 1, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "Decimal Separator :" );
	cell.SetAlignment( UG_ALIGNRIGHT );
	cell.SetBackColor( SUBLABEL_BACK );
	SetCell( usingCol, usingRow, &cell );
	// property
	GetCell( usingCol + 2, usingRow, &cell );
	cell.SetCellType( UGCT_DROPLIST );
	cell.SetReadOnly( FALSE );
	cell.SetText( "." );
	cell.SetLabelText( ".\n,\n|\n/\n" );
	cell.SetAlignment( UG_ALIGNCENTER );
	cell.SetParam( USE_SETCOXCURRENCY );
	SetCell( usingCol + 2, usingRow, &cell );
	// Fractional digit count
	usingRow += 1;
	// label
	JoinCells( usingCol, usingRow, usingCol + 1, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "Fractional digit count :" );
	cell.SetAlignment( UG_ALIGNRIGHT );
	cell.SetBackColor( SUBLABEL_BACK );
	SetCell( usingCol, usingRow, &cell );
	// property
	GetCell( usingCol + 2, usingRow, &cell );
	cell.SetCellType( UGCT_DROPLIST );
	cell.SetReadOnly( FALSE );
	cell.SetText( "2" );
	cell.SetLabelText( "0\n1\n2\n3\n4\n5\n6\n" );
	cell.SetAlignment( UG_ALIGNCENTER );
	cell.SetParam( USE_SETCOXCURRENCY );
	SetCell( usingCol + 2, usingRow, &cell );
	// Group Separator
	usingRow += 1;
	// label
	JoinCells( usingCol, usingRow, usingCol + 1, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "Group Separator :" );
	cell.SetAlignment( UG_ALIGNRIGHT );
	cell.SetBackColor( SUBLABEL_BACK );
	SetCell( usingCol, usingRow, &cell );
	// property
	GetCell( usingCol + 2, usingRow, &cell );
	cell.SetCellType( UGCT_DROPLIST );
	cell.SetReadOnly( FALSE );
	cell.SetText( "," );
	cell.SetLabelText( ".\n,\n|\n/\n" );
	cell.SetAlignment( UG_ALIGNCENTER );
	cell.SetParam( USE_SETCOXCURRENCY );
	SetCell( usingCol + 2, usingRow, &cell );
	// Digits in group
	usingRow += 1;
	// label
	JoinCells( usingCol, usingRow, usingCol + 1, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "Digits in group :" );
	cell.SetAlignment( UG_ALIGNRIGHT );
	cell.SetBackColor( SUBLABEL_BACK );
	SetCell( usingCol, usingRow, &cell );
	// property
	GetCell( usingCol + 2, usingRow, &cell );
	cell.SetCellType( UGCT_DROPLIST );
	cell.SetReadOnly( FALSE );
	cell.SetText( "3" );
	cell.SetLabelText( "<Disabled>\n1\n2\n3\n4\n5\n6\n" );
	cell.SetAlignment( UG_ALIGNCENTER );
	cell.SetParam( USE_SETCOXCURRENCY );
	SetCell( usingCol + 2, usingRow, &cell );
	// Positive Format
	usingRow += 1;
	// label
	JoinCells( usingCol, usingRow, usingCol + 1, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "Positive Format :" );
	cell.SetAlignment( UG_ALIGNRIGHT );
	cell.SetBackColor( SUBLABEL_BACK );
	SetCell( usingCol, usingRow, &cell );
	// property
	GetCell( usingCol + 2, usingRow, &cell );
	cell.SetCellType( UGCT_DROPLIST );
	cell.SetReadOnly( FALSE );
	cell.SetText( "$1.1" );
	cell.SetLabelText( "$1.1\n1.1$\n$ 1.1\n1.1 $\n" );
	cell.SetAlignment( UG_ALIGNCENTER );
	cell.SetParam( USE_SETCOXCURRENCY );
	SetCell( usingCol + 2, usingRow, &cell );
	// Negative Format
	usingRow += 1;
	// label
	JoinCells( usingCol, usingRow, usingCol + 1, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "Negative Format :" );
	cell.SetAlignment( UG_ALIGNRIGHT );
	cell.SetBackColor( SUBLABEL_BACK );
	SetCell( usingCol, usingRow, &cell );
	// property
	GetCell( usingCol + 2, usingRow, &cell );
	cell.SetCellType( UGCT_DROPLIST );
	cell.SetReadOnly( FALSE );
	cell.SetText( "-$1.1" );
	cell.SetLabelText( "($1.1)\n-$1.1\n$-1.1\n$1.1-\n(1.1$)\n-1.1$\n1.1-$\n1.1$-\n" );
	cell.SetAlignment( UG_ALIGNCENTER );
	cell.SetParam( USE_SETCOXCURRENCY );
	SetCell( usingCol + 2, usingRow, &cell );
	// Currency name
	usingRow += 1;
	// label
	JoinCells( usingCol, usingRow, usingCol + 1, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "Currency name :" );
	cell.SetAlignment( UG_ALIGNRIGHT );
	cell.SetBackColor( SUBLABEL_BACK );
	SetCell( usingCol, usingRow, &cell );
	// property
	GetCell( usingCol + 2, usingRow, &cell );
	cell.SetCellType( UGCT_DROPLIST );
	cell.SetReadOnly( FALSE );
	cell.SetText( "$" );
	cell.SetLabelText( "$\n@\n€\n£\n" );
	cell.SetAlignment( UG_ALIGNCENTER );
	cell.SetParam( USE_SETCOXCURRENCY );
	SetCell( usingCol + 2, usingRow, &cell );
	// Show leading zero
	usingRow += 1;
	// label
	JoinCells( usingCol, usingRow, usingCol + 1, usingRow );
	GetCell( usingCol, usingRow, &cell );
	cell.SetText( "Show leading zero :" );
	cell.SetAlignment( UG_ALIGNRIGHT );
	cell.SetBackColor( SUBLABEL_BACK );
	SetCell( usingCol, usingRow, &cell );
	// property
	GetCell( usingCol + 2, usingRow, &cell );
	cell.SetCellType( UGCT_CHECKBOX );
	cell.SetCellTypeEx( UGCT_CHECKBOXUSEALIGN );
	cell.SetAlignment( UG_ALIGNCENTER|UG_ALIGNVCENTER );
	cell.SetBool( TRUE );
	cell.SetReadOnly( FALSE );
	cell.SetParam( USE_SETCOXCURRENCY );
	SetCell( usingCol + 2, usingRow, &cell );
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
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(processed);

	CUGCell cell;
	GetCellIndirect( col, row, &cell );

	if ( CString(cell.GetText()) == "<Type here>" )
	{
		cell.SetText( "" );
		SetCell( col, row, &cell );
	}

	StartEdit();
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
void MyCug::OnKeyDown(UINT *vcKey,BOOL processed)
{
	UNREFERENCED_PARAMETER(processed);

	if ( *vcKey == VK_TAB )
	{
		int col = GetCurrentCol();
		long row = GetCurrentRow();

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
		GotoCell( col, row );
	}
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

	CUGCell cell;
	GetCellIndirect( GetCurrentCol(), GetCurrentRow(), &cell );

	if ( CString(cell.GetText()) == "<Type here>" )
	{
		cell.SetText( "" );
		SetCell( GetCurrentCol(), GetCurrentRow(), &cell );
	}

	StartEdit( *vcKey );
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
void MyCug::OnSetCell(int col,long row,CUGCell *cell)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);

	if ( cell->GetParam() == USE_PASSWORD )
	{
		CString tempStr( '*', cell->GetTextLength());
		cell->SetText( tempStr );
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
	GetCellIndirect( col, row, &cell );
	CFont *selectedFont = NULL;
	LOGFONT selectedLogFont;
	COLORREF textColor(RGB(0,0,0));

	if ( cell.GetParam() == USE_SETMASK || cell.GetParam() == USE_SETCOXMASK )
	{
		// special handling of the drop list cell type to help setting mask
		if ( msg == UGCT_DROPLISTSTART && cell.GetParam() == USE_SETMASK )
		{	// populate the droplist
			CStringList *pStringList = (CStringList*)param;
			pStringList->RemoveAll();
			pStringList->AddTail( "(000)000-0000" );
			pStringList->AddTail( "(999)000-0000" );
			pStringList->AddTail( "(000)AAA-AAAA" );
			pStringList->AddTail( "L????L?000L0" );
			pStringList->AddTail( "L0L 0L0" );
			pStringList->AddTail( "00000-9999" );
			pStringList->AddTail( "???????????????" );
			pStringList->AddTail( "<no mask>" );
		}
		else if ( msg == UGCT_DROPLISTSTART && cell.GetParam() == USE_SETCOXMASK )
		{
			CStringList *pStringList = (CStringList*)param;
			pStringList->RemoveAll();
			pStringList->AddTail( _T("Digit Test: ###-####") ) ;
			pStringList->AddTail( _T("Decimal Test: ###.###.###.###") ) ;
			pStringList->AddTail( _T("Thousands Test: ##,###.##") ) ;
			pStringList->AddTail( _T("Time Test: ##:##") ) ;
			pStringList->AddTail( _T("Date Test: ##/##/####") ) ;
			pStringList->AddTail( _T("\\Alphanumeric Test: AAAAAAAAAA\\, AAAAAAAA") ) ;
			pStringList->AddTail( _T("\\Alphabetic Test: ????????????????") ) ;
			pStringList->AddTail( _T("Uppercase Test: >>>>>>> ????????") ) ;
			pStringList->AddTail( _T("Lowercase Test: <<<<<<< ????????") ) ;
			pStringList->AddTail( _T("Phone:(###)###-#### Ext:####") ) ;
			pStringList->AddTail( _T("AAA-#######")                  ) ;
			pStringList->AddTail( _T("&####-##-## ##\\:##\\:##")     ) ;
			pStringList->AddTail( _T("AAAAA")     );
			pStringList->AddTail( _T("<no mask>") );
		}
		else if ( msg == UGCT_DROPLISTSELECT )
		{
			CString *pTempStr = (CString*)param;
			GetCellIndirect( col, row + 1, &cell );

			if ( *pTempStr == "<no mask>" )
			{
				cell.SetMask( "" );
				cell.SetText( "<Type here>" );
			}
			else
			{
				cell.SetMask( *pTempStr );
				cell.SetText( *pTempStr );
			}

			SetCell( col, row + 1, &cell );
			RedrawCell( col, row + 1 );
		}
	}
	else if ( cell.GetParam() == USE_SETCOXCURRENCY || cell.GetParam() == USE_SETCOXNUMBER )
	{	// clear text in the cell that user can edit in.
		if ( ID == UGCT_DROPLIST && msg == UGCT_DROPLISTSELECT )
		{
			QuickSetText( col, 34, "<Type here>" );
			RedrawCell( col, 34 );
		}
	}
	else if ( ID == UGCT_DROPLIST && msg == UGCT_DROPLISTSELECTEX )
	{
		if ( param == 0 )
			QuickSetFont( col, row, m_smallFont );
		else if ( param == 1 )
			QuickSetFont( col, row, m_defFont );
		else if ( param == 2 )
			QuickSetFont( col, row, m_largeFont );

	}
	else if ( ID == m_ellipType.GetID() && msg == UGCT_ELLIPSISBUTTONCLICK )
	{
		textColor = cell.GetTextColor();

		if ( ShowFontDlg( cell, selectedLogFont, textColor ))
		{
			selectedFont = CreateFontIndirect( selectedLogFont );
			cell.SetFont( selectedFont );
			cell.SetTextColor( textColor );
			SetCell( col, row, &cell );
		}
		RedrawCell( col, row );
	}

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
int MyCug::OnEditStart(int col, long row,CWnd **edit)
{
	CUGCell cell;
	GetCellIndirect( col, row, &cell );
	DWORD dwStyle = 0;

	if ( cell.GetCellType() == UGCT_DROPLIST )
	{
		return FALSE;
	}
	else if ( cell.GetParam() == USE_SETCOXMASK )
	{
		if ( ! m_cutMaskEdit.GetSafeHwnd())
		{
			m_cutMaskEdit.Create( WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, COXMASK_ID );
			m_cutMaskEdit.m_ctrl = this;
		}

		*edit = &m_cutMaskEdit;

		return TRUE;
	}
	else if ( cell.GetParam() == USE_SETCOXNUMBER )
	{
		if ( ! m_cutNumeric.GetSafeHwnd())
		{
			m_cutNumeric.Create( WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, COXMASK_ID );
			m_cutNumeric.m_ctrl = this;
		}
		m_cutNumeric.SetDecimalSeparator( 'a' );
		m_cutNumeric.SetGroupSeparator( ' ' );

		// setup properties of the numeric edit control (located in rows 36 to 42)
		GetCell( col, 36, &cell );	// Decimal digit count
		if ( CString(cell.GetText()) != "<Disabled>" )
			m_cutNumeric.SetDecimalDigitCount((int)cell.GetNumber());
		else
			m_cutNumeric.SetDecimalDigitCount( -1 );
		GetCell( col, 37, &cell );	// Decimal Separator
		m_cutNumeric.SetDecimalSeparator( CString(cell.GetText()).GetAt(0));
		GetCell( col, 38, &cell );	// Fractional digit count
		m_cutNumeric.SetFractionalDigitCount((int)cell.GetNumber());
		GetCell( col, 39, &cell );	// Group Separator
		m_cutNumeric.SetGroupSeparator( CString(cell.GetText()).GetAt(0));
		GetCell( col, 40, &cell );	// Digits in group
		if ( CString(cell.GetText()) != "<Disabled>" )
			m_cutNumeric.SetGroupLength((int)cell.GetNumber());
		else
			m_cutNumeric.SetDecimalDigitCount( -1 );
		GetCell( col, 41, &cell );	// Negative Format
		m_cutNumeric.SetNegativeFormat( cell.GetText());
		GetCell( col, 42, &cell );	// Show leading zero
		m_cutNumeric.SetShowLeadingZero( cell.GetBool());

		*edit = &m_cutNumeric;
		return TRUE;
	}
	else if ( cell.GetParam() == USE_SETCOXCURRENCY )
	{
		if ( ! m_cutCurrency.GetSafeHwnd())
		{
			m_cutCurrency.Create( WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, COXMASK_ID );
			m_cutCurrency.m_ctrl = this;
		}
		m_cutCurrency.SetDecimalSeparator( 'a' );
		m_cutCurrency.SetGroupSeparator( ' ' );

		// setup properties of the currency edit control (located in rows 36 to 44)
		GetCell( col, 36, &cell );	// Decimal digit count
		if ( CString(cell.GetText()) != "<Disabled>" )
			m_cutCurrency.SetDecimalDigitCount((int)cell.GetNumber());
		else
			m_cutCurrency.SetDecimalDigitCount( -1 );
		GetCell( col, 37, &cell );	// Decimal Separator
		m_cutCurrency.SetDecimalSeparator( CString(cell.GetText()).GetAt(0));
		GetCell( col, 38, &cell );	// Fractional digit count
		m_cutCurrency.SetFractionalDigitCount((int)cell.GetNumber());
		GetCell( col, 39, &cell );	// Group Separator
		m_cutCurrency.SetGroupSeparator( CString(cell.GetText()).GetAt(0));
		GetCell( col, 40, &cell );	// Digits in group
		if ( CString(cell.GetText()) != "<Disabled>" )
			m_cutCurrency.SetGroupLength((int)cell.GetNumber());
		else
			m_cutCurrency.SetDecimalDigitCount( -1 );
		GetCell( col, 41, &cell );	// Positive Format
		m_cutCurrency.SetPositiveFormat( cell.GetText());
		GetCell( col, 42, &cell );	// Negative Format
		m_cutCurrency.SetNegativeFormat( cell.GetText());
		GetCell( col, 43, &cell );	// Currency name
		m_cutCurrency.SetCurrencyName( cell.GetText());
		GetCell( col, 44, &cell );	// Show leading zero
		m_cutCurrency.SetShowLeadingZero( cell.GetBool());

		*edit = &m_cutCurrency;
		return TRUE;
	}
	else if ( cell.GetParam() == USE_UPPER )
	{
		((CEdit*)*edit)->ModifyStyle( 0, ES_UPPERCASE );
	}
	else if ( cell.GetParam() == USE_LOWER )
	{
		((CEdit*)*edit)->ModifyStyle( 0, ES_LOWERCASE );
	}
	else if ( cell.GetParam() == USE_PASSWORD )
	{
		dwStyle = ES_PASSWORD;
	}
	else
	{
		((CEdit*)*edit)->ModifyStyle( ES_UPPERCASE, 0 );
		((CEdit*)*edit)->ModifyStyle( ES_LOWERCASE, 0 );
		((CEdit*)*edit)->ModifyStyle( ES_PASSWORD, 0 );
	}

	if ( cell.GetAlignment() & UG_ALIGNRIGHT )
		dwStyle |= ES_RIGHT;
	else if ( cell.GetAlignment() & UG_ALIGNCENTER )
		dwStyle |= ES_CENTER;

	if ( dwStyle != 0 )
	{
		if ( m_myCUGEdit.GetSafeHwnd())
			m_myCUGEdit.DestroyWindow();

		dwStyle |= WS_CHILD|WS_VISIBLE;
		// create the edit control with specified style
		m_myCUGEdit.Create( dwStyle, CRect(0,0,0,0), this, FLEXEDIT_ID );
		m_myCUGEdit.m_ctrl = this;		

		*edit = &m_myCUGEdit;
	}

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
int MyCug::OnEditVerify(int col, long row,CWnd *edit,UINT *vcKey)
{
	CUGCell cell;
	GetCellIndirect( col, row, &cell );

	// In OnSetup I have set USE_CHARLIMIT and USE_NUMLIMIT as parameters
	// on cells that I want to verify user's input.
	// - USE_CHARLIMIT is set on cells that I limit number of input characters to 4
	// - USE_NUMLIMIT is set on cells that only allow numbers with total value < 500

	if ( cell.GetParam() == USE_CHARLIMIT )
	{	// check if user has reached the 4 character limit
		if ( edit->GetWindowTextLength() >= 4 && *vcKey != 8 )
			return FALSE;
	}
	else if ( cell.GetParam() == USE_NUMLIMIT )
	{
		CString string;
		edit->GetWindowText( string );
		int pointPos = string.Find( "." );
		int fraction = 0;

		if ( pointPos >= 0 )
			fraction = string.GetLength() - pointPos;

		string += (char)*vcKey;
		
		// check if the character pressed is a numeric digit or a dot, and make
		// sure that the dot only is present once.  Also only allow two fractional
		// digits.
		if (( *vcKey >= 48 && *vcKey <= 57 && *vcKey == '.' && pointPos == -1 ) ||
			 fraction <= 2 || *vcKey == 8 )
		{
			int stSel, edSel;

			((CEdit*)edit)->GetSel( stSel, edSel );

			// make sure that the new value is under 500
			if (( atol( string ) > 500 ) && ( stSel == edSel ))
				return FALSE;
		}
		else
			return FALSE;
	}

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
int MyCug::OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag)
{
	UNREFERENCED_PARAMETER(edit);

	CString tempStr( string );
	CUGCell cell;
	GetCellIndirect( col, row, &cell );

	if ( cell.GetParam() == USE_PASSWORD )
	{
		QuickSetText( col + 2, row, "Entered password was: " + tempStr );
		RedrawCell( col + 2, row );
	}
	else if ( cell.GetParam() == USE_FINISHTEST && cancelFlag != TRUE )
	{
		if ( tempStr == "" )
		{
			MessageBox( "This field cannot be left blank\n"
						"please make sure a value is entered.\n"
						"Or hit ESC to cancel edit.", "Input error", MB_ICONEXCLAMATION );
			return FALSE;
		}
	}
	else if ( cell.GetParam() == USE_SETMASK && cancelFlag != TRUE )
	{
		GetCellIndirect( col, row + 1, &cell );
		cell.SetMask( string );
		cell.SetText( "<Type here>" );
		SetCell( col, row + 1, &cell );
		RedrawCell( col, row + 1 );
	}

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
int MyCug::OnEditContinue(int oldcol,long oldrow,int* newcol,long* newrow)
{
	UNREFERENCED_PARAMETER(oldcol);
	UNREFERENCED_PARAMETER(oldrow);

	CUGCell cell;
	GetCellIndirect( *newcol, *newrow, &cell );

	if ( CString(cell.GetText()) == "<Type here>" )
	{
		cell.SetText( "" );
		SetCell( *newcol, *newrow, &cell );
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	OnGetDefBackColor
//		Sent when the area behind the grid needs to be painted.
//	Params:
//		section - Id of the grid section that requested this color
//				  possible sections:
//						UG_TOPHEADING, UG_SIDEHEADING, UG_GRID
//	Return:
//		RGB value representing the color of choice
COLORREF MyCug::OnGetDefBackColor(int section)
{
	UNREFERENCED_PARAMETER(section);
	return RGB(255,255,255);
}
