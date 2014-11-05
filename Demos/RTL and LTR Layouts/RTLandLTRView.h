// RTLandLTRView.h : interface of the CRTLandLTRView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTLANDLTRVIEW_H__C5781C59_6456_4221_ACED_FE963D48D2A9__INCLUDED_)
#define AFX_RTLANDLTRVIEW_H__C5781C59_6456_4221_ACED_FE963D48D2A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyCug.h"

class CRTLandLTRView : public CView
{
protected: // create from serialization only
	CRTLandLTRView();
	DECLARE_DYNCREATE(CRTLandLTRView)

// Attributes
public:
	CRTLandLTRDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRTLandLTRView)
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
	virtual ~CRTLandLTRView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	MyCug m_grid;

// Generated message map functions
protected:
	//{{AFX_MSG(CRTLandLTRView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSetLrt();
	afx_msg void OnSetRtl();
	afx_msg void OnUpdateSetLrt(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSetRtl(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg void OnThemesNone();
	afx_msg void OnUpdateThemesNone(CCmdUI *pCmdUI);
	afx_msg void OnThemesStyle1();
	afx_msg void OnUpdateThemesStyle1(CCmdUI *pCmdUI);
	afx_msg void OnThemesStyle2();
	afx_msg void OnUpdateThemesStyle2(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in RTLandLTRView.cpp
inline CRTLandLTRDoc* CRTLandLTRView::GetDocument()
   { return (CRTLandLTRDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RTLANDLTRVIEW_H__C5781C59_6456_4221_ACED_FE963D48D2A9__INCLUDED_)
