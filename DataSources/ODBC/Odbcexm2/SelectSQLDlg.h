#if !defined(AFX_SELECTSQLDLG_H__B56D4544_1E82_11D2_8911_0080C86AC2FB__INCLUDED_)
#define AFX_SELECTSQLDLG_H__B56D4544_1E82_11D2_8911_0080C86AC2FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SelectSQLDlg.h : header file
//
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CSelectSQLDlg dialog

class CSelectSQLDlg : public CDialog
{
// Construction
public:

	CString			m_strSQL, m_strDSN;
	CStringArray	m_strSQLArray;

	CSelectSQLDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectSQLDlg)
	enum { IDD = IDD_PICKSQL };
	CListBox	m_sqlList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectSQLDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectSQLDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeSqllist();
	afx_msg void OnDblclkSqllist();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTSQLDLG_H__B56D4544_1E82_11D2_8911_0080C86AC2FB__INCLUDED_)
