// Ex22Dlg.h : header file
//

#if !defined(AFX_EX22DLG_H__4BC5D7CB_B853_11D1_8F92_0020359646CF__INCLUDED_)
#define AFX_EX22DLG_H__4BC5D7CB_B853_11D1_8F92_0020359646CF__INCLUDED_

#include "Ex22PSht.h"	// Added by ClassView
#include "PPage1.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CEx22Dlg dialog

class CEx22Dlg : public CDialog
{
// Construction
public:
	CEx22Dlg(CWnd* pParent = NULL);	// standard constructor
	~CEx22Dlg();

// Dialog Data
	//{{AFX_DATA(CEx22Dlg)
	enum { IDD = IDD_EX22_DIALOG };
	BOOL	m_wiz;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx22Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL m_hasBeenRun;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEx22Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnInvoke();
	afx_msg void OnCheck1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX22DLG_H__4BC5D7CB_B853_11D1_8F92_0020359646CF__INCLUDED_)
