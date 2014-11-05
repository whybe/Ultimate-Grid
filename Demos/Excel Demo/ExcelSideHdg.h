#if !defined(AFX_EXCELSIDEHDG_H__897EE92D_2071_4554_95AD_4A2618B5BD9A__INCLUDED_)
#define AFX_EXCELSIDEHDG_H__897EE92D_2071_4554_95AD_4A2618B5BD9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExcelSideHdg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExcelSideHdg window
#include "UGCtrl.h"

class CExcelSideHdg : public CUGSideHdg
{
// Construction
public:
	CExcelSideHdg();

protected:
	BOOL	m_isSelecting;		// flag identifying if the user is performing
								// multiselection operation using the sideheading
								// this will select the entire row
	int		m_iLastRowSelected;	// member variable indicating the last row set
								// during column selection process, -1 when not used

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExcelSideHdg)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExcelSideHdg();

	// Generated message map functions
protected:
	//{{AFX_MSG(CExcelSideHdg)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXCELSIDEHDG_H__897EE92D_2071_4554_95AD_4A2618B5BD9A__INCLUDED_)
