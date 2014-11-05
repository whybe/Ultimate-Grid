
#if !defined(AFX_CONNECTDLG_H__3205F60B_E9F2_4D9F_AA1D_CD0FD471C951__INCLUDED_)
#define AFX_CONNECTDLG_H__3205F60B_E9F2_4D9F_AA1D_CD0FD471C951__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConnectDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConnectDlg dialog

class CConnectDlg : public CDialog
{
// Construction
public:
	CConnectDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConnectDlg)
	enum { IDD = IDD_CONNECT_DLG };
	int		m_browseOpt;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConnectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	CString GetConnectionString() { return m_szConnection; }
	CString GetSQLString() { return m_szSQL; }

protected:
	CString m_szConnection;
	CString m_szSQL;
	int DnsBrowse();
	int FileBrowse();

	// Generated message map functions
	//{{AFX_MSG(CConnectDlg)
	virtual void OnOK();
	afx_msg void OnRadioChange( UINT nID );
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioChage( UINT nID );
	afx_msg void OnBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONNECTDLG_H__3205F60B_E9F2_4D9F_AA1D_CD0FD471C951__INCLUDED_)
