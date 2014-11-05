#if !defined(AFX_OPENDATABASEDLG_H__E92E8AE3_EEE7_11D3_9825_0020359647BF__INCLUDED_)
#define AFX_OPENDATABASEDLG_H__E92E8AE3_EEE7_11D3_9825_0020359647BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OpenDatabaseDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COpenDatabaseDlg dialog

class COpenDatabaseDlg : public CDialog
{
// Construction
public:
	CString GetSQL();
	CString GetFileName();
	COpenDatabaseDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COpenDatabaseDlg)
	enum { IDD = IDD_OPEN_DB };
	int		m_accessVer;
	CString	m_sql;
	CString	m_fileName;
	int		m_openStyle;
	CString	m_tableName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenDatabaseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COpenDatabaseDlg)
	virtual void OnOK();
	afx_msg void OnBrowse();
	virtual BOOL OnInitDialog();
	afx_msg void OnOpenSql();
	afx_msg void OnOpenTable();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENDATABASEDLG_H__E92E8AE3_EEE7_11D3_9825_0020359647BF__INCLUDED_)
