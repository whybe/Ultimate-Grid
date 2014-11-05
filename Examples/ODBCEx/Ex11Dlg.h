// Ex11Dlg.h : header file
//

#include "MyCug.h"

#if !defined(AFX_EX11DLG_H__53F2CD47_B505_11D1_BF47_0020359647BF__INCLUDED_)
#define AFX_EX11DLG_H__53F2CD47_B505_11D1_BF47_0020359647BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CEx11Dlg dialog

class CEx11Dlg : public CDialog
{
// Construction
public:
	CEx11Dlg(CWnd* pParent = NULL);	// standard constructor

	MyCug m_dialog;
	int m_index;

// Dialog Data
	//{{AFX_DATA(CEx11Dlg)
	enum { IDD = IDD_EX11_DIALOG };
	CEdit	m_sql2;
	CComboBox	m_control2;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx11Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEx11Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBrowse();
	afx_msg void OnSql();
	afx_msg void OnCheck1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX11DLG_H__53F2CD47_B505_11D1_BF47_0020359647BF__INCLUDED_)
