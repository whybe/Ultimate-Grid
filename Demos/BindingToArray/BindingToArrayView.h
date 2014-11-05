// BindingToArrayView.h : interface of the CBindingToArrayView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BINDINGTOARRAYVIEW_H__986C34B5_06FB_48FD_A528_4B50783A5191__INCLUDED_)
#define AFX_BINDINGTOARRAYVIEW_H__986C34B5_06FB_48FD_A528_4B50783A5191__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyCug.h"

class CBindingToArrayView : public CView
{
protected: // create from serialization only
	CBindingToArrayView();
	DECLARE_DYNCREATE(CBindingToArrayView)

// Attributes
public:
	CBindingToArrayDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBindingToArrayView)
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
	virtual ~CBindingToArrayView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	MyCug m_grid;

// Generated message map functions
protected:
	//{{AFX_MSG(CBindingToArrayView)
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
};

#ifndef _DEBUG  // debug version in BindingToArrayView.cpp
inline CBindingToArrayDoc* CBindingToArrayView::GetDocument()
   { return (CBindingToArrayDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BINDINGTOARRAYVIEW_H__986C34B5_06FB_48FD_A528_4B50783A5191__INCLUDED_)
