// Use UG LibView.h : interface of the CUseUGLibView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_USEUGLIBVIEW_H__5E6538DB_8802_46B6_87B2_FE5D32B2E738__INCLUDED_)
#define AFX_USEUGLIBVIEW_H__5E6538DB_8802_46B6_87B2_FE5D32B2E738__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyCug.h"

class CUseUGLibView : public CView
{
protected: // create from serialization only
	CUseUGLibView();
	DECLARE_DYNCREATE(CUseUGLibView)

// Attributes
public:
	CUseUGLibDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUseUGLibView)
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
	virtual ~CUseUGLibView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	MyCug m_grid;

// Generated message map functions
protected:
	//{{AFX_MSG(CUseUGLibView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Use UG LibView.cpp
inline CUseUGLibDoc* CUseUGLibView::GetDocument()
   { return (CUseUGLibDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USEUGLIBVIEW_H__5E6538DB_8802_46B6_87B2_FE5D32B2E738__INCLUDED_)
