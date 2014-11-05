// SpeedTestView.h : interface of the CSpeedTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPEEDTESTVIEW_H__19F98A99_3B6B_49AB_B5FF_09E7D9CFA2CA__INCLUDED_)
#define AFX_SPEEDTESTVIEW_H__19F98A99_3B6B_49AB_B5FF_09E7D9CFA2CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyCug.h"

class CSpeedTestView : public CView
{
protected: // create from serialization only
	CSpeedTestView();
	DECLARE_DYNCREATE(CSpeedTestView)

// Attributes
public:
	CSpeedTestDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpeedTestView)
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
	virtual ~CSpeedTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	MyCug m_grid;

// Generated message map functions
protected:
	//{{AFX_MSG(CSpeedTestView)
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

#ifndef _DEBUG  // debug version in SpeedTestView.cpp
inline CSpeedTestDoc* CSpeedTestView::GetDocument()
   { return (CSpeedTestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPEEDTESTVIEW_H__19F98A99_3B6B_49AB_B5FF_09E7D9CFA2CA__INCLUDED_)
