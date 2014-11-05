#if !defined(AFX_CONNECTDLG_H__B20EBE9C_F00B_11D1_88D1_0080C86AC2FB__INCLUDED_)
#define AFX_CONNECTDLG_H__B20EBE9C_F00B_11D1_88D1_0080C86AC2FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ConnectDlg.h : header file
//

#include "ugodbc.h"
#include "resource.h"
#include "selectsqldlg.h"

/////////////////////////////////////////////////////////////////////////////
// CConnectDlg dialog

class CConnectDlg : public CDialog
{
// Construction
public:

	CSelectSQLDlg	    m_selectSQLDlg;

	CUGODBCDatasource	*m_pOdbc;		 // ODBC datasource

	CString		m_strSQL;
	CString		m_strDSN;	// may be a DSN or a connectstring

	int	 m_nOpenType;		// CRecordset::snapshot, dynaset

	CConnectDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConnectDlg)
	enum { IDD = IDD_CONNECTDLG };
	CButton	m_sqlButton;
	CEdit	m_sqlEdit;
	CComboBox	m_dsnCombo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConnectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConnectDlg)
	afx_msg void OnBrowsebutton();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadiodynaset();
	afx_msg void OnRadiosnapshot();
	virtual void OnOK();
	afx_msg void OnSqldotbutton();
	afx_msg void OnSelchangeDsncombo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONNECTDLG_H__B20EBE9C_F00B_11D1_88D1_0080C86AC2FB__INCLUDED_)
