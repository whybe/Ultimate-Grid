// Cell typesView.h : interface of the CCelltypesView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CELLTYPESVIEW_H__E0663976_3ECD_4B32_8CD5_C17EAD0D43A5__INCLUDED_)
#define AFX_CELLTYPESVIEW_H__E0663976_3ECD_4B32_8CD5_C17EAD0D43A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CellTypeDemoGrid.h"

class CCelltypesView : public CView
{
protected: // create from serialization only
	CCelltypesView();
	DECLARE_DYNCREATE(CCelltypesView)

// Attributes
public:
	CCelltypesDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCelltypesView)
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
	virtual ~CCelltypesView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CCellTypeDemoGrid m_grid;

// Generated message map functions
protected:
	//{{AFX_MSG(CCelltypesView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnViewUsexpthemes1();
	afx_msg void OnViewUsexpthemes2();
	afx_msg void OnViewUsexpthemesNone();
	afx_msg void OnUpdateViewUsexpthemes1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewUsexpthemes2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewUsexpthemesNone(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnViewReset();
};

#ifndef _DEBUG  // debug version in Cell typesView.cpp
inline CCelltypesDoc* CCelltypesView::GetDocument()
   { return (CCelltypesDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CELLTYPESVIEW_H__E0663976_3ECD_4B32_8CD5_C17EAD0D43A5__INCLUDED_)
