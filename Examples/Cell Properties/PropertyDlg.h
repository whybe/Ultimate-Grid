#pragma once
#include "UGCtrl.h"
#include "afxwin.h"

// CPropertyDlg dialog

class CPropertyDlg : public CDialog
{
	DECLARE_DYNAMIC(CPropertyDlg)

public:
	CPropertyDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPropertyDlg();

	void UseCell( CUGCell *pCell ) { m_pCell = pCell; }
	void UseCtrl( CUGCtrl *pCtrl ) { m_pCtrl = pCtrl; }

// Dialog Data
	enum { IDD = IDD_PROP_DLG };

protected:
	CUGCell *m_pCell;
	CUGCtrl *m_pCtrl;

	int m_alignmentSel;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void ShowValueInformation();
	void ShowRGBValue( int nID, COLORREF color );
	void ShowFontInfo ();
	BOOL ShowFontDlg( LOGFONT &selectedLogFont );

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedFontBrowse();
	afx_msg void OnBnClickedTextBrowse();
	afx_msg void OnBnClickedBackBrowse();
	afx_msg void OnBnClickedHtextBrowse();
	afx_msg void OnBnClickedHbackBrowse();
	afx_msg void OnCbnSelchangeDatatype();
	afx_msg void OnCbnSelchangeCelltype();
	afx_msg void OnCbnSelchangeBitmap();
	afx_msg void OnAlignmentChange( UINT nID );
};
