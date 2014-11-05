#if !defined(AFX_EXCELTOPHDG_H__8C251849_83C6_4B59_AC5A_F92F3331A48F__INCLUDED_)
#define AFX_EXCELTOPHDG_H__8C251849_83C6_4B59_AC5A_F92F3331A48F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExcelTopHdg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExcelTopHdg window
#include "UGCtrl.h"

class CExcelTopHdg : public CUGTopHdg
{
// Construction
public:
	CExcelTopHdg();

protected:
	BOOL	m_isSelecting;		// flag identifying if the user is performing
								// multiselection operation using the tophading
								// this will select the entire column
	int		m_iLastColSelected;	// member variable indicating the last column set
								// during column selection process or -1 when not used

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExcelTopHdg)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExcelTopHdg();

	// Generated message map functions
protected:
	//{{AFX_MSG(CExcelTopHdg)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXCELTOPHDG_H__8C251849_83C6_4B59_AC5A_F92F3331A48F__INCLUDED_)
