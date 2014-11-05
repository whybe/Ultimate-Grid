// EditingDemoDlg.h : header file
//

#if !defined(AFX_EDITINGDEMODLG_H__5E4CC8E7_1B62_4C61_BB2C_65E45F1C71B4__INCLUDED_)
#define AFX_EDITINGDEMODLG_H__5E4CC8E7_1B62_4C61_BB2C_65E45F1C71B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEditingDemoDlg dialog
#include "MyCug.h"

class CEditingDemoDlg : public CDialog
{
// Construction
public:
	CEditingDemoDlg(CWnd* pParent = NULL);	// standard constructor
	~CEditingDemoDlg();

// Dialog Data
	//{{AFX_DATA(CEditingDemoDlg)
	enum { IDD = IDD_EDITINGDEMO_DIALOG };
	BOOL	m_UseThemes;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditingDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	MyCug m_grid;

	// Generated message map functions
	//{{AFX_MSG(CEditingDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCheckxpthemes();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITINGDEMODLG_H__5E4CC8E7_1B62_4C61_BB2C_65E45F1C71B4__INCLUDED_)
