// Find and SortView.h : interface of the CFindandSortView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FINDANDSORTVIEW_H__027D08F2_C387_4C75_AC1A_5112C5E6AB1B__INCLUDED_)
#define AFX_FINDANDSORTVIEW_H__027D08F2_C387_4C75_AC1A_5112C5E6AB1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FindGrid.h"

class CFindandSortView : public CView
{
protected: // create from serialization only
	CFindandSortView();
	DECLARE_DYNCREATE(CFindandSortView)

// Attributes
public:
	CFindandSortDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindandSortView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFindandSortView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CFindGrid m_grid;

// Generated message map functions
protected:
	//{{AFX_MSG(CFindandSortView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnThemesNone();
	afx_msg void OnUpdateThemesNone(CCmdUI *pCmdUI);
	afx_msg void OnThemesStyle1();
	afx_msg void OnUpdateThemesStyle1(CCmdUI *pCmdUI);
	afx_msg void OnThemesStyle2();
	afx_msg void OnUpdateThemesStyle2(CCmdUI *pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Find and SortView.cpp
inline CFindandSortDoc* CFindandSortView::GetDocument()
   { return (CFindandSortDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDANDSORTVIEW_H__027D08F2_C387_4C75_AC1A_5112C5E6AB1B__INCLUDED_)
