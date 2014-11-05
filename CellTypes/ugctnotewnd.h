/*************************************************************************
				Class Declaration : CUGNoteTypeEWnd
**************************************************************************
	Source file : UGCTNoteWnd.cpp
	Header file : UGCTNoteWnd.h
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

    Purpose
*************************************************************************/

#ifndef _UGCTNoteWnd_H_
#define _UGCTNoteWnd_H_


//Class Declaration
class UG_CLASS_DECL CUGNoteTypeEWnd : public CEdit
{
// Construction
public:
	CUGNoteTypeEWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUGNoteTypeEWnd)
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual ~CUGNoteTypeEWnd();

protected:
	CBrush m_bkGndBrush;
	CFont  m_font;

	void CalcEditRect();

	// Generated message map functions
protected:
	//{{AFX_MSG(CUGNoteTypeEWnd)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdate();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

};

#endif //#ifndef _UGCTNoteWnd_H_
