// ContextSensitiveGridView.h : interface of the CContextSensitiveGridView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTEXTSENSITIVEGRIDVIEW_H__BC1D8F9F_F912_11D3_9831_0020359647BF__INCLUDED_)
#define AFX_CONTEXTSENSITIVEGRIDVIEW_H__BC1D8F9F_F912_11D3_9831_0020359647BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyCug.h"

class CContextSensitiveGridView : public CView
{
protected: // create from serialization only
	CContextSensitiveGridView();
	DECLARE_DYNCREATE(CContextSensitiveGridView)

// Attributes
public:
	CContextSensitiveGridDoc* GetDocument();

// Operations
public:
	MyCug m_grid;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CContextSensitiveGridView)
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
	virtual ~CContextSensitiveGridView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CContextSensitiveGridView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnThemesNone();
	afx_msg void OnUpdateThemesNone(CCmdUI *pCmdUI);
	afx_msg void OnThemesStyle1();
	afx_msg void OnUpdateThemesStyle1(CCmdUI *pCmdUI);
	afx_msg void OnThemesStyle2();
	afx_msg void OnUpdateThemesStyle2(CCmdUI *pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ContextSensitiveGridView.cpp
inline CContextSensitiveGridDoc* CContextSensitiveGridView::GetDocument()
   { return (CContextSensitiveGridDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTEXTSENSITIVEGRIDVIEW_H__BC1D8F9F_F912_11D3_9831_0020359647BF__INCLUDED_)
