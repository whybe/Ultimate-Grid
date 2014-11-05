// ResizeGridToDataDlg.h : header file
//

#if !defined(AFX_RESIZEGRIDTODATADLG_H__5601EAC3_F327_4875_A518_46E97F72CFB2__INCLUDED_)
#define AFX_RESIZEGRIDTODATADLG_H__5601EAC3_F327_4875_A518_46E97F72CFB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CResizeGridToDataDlg dialog
#include "MyCug.h"

class CResizeGridToDataDlg : public CDialog
{
// Construction
public:
	CResizeGridToDataDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CResizeGridToDataDlg)
	enum { IDD = IDD_RESIZEGRIDTODATA_DIALOG };
	BOOL	m_XPStyle;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResizeGridToDataDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	MyCug m_grid;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CResizeGridToDataDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnResizeGrid();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnXPStyle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESIZEGRIDTODATADLG_H__5601EAC3_F327_4875_A518_46E97F72CFB2__INCLUDED_)
