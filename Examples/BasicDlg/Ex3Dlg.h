// Ex3Dlg.h : header file
//

#if !defined(AFX_EX3DLG_H__4870F659_0F4B_11D1_B1F2_002035964AAA__INCLUDED_)
#define AFX_EX3DLG_H__4870F659_0F4B_11D1_B1F2_002035964AAA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CEx3Dlg dialog

class CEx3Dlg : public CDialog
{
// Construction
public:

	//: here is the instance of Ultimate Grid for the view
	MyCug	m_ctrl;


	CEx3Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEx3Dlg)
	enum { IDD = IDD_EX3_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx3Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEx3Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCheckxp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX3DLG_H__4870F659_0F4B_11D1_B1F2_002035964AAA__INCLUDED_)
