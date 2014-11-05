#if !defined(AFX_MYSQLDLG_H__6B439BE3_52E6_11D1_B267_002035964AAA__INCLUDED_)
#define AFX_MYSQLDLG_H__6B439BE3_52E6_11D1_B267_002035964AAA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MYSQLDLG.h : header file
//

#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CMySQLDlg dialog

class CMySQLDlg : public CDialog
{
// data
	CDaoDatabase*   m_pData;
	CString			m_csSQLString;
	CString			m_csTableName;
	
// Construction
public:
	BOOL			m_bUseGhost;
	BOOL			m_bAllowEdit;
	CString			m_csPath;
	INT				m_nOpenType;

	CMySQLDlg(CWnd* pParent = NULL);   // standard constructor

	// Interface
	LPTSTR	GetSQLString();
	LPTSTR	GetTableName();
	INT		GetOpenType();
	void	SetDatabase(CDaoDatabase* pDb);


// Dialog Data
	//{{AFX_DATA(CMySQLDlg)
	enum { IDD = IDD_SQLDIALOG };
	CComboBox	m_cbTableName;
	CButton	m_AllowEditCheck;
	CButton	m_GhostCheck;
	CComboBox	m_cbRecordType;
	CComboBox	m_cbSQL;
	BOOL	m_bNumSH;
	BOOL	m_bBase1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySQLDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMySQLDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnGhost();
	afx_msg void OnSelchangeCombo2();
	afx_msg void OnAllowedit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSQLDLG_H__6B439BE3_52E6_11D1_B267_002035964AAA__INCLUDED_)
