// Multiselect ExampleView.h : interface of the CMultiselectExampleView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MULTISELECTEXAMPLEVIEW_H__9E95221D_D32B_11D2_83E4_0020359647BF__INCLUDED_)
#define AFX_MULTISELECTEXAMPLEVIEW_H__9E95221D_D32B_11D2_83E4_0020359647BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyCug.h"

class CMultiselectExampleView : public CView
{
protected: // create from serialization only
	CMultiselectExampleView();
	DECLARE_DYNCREATE(CMultiselectExampleView)

// Attributes
public:
	CMultiselectExampleDoc* GetDocument();

// Operations
public:
	MyCug m_grid;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiselectExampleView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	MyCug* GetGrid ( void );
	virtual ~CMultiselectExampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	BOOL m_rowSelection;
	//{{AFX_MSG(CMultiselectExampleView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRndSelection();
	afx_msg void OnClear();
	afx_msg void OnRowCell();
	afx_msg void OnUpdateRowCell(CCmdUI* pCmdUI);
	afx_msg void OnCell();
	afx_msg void OnUpdateCell(CCmdUI* pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnExFocus();
	afx_msg void OnUpdateExFocus(CCmdUI* pCmdUI);
	afx_msg void OnStFocus();
	afx_msg void OnUpdateStFocus(CCmdUI* pCmdUI);
	afx_msg void OnRndCell();
	afx_msg void OnFill();
	afx_msg void OnThemesNone();
	afx_msg void OnUpdateThemesNone(CCmdUI *pCmdUI);
	afx_msg void OnThemesStyle1();
	afx_msg void OnUpdateThemesStyle1(CCmdUI *pCmdUI);
	afx_msg void OnThemesStyle2();
	afx_msg void OnUpdateThemesStyle2(CCmdUI *pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#ifndef _DEBUG  // debug version in Multiselect ExampleView.cpp
inline CMultiselectExampleDoc* CMultiselectExampleView::GetDocument()
   { return (CMultiselectExampleDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTISELECTEXAMPLEVIEW_H__9E95221D_D32B_11D2_83E4_0020359647BF__INCLUDED_)
