// Stock WatchView.h : interface of the CStockWatchView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_STOCKWATCHVIEW_H__3AD4684C_297F_4D9A_97B3_F38DE4476049__INCLUDED_)
#define AFX_STOCKWATCHVIEW_H__3AD4684C_297F_4D9A_97B3_F38DE4476049__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyCug.h"

class CStockWatchView : public CView
{
protected: // create from serialization only
	CStockWatchView();
	DECLARE_DYNCREATE(CStockWatchView)

// Attributes
public:
	CStockWatchDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStockWatchView)
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
	virtual ~CStockWatchView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	MyCug m_grid;

// Generated message map functions
protected:
	//{{AFX_MSG(CStockWatchView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg void OnThemesNone();
	afx_msg void OnUpdateThemesNone(CCmdUI *pCmdUI);
	afx_msg void OnThemesStyle1();
	afx_msg void OnUpdateThemesStyle1(CCmdUI *pCmdUI);
	afx_msg void OnThemesStyle2();
	afx_msg void OnUpdateThemesStyle2(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in Stock WatchView.cpp
inline CStockWatchDoc* CStockWatchView::GetDocument()
   { return (CStockWatchDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STOCKWATCHVIEW_H__3AD4684C_297F_4D9A_97B3_F38DE4476049__INCLUDED_)
