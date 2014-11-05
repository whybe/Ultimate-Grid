#if !defined(AFX_CELLVIEW_H__EE1229A5_25FB_11D1_A90E_0080C85A0F46__INCLUDED_)
#define AFX_CELLVIEW_H__EE1229A5_25FB_11D1_A90E_0080C85A0F46__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CellView.h : header file
//
#include "ugctrl.h"
/////////////////////////////////////////////////////////////////////////////
// CUGCellPropViewer dialog

class CUGCellPropViewer : public CDialog
{
// Construction
public:
	CUGCellPropViewer(CUGCell& cell, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUGCellPropViewer)
	enum { IDD = IDD_PROP_VIEW };
	CString	m_backColor;
	CString	m_font;
	CString	m_bitmap;
	CString	m_hbackColor;
	CString	m_htextColor;
	CString	m_horizAlign;
	CString	m_text;
	CString	m_textColor;
	CString	m_vertAlign;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUGCellPropViewer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUGCellPropViewer)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CELLVIEW_H__EE1229A5_25FB_11D1_A90E_0080C85A0F46__INCLUDED_)
