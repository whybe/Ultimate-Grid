// TextDlg.h : header file
//

#if !defined(AFX_TEXTDLG_H__C13D360B_013D_11D2_88AA_0080C859A484__INCLUDED_)
#define AFX_TEXTDLG_H__C13D360B_013D_11D2_88AA_0080C859A484__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "MyGrid.h"

/////////////////////////////////////////////////////////////////////////////
// CTextDlg dialog

class CTextDlg : public CDialog
{
// Construction
public:
	CTextDlg(CWnd* pParent = NULL);	// standard constructor
	~CTextDlg();
// Dialog Data
	//{{AFX_DATA(CTextDlg)
	enum { IDD = IDD_TEXT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	CMyGrid m_grid;

	// Generated message map functions
	//{{AFX_MSG(CTextDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCheckxp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTDLG_H__C13D360B_013D_11D2_88AA_0080C859A484__INCLUDED_)
