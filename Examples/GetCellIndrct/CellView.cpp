// CellView.cpp : implementation file
//

#include "stdafx.h"
#include "Ex7.h"
#include "CellView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUGCellPropViewer dialog

// helper functions
CString Color2String(COLORREF col){
	CString temp;
	temp.Format("Red %d, Green %d, Blue %d", (col&0x0000FF), (col&0x00FF00)>>8, (col&0xFF0000)>>16);
	return temp;
}

CString Font2String(CFont* font){
	// Get the name of the font being assigned for the cell
	// from the font log
	if(font==NULL)
		return _T("None Assigned");

	LOGFONT lf;
	font->GetLogFont(&lf);
	return lf.lfFaceName;
}

/**************************************************
Dialog constructor:
Parameter:
	CUGCell cell	the cell object to display the properties for
	CWnd *pParent  Pointerto the parent window

***************************************************/

CUGCellPropViewer::CUGCellPropViewer(CUGCell& cell, CWnd* pParent /*=NULL*/)
	: CDialog(CUGCellPropViewer::IDD, pParent)
{

	// Lets test for the properties if they are set or not
	// Look in ugdefine.h for the grid constants names
	
	if(cell.IsPropertySet(UGCELL_FONT_SET))
		m_font = Font2String(cell.GetFont());
	else
		m_font = _T("None Assigned");

	if(cell.IsPropertySet(UGCELL_BITMAP_SET))
		m_bitmap = _T("Assigned");
	else
		m_bitmap = _T("None Assigned");

	if(cell.IsPropertySet(UGCELL_TEXTCOLOR_SET))
		m_textColor = Color2String(cell.GetTextColor());
	else
		m_textColor = _T("Not Set");

	if(cell.IsPropertySet(UGCELL_BACKCOLOR_SET))
		m_backColor = Color2String(cell.GetBackColor());
	else
		m_backColor = _T("Not Set");

	if(cell.IsPropertySet(UGCELL_HBACKCOLOR_SET))
		m_hbackColor = Color2String(cell.GetHBackColor());
	else
		m_hbackColor = _T("Not Set");
	if(cell.IsPropertySet(UGCELL_HTEXTCOLOR_SET))
		m_htextColor = Color2String(cell.GetHTextColor());
	else
		m_htextColor =_T("Not Set");
	cell.GetText(&m_text);
	

	if(cell.IsPropertySet(UGCELL_ALIGNMENT_SET)){
		short align = cell.GetAlignment();
		if(align&UG_ALIGNRIGHT)
			m_horizAlign = _T("Right");
		else if(align&UG_ALIGNCENTER)
			m_horizAlign = _T("Center");
		else
			m_horizAlign = _T("Left");

		if(align&UG_ALIGNBOTTOM)
			m_vertAlign = _T("Bottom");
		else if(align&UG_ALIGNVCENTER)
			m_vertAlign = _T("Center");
		else
			m_vertAlign = _T("Top");

	}
	else{
		m_horizAlign =_T("Not Set");
		m_vertAlign =_T("Not Set");
	}
}


void CUGCellPropViewer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUGCellPropViewer)
	DDX_Text(pDX, IDC_BACK_COLOR, m_backColor);
	DDX_Text(pDX, IDC_FONT, m_font);
	DDX_Text(pDX, IDC_BITMAP, m_bitmap);
	DDX_Text(pDX, IDC_HIGH_BACK_COL, m_hbackColor);
	DDX_Text(pDX, IDC_HIGH_TEXT_COLOR, m_htextColor);
	DDX_Text(pDX, IDC_HORIZ_ALIGN, m_horizAlign);
	DDX_Text(pDX, IDC_TEXT, m_text);
	DDX_Text(pDX, IDC_TEXT_COLOR, m_textColor);
	DDX_Text(pDX, IDC_VERT_ALIGN, m_vertAlign);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUGCellPropViewer, CDialog)
	//{{AFX_MSG_MAP(CUGCellPropViewer)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUGCellPropViewer message handlers
