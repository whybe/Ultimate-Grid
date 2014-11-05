#if !defined(AFX_SQLEditDlg_H__62B5D901_E0DE_4722_A0BC_D009DA0C177C__INCLUDED_)
#define AFX_SQLEditDlg_H__62B5D901_E0DE_4722_A0BC_D009DA0C177C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SQLEditDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSQLEditDlg dialog

class CSQLEditDlg : public CDialog
{
// Construction
public:
	CString GetSQLStr();
	void SetSQLStr( CString szSQL );
	CSQLEditDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSQLEditDlg)
	enum { IDD = IDD_SQLEDIT_DLG };
	CString	m_szSQLStr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSQLEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSQLEditDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SQLEditDlg_H__62B5D901_E0DE_4722_A0BC_D009DA0C177C__INCLUDED_)
