// PropertyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Cell Properties.h"
#include "PropertyDlg.h"


// CPropertyDlg dialog

IMPLEMENT_DYNAMIC(CPropertyDlg, CDialog)
CPropertyDlg::CPropertyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPropertyDlg::IDD, pParent)
{
	m_pCell = NULL;
	m_pCtrl = NULL;
	m_alignmentSel = -1;
}

CPropertyDlg::~CPropertyDlg()
{
}

void CPropertyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_ALIGN_TL, m_alignmentSel);
}


BEGIN_MESSAGE_MAP(CPropertyDlg, CDialog)
	ON_BN_CLICKED(IDC_FONT_BROWSE, OnBnClickedFontBrowse)
	ON_BN_CLICKED(IDC_TEXT_BROWSE, OnBnClickedTextBrowse)
	ON_BN_CLICKED(IDC_BACK_BROWSE, OnBnClickedBackBrowse)
	ON_BN_CLICKED(IDC_HTEXT_BROWSE, OnBnClickedHtextBrowse)
	ON_BN_CLICKED(IDC_HBACK_BROWSE, OnBnClickedHbackBrowse)
	ON_CBN_SELCHANGE(IDC_DATATYPE, OnCbnSelchangeDatatype)
	ON_CBN_SELCHANGE(IDC_CELLTYPE, OnCbnSelchangeCelltype)
	ON_CBN_SELCHANGE(IDC_BITMAP, OnCbnSelchangeBitmap)
	ON_COMMAND_RANGE(IDC_ALIGN_TL, IDC_ALIGN_BR, OnAlignmentChange)
END_MESSAGE_MAP()

// CPropertyDlg message handlers

BOOL CPropertyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Initialize the dialog controls
	// add options for the Data Type droplist
	CComboBox *pCombo = (CComboBox*)GetDlgItem( IDC_DATATYPE );
	pCombo->AddString( "String" );
	pCombo->AddString( "Numeric" );
	pCombo->AddString( "Boolean" );
	pCombo->AddString( "Date/Time" );
	pCombo->AddString( "Currency" );
	// add options to the Cell types droplist
	pCombo = (CComboBox*)GetDlgItem( IDC_CELLTYPE );
	pCombo->AddString( "Normal" );
	pCombo->AddString( "Drop-list" );
	pCombo->AddString( "Check-box" );
	pCombo->AddString( "Arrow" );
	// Add options to the bitmap droplist
	pCombo = (CComboBox*)GetDlgItem( IDC_BITMAP );
	pCombo->AddString( "<none>" );
	pCombo->AddString( "Check mark" );
	pCombo->AddString( "Dundas logo" );

	// Load cell's properties
	// cell's value and data type
	ShowValueInformation();
	// cell type information
	((CComboBox*)GetDlgItem( IDC_CELLTYPE ))->SetCurSel( m_pCell->GetCellType());
	// Bitmap
	pCombo = (CComboBox*)GetDlgItem( IDC_BITMAP );
	if ( m_pCell->GetBitmap() == NULL )
		pCombo->SetCurSel( 0 );
	else if ( m_pCell->GetBitmap() == m_pCtrl->GetBitmap( 0 ))
		pCombo->SetCurSel( 1 );
	else
		pCombo->SetCurSel( 2 );
	// Alignement
	if ( m_pCell->GetPropertyFlags()&UGCELL_ALIGNMENT_SET )
	{
		if ( m_pCell->GetAlignment()&UG_ALIGNLEFT )
			m_alignmentSel = 0;
		else if ( m_pCell->GetAlignment()&UG_ALIGNCENTER )
			m_alignmentSel = 1;
		else
			m_alignmentSel = 2;

		if ( m_pCell->GetAlignment()&UG_ALIGNTOP )
			m_alignmentSel += 0;
		else if ( m_pCell->GetAlignment()&UG_ALIGNVCENTER )
			m_alignmentSel += 3;
		else if ( m_pCell->GetAlignment()&UG_ALIGNBOTTOM )
			m_alignmentSel += 6;

		UpdateData( FALSE );
	}
	// Font
	ShowFontInfo();
	// Colors
	ShowRGBValue( IDC_TEXT_COLOR, m_pCell->GetTextColor());
	ShowRGBValue( IDC_HTEXT_COLOR, m_pCell->GetHTextColor());
	ShowRGBValue( IDC_BACK_COLOR, m_pCell->GetBackColor());
	ShowRGBValue( IDC_HBACK_COLOR, m_pCell->GetHBackColor());

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CPropertyDlg::OnBnClickedFontBrowse()
{
	LOGFONT selectedLogFont;

	if ( ShowFontDlg( selectedLogFont ) == IDOK )
	{	// get the font new information.
		m_pCell->SetFont( m_pCtrl->GetFont( m_pCtrl->AddFontIndirect( selectedLogFont )));
		// update the dialog control to show new font information
		ShowFontInfo();
	}
}

