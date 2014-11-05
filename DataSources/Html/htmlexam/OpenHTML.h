#if !defined(AFX_OPENHTML_H__EE359B82_333C_11D1_B28B_444553540000__INCLUDED_)
#define AFX_OPENHTML_H__EE359B82_333C_11D1_B28B_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// OpenHTML.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// OpenHTML dialog

class OpenHTML : public CDialog
{
// Construction
public:
	OpenHTML(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(OpenHTML)
	enum { IDD = IDD_OPEN };
	CButton	m_browse;
	CString	m_fileName;
	long	m_TableNumber;
	//}}AFX_DATA

	BOOL	m_File;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(OpenHTML)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(OpenHTML)
	afx_msg void OnBrowse();
	afx_msg void OnFile();
	afx_msg void OnUrl();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENHTML_H__EE359B82_333C_11D1_B28B_444553540000__INCLUDED_)
