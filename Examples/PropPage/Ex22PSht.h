#if !defined(AFX_EX22PSHT_H__4BC5D7D6_B853_11D1_8F92_0020359646CF__INCLUDED_)
#define AFX_EX22PSHT_H__4BC5D7D6_B853_11D1_8F92_0020359646CF__INCLUDED_

#include "PPage1.h"	// Added by ClassView
#include "PPage2.h"	// Added by ClassView
#include "PPage3.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Ex22PSht.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEx22PSht

class CEx22PSht : public CPropertySheet
{
	DECLARE_DYNAMIC(CEx22PSht)

// Construction
public:
	CEx22PSht(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CEx22PSht(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx22PSht)
	//}}AFX_VIRTUAL

// Implementation
public:
	CPPage3 m_page3;
	CPPage2 m_page2;
	CPPage1 m_page1;
	virtual ~CEx22PSht();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEx22PSht)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX22PSHT_H__4BC5D7D6_B853_11D1_8F92_0020359646CF__INCLUDED_)