void CPropertyDlg::OnBnClickedTextBrowse()
{
	CColorDialog colorDlg( m_pCell->GetTextColor());

	if ( colorDlg.DoModal() == IDOK ) 
	{
		m_pCell->SetTextColor( colorDlg.GetColor());
		// update the RGB value displayed on the dialog
		ShowRGBValue( IDC_TEXT_COLOR, colorDlg.GetColor());
	}
}

void CPropertyDlg::OnBnClickedHtextBrowse()
{
	CColorDialog colorDlg( m_pCell->GetHTextColor());

	if ( colorDlg.DoModal() == IDOK ) 
	{
		m_pCell->SetTextColor( colorDlg.GetColor());
		// update the RGB value displayed on the dialog
		ShowRGBValue( IDC_HTEXT_COLOR, colorDlg.GetColor());
	}
}

void CPropertyDlg::OnBnClickedBackBrowse()
{
	CColorDialog colorDlg( m_pCell->GetBackColor());

	if ( colorDlg.DoModal() == IDOK ) 
	{
		m_pCell->SetBackColor( colorDlg.GetColor());
		// update the RGB value displayed on the dialog
		ShowRGBValue( IDC_BACK_COLOR, colorDlg.GetColor());
	}
}

void CPropertyDlg::OnBnClickedHbackBrowse()
{
	CColorDialog colorDlg( m_pCell->GetHBackColor());

	if ( colorDlg.DoModal() == IDOK ) 
	{
		m_pCell->SetBackColor( colorDlg.GetColor());
		// update the RGB value displayed on the dialog
		ShowRGBValue( IDC_HBACK_COLOR, colorDlg.GetColor());
	}
}

void CPropertyDlg::ShowValueInformation()
{
	SetDlgItemText( IDC_VALUE, m_pCell->GetText());

	CComboBox *pCombo = (CComboBox*)GetDlgItem( IDC_DATATYPE );

	switch( m_pCell->GetDataType())
	{
		case UGCELLDATA_STRING:
			pCombo->SelectString( -1, "String" );
			break;
		case UGCELLDATA_NUMBER:
			pCombo->SelectString( -1, "Numeric" );
			break;
		case UGCELLDATA_BOOL:
			pCombo->SelectString( -1, "Boolean" );
			break;
		case UGCELLDATA_TIME:	
			pCombo->SelectString( -1, "Date/Time" );
			break;
		case UGCELLDATA_CURRENCY:
			pCombo->SelectString( -1, "Currency" );
			break;
		default:
			pCombo->SetCurSel( 0 );
			break;
	}
}

void CPropertyDlg::ShowRGBValue( int nID, COLORREF color )
{
	CString wndText;
	wndText.Format( " RGB(%d,%d,%d)", GetRValue( color ),
									GetGValue( color ),
									GetBValue( color ));
	SetDlgItemText( nID, wndText );
}

