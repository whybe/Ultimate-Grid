// RealTimeView.h : interface of the CRealTimeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_REALTIMEVIEW_H__E57232EA_816E_483B_816A_0FD74C282D59__INCLUDED_)
#define AFX_REALTIMEVIEW_H__E57232EA_816E_483B_816A_0FD74C282D59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "demo50g.h"

class CRealTimeView : public CView
{
protected: // create from serialization only
	CRealTimeView();
	DECLARE_DYNCREATE(CRealTimeView)

// Attributes
public:
	CRealTimeDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRealTimeView)
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
	virtual ~CRealTimeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CRealTimeGrid m_grid;

// Generated message map functions
protected:
	//{{AFX_MSG(CRealTimeView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg void On32775();
	afx_msg void OnUpdateThemesStyle2(CCmdUI *pCmdUI);
	afx_msg void OnThemesNone();
	afx_msg void OnUpdateThemesNone(CCmdUI *pCmdUI);
	afx_msg void OnThemesStyle1();
	afx_msg void OnUpdateThemesStyle1(CCmdUI *pCmdUI);
	afx_msg void OnThemesStyle2();
};

#ifndef _DEBUG  // debug version in RealTimeView.cpp
inline CRealTimeDoc* CRealTimeView::GetDocument()
   { return (CRealTimeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REALTIMEVIEW_H__E57232EA_816E_483B_816A_0FD74C282D59__INCLUDED_)
