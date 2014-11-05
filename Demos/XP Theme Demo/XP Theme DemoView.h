// XP Theme DemoView.h : interface of the CXPThemeDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XPTHEMEDEMOVIEW_H__D1A8E7B4_E26A_4067_B0B4_CF5926E17092__INCLUDED_)
#define AFX_XPTHEMEDEMOVIEW_H__D1A8E7B4_E26A_4067_B0B4_CF5926E17092__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XPThemeDemoGrid.h"

class CXPThemeDemoView : public CView
{
protected: // create from serialization only
	CXPThemeDemoView();
	DECLARE_DYNCREATE(CXPThemeDemoView)

// Attributes
public:
	CXPThemeDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXPThemeDemoView)
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
	virtual ~CXPThemeDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CXPThemeDemoGrid m_grid;

// Generated message map functions
protected:
	//{{AFX_MSG(CXPThemeDemoView)
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnThemesCustom();
	afx_msg void OnThemesNone();
	afx_msg void OnUpdateThemesNone(CCmdUI* pCmdUI);
	afx_msg void OnThemesStyle1();
	afx_msg void OnUpdateThemesStyle1(CCmdUI* pCmdUI);
	afx_msg void OnThemesStyle2();
	afx_msg void OnUpdateThemesStyle2(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in XP Theme DemoView.cpp
inline CXPThemeDemoDoc* CXPThemeDemoView::GetDocument()
   { return (CXPThemeDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XPTHEMEDEMOVIEW_H__D1A8E7B4_E26A_4067_B0B4_CF5926E17092__INCLUDED_)