void CPropertyDlg::ShowFontInfo()
{
	if ( m_pCell->GetPropertyFlags()&UGCELL_FONT_SET )
	{
		CString fontInfo;
		LOGFONT lgFont;
		CFont *pFont = m_pCell->GetFont();
		pFont->GetLogFont( &lgFont );

		CDC dc;
		float nSize = (float)lgFont.lfHeight;
		// get display information
		dc.CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
		float yPerInch = (float)dc.GetDeviceCaps(LOGPIXELSY);

		CString bold = (lgFont.lfWeight == 400 ? _T("Regular") : _T("Bold"));
		CString italic = (lgFont.lfItalic == 0 ? _T("Normal") : _T("Italic"));

		fontInfo.Format( "%s, %.0f", lgFont.lfFaceName,
									-( nSize * 72 / yPerInch ));
		GetDlgItem( IDC_FONT_INFO )->SetWindowText( fontInfo + ", " + bold + ", " + italic );
	}
	else
	{
		GetDlgItem( IDC_FONT_INFO )->SetWindowText( "< Font is not set >" );
	}
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
BOOL CPropertyDlg::ShowFontDlg( LOGFONT &selectedLogFont )
{
	BOOL retVal = FALSE;
	LOGFONT tempLogFont;
	CFont *font = m_pCell->GetFont();
	CFontDialog *fontDlg;

	if ( font != NULL )
	{
		font->GetLogFont( &tempLogFont );
		fontDlg = new CFontDialog( &tempLogFont );
	}
	else
	{
		fontDlg = new CFontDialog;
	}

	
	fontDlg->m_cf.rgbColors = m_pCell->GetTextColor();

	if ( fontDlg->DoModal() == IDOK )
	{
		fontDlg->GetCurrentFont( &selectedLogFont );

		retVal = TRUE;
	}

	delete fontDlg;
	return retVal;
}

void CPropertyDlg::OnCbnSelchangeDatatype()
{
	CComboBox *pCombo = (CComboBox*)GetDlgItem( IDC_DATATYPE );

	switch( pCombo->GetCurSel())
	{
	case 0: // String
		m_pCell->SetDataType( UGCELLDATA_STRING );
		break;
	case 1: // Numeric
		m_pCell->SetDataType( UGCELLDATA_NUMBER );
		break;
	case 2: // Boolean
		m_pCell->SetDataType( UGCELLDATA_BOOL );
		break;
	case 3: // Date/Time
		m_pCell->SetDataType( UGCELLDATA_TIME );
		break;
	case 4: // Currency
		m_pCell->SetDataType( UGCELLDATA_CURRENCY );
		break;
	}

	ShowValueInformation();
}

void CPropertyDlg::OnCbnSelchangeCelltype()
{
	CComboBox *pCombo = (CComboBox*)GetDlgItem( IDC_CELLTYPE );

	switch( pCombo->GetCurSel())
	{
	case 0: // Normal
		m_pCell->SetLabelText( "" );
		m_pCell->SetCellType( UGCT_NORMAL );
		break;
	case 1: // Drop-list
		m_pCell->SetLabelText( "" );
		m_pCell->SetCellType( UGCT_DROPLIST );
		break;
	case 2: // Check-box
		m_pCell->SetLabelText( m_pCell->GetText());
		m_pCell->SetCellType( UGCT_CHECKBOX );
		break;
	case 3: // Arrow
		m_pCell->SetLabelText( "" );
		m_pCell->SetCellType( UGCT_ARROW );
		break;
	}
}

void CPropertyDlg::OnCbnSelchangeBitmap()
{
	CComboBox *pCombo = (CComboBox*)GetDlgItem( IDC_BITMAP );

	switch( pCombo->GetCurSel())
	{
	case 0:	// None
		m_pCell->SetBitmap( NULL );
		break;
	case 1:	// check mark
		m_pCell->SetBitmap( m_pCtrl->GetBitmap( 0 ));
		break;
	case 2:	// Dundas logo
		m_pCell->SetBitmap( m_pCtrl->GetBitmap( 1 ));
		break;
	}
}

void CPropertyDlg::OnAlignmentChange( UINT nID )
{
	UpdateData( TRUE );

	switch( m_alignmentSel )
	{
	case 0:
		m_pCell->SetAlignment( UG_ALIGNLEFT|UG_ALIGNTOP );
		break;
	case 1:
		m_pCell->SetAlignment( UG_ALIGNCENTER|UG_ALIGNTOP );
		break;
	case 2:
		m_pCell->SetAlignment( UG_ALIGNRIGHT|UG_ALIGNTOP );
		break;
	case 3:
		m_pCell->SetAlignment( UG_ALIGNLEFT|UG_ALIGNVCENTER );
		break;
	case 4:
		m_pCell->SetAlignment( UG_ALIGNCENTER|UG_ALIGNVCENTER );
		break;
	case 5:
		m_pCell->SetAlignment( UG_ALIGNRIGHT|UG_ALIGNVCENTER );
		break;
	case 6:
		m_pCell->SetAlignment( UG_ALIGNLEFT|UG_ALIGNBOTTOM );
		break;
	case 7:
		m_pCell->SetAlignment( UG_ALIGNCENTER|UG_ALIGNBOTTOM );
		break;
	case 8:
		m_pCell->SetAlignment( UG_ALIGNRIGHT|UG_ALIGNBOTTOM );
		break;
	}
}