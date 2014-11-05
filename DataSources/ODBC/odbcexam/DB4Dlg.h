// DB4Dlg.h : header file
//

#if !defined(AFX_DB4DLG_H__D8C150C9_22E8_11D1_B210_002035964AAA__INCLUDED_)
#define AFX_DB4DLG_H__D8C150C9_22E8_11D1_B210_002035964AAA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CDB4Dlg dialog

class CDB4Dlg : public CDialog
{
public:

    MyCug   m_ctrl;
    
    int     m_index;        // index of the datasource...

// Construction
public:
	CDB4Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDB4Dlg)
	enum { IDD = IDD_DB4_DIALOG };
	CEdit	m_eConnect;
	CComboBox	m_cbSQL;
	CButton	m_buttonOpen;
	CButton	m_buttonBrowse;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDB4Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDB4Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpen();
	afx_msg void OnBrowse();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DB4DLG_H__D8C150C9_22E8_11D1_B210_002035964AAA__INCLUDED_)
